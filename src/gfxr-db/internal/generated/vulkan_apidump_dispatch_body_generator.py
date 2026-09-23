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


class VulkanApiDumpDispatchBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating the api dump command dispatch."""

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


class VulkanApiDumpDispatchBodyGenerator(VulkanBaseGenerator, ApiDumpMemberEncodingMixin):
    """Generate one encoder per Vulkan command, plus the name to command lookup.

    Each function writes the parameter buffer for a call exactly as gfxreconstruct's capture layer
    would: parameters in declaration order, then the return value. That is what lets the stock
    VulkanDecoder parse the result and hand it to the sqlite consumer unchanged.

    The command set matches the decoder's rather than the encoder's. A command the decoder skips
    has no Decode_ function, so a buffer produced for it would never be parsed; a command the
    *encoder* skips is only hand written for capture time reasons and still has the plain
    registry derived layout.
    """

    def __init__(self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

        self.emitted_commands = []

    def beginFile(self, genOpts):
        VulkanBaseGenerator.beginFile(self, genOpts)

        # is_cmd_black_listed keys the decoder list off the class name, which this class does not
        # match, so fold it in explicitly.
        for name in self.APICALL_DECODER_BLACKLIST:
            if name not in self.APICALL_BLACKLIST:
                self.APICALL_BLACKLIST.append(name)

        body = inspect.cleandoc(
            '''
            #include "generated_vulkan_apidump_dispatch.h"

            #include "apidump_struct_encode.h"
            #include "generated_vulkan_enum_from_string.h"
            #include "generated_vulkan_struct_from_apidump.h"

            #include "format/api_call_id.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            namespace
            {
            '''
        )
        write(body, file=self.outFile)

    def endFile(self):
        write('', file=self.outFile)

        for command in self.get_all_filtered_cmd_names():
            # all_cmd_params stores (return_type, proto_decl, values).
            return_type, _, values = self.all_cmd_params[command]
            self.write_command(command, return_type, values)

        write('} // namespace', file=self.outFile)
        write('', file=self.outFile)
        self.write_table()

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

    #
    # ApiDumpMemberEncodingMixin hooks.
    #

    def node_expr_by_name(self, name):
        return 'call.Arg("{0}")'.format(name)

    def handle_method(self, owner, member, shape):
        """Output handles of a create or allocate start a new identity; everything else resolves.

        The distinction matters because drivers recycle addresses. Treating a create as a plain
        lookup would fold a new object into the lifetime of a destroyed one that happened to sit
        at the same address, which is exactly what the orphaned objects scene does on purpose.
        """
        if member.is_pointer and self.is_creation_command(owner):
            return 'VulkanHandleCreated{0}'.format('Array' if shape == 'Array' else 'Ptr')

        return 'VulkanHandle{0}'.format(shape)

    #
    # Command classification.
    #

    def is_creation_command(self, name):
        return name.startswith('vkCreate') or name.startswith('vkAllocate')

    def is_destruction_command(self, name):
        return name.startswith('vkDestroy') or name.startswith('vkFree')

    def released_param(self, name, params):
        """The parameter a destroy or free invalidates, or None.

        Always the last handle typed parameter: vkDestroyBuffer(device, buffer, pAllocator) frees
        the second, vkDestroyDevice(device, pAllocator) the first, and vkFreeCommandBuffers frees
        the trailing array. The leading handles are the parent object in every case.
        """
        if not self.is_destruction_command(name):
            return None

        released = None
        for param in params:
            if self.is_handle(param.base_type):
                released = param

        return released

    #
    # Emission.
    #

    def write_command(self, name, return_type, params):
        self.emitted_commands.append(name)

        write(
            'void ApiDump_{0}(ApiDumpContext& ctx, const ApiDumpCall& call)'.format(name),
            file=self.outFile
        )
        write('{', file=self.outFile)

        return_statement = self.make_return_call(return_type)

        if not params and (return_statement is None):
            write('    GFXRECON_UNREFERENCED_PARAMETER(ctx);', file=self.outFile)
            write('    GFXRECON_UNREFERENCED_PARAMETER(call);', file=self.outFile)
        else:
            for param in params:
                write('    {};'.format(self.make_member_call(name, param, params)), file=self.outFile)

            if return_statement is not None:
                write('    {};'.format(return_statement), file=self.outFile)

            # Released after the parameters are encoded, so the call itself still records the id
            # the object had while it existed.
            released = self.released_param(name, params)
            if released is not None:
                object_type = self.handle_object_types.get(released.base_type)
                if object_type is not None:
                    method = 'ReleaseHandleArray' if released.is_array else 'ReleaseHandle'
                    write(
                        '    ctx.{0}({1}, {2});'.format(method, self.node_expr(released), object_type),
                        file=self.outFile
                    )

        write('}', file=self.outFile)
        write('', file=self.outFile)

    def make_return_call(self, return_type):
        """The statement encoding the return value, which gfxreconstruct writes last."""
        if (return_type is None) or (return_type == 'void') or (return_type == ''):
            return None

        node = 'call.ReturnValue()'

        if self.is_enum(return_type):
            return 'ctx.EnumValue({0}, EnumFromString_{1})'.format(node, self.canonical_enum(return_type))

        if self.is_flags(return_type):
            bits = self.flag_enum_bits_type(return_type)
            call = 'Flags64Value' if self.is_64bit_flags(return_type) else 'FlagsValue'
            if bits is not None:
                return 'ctx.{0}({1}, EnumFromString_{2})'.format(call, node, self.canonical_enum(bits))
            return 'ctx.{0}({1})'.format(call, node)

        if return_type.startswith('PFN_'):
            return 'ctx.FunctionPtrValue({0})'.format(node)

        scalar = self.scalar_method_name(return_type, self.make_invocation_type_name(return_type))
        if scalar is None:
            return 'ctx.UInt64Value({0}) /* unmapped return type {1} */'.format(node, return_type)

        return 'ctx.{0}Value({1})'.format(scalar, node)

    def write_table(self):
        write('const ApiDumpCommandTable& GetApiDumpCommandTable()', file=self.outFile)
        write('{', file=self.outFile)
        write('    static const ApiDumpCommandTable table = {', file=self.outFile)

        for name in self.emitted_commands:
            write(
                '        {{ "{0}", {{ format::ApiCallId::ApiCall_{0}, ApiDump_{0} }} }},'.format(name),
                file=self.outFile
            )

        write('    };', file=self.outFile)
        write('', file=self.outFile)
        write('    return table;', file=self.outFile)
        write('}', file=self.outFile)
