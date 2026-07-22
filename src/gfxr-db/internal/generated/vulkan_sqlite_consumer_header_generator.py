#!/usr/bin/python3 -i
#
# Copyright (c) 2022-2023 LunarG, Inc.
# Copyright (c) 2024-2026 The Sokatoa Project Authors
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

import sys
import inspect
from vulkan_consumer_header_generator import VulkanConsumerHeaderGenerator, VulkanConsumerHeaderGeneratorOptions, write


class VulkanSqliteConsumerHeaderGeneratorOptions(VulkanConsumerHeaderGeneratorOptions):
    """Options for generating a C++ class for Vulkan capture file to vulkan sqlite database generation."""

    def __init__(
        self,
        class_name,
        base_class_header,
        is_override,
        constructor_args='',
        blacklists=None, # Path to json file listing apicalls and structs to ignore.
        platform_types=None, # Path to json file listing platform (WIN32, X11, etc.) defined types.
        filename=None,
        directory='.',
        prefix_text=[],
        protect_file=False,
        protect_feature=True,
        extra_headers=[]
    ):
        VulkanConsumerHeaderGeneratorOptions.__init__(
            self,
            class_name,
            base_class_header,
            is_override,
            constructor_args,
            blacklists,
            platform_types,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extra_headers=extra_headers
        )


class VulkanSqliteConsumerHeaderGenerator(VulkanConsumerHeaderGenerator):
    """VulkanSqliteConsumerHeaderGenerator - subclass of BaseGenerator.
    Generate a C++ class for Vulkan capture file to vulkan sqlite database generation.
    """

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanConsumerHeaderGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        self.customImplementationRequired = {
            'vkCmdBuildAccelerationStructuresIndirectKHR'
        }

    def beginFile(self, gen_opts):
        VulkanConsumerHeaderGenerator.beginFile(self, gen_opts)
        # Each code generator is passed a blacklist like framework\generated\vulkan_generators\blacklists.json
        # of functions and structures not to generate code for. We need all functions and structs to be generated
        # thus we are clearing the list before generating features.
        self.APICALL_BLACKLIST.clear()
        # These functions aren't captured by GFXR, and don't really make sense to capture either. Recording them
        # would involve storing function pointers in the database (and GFXR file), which doesn't make sense.
        self.APICALL_BLACKLIST.append('vkGetInstanceProcAddr')
        self.APICALL_BLACKLIST.append('vkGetDeviceProcAddr')
        # Loader/layer-negotiation calls reporting per-machine capability info (available layers,
        # extensions, API version). gfxreconstruct's own replay consumer re-queries the replay
        # machine's real driver directly for these rather than replaying a recorded value (see
        # vulkan_replay_consumer_base.cpp), so it doesn't generate an args:: struct for them either.
        self.APICALL_BLACKLIST.append('vkEnumerateInstanceExtensionProperties')
        self.APICALL_BLACKLIST.append('vkEnumerateDeviceExtensionProperties')
        self.APICALL_BLACKLIST.append('vkEnumerateInstanceLayerProperties')
        self.APICALL_BLACKLIST.append('vkEnumerateDeviceLayerProperties')
        self.APICALL_BLACKLIST.append('vkEnumerateInstanceVersion')
        # Add the following to the blacklist due to custom implementations in vulkan_sqlite_consumer_base
        # Custom implementations are needed due to generated code using uint64_t or void* for pData,
        # while actual code uses DescriptorUpdateTemplateDecoder* instead.
        # The original black list also includes these functions (but also includes
        # vkCmdPushDescriptorSetWithTemplate2/vkCmdPushDescriptorSetWithTemplate2KHR which are not
        # affected by this issue).
        self.APICALL_BLACKLIST.append('vkUpdateDescriptorSetWithTemplate')
        self.APICALL_BLACKLIST.append('vkUpdateDescriptorSetWithTemplateKHR')
        self.APICALL_BLACKLIST.append('vkCmdPushDescriptorSetWithTemplate')
        self.APICALL_BLACKLIST.append('vkCmdPushDescriptorSetWithTemplateKHR')
        # Add the following to the blacklist due to missing support issues, attempt to re-enable once feature is required
        self.APICALL_BLACKLIST.append('vkCreateIndirectExecutionSetEXT')
        # VK_NV_external_compute_queue: no args:: struct or consumer virtual exists anywhere upstream
        # (also blacklisted in gfxreconstruct's own "functions-all"); brand new, no prior gfxr-sqlite
        # tracking to preserve.
        self.APICALL_BLACKLIST.append('vkCreateExternalComputeQueueNV')
        self.APICALL_BLACKLIST.append('vkDestroyExternalComputeQueueNV')
        self.APICALL_BLACKLIST.append('vkGetExternalComputeQueueDataNV')
        # VK_EXT_descriptor_buffer extension functions need custom struct handling for unions
        self.APICALL_BLACKLIST.append('vkGetBufferOpaqueCaptureDescriptorDataEXT')
        self.APICALL_BLACKLIST.append('vkGetImageOpaqueCaptureDescriptorDataEXT')
        self.APICALL_BLACKLIST.append('vkGetImageViewOpaqueCaptureDescriptorDataEXT')
        self.APICALL_BLACKLIST.append('vkGetSamplerOpaqueCaptureDescriptorDataEXT')
        self.APICALL_BLACKLIST.append('vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT')
        # VK_ARM_tensors: same OpaqueCaptureDescriptorData family/reason as the EXT ones above; also
        # blacklisted upstream (gfxreconstruct's own blacklists.json "functions-all"), so no args::
        # struct exists to generate against.
        self.APICALL_BLACKLIST.append('vkGetTensorOpaqueCaptureDescriptorDataARM')
        self.APICALL_BLACKLIST.append('vkGetTensorViewOpaqueCaptureDescriptorDataARM')
        self.APICALL_BLACKLIST.append('vkGetDescriptorSetLayoutSizeEXT')
        self.APICALL_BLACKLIST.append('vkGetDescriptorSetLayoutBindingOffsetEXT')
        self.APICALL_BLACKLIST.append('vkGetDescriptorEXT')
        self.APICALL_BLACKLIST.append('vkCmdBindDescriptorBuffersEXT')
        self.APICALL_BLACKLIST.append('vkCmdSetDescriptorBufferOffsetsEXT')
        self.APICALL_BLACKLIST.append('vkCmdBindDescriptorBufferEmbeddedSamplersEXT')
        self.APICALL_BLACKLIST.append('vkCmdSetDescriptorBufferOffsets2EXT')
        self.APICALL_BLACKLIST.append('vkCmdBindDescriptorBufferEmbeddedSamplers2EXT')

    def write_class_contents(self):
        """
        Method Override
        Performs C++ code generation for the feature.
        """

        for cmd in self.get_all_filtered_cmd_names():
            if cmd not in self.customImplementationRequired:
                info = self.all_cmd_params[cmd]
                return_type = info[0]
                values = info[2]

                decl = self.make_consumer_func_decl(
                    return_type, 'Process_' + cmd, values
                )

                cmddef = '\n'
                if self.genOpts.is_override:
                    cmddef += self.indent(
                        'virtual ' + decl + ' override;', self.INDENT_SIZE
                    )
                else:
                    cmddef += self.indent(
                        'virtual ' + decl + ' {}', self.INDENT_SIZE
                    )

                write(cmddef, file=self.outFile)
