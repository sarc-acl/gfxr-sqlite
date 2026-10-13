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
from apidump_member_encoding import ApiDumpMemberEncodingMixin
from vulkan_base_generator import VulkanBaseGeneratorOptions, VulkanBaseGenerator, write


class VulkanStructFromApiDumpBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating the api dump struct encoders."""

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


class VulkanStructFromApiDumpBodyGenerator(VulkanBaseGenerator, ApiDumpMemberEncodingMixin):
    """Generate the encoders that turn api dump JSON structs into gfxreconstruct parameter buffers.

    This is a transform of gfxreconstruct's own struct encoder generator: same member order, same
    encoder primitives, same array and pointer handling, but reading each member out of a JSON node
    instead of a C struct. Keeping the two in step is what makes the produced buffers decodable by
    the stock gfxreconstruct decoders.

    Structs on the shared blacklist are skipped, as are unions, exactly as in the gfxreconstruct
    generator. Those are hand written in custom_vulkan_struct_from_apidump.cpp, mirroring whichever
    representation gfxreconstruct's own hand written encoder chose.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include "generated_vulkan_struct_from_apidump.h"

            #include "apidump_struct_encode.h"
            #include "generated_vulkan_enum_from_string.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        write('', file=self.outFile)

        for struct in self.get_all_filtered_struct_names():
            if struct in self.all_struct_aliases:
                continue
            self.write_struct_body(struct, self.all_struct_members[struct])

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

    def write_struct_body(self, struct, members):
        write(
            'template <> void StructFromApiDump<{0}>(ApiDumpContext& ctx, const ApiDumpNode& value)'.format(struct),
            file=self.outFile
        )
        write('{', file=self.outFile)

        if not members:
            write('    GFXRECON_UNREFERENCED_PARAMETER(ctx);', file=self.outFile)
            write('    GFXRECON_UNREFERENCED_PARAMETER(value);', file=self.outFile)
        else:
            for member in members:
                write('    {};'.format(self.make_member_call(struct, member, members)), file=self.outFile)

        write('}', file=self.outFile)
        write('', file=self.outFile)

    def node_expr_by_name(self, name):
        return 'value["{0}"]'.format(name)

    def node_expr(self, member):
        return 'value["{0}"]'.format(member.name)
