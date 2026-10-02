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


class VulkanApiDumpDispatchHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for declaring the api dump command dispatch."""

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


class VulkanApiDumpDispatchHeaderGenerator(VulkanBaseGenerator):
    """Declare the api dump command lookup.

    The per command encoders stay internal to the generated body; only the table is exported,
    because the processor reaches every command through it by name.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include <string_view>
            #include <unordered_map>

            #include "apidump_context.h"
            #include "apidump_json.h"

            #include "format/api_call_id.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            /** Writes the parameter buffer for one recorded call. */
            using PFN_ApiDumpEncode = void (*)(ApiDumpContext& ctx, const ApiDumpCall& call);

            struct ApiDumpCommandInfo
            {
                format::ApiCallId call_id;
                PFN_ApiDumpEncode encode;
            };

            using ApiDumpCommandTable = std::unordered_map<std::string_view, ApiDumpCommandInfo>;

            /** Every command the decoder can parse, keyed by the name the layer records.
             *
             * A name missing from this table is a command gfxreconstruct does not decode, so there
             * is nothing useful to write for it; the processor skips and counts those.
             */
            const ApiDumpCommandTable& GetApiDumpCommandTable();
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
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
        return bool(self.feature_cmd_params)
