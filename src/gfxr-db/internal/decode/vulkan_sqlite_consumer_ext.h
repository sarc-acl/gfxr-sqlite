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
        const ApiCallInfo& callInfo, args::SetDebugUtilsObjectNameEXT& args
    ) override;

    void Process_vkSetDebugUtilsObjectTagEXT(
        const ApiCallInfo& callInfo, args::SetDebugUtilsObjectTagEXT& args
    ) override;

    void Process_vkQueueBeginDebugUtilsLabelEXT(
        const ApiCallInfo& callInfo, args::QueueBeginDebugUtilsLabelEXT& args
    ) override;

    void Process_vkQueueEndDebugUtilsLabelEXT(
        const ApiCallInfo& callInfo, args::QueueEndDebugUtilsLabelEXT& args
    ) override;

    void Process_vkQueueInsertDebugUtilsLabelEXT(
        const ApiCallInfo& callInfo, args::QueueInsertDebugUtilsLabelEXT& args
    ) override;

    void Process_vkCmdBeginDebugUtilsLabelEXT(
        const ApiCallInfo& callInfo, args::CmdBeginDebugUtilsLabelEXT& args
    ) override;

    void Process_vkCmdEndDebugUtilsLabelEXT(const ApiCallInfo& callInfo, args::CmdEndDebugUtilsLabelEXT& args) override;

    void Process_vkCmdInsertDebugUtilsLabelEXT(
        const ApiCallInfo& callInfo, args::CmdInsertDebugUtilsLabelEXT& args
    ) override;

    void Process_vkDebugMarkerSetObjectTagEXT(
        const ApiCallInfo& callInfo, args::DebugMarkerSetObjectTagEXT& args
    ) override;

    void Process_vkDebugMarkerSetObjectNameEXT(
        const ApiCallInfo& callInfo, args::DebugMarkerSetObjectNameEXT& args
    ) override;

    void Process_vkCmdDebugMarkerBeginEXT(const ApiCallInfo& callInfo, args::CmdDebugMarkerBeginEXT& args) override;

    void Process_vkCmdDebugMarkerEndEXT(const ApiCallInfo& callInfo, args::CmdDebugMarkerEndEXT& args) override;

    void Process_vkCmdDebugMarkerInsertEXT(const ApiCallInfo& callInfo, args::CmdDebugMarkerInsertEXT& args) override;

    void Process_vkCreateDebugReportCallbackEXT(
        const ApiCallInfo& callInfo, args::CreateDebugReportCallbackEXT& args
    ) override;

    void Process_vkDestroyDebugReportCallbackEXT(
        const ApiCallInfo& callInfo, args::DestroyDebugReportCallbackEXT& args
    ) override;

    void Process_vkCreateDebugUtilsMessengerEXT(
        const ApiCallInfo& callInfo, args::CreateDebugUtilsMessengerEXT& args
    ) override;

    void Process_vkDestroyDebugUtilsMessengerEXT(
        const ApiCallInfo& callInfo, args::DestroyDebugUtilsMessengerEXT& args
    ) override;

    void Process_vkCreateInstance(const ApiCallInfo& callInfo, args::CreateInstance& args) override;

    void Process_vkDestroyInstance(const ApiCallInfo& callInfo, args::DestroyInstance& args) override;

    void Process_vkEnumeratePhysicalDevices(const ApiCallInfo& callInfo, args::EnumeratePhysicalDevices& args) override;

    void Process_vkCreateDevice(const ApiCallInfo& callInfo, args::CreateDevice& args) override;

    void Process_vkDestroyDevice(const ApiCallInfo& callInfo, args::DestroyDevice& args) override;

    void Process_vkGetDeviceQueue(const ApiCallInfo& callInfo, args::GetDeviceQueue& args) override;

    void ProcessQueue(
        const ApiCallInfo& callInfo,
        format::HandleId device,
        uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        VkDeviceQueueCreateFlags flags,
        HandlePointerDecoder<VkQueue>* pQueue
    );

    void Process_vkGetDeviceQueue2(const ApiCallInfo& callInfo, args::GetDeviceQueue2& args) override;

    void Process_vkQueueSubmit(const ApiCallInfo& callInfo, args::QueueSubmit& args) override;

    void ProcessQueueSubmit2Info(
        const ApiCallInfo& callInfo,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
        format::HandleId fence
    );

    void Process_vkQueueSubmit2(const ApiCallInfo& callInfo, args::QueueSubmit2& args) override;

    void Process_vkQueueSubmit2KHR(const ApiCallInfo& callInfo, args::QueueSubmit2KHR& args) override;

    void Process_vkQueuePresentKHR(const ApiCallInfo& callInfo, args::QueuePresentKHR& args) override;

    void Process_vkCreateFence(const ApiCallInfo& callInfo, args::CreateFence& args) override;

    void Process_vkDestroyFence(const ApiCallInfo& callInfo, args::DestroyFence& args) override;

    void Process_vkResetFences(const ApiCallInfo& callInfo, args::ResetFences& args) override;

    void Process_vkWaitForFences(const ApiCallInfo& callInfo, args::WaitForFences& args) override;

    void Process_vkCreateSemaphore(const ApiCallInfo& callInfo, args::CreateSemaphore& args) override;

    void Process_vkDestroySemaphore(const ApiCallInfo& callInfo, args::DestroySemaphore& args) override;

    void Process_VkSemaphoreWaitInfo(
        const ApiCallInfo& callInfo,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
        uint64_t timeout
    );

    void Process_VkSemaphoreSignalInfo(
        const ApiCallInfo& callInfo,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
    );

    void Process_vkWaitSemaphores(const ApiCallInfo& callInfo, args::WaitSemaphores& args) override;

    void Process_vkSignalSemaphore(const ApiCallInfo& callInfo, args::SignalSemaphore& args) override;

    void Process_vkWaitSemaphoresKHR(const ApiCallInfo& callInfo, args::WaitSemaphoresKHR& args) override;

    void Process_vkSignalSemaphoreKHR(const ApiCallInfo& callInfo, args::SignalSemaphoreKHR& args) override;

    void Process_vkCreateEvent(const ApiCallInfo& callInfo, args::CreateEvent& args) override;

    void Process_vkDestroyEvent(const ApiCallInfo& callInfo, args::DestroyEvent& args) override;

    void Process_vkCreateQueryPool(const ApiCallInfo& callInfo, args::CreateQueryPool& args) override;

    void Process_vkDestroyQueryPool(const ApiCallInfo& callInfo, args::DestroyQueryPool& args) override;

    void Process_vkCreateShadersEXT(const ApiCallInfo& callInfo, args::CreateShadersEXT& args) override;

    void Process_vkDestroyShaderEXT(const ApiCallInfo& callInfo, args::DestroyShaderEXT& args) override;

    void Process_vkCreateShaderModule(const ApiCallInfo& callInfo, args::CreateShaderModule& args) override;

    void Process_vkDestroyShaderModule(const ApiCallInfo& callInfo, args::DestroyShaderModule& args) override;

    void Process_vkCreateValidationCacheEXT(const ApiCallInfo& callInfo, args::CreateValidationCacheEXT& args) override;

    void Process_vkDestroyValidationCacheEXT(
        const ApiCallInfo& callInfo, args::DestroyValidationCacheEXT& args
    ) override;

    void Process_vkCreatePipelineCache(const ApiCallInfo& callInfo, args::CreatePipelineCache& args) override;

    void Process_vkDestroyPipelineCache(const ApiCallInfo& callInfo, args::DestroyPipelineCache& args) override;

    void Process_vkCreateGraphicsPipelines(const ApiCallInfo& callInfo, args::CreateGraphicsPipelines& args) override;

    void Process_vkCreateComputePipelines(const ApiCallInfo& callInfo, args::CreateComputePipelines& args) override;

    void Process_vkCreateRayTracingPipelinesNV(
        const ApiCallInfo& callInfo, args::CreateRayTracingPipelinesNV& args
    ) override;

    void Process_vkCreateRayTracingPipelinesKHR(
        const ApiCallInfo& callInfo, args::CreateRayTracingPipelinesKHR& args
    ) override;

    void Process_vkDestroyPipeline(const ApiCallInfo& callInfo, args::DestroyPipeline& args) override;

    void Process_vkCreatePipelineLayout(const ApiCallInfo& callInfo, args::CreatePipelineLayout& args) override;

    void Process_vkDestroyPipelineLayout(const ApiCallInfo& callInfo, args::DestroyPipelineLayout& args) override;

    void Process_vkCreateDescriptorSetLayout(
        const ApiCallInfo& callInfo, args::CreateDescriptorSetLayout& args
    ) override;

    void Process_vkDestroyDescriptorSetLayout(
        const ApiCallInfo& callInfo, args::DestroyDescriptorSetLayout& args
    ) override;

    void Process_vkCreateDescriptorPool(const ApiCallInfo& callInfo, args::CreateDescriptorPool& args) override;

    void Process_vkDestroyDescriptorPool(const ApiCallInfo& callInfo, args::DestroyDescriptorPool& args) override;

    void Process_vkResetDescriptorPool(const ApiCallInfo& callInfo, args::ResetDescriptorPool& args) override;

    void Process_vkAllocateDescriptorSets(const ApiCallInfo& callInfo, args::AllocateDescriptorSets& args) override;

    void Process_vkFreeDescriptorSets(const ApiCallInfo& callInfo, args::FreeDescriptorSets& args) override;

    void Process_vkCreateRenderPass(const ApiCallInfo& callInfo, args::CreateRenderPass& args) override;

    void Process_vkCreateRenderPass2KHR(const ApiCallInfo& callInfo, args::CreateRenderPass2KHR& args) override;

    void Process_vkCreateRenderPass2(const ApiCallInfo& callInfo, args::CreateRenderPass2& args) override;

    void Process_vkDestroyRenderPass(const ApiCallInfo& callInfo, args::DestroyRenderPass& args) override;

    void Process_vkCreateSamplerYcbcrConversion(
        const ApiCallInfo& callInfo, args::CreateSamplerYcbcrConversion& args
    ) override;

    void Process_vkCreateSamplerYcbcrConversionKHR(
        const ApiCallInfo& callInfo, args::CreateSamplerYcbcrConversionKHR& args
    ) override;

    void Process_vkDestroySamplerYcbcrConversion(
        const ApiCallInfo& callInfo, args::DestroySamplerYcbcrConversion& args
    ) override;

    void Process_vkDestroySamplerYcbcrConversionKHR(
        const ApiCallInfo& callInfo, args::DestroySamplerYcbcrConversionKHR& args
    ) override;

    void Process_vkCreatePrivateDataSlot(const ApiCallInfo& callInfo, args::CreatePrivateDataSlot& args) override;

    void Process_vkCreatePrivateDataSlotEXT(const ApiCallInfo& callInfo, args::CreatePrivateDataSlotEXT& args) override;

    void Process_vkDestroyPrivateDataSlot(const ApiCallInfo& callInfo, args::DestroyPrivateDataSlot& args) override;

    void Process_vkDestroyPrivateDataSlotEXT(
        const ApiCallInfo& callInfo, args::DestroyPrivateDataSlotEXT& args
    ) override;

    void Process_vkCreateDescriptorUpdateTemplate(
        const ApiCallInfo& callInfo, args::CreateDescriptorUpdateTemplate& args
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplate(
        const ApiCallInfo& callInfo, args::DestroyDescriptorUpdateTemplate& args
    ) override;

    void Process_vkCreateDescriptorUpdateTemplateKHR(
        const ApiCallInfo& callInfo, args::CreateDescriptorUpdateTemplateKHR& args
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplateKHR(
        const ApiCallInfo& callInfo, args::DestroyDescriptorUpdateTemplateKHR& args
    ) override;

    void Process_vkUpdateDescriptorSets(const ApiCallInfo& callInfo, args::UpdateDescriptorSets& args) override;

    void Process_vkUpdateDescriptorSetWithTemplate(
        const ApiCallInfo& callInfo, args::UpdateDescriptorSetWithTemplate& args
    ) override;

    void Process_vkUpdateDescriptorSetWithTemplateKHR(
        const ApiCallInfo& callInfo, args::UpdateDescriptorSetWithTemplateKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet(const ApiCallInfo& callInfo, args::CmdPushDescriptorSet& args) override;

    virtual void Process_vkCmdPushDescriptorSetKHR(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSet2& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2KHR(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSet2KHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplate& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplateKHR(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplateKHR& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplate2& args
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2KHR(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplate2KHR& args
    ) override;

    void Process_vkCreateBuffer(const ApiCallInfo& callInfo, args::CreateBuffer& args) override;

    void Process_vkDestroyBuffer(const ApiCallInfo& callInfo, args::DestroyBuffer& args) override;

    void Process_vkCreateBufferView(const ApiCallInfo& callInfo, args::CreateBufferView& args) override;

    void Process_vkDestroyBufferView(const ApiCallInfo& callInfo, args::DestroyBufferView& args) override;

    void Process_vkCreateImage(const ApiCallInfo& callInfo, args::CreateImage& args) override;

    void Process_vkDestroyImage(const ApiCallInfo& callInfo, args::DestroyImage& args) override;

    void Process_vkCreateImageView(const ApiCallInfo& callInfo, args::CreateImageView& args) override;

    void Process_vkDestroyImageView(const ApiCallInfo& callInfo, args::DestroyImageView& args) override;

    void Process_vkCreateSampler(const ApiCallInfo& callInfo, args::CreateSampler& args) override;

    void Process_vkDestroySampler(const ApiCallInfo& callInfo, args::DestroySampler& args) override;

    void Process_vkGetRandROutputDisplayEXT(const ApiCallInfo& callInfo, args::GetRandROutputDisplayEXT& args) override;

    void Process_vkGetDrmDisplayEXT(const ApiCallInfo& callInfo, args::GetDrmDisplayEXT& args) override;

    void Process_vkGetWinrtDisplayNV(const ApiCallInfo& callInfo, args::GetWinrtDisplayNV& args) override;

    void Process_vkCreateDisplayModeKHR(const ApiCallInfo& callInfo, args::CreateDisplayModeKHR& args) override;

    void Process_vkCreateSwapchainKHR(const ApiCallInfo& callInfo, args::CreateSwapchainKHR& args) override;

    void Process_vkCreateSharedSwapchainsKHR(
        const ApiCallInfo& callInfo, args::CreateSharedSwapchainsKHR& args
    ) override;

    void Process_vkDestroySwapchainKHR(const ApiCallInfo& callInfo, args::DestroySwapchainKHR& args) override;

    void Process_vkGetSwapchainImagesKHR(const ApiCallInfo& callInfo, args::GetSwapchainImagesKHR& args) override;

    void Process_vkAcquireNextImageKHR(const ApiCallInfo& callInfo, args::AcquireNextImageKHR& args) override;

    void Process_vkAcquireNextImage2KHR(const ApiCallInfo& callInfo, args::AcquireNextImage2KHR& args) override;

    void Process_vkCreateFramebuffer(const ApiCallInfo& callInfo, args::CreateFramebuffer& args) override;

    void Process_vkDestroyFramebuffer(const ApiCallInfo& callInfo, args::DestroyFramebuffer& args) override;

    void Process_vkCmdSetVertexInputEXT(const ApiCallInfo& callInfo, args::CmdSetVertexInputEXT& args) override;

    void Process_vkCmdSetRenderingAttachmentLocations(
        const ApiCallInfo& callInfo, args::CmdSetRenderingAttachmentLocations& args
    ) override;

    void Process_vkCmdSetRenderingAttachmentLocationsKHR(
        const ApiCallInfo& callInfo, args::CmdSetRenderingAttachmentLocationsKHR& args
    ) override;

    void Process_vkCmdSetRenderingInputAttachmentIndices(
        const ApiCallInfo& callInfo, args::CmdSetRenderingInputAttachmentIndices& args
    ) override;

    void Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
        const ApiCallInfo& callInfo, args::CmdSetRenderingInputAttachmentIndicesKHR& args
    ) override;

    void Process_vkCmdSetViewport(const ApiCallInfo& callInfo, args::CmdSetViewport& args) override;

    void Process_vkCmdSetViewportWithCount(const ApiCallInfo& callInfo, args::CmdSetViewportWithCount& args) override;

    void Process_vkCmdSetViewportWithCountEXT(
        const ApiCallInfo& callInfo, args::CmdSetViewportWithCountEXT& args
    ) override;

    void Process_vkCmdSetScissor(const ApiCallInfo& callInfo, args::CmdSetScissor& args) override;

    void Process_vkCmdSetScissorWithCount(const ApiCallInfo& callInfo, args::CmdSetScissorWithCount& args) override;

    void Process_vkCmdSetScissorWithCountEXT(
        const ApiCallInfo& callInfo, args::CmdSetScissorWithCountEXT& args
    ) override;

    void Process_vkCmdSetLineWidth(const ApiCallInfo& callInfo, args::CmdSetLineWidth& args) override;

    void Process_vkCmdSetDepthBias(const ApiCallInfo& callInfo, args::CmdSetDepthBias& args) override;
    void Process_vkCmdSetDepthBias2EXT(const ApiCallInfo& callInfo, args::CmdSetDepthBias2EXT& args) override;

    void Process_vkCmdSetBlendConstants(const ApiCallInfo& callInfo, args::CmdSetBlendConstants& args) override;

    void Process_vkCmdSetDepthBounds(const ApiCallInfo& callInfo, args::CmdSetDepthBounds& args) override;

    void Process_vkCmdSetStencilCompareMask(const ApiCallInfo& callInfo, args::CmdSetStencilCompareMask& args) override;

    void Process_vkCmdSetStencilWriteMask(const ApiCallInfo& callInfo, args::CmdSetStencilWriteMask& args) override;

    void Process_vkCmdSetStencilReference(const ApiCallInfo& callInfo, args::CmdSetStencilReference& args) override;

    void Process_vkCmdSetCullMode(const ApiCallInfo& callInfo, args::CmdSetCullMode& args) override;
    void Process_vkCmdSetCullModeEXT(const ApiCallInfo& callInfo, args::CmdSetCullModeEXT& args) override;

    void Process_vkCmdSetFrontFace(const ApiCallInfo& callInfo, args::CmdSetFrontFace& args) override;
    void Process_vkCmdSetFrontFaceEXT(const ApiCallInfo& callInfo, args::CmdSetFrontFaceEXT& args) override;

    void Process_vkCmdSetPrimitiveTopology(const ApiCallInfo& callInfo, args::CmdSetPrimitiveTopology& args) override;
    void Process_vkCmdSetPrimitiveTopologyEXT(
        const ApiCallInfo& callInfo, args::CmdSetPrimitiveTopologyEXT& args
    ) override;

    void Process_vkCmdSetDepthTestEnable(const ApiCallInfo& callInfo, args::CmdSetDepthTestEnable& args) override;
    void Process_vkCmdSetDepthTestEnableEXT(const ApiCallInfo& callInfo, args::CmdSetDepthTestEnableEXT& args) override;

    void Process_vkCmdSetDepthWriteEnable(const ApiCallInfo& callInfo, args::CmdSetDepthWriteEnable& args) override;
    void Process_vkCmdSetDepthWriteEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetDepthWriteEnableEXT& args
    ) override;

    void Process_vkCmdSetDepthCompareOp(const ApiCallInfo& callInfo, args::CmdSetDepthCompareOp& args) override;
    void Process_vkCmdSetDepthCompareOpEXT(const ApiCallInfo& callInfo, args::CmdSetDepthCompareOpEXT& args) override;

    void Process_vkCmdSetDepthBoundsTestEnable(
        const ApiCallInfo& callInfo, args::CmdSetDepthBoundsTestEnable& args
    ) override;
    void Process_vkCmdSetDepthBoundsTestEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetDepthBoundsTestEnableEXT& args
    ) override;

    void Process_vkCmdSetStencilTestEnable(const ApiCallInfo& callInfo, args::CmdSetStencilTestEnable& args) override;
    void Process_vkCmdSetStencilTestEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetStencilTestEnableEXT& args
    ) override;

    void Process_vkCmdSetStencilOp(const ApiCallInfo& callInfo, args::CmdSetStencilOp& args) override;
    void Process_vkCmdSetStencilOpEXT(const ApiCallInfo& callInfo, args::CmdSetStencilOpEXT& args) override;

    void Process_vkCmdSetRasterizerDiscardEnable(
        const ApiCallInfo& callInfo, args::CmdSetRasterizerDiscardEnable& args
    ) override;
    void Process_vkCmdSetRasterizerDiscardEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetRasterizerDiscardEnableEXT& args
    ) override;

    void Process_vkCmdSetDepthBiasEnable(const ApiCallInfo& callInfo, args::CmdSetDepthBiasEnable& args) override;
    void Process_vkCmdSetDepthBiasEnableEXT(const ApiCallInfo& callInfo, args::CmdSetDepthBiasEnableEXT& args) override;

    void Process_vkCmdSetPrimitiveRestartEnable(
        const ApiCallInfo& callInfo, args::CmdSetPrimitiveRestartEnable& args
    ) override;
    void Process_vkCmdSetPrimitiveRestartEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetPrimitiveRestartEnableEXT& args
    ) override;

    void Process_vkCmdSetPatchControlPointsEXT(
        const ApiCallInfo& callInfo, args::CmdSetPatchControlPointsEXT& args
    ) override;

    void Process_vkCmdSetLogicOpEXT(const ApiCallInfo& callInfo, args::CmdSetLogicOpEXT& args) override;

    void Process_vkCmdSetColorWriteEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetColorWriteEnableEXT& args
    ) override;

    void Process_vkCmdSetLineStipple(const ApiCallInfo& callInfo, args::CmdSetLineStipple& args) override;
    void Process_vkCmdSetLineStippleKHR(const ApiCallInfo& callInfo, args::CmdSetLineStippleKHR& args) override;
    void Process_vkCmdSetLineStippleEXT(const ApiCallInfo& callInfo, args::CmdSetLineStippleEXT& args) override;

    void Process_vkCmdSetFragmentShadingRateKHR(
        const ApiCallInfo& callInfo, args::CmdSetFragmentShadingRateKHR& args
    ) override;
    void Process_vkCmdSetFragmentShadingRateEnumNV(
        const ApiCallInfo& callInfo, args::CmdSetFragmentShadingRateEnumNV& args
    ) override;

    void Process_vkCmdSetViewportWScalingNV(const ApiCallInfo& callInfo, args::CmdSetViewportWScalingNV& args) override;

    void Process_vkCmdSetDiscardRectangleEXT(
        const ApiCallInfo& callInfo, args::CmdSetDiscardRectangleEXT& args
    ) override;
    void Process_vkCmdSetDiscardRectangleEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetDiscardRectangleEnableEXT& args
    ) override;
    void Process_vkCmdSetDiscardRectangleModeEXT(
        const ApiCallInfo& callInfo, args::CmdSetDiscardRectangleModeEXT& args
    ) override;

    void Process_vkCmdSetSampleLocationsEXT(const ApiCallInfo& callInfo, args::CmdSetSampleLocationsEXT& args) override;

    void Process_vkCmdSetViewportShadingRatePaletteNV(
        const ApiCallInfo& callInfo, args::CmdSetViewportShadingRatePaletteNV& args
    ) override;
    void Process_vkCmdSetCoarseSampleOrderNV(
        const ApiCallInfo& callInfo, args::CmdSetCoarseSampleOrderNV& args
    ) override;

    void Process_vkCmdSetExclusiveScissorEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetExclusiveScissorEnableNV& args
    ) override;
    void Process_vkCmdSetExclusiveScissorNV(const ApiCallInfo& callInfo, args::CmdSetExclusiveScissorNV& args) override;

    void Process_vkCmdSetDepthClampEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetDepthClampEnableEXT& args
    ) override;
    void Process_vkCmdSetPolygonModeEXT(const ApiCallInfo& callInfo, args::CmdSetPolygonModeEXT& args) override;
    void Process_vkCmdSetRasterizationSamplesEXT(
        const ApiCallInfo& callInfo, args::CmdSetRasterizationSamplesEXT& args
    ) override;
    void Process_vkCmdSetSampleMaskEXT(const ApiCallInfo& callInfo, args::CmdSetSampleMaskEXT& args) override;
    void Process_vkCmdSetAlphaToCoverageEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetAlphaToCoverageEnableEXT& args
    ) override;
    void Process_vkCmdSetAlphaToOneEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetAlphaToOneEnableEXT& args
    ) override;
    void Process_vkCmdSetLogicOpEnableEXT(const ApiCallInfo& callInfo, args::CmdSetLogicOpEnableEXT& args) override;
    void Process_vkCmdSetColorBlendEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetColorBlendEnableEXT& args
    ) override;
    void Process_vkCmdSetColorBlendEquationEXT(
        const ApiCallInfo& callInfo, args::CmdSetColorBlendEquationEXT& args
    ) override;
    void Process_vkCmdSetColorWriteMaskEXT(const ApiCallInfo& callInfo, args::CmdSetColorWriteMaskEXT& args) override;
    void Process_vkCmdSetTessellationDomainOriginEXT(
        const ApiCallInfo& callInfo, args::CmdSetTessellationDomainOriginEXT& args
    ) override;
    void Process_vkCmdSetRasterizationStreamEXT(
        const ApiCallInfo& callInfo, args::CmdSetRasterizationStreamEXT& args
    ) override;
    void Process_vkCmdSetConservativeRasterizationModeEXT(
        const ApiCallInfo& callInfo, args::CmdSetConservativeRasterizationModeEXT& args
    ) override;
    void Process_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
        const ApiCallInfo& callInfo, args::CmdSetExtraPrimitiveOverestimationSizeEXT& args
    ) override;
    void Process_vkCmdSetDepthClipEnableEXT(const ApiCallInfo& callInfo, args::CmdSetDepthClipEnableEXT& args) override;
    void Process_vkCmdSetSampleLocationsEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetSampleLocationsEnableEXT& args
    ) override;
    void Process_vkCmdSetColorBlendAdvancedEXT(
        const ApiCallInfo& callInfo, args::CmdSetColorBlendAdvancedEXT& args
    ) override;
    void Process_vkCmdSetProvokingVertexModeEXT(
        const ApiCallInfo& callInfo, args::CmdSetProvokingVertexModeEXT& args
    ) override;
    void Process_vkCmdSetLineRasterizationModeEXT(
        const ApiCallInfo& callInfo, args::CmdSetLineRasterizationModeEXT& args
    ) override;
    void Process_vkCmdSetLineStippleEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetLineStippleEnableEXT& args
    ) override;
    void Process_vkCmdSetDepthClipNegativeOneToOneEXT(
        const ApiCallInfo& callInfo, args::CmdSetDepthClipNegativeOneToOneEXT& args
    ) override;
    void Process_vkCmdSetViewportWScalingEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetViewportWScalingEnableNV& args
    ) override;
    void Process_vkCmdSetViewportSwizzleNV(const ApiCallInfo& callInfo, args::CmdSetViewportSwizzleNV& args) override;
    void Process_vkCmdSetCoverageToColorEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageToColorEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageToColorLocationNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageToColorLocationNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationModeNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageModulationModeNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationTableEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageModulationTableEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageModulationTableNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageModulationTableNV& args
    ) override;
    void Process_vkCmdSetShadingRateImageEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetShadingRateImageEnableNV& args
    ) override;
    void Process_vkCmdSetRepresentativeFragmentTestEnableNV(
        const ApiCallInfo& callInfo, args::CmdSetRepresentativeFragmentTestEnableNV& args
    ) override;
    void Process_vkCmdSetCoverageReductionModeNV(
        const ApiCallInfo& callInfo, args::CmdSetCoverageReductionModeNV& args
    ) override;

    void Process_vkCmdSetDepthClampRangeEXT(const ApiCallInfo& callInfo, args::CmdSetDepthClampRangeEXT& args) override;

    void Process_vkCmdSetAttachmentFeedbackLoopEnableEXT(
        const ApiCallInfo& callInfo, args::CmdSetAttachmentFeedbackLoopEnableEXT& args
    ) override;

    void Process_vkCmdSetRayTracingPipelineStackSizeKHR(
        const ApiCallInfo& callInfo, args::CmdSetRayTracingPipelineStackSizeKHR& args
    ) override;

    // Not backed by a VkDynamicState enum, but still unimplemented command-buffer state setters.
    void Process_vkCmdSetComputeOccupancyPriorityNV(
        const ApiCallInfo& callInfo, args::CmdSetComputeOccupancyPriorityNV& args
    ) override;
    void Process_vkCmdSetPrimitiveRestartIndexEXT(
        const ApiCallInfo& callInfo, args::CmdSetPrimitiveRestartIndexEXT& args
    ) override;
    void Process_vkCmdSetDispatchParametersARM(
        const ApiCallInfo& callInfo, args::CmdSetDispatchParametersARM& args
    ) override;

    void Process_vkCreateAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CreateAccelerationStructureKHR& args
    ) override;

    void Process_vkCreateAccelerationStructureNV(
        const ApiCallInfo& callInfo, args::CreateAccelerationStructureNV& args
    ) override;

    void Process_vkDestroyAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::DestroyAccelerationStructureKHR& args
    ) override;

    void Process_vkDestroyAccelerationStructureNV(
        const ApiCallInfo& callInfo, args::DestroyAccelerationStructureNV& args
    ) override;

    void Process_vkBuildAccelerationStructuresKHR(
        const ApiCallInfo& callInfo, args::BuildAccelerationStructuresKHR& args
    ) override;

    void Process_vkCmdBuildAccelerationStructuresKHR(
        const ApiCallInfo& callInfo, args::CmdBuildAccelerationStructuresKHR& args
    ) override;

    void ProcessVulkanBuildAccelerationStructuresCommand(
        format::HandleId device,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos
    ) override;

    void Process_vkCopyAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CopyAccelerationStructureKHR& args
    ) override;

    void Process_vkCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& callInfo, args::CopyAccelerationStructureToMemoryKHR& args
    ) override;

    void Process_vkCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CopyMemoryToAccelerationStructureKHR& args
    ) override;

    void Process_vkCmdCopyAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CmdCopyAccelerationStructureKHR& args
    ) override;

    void Process_vkCmdCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& callInfo, args::CmdCopyAccelerationStructureToMemoryKHR& args
    ) override;

    void ProcessVulkanCopyAccelerationStructuresCommand(
        format::HandleId device, StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
    ) override;

    // Transfer command overrides
    void Process_vkCmdCopyBuffer(const ApiCallInfo& callInfo, args::CmdCopyBuffer& args) override;

    void Process_vkCmdCopyBuffer2(const ApiCallInfo& callInfo, args::CmdCopyBuffer2& args) override;

    void Process_vkCmdCopyBuffer2KHR(const ApiCallInfo& callInfo, args::CmdCopyBuffer2KHR& args) override;

    void Process_vkCmdCopyImage(const ApiCallInfo& callInfo, args::CmdCopyImage& args) override;

    void Process_vkCmdCopyImage2(const ApiCallInfo& callInfo, args::CmdCopyImage2& args) override;

    void Process_vkCmdCopyImage2KHR(const ApiCallInfo& callInfo, args::CmdCopyImage2KHR& args) override;

    void Process_vkCmdCopyBufferToImage(const ApiCallInfo& callInfo, args::CmdCopyBufferToImage& args) override;

    void Process_vkCmdCopyBufferToImage2(const ApiCallInfo& callInfo, args::CmdCopyBufferToImage2& args) override;

    void Process_vkCmdCopyBufferToImage2KHR(const ApiCallInfo& callInfo, args::CmdCopyBufferToImage2KHR& args) override;

    void Process_vkCmdCopyImageToBuffer(const ApiCallInfo& callInfo, args::CmdCopyImageToBuffer& args) override;

    void Process_vkCmdCopyImageToBuffer2(const ApiCallInfo& callInfo, args::CmdCopyImageToBuffer2& args) override;

    void Process_vkCmdCopyImageToBuffer2KHR(const ApiCallInfo& callInfo, args::CmdCopyImageToBuffer2KHR& args) override;

    void Process_vkCmdBlitImage(const ApiCallInfo& callInfo, args::CmdBlitImage& args) override;

    void Process_vkCmdBlitImage2(const ApiCallInfo& callInfo, args::CmdBlitImage2& args) override;

    void Process_vkCmdBlitImage2KHR(const ApiCallInfo& callInfo, args::CmdBlitImage2KHR& args) override;

    void Process_vkCmdResolveImage(const ApiCallInfo& callInfo, args::CmdResolveImage& args) override;

    void Process_vkCmdResolveImage2(const ApiCallInfo& callInfo, args::CmdResolveImage2& args) override;

    void Process_vkCmdResolveImage2KHR(const ApiCallInfo& callInfo, args::CmdResolveImage2KHR& args) override;

    void Process_vkCmdCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CmdCopyMemoryToAccelerationStructureKHR& args
    ) override;

    void Process_vkCreateDeferredOperationKHR(
        const ApiCallInfo& callInfo, args::CreateDeferredOperationKHR& args
    ) override;

    void Process_vkDestroyDeferredOperationKHR(
        const ApiCallInfo& callInfo, args::DestroyDeferredOperationKHR& args
    ) override;

    void Process_vkCreatePipelineBinariesKHR(
        const ApiCallInfo& callInfo, args::CreatePipelineBinariesKHR& args
    ) override;

    void Process_vkDestroyPipelineBinaryKHR(const ApiCallInfo& callInfo, args::DestroyPipelineBinaryKHR& args) override;

    void Process_vkCreateVideoSessionKHR(const ApiCallInfo& callInfo, args::CreateVideoSessionKHR& args) override;

    void Process_vkDestroyVideoSessionKHR(const ApiCallInfo& callInfo, args::DestroyVideoSessionKHR& args) override;

    void Process_vkCreateVideoSessionParametersKHR(
        const ApiCallInfo& callInfo, args::CreateVideoSessionParametersKHR& args
    ) override;

    void Process_vkDestroyVideoSessionParametersKHR(
        const ApiCallInfo& callInfo, args::DestroyVideoSessionParametersKHR& args
    ) override;

    void Process_vkCreateIndirectCommandsLayoutEXT(
        const ApiCallInfo& callInfo, args::CreateIndirectCommandsLayoutEXT& args
    ) override;

    void Process_vkDestroyIndirectCommandsLayoutEXT(
        const ApiCallInfo& callInfo, args::DestroyIndirectCommandsLayoutEXT& args
    ) override;

    void Process_vkCreateMicromapEXT(const ApiCallInfo& callInfo, args::CreateMicromapEXT& args) override;

    void Process_vkDestroyMicromapEXT(const ApiCallInfo& callInfo, args::DestroyMicromapEXT& args) override;

    void Process_vkCreateOpticalFlowSessionNV(
        const ApiCallInfo& callInfo, args::CreateOpticalFlowSessionNV& args
    ) override;

    void Process_vkDestroyOpticalFlowSessionNV(
        const ApiCallInfo& callInfo, args::DestroyOpticalFlowSessionNV& args
    ) override;

    void Process_vkCreateDataGraphPipelinesARM(
        const ApiCallInfo& callInfo, args::CreateDataGraphPipelinesARM& args
    ) override;

    void Process_vkCreateDataGraphPipelineSessionARM(
        const ApiCallInfo& callInfo, args::CreateDataGraphPipelineSessionARM& args
    ) override;

    void Process_vkDestroyDataGraphPipelineSessionARM(
        const ApiCallInfo& callInfo, args::DestroyDataGraphPipelineSessionARM& args
    ) override;

    void Process_vkCmdDispatchDataGraphARM(const ApiCallInfo& callInfo, args::CmdDispatchDataGraphARM& args) override;

    // TODO these were originally overridden in the export json
    // notes about each one in the implementation but need to determine
    // if these are still necessary
    void Process_vkCmdBuildAccelerationStructuresIndirectKHR(
        const ApiCallInfo& callInfo, args::CmdBuildAccelerationStructuresIndirectKHR& args
    ) override;

    void Process_vkCmdPushConstants(const ApiCallInfo& callInfo, args::CmdPushConstants& args) override;

    void Process_vkCmdBindDescriptorSets(const ApiCallInfo& callInfo, args::CmdBindDescriptorSets& args) override;

    void Process_vkCmdBindDescriptorSets2(const ApiCallInfo& callInfo, args::CmdBindDescriptorSets2& args) override;

    void Process_vkCmdBindDescriptorSets2KHR(
        const ApiCallInfo& callInfo, args::CmdBindDescriptorSets2KHR& args
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
        size_t numPreRasterizationShaders,
        const PipelineCreationFeedback& feedback
    );
    GraphicsPipelineFragmentShaderState CopyGraphicsPipelineFragmentShaderState(
        int64_t pipelineId, int64_t libraryPipelineId, size_t numPreRasterizationShaders
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
