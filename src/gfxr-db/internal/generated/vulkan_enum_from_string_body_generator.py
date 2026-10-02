#!/usr/bin/python3 -i
#
# Copyright (c) 2026 The Sokatoa Project Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import inspect
import sys
from vulkan_base_generator import VulkanBaseGeneratorOptions, VulkanBaseGenerator, write


class VulkanEnumFromStringBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating the api dump enum name lookup tables."""

    def __init__(
        self,
        blacklists=None,  # Path to JSON file listing apicalls and structs to ignore.
        platform_types=None,  # Path to JSON file listing platform (WIN32, X11, etc.) defined types.
        filename=None,
        directory='.',
        prefixText=[],
        protectFile=False,
        protectFeature=True,
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefixText,
            protectFile,
            protectFeature,
            extra_headers=extra_headers
        )


class VulkanEnumFromStringBodyGenerator(VulkanBaseGenerator):
    """Generate the tables mapping Vulkan enumerant spellings back to their values.

    Each table is a file scope constexpr array sorted by name at generation time and binary
    searched at runtime, so no static initialisation runs at load.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

        # Enum name -> { alias spelling: target spelling }.
        #
        # KhronosBaseGenerator.genGroup deliberately drops enumerants carrying an alias attribute,
        # because emitting them alongside their target would produce duplicate case labels in the
        # to-string direction. Coming the other way they are exactly what we need: the layer prints
        # whichever C spelling the value resolved to, which may well be the alias.
        self.enum_alias_enumerants = dict()

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include "generated_vulkan_enum_from_string.h"

            #include "apidump_enum_lookup.h"

            #include <utility>

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        write('', file=self.outFile)
        self.make_bodies()

        body = inspect.cleandoc(
            '''
            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
            '''
        )
        write(body, file=self.outFile)

        VulkanBaseGenerator.endFile(self)

    def need_feature_generation(self):
        return bool(self.feature_struct_members)

    def genGroup(self, groupinfo, group_name, alias):
        VulkanBaseGenerator.genGroup(self, groupinfo, group_name, alias)

        if alias:
            return

        aliases = dict()
        for elem in groupinfo.elem:
            name = elem.get('name')
            target = elem.get('alias')
            if name and target:
                aliases[name] = target

        self.enum_alias_enumerants[group_name] = aliases

    def collect_spellings(self, enum):
        """Returns every C spelling that resolves for this enum, sorted for binary search.

        An alias is only emitted when its target survived the supported-subset filter in
        KhronosBaseGenerator.genGroup, otherwise the spelling would not exist in the headers we
        compile against.
        """
        enumerants = self.enumEnumerants.get(enum, dict())
        spellings = set(enumerants.keys())

        for alias, target in self.enum_alias_enumerants.get(enum, dict()).items():
            if target in enumerants:
                spellings.add(alias)

        # std::string_view compares bytes, and these spellings are ASCII, so Python's ordering is
        # the same ordering LookupEnumName will binary search with.
        return sorted(spellings)

    def make_bodies(self):
        for enum in sorted(self.enum_names):
            if enum in self.enumAliases:
                continue

            spellings = self.collect_spellings(enum)

            write(
                'bool EnumFromString_{0}(std::string_view name, {0}& out)'.format(enum),
                file=self.outFile
            )
            write('{', file=self.outFile)

            if not spellings:
                # Extension enums with no enumerants in this registry. Keep the symbol so callers
                # generated from the same registry always link.
                write('    GFXRECON_UNREFERENCED_PARAMETER(name);', file=self.outFile)
                write('    GFXRECON_UNREFERENCED_PARAMETER(out);', file=self.outFile)
                write('    return false;', file=self.outFile)
            else:
                write(
                    '    static constexpr std::pair<std::string_view, {0}> kTable[] = {{'.format(enum),
                    file=self.outFile
                )
                for spelling in spellings:
                    write('        {{ "{0}", {0} }},'.format(spelling), file=self.outFile)
                write('    };', file=self.outFile)
                write('', file=self.outFile)
                write('    return LookupEnumName(kTable, name, out);', file=self.outFile)

            write('}', file=self.outFile)
            write('', file=self.outFile)
