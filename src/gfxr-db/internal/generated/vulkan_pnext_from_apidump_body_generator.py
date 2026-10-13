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


class VulkanPNextFromApiDumpBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating the api dump pNext chain encoder."""

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


class VulkanPNextFromApiDumpBodyGenerator(VulkanBaseGenerator):
    """Generate the sType dispatch that encodes a pNext chain from api dump JSON.

    A transform of gfxreconstruct's EncodePNextStruct generator. It switches on the recorded sType
    instead of a live one and recurses through the nested members, which is how the layer writes a
    chain: each struct's pNext is a member of that struct, carrying the next link.

    Two deliberate differences from the gfxreconstruct original. It does not skip the loader
    specific structure types, which a layer never sees, and an unrecognised sType logs and walks on
    to the rest of the chain rather than calling into the capture manager, which does not exist
    here.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        body = inspect.cleandoc(
            '''
            #include "apidump_struct_encode.h"

            #include "generated_vulkan_enum_from_string.h"
            #include "generated_vulkan_struct_from_apidump.h"

            #include "util/logging.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            namespace
            {

            /** Reads the sType of a chain link, by number when the layer wrote one and by name otherwise. */
            bool ResolveStructureType(ApiDumpContext& ctx, std::string_view text, VkStructureType& out)
            {
                int64_t numeric = 0;
                if (ParseLeadingSigned(text, numeric))
                {
                    out = static_cast<VkStructureType>(numeric);
                    return true;
                }

                if (text.empty() || !EnumFromString_VkStructureType(text, out))
                {
                    ++ctx.MutableStats().unknown_structure_types;
                    return false;
                }

                return true;
            }

            } // namespace

            void PNextFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value)
            {
                if (value.IsNullPointer() || !value.HasData())
                {
                    ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
                    return;
                }

                VkStructureType stype{};
                const std::string_view stype_text = value["sType"].ValueString();

                if (!ResolveStructureType(ctx, stype_text, stype))
                {
                    // The chain cannot be walked past a link whose type is unknown, because the
                    // members that follow cannot be interpreted. Encode a null so the buffer stays
                    // well formed and let the conversion summary report it.
                    ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
                    return;
                }

                switch (stype)
                {
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        for struct in sorted(self.all_possible_extendable_structs):
            if (struct not in self.struct_type_names) or (struct in self.all_struct_aliases):
                continue

            write('    case {0}:'.format(self.struct_type_names[struct]), file=self.outFile)
            write('        StructPtrFromApiDump<{0}>(ctx, value);'.format(struct), file=self.outFile)
            write('        break;', file=self.outFile)

        body = inspect.cleandoc(
            '''
                default:
                    ++ctx.MutableStats().unknown_structure_types;
                    GFXRECON_LOG_WARNING("PNextFromApiDump: unrecognized structure type %d", stype);
                    ctx.Encoder().EncodeStructPtrPreamble(0, true, false);
                    break;
                }
            }

            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
            '''
        )
        write(body, file=self.outFile)

        VulkanBaseGenerator.endFile(self)

    def need_feature_generation(self):
        return bool(self.feature_struct_members)
