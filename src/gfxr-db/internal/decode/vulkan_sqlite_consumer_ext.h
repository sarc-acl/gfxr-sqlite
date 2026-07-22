/********************************************************************************
    Copyright 2023-2026 The Sokatoa Project Authors

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 ********************************************************************************/

#ifndef VULKAN_SQLITE_CONSUMER_EXT_H
#define VULKAN_SQLITE_CONSUMER_EXT_H

#include "util/defines.h"
#include "generated/generated_vulkan_sqlite_consumer.h"

#include "sqlite3.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

class VulkanSqliteConsumerExt : public VulkanSqliteConsumer
{
  public:
    VulkanSqliteConsumerExt(sqlite3* db);

    // special handling override functions
    void Process_vkSetDebugUtilsObjectNameEXT(
        const ApiCallInfo& call_info, args::SetDebugUtilsObjectNameEXT& args
    ) override;

    void Process_vkSetDebugUtilsObjectTagEXT(
        const ApiCallInfo& call_info, args::SetDebugUtilsObjectTagEXT& args
    ) override;

    void Process_vkQueueBeginDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::QueueBeginDebugUtilsLabelEXT& args
    ) override;

    void Process_vkQueueEndDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::QueueEndDebugUtilsLabelEXT& args
    ) override;

    void Process_vkQueueInsertDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::QueueInsertDebugUtilsLabelEXT& args
    ) override;

    void Process_vkCmdBeginDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::CmdBeginDebugUtilsLabelEXT& args
    ) override;

    void Process_vkCmdEndDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::CmdEndDebugUtilsLabelEXT& args
    ) override;

    void Process_vkCmdInsertDebugUtilsLabelEXT(
        const ApiCallInfo& call_info, args::CmdInsertDebugUtilsLabelEXT& args
    ) override;

    void Process_vkDebugMarkerSetObjectTagEXT(
        const ApiCallInfo& call_info, args::DebugMarkerSetObjectTagEXT& args
    ) override;

    void Process_vkDebugMarkerSetObjectNameEXT(
        const ApiCallInfo& call_info, args::DebugMarkerSetObjectNameEXT& args
    ) override;

    void Process_vkCmdDebugMarkerBeginEXT(const ApiCallInfo& call_info, args::CmdDebugMarkerBeginEXT& args) override;

    void Process_vkCmdDebugMarkerEndEXT(const ApiCallInfo& call_info, args::CmdDebugMarkerEndEXT& args) override;

    void Process_vkCmdDebugMarkerInsertEXT(const ApiCallInfo& call_info, args::CmdDebugMarkerInsertEXT& args) override;

    void Process_vkCreateDebugReportCallbackEXT(
        const ApiCallInfo& call_info, args::CreateDebugReportCallbackEXT& args
    ) override;

    void Process_vkDestroyDebugReportCallbackEXT(
        const ApiCallInfo& call_info, args::DestroyDebugReportCallbackEXT& args
    ) override;

    void Process_vkCreateDebugUtilsMessengerEXT(
        const ApiCallInfo& call_info, args::CreateDebugUtilsMessengerEXT& args
    ) override;

    void Process_vkDestroyDebugUtilsMessengerEXT(
        const ApiCallInfo& call_info, args::DestroyDebugUtilsMessengerEXT& args
    ) override;

    void Process_vkCreateInstance(const ApiCallInfo& call_info, args::CreateInstance& args) override;

    void Process_vkDestroyInstance(const ApiCallInfo& call_info, args::DestroyInstance& args) override;

    void Process_vkEnumeratePhysicalDevices(
        const ApiCallInfo& call_info, args::EnumeratePhysicalDevices& args
    ) override;

    void Process_vkCreateDevice(const ApiCallInfo& call_info, args::CreateDevice& args) override;

    void Process_vkDestroyDevice(const ApiCallInfo& call_info, args::DestroyDevice& args) override;

    void Process_vkGetDeviceQueue(const ApiCallInfo& call_info, args::GetDeviceQueue& args) override;

    void ProcessQueue(
        const ApiCallInfo& call_info,
        format::HandleId device,
        uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        VkDeviceQueueCreateFlags flags,
        HandlePointerDecoder<VkQueue>* pQueue
    );

    void Process_vkGetDeviceQueue2(const ApiCallInfo& call_info, args::GetDeviceQueue2& args) override;

    void Process_vkQueueSubmit(const ApiCallInfo& call_info, args::QueueSubmit& args) override;

    void ProcessQueueSubmit2Info(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
        format::HandleId fence
    );

    void Process_vkQueueSubmit2(const ApiCallInfo& call_info, args::QueueSubmit2& args) override;

    void Process_vkQueueSubmit2KHR(const ApiCallInfo& call_info, args::QueueSubmit2KHR& args) override;

    void Process_vkQueuePresentKHR(const ApiCallInfo& call_info, args::QueuePresentKHR& args) override;

    void Process_vkCreateFence(const ApiCallInfo& call_info, args::CreateFence& args) override;

    void Process_vkDestroyFence(const ApiCallInfo& call_info, args::DestroyFence& args) override;

    void Process_vkResetFences(const ApiCallInfo& call_info, args::ResetFences& args) override;

    void Process_vkWaitForFences(const ApiCallInfo& call_info, args::WaitForFences& args) override;

    void Process_vkCreateSemaphore(const ApiCallInfo& call_info, args::CreateSemaphore& args) override;

    void Process_vkDestroySemaphore(const ApiCallInfo& call_info, args::DestroySemaphore& args) override;

    void Process_VkSemaphoreWaitInfo(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
        uint64_t timeout
    );

    void Process_VkSemaphoreSignalInfo(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
    );

    void Process_vkWaitSemaphores(const ApiCallInfo& call_info, args::WaitSemaphores& args) override;

    void Process_vkSignalSemaphore(const ApiCallInfo& call_info, args::SignalSemaphore& args) override;

    void Process_vkWaitSemaphoresKHR(const ApiCallInfo& call_info, args::WaitSemaphoresKHR& args) override;

    void Process_vkSignalSemaphoreKHR(const ApiCallInfo& call_info, args::SignalSemaphoreKHR& args) override;

    void Process_vkCreateEvent(const ApiCallInfo& call_info, args::CreateEvent& args) override;

    void Process_vkDestroyEvent(const ApiCallInfo& call_info, args::DestroyEvent& args) override;

    void Process_vkCreateQueryPool(const ApiCallInfo& call_info, args::CreateQueryPool& args) override;

    void Process_vkDestroyQueryPool(const ApiCallInfo& call_info, args::DestroyQueryPool& args) override;

    void Process_vkCreateShadersEXT(const ApiCallInfo& call_info, args::CreateShadersEXT& args) override;

    void Process_vkDestroyShaderEXT(const ApiCallInfo& call_info, args::DestroyShaderEXT& args) override;

    void Process_vkCreateShaderModule(const ApiCallInfo& call_info, args::CreateShaderModule& args) override;

    void Process_vkDestroyShaderModule(const ApiCallInfo& call_info, args::DestroyShaderModule& args) override;

    void Process_vkCreateValidationCacheEXT(
        const ApiCallInfo& call_info, args::CreateValidationCacheEXT& args
    ) override;

    void Process_vkDestroyValidationCacheEXT(
        const ApiCallInfo& call_info, args::DestroyValidationCacheEXT& args
    ) override;

    void Process_vkCreatePipelineCache(const ApiCallInfo& call_info, args::CreatePipelineCache& args) override;

    void Process_vkDestroyPipelineCache(const ApiCallInfo& call_info, args::DestroyPipelineCache& args) override;

    void Process_vkCreateGraphicsPipelines(const ApiCallInfo& call_info, args::CreateGraphicsPipelines& args) override;

    void Process_vkCreateComputePipelines(const ApiCallInfo& call_info, args::CreateComputePipelines& args) override;

    void Process_vkCreateRayTracingPipelinesNV(
        const ApiCallInfo& call_info, args::CreateRayTracingPipelinesNV& args
    ) override;

    void Process_vkCreateRayTracingPipelinesKHR(
        const ApiCallInfo& call_info, args::CreateRayTracingPipelinesKHR& args
    ) override;

    void Process_vkDestroyPipeline(const ApiCallInfo& call_info, args::DestroyPipeline& args) override;

    void Process_vkCreatePipelineLayout(const ApiCallInfo& call_info, args::CreatePipelineLayout& args) override;

    void Process_vkDestroyPipelineLayout(const ApiCallInfo& call_info, args::DestroyPipelineLayout& args) override;

    void Process_vkCreateDescriptorSetLayout(
        const ApiCallInfo& call_info, args::CreateDescriptorSetLayout& args
    ) override;

    void Process_vkDestroyDescriptorSetLayout(
        const ApiCallInfo& call_info, args::DestroyDescriptorSetLayout& args
    ) override;

    void Process_vkCreateDescriptorPool(const ApiCallInfo& call_info, args::CreateDescriptorPool& args) override;

    void Process_vkDestroyDescriptorPool(const ApiCallInfo& call_info, args::DestroyDescriptorPool& args) override;

    void Process_vkResetDescriptorPool(const ApiCallInfo& call_info, args::ResetDescriptorPool& args) override;

    void Process_vkAllocateDescriptorSets(const ApiCallInfo& call_info, args::AllocateDescriptorSets& args) override;

    void Process_vkFreeDescriptorSets(const ApiCallInfo& call_info, args::FreeDescriptorSets& args) override;

    void Process_vkCreateRenderPass(const ApiCallInfo& call_info, args::CreateRenderPass& args) override;

    void Process_vkCreateRenderPass2KHR(const ApiCallInfo& call_info, args::CreateRenderPass2KHR& args) override;

    void Process_vkCreateRenderPass2(const ApiCallInfo& call_info, args::CreateRenderPass2& args) override;

    void Process_vkDestroyRenderPass(const ApiCallInfo& call_info, args::DestroyRenderPass& args) override;

    void Process_vkCreateSamplerYcbcrConversion(
        const ApiCallInfo& call_info, args::CreateSamplerYcbcrConversion& args
    ) override;

    void Process_vkCreateSamplerYcbcrConversionKHR(
        const ApiCallInfo& call_info, args::CreateSamplerYcbcrConversionKHR& args
    ) override;

    void Process_vkDestroySamplerYcbcrConversion(
        const ApiCallInfo& call_info, args::DestroySamplerYcbcrConversion& args
    ) override;

    void Process_vkDestroySamplerYcbcrConversionKHR(
        const ApiCallInfo& call_info, args::DestroySamplerYcbcrConversionKHR& args
    ) override;

    void Process_vkCreatePrivateDataSlot(const ApiCallInfo& call_info, args::CreatePrivateDataSlot& args) override;

    void Process_vkCreatePrivateDataSlotEXT(
        const ApiCallInfo& call_info, args::CreatePrivateDataSlotEXT& args
    ) override;

    void Process_vkDestroyPrivateDataSlot(const ApiCallInfo& call_info, args::DestroyPrivateDataSlot& args) override;

    void Process_vkDestroyPrivateDataSlotEXT(
        const ApiCallInfo& call_info, args::DestroyPrivateDataSlotEXT& args
    ) override;

    void Process_vkCreateDescriptorUpdateTemplate(
        const ApiCallInfo& call_info, args::CreateDescriptorUpdateTemplate& args
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplate(
        const ApiCallInfo& call_info, args::DestroyDescriptorUpdateTemplate& args
    ) override;

    void Process_vkCreateDescriptorUpdateTemplateKHR(
        const ApiCallInfo& call_info, args::CreateDescriptorUpdateTemplateKHR& args
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplateKHR(
        const ApiCallInfo& call_info, args::DestroyDescriptorUpdateTemplateKHR& args
    ) override;

    void Process_vkUpdateDescriptorSets(const ApiCallInfo& call_info, args::UpdateDescriptorSets& args) override;

    void Process_vkUpdateDescriptorSetWithTemplate(
        const ApiCallInfo& call_info, args::UpdateDescriptorSetWithTemplate& args
    ) override;

    void Process_vkUpdateDescriptorSetWithTemplateKHR(
        const ApiCallInfo& call_info, args::UpdateDescriptorSetWithTemplateKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSet& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetKHR(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSetKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSet2& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2KHR(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSet2KHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSetWithTemplate& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplateKHR(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSetWithTemplateKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSetWithTemplate2& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2KHR(
        const ApiCallInfo& call_info, args::CmdPushDescriptorSetWithTemplate2KHR& args
    ) override;

    void Process_vkCreateBuffer(const ApiCallInfo& call_info, args::CreateBuffer& args) override;

    void Process_vkDestroyBuffer(const ApiCallInfo& call_info, args::DestroyBuffer& args) override;

    void Process_vkCreateBufferView(const ApiCallInfo& call_info, args::CreateBufferView& args) override;

    void Process_vkDestroyBufferView(const ApiCallInfo& call_info, args::DestroyBufferView& args) override;

    void Process_vkCreateImage(const ApiCallInfo& call_info, args::CreateImage& args) override;

    void Process_vkDestroyImage(const ApiCallInfo& call_info, args::DestroyImage& args) override;

    void Process_vkCreateImageView(const ApiCallInfo& call_info, args::CreateImageView& args) override;

    void Process_vkDestroyImageView(const ApiCallInfo& call_info, args::DestroyImageView& args) override;

    void Process_vkCreateSampler(const ApiCallInfo& call_info, args::CreateSampler& args) override;

    void Process_vkDestroySampler(const ApiCallInfo& call_info, args::DestroySampler& args) override;

    void Process_vkGetRandROutputDisplayEXT(
        const ApiCallInfo& call_info, args::GetRandROutputDisplayEXT& args
    ) override;

    void Process_vkGetDrmDisplayEXT(const ApiCallInfo& call_info, args::GetDrmDisplayEXT& args) override;

    void Process_vkGetWinrtDisplayNV(const ApiCallInfo& call_info, args::GetWinrtDisplayNV& args) override;

    void Process_vkCreateDisplayModeKHR(const ApiCallInfo& call_info, args::CreateDisplayModeKHR& args) override;

    void Process_vkCreateSwapchainKHR(const ApiCallInfo& call_info, args::CreateSwapchainKHR& args) override;

    void Process_vkCreateSharedSwapchainsKHR(
        const ApiCallInfo& call_info, args::CreateSharedSwapchainsKHR& args
    ) override;

    void Process_vkDestroySwapchainKHR(const ApiCallInfo& call_info, args::DestroySwapchainKHR& args) override;

    void Process_vkGetSwapchainImagesKHR(const ApiCallInfo& call_info, args::GetSwapchainImagesKHR& args) override;

    void Process_vkAcquireNextImageKHR(const ApiCallInfo& call_info, args::AcquireNextImageKHR& args) override;

    void Process_vkAcquireNextImage2KHR(const ApiCallInfo& call_info, args::AcquireNextImage2KHR& args) override;

    void Process_vkCreateFramebuffer(const ApiCallInfo& call_info, args::CreateFramebuffer& args) override;

    void Process_vkDestroyFramebuffer(const ApiCallInfo& call_info, args::DestroyFramebuffer& args) override;

    void Process_vkCmdSetVertexInputEXT(const ApiCallInfo& call_info, args::CmdSetVertexInputEXT& args) override;

    void Process_vkCmdSetRenderingAttachmentLocations(
        const ApiCallInfo& call_info, args::CmdSetRenderingAttachmentLocations& args
    ) override;

    void Process_vkCmdSetRenderingAttachmentLocationsKHR(
        const ApiCallInfo& call_info, args::CmdSetRenderingAttachmentLocationsKHR& args
    ) override;

    void Process_vkCmdSetRenderingInputAttachmentIndices(
        const ApiCallInfo& call_info, args::CmdSetRenderingInputAttachmentIndices& args
    ) override;

    void Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
        const ApiCallInfo& call_info, args::CmdSetRenderingInputAttachmentIndicesKHR& args
    ) override;

    void Process_vkCmdSetViewport(const ApiCallInfo& call_info, args::CmdSetViewport& args) override;

    void Process_vkCmdSetViewportWithCount(const ApiCallInfo& call_info, args::CmdSetViewportWithCount& args) override;

    void Process_vkCmdSetViewportWithCountEXT(
        const ApiCallInfo& call_info, args::CmdSetViewportWithCountEXT& args
    ) override;

    void Process_vkCmdSetScissor(const ApiCallInfo& call_info, args::CmdSetScissor& args) override;

    void Process_vkCmdSetScissorWithCount(const ApiCallInfo& call_info, args::CmdSetScissorWithCount& args) override;

    void Process_vkCmdSetScissorWithCountEXT(
        const ApiCallInfo& call_info, args::CmdSetScissorWithCountEXT& args
    ) override;

    void Process_vkCmdSetLineWidth(const ApiCallInfo& call_info, args::CmdSetLineWidth& args) override;

    void Process_vkCmdSetDepthBias(const ApiCallInfo& call_info, args::CmdSetDepthBias& args) override;
    void Process_vkCmdSetDepthBias2EXT(const ApiCallInfo& call_info, args::CmdSetDepthBias2EXT& args) override;

    void Process_vkCmdSetBlendConstants(const ApiCallInfo& call_info, args::CmdSetBlendConstants& args) override;

    void Process_vkCmdSetDepthBounds(const ApiCallInfo& call_info, args::CmdSetDepthBounds& args) override;

    void Process_vkCmdSetStencilCompareMask(
        const ApiCallInfo& call_info, args::CmdSetStencilCompareMask& args
    ) override;

    void Process_vkCmdSetStencilWriteMask(const ApiCallInfo& call_info, args::CmdSetStencilWriteMask& args) override;

    void Process_vkCmdSetStencilReference(const ApiCallInfo& call_info, args::CmdSetStencilReference& args) override;

    void Process_vkCmdSetCullMode(const ApiCallInfo& call_info, args::CmdSetCullMode& args) override;
    void Process_vkCmdSetCullModeEXT(const ApiCallInfo& call_info, args::CmdSetCullModeEXT& args) override;

    void Process_vkCmdSetFrontFace(const ApiCallInfo& call_info, args::CmdSetFrontFace& args) override;
    void Process_vkCmdSetFrontFaceEXT(const ApiCallInfo& call_info, args::CmdSetFrontFaceEXT& args) override;

    void Process_vkCmdSetPrimitiveTopology(const ApiCallInfo& call_info, args::CmdSetPrimitiveTopology& args) override;
    void Process_vkCmdSetPrimitiveTopologyEXT(
        const ApiCallInfo& call_info, args::CmdSetPrimitiveTopologyEXT& args
    ) override;

    void Process_vkCmdSetDepthTestEnable(const ApiCallInfo& call_info, args::CmdSetDepthTestEnable& args) override;
    void Process_vkCmdSetDepthTestEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthTestEnableEXT& args
    ) override;

    void Process_vkCmdSetDepthWriteEnable(const ApiCallInfo& call_info, args::CmdSetDepthWriteEnable& args) override;
    void Process_vkCmdSetDepthWriteEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthWriteEnableEXT& args
    ) override;

    void Process_vkCmdSetDepthCompareOp(const ApiCallInfo& call_info, args::CmdSetDepthCompareOp& args) override;
    void Process_vkCmdSetDepthCompareOpEXT(const ApiCallInfo& call_info, args::CmdSetDepthCompareOpEXT& args) override;

    void Process_vkCmdSetDepthBoundsTestEnable(
        const ApiCallInfo& call_info, args::CmdSetDepthBoundsTestEnable& args
    ) override;
    void Process_vkCmdSetDepthBoundsTestEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthBoundsTestEnableEXT& args
    ) override;

    void Process_vkCmdSetStencilTestEnable(const ApiCallInfo& call_info, args::CmdSetStencilTestEnable& args) override;
    void Process_vkCmdSetStencilTestEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetStencilTestEnableEXT& args
    ) override;

    void Process_vkCmdSetStencilOp(const ApiCallInfo& call_info, args::CmdSetStencilOp& args) override;
    void Process_vkCmdSetStencilOpEXT(const ApiCallInfo& call_info, args::CmdSetStencilOpEXT& args) override;

    void Process_vkCmdSetRasterizerDiscardEnable(
        const ApiCallInfo& call_info, args::CmdSetRasterizerDiscardEnable& args
    ) override;
    void Process_vkCmdSetRasterizerDiscardEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetRasterizerDiscardEnableEXT& args
    ) override;

    void Process_vkCmdSetDepthBiasEnable(const ApiCallInfo& call_info, args::CmdSetDepthBiasEnable& args) override;
    void Process_vkCmdSetDepthBiasEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthBiasEnableEXT& args
    ) override;

    void Process_vkCmdSetPrimitiveRestartEnable(
        const ApiCallInfo& call_info, args::CmdSetPrimitiveRestartEnable& args
    ) override;
    void Process_vkCmdSetPrimitiveRestartEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetPrimitiveRestartEnableEXT& args
    ) override;

    void Process_vkCmdSetPatchControlPointsEXT(
        const ApiCallInfo& call_info, args::CmdSetPatchControlPointsEXT& args
    ) override;

    void Process_vkCmdSetLogicOpEXT(const ApiCallInfo& call_info, args::CmdSetLogicOpEXT& args) override;

    void Process_vkCmdSetColorWriteEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetColorWriteEnableEXT& args
    ) override;

    void Process_vkCmdSetLineStipple(const ApiCallInfo& call_info, args::CmdSetLineStipple& args) override;
    void Process_vkCmdSetLineStippleKHR(const ApiCallInfo& call_info, args::CmdSetLineStippleKHR& args) override;
    void Process_vkCmdSetLineStippleEXT(const ApiCallInfo& call_info, args::CmdSetLineStippleEXT& args) override;

    void Process_vkCmdSetFragmentShadingRateKHR(
        const ApiCallInfo& call_info, args::CmdSetFragmentShadingRateKHR& args
    ) override;
    void Process_vkCmdSetFragmentShadingRateEnumNV(
        const ApiCallInfo& call_info, args::CmdSetFragmentShadingRateEnumNV& args
    ) override;

    void Process_vkCmdSetViewportWScalingNV(
        const ApiCallInfo& call_info, args::CmdSetViewportWScalingNV& args
    ) override;

    void Process_vkCmdSetDiscardRectangleEXT(
        const ApiCallInfo& call_info, args::CmdSetDiscardRectangleEXT& args
    ) override;
    void Process_vkCmdSetDiscardRectangleEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDiscardRectangleEnableEXT& args
    ) override;
    void Process_vkCmdSetDiscardRectangleModeEXT(
        const ApiCallInfo& call_info, args::CmdSetDiscardRectangleModeEXT& args
    ) override;

    void Process_vkCmdSetSampleLocationsEXT(
        const ApiCallInfo& call_info, args::CmdSetSampleLocationsEXT& args
    ) override;

    void Process_vkCmdSetViewportShadingRatePaletteNV(
        const ApiCallInfo& call_info, args::CmdSetViewportShadingRatePaletteNV& args
    ) override;
    void Process_vkCmdSetCoarseSampleOrderNV(
        const ApiCallInfo& call_info, args::CmdSetCoarseSampleOrderNV& args
    ) override;

    void Process_vkCmdSetExclusiveScissorEnableNV(
        const ApiCallInfo& call_info, args::CmdSetExclusiveScissorEnableNV& args
    ) override;
    void Process_vkCmdSetExclusiveScissorNV(
        const ApiCallInfo& call_info, args::CmdSetExclusiveScissorNV& args
    ) override;

    void Process_vkCmdSetDepthClampEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthClampEnableEXT& args
    ) override;
    void Process_vkCmdSetPolygonModeEXT(const ApiCallInfo& call_info, args::CmdSetPolygonModeEXT& args) override;
    void Process_vkCmdSetRasterizationSamplesEXT(
        const ApiCallInfo& call_info, args::CmdSetRasterizationSamplesEXT& args
    ) override;
    void Process_vkCmdSetSampleMaskEXT(const ApiCallInfo& call_info, args::CmdSetSampleMaskEXT& args) override;
    void Process_vkCmdSetAlphaToCoverageEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetAlphaToCoverageEnableEXT& args
    ) override;
    void Process_vkCmdSetAlphaToOneEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetAlphaToOneEnableEXT& args
    ) override;
    void Process_vkCmdSetLogicOpEnableEXT(const ApiCallInfo& call_info, args::CmdSetLogicOpEnableEXT& args) override;
    void Process_vkCmdSetColorBlendEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetColorBlendEnableEXT& args
    ) override;
    void Process_vkCmdSetColorBlendEquationEXT(
        const ApiCallInfo& call_info, args::CmdSetColorBlendEquationEXT& args
    ) override;
    void Process_vkCmdSetColorWriteMaskEXT(const ApiCallInfo& call_info, args::CmdSetColorWriteMaskEXT& args) override;
    void Process_vkCmdSetTessellationDomainOriginEXT(
        const ApiCallInfo& call_info, args::CmdSetTessellationDomainOriginEXT& args
    ) override;
    void Process_vkCmdSetRasterizationStreamEXT(
        const ApiCallInfo& call_info, args::CmdSetRasterizationStreamEXT& args
    ) override;
    void Process_vkCmdSetConservativeRasterizationModeEXT(
        const ApiCallInfo& call_info, args::CmdSetConservativeRasterizationModeEXT& args
    ) override;
    void Process_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
        const ApiCallInfo& call_info, args::CmdSetExtraPrimitiveOverestimationSizeEXT& args
    ) override;
    void Process_vkCmdSetDepthClipEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthClipEnableEXT& args
    ) override;
    void Process_vkCmdSetSampleLocationsEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetSampleLocationsEnableEXT& args
    ) override;
    void Process_vkCmdSetColorBlendAdvancedEXT(
        const ApiCallInfo& call_info, args::CmdSetColorBlendAdvancedEXT& args
    ) override;
    void Process_vkCmdSetProvokingVertexModeEXT(
        const ApiCallInfo& call_info, args::CmdSetProvokingVertexModeEXT& args
    ) override;
    void Process_vkCmdSetLineRasterizationModeEXT(
        const ApiCallInfo& call_info, args::CmdSetLineRasterizationModeEXT& args
    ) override;
    void Process_vkCmdSetLineStippleEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetLineStippleEnableEXT& args
    ) override;
    void Process_vkCmdSetDepthClipNegativeOneToOneEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthClipNegativeOneToOneEXT& args
    ) override;
    void Process_vkCmdSetViewportWScalingEnableNV(
        const ApiCallInfo& call_info, args::CmdSetViewportWScalingEnableNV& args
    ) override;
    void Process_vkCmdSetViewportSwizzleNV(const ApiCallInfo& call_info, args::CmdSetViewportSwizzleNV& args) override;
    void Process_vkCmdSetCoverageToColorEnableNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageToColorEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageToColorLocationNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageToColorLocationNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationModeNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageModulationModeNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationTableEnableNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageModulationTableEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationTableNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageModulationTableNV& args
    ) override;
    void Process_vkCmdSetShadingRateImageEnableNV(
        const ApiCallInfo& call_info, args::CmdSetShadingRateImageEnableNV& args
    ) override;
    void Process_vkCmdSetRepresentativeFragmentTestEnableNV(
        const ApiCallInfo& call_info, args::CmdSetRepresentativeFragmentTestEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageReductionModeNV(
        const ApiCallInfo& call_info, args::CmdSetCoverageReductionModeNV& args
    ) override;

    void Process_vkCmdSetDepthClampRangeEXT(
        const ApiCallInfo& call_info, args::CmdSetDepthClampRangeEXT& args
    ) override;

    void Process_vkCmdSetAttachmentFeedbackLoopEnableEXT(
        const ApiCallInfo& call_info, args::CmdSetAttachmentFeedbackLoopEnableEXT& args
    ) override;

    void Process_vkCmdSetRayTracingPipelineStackSizeKHR(
        const ApiCallInfo& call_info, args::CmdSetRayTracingPipelineStackSizeKHR& args
    ) override;

    // Not backed by a VkDynamicState enum, but still unimplemented command-buffer state setters.
    void Process_vkCmdSetComputeOccupancyPriorityNV(
        const ApiCallInfo& call_info, args::CmdSetComputeOccupancyPriorityNV& args
    ) override;
    void Process_vkCmdSetPrimitiveRestartIndexEXT(
        const ApiCallInfo& call_info, args::CmdSetPrimitiveRestartIndexEXT& args
    ) override;
    void Process_vkCmdSetDispatchParametersARM(
        const ApiCallInfo& call_info, args::CmdSetDispatchParametersARM& args
    ) override;

    void Process_vkCreateAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::CreateAccelerationStructureKHR& args
    ) override;

    void Process_vkCreateAccelerationStructureNV(
        const ApiCallInfo& call_info, args::CreateAccelerationStructureNV& args
    ) override;

    void Process_vkDestroyAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::DestroyAccelerationStructureKHR& args
    ) override;

    void Process_vkDestroyAccelerationStructureNV(
        const ApiCallInfo& call_info, args::DestroyAccelerationStructureNV& args
    ) override;

    void Process_vkBuildAccelerationStructuresKHR(
        const ApiCallInfo& call_info, args::BuildAccelerationStructuresKHR& args
    ) override;

    void Process_vkCmdBuildAccelerationStructuresKHR(
        const ApiCallInfo& call_info, args::CmdBuildAccelerationStructuresKHR& args
    ) override;

    void ProcessVulkanBuildAccelerationStructuresCommand(
        format::HandleId device,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos
    ) override;

    void Process_vkCopyAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::CopyAccelerationStructureKHR& args
    ) override;

    void Process_vkCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& call_info, args::CopyAccelerationStructureToMemoryKHR& args
    ) override;

    void Process_vkCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::CopyMemoryToAccelerationStructureKHR& args
    ) override;

    void Process_vkCmdCopyAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::CmdCopyAccelerationStructureKHR& args
    ) override;

    void Process_vkCmdCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& call_info, args::CmdCopyAccelerationStructureToMemoryKHR& args
    ) override;

    void ProcessVulkanCopyAccelerationStructuresCommand(
        format::HandleId device, StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
    ) override;

    // Transfer command overrides
    void Process_vkCmdCopyBuffer(const ApiCallInfo& call_info, args::CmdCopyBuffer& args) override;

    void Process_vkCmdCopyBuffer2(const ApiCallInfo& call_info, args::CmdCopyBuffer2& args) override;

    void Process_vkCmdCopyBuffer2KHR(const ApiCallInfo& call_info, args::CmdCopyBuffer2KHR& args) override;

    void Process_vkCmdCopyImage(const ApiCallInfo& call_info, args::CmdCopyImage& args) override;

    void Process_vkCmdCopyImage2(const ApiCallInfo& call_info, args::CmdCopyImage2& args) override;

    void Process_vkCmdCopyImage2KHR(const ApiCallInfo& call_info, args::CmdCopyImage2KHR& args) override;

    void Process_vkCmdCopyBufferToImage(const ApiCallInfo& call_info, args::CmdCopyBufferToImage& args) override;

    void Process_vkCmdCopyBufferToImage2(const ApiCallInfo& call_info, args::CmdCopyBufferToImage2& args) override;

    void Process_vkCmdCopyBufferToImage2KHR(
        const ApiCallInfo& call_info, args::CmdCopyBufferToImage2KHR& args
    ) override;

    void Process_vkCmdCopyImageToBuffer(const ApiCallInfo& call_info, args::CmdCopyImageToBuffer& args) override;

    void Process_vkCmdCopyImageToBuffer2(const ApiCallInfo& call_info, args::CmdCopyImageToBuffer2& args) override;

    void Process_vkCmdCopyImageToBuffer2KHR(
        const ApiCallInfo& call_info, args::CmdCopyImageToBuffer2KHR& args
    ) override;

    void Process_vkCmdBlitImage(const ApiCallInfo& call_info, args::CmdBlitImage& args) override;

    void Process_vkCmdBlitImage2(const ApiCallInfo& call_info, args::CmdBlitImage2& args) override;

    void Process_vkCmdBlitImage2KHR(const ApiCallInfo& call_info, args::CmdBlitImage2KHR& args) override;

    void Process_vkCmdResolveImage(const ApiCallInfo& call_info, args::CmdResolveImage& args) override;

    void Process_vkCmdResolveImage2(const ApiCallInfo& call_info, args::CmdResolveImage2& args) override;

    void Process_vkCmdResolveImage2KHR(const ApiCallInfo& call_info, args::CmdResolveImage2KHR& args) override;

    void Process_vkCmdCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& call_info, args::CmdCopyMemoryToAccelerationStructureKHR& args
    ) override;

    void Process_vkCreateDeferredOperationKHR(
        const ApiCallInfo& call_info, args::CreateDeferredOperationKHR& args
    ) override;

    void Process_vkDestroyDeferredOperationKHR(
        const ApiCallInfo& call_info, args::DestroyDeferredOperationKHR& args
    ) override;

    void Process_vkCreatePipelineBinariesKHR(
        const ApiCallInfo& call_info, args::CreatePipelineBinariesKHR& args
    ) override;

    void Process_vkDestroyPipelineBinaryKHR(
        const ApiCallInfo& call_info, args::DestroyPipelineBinaryKHR& args
    ) override;

    void Process_vkCreateVideoSessionKHR(const ApiCallInfo& call_info, args::CreateVideoSessionKHR& args) override;

    void Process_vkDestroyVideoSessionKHR(const ApiCallInfo& call_info, args::DestroyVideoSessionKHR& args) override;

    void Process_vkCreateVideoSessionParametersKHR(
        const ApiCallInfo& call_info, args::CreateVideoSessionParametersKHR& args
    ) override;

    void Process_vkDestroyVideoSessionParametersKHR(
        const ApiCallInfo& call_info, args::DestroyVideoSessionParametersKHR& args
    ) override;

    void Process_vkCreateIndirectCommandsLayoutEXT(
        const ApiCallInfo& call_info, args::CreateIndirectCommandsLayoutEXT& args
    ) override;

    void Process_vkDestroyIndirectCommandsLayoutEXT(
        const ApiCallInfo& call_info, args::DestroyIndirectCommandsLayoutEXT& args
    ) override;

    void Process_vkCreateMicromapEXT(const ApiCallInfo& call_info, args::CreateMicromapEXT& args) override;

    void Process_vkDestroyMicromapEXT(const ApiCallInfo& call_info, args::DestroyMicromapEXT& args) override;

    void Process_vkCreateOpticalFlowSessionNV(
        const ApiCallInfo& call_info, args::CreateOpticalFlowSessionNV& args
    ) override;

    void Process_vkDestroyOpticalFlowSessionNV(
        const ApiCallInfo& call_info, args::DestroyOpticalFlowSessionNV& args
    ) override;

    void Process_vkCreateDataGraphPipelinesARM(
        const ApiCallInfo& call_info, args::CreateDataGraphPipelinesARM& args
    ) override;

    void Process_vkCreateDataGraphPipelineSessionARM(
        const ApiCallInfo& call_info, args::CreateDataGraphPipelineSessionARM& args
    ) override;

    void Process_vkDestroyDataGraphPipelineSessionARM(
        const ApiCallInfo& call_info, args::DestroyDataGraphPipelineSessionARM& args
    ) override;

    void Process_vkCmdDispatchDataGraphARM(const ApiCallInfo& call_info, args::CmdDispatchDataGraphARM& args) override;

    // TODO these were originally overridden in the export json
    // notes about each one in the implementation but need to determine
    // if these are still necessary
    void Process_vkCmdBuildAccelerationStructuresIndirectKHR(
        const ApiCallInfo& call_info, args::CmdBuildAccelerationStructuresIndirectKHR& args
    ) override;

    void Process_vkGetPipelineCacheData(const ApiCallInfo& call_info, args::GetPipelineCacheData& args) override;

    void Process_vkCmdPushConstants(const ApiCallInfo& call_info, args::CmdPushConstants& args) override;

    void Process_vkCmdBindDescriptorSets(const ApiCallInfo& call_info, args::CmdBindDescriptorSets& args) override;

    void Process_vkCmdBindDescriptorSets2(const ApiCallInfo& call_info, args::CmdBindDescriptorSets2& args) override;

    void Process_vkCmdBindDescriptorSets2KHR(
        const ApiCallInfo& call_info, args::CmdBindDescriptorSets2KHR& args
    ) override;

  private:
    struct LibraryInfo
    {
        format::HandleId pipelineHandle{};
        int64_t pipelineId{};
        std::optional<int64_t> renderPass;
        VkPipelineCreateFlagBits2 flags{};
        VkGraphicsPipelineLibraryFlagsEXT libraryFlags{};
    };

    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-vertex-input
    struct GraphicsPipelineVertexInputState
    {
        std::optional<int64_t> vertexInputStateId;
        std::optional<int64_t> inputAssemblyStateId;
    };
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-pre-rasterization
    struct GraphicsPipelinePreRasterizationShaderState
    {
        size_t numShaderStages = 0; // excludes fragment shader
        // pipeline layout is specified in final linked pipeline
        std::optional<int64_t> viewportStateId;
        std::optional<int64_t> rasterizationStateId;
        std::optional<int64_t> tessellationStateId;
        // render pass is in multiple places and is handled separately
        // TODO: VkPipelineRenderingCreateInfo (in multiple places)
        // TODO: VkPipelineDiscardRectangleStateCreateInfoEXT
        // TODO: VkPipelineFragmentShadingRateStateCreateInfoKHR
        // TODO: VkPipelineMultisampleStateCreateInfo (in multiple places; not listed on the Pre-Rasterization Shader
        // State section but is here according to VUID-VkGraphicsPipelineCreateInfo-pRasterizationState-09039)
    };
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-fragment-shader
    struct GraphicsPipelineFragmentShaderState
    {
        size_t numShaderStages = 0; // optional fragment shader only, so only 0 or 1
        // pipeline layout is specified in final linked pipeline
        // VkPipelineMultisampleStateCreateInfo is in multiple places and is handled separately
        std::optional<int64_t> depthStencilStateId;
        // render pass is in multiple places and is handled separately
        // TODO: VkPipelineRenderingCreateInfo (in multiple places)
        // TODO: VkPipelineFragmentShadingRateStateCreateInfoKHR and other shading rate stuff
        // TODO: VkRenderingInputAttachmentIndexInfo
    };
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-fragment-output
    struct GraphicsPipelineFragmentOutputState
    {
        std::optional<int64_t> colorBlendStateId;
        // render pass is in multiple places and is handled separately
        // VkPipelineMultisampleStateCreateInfo is in multiple places and is handled separately
        // TODO: VkPipelineRenderingCreateInfo (in multiple places)
        // TODO: VkAttachmentSampleCountInfoAMD/VkAttachmentSampleCountInfoNV
        // TODO: VkRenderingAttachmentLocationInfo
    };

    std::optional<int64_t> GetBasePipelineId(
        VkResult returnValue,
        const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
        const format::HandleId* pipelines,
        size_t currentPipelineIndex
    );

    std::unordered_map<VkGraphicsPipelineLibraryFlagBitsEXT, LibraryInfo> GetPipelineLibraryInfo(
        format::HandleId pipelineHandle, size_t libraryCount, const format::HandleId* libraryHandles
    );

    // Holds VkPipelineCreationFeedbackCreateInfo data extracted from a pipeline create info pNext chain.
    // pipelineFlags/pipelineDuration are the pipeline-level feedback; stageFeedbacks/stageFeedbackCount are
    // the per-stage feedback array, indexed by the original Vk*PipelineCreateInfo::pStages index. These are
    // only populated when the feedback struct is present in the pNext chain; otherwise the optionals are empty
    // and the corresponding database columns are written as NULL.
    struct PipelineCreationFeedback
    {
        std::optional<int64_t> pipelineFlags;
        std::optional<int64_t> pipelineDuration;
        const Decoded_VkPipelineCreationFeedback* stageFeedbacks = nullptr;
        uint64_t stageFeedbackCount = 0;
    };

    // Extracts the pipeline-level and per-stage feedback from a (possibly null) feedback create info struct.
    // Callers locate the struct while walking the pipeline create info pNext chain.
    PipelineCreationFeedback ReadPipelineCreationFeedback(
        const Decoded_VkPipelineCreationFeedbackCreateInfo* feedbackCreateInfo
    );

    // Returns {feedbackFlags, createDuration} for the stage at the given original pStages index, or
    // {nullopt, nullopt} when no feedback is available for that stage.
    static std::pair<std::optional<int64_t>, std::optional<int64_t>> GetStageCreationFeedback(
        const PipelineCreationFeedback& feedback, size_t stageIndex
    );

    void ProcessPipelineDynamicStateCreateInfo(
        const StructPointerDecoder<Decoded_VkPipelineDynamicStateCreateInfo>* createInfo,
        int64_t pipelineId,
        const std::unordered_set<VkDynamicState>& stage_states
    );
    void CopyPipelineDynamicStates(int64_t pipelineId, int64_t libraryPipelineId);

    // Returns true if the pipeline's VkPipelineDynamicStateCreateInfo enables the given dynamic state.
    bool PipelineEnablesDynamicState(
        const StructPointerDecoder<Decoded_VkPipelineDynamicStateCreateInfo>* createInfo, VkDynamicState state
    );

    GraphicsPipelineVertexInputState ProcessGraphicsPipelineVertexInputState(
        VkResult returnValue, const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
    );
    GraphicsPipelineVertexInputState CopyGraphicsPipelineVertexInputState(
        int64_t pipelineId, int64_t libraryPipelineId
    );
    GraphicsPipelinePreRasterizationShaderState ProcessGraphicsPipelinePreRasterizationShaderState(
        std::optional<int64_t> deviceId,
        const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
        int64_t pipelineId,
        int64_t pipelineHandle,
        const PipelineCreationFeedback& feedback
    );
    GraphicsPipelinePreRasterizationShaderState CopyGraphicsPipelinePreRasterizationShaderState(
        int64_t pipelineId, int64_t libraryPipelineId
    );
    GraphicsPipelineFragmentShaderState ProcessGraphicsPipelineFragmentShaderState(
        std::optional<int64_t> deviceId,
        const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
        int64_t pipelineId,
        int64_t pipelineHandle,
        size_t num_pre_rasterization_shaders,
        const PipelineCreationFeedback& feedback
    );
    GraphicsPipelineFragmentShaderState CopyGraphicsPipelineFragmentShaderState(
        int64_t pipelineId, int64_t libraryPipelineId, size_t num_pre_rasterization_shaders
    );
    GraphicsPipelineFragmentOutputState ProcessGraphicsPipelineFragmentOutputState(
        const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
    );
    GraphicsPipelineFragmentOutputState CopyGraphicsPipelineFragmentOutputState(
        int64_t pipelineId, int64_t libraryPipelineId
    );

    // Present in both fragment shader state and fragment output state, but both need to be identically-defined
    std::optional<int64_t> ProcessGraphicsPipelineMultisampleState(
        const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
    );
    std::optional<int64_t> CopyGraphicsPipelineMultisampleState(int64_t pipelineId, int64_t libraryPipelineId);

    void ProcessPipelineShaderStageCreateInfo(
        std::optional<int64_t> deviceId,
        int64_t pipelineId,
        int64_t pipelineHandle,
        const Decoded_VkPipelineShaderStageCreateInfo& createInfo,
        size_t stageIndex,
        std::optional<int64_t> feedbackFlags,
        std::optional<int64_t> createDuration
    );

    // implemented in generated_vulkan_process_features.cpp
    void ProcessVkPhysicalDeviceFeatures(
        VkPhysicalDeviceFeatures* deviceFeatures, std::vector<std::string_view>& enabledFeatureNames
    );
    void ProcessVkDeviceCreateInfoPNext(PNextNode* pNext, std::vector<std::string_view>& enabledFeatureNames);
    template <typename T>
        requires std::same_as<T, Decoded_VkRenderPassCreateInfo> || std::same_as<T, Decoded_VkRenderPassCreateInfo2>
    void CreateRenderPass(
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<T>* pCreateInfo,
        HandlePointerDecoder<VkRenderPass>* pRenderPass
    );

    void CreateSamplerYcbcrConversion(
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
        HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
    );
    void DestroySamplerYcbcrConversion(format::HandleId ycbcrConversion);
    void CreatePrivateDataSlot(
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
        HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
    );
    void DestroyPrivateDataSlot(format::HandleId privateDataSlot);
    void CreateDescriptorUpdateTemplate(
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
        HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
    );
    void DestroyDescriptorUpdateTemplate(format::HandleId descriptorUpdateTemplate);

    void GetDisplay(
        VkResult returnValue, format::HandleId physicalDevice, HandlePointerDecoder<VkDisplayKHR>* pDisplay
    );

    void BindDescriptorSets2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
    );

    void WriteOrPushDescriptorSet(
        format::HandleId device,
        const Decoded_VkWriteDescriptorSet& descriptorWrite,
        int64_t descriptorSetDst,
        std::optional<int64_t> commandBufferRecordingId,
        int64_t layoutId,
        bool isPush
    );
    void WriteDescriptorSet(format::HandleId device, const Decoded_VkWriteDescriptorSet& descriptorWrite);
    void CopyDescriptorSet(const Decoded_VkCopyDescriptorSet& descriptorCopy);

    void PushDescriptorSet(
        format::HandleId commandBuffer,
        std::optional<VkPipelineBindPoint> bindPoint,
        std::optional<VkShaderStageFlags> stageFlags,
        format::HandleId pipelineLayout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
    );

    void WriteOrPushDescriptorSetWithTemplate(
        format::HandleId device,
        int64_t descriptorSetDst,
        std::optional<int64_t> commandBufferRecordingId,
        int64_t layoutId,
        format::HandleId descriptorUpdateTemplate,
        const DescriptorUpdateTemplateDecoder* pData,
        bool isPush
    );
    void WriteDescriptorSetWithTemplate(
        format::HandleId device,
        format::HandleId descriptorSet,
        format::HandleId descriptorUpdateTemplate,
        const DescriptorUpdateTemplateDecoder* pData
    );
    void PushDescriptorSetWithTemplate(
        format::HandleId commandBuffer,
        format::HandleId descriptorUpdateTemplate,
        format::HandleId pipelineLayout,
        uint32_t set,
        const DescriptorUpdateTemplateDecoder* pData
    );
    void PushDescriptorSetWithTemplate2(
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
    );

    void ProcessVkAccelerationStructureBuildGeometryInfo(
        const int64_t buildId,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
    );

    void ProcessVkAccelerationStructureBuildRangeInfo(
        const int64_t infoId,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos,
        size_t infoIndex
    );

    // Transfer command utility functions
    void ProcessTransferCommandBufferCopy(
        format::HandleId commandBuffer,
        format::HandleId srcBuffer,
        format::HandleId dstBuffer,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferCopy>* pRegions
    );

    void ProcessTransferCommandBufferCopy2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
    );

    void ProcessTransferCommandImageCopy(
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkImageCopy>* pRegions
    );

    void ProcessTransferCommandImageCopy2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
    );

    void ProcessTransferCommandBufferToImage(
        format::HandleId commandBuffer,
        format::HandleId srcBuffer,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
    );

    void ProcessTransferCommandBufferToImage2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
    );

    void ProcessTransferCommandImageToBuffer(
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstBuffer,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
    );

    void ProcessTransferCommandImageToBuffer2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
    );

    void ProcessTransferCommandBlit(
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        VkFilter filter,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkImageBlit>* pRegions
    );

    void ProcessTransferCommandBlit2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
    );

    void ProcessTransferCommandResolve2(
        format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
    );
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // VULKAN_SQLITE_CONSUMER_EXT_H
