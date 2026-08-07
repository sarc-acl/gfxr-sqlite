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
import textwrap
from vulkan_base_generator import VulkanBaseGenerator, VulkanBaseGeneratorOptions, write


class VulkanSqliteConsumerBodyGeneratorOptions(VulkanBaseGeneratorOptions):
    """Options for generating a C++ class for Vulkan capture file to vulkan sqlite database generation."""

    def __init__(
        self,
        # Path to vulkan sqlite database listing apicalls and structs to ignore.
        blacklists=None,
        # Path to vulkan sqlite database listing platform (WIN32, X11, etc.) defined types.
        platform_types=None,
        filename=None,
        directory='.',
        prefix_text=[],
        protect_file=False,
        protect_feature=True,
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extra_headers=extra_headers
        )


class VulkanSqliteConsumerBodyGenerator(VulkanBaseGenerator):
    """VulkanSqliteConsumerBodyGenerator - subclass of BaseGenerator.
    Generates C++ member definitions for the VulkanSqliteConsumer class responsible for
    generating a textfile containing decoded Vulkan API call parameter data.
    Generate a C++ class for Vulkan capture file to vulkan sqlite database generation.
    """

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        self.customImplementationRequired = {
            # Consider putting extensions into overrides instead of custom
            # implementations unless fully custom implementation is required
            # Every event needs to be added to the apiEvents table and as such
            # custom implementations will need to add themselves, however
            # extending implementations can simply call the base class
            'vkCmdBuildAccelerationStructuresIndirectKHR'
        }

        # New Vulkan commands using VkDeviceAddress/pInfo structs instead of VkBuffer handles.
        # These cannot be tracked in draw/bind tables until buffer address resolution is supported.
        self.addressBasedCmds = {
            # Draw commands
            'vkCmdDrawIndirect2KHR',
            'vkCmdDrawIndexedIndirect2KHR',
            'vkCmdDrawIndirectCount2KHR',
            'vkCmdDrawIndexedIndirectCount2KHR',
            'vkCmdDrawIndirectByteCount2EXT',
            'vkCmdDrawMeshTasksIndirect2EXT',
            'vkCmdDrawMeshTasksIndirectCount2EXT',
            # Dispatch commands
            'vkCmdDispatchIndirect2KHR',
            # Bind commands
            'vkCmdBindIndexBuffer3KHR',
            'vkCmdBindVertexBuffers3KHR',
            'vkCmdBindTransformFeedbackBuffers2EXT',
        }

        self.allSpecialFunctions = set()
        self.seenFunctions = set()
        def make_function_list(functions):
            for function in functions:
                assert function not in self.allSpecialFunctions, f"{function} is already in another list"
            self.allSpecialFunctions.update(functions)
            return functions

        self.createSurface = make_function_list({
            'vkCreateDisplayPlaneSurfaceKHR',
            'vkCreateXlibSurfaceKHR',
            'vkCreateXcbSurfaceKHR',
            'vkCreateWaylandSurfaceKHR',
            'vkCreateAndroidSurfaceKHR',
            'vkCreateWin32SurfaceKHR',
            'vkCreateStreamDescriptorSurfaceGGP',
            'vkCreateViSurfaceNN',
            'vkCreateIOSSurfaceMVK',
            'vkCreateMacOSSurfaceMVK',
            'vkCreateImagePipeSurfaceFUCHSIA',
            'vkCreateMetalSurfaceEXT',
            'vkCreateHeadlessSurfaceEXT',
            'vkCreateDirectFBSurfaceEXT',
            'vkCreateScreenSurfaceQNX'
        })

        self.destroySurface = make_function_list({
            'vkDestroySurfaceKHR'
        })

        self.commandPool = make_function_list({
            "vkCreateCommandPool"
        })

        self.destroyCommandPool = make_function_list({
            "vkDestroyCommandPool"
        })

        self.resetCommandPool = make_function_list({
            "vkResetCommandPool"
        })

        self.allocateCommandBuffers = make_function_list({
            "vkAllocateCommandBuffers"
        })

        self.beginCommandBuffer = make_function_list({
            "vkBeginCommandBuffer"
        })

        self.endCommandBuffer = make_function_list({
            "vkEndCommandBuffer"
        })

        self.freeCommandBuffers = make_function_list({
            "vkFreeCommandBuffers"
        })

        self.resetCommandBuffer = make_function_list({
            "vkResetCommandBuffer"
        })

        self.beginRenderPass = make_function_list({
            "vkCmdBeginRenderPass"
        })
        self.beginRenderPass2 = make_function_list({
            "vkCmdBeginRenderPass2KHR",
            "vkCmdBeginRenderPass2"
        })

        self.nextRenderSubpass = make_function_list({
            "vkCmdNextSubpass"
        })
        self.nextRenderSubpass2 = make_function_list({
            "vkCmdNextSubpass2KHR",
            "vkCmdNextSubpass2"
        })

        self.endRenderPass = make_function_list({
            "vkCmdEndRenderPass"
        })
        self.endRenderPass2 = make_function_list({
            "vkCmdEndRenderPass2KHR",
            "vkCmdEndRenderPass2"
        })

        self.beginDynamicRenderPass = make_function_list({
            "vkCmdBeginRendering",
            "vkCmdBeginRenderingKHR"
        })
        self.endDynamicRenderPass = make_function_list({
            "vkCmdEndRendering",
            "vkCmdEndRenderingKHR"
        })

        self.secondaryExecution = make_function_list({
            "vkCmdExecuteCommands"
        })

        self.bindPipeline = make_function_list({
            "vkCmdBindPipeline"
        })

        self.bindShaderObject = make_function_list({
            "vkCmdBindShadersEXT"
        })

        self.bindVertexBuffers = make_function_list({
            "vkCmdBindVertexBuffers",
            "vkCmdBindVertexBuffers2",
            "vkCmdBindVertexBuffers2EXT"
        })

        self.bindIndexBuffer = make_function_list({
            "vkCmdBindIndexBuffer",
            "vkCmdBindIndexBuffer2KHR",
            "vkCmdBindIndexBuffer2"
        })

        # Transfer commands that have specialized instance tables for querying src/dst resources.
        # These include buffer copies, image copies, buffer-image copies, and blit operations.
        self.transferCommands = make_function_list({
            "vkCmdCopyBuffer",
            "vkCmdCopyBuffer2",
            "vkCmdCopyBuffer2KHR",
            "vkCmdCopyImage",
            "vkCmdCopyImage2",
            "vkCmdCopyImage2KHR",
            "vkCmdCopyBufferToImage",
            "vkCmdCopyBufferToImage2",
            "vkCmdCopyBufferToImage2KHR",
            "vkCmdCopyImageToBuffer",
            "vkCmdCopyImageToBuffer2",
            "vkCmdCopyImageToBuffer2KHR",
            "vkCmdBlitImage",
            "vkCmdBlitImage2",
            "vkCmdBlitImage2KHR",
            "vkCmdResolveImage",
            "vkCmdResolveImage2",
            "vkCmdResolveImage2KHR"
        })

        # Commands that are important enough to be displayed as nodes in the command tree.
        # These are synchronization commands, queries, and other miscellaneous operations.
        # Getters and bind commands, as well as vkCmdPushConstants, should instead be parsed and
        # shown in the pipeline view.
        # Note: Transfer commands (buffer/image copies, blits) have been moved to self.transferCommands
        # Note: Acceleration structure operations have specialized tables and are not in this list
        self.trackedCommands = make_function_list({
            "vkCmdBeginQuery",
            "vkCmdBeginQueryIndexedEXT",
            "vkCmdBeginTransformFeedbackEXT",
            "vkCmdBuildAccelerationStructureNV",
            "vkCmdClearAttachments",
            "vkCmdClearColorImage",
            "vkCmdClearDepthStencilImage",
            "vkCmdCopyAccelerationStructureNV",
            "vkCmdCopyAccelerationStructureToMemoryKHR",
            "vkCmdCopyMemoryToAccelerationStructureKHR",
            "vkCmdCopyMemoryToMicromapEXT",
            "vkCmdCopyMicromapEXT",
            "vkCmdCopyMicromapToMemoryEXT",
            "vkCmdCopyQueryPoolResults",
            "vkCmdEndQuery",
            "vkCmdEndQueryIndexedEXT",
            "vkCmdEndTransformFeedbackEXT",
            "vkCmdExecuteGeneratedCommandsEXT",
            "vkCmdExecuteGeneratedCommandsNV",
            "vkCmdFillBuffer",
            "vkCmdPipelineBarrier",
            "vkCmdPipelineBarrier2",
            "vkCmdPipelineBarrier2KHR",
            "vkCmdPreprocessGeneratedCommandsEXT",
            "vkCmdPreprocessGeneratedCommandsNV",
            "vkCmdResetEvent",
            "vkCmdResetEvent2",
            "vkCmdResetEvent2KHR",
            "vkCmdResetQueryPool",
            "vkCmdSetCheckpointNV",
            "vkCmdSetEvent",
            "vkCmdSetEvent2",
            "vkCmdSetEvent2KHR",
            "vkCmdSetPerformanceMarkerINTEL",
            "vkCmdSetPerformanceOverrideINTEL",
            "vkCmdSetPerformanceStreamMarkerINTEL",
            "vkCmdUpdateBuffer",
            "vkCmdUpdatePipelineIndirectBufferNV",
            "vkCmdWaitEvents",
            "vkCmdWaitEvents2",
            "vkCmdWaitEvents2KHR",
            "vkCmdWriteAccelerationStructuresPropertiesKHR",
            "vkCmdWriteAccelerationStructuresPropertiesNV",
            "vkCmdWriteBufferMarker2AMD",
            "vkCmdWriteBufferMarkerAMD",
            "vkCmdWriteMicromapsPropertiesEXT"
        })

        self.trackedDeviceCommands = make_function_list({
            "vkResetFences",
            "vkWaitForFences",
            "vkWaitSemaphores",
            "vkSignalSemaphore",
            "vkWaitSemaphoresKHR",
            "vkSignalSemaphoreKHR",
            "vkDeviceWaitIdle",
            "vkAllocateMemory",
            "vkFreeMemory",
            "vkMapMemory",
            "vkMapMemory2",
            "vkMapMemory2KHR",
            "vkUnmapMemory",
            "vkUnmapMemory2",
            "vkUnmapMemory2KHR",
            "vkFlushMappedMemoryRanges",
            "vkInvalidateMappedMemoryRanges",
            "vkBindBufferMemory",
            "vkBindBufferMemory2",
            "vkBindBufferMemory2KHR",
            "vkBindImageMemory",
            "vkBindImageMemory2",
            "vkBindImageMemory2KHR",
            "vkWaitForPresentKHR",
            "vkWaitForPresent2KHR",
        })

        self.flagsType = dict()
        self.flagsTypeAlias = dict()
        self.flagEnumBitsType = dict()


    def beginFile(self, gen_opts):
        """Method override."""
        VulkanBaseGenerator.beginFile(self, gen_opts)

        includes = inspect.cleandoc(
            '''
            #include "util/defines.h"
            #include "generated/generated_vulkan_sqlite_consumer.h"
            #include "generated/generated_vulkan_struct_to_sqlite.h"
            #include "decode/consumer_utils.h"
            #include "decode/custom_vulkan_struct_to_sqlite.h"
            #include "decode/api_event_types.h"

            #include "sqlite_utils.h"

            #include <cstdint>
            #include <sstream>
            #include <optional>
            #include <unordered_set>
            '''
        )
        write(includes, file=self.outFile)

        namespace = inspect.cleandoc(
            '''
            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            '''
        )
        write(namespace, file=self.outFile)

        # Each code generator is passed a blacklist like framework\generated\vulkan_generators\blacklists.json
        # of functions and structures not to generate code for. We need all functions and structs to be generated
        # thus we are clearing the list before populating our own.
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

    def endFile(self):
        """Method override."""
        body = '\n' + inspect.cleandoc(
            '''
            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
            '''
        )
        write(body, file=self.outFile)

        for function in self.allSpecialFunctions:
            assert function in self.seenFunctions, f"{function} has special logic but was never generated"

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    def need_feature_generation(self):
        """Indicates that the current feature has C++ code to generate."""
        if self.feature_cmd_params:
            return True
        return False

    def generate_feature(self):
        """Performs C++ code generation for the feature."""
        first = True

    def endFile(self):
        """Method override."""
        body = '\n' + inspect.cleandoc(
            '''
            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
            '''
        )
        write(body, file=self.outFile)

        for function in self.allSpecialFunctions:
            assert function in self.seenFunctions, f"{function} has special logic but was never generated"

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    def need_feature_generation(self):
        """Indicates that the current feature has C++ code to generate."""
        if self.feature_cmd_params:
            return True
        return False

    def generate_feature(self):
        """Performs C++ code generation for the feature."""
        first = True

        for cmd in self.get_filtered_cmd_names():
            if not cmd in self.customImplementationRequired:
                info = self.feature_cmd_params[cmd]
                return_type = info[0]
                values = info[2]

                cmddef = '' if first else '\n'
                cmddef += self.make_consumer_func_decl(
                    return_type, 'VulkanSqliteConsumer::Process_' + cmd, values
                ) + '\n'
                cmddef += inspect.cleandoc(
                    '''
                    {{
                        FieldInfo fieldInfo = {{this->block_index_, 0, 0, 0}};
                        const auto functionId = statements.InsertFunctionName("{0}");
                        statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);
                    '''.format(cmd)
                )
                cmddef += '\n'
                cmddef += self.make_consumer_func_body(
                    return_type, cmd, values
                )
                cmddef += '\n}'
                write(cmddef, file=self.outFile)
                first = False

    def is_command_buffer_cmd(self, command):
        if 'vkCmd' in command:
            return True
        return False

    def is_multi_cmd(self, command):
        if 'vkCmdDrawMulti' in command:
            return True
        return False

    def is_mesh_task_cmd(self, command):
        if command in self.addressBasedCmds:
            return False
        if 'vkCmdDrawMeshTask' in command:
            return True
        return False

    def is_cluster_cmd(self, command):
        if 'vkCmdDrawCluster' in command:
            return True
        return False

    def is_draw_cmd(self, command):
        if command in self.addressBasedCmds:
            return False
        if self.is_multi_cmd(command):
            return False
        if self.is_mesh_task_cmd(command):
            return False
        if self.is_cluster_cmd(command):
            return False
        if 'vkCmdDraw' in command:
            return True
        return False

    def is_dispatch_cmd(self, command):
        if command in self.addressBasedCmds:
            return False
        if 'vkCmdDispatchTileQCOM' == command:
            # This function is not a normal dispatch call
            return False
        if 'vkCmdDispatchDataGraphARM' == command:
            # This function is not a normal dispatch call
            return False
        if 'vkCmdDispatch' in command: 
            return True
        return False

    def is_traceray_cmd(self, command):
        if 'vkCmdTraceRays' in command:
            return True
        return False

    def make_command_pool(self, action):
        return f'''
            auto commandPoolIter = context.commandPoolHandleToId.find(ToInt64(args.commandPool));
            if (commandPoolIter == context.commandPoolHandleToId.end())
            {{
                GFXRECON_SQLITE_LOG_WARNING("Failed to {action}, failed to find command pool for handle %" PRIi64, args.commandPool);
                return;
            }}
        '''

    def make_command_buffer_recording(self, action):
        return f'''
            auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
            if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
            {{
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to {action}, failed to find command buffer recording for command buffer with handle %" PRIi64,
                    args.commandBuffer
                );
                return;
            }}
        '''

    def make_renderpass_recording_from_command_buffer_recording(self, warnOnMissingRenderpass):
        """
            Requires previous call to self.make_command_buffer_recording()
        """
        value = '''
            std::optional<int64_t> renderPassRecordingId = std::nullopt;
            std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
            std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;
        '''
        if warnOnMissingRenderpass:
            value += '''
            auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
            if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
                    args.commandBuffer
                );
            } else {
                commandBufferLevel = commandBufferLevelIter->second;
            }
            '''
        value += '''
            std::optional<int64_t> deviceId = std::nullopt;
            auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
            if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
            {
                deviceId = deviceIdIter->second;
            }
            if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
            {
                auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
                if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
                {
                    if (!commandBufferDynamicRenderPassStackIter->second.empty())
                    {
                        dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
                    }
                }
            }

            if (!dynamicRenderPassRecordingId.has_value())
            {
                auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
                if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
                {
                    if (!commandBufferRenderPassStackIter->second.empty())
                    {
                        renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                        auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                        if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                        {
                            renderSubpassRecordingId = renderSubpassRecordingIter->second;
                        }'''
        if warnOnMissingRenderpass:
            value += '''
                        else
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                                "setting foreign key to NULL",
                                renderPassRecordingId.value()
                            );
                        }
                    }
                    else
                    {
                        if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                                "setting foreign keys to NULL",
                                args.commandBuffer
                            );
                        }
                    }
                }
                else
                {
                    if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                            args.commandBuffer
                        );
                    }
                }
            }
        '''
        else:
            value += '''
                    }
                }
            }
            '''

        return value

    # Decoder wrapper classes whose FieldToSqlite/GetHandle/GetMetaStructPointer/etc. overloads take a
    # pointer-to-decoder (no reference overload exists), so a by-value args-struct field needs "&".
    # PointerDecoder<T> is deliberately excluded: it has a reference-taking overload and is passed
    # directly. Opaque single pointers (e.g. a lone "void*") decode to a plain uint64_t scalar rather
    # than any wrapper class, so they also fall through to "no &" (passed by value, like RecordField).
    POINTER_DECODER_WRAPPER_PREFIXES = (
        'StructPointerDecoder<',
        'HandlePointerDecoder<',
        'StringDecoder',
        'StringArrayDecoder',
        'WStringDecoder',
    )

    def make_field_ref(self, value):
        """Return the C++ expression referencing this value's args-struct field, for passing to
        FieldToSqlite/GetHandle/GetMetaStructPointer/etc. helpers that expect a pointer-to-decoder.
        Since the args:: struct refactor, decoder fields are stored BY VALUE in the args struct (not by
        pointer, as the old per-command positional parameters were), so calls whose decoded type is one
        of the pointer-only wrapper classes need the address-of operator; everything else (PointerDecoder<T>,
        which has a reference overload, and plain scalars like a lone uint64_t-encoded void*) is passed
        directly, matching what these helpers already accepted before the args-struct refactor.
        """
        decoded_param_type = self.make_decoded_param_type(value)
        if decoded_param_type.startswith(self.POINTER_DECODER_WRAPPER_PREFIXES):
            return f'&{value.prefixed_name}'
        return value.prefixed_name

    # yapf: disable
    def make_consumer_func_body(self, return_type, name, values):
        """Return VulkanSqliteConsumer class member function definition."""
        self.seenFunctions.add(name)

        body = ''

        # Event Argument values (do not return in these)
        if len(values) > 0:
            fieldIndex = 1
            for value in values:
                type_name = value.platform_full_type
                if type_name == None:
                    type_name = value.full_type
                body += '\n'
                if value.is_pointer and not value.is_array:
                    field_ref = self.make_field_ref(value)
                    body += textwrap.indent(inspect.cleandoc(
                        f'''
                            FieldToSqlite(statements, fieldInfo, {fieldIndex}, "{value.name}", {
                            field_ref}, "{type_name}");
                        '''
                    ), '    ')
                elif value.is_array:
                    field_ref = self.make_field_ref(value)
                    body += textwrap.indent(inspect.cleandoc(
                        f'''
                            FieldToSqlite(statements, fieldInfo, {fieldIndex}, "{value.name}", {
                            field_ref}, "{type_name}");
                        '''
                    ), '    ')
                else:
                    body += textwrap.indent(inspect.cleandoc(
                        f'''
                            RecordField(
                                statements, fieldInfo, {fieldIndex}, "{value.name}", "{type_name}", {value.prefixed_name});
                        '''
                    ), '    ')
                fieldIndex += 1

        # Event Return value
        body += '\n'
        return_value = '"void"'
        if not 'void' in return_type:
            return_value = 'args.result'

        body += '\n'
        body += textwrap.indent(inspect.cleandoc(
            f'''
                statements.InsertApiEventReturns(this->block_index_, "{return_type}", {return_value});
            '''
        ), '    ')

        # Common Command values (do not return in these)
        if self.is_command_buffer_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    UpdateCommandBufferCommands(call_info, args.commandBuffer);
                '''
            ), '    ')

        if name in self.addressBasedCmds:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    // TODO: No draw recording or state binding tracking for device-address-based commands.
                    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
                    // cannot be resolved to database buffer IDs with the current tracking system.
                '''
            ), '    ')

        # "Specific" function values (returning in these exits any further generated data, do with caution)
        if name in self.createSurface:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [surfaceValid, surface] = GetHandle(&args.pSurface);
                    if (!surfaceValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create surface, invalid pSurface handle");
                        }
                        return;
                    }

                    auto [createInfoValid, createInfo] = GetMetaStructPointer(&args.pCreateInfo);
                    if (!createInfoValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create surface, invalid pCreateInfo struct");
                        }
                        return;
                    }

                    LogUnsupportedPNext(createInfo->pNext);

                    auto createInfoType = createInfo->decoded_value->sType;

                    statements.InsertSurface(ToInt64(surface), createInfoType, this->block_index_);
                '''
            ), '    ')
        if name in self.destroySurface:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto surfaceIter = context.surfaceHandleToId.find(ToInt64(args.surface));
                    if (surfaceIter == context.surfaceHandleToId.end())
                    {
                        if (args.surface != format::kNullHandleId)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to destroy surface, no surface found with handle %" PRIi64, args.surface);
                        }
                        return;
                    }

                    statements.DestroyObject(statements.destroySurfaceUpdateStatement, this->block_index_, surfaceIter->second);

                    context.surfaceHandleToId.erase(surfaceIter);
                '''
            ), '    ')
        if name in self.bindPipeline:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('bind pipeline')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto pipelineIter = context.pipelineHandleToId.find(ToInt64(args.pipeline));
                    if (pipelineIter == context.pipelineHandleToId.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to bind pipeline, failed to find pipeline for handle %" PRIi64,
                            args.pipeline
                        );
                        return;
                    }

                    std::unordered_set<VkShaderStageFlagBits> stagesToClear;
                    switch(args.pipelineBindPoint)
                    {
                        case VK_PIPELINE_BIND_POINT_GRAPHICS:
                            {
                                stagesToClear.insert(VK_SHADER_STAGE_VERTEX_BIT);
                                stagesToClear.insert(VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
                                stagesToClear.insert(VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);
                                stagesToClear.insert(VK_SHADER_STAGE_GEOMETRY_BIT);
                                stagesToClear.insert(VK_SHADER_STAGE_FRAGMENT_BIT);
                                stagesToClear.insert(VK_SHADER_STAGE_TASK_BIT_EXT);
                                stagesToClear.insert(VK_SHADER_STAGE_MESH_BIT_EXT);
                                stagesToClear.insert(VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI);
                                break;
                            }
                        case VK_PIPELINE_BIND_POINT_COMPUTE:
                        case VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX:
                            {
                                stagesToClear.insert(VK_SHADER_STAGE_COMPUTE_BIT);
                                break;
                            }
                        case VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR:
                            {
                                stagesToClear.insert(VK_SHADER_STAGE_ANY_HIT_BIT_KHR);
                                stagesToClear.insert(VK_SHADER_STAGE_CALLABLE_BIT_KHR);
                                stagesToClear.insert(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR);
                                stagesToClear.insert(VK_SHADER_STAGE_INTERSECTION_BIT_KHR);
                                stagesToClear.insert(VK_SHADER_STAGE_MISS_BIT_KHR);
                                stagesToClear.insert(VK_SHADER_STAGE_RAYGEN_BIT_KHR);
                                break;
                            }
                        case VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI:
                            {
                                stagesToClear.insert(VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI);
                                break;
                            }
                        case VK_PIPELINE_BIND_POINT_MAX_ENUM:
                            // do nothing
                        default:
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to clear shader stages on pipeline binding, unsupported bind point %" PRIu64,
                                args.pipelineBindPoint
                            );
                    }

                    // binding pipelines will reset any previous shader object binding so clear that now
                    auto shaderBindingsIter = context.commandBufferRecordingShaderObjectBindings.find(commandBufferRecordingIter->second);
                    if (shaderBindingsIter != context.commandBufferRecordingShaderObjectBindings.end())
                    {
                        for (auto stage : stagesToClear)
                        {
                            shaderBindingsIter->second.erase(stage);
                        }
                        if (shaderBindingsIter->second.empty())
                        {
                            context.commandBufferRecordingShaderObjectBindings.erase(shaderBindingsIter);
                        }
                    }

                    statements.InsertStatePipelineBinding(this->block_index_, commandBufferRecordingIter->second, pipelineIter->second, args.pipelineBindPoint);
                '''
            ), '    ')
        if name in self.bindShaderObject:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [shadersValid, shaders, shadersCount] = GetHandleArray(&args.pShaders);
                    auto [stagesValid, stages, stagesCount] = GetPointerArray(&args.pStages);
                    if (!stagesValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to bind shader objects, invalid pStages");
                        return;
                    }
                '''
            ), '    ')
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('bind shader object')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    if (shadersValid && shadersCount != stagesCount) {
                        GFXRECON_SQLITE_LOG_WARNING("pShaders and pStages counts do not match, using min");
                    }
                    std::unordered_set<VkPipelineBindPoint> bindPointsToClear;
                    for (size_t i = 0; i < (shadersValid ? std::min(shadersCount, stagesCount) : stagesCount); ++i)
                    {
                        auto shader = shadersValid ? shaders[i] : format::kNullHandleId;
                        auto stage = stages[i];
                        switch(stage)
                        {
                            case VK_SHADER_STAGE_ALL:
                                {
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_GRAPHICS);
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_COMPUTE);
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX);
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
                                    break;
                                }
                            case VK_SHADER_STAGE_VERTEX_BIT:
                            case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
                            case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
                            case VK_SHADER_STAGE_GEOMETRY_BIT:
                            case VK_SHADER_STAGE_FRAGMENT_BIT:
                            case VK_SHADER_STAGE_TASK_BIT_EXT:
                            case VK_SHADER_STAGE_MESH_BIT_EXT:
                            case VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI:
                            case VK_SHADER_STAGE_ALL_GRAPHICS:
                                {
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_GRAPHICS);
                                    break;
                                }
                            case VK_SHADER_STAGE_COMPUTE_BIT:
                                {
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_COMPUTE);
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX);
                                    break;
                                }
                            case VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
                            case VK_SHADER_STAGE_CALLABLE_BIT_KHR:
                            case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
                            case VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
                            case VK_SHADER_STAGE_MISS_BIT_KHR:
                            case VK_SHADER_STAGE_RAYGEN_BIT_KHR:
                                {
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
                                    break;
                                }
                            case VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI:
                                {
                                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
                                    break;
                                }
                            default:
                                GFXRECON_SQLITE_LOG_WARNING(
                                    "Failed to clear bind points, unsupported shader stage %" PRIu64,
                                    stage
                                );
                        }
                        if (shader)
                        {
                            auto shaderIter = context.shaderObjectHandleToId.find(ToInt64(shader));
                            if (shaderIter == context.shaderObjectHandleToId.end())
                            {
                                GFXRECON_SQLITE_LOG_WARNING(
                                    "Failed to bind shader, failed to find shader with handle %" PRIi64,
                                    shader
                                );
                                continue;
                            }

                            statements.InsertStateShaderObjectBinding(this->block_index_, commandBufferRecordingIter->second, shaderIter->second, stage);
                        }
                        else
                        {
                            // clear any existing shader binding for the stage since the shader was a VK_NULL_HANDLE
                            auto shaderBindingsIter = context.commandBufferRecordingShaderObjectBindings.find(commandBufferRecordingIter->second);
                            if (shaderBindingsIter != context.commandBufferRecordingShaderObjectBindings.end())
                            {
                                shaderBindingsIter->second.erase(stage);
                                if (shaderBindingsIter->second.empty())
                                {
                                    context.commandBufferRecordingShaderObjectBindings.erase(shaderBindingsIter);
                                    context.commandBufferRecordingWithDirtyState.insert(commandBufferRecordingIter->second);
                                }
                            }
                        }
                    }

                    // binding shader objects will reset any previous pipeline binding so clear that now
                    auto pipelineBindingsIter = context.commandBufferRecordingPipelineBindings.find(commandBufferRecordingIter->second);
                    if (pipelineBindingsIter != context.commandBufferRecordingPipelineBindings.end())
                    {
                        for (auto bindPoint : bindPointsToClear)
                        {
                            pipelineBindingsIter->second.erase(bindPoint);
                        }
                        if (pipelineBindingsIter->second.empty())
                        {
                            context.commandBufferRecordingPipelineBindings.erase(pipelineBindingsIter);
                        }
                        context.commandBufferRecordingWithDirtyState.insert(commandBufferRecordingIter->second);
                    }
                '''
            ), '    ')
        if name in self.bindVertexBuffers:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [buffersValid, buffers, buffersCount] = GetHandleArray(&args.pBuffers);
                    if (!buffersValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pBuffers");
                        return;
                    }

                    auto [offsetsValid, offsets, offsetsCount] = GetPointerArray(&args.pOffsets);
                    if (!offsetsValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pOffsets");
                        return;
                    }
                '''
            ), '    ')
            if '2' in name: # vkCmdBindVertexBuffers2/EXT
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto [sizesValid, sizes, sizesCount] = GetPointerArray(&args.pSizes);
                        auto [stridesValid, strides, stridesCount] = GetPointerArray(&args.pStrides);
                    '''
                ), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('bind vertex buffers')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    if (buffersCount != offsetsCount) {
                        GFXRECON_SQLITE_LOG_WARNING("pBuffer and pOffset counts do not match, using min");
                    }
                    for (size_t i = 0; i < std::min(buffersCount, offsetsCount); ++i)
                    {
                '''
            ), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    std::optional<uint64_t> size = std::nullopt;
                    std::optional<uint64_t> stride = std::nullopt;
                '''
            ), '        ')
            if '2' in name: # vkCmdBindVertexBuffers2/EXT
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        if (sizesValid)
                        {
                            size = sizes[i];
                        }
                        if (stridesValid)
                        {
                            stride = strides[i];
                        }
                    '''
                ), '        ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                        bool nullDescriptorEnabled = false;
                        auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
                        if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
                        {
                            nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
                        }

                        auto buffer = buffers[i];
                        std::optional<int64_t> bufferId = std::nullopt;
                        if (buffer != format::kNullHandleId || !nullDescriptorEnabled)
                        {
                            auto bufferIter = context.bufferHandleToId.find(ToInt64(buffer));
                            if (bufferIter == context.bufferHandleToId.end())
                            {
                                GFXRECON_SQLITE_LOG_WARNING(
                                    "Failed to bind vertex buffer, failed to find buffer with handle %" PRIi64,
                                    buffer
                                );
                                continue;
                            }
                            else
                            {
                                bufferId = bufferIter->second;
                            }
                        }
                        auto offset = offsets[i];
                        auto binding = args.firstBinding + static_cast<uint32_t>(i);

                        statements.InsertStateVertexBufferBinding(this->block_index_, commandBufferRecordingIter->second, binding, bufferId, offset, size, stride);
                    }
                '''
            ), '    ')
        if name in self.bindIndexBuffer:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    bool nullDescriptorEnabled = false;
                    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
                    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
                    {
                        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
                    }

                    std::optional<int64_t> bufferId = std::nullopt;
                    if (args.buffer != format::kNullHandleId || !nullDescriptorEnabled)
                    {
                        auto bufferIter = context.bufferHandleToId.find(ToInt64(args.buffer));
                        if (bufferIter == context.bufferHandleToId.end())
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to bind index buffer, failed to find buffer with handle %" PRIi64,
                                args.commandBuffer
                            );
                            return;
                        }
                        else
                        {
                            bufferId = bufferIter->second;
                        }
                    }
                '''
            ), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('bind index buffer')), '    ')
            size_ref = 'size'
            if not '2' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                '''
                        std::optional<uint64_t> size = std::nullopt;
                '''
                ), '    ')
            else:
                size_ref = 'args.size'
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                f'''
                    statements.InsertStateIndexBufferBinding(this->block_index_, commandBufferRecordingIter->second, bufferId, args.offset, args.indexType, {size_ref});
                '''
            ), '    ')
        if name in self.trackedCommands:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert tracked command')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_renderpass_recording_from_command_buffer_recording(False)), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                   statements.InsertTrackedCmdCommand(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
                '''
            ), '    ')
        if name in self.trackedDeviceCommands:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto deviceId = context.GetDeviceId(args.device);
                    if (!deviceId.has_value())
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to insert device command, unknown device handle");
                    }
                    else
                    {
                        statements.InsertTrackedDeviceCommand(*deviceId, this->block_index_);
                    }
                '''
            ), '    ')
        if name in self.transferCommands:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert transfer command')), '    ')
        if self.is_draw_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert cmd draw recording')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_renderpass_recording_from_command_buffer_recording(True)), '    ')
            if 'Indexed' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
                    '''
                ), '    ')
            else:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
                    '''
                ), '    ')
            if 'Indirect' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        std::optional<int64_t> indirectBuffer = std::nullopt;
                        std::optional<uint64_t> indirectBufferOffset = std::nullopt;
                        std::optional<int64_t> indirectCountBuffer = std::nullopt;
                        std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
                        std::optional<uint32_t> indirectCountOffset = std::nullopt;
                        std::optional<uint32_t> indirectDrawCount = std::nullopt;
                        std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
                        std::optional<uint32_t> indirectStride = std::nullopt;
                        std::optional<uint32_t> indirectVertexStride = std::nullopt;
                    '''
                ), '    ')
                if 'ByteCount' not in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectBuffer = context.GetBufferId(args.buffer);
                            indirectBufferOffset = args.offset;
                        '''
                    ), '    ')
                if 'ByteCount' in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectCountBuffer = context.GetBufferId(args.counterBuffer);
                            indirectCountBufferOffset = args.counterBufferOffset;
                            indirectCountOffset = args.counterOffset;
                            indirectVertexStride = args.vertexStride;
                        '''
                    ), '    ')
                elif 'Count' in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectCountBuffer = context.GetBufferId(args.countBuffer);
                            indirectCountBufferOffset = args.countBufferOffset;
                            indirectMaxDrawCount = args.maxDrawCount;
                            indirectStride = args.stride;
                        '''
                    ), '    ')
                else:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectDrawCount = args.drawCount;
                        '''
                    ), '    ')
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
                    '''
                ), '    ')
            else:
                if 'Indexed' in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            statements.InsertCmdDrawRecordingInfo(cmdDrawRecordingId, std::nullopt, std::nullopt, args.vertexOffset, args.indexCount, args.firstIndex, args.instanceCount, args.firstInstance);
                        '''
                    ), '    ')
                else:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            statements.InsertCmdDrawRecordingInfo(cmdDrawRecordingId, args.vertexCount, args.firstVertex, std::nullopt, std::nullopt, std::nullopt, args.instanceCount, args.firstInstance);
                        '''
                    ), '    ')
        if self.is_mesh_task_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert cmd mesh task recording')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_renderpass_recording_from_command_buffer_recording(True)), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
                '''
            ), '    ')
            if 'Indirect' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        std::optional<int64_t> indirectBuffer = context.GetBufferId(args.buffer);
                        std::optional<int64_t> indirectCountBuffer = std::nullopt;
                        std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
                        std::optional<uint32_t> indirectDrawCount = std::nullopt;
                        std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
                    '''
                ), '    ')
                if 'Count' in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectCountBuffer = context.GetBufferId(args.countBuffer);
                            indirectCountBufferOffset = args.countBufferOffset;
                            indirectMaxDrawCount = args.maxDrawCount;
                        '''
                    ), '    ')
                else:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            indirectDrawCount = args.drawCount;
                        '''
                    ), '    ')
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdMeshTaskRecordingIndirectInfo(cmdMeshTaskRecordingId, indirectBuffer, args.offset, indirectCountBuffer, indirectCountBufferOffset, indirectDrawCount, indirectMaxDrawCount, args.stride);
                    '''
                ), '    ')
            else:
                if 'NV' in name:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            // TODO handle firstTask value which represents the x component of the first workgroup ID
                            // per: https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawMeshTasksNV.html
                            statements.InsertCmdMeshTaskRecordingInfo(cmdMeshTaskRecordingId, args.taskCount, 1, 1);
                        '''
                    ), '    ')
                else:
                    body += '\n'
                    body += textwrap.indent(inspect.cleandoc(
                        '''
                            statements.InsertCmdMeshTaskRecordingInfo(cmdMeshTaskRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
                        '''
                    ), '    ')
        if self.is_cluster_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert cmd cluster recording')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_renderpass_recording_from_command_buffer_recording(True)), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto cmdClusterRecordingId = statements.InsertCmdClusterRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
                '''
            ), '    ')
            if 'Indirect' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdClusterRecordingIndirectInfo(cmdClusterRecordingId, context.GetBufferId(args.buffer), args.offset);
                    '''
                ), '    ')
            else:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdClusterRecordingInfo(cmdClusterRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
                    '''
                ), '    ')
        if self.is_dispatch_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert cmd dispatch recording')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto cmdDispatchRecordingId = statements.InsertCmdDispatchRecording(this->block_index_, commandBufferRecordingIter->second);
                '''
            ), '    ')
            if 'Base' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdDispatchRecordingBaseInfo(cmdDispatchRecordingId, args.baseGroupX, args.baseGroupY, args.baseGroupZ);
                    '''
                ), '    ')
            if 'Indirect' in name:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdDispatchRecordingIndirectInfo(cmdDispatchRecordingId, context.GetBufferId(args.buffer), args.offset);
                    '''
                ), '    ')
            else:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        statements.InsertCmdDispatchRecordingInfo(cmdDispatchRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
                    '''
                ), '    ')
        if self.is_traceray_cmd(name):
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('insert cmd raytracing recording')), '    ')
            body += '\n'
            ## TODO save off cmdRaytracingRecordingId returned by insertCmdRaytracingRecording for use in populating info structs
            body += textwrap.indent(inspect.cleandoc(
                '''
                    statements.InsertCmdRaytracingRecording(this->block_index_, commandBufferRecordingIter->second);
                '''
            ), '    ')
            ## TODO add handling of NV/KHR extension differences and Indirect/Indirect2 versions
        if name in self.commandPool:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [commandPoolValid, commandPool] = GetHandle(&args.pCommandPool);
                    if (!commandPoolValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create command pool, invalid pCommandPool");
                        }
                        return;
                    }

                    auto [createInfoValid, createInfo] = GetMetaStructPointer(&args.pCreateInfo);
                    if (!createInfoValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create command pool, invalid pCreateInfo");
                        }
                        return;
                    }

                    LogUnsupportedPNext(createInfo->pNext);

                    auto flags = createInfo->decoded_value->flags;
                    auto queueFamilyIndex = createInfo->decoded_value->queueFamilyIndex;
                    statements.InsertCommandPool(this->block_index_, commandPool, args.device, flags, queueFamilyIndex);
                '''
            ), '    ')
        if name in self.destroyCommandPool or name in self.resetCommandPool:
            if name in self.destroyCommandPool:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(self.make_command_pool('destroy command pool')), '    ')
            if name in self.resetCommandPool:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(self.make_command_pool('reset command buffers associated with command pool')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto commandPoolCommandBufferHandlesIter = context.commandPoolHandleToCommandBufferHandles.find(ToInt64(args.commandPool));
                    if (commandPoolCommandBufferHandlesIter != context.commandPoolHandleToCommandBufferHandles.end())
                    {
                        for (auto commandBufferHandle : commandPoolCommandBufferHandlesIter->second)
                        {
                            auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
                            if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end())
                            {
                                statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                                context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
                            }
                '''
                ), '    ')
            if name in self.destroyCommandPool:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                            auto commandBufferId = context.GetCommandBufferId(commandBufferHandle);
                            if (commandBufferId.has_value())
                            {
                                statements.DestroyObject(statements.freeCommandBufferUpdateStatement, this->block_index_, commandBufferId.value());
                            }
                            context.commandBufferHandleToId.erase(commandBufferHandle);
                            context.commandBufferHandleToLevel.erase(commandBufferHandle);
                            context.commandBufferHandleToDeviceId.erase(commandBufferHandle);
                        }
                    }
                    statements.DestroyObject(statements.destroyCommandPoolUpdateStatement, this->block_index_, commandPoolIter->second);
                    context.commandPoolHandleToId.erase(commandPoolIter);
                    '''
                ), '    ')
            else:
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        }
                    }
                    '''
                ), '    ')
        if name in self.allocateCommandBuffers:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
                    if (!commandBuffersValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to allocate command buffers, invalid pCommandBuffers");
                        }
                        return;
                    }

                    auto [allocateInfoValid, allocateInfo] = GetMetaStructPointer(&args.pAllocateInfo);
                    if (!allocateInfoValid)
                    {
                        if (args.result == VK_SUCCESS)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to allocate command buffers, invalid pAllocateInfo");
                        }
                        return;
                    }

                    LogUnsupportedPNext(allocateInfo->pNext);

                    auto commandPool = allocateInfo->commandPool;
                    auto level = allocateInfo->decoded_value->level;

                    for (size_t i = 0; i < commandBuffersCount; ++i)
                    {
                        statements.InsertCommandBuffer(this->block_index_, commandBuffers[i], args.device, commandPool, level);
                    }
                '''
            ), '    ')
        if name in self.beginCommandBuffer:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pBeginInfo);
                    if (!beginInfoValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to create command buffer recording, invalid pBeginInfo");
                        return;
                    }

                    LogUnsupportedPNext(beginInfo->pNext);

                    std::optional<int64_t> inheritanceId = std::nullopt;
                    auto [inheritanceInfoValid, inheritanceInfo] = GetMetaStructPointer(beginInfo->pInheritanceInfo);
                    if (inheritanceInfoValid)
                    {
                        LogUnsupportedPNext(inheritanceInfo->pNext);

                        auto renderPassId = context.GetRenderPassId(inheritanceInfo->renderPass, true);
                        auto framebufferId = context.GetFramebufferId(inheritanceInfo->framebuffer, true);
                        auto queryFlags = inheritanceInfo->decoded_value->queryFlags;
                        auto pipelineStats = inheritanceInfo->decoded_value->pipelineStatistics;
                        auto occlusionQueryEnable = inheritanceInfo->decoded_value->occlusionQueryEnable;
                        auto subpass = inheritanceInfo->decoded_value->subpass;
                        inheritanceId = statements.InsertCommandBufferInheritanceInfo(renderPassId, subpass, framebufferId, occlusionQueryEnable, queryFlags, pipelineStats);
                    }

                    auto commandBufferHandle = ToInt64(args.commandBuffer);
                    auto commandBufferIter = context.commandBufferHandleToId.find(commandBufferHandle);
                    if (commandBufferIter == context.commandBufferHandleToId.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to find command buffer for handle %" PRIi64 ", setting foreign key to NULL", args.commandBuffer
                        );
                        return;
                    }

                    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
                    if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end())
                    {
                        statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                        context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
                    }
                    auto commandBufferRecordingId = statements.InsertCommandBufferRecording(this->block_index_, commandBufferIter->second, beginInfo->decoded_value->flags, inheritanceId);

                    context.commandBufferHandleToRecordingId[commandBufferHandle] = commandBufferRecordingId;
                    context.commandBufferHandleToRenderPassRecordingIdStack[commandBufferHandle] = {};
                    context.commandBufferHandleToDynamicRenderPassRecordingIdStack[commandBufferHandle] = {};


                    UpdateCommandBufferCommands(call_info, args.commandBuffer);
                '''
            ), '    ')
        if name in self.endCommandBuffer:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(self.make_command_buffer_recording('end command buffer recording')), '    ')
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    statements.EndCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);

                    UpdateCommandBufferCommands(call_info, args.commandBuffer);
                    auto pipelineBindingIter = context.commandBufferRecordingPipelineBindings.find(commandBufferRecordingIter->second);
                    if (pipelineBindingIter != context.commandBufferRecordingPipelineBindings.end()) {
                        pipelineBindingIter->second.clear();
                        context.commandBufferRecordingPipelineBindings.erase(pipelineBindingIter);
                    }
                    auto vertexBindingIter = context.commandBufferRecordingVertexBindings.find(commandBufferRecordingIter->second);
                    if (vertexBindingIter != context.commandBufferRecordingVertexBindings.end()) {
                        vertexBindingIter->second.clear();
                        context.commandBufferRecordingVertexBindings.erase(vertexBindingIter);
                    }
                    context.commandBufferRecordingIndexBindings.erase(commandBufferRecordingIter->second);
                '''
            ), '    ')
        if name in self.freeCommandBuffers:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
                if (!commandBuffersValid)
                {
                    GFXRECON_SQLITE_LOG_WARNING("Failed to free command buffers, invalid pCommandBuffers");
                    return;
                }

                auto commandPoolCommandBuffersIter = context.commandPoolHandleToCommandBufferHandles.find(ToInt64(args.commandPool));

                for (size_t i = 0; i < commandBuffersCount; ++i)
                {
                    auto commandBuffer = commandBuffers[i];
                    auto commandBufferHandle = ToInt64(commandBuffer);
                    // ensure we "reset" the command buffer if it was not reset automatically
                    // don't report an error if the recording is not found as it may have been previously reset
                    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
                    if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end()) {
                        statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                        context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
                    }

                    auto commandBufferIter = context.commandBufferHandleToId.find(commandBufferHandle);
                    if (commandBufferIter == context.commandBufferHandleToId.end()) {
                        if (commandBuffer != format::kNullHandleId)
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to free command buffer, no active command buffer found for handle %" PRIi64,
                                commandBuffer
                            );
                        }
                        continue;
                    }

                    statements.DestroyObject(statements.freeCommandBufferUpdateStatement, this->block_index_, commandBufferIter->second);

                    // cleanup context tracking
                    if (commandPoolCommandBuffersIter != context.commandPoolHandleToCommandBufferHandles.end())
                    {
                        auto& commandPoolCommandBuffers = commandPoolCommandBuffersIter->second;
                        std::erase(commandPoolCommandBuffers, commandBufferHandle);
                    }
                    context.commandBufferHandleToId.erase(commandBufferIter);
                    context.commandBufferHandleToLevel.erase(commandBufferHandle);
                    context.commandBufferHandleToDeviceId.erase(commandBufferHandle);
                }
                '''
            ), '    ')
        if name in self.resetCommandBuffer:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    // don't report an error if the recording is not found as it may have been previously reset
                    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
                    if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end()) {
                        statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                        context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
                    }
                '''
            ), '    ')
        if name in self.beginRenderPass or name in self.beginRenderPass2:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pRenderPassBegin);
                    if (!beginInfoValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass recording, invalid pBeginInfo");
                        return;
                    }

                    const Decoded_VkRenderPassAttachmentBeginInfo* attachmentBeginInfo = nullptr;

                    auto pnext = beginInfo->pNext;
                    while (pnext != nullptr)
                    {
                        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
                        if (*header->sType == gfxrecon::util::GetSType<VkRenderPassAttachmentBeginInfo>())
                        {
                            attachmentBeginInfo = reinterpret_cast<const Decoded_VkRenderPassAttachmentBeginInfo*>(header);
                        }
                        else
                        {
                            LogUnsupportedPNext(*header->sType);
                        }

                        pnext = header->pNext;
                    }

                    std::optional<int64_t> renderPassId = context.GetRenderPassId(beginInfo->renderPass, true);
                    std::optional<int64_t> framebufferId = context.GetFramebufferId(beginInfo->framebuffer);
                    auto renderOffset = beginInfo->renderArea->offset->decoded_value;
                    auto renderExtent = beginInfo->renderArea->extent->decoded_value;
                    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

                    uint64_t passIndex = 0;
                    if (commandBufferRecordingId.has_value())
                    {
                        auto passIndexIter = context.commandBufferRecordingIdToRenderPassIndex.find(commandBufferRecordingId.value());
                        if (passIndexIter == context.commandBufferRecordingIdToRenderPassIndex.end())
                        {
                            context.commandBufferRecordingIdToRenderPassIndex[commandBufferRecordingId.value()] = 0;
                        }
                        else
                        {
                            passIndexIter->second++;
                            passIndex = passIndexIter->second;
                        }
                    }

                    auto renderPassRecordingId = statements.InsertRenderPassRecording(this->block_index_, renderPassId, passIndex,
                                                                         commandBufferRecordingId, framebufferId,
                                                                         renderOffset->x, renderOffset->y, renderExtent->width,
                                                                         renderExtent->height );

                    context.commandBufferHandleToRenderPassRecordingIdStack[args.commandBuffer].push(renderPassRecordingId);

                    auto [clearValuesValid, clearValues, clearValuesCount] = GetMetaStructArray(beginInfo->pClearValues);
                    if (clearValuesValid)
                    {
                        for (size_t i = 0; i < clearValuesCount; ++i) {
                            const auto& clearValue = clearValues[i];
                            const auto& clearDS = clearValue.decoded_value->depthStencil;

                            auto clearColorId = statements.InsertUnionColor(clearValue.decoded_value->color);

                            statements.InsertRenderPassRecordingClearValues(renderPassRecordingId, i, clearColorId, clearDS.depth, clearDS.stencil);

                        }
                    }

                    if (attachmentBeginInfo != nullptr)
                    {
                        auto [attachmentsValid, attachments, attachmentsCount] = GetHandleArray(&attachmentBeginInfo->pAttachments);
                        if (attachmentsValid)
                        {
                            for (size_t i = 0; i < attachmentsCount; ++i) {
                                auto imageViewId = context.GetImageViewId(attachments[i]);
                                if (imageViewId.has_value())
                                {
                                    statements.InsertRenderPassRecordingAttachment(renderPassRecordingId, i, imageViewId.value());
                                }
                            }
                        }
                    }
                '''
            ), '    ')
            contents_ref = 'args.contents'
            if name in self.beginRenderPass2:
                contents_ref = 'contents'
                body += '\n'
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
                        if (!subpassBeginInfoValid)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create render subpass recording, invalid pSubpassBeginInfo");
                            return;
                        }

                        LogUnsupportedPNext(subpassBeginInfo->pNext);

                        const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;
                    '''
                ), '    ')
            body += '\n'
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                f'''
                    // insert implicit first subpass
                    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, {contents_ref});
                '''
            ), '    ')
        if name in self.nextRenderSubpass or name in self.nextRenderSubpass2:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto renderPassRecordingStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
                    if (renderPassRecordingStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end previous subpass and create next subpass, "
                            "failed to find render pass recording stack for command buffer with handle %" PRIi64,
                            args.commandBuffer
                        );
                        return;
                    }
                    if (renderPassRecordingStackIter->second.empty())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end previous subpass and create next subpass, "
                            " render subpass recording stack for command buffer with handle %" PRIi64 " is empty, "
                            "expecting a render pass recording for next render pass event",
                            args.commandBuffer
                        );
                        return;
                    }

                    auto renderPassRecordingId = renderPassRecordingStackIter->second.top();
                    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
                    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end previous subpass, failed to find subpass pass recording for render pass recording %" PRIu64,
                            renderPassRecordingStackIter->second.top()
                        );
                        // this is an error for the previous subpass, but we want to continue so we can add the next subpass
                    }
                    else
                    {
                        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);
                    }
                '''
            ), '    ')

            contents_ref = 'args.contents'
            if name in self.nextRenderSubpass2:
                contents_ref = 'contents'
                body += '\n'
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
                        if (!subpassBeginInfoValid)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create next subpass, invalid pSubpassBeginInfo");
                            return;
                        }

                        LogUnsupportedPNext(subpassBeginInfo->pNext);

                        auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
                        if (!subpassEndInfoValid)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to create create next subpass, invalid pSubpassEndInfo");
                            return;
                        }

                        LogUnsupportedPNext(subpassEndInfo->pNext);

                        const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;
                    '''
                ), '    ')

            body += '\n'
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                f'''
                    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, {contents_ref});
                '''
            ), '    ')
        if name in self.endRenderPass or name in self.endRenderPass2:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto renderPassRecordingIdStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
                    if (renderPassRecordingIdStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end render pass recording, failed to find render pass recording stack for command buffer %" PRIu64,
                            args.commandBuffer
                        );
                        return;
                    }
                    if (renderPassRecordingIdStackIter->second.empty())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end render pass recording, render pass recording stack for command buffer %" PRIu64 " is empty, "
                            "expected prior render pass begin",
                            args.commandBuffer
                        );
                        return;
                    }

                    auto renderPassRecordingId = renderPassRecordingIdStackIter->second.top();
                    statements.EndRenderPassRecording(this->block_index_, renderPassRecordingId);

                    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
                    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end render subpass recording, render pass recording stack for render pass %" PRIu64 " is empty, "
                            "expected implicit first subpass",
                            renderPassRecordingId
                        );
                        // This is an error for the subpass but not for render pass, we need to continue to finish ending the render pass recording
                    }
                    else
                    {
                        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);

                        context.renderPassRecordingIdToRenderSubpassRecordingId.erase(subpassRecordingIter);
                    }

                    auto subpassIndexRemoved = context.renderPassRecordingIdToSubpassIndex.erase(renderPassRecordingId);
                    if (!subpassIndexRemoved)
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to cleanup render subpass index for render pass recording %" PRIu64 ", expected implicit first subpass",
                            renderPassRecordingId
                        );
                    }

                    renderPassRecordingIdStackIter->second.pop();
                    if (!renderPassRecordingIdStackIter->second.empty())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to cleanup render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end render pass api event",
                            args.commandBuffer
                        );
                    }
                    else
                    {
                        context.commandBufferHandleToRenderPassRecordingIdStack.erase(renderPassRecordingIdStackIter);
                    }
                '''
            ), '    ')

            if name in self.endRenderPass2:
                body += '\n'
                body += '\n'
                body += textwrap.indent(inspect.cleandoc(
                    '''
                        auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
                        if (!subpassEndInfoValid)
                        {
                            GFXRECON_SQLITE_LOG_WARNING("Failed to process end subpass, invalid pSubpassEndInfo");
                            return;
                        }

                        LogUnsupportedPNext(subpassEndInfo->pNext);
                    '''
                ), '    ')
        if name in self.beginDynamicRenderPass:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [renderingInfoValid, renderingInfo] = GetMetaStructPointer(&args.pRenderingInfo);
                    if (!renderingInfoValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to create dynamic render pass recording, invalid pRenderingInfo");
                        return;
                    }

                    LogUnsupportedPNext(renderingInfo->pNext);

                    auto flags = renderingInfo->decoded_value->flags;
                    auto renderOffset = renderingInfo->renderArea->offset->decoded_value;
                    auto renderExtent = renderingInfo->renderArea->extent->decoded_value;
                    auto layerCount = renderingInfo->decoded_value->layerCount;
                    auto viewMask = renderingInfo->decoded_value->viewMask;


                    // create rendering attachments
                    std::optional<int64_t> depthAttachmentId = std::nullopt;
                    auto [depthAttachmentValid, depthAttachment] = GetMetaStructPointer(renderingInfo->pDepthAttachment);
                    if (depthAttachmentValid)
                    {
                        auto imageView = context.GetImageViewId(depthAttachment->imageView, true);
                        auto imageLayout = depthAttachment->decoded_value->imageLayout;
                        auto resolveMode = depthAttachment->decoded_value->resolveMode;
                        auto resolveImageViewId = context.GetImageViewId(depthAttachment->resolveImageView, true);
                        auto resolveImageLayout = depthAttachment->decoded_value->resolveImageLayout;
                        auto loadOp = depthAttachment->decoded_value->loadOp;
                        auto storeOp = depthAttachment->decoded_value->storeOp;
                        auto clearValue = depthAttachment->clearValue;
                        auto vkClearColor = clearValue->color->decoded_value;
                        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
                        auto clearDepth = clearDepthStencil.depth;
                        auto clearStencil = clearDepthStencil.stencil;

                        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

                        depthAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                                      resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                                      clearStencil);
                    }

                    std::optional<int64_t> stencilAttachmentId = std::nullopt;
                    auto [stencilAttachmentValid, stencilAttachment] = GetMetaStructPointer(renderingInfo->pStencilAttachment);
                    if (stencilAttachmentValid)
                    {
                        auto imageView = context.GetImageViewId(stencilAttachment->imageView, true);
                        auto imageLayout = stencilAttachment->decoded_value->imageLayout;
                        auto resolveMode = stencilAttachment->decoded_value->resolveMode;
                        auto resolveImageViewId = context.GetImageViewId(stencilAttachment->resolveImageView, true);
                        auto resolveImageLayout = stencilAttachment->decoded_value->resolveImageLayout;
                        auto loadOp = stencilAttachment->decoded_value->loadOp;
                        auto storeOp = stencilAttachment->decoded_value->storeOp;
                        auto clearValue = stencilAttachment->clearValue;
                        auto vkClearColor = clearValue->color->decoded_value;
                        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
                        auto clearDepth = clearDepthStencil.depth;
                        auto clearStencil = clearDepthStencil.stencil;

                        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

                        stencilAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                                        resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                                        clearStencil);
                    }

                    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

                    uint64_t passIndex = 0;
                    if (commandBufferRecordingId.has_value())
                    {
                        auto passIndexIter = context.commandBufferRecordingIdToDynamicRenderPassIndex.find(commandBufferRecordingId.value());
                        if (passIndexIter == context.commandBufferRecordingIdToDynamicRenderPassIndex.end())
                        {
                            context.commandBufferRecordingIdToDynamicRenderPassIndex[commandBufferRecordingId.value()] = 0;
                        }
                        else
                        {
                            passIndexIter->second++;
                            passIndex = passIndexIter->second;
                        }
                    }

                    auto dynamicRenderPassRecordingId = statements.InsertDynamicRenderPassRecording(this->block_index_, passIndex, commandBufferRecordingId, flags,
                                                                                       renderOffset->x, renderOffset->y,
                                                                                       renderExtent->width, renderExtent->height,
                                                                                       layerCount, viewMask,
                                                                                       depthAttachmentId, stencilAttachmentId);

                    context.commandBufferHandleToDynamicRenderPassRecordingIdStack[ToInt64(args.commandBuffer)].push(dynamicRenderPassRecordingId);

                    // create color rendering attachments - needs dynamicRenderPassRecordingId so must be done after
                    auto [colorAttachmentsValid, colorAttachments, colorAttachmentsCount] = GetMetaStructArray(renderingInfo->pColorAttachments);
                    if (colorAttachmentsValid)
                    {
                        for (size_t i = 0; i < colorAttachmentsCount; ++i)
                        {
                            auto& colorAttachment = colorAttachments[i];
                            auto imageView = context.GetImageViewId(colorAttachment.imageView, true);
                            auto imageLayout = colorAttachment.decoded_value->imageLayout;
                            auto resolveMode = colorAttachment.decoded_value->resolveMode;
                            auto resolveImageViewId = context.GetImageViewId(colorAttachment.resolveImageView, true);
                            auto resolveImageLayout = colorAttachment.decoded_value->resolveImageLayout;
                            auto loadOp = colorAttachment.decoded_value->loadOp;
                            auto storeOp = colorAttachment.decoded_value->storeOp;
                            auto clearValue = colorAttachment.clearValue;
                            auto vkClearColor = clearValue->color->decoded_value;
                            auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
                            auto clearDepth = clearDepthStencil.depth;
                            auto clearStencil = clearDepthStencil.stencil;

                            auto clearColorId = statements.InsertUnionColor(*vkClearColor);

                            auto colorAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                                               resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                                               clearStencil);

                            statements.InsertDynamicColorAttachment(dynamicRenderPassRecordingId, i, colorAttachmentId);
                        }
                    }

                '''
            ), '    ')
        if name in self.endDynamicRenderPass:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto dynamicRenderPassRecordingIdStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
                    if (dynamicRenderPassRecordingIdStackIter == context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end render pass recording, failed to find dynamic render pass recording stack for command buffer %" PRIu64,
                            args.commandBuffer
                        );
                        return;
                    }
                    if (dynamicRenderPassRecordingIdStackIter->second.empty())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to end dynamic render pass recording, dynamic render pass recording stack for command buffer %" PRIu64 " is empty, "
                            "expected prior dynamic render pass begin",
                            args.commandBuffer
                        );
                        return;
                    }

                    auto dynamicRenderPassRecordingId = dynamicRenderPassRecordingIdStackIter->second.top();
                    statements.EndDynamicRenderPassRecording(this->block_index_, dynamicRenderPassRecordingId);

                    dynamicRenderPassRecordingIdStackIter->second.pop();
                    if (!dynamicRenderPassRecordingIdStackIter->second.empty())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to cleanup dynamic render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end dynamic render pass api event",
                            args.commandBuffer
                        );
                    }
                    else
                    {
                        context.commandBufferHandleToDynamicRenderPassRecordingIdStack.erase(dynamicRenderPassRecordingIdStackIter);
                    }
                '''
            ), '    ')
        if name in self.secondaryExecution:
            body += '\n'
            body += textwrap.indent(inspect.cleandoc(
                '''
                    auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
                    if (!commandBuffersValid)
                    {
                        GFXRECON_SQLITE_LOG_WARNING("Failed to insert secondary command buffer execution, invalid pCommandBuffers");
                        return;
                    }

                    auto parentCommandBufferHandle = ToInt64(args.commandBuffer);
                    auto parentCommandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(parentCommandBufferHandle);
                    if (parentCommandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
                    {
                        GFXRECON_SQLITE_LOG_WARNING(
                            "Failed to insert secondary command buffer, failed to find command buffer recording for parent command buffer with handle %" PRIi64,
                            args.commandBuffer
                        );
                        return;
                    }

                    std::optional<uint64_t> renderPassRecordingId = std::nullopt;
                    std::optional<uint64_t> renderSubpassRecordingId = std::nullopt;

                    auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(parentCommandBufferHandle);
                    if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end() &&
                        !commandBufferRenderPassStackIter->second.empty())
                    {
                        renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                        auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                        if (renderSubpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                                "setting foreign key to NULL",
                                renderPassRecordingId.value()
                            );
                        }
                        else
                        {
                            renderSubpassRecordingId = renderSubpassRecordingIter->second;
                        }
                    }

                    std::optional<uint64_t> dynamicRenderPassRecordingId = std::nullopt;

                    auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(parentCommandBufferHandle);
                    if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end() &&
                        !commandBufferDynamicRenderPassStackIter->second.empty())
                    {
                        dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
                    }

                    for (size_t i = 0; i < commandBuffersCount; ++i)
                    {
                        auto secondaryCommandBuffer = commandBuffers[i];
                        std::string secondaryCommandBufferRecordingIdStr = "NULL";
                        auto secondaryCommandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(secondaryCommandBuffer));
                        if (secondaryCommandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to insert secondary command buffer execution, failed to find secondary command buffer recording for command buffer with handle %" PRIi64,
                                secondaryCommandBuffer
                            );
                            continue;
                        }

                        statements.InsertSecondaryCommandBufferExecutionRecording(
                            this->block_index_,
                            parentCommandBufferRecordingIter->second,
                            secondaryCommandBufferRecordingIter->second,
                            renderPassRecordingId,
                            renderSubpassRecordingId,
                            dynamicRenderPassRecordingId,
                            i
                        );
                    }
                '''
            ), '    ')

        return body
    # yapf: enable

    def genType(self, typeinfo, name, alias):
        super().genType(typeinfo, name, alias)
        if self.is_flags(name):
            if alias is None:
                self.flagsType[name] = self.flags_types[name]
                bittype = typeinfo.elem.get('requires')
                if bittype is None:
                    bittype = typeinfo.elem.get('bitvalues')
                if bittype is not None:
                    self.flagEnumBitsType[bittype] = name
            else:
                self.flagsTypeAlias[name] = alias
