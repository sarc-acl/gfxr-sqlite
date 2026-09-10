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


class VulkanEnumFromStringHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating declarations of the api dump enum name lookups."""

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


class VulkanEnumFromStringHeaderGenerator(VulkanBaseGenerator):
    """Generate declarations mapping Vulkan enumerant spellings back to their values.

    An api dump records enums by name only, so the adapter needs the inverse of gfxreconstruct's
    enum-to-string tables. Generating them from vk.xml means a Vulkan-Headers bump picks up new
    enums and new enumerants without anyone editing a table by hand.

    The functions carry the type in their name rather than being overloads or template
    specializations. Vulkan makes both of those unreliable here: every VkFooFlags typedef collapses
    to the same VkFlags, and a 64 bit VkFooFlagBits2 is a VkFlags64 typedef rather than a distinct
    enum type, so overload resolution cannot tell them apart. Callers are generated too, so the
    verbosity costs nothing.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

        # Enum name -> 'VkFlags64' for the 64 bit bitmask typedefs, 'VkFlags' otherwise.
        self.enum_bitwidth = dict()

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include "format/platform_types.h"

            #include <string_view>

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            /** Resolves an enumerant spelling to its value, returning false for an unknown name.
             *
             * Alias spellings are included, so both VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
             * and its _KHR spelling resolve, whichever one the layer happened to print.
             */
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        write('', file=self.outFile)
        self.make_decls()

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
        if groupinfo.elem.get('bitwidth') == '64':
            self.enum_bitwidth[group_name] = 'VkFlags64'
        else:
            self.enum_bitwidth[group_name] = 'VkFlags'

    def make_decls(self):
        for enum in sorted(self.enum_names):
            if enum in self.enumAliases:
                continue

            write(
                'bool EnumFromString_{0}(std::string_view name, {0}& out);'.format(enum),
                file=self.outFile
            )

        write('', file=self.outFile)
