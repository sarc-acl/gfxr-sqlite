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
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDebugUtilsObjectNameInfoEXT>* pNameInfo
    ) override;

    void Process_vkSetDebugUtilsObjectTagEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDebugUtilsObjectTagInfoEXT>* pTagInfo
    ) override;

    void Process_vkQueueBeginDebugUtilsLabelEXT(
        const ApiCallInfo& call_info,
        format::HandleId queue,
        StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
    ) override;

    void Process_vkQueueEndDebugUtilsLabelEXT(const ApiCallInfo& call_info, format::HandleId queue) override;

    void Process_vkQueueInsertDebugUtilsLabelEXT(
        const ApiCallInfo& call_info,
        format::HandleId queue,
        StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
    ) override;

    void Process_vkCmdBeginDebugUtilsLabelEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
    ) override;

    void Process_vkCmdEndDebugUtilsLabelEXT(const ApiCallInfo& call_info, format::HandleId commandBuffer) override;

    void Process_vkCmdInsertDebugUtilsLabelEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
    ) override;

    void Process_vkDebugMarkerSetObjectTagEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDebugMarkerObjectTagInfoEXT>* pTagInfo
    ) override;

    void Process_vkDebugMarkerSetObjectNameEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDebugMarkerObjectNameInfoEXT>* pNameInfo
    ) override;

    void Process_vkCmdDebugMarkerBeginEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo
    ) override;

    void Process_vkCmdDebugMarkerEndEXT(const ApiCallInfo& call_info, format::HandleId commandBuffer) override;

    void Process_vkCmdDebugMarkerInsertEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo
    ) override;

    void Process_vkCreateDebugReportCallbackEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId instance,
        StructPointerDecoder<Decoded_VkDebugReportCallbackCreateInfoEXT>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDebugReportCallbackEXT>* pCallback
    ) override;

    void Process_vkDestroyDebugReportCallbackEXT(
        const ApiCallInfo& call_info,
        format::HandleId instance,
        format::HandleId callback,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDebugUtilsMessengerEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId instance,
        StructPointerDecoder<Decoded_VkDebugUtilsMessengerCreateInfoEXT>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDebugUtilsMessengerEXT>* pMessenger
    ) override;

    void Process_vkDestroyDebugUtilsMessengerEXT(
        const ApiCallInfo& call_info,
        format::HandleId instance,
        format::HandleId messenger,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateInstance(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        StructPointerDecoder<Decoded_VkInstanceCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkInstance>* pInstance
    ) override;

    void Process_vkDestroyInstance(
        const ApiCallInfo& call_info,
        format::HandleId instance,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkEnumeratePhysicalDevices(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId instance,
        PointerDecoder<uint32_t>* pPhysicalDeviceCount,
        HandlePointerDecoder<VkPhysicalDevice>* pPhysicalDevices
    ) override;

    void Process_vkCreateDevice(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId physicalDevice,
        StructPointerDecoder<Decoded_VkDeviceCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDevice>* pDevice
    ) override;

    void Process_vkDestroyDevice(
        const ApiCallInfo& call_info,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkGetDeviceQueue(
        const ApiCallInfo& call_info,
        format::HandleId device,
        uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        HandlePointerDecoder<VkQueue>* pQueue
    ) override;

    void ProcessQueue(
        const ApiCallInfo& call_info,
        format::HandleId device,
        uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        VkDeviceQueueCreateFlags flags,
        HandlePointerDecoder<VkQueue>* pQueue
    );

    void Process_vkGetDeviceQueue2(
        const ApiCallInfo& call_info,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDeviceQueueInfo2>* pQueueInfo,
        HandlePointerDecoder<VkQueue>* pQueue
    ) override;

    void Process_vkQueueSubmit(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo>* pSubmits,
        format::HandleId fence
    ) override;

    void ProcessQueueSubmit2Info(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
        format::HandleId fence
    );

    void Process_vkQueueSubmit2(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
        format::HandleId fence
    ) override;

    void Process_vkQueueSubmit2KHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        uint32_t submitCount,
        StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
        format::HandleId fence
    ) override;

    void Process_vkQueuePresentKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId queue,
        StructPointerDecoder<Decoded_VkPresentInfoKHR>* pPresentInfo
    ) override;

    void Process_vkCreateFence(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkFenceCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkFence>* pFence
    ) override;

    void Process_vkDestroyFence(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId fence,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkResetFences(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        uint32_t fenceCount,
        HandlePointerDecoder<VkFence>* pFences
    ) override;

    void Process_vkWaitForFences(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        uint32_t fenceCount,
        HandlePointerDecoder<VkFence>* pFences,
        VkBool32 waitAll,
        uint64_t timeout
    ) override;

    void Process_vkCreateSemaphore(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSemaphore>* pSemaphore
    ) override;

    void Process_vkDestroySemaphore(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId semaphore,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

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

    void Process_vkWaitSemaphores(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
        uint64_t timeout
    ) override;

    void Process_vkSignalSemaphore(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
    ) override;

    void Process_vkWaitSemaphoresKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
        uint64_t timeout
    ) override;

    void Process_vkSignalSemaphoreKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
    ) override;

    void Process_vkCreateEvent(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkEventCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkEvent>* pEvent
    ) override;

    void Process_vkDestroyEvent(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId event,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateQueryPool(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkQueryPoolCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkQueryPool>* pQueryPool
    ) override;

    void Process_vkDestroyQueryPool(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId queryPool,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateShadersEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkShaderCreateInfoEXT>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkShaderEXT>* pShaders
    ) override;

    void Process_vkDestroyShaderEXT(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId shader,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateShaderModule(
        const gfxrecon::decode::ApiCallInfo& call_info,
        VkResult returnValue,
        gfxrecon::format::HandleId device,
        gfxrecon::decode::StructPointerDecoder<gfxrecon::decode::Decoded_VkShaderModuleCreateInfo>* pCreateInfo,
        gfxrecon::decode::StructPointerDecoder<gfxrecon::decode::Decoded_VkAllocationCallbacks>* pAllocator,
        gfxrecon::decode::HandlePointerDecoder<VkShaderModule>* pShaderModule
    ) override;

    void Process_vkDestroyShaderModule(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId shaderModule,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateValidationCacheEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkValidationCacheCreateInfoEXT>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkValidationCacheEXT>* pValidationCache
    ) override;

    void Process_vkDestroyValidationCacheEXT(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId validationCache,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreatePipelineCache(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPipelineCacheCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipelineCache>* pPipelineCache
    ) override;

    void Process_vkDestroyPipelineCache(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId pipelineCache,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateGraphicsPipelines(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId pipelineCache,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkGraphicsPipelineCreateInfo>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipeline>* pPipelines
    ) override;

    void Process_vkCreateComputePipelines(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId pipelineCache,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkComputePipelineCreateInfo>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipeline>* pPipelines
    ) override;

    void Process_vkCreateRayTracingPipelinesNV(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId pipelineCache,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoNV>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipeline>* pPipelines
    ) override;

    void Process_vkCreateRayTracingPipelinesKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        format::HandleId pipelineCache,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoKHR>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipeline>* pPipelines
    ) override;

    void Process_vkDestroyPipeline(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId pipeline,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreatePipelineLayout(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPipelineLayoutCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipelineLayout>* pPipelineLayout
    ) override;

    void Process_vkDestroyPipelineLayout(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId pipelineLayout,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDescriptorSetLayout(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDescriptorSetLayout>* pSetLayout
    ) override;

    void Process_vkDestroyDescriptorSetLayout(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorSetLayout,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDescriptorPool(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorPoolCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDescriptorPool>* pDescriptorPool
    ) override;

    void Process_vkDestroyDescriptorPool(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorPool,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkResetDescriptorPool(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId descriptorPool,
        VkDescriptorPoolResetFlags flags
    ) override;

    void Process_vkAllocateDescriptorSets(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorSetAllocateInfo>* pAllocateInfo,
        HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets
    ) override;

    void Process_vkFreeDescriptorSets(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId descriptorPool,
        uint32_t descriptorSetCount,
        HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets
    ) override;

    void Process_vkCreateRenderPass(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkRenderPassCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkRenderPass>* pRenderPass
    ) override;

    void Process_vkCreateRenderPass2KHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkRenderPass>* pRenderPass
    ) override;

    void Process_vkCreateRenderPass2(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkRenderPass>* pRenderPass
    ) override;

    void Process_vkDestroyRenderPass(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId renderPass,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateSamplerYcbcrConversion(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
    ) override;

    void Process_vkCreateSamplerYcbcrConversionKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
    ) override;

    void Process_vkDestroySamplerYcbcrConversion(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId ycbcrConversion,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkDestroySamplerYcbcrConversionKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId ycbcrConversion,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreatePrivateDataSlot(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
    ) override;

    void Process_vkCreatePrivateDataSlotEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
    ) override;

    void Process_vkDestroyPrivateDataSlot(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId privateDataSlot,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkDestroyPrivateDataSlotEXT(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId privateDataSlot,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDescriptorUpdateTemplate(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplate(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorUpdateTemplate,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDescriptorUpdateTemplateKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
    ) override;

    void Process_vkDestroyDescriptorUpdateTemplateKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorUpdateTemplate,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkUpdateDescriptorSets(
        const ApiCallInfo& call_info,
        format::HandleId device,
        uint32_t descriptorWriteCount,
        StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites,
        uint32_t descriptorCopyCount,
        StructPointerDecoder<Decoded_VkCopyDescriptorSet>* pDescriptorCopies
    ) override;

    void Process_vkUpdateDescriptorSetWithTemplate(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorSet,
        format::HandleId descriptorUpdateTemplate,
        DescriptorUpdateTemplateDecoder* pData
    ) override;

    void Process_vkUpdateDescriptorSetWithTemplateKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId descriptorSet,
        format::HandleId descriptorUpdateTemplate,
        DescriptorUpdateTemplateDecoder* pData
    ) override;

    virtual void Process_vkCmdPushDescriptorSet(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        VkPipelineBindPoint pipelineBindPoint,
        format::HandleId layout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
    ) override;

    virtual void Process_vkCmdPushDescriptorSetKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        VkPipelineBindPoint pipelineBindPoint,
        format::HandleId layout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo
    ) override;

    virtual void Process_vkCmdPushDescriptorSet2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId descriptorUpdateTemplate,
        format::HandleId layout,
        uint32_t set,
        DescriptorUpdateTemplateDecoder* pData
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplateKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId descriptorUpdateTemplate,
        format::HandleId layout,
        uint32_t set,
        DescriptorUpdateTemplateDecoder* pData
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
    ) override;

    virtual void Process_vkCmdPushDescriptorSetWithTemplate2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
    ) override;

    void Process_vkCreateBuffer(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkBufferCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkBuffer>* pBuffer
    ) override;

    void Process_vkDestroyBuffer(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId buffer,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateBufferView(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkBufferViewCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkBufferView>* pView
    ) override;

    void Process_vkDestroyBufferView(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId bufferView,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateImage(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkImageCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkImage>* pImage
    ) override;

    void Process_vkDestroyImage(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId image,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateImageView(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkImageViewCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkImageView>* pView
    ) override;

    void Process_vkDestroyImageView(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId imageView,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateSampler(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSamplerCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSampler>* pSampler
    ) override;

    void Process_vkDestroySampler(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId sampler,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkGetRandROutputDisplayEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId physicalDevice,
        uint64_t dpy,
        size_t rrOutput,
        HandlePointerDecoder<VkDisplayKHR>* pDisplay
    ) override;

    void Process_vkGetDrmDisplayEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId physicalDevice,
        int32_t drmFd,
        uint32_t connectorId,
        HandlePointerDecoder<VkDisplayKHR>* display
    ) override;

    void Process_vkGetWinrtDisplayNV(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId physicalDevice,
        uint32_t deviceRelativeId,
        HandlePointerDecoder<VkDisplayKHR>* pDisplay
    ) override;

    void Process_vkCreateDisplayModeKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId physicalDevice,
        format::HandleId display,
        StructPointerDecoder<Decoded_VkDisplayModeCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDisplayModeKHR>* pMode
    ) override;

    void Process_vkCreateSwapchainKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSwapchainKHR>* pSwapchain
    ) override;

    void Process_vkCreateSharedSwapchainsKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        uint32_t swapchainCount,
        StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkSwapchainKHR>* pSwapchains
    ) override;

    void Process_vkDestroySwapchainKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId swapchain,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkGetSwapchainImagesKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId swapchain,
        PointerDecoder<uint32_t>* pSwapchainImageCount,
        HandlePointerDecoder<VkImage>* pSwapchainImages
    ) override;

    void Process_vkAcquireNextImageKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId swapchain,
        uint64_t timeout,
        format::HandleId semaphore,
        format::HandleId fence,
        PointerDecoder<uint32_t>* pImageIndex
    ) override;

    void Process_vkAcquireNextImage2KHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkAcquireNextImageInfoKHR>* pAcquireInfo,
        PointerDecoder<uint32_t>* pImageIndex
    ) override;

    void Process_vkCreateFramebuffer(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkFramebufferCreateInfo>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkFramebuffer>* pFramebuffer
    ) override;

    void Process_vkDestroyFramebuffer(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId framebuffer,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCmdSetVertexInputEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t vertexBindingDescriptionCount,
        StructPointerDecoder<Decoded_VkVertexInputBindingDescription2EXT>* pVertexBindingDescriptions,
        uint32_t vertexAttributeDescriptionCount,
        StructPointerDecoder<Decoded_VkVertexInputAttributeDescription2EXT>* pVertexAttributeDescriptions
    ) override;

    void Process_vkCmdSetRenderingAttachmentLocations(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfoKHR>* pLocationInfo
    ) override;
    void Process_vkCmdSetRenderingAttachmentLocationsKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfoKHR>* pLocationInfo
    ) override;

    void Process_vkCmdSetRenderingInputAttachmentIndices(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo
    ) override;
    void Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfoKHR>* pInputAttachmentIndexInfo
    ) override;

    void Process_vkCmdSetViewport(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        StructPointerDecoder<Decoded_VkViewport>* pViewports
    ) override;

    void Process_vkCmdSetViewportWithCount(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t viewportCount,
        StructPointerDecoder<Decoded_VkViewport>* pViewports
    ) override;

    void Process_vkCmdSetViewportWithCountEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t viewportCount,
        StructPointerDecoder<Decoded_VkViewport>* pViewports
    ) override;

    void Process_vkCmdSetScissor(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t firstScissor,
        uint32_t scissorCount,
        StructPointerDecoder<Decoded_VkRect2D>* pScissors
    ) override;

    void Process_vkCmdSetScissorWithCount(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t scissorCount,
        StructPointerDecoder<Decoded_VkRect2D>* pScissors
    ) override;

    void Process_vkCmdSetScissorWithCountEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t scissorCount,
        StructPointerDecoder<Decoded_VkRect2D>* pScissors
    ) override;

    void Process_vkCmdSetLineWidth(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, float lineWidth
    ) override;

    void Process_vkCmdSetDepthBias(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        float depthBiasConstantFactor,
        float depthBiasClamp,
        float depthBiasSlopeFactor
    ) override;
    void Process_vkCmdSetDepthBias2EXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkDepthBiasInfoEXT>* pDepthBiasInfo
    ) override;

    void Process_vkCmdSetBlendConstants(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, PointerDecoder<float>* blendConstants
    ) override;

    void Process_vkCmdSetDepthBounds(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, float minDepthBounds, float maxDepthBounds
    ) override;

    void Process_vkCmdSetStencilCompareMask(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask
    ) override;

    void Process_vkCmdSetStencilWriteMask(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask
    ) override;

    void Process_vkCmdSetStencilReference(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference
    ) override;

    void Process_vkCmdSetCullMode(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCullModeFlags cullMode
    ) override;
    void Process_vkCmdSetCullModeEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCullModeFlags cullMode
    ) override;

    void Process_vkCmdSetFrontFace(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkFrontFace frontFace
    ) override;
    void Process_vkCmdSetFrontFaceEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkFrontFace frontFace
    ) override;

    void Process_vkCmdSetPrimitiveTopology(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkPrimitiveTopology primitiveTopology
    ) override;
    void Process_vkCmdSetPrimitiveTopologyEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkPrimitiveTopology primitiveTopology
    ) override;

    void Process_vkCmdSetDepthTestEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthTestEnable
    ) override;
    void Process_vkCmdSetDepthTestEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthTestEnable
    ) override;

    void Process_vkCmdSetDepthWriteEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthWriteEnable
    ) override;
    void Process_vkCmdSetDepthWriteEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthWriteEnable
    ) override;

    void Process_vkCmdSetDepthCompareOp(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCompareOp depthCompareOp
    ) override;
    void Process_vkCmdSetDepthCompareOpEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCompareOp depthCompareOp
    ) override;

    void Process_vkCmdSetDepthBoundsTestEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBoundsTestEnable
    ) override;
    void Process_vkCmdSetDepthBoundsTestEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBoundsTestEnable
    ) override;

    void Process_vkCmdSetStencilTestEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 stencilTestEnable
    ) override;
    void Process_vkCmdSetStencilTestEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 stencilTestEnable
    ) override;

    void Process_vkCmdSetStencilOp(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        VkStencilFaceFlags faceMask,
        VkStencilOp failOp,
        VkStencilOp passOp,
        VkStencilOp depthFailOp,
        VkCompareOp compareOp
    ) override;
    void Process_vkCmdSetStencilOpEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        VkStencilFaceFlags faceMask,
        VkStencilOp failOp,
        VkStencilOp passOp,
        VkStencilOp depthFailOp,
        VkCompareOp compareOp
    ) override;

    void Process_vkCmdSetRasterizerDiscardEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 rasterizerDiscardEnable
    ) override;
    void Process_vkCmdSetRasterizerDiscardEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 rasterizerDiscardEnable
    ) override;

    void Process_vkCmdSetDepthBiasEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBiasEnable
    ) override;
    void Process_vkCmdSetDepthBiasEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBiasEnable
    ) override;

    void Process_vkCmdSetPrimitiveRestartEnable(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 primitiveRestartEnable
    ) override;
    void Process_vkCmdSetPrimitiveRestartEnableEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 primitiveRestartEnable
    ) override;

    void Process_vkCmdSetPatchControlPointsEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 patchControlPoints
    ) override;

    void Process_vkCmdSetLogicOpEXT(
        const ApiCallInfo& call_info, format::HandleId commandBuffer, VkLogicOp logicOp
    ) override;

    void Process_vkCmdSetColorWriteEnableEXT(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t attachmentCount,
        PointerDecoder<VkBool32>* pColorWriteEnables
    ) override;

    void Process_vkCreateAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructure
    ) override;

    void Process_vkCreateAccelerationStructureNV(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoNV>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkAccelerationStructureNV>* pAccelerationStructure
    ) override;

    void Process_vkDestroyAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId accelerationStructure,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkDestroyAccelerationStructureNV(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId accelerationStructure,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkBuildAccelerationStructuresKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
    ) override;

    void Process_vkCmdBuildAccelerationStructuresKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
    ) override;

    void ProcessVulkanBuildAccelerationStructuresCommand(
        format::HandleId device,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos
    ) override;

    void Process_vkCopyAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
    ) override;

    void Process_vkCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo
    ) override;

    void Process_vkCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo
    ) override;

    void Process_vkCmdCopyAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
    ) override;

    void Process_vkCmdCopyAccelerationStructureToMemoryKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo
    ) override;

    void ProcessVulkanCopyAccelerationStructuresCommand(
        format::HandleId device, StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
    ) override;

    // Transfer command overrides
    void Process_vkCmdCopyBuffer(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcBuffer,
        format::HandleId dstBuffer,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferCopy>* pRegions
    ) override;

    void Process_vkCmdCopyBuffer2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
    ) override;

    void Process_vkCmdCopyBuffer2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
    ) override;

    void Process_vkCmdCopyImage(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkImageCopy>* pRegions
    ) override;

    void Process_vkCmdCopyImage2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
    ) override;

    void Process_vkCmdCopyImage2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
    ) override;

    void Process_vkCmdCopyBufferToImage(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcBuffer,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
    ) override;

    void Process_vkCmdCopyBufferToImage2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
    ) override;

    void Process_vkCmdCopyBufferToImage2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
    ) override;

    void Process_vkCmdCopyImageToBuffer(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstBuffer,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
    ) override;

    void Process_vkCmdCopyImageToBuffer2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
    ) override;

    void Process_vkCmdCopyImageToBuffer2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
    ) override;

    void Process_vkCmdBlitImage(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkImageBlit>* pRegions,
        VkFilter filter
    ) override;

    void Process_vkCmdBlitImage2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
    ) override;

    void Process_vkCmdBlitImage2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
    ) override;

    void Process_vkCmdResolveImage(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId srcImage,
        VkImageLayout srcImageLayout,
        format::HandleId dstImage,
        VkImageLayout dstImageLayout,
        uint32_t regionCount,
        StructPointerDecoder<Decoded_VkImageResolve>* pRegions
    ) override;

    void Process_vkCmdResolveImage2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
    ) override;

    void Process_vkCmdResolveImage2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
    ) override;

    void Process_vkCmdCopyMemoryToAccelerationStructureKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo
    ) override;

    void Process_vkCreateDeferredOperationKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDeferredOperationKHR>* pDeferredOperation
    ) override;

    void Process_vkDestroyDeferredOperationKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId operation,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreatePipelineBinariesKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkPipelineBinaryCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        StructPointerDecoder<Decoded_VkPipelineBinaryHandlesInfoKHR>* pBinaries
    ) override;

    void Process_vkDestroyPipelineBinaryKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId pipelineBinary,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateVideoSessionKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkVideoSessionCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkVideoSessionKHR>* pVideoSession
    ) override;

    void Process_vkDestroyVideoSessionKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId videoSession,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateVideoSessionParametersKHR(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkVideoSessionParametersCreateInfoKHR>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkVideoSessionParametersKHR>* pVideoSessionParameters
    ) override;

    void Process_vkDestroyVideoSessionParametersKHR(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId videoSessionParameters,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateIndirectCommandsLayoutEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoEXT>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkIndirectCommandsLayoutEXT>* pIndirectCommandsLayout
    ) override;

    void Process_vkDestroyIndirectCommandsLayoutEXT(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId indirectCommandsLayout,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateMicromapEXT(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkMicromapCreateInfoEXT>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkMicromapEXT>* pMicromap
    ) override;

    void Process_vkDestroyMicromapEXT(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId micromap,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateOpticalFlowSessionNV(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkOpticalFlowSessionCreateInfoNV>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkOpticalFlowSessionNV>* pSession
    ) override;

    void Process_vkDestroyOpticalFlowSessionNV(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId session,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCreateDataGraphPipelinesARM(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId deferredOperation,
        format::HandleId pipelineCache,
        uint32_t createInfoCount,
        StructPointerDecoder<Decoded_VkDataGraphPipelineCreateInfoARM>* pCreateInfos,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkPipeline>* pPipelines
    ) override;

    void Process_vkCreateDataGraphPipelineSessionARM(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        StructPointerDecoder<Decoded_VkDataGraphPipelineSessionCreateInfoARM>* pCreateInfo,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
        HandlePointerDecoder<VkDataGraphPipelineSessionARM>* pSession
    ) override;

    void Process_vkDestroyDataGraphPipelineSessionARM(
        const ApiCallInfo& call_info,
        format::HandleId device,
        format::HandleId session,
        StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
    ) override;

    void Process_vkCmdDispatchDataGraphARM(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId session,
        StructPointerDecoder<Decoded_VkDataGraphPipelineDispatchInfoARM>* pDispatchInfo
    ) override;

    // TODO these were originally overridden in the export json
    // notes about each one in the implementation but need to determine
    // if these are still necessary
    void Process_vkCmdBuildAccelerationStructuresIndirectKHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        uint32_t infoCount,
        StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
        PointerDecoder<VkDeviceAddress>* pIndirectDeviceAddresses,
        PointerDecoder<uint32_t>* pIndirectStrides,
        PointerDecoder<uint32_t*>* ppMaxPrimitiveCounts
    ) override;

    void Process_vkGetPipelineCacheData(
        const ApiCallInfo& call_info,
        VkResult returnValue,
        format::HandleId device,
        format::HandleId pipelineCache,
        PointerDecoder<size_t>* pDataSize,
        PointerDecoder<uint8_t>* pData
    ) override;

    void Process_vkCmdPushConstants(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        format::HandleId layout,
        VkShaderStageFlags stageFlags,
        uint32_t offset,
        uint32_t size,
        PointerDecoder<uint8_t>* pValues
    ) override;

    void Process_vkCmdBindDescriptorSets(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        VkPipelineBindPoint pipelineBindPoint,
        format::HandleId layout,
        uint32_t firstSet,
        uint32_t descriptorSetCount,
        HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets,
        uint32_t dynamicOffsetCount,
        PointerDecoder<uint32_t>* pDynamicOffsets
    ) override;

    void Process_vkCmdBindDescriptorSets2(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
    ) override;

    void Process_vkCmdBindDescriptorSets2KHR(
        const ApiCallInfo& call_info,
        format::HandleId commandBuffer,
        StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
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
