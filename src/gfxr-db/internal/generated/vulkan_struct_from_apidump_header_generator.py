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


class VulkanStructFromApiDumpHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for declaring the api dump struct encoders."""

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


class VulkanStructFromApiDumpHeaderGenerator(VulkanBaseGenerator):
    """Declare a StructFromApiDump specialization for every Vulkan struct and union.

    Declarations cover the hand written specializations as well as the generated ones, so a caller
    only has to include this header to reach any of them, and so that a struct with no
    specialization anywhere fails at link time instead of quietly encoding nothing.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include "format/platform_types.h"

            #include "apidump_context.h"
            #include "apidump_json.h"
            #include "apidump_struct_encode.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        write('', file=self.outFile)

        names = set(self.all_struct_members.keys())
        names.update(self.all_union_members.keys())

        for name in sorted(names):
            if (name in self.all_struct_aliases) or (name in self.all_union_aliases):
                continue

            write(
                'template <> void StructFromApiDump<{0}>(ApiDumpContext& ctx, const ApiDumpNode& value);'
                .format(name),
                file=self.outFile
            )

        write('', file=self.outFile)

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
