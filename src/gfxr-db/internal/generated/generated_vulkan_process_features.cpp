/********************************************************************************
    Copyright 2024-2026 The Sokatoa Project Authors

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

/*
** This file is generated from the Khronos Vulkan XML API Registry.
**
*/

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

#include "decode/vulkan_sqlite_consumer_ext.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void VulkanSqliteConsumerExt::ProcessVkPhysicalDeviceFeatures(
    VkPhysicalDeviceFeatures* deviceFeatures, std::vector<std::string_view>& enabledFeatureNames
)
{
    // clang-format off
    if(deviceFeatures->robustBufferAccess) { enabledFeatureNames.emplace_back("robustBufferAccess"); }
    if(deviceFeatures->fullDrawIndexUint32) { enabledFeatureNames.emplace_back("fullDrawIndexUint32"); }
    if(deviceFeatures->imageCubeArray) { enabledFeatureNames.emplace_back("imageCubeArray"); }
    if(deviceFeatures->independentBlend) { enabledFeatureNames.emplace_back("independentBlend"); }
    if(deviceFeatures->geometryShader) { enabledFeatureNames.emplace_back("geometryShader"); }
    if(deviceFeatures->tessellationShader) { enabledFeatureNames.emplace_back("tessellationShader"); }
    if(deviceFeatures->sampleRateShading) { enabledFeatureNames.emplace_back("sampleRateShading"); }
    if(deviceFeatures->dualSrcBlend) { enabledFeatureNames.emplace_back("dualSrcBlend"); }
    if(deviceFeatures->logicOp) { enabledFeatureNames.emplace_back("logicOp"); }
    if(deviceFeatures->multiDrawIndirect) { enabledFeatureNames.emplace_back("multiDrawIndirect"); }
    if(deviceFeatures->drawIndirectFirstInstance) { enabledFeatureNames.emplace_back("drawIndirectFirstInstance"); }
    if(deviceFeatures->depthClamp) { enabledFeatureNames.emplace_back("depthClamp"); }
    if(deviceFeatures->depthBiasClamp) { enabledFeatureNames.emplace_back("depthBiasClamp"); }
    if(deviceFeatures->fillModeNonSolid) { enabledFeatureNames.emplace_back("fillModeNonSolid"); }
    if(deviceFeatures->depthBounds) { enabledFeatureNames.emplace_back("depthBounds"); }
    if(deviceFeatures->wideLines) { enabledFeatureNames.emplace_back("wideLines"); }
    if(deviceFeatures->largePoints) { enabledFeatureNames.emplace_back("largePoints"); }
    if(deviceFeatures->alphaToOne) { enabledFeatureNames.emplace_back("alphaToOne"); }
    if(deviceFeatures->multiViewport) { enabledFeatureNames.emplace_back("multiViewport"); }
    if(deviceFeatures->samplerAnisotropy) { enabledFeatureNames.emplace_back("samplerAnisotropy"); }
    if(deviceFeatures->textureCompressionETC2) { enabledFeatureNames.emplace_back("textureCompressionETC2"); }
    if(deviceFeatures->textureCompressionASTC_LDR) { enabledFeatureNames.emplace_back("textureCompressionASTC_LDR"); }
    if(deviceFeatures->textureCompressionBC) { enabledFeatureNames.emplace_back("textureCompressionBC"); }
    if(deviceFeatures->occlusionQueryPrecise) { enabledFeatureNames.emplace_back("occlusionQueryPrecise"); }
    if(deviceFeatures->pipelineStatisticsQuery) { enabledFeatureNames.emplace_back("pipelineStatisticsQuery"); }
    if(deviceFeatures->vertexPipelineStoresAndAtomics) { enabledFeatureNames.emplace_back("vertexPipelineStoresAndAtomics"); }
    if(deviceFeatures->fragmentStoresAndAtomics) { enabledFeatureNames.emplace_back("fragmentStoresAndAtomics"); }
    if(deviceFeatures->shaderTessellationAndGeometryPointSize) { enabledFeatureNames.emplace_back("shaderTessellationAndGeometryPointSize"); }
    if(deviceFeatures->shaderImageGatherExtended) { enabledFeatureNames.emplace_back("shaderImageGatherExtended"); }
    if(deviceFeatures->shaderStorageImageExtendedFormats) { enabledFeatureNames.emplace_back("shaderStorageImageExtendedFormats"); }
    if(deviceFeatures->shaderStorageImageMultisample) { enabledFeatureNames.emplace_back("shaderStorageImageMultisample"); }
    if(deviceFeatures->shaderStorageImageReadWithoutFormat) { enabledFeatureNames.emplace_back("shaderStorageImageReadWithoutFormat"); }
    if(deviceFeatures->shaderStorageImageWriteWithoutFormat) { enabledFeatureNames.emplace_back("shaderStorageImageWriteWithoutFormat"); }
    if(deviceFeatures->shaderUniformBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderUniformBufferArrayDynamicIndexing"); }
    if(deviceFeatures->shaderSampledImageArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderSampledImageArrayDynamicIndexing"); }
    if(deviceFeatures->shaderStorageBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageBufferArrayDynamicIndexing"); }
    if(deviceFeatures->shaderStorageImageArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageImageArrayDynamicIndexing"); }
    if(deviceFeatures->shaderClipDistance) { enabledFeatureNames.emplace_back("shaderClipDistance"); }
    if(deviceFeatures->shaderCullDistance) { enabledFeatureNames.emplace_back("shaderCullDistance"); }
    if(deviceFeatures->shaderFloat64) { enabledFeatureNames.emplace_back("shaderFloat64"); }
    if(deviceFeatures->shaderInt64) { enabledFeatureNames.emplace_back("shaderInt64"); }
    if(deviceFeatures->shaderInt16) { enabledFeatureNames.emplace_back("shaderInt16"); }
    if(deviceFeatures->shaderResourceResidency) { enabledFeatureNames.emplace_back("shaderResourceResidency"); }
    if(deviceFeatures->shaderResourceMinLod) { enabledFeatureNames.emplace_back("shaderResourceMinLod"); }
    if(deviceFeatures->sparseBinding) { enabledFeatureNames.emplace_back("sparseBinding"); }
    if(deviceFeatures->sparseResidencyBuffer) { enabledFeatureNames.emplace_back("sparseResidencyBuffer"); }
    if(deviceFeatures->sparseResidencyImage2D) { enabledFeatureNames.emplace_back("sparseResidencyImage2D"); }
    if(deviceFeatures->sparseResidencyImage3D) { enabledFeatureNames.emplace_back("sparseResidencyImage3D"); }
    if(deviceFeatures->sparseResidency2Samples) { enabledFeatureNames.emplace_back("sparseResidency2Samples"); }
    if(deviceFeatures->sparseResidency4Samples) { enabledFeatureNames.emplace_back("sparseResidency4Samples"); }
    if(deviceFeatures->sparseResidency8Samples) { enabledFeatureNames.emplace_back("sparseResidency8Samples"); }
    if(deviceFeatures->sparseResidency16Samples) { enabledFeatureNames.emplace_back("sparseResidency16Samples"); }
    if(deviceFeatures->sparseResidencyAliased) { enabledFeatureNames.emplace_back("sparseResidencyAliased"); }
    if(deviceFeatures->variableMultisampleRate) { enabledFeatureNames.emplace_back("variableMultisampleRate"); }
    if(deviceFeatures->inheritedQueries) { enabledFeatureNames.emplace_back("inheritedQueries"); }
    // clang-format on
}

void VulkanSqliteConsumerExt::ProcessVkDeviceCreateInfoPNext(
    PNextNode* pNext, std::vector<std::string_view>& enabledFeatureNames
)
{
    auto* pnext = pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        switch(*header->sType)
        {
            case gfxrecon::util::GetSType<VkPhysicalDeviceFeatures2>():
            {
                const auto* pPhysicalDeviceFeatures2 =
                    reinterpret_cast<const Decoded_VkPhysicalDeviceFeatures2*>(header);
                ProcessVkPhysicalDeviceFeatures(pPhysicalDeviceFeatures2->features->decoded_value, enabledFeatureNames);
                pnext = header->pNext;
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceProtectedMemoryFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceProtectedMemoryFeatures*>(header);
                if(pFeatures->protectedMemory) { enabledFeatureNames.emplace_back("protectedMemory"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevice16BitStorageFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevice16BitStorageFeatures*>(header);
                if(pFeatures->storageBuffer16BitAccess) { enabledFeatureNames.emplace_back("storageBuffer16BitAccess"); }
                if(pFeatures->uniformAndStorageBuffer16BitAccess) { enabledFeatureNames.emplace_back("uniformAndStorageBuffer16BitAccess"); }
                if(pFeatures->storagePushConstant16) { enabledFeatureNames.emplace_back("storagePushConstant16"); }
                if(pFeatures->storageInputOutput16) { enabledFeatureNames.emplace_back("storageInputOutput16"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVariablePointersFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVariablePointersFeatures*>(header);
                if(pFeatures->variablePointersStorageBuffer) { enabledFeatureNames.emplace_back("variablePointersStorageBuffer"); }
                if(pFeatures->variablePointers) { enabledFeatureNames.emplace_back("variablePointers"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSamplerYcbcrConversionFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSamplerYcbcrConversionFeatures*>(header);
                if(pFeatures->samplerYcbcrConversion) { enabledFeatureNames.emplace_back("samplerYcbcrConversion"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMultiviewFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMultiviewFeatures*>(header);
                if(pFeatures->multiview) { enabledFeatureNames.emplace_back("multiview"); }
                if(pFeatures->multiviewGeometryShader) { enabledFeatureNames.emplace_back("multiviewGeometryShader"); }
                if(pFeatures->multiviewTessellationShader) { enabledFeatureNames.emplace_back("multiviewTessellationShader"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderDrawParametersFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderDrawParametersFeatures*>(header);
                if(pFeatures->shaderDrawParameters) { enabledFeatureNames.emplace_back("shaderDrawParameters"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVulkan11Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVulkan11Features*>(header);
                if(pFeatures->storageBuffer16BitAccess) { enabledFeatureNames.emplace_back("storageBuffer16BitAccess"); }
                if(pFeatures->uniformAndStorageBuffer16BitAccess) { enabledFeatureNames.emplace_back("uniformAndStorageBuffer16BitAccess"); }
                if(pFeatures->storagePushConstant16) { enabledFeatureNames.emplace_back("storagePushConstant16"); }
                if(pFeatures->storageInputOutput16) { enabledFeatureNames.emplace_back("storageInputOutput16"); }
                if(pFeatures->multiview) { enabledFeatureNames.emplace_back("multiview"); }
                if(pFeatures->multiviewGeometryShader) { enabledFeatureNames.emplace_back("multiviewGeometryShader"); }
                if(pFeatures->multiviewTessellationShader) { enabledFeatureNames.emplace_back("multiviewTessellationShader"); }
                if(pFeatures->variablePointersStorageBuffer) { enabledFeatureNames.emplace_back("variablePointersStorageBuffer"); }
                if(pFeatures->variablePointers) { enabledFeatureNames.emplace_back("variablePointers"); }
                if(pFeatures->protectedMemory) { enabledFeatureNames.emplace_back("protectedMemory"); }
                if(pFeatures->samplerYcbcrConversion) { enabledFeatureNames.emplace_back("samplerYcbcrConversion"); }
                if(pFeatures->shaderDrawParameters) { enabledFeatureNames.emplace_back("shaderDrawParameters"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVulkan12Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVulkan12Features*>(header);
                if(pFeatures->samplerMirrorClampToEdge) { enabledFeatureNames.emplace_back("samplerMirrorClampToEdge"); }
                if(pFeatures->drawIndirectCount) { enabledFeatureNames.emplace_back("drawIndirectCount"); }
                if(pFeatures->storageBuffer8BitAccess) { enabledFeatureNames.emplace_back("storageBuffer8BitAccess"); }
                if(pFeatures->uniformAndStorageBuffer8BitAccess) { enabledFeatureNames.emplace_back("uniformAndStorageBuffer8BitAccess"); }
                if(pFeatures->storagePushConstant8) { enabledFeatureNames.emplace_back("storagePushConstant8"); }
                if(pFeatures->shaderBufferInt64Atomics) { enabledFeatureNames.emplace_back("shaderBufferInt64Atomics"); }
                if(pFeatures->shaderSharedInt64Atomics) { enabledFeatureNames.emplace_back("shaderSharedInt64Atomics"); }
                if(pFeatures->shaderFloat16) { enabledFeatureNames.emplace_back("shaderFloat16"); }
                if(pFeatures->shaderInt8) { enabledFeatureNames.emplace_back("shaderInt8"); }
                if(pFeatures->descriptorIndexing) { enabledFeatureNames.emplace_back("descriptorIndexing"); }
                if(pFeatures->shaderInputAttachmentArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderInputAttachmentArrayDynamicIndexing"); }
                if(pFeatures->shaderUniformTexelBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderUniformTexelBufferArrayDynamicIndexing"); }
                if(pFeatures->shaderStorageTexelBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageTexelBufferArrayDynamicIndexing"); }
                if(pFeatures->shaderUniformBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderUniformBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderSampledImageArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderSampledImageArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageImageArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageImageArrayNonUniformIndexing"); }
                if(pFeatures->shaderInputAttachmentArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderInputAttachmentArrayNonUniformIndexing"); }
                if(pFeatures->shaderUniformTexelBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderUniformTexelBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageTexelBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageTexelBufferArrayNonUniformIndexing"); }
                if(pFeatures->descriptorBindingUniformBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingUniformBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingSampledImageUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingSampledImageUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageImageUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageImageUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingUniformTexelBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingUniformTexelBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageTexelBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageTexelBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingUpdateUnusedWhilePending) { enabledFeatureNames.emplace_back("descriptorBindingUpdateUnusedWhilePending"); }
                if(pFeatures->descriptorBindingPartiallyBound) { enabledFeatureNames.emplace_back("descriptorBindingPartiallyBound"); }
                if(pFeatures->descriptorBindingVariableDescriptorCount) { enabledFeatureNames.emplace_back("descriptorBindingVariableDescriptorCount"); }
                if(pFeatures->runtimeDescriptorArray) { enabledFeatureNames.emplace_back("runtimeDescriptorArray"); }
                if(pFeatures->samplerFilterMinmax) { enabledFeatureNames.emplace_back("samplerFilterMinmax"); }
                if(pFeatures->scalarBlockLayout) { enabledFeatureNames.emplace_back("scalarBlockLayout"); }
                if(pFeatures->imagelessFramebuffer) { enabledFeatureNames.emplace_back("imagelessFramebuffer"); }
                if(pFeatures->uniformBufferStandardLayout) { enabledFeatureNames.emplace_back("uniformBufferStandardLayout"); }
                if(pFeatures->shaderSubgroupExtendedTypes) { enabledFeatureNames.emplace_back("shaderSubgroupExtendedTypes"); }
                if(pFeatures->separateDepthStencilLayouts) { enabledFeatureNames.emplace_back("separateDepthStencilLayouts"); }
                if(pFeatures->hostQueryReset) { enabledFeatureNames.emplace_back("hostQueryReset"); }
                if(pFeatures->timelineSemaphore) { enabledFeatureNames.emplace_back("timelineSemaphore"); }
                if(pFeatures->bufferDeviceAddress) { enabledFeatureNames.emplace_back("bufferDeviceAddress"); }
                if(pFeatures->bufferDeviceAddressCaptureReplay) { enabledFeatureNames.emplace_back("bufferDeviceAddressCaptureReplay"); }
                if(pFeatures->bufferDeviceAddressMultiDevice) { enabledFeatureNames.emplace_back("bufferDeviceAddressMultiDevice"); }
                if(pFeatures->vulkanMemoryModel) { enabledFeatureNames.emplace_back("vulkanMemoryModel"); }
                if(pFeatures->vulkanMemoryModelDeviceScope) { enabledFeatureNames.emplace_back("vulkanMemoryModelDeviceScope"); }
                if(pFeatures->vulkanMemoryModelAvailabilityVisibilityChains) { enabledFeatureNames.emplace_back("vulkanMemoryModelAvailabilityVisibilityChains"); }
                if(pFeatures->shaderOutputViewportIndex) { enabledFeatureNames.emplace_back("shaderOutputViewportIndex"); }
                if(pFeatures->shaderOutputLayer) { enabledFeatureNames.emplace_back("shaderOutputLayer"); }
                if(pFeatures->subgroupBroadcastDynamicId) { enabledFeatureNames.emplace_back("subgroupBroadcastDynamicId"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVulkanMemoryModelFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVulkanMemoryModelFeatures*>(header);
                if(pFeatures->vulkanMemoryModel) { enabledFeatureNames.emplace_back("vulkanMemoryModel"); }
                if(pFeatures->vulkanMemoryModelDeviceScope) { enabledFeatureNames.emplace_back("vulkanMemoryModelDeviceScope"); }
                if(pFeatures->vulkanMemoryModelAvailabilityVisibilityChains) { enabledFeatureNames.emplace_back("vulkanMemoryModelAvailabilityVisibilityChains"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceHostQueryResetFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceHostQueryResetFeatures*>(header);
                if(pFeatures->hostQueryReset) { enabledFeatureNames.emplace_back("hostQueryReset"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTimelineSemaphoreFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTimelineSemaphoreFeatures*>(header);
                if(pFeatures->timelineSemaphore) { enabledFeatureNames.emplace_back("timelineSemaphore"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceBufferDeviceAddressFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceBufferDeviceAddressFeatures*>(header);
                if(pFeatures->bufferDeviceAddress) { enabledFeatureNames.emplace_back("bufferDeviceAddress"); }
                if(pFeatures->bufferDeviceAddressCaptureReplay) { enabledFeatureNames.emplace_back("bufferDeviceAddressCaptureReplay"); }
                if(pFeatures->bufferDeviceAddressMultiDevice) { enabledFeatureNames.emplace_back("bufferDeviceAddressMultiDevice"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevice8BitStorageFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevice8BitStorageFeatures*>(header);
                if(pFeatures->storageBuffer8BitAccess) { enabledFeatureNames.emplace_back("storageBuffer8BitAccess"); }
                if(pFeatures->uniformAndStorageBuffer8BitAccess) { enabledFeatureNames.emplace_back("uniformAndStorageBuffer8BitAccess"); }
                if(pFeatures->storagePushConstant8) { enabledFeatureNames.emplace_back("storagePushConstant8"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderAtomicInt64Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderAtomicInt64Features*>(header);
                if(pFeatures->shaderBufferInt64Atomics) { enabledFeatureNames.emplace_back("shaderBufferInt64Atomics"); }
                if(pFeatures->shaderSharedInt64Atomics) { enabledFeatureNames.emplace_back("shaderSharedInt64Atomics"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderFloat16Int8Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderFloat16Int8Features*>(header);
                if(pFeatures->shaderFloat16) { enabledFeatureNames.emplace_back("shaderFloat16"); }
                if(pFeatures->shaderInt8) { enabledFeatureNames.emplace_back("shaderInt8"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDescriptorIndexingFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDescriptorIndexingFeatures*>(header);
                if(pFeatures->shaderInputAttachmentArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderInputAttachmentArrayDynamicIndexing"); }
                if(pFeatures->shaderUniformTexelBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderUniformTexelBufferArrayDynamicIndexing"); }
                if(pFeatures->shaderStorageTexelBufferArrayDynamicIndexing) { enabledFeatureNames.emplace_back("shaderStorageTexelBufferArrayDynamicIndexing"); }
                if(pFeatures->shaderUniformBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderUniformBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderSampledImageArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderSampledImageArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageImageArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageImageArrayNonUniformIndexing"); }
                if(pFeatures->shaderInputAttachmentArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderInputAttachmentArrayNonUniformIndexing"); }
                if(pFeatures->shaderUniformTexelBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderUniformTexelBufferArrayNonUniformIndexing"); }
                if(pFeatures->shaderStorageTexelBufferArrayNonUniformIndexing) { enabledFeatureNames.emplace_back("shaderStorageTexelBufferArrayNonUniformIndexing"); }
                if(pFeatures->descriptorBindingUniformBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingUniformBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingSampledImageUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingSampledImageUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageImageUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageImageUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingUniformTexelBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingUniformTexelBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingStorageTexelBufferUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingStorageTexelBufferUpdateAfterBind"); }
                if(pFeatures->descriptorBindingUpdateUnusedWhilePending) { enabledFeatureNames.emplace_back("descriptorBindingUpdateUnusedWhilePending"); }
                if(pFeatures->descriptorBindingPartiallyBound) { enabledFeatureNames.emplace_back("descriptorBindingPartiallyBound"); }
                if(pFeatures->descriptorBindingVariableDescriptorCount) { enabledFeatureNames.emplace_back("descriptorBindingVariableDescriptorCount"); }
                if(pFeatures->runtimeDescriptorArray) { enabledFeatureNames.emplace_back("runtimeDescriptorArray"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceScalarBlockLayoutFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceScalarBlockLayoutFeatures*>(header);
                if(pFeatures->scalarBlockLayout) { enabledFeatureNames.emplace_back("scalarBlockLayout"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceUniformBufferStandardLayoutFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceUniformBufferStandardLayoutFeatures*>(header);
                if(pFeatures->uniformBufferStandardLayout) { enabledFeatureNames.emplace_back("uniformBufferStandardLayout"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures*>(header);
                if(pFeatures->shaderSubgroupExtendedTypes) { enabledFeatureNames.emplace_back("shaderSubgroupExtendedTypes"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImagelessFramebufferFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImagelessFramebufferFeatures*>(header);
                if(pFeatures->imagelessFramebuffer) { enabledFeatureNames.emplace_back("imagelessFramebuffer"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures*>(header);
                if(pFeatures->separateDepthStencilLayouts) { enabledFeatureNames.emplace_back("separateDepthStencilLayouts"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVulkan13Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVulkan13Features*>(header);
                if(pFeatures->robustImageAccess) { enabledFeatureNames.emplace_back("robustImageAccess"); }
                if(pFeatures->inlineUniformBlock) { enabledFeatureNames.emplace_back("inlineUniformBlock"); }
                if(pFeatures->descriptorBindingInlineUniformBlockUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingInlineUniformBlockUpdateAfterBind"); }
                if(pFeatures->pipelineCreationCacheControl) { enabledFeatureNames.emplace_back("pipelineCreationCacheControl"); }
                if(pFeatures->privateData) { enabledFeatureNames.emplace_back("privateData"); }
                if(pFeatures->shaderDemoteToHelperInvocation) { enabledFeatureNames.emplace_back("shaderDemoteToHelperInvocation"); }
                if(pFeatures->shaderTerminateInvocation) { enabledFeatureNames.emplace_back("shaderTerminateInvocation"); }
                if(pFeatures->subgroupSizeControl) { enabledFeatureNames.emplace_back("subgroupSizeControl"); }
                if(pFeatures->computeFullSubgroups) { enabledFeatureNames.emplace_back("computeFullSubgroups"); }
                if(pFeatures->synchronization2) { enabledFeatureNames.emplace_back("synchronization2"); }
                if(pFeatures->textureCompressionASTC_HDR) { enabledFeatureNames.emplace_back("textureCompressionASTC_HDR"); }
                if(pFeatures->shaderZeroInitializeWorkgroupMemory) { enabledFeatureNames.emplace_back("shaderZeroInitializeWorkgroupMemory"); }
                if(pFeatures->dynamicRendering) { enabledFeatureNames.emplace_back("dynamicRendering"); }
                if(pFeatures->shaderIntegerDotProduct) { enabledFeatureNames.emplace_back("shaderIntegerDotProduct"); }
                if(pFeatures->maintenance4) { enabledFeatureNames.emplace_back("maintenance4"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePrivateDataFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePrivateDataFeatures*>(header);
                if(pFeatures->privateData) { enabledFeatureNames.emplace_back("privateData"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSynchronization2Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSynchronization2Features*>(header);
                if(pFeatures->synchronization2) { enabledFeatureNames.emplace_back("synchronization2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTextureCompressionASTCHDRFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTextureCompressionASTCHDRFeatures*>(header);
                if(pFeatures->textureCompressionASTC_HDR) { enabledFeatureNames.emplace_back("textureCompressionASTC_HDR"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance4Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance4Features*>(header);
                if(pFeatures->maintenance4) { enabledFeatureNames.emplace_back("maintenance4"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderTerminateInvocationFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderTerminateInvocationFeatures*>(header);
                if(pFeatures->shaderTerminateInvocation) { enabledFeatureNames.emplace_back("shaderTerminateInvocation"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderDemoteToHelperInvocationFeatures*>(header);
                if(pFeatures->shaderDemoteToHelperInvocation) { enabledFeatureNames.emplace_back("shaderDemoteToHelperInvocation"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineCreationCacheControlFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineCreationCacheControlFeatures*>(header);
                if(pFeatures->pipelineCreationCacheControl) { enabledFeatureNames.emplace_back("pipelineCreationCacheControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeatures*>(header);
                if(pFeatures->shaderZeroInitializeWorkgroupMemory) { enabledFeatureNames.emplace_back("shaderZeroInitializeWorkgroupMemory"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageRobustnessFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageRobustnessFeatures*>(header);
                if(pFeatures->robustImageAccess) { enabledFeatureNames.emplace_back("robustImageAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSubgroupSizeControlFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSubgroupSizeControlFeatures*>(header);
                if(pFeatures->subgroupSizeControl) { enabledFeatureNames.emplace_back("subgroupSizeControl"); }
                if(pFeatures->computeFullSubgroups) { enabledFeatureNames.emplace_back("computeFullSubgroups"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceInlineUniformBlockFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceInlineUniformBlockFeatures*>(header);
                if(pFeatures->inlineUniformBlock) { enabledFeatureNames.emplace_back("inlineUniformBlock"); }
                if(pFeatures->descriptorBindingInlineUniformBlockUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingInlineUniformBlockUpdateAfterBind"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderIntegerDotProductFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderIntegerDotProductFeatures*>(header);
                if(pFeatures->shaderIntegerDotProduct) { enabledFeatureNames.emplace_back("shaderIntegerDotProduct"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDynamicRenderingFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDynamicRenderingFeatures*>(header);
                if(pFeatures->dynamicRendering) { enabledFeatureNames.emplace_back("dynamicRendering"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVulkan14Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVulkan14Features*>(header);
                if(pFeatures->globalPriorityQuery) { enabledFeatureNames.emplace_back("globalPriorityQuery"); }
                if(pFeatures->shaderSubgroupRotate) { enabledFeatureNames.emplace_back("shaderSubgroupRotate"); }
                if(pFeatures->shaderSubgroupRotateClustered) { enabledFeatureNames.emplace_back("shaderSubgroupRotateClustered"); }
                if(pFeatures->shaderFloatControls2) { enabledFeatureNames.emplace_back("shaderFloatControls2"); }
                if(pFeatures->shaderExpectAssume) { enabledFeatureNames.emplace_back("shaderExpectAssume"); }
                if(pFeatures->rectangularLines) { enabledFeatureNames.emplace_back("rectangularLines"); }
                if(pFeatures->bresenhamLines) { enabledFeatureNames.emplace_back("bresenhamLines"); }
                if(pFeatures->smoothLines) { enabledFeatureNames.emplace_back("smoothLines"); }
                if(pFeatures->stippledRectangularLines) { enabledFeatureNames.emplace_back("stippledRectangularLines"); }
                if(pFeatures->stippledBresenhamLines) { enabledFeatureNames.emplace_back("stippledBresenhamLines"); }
                if(pFeatures->stippledSmoothLines) { enabledFeatureNames.emplace_back("stippledSmoothLines"); }
                if(pFeatures->vertexAttributeInstanceRateDivisor) { enabledFeatureNames.emplace_back("vertexAttributeInstanceRateDivisor"); }
                if(pFeatures->vertexAttributeInstanceRateZeroDivisor) { enabledFeatureNames.emplace_back("vertexAttributeInstanceRateZeroDivisor"); }
                if(pFeatures->indexTypeUint8) { enabledFeatureNames.emplace_back("indexTypeUint8"); }
                if(pFeatures->dynamicRenderingLocalRead) { enabledFeatureNames.emplace_back("dynamicRenderingLocalRead"); }
                if(pFeatures->maintenance5) { enabledFeatureNames.emplace_back("maintenance5"); }
                if(pFeatures->maintenance6) { enabledFeatureNames.emplace_back("maintenance6"); }
                if(pFeatures->pipelineProtectedAccess) { enabledFeatureNames.emplace_back("pipelineProtectedAccess"); }
                if(pFeatures->pipelineRobustness) { enabledFeatureNames.emplace_back("pipelineRobustness"); }
                if(pFeatures->hostImageCopy) { enabledFeatureNames.emplace_back("hostImageCopy"); }
                if(pFeatures->pushDescriptor) { enabledFeatureNames.emplace_back("pushDescriptor"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceGlobalPriorityQueryFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceGlobalPriorityQueryFeatures*>(header);
                if(pFeatures->globalPriorityQuery) { enabledFeatureNames.emplace_back("globalPriorityQuery"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceIndexTypeUint8Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceIndexTypeUint8Features*>(header);
                if(pFeatures->indexTypeUint8) { enabledFeatureNames.emplace_back("indexTypeUint8"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance5Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance5Features*>(header);
                if(pFeatures->maintenance5) { enabledFeatureNames.emplace_back("maintenance5"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance6Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance6Features*>(header);
                if(pFeatures->maintenance6) { enabledFeatureNames.emplace_back("maintenance6"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceHostImageCopyFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceHostImageCopyFeatures*>(header);
                if(pFeatures->hostImageCopy) { enabledFeatureNames.emplace_back("hostImageCopy"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderSubgroupRotateFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderSubgroupRotateFeatures*>(header);
                if(pFeatures->shaderSubgroupRotate) { enabledFeatureNames.emplace_back("shaderSubgroupRotate"); }
                if(pFeatures->shaderSubgroupRotateClustered) { enabledFeatureNames.emplace_back("shaderSubgroupRotateClustered"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderFloatControls2Features>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderFloatControls2Features*>(header);
                if(pFeatures->shaderFloatControls2) { enabledFeatureNames.emplace_back("shaderFloatControls2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderExpectAssumeFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderExpectAssumeFeatures*>(header);
                if(pFeatures->shaderExpectAssume) { enabledFeatureNames.emplace_back("shaderExpectAssume"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineProtectedAccessFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineProtectedAccessFeatures*>(header);
                if(pFeatures->pipelineProtectedAccess) { enabledFeatureNames.emplace_back("pipelineProtectedAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineRobustnessFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineRobustnessFeatures*>(header);
                if(pFeatures->pipelineRobustness) { enabledFeatureNames.emplace_back("pipelineRobustness"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceLineRasterizationFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceLineRasterizationFeatures*>(header);
                if(pFeatures->rectangularLines) { enabledFeatureNames.emplace_back("rectangularLines"); }
                if(pFeatures->bresenhamLines) { enabledFeatureNames.emplace_back("bresenhamLines"); }
                if(pFeatures->smoothLines) { enabledFeatureNames.emplace_back("smoothLines"); }
                if(pFeatures->stippledRectangularLines) { enabledFeatureNames.emplace_back("stippledRectangularLines"); }
                if(pFeatures->stippledBresenhamLines) { enabledFeatureNames.emplace_back("stippledBresenhamLines"); }
                if(pFeatures->stippledSmoothLines) { enabledFeatureNames.emplace_back("stippledSmoothLines"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVertexAttributeDivisorFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVertexAttributeDivisorFeatures*>(header);
                if(pFeatures->vertexAttributeInstanceRateDivisor) { enabledFeatureNames.emplace_back("vertexAttributeInstanceRateDivisor"); }
                if(pFeatures->vertexAttributeInstanceRateZeroDivisor) { enabledFeatureNames.emplace_back("vertexAttributeInstanceRateZeroDivisor"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDynamicRenderingLocalReadFeatures>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDynamicRenderingLocalReadFeatures*>(header);
                if(pFeatures->dynamicRenderingLocalRead) { enabledFeatureNames.emplace_back("dynamicRenderingLocalRead"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePerformanceQueryFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePerformanceQueryFeaturesKHR*>(header);
                if(pFeatures->performanceCounterQueryPools) { enabledFeatureNames.emplace_back("performanceCounterQueryPools"); }
                if(pFeatures->performanceCounterMultipleQueryPools) { enabledFeatureNames.emplace_back("performanceCounterMultipleQueryPools"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderBfloat16FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderBfloat16FeaturesKHR*>(header);
                if(pFeatures->shaderBFloat16Type) { enabledFeatureNames.emplace_back("shaderBFloat16Type"); }
                if(pFeatures->shaderBFloat16DotProduct) { enabledFeatureNames.emplace_back("shaderBFloat16DotProduct"); }
                if(pFeatures->shaderBFloat16CooperativeMatrix) { enabledFeatureNames.emplace_back("shaderBFloat16CooperativeMatrix"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePortabilitySubsetFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePortabilitySubsetFeaturesKHR*>(header);
                if(pFeatures->constantAlphaColorBlendFactors) { enabledFeatureNames.emplace_back("constantAlphaColorBlendFactors"); }
                if(pFeatures->events) { enabledFeatureNames.emplace_back("events"); }
                if(pFeatures->imageViewFormatReinterpretation) { enabledFeatureNames.emplace_back("imageViewFormatReinterpretation"); }
                if(pFeatures->imageViewFormatSwizzle) { enabledFeatureNames.emplace_back("imageViewFormatSwizzle"); }
                if(pFeatures->imageView2DOn3DImage) { enabledFeatureNames.emplace_back("imageView2DOn3DImage"); }
                if(pFeatures->multisampleArrayImage) { enabledFeatureNames.emplace_back("multisampleArrayImage"); }
                if(pFeatures->mutableComparisonSamplers) { enabledFeatureNames.emplace_back("mutableComparisonSamplers"); }
                if(pFeatures->pointPolygons) { enabledFeatureNames.emplace_back("pointPolygons"); }
                if(pFeatures->samplerMipLodBias) { enabledFeatureNames.emplace_back("samplerMipLodBias"); }
                if(pFeatures->separateStencilMaskRef) { enabledFeatureNames.emplace_back("separateStencilMaskRef"); }
                if(pFeatures->shaderSampleRateInterpolationFunctions) { enabledFeatureNames.emplace_back("shaderSampleRateInterpolationFunctions"); }
                if(pFeatures->tessellationIsolines) { enabledFeatureNames.emplace_back("tessellationIsolines"); }
                if(pFeatures->tessellationPointMode) { enabledFeatureNames.emplace_back("tessellationPointMode"); }
                if(pFeatures->triangleFans) { enabledFeatureNames.emplace_back("triangleFans"); }
                if(pFeatures->vertexAttributeAccessBeyondStride) { enabledFeatureNames.emplace_back("vertexAttributeAccessBeyondStride"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderClockFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderClockFeaturesKHR*>(header);
                if(pFeatures->shaderSubgroupClock) { enabledFeatureNames.emplace_back("shaderSubgroupClock"); }
                if(pFeatures->shaderDeviceClock) { enabledFeatureNames.emplace_back("shaderDeviceClock"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentShadingRateFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentShadingRateFeaturesKHR*>(header);
                if(pFeatures->pipelineFragmentShadingRate) { enabledFeatureNames.emplace_back("pipelineFragmentShadingRate"); }
                if(pFeatures->primitiveFragmentShadingRate) { enabledFeatureNames.emplace_back("primitiveFragmentShadingRate"); }
                if(pFeatures->attachmentFragmentShadingRate) { enabledFeatureNames.emplace_back("attachmentFragmentShadingRate"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderConstantDataFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderConstantDataFeaturesKHR*>(header);
                if(pFeatures->shaderConstantData) { enabledFeatureNames.emplace_back("shaderConstantData"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderAbortFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderAbortFeaturesKHR*>(header);
                if(pFeatures->shaderAbort) { enabledFeatureNames.emplace_back("shaderAbort"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderQuadControlFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderQuadControlFeaturesKHR*>(header);
                if(pFeatures->shaderQuadControl) { enabledFeatureNames.emplace_back("shaderQuadControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentWaitFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentWaitFeaturesKHR*>(header);
                if(pFeatures->presentWait) { enabledFeatureNames.emplace_back("presentWait"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR*>(header);
                if(pFeatures->pipelineExecutableInfo) { enabledFeatureNames.emplace_back("pipelineExecutableInfo"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentIdFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentIdFeaturesKHR*>(header);
                if(pFeatures->presentId) { enabledFeatureNames.emplace_back("presentId"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDeviceAddressCommandsFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDeviceAddressCommandsFeaturesKHR*>(header);
                if(pFeatures->deviceAddressCommands) { enabledFeatureNames.emplace_back("deviceAddressCommands"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentShaderBarycentricFeaturesKHR*>(header);
                if(pFeatures->fragmentShaderBarycentric) { enabledFeatureNames.emplace_back("fragmentShaderBarycentric"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR*>(header);
                if(pFeatures->shaderSubgroupUniformControlFlow) { enabledFeatureNames.emplace_back("shaderSubgroupUniformControlFlow"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR*>(header);
                if(pFeatures->workgroupMemoryExplicitLayout) { enabledFeatureNames.emplace_back("workgroupMemoryExplicitLayout"); }
                if(pFeatures->workgroupMemoryExplicitLayoutScalarBlockLayout) { enabledFeatureNames.emplace_back("workgroupMemoryExplicitLayoutScalarBlockLayout"); }
                if(pFeatures->workgroupMemoryExplicitLayout8BitAccess) { enabledFeatureNames.emplace_back("workgroupMemoryExplicitLayout8BitAccess"); }
                if(pFeatures->workgroupMemoryExplicitLayout16BitAccess) { enabledFeatureNames.emplace_back("workgroupMemoryExplicitLayout16BitAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingMaintenance1FeaturesKHR*>(header);
                if(pFeatures->rayTracingMaintenance1) { enabledFeatureNames.emplace_back("rayTracingMaintenance1"); }
                if(pFeatures->rayTracingPipelineTraceRaysIndirect2) { enabledFeatureNames.emplace_back("rayTracingPipelineTraceRaysIndirect2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderUntypedPointersFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderUntypedPointersFeaturesKHR*>(header);
                if(pFeatures->shaderUntypedPointers) { enabledFeatureNames.emplace_back("shaderUntypedPointers"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderMaximalReconvergenceFeaturesKHR*>(header);
                if(pFeatures->shaderMaximalReconvergence) { enabledFeatureNames.emplace_back("shaderMaximalReconvergence"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentId2FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentId2FeaturesKHR*>(header);
                if(pFeatures->presentId2) { enabledFeatureNames.emplace_back("presentId2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentWait2FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentWait2FeaturesKHR*>(header);
                if(pFeatures->presentWait2) { enabledFeatureNames.emplace_back("presentWait2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingPositionFetchFeaturesKHR*>(header);
                if(pFeatures->rayTracingPositionFetch) { enabledFeatureNames.emplace_back("rayTracingPositionFetch"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineBinaryFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineBinaryFeaturesKHR*>(header);
                if(pFeatures->pipelineBinaries) { enabledFeatureNames.emplace_back("pipelineBinaries"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSwapchainMaintenance1FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSwapchainMaintenance1FeaturesKHR*>(header);
                if(pFeatures->swapchainMaintenance1) { enabledFeatureNames.emplace_back("swapchainMaintenance1"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceInternallySynchronizedQueuesFeaturesKHR*>(header);
                if(pFeatures->internallySynchronizedQueues) { enabledFeatureNames.emplace_back("internallySynchronizedQueues"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCooperativeMatrixFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCooperativeMatrixFeaturesKHR*>(header);
                if(pFeatures->cooperativeMatrix) { enabledFeatureNames.emplace_back("cooperativeMatrix"); }
                if(pFeatures->cooperativeMatrixRobustBufferAccess) { enabledFeatureNames.emplace_back("cooperativeMatrixRobustBufferAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceComputeShaderDerivativesFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceComputeShaderDerivativesFeaturesKHR*>(header);
                if(pFeatures->computeDerivativeGroupQuads) { enabledFeatureNames.emplace_back("computeDerivativeGroupQuads"); }
                if(pFeatures->computeDerivativeGroupLinear) { enabledFeatureNames.emplace_back("computeDerivativeGroupLinear"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoEncodeAV1FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoEncodeAV1FeaturesKHR*>(header);
                if(pFeatures->videoEncodeAV1) { enabledFeatureNames.emplace_back("videoEncodeAV1"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoDecodeVP9FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoDecodeVP9FeaturesKHR*>(header);
                if(pFeatures->videoDecodeVP9) { enabledFeatureNames.emplace_back("videoDecodeVP9"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoMaintenance1FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoMaintenance1FeaturesKHR*>(header);
                if(pFeatures->videoMaintenance1) { enabledFeatureNames.emplace_back("videoMaintenance1"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR*>(header);
                if(pFeatures->unifiedImageLayouts) { enabledFeatureNames.emplace_back("unifiedImageLayouts"); }
                if(pFeatures->unifiedImageLayoutsVideo) { enabledFeatureNames.emplace_back("unifiedImageLayoutsVideo"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCopyMemoryIndirectFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCopyMemoryIndirectFeaturesKHR*>(header);
                if(pFeatures->indirectMemoryCopy) { enabledFeatureNames.emplace_back("indirectMemoryCopy"); }
                if(pFeatures->indirectMemoryToImageCopy) { enabledFeatureNames.emplace_back("indirectMemoryToImageCopy"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR*>(header);
                if(pFeatures->videoEncodeIntraRefresh) { enabledFeatureNames.emplace_back("videoEncodeIntraRefresh"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR*>(header);
                if(pFeatures->videoEncodeQuantizationMap) { enabledFeatureNames.emplace_back("videoEncodeQuantizationMap"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR*>(header);
                if(pFeatures->shaderRelaxedExtendedInstruction) { enabledFeatureNames.emplace_back("shaderRelaxedExtendedInstruction"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance7FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance7FeaturesKHR*>(header);
                if(pFeatures->maintenance7) { enabledFeatureNames.emplace_back("maintenance7"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFaultFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFaultFeaturesKHR*>(header);
                if(pFeatures->deviceFault) { enabledFeatureNames.emplace_back("deviceFault"); }
                if(pFeatures->deviceFaultVendorBinary) { enabledFeatureNames.emplace_back("deviceFaultVendorBinary"); }
                if(pFeatures->deviceFaultReportMasked) { enabledFeatureNames.emplace_back("deviceFaultReportMasked"); }
                if(pFeatures->deviceFaultDeviceLostOnMasked) { enabledFeatureNames.emplace_back("deviceFaultDeviceLostOnMasked"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance8FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance8FeaturesKHR*>(header);
                if(pFeatures->maintenance8) { enabledFeatureNames.emplace_back("maintenance8"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderFmaFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderFmaFeaturesKHR*>(header);
                if(pFeatures->shaderFmaFloat16) { enabledFeatureNames.emplace_back("shaderFmaFloat16"); }
                if(pFeatures->shaderFmaFloat32) { enabledFeatureNames.emplace_back("shaderFmaFloat32"); }
                if(pFeatures->shaderFmaFloat64) { enabledFeatureNames.emplace_back("shaderFmaFloat64"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance9FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance9FeaturesKHR*>(header);
                if(pFeatures->maintenance9) { enabledFeatureNames.emplace_back("maintenance9"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDepthClampZeroOneFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDepthClampZeroOneFeaturesKHR*>(header);
                if(pFeatures->depthClampZeroOne) { enabledFeatureNames.emplace_back("depthClampZeroOne"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRobustness2FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRobustness2FeaturesKHR*>(header);
                if(pFeatures->robustBufferAccess2) { enabledFeatureNames.emplace_back("robustBufferAccess2"); }
                if(pFeatures->robustImageAccess2) { enabledFeatureNames.emplace_back("robustImageAccess2"); }
                if(pFeatures->nullDescriptor) { enabledFeatureNames.emplace_back("nullDescriptor"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentModeFifoLatestReadyFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentModeFifoLatestReadyFeaturesKHR*>(header);
                if(pFeatures->presentModeFifoLatestReady) { enabledFeatureNames.emplace_back("presentModeFifoLatestReady"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance10FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance10FeaturesKHR*>(header);
                if(pFeatures->maintenance10) { enabledFeatureNames.emplace_back("maintenance10"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMaintenance11FeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMaintenance11FeaturesKHR*>(header);
                if(pFeatures->maintenance11) { enabledFeatureNames.emplace_back("maintenance11"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTransformFeedbackFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTransformFeedbackFeaturesEXT*>(header);
                if(pFeatures->transformFeedback) { enabledFeatureNames.emplace_back("transformFeedback"); }
                if(pFeatures->geometryStreams) { enabledFeatureNames.emplace_back("geometryStreams"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCornerSampledImageFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCornerSampledImageFeaturesNV*>(header);
                if(pFeatures->cornerSampledImage) { enabledFeatureNames.emplace_back("cornerSampledImage"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceASTCDecodeFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceASTCDecodeFeaturesEXT*>(header);
                if(pFeatures->decodeModeSharedExponent) { enabledFeatureNames.emplace_back("decodeModeSharedExponent"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceConditionalRenderingFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceConditionalRenderingFeaturesEXT*>(header);
                if(pFeatures->conditionalRendering) { enabledFeatureNames.emplace_back("conditionalRendering"); }
                if(pFeatures->inheritedConditionalRendering) { enabledFeatureNames.emplace_back("inheritedConditionalRendering"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDepthClipEnableFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDepthClipEnableFeaturesEXT*>(header);
                if(pFeatures->depthClipEnable) { enabledFeatureNames.emplace_back("depthClipEnable"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRelaxedLineRasterizationFeaturesIMG*>(header);
                if(pFeatures->relaxedLineRasterization) { enabledFeatureNames.emplace_back("relaxedLineRasterization"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT*>(header);
                if(pFeatures->advancedBlendCoherentOperations) { enabledFeatureNames.emplace_back("advancedBlendCoherentOperations"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderSMBuiltinsFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderSMBuiltinsFeaturesNV*>(header);
                if(pFeatures->shaderSMBuiltins) { enabledFeatureNames.emplace_back("shaderSMBuiltins"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShadingRateImageFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShadingRateImageFeaturesNV*>(header);
                if(pFeatures->shadingRateImage) { enabledFeatureNames.emplace_back("shadingRateImage"); }
                if(pFeatures->shadingRateCoarseSampleOrder) { enabledFeatureNames.emplace_back("shadingRateCoarseSampleOrder"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV*>(header);
                if(pFeatures->representativeFragmentTest) { enabledFeatureNames.emplace_back("representativeFragmentTest"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCooperativeMatrixConversionFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCooperativeMatrixConversionFeaturesQCOM*>(header);
                if(pFeatures->cooperativeMatrixConversion) { enabledFeatureNames.emplace_back("cooperativeMatrixConversion"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMeshShaderFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMeshShaderFeaturesNV*>(header);
                if(pFeatures->taskShader) { enabledFeatureNames.emplace_back("taskShader"); }
                if(pFeatures->meshShader) { enabledFeatureNames.emplace_back("meshShader"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderImageFootprintFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderImageFootprintFeaturesNV*>(header);
                if(pFeatures->imageFootprint) { enabledFeatureNames.emplace_back("imageFootprint"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExclusiveScissorFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExclusiveScissorFeaturesNV*>(header);
                if(pFeatures->exclusiveScissor) { enabledFeatureNames.emplace_back("exclusiveScissor"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentTimingFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentTimingFeaturesEXT*>(header);
                if(pFeatures->presentTiming) { enabledFeatureNames.emplace_back("presentTiming"); }
                if(pFeatures->presentAtAbsoluteTime) { enabledFeatureNames.emplace_back("presentAtAbsoluteTime"); }
                if(pFeatures->presentAtRelativeTime) { enabledFeatureNames.emplace_back("presentAtRelativeTime"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL*>(header);
                if(pFeatures->shaderIntegerFunctions2) { enabledFeatureNames.emplace_back("shaderIntegerFunctions2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentDensityMapFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentDensityMapFeaturesEXT*>(header);
                if(pFeatures->fragmentDensityMap) { enabledFeatureNames.emplace_back("fragmentDensityMap"); }
                if(pFeatures->fragmentDensityMapDynamic) { enabledFeatureNames.emplace_back("fragmentDensityMapDynamic"); }
                if(pFeatures->fragmentDensityMapNonSubsampledImages) { enabledFeatureNames.emplace_back("fragmentDensityMapNonSubsampledImages"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCoherentMemoryFeaturesAMD>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCoherentMemoryFeaturesAMD*>(header);
                if(pFeatures->deviceCoherentMemory) { enabledFeatureNames.emplace_back("deviceCoherentMemory"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT*>(header);
                if(pFeatures->shaderImageInt64Atomics) { enabledFeatureNames.emplace_back("shaderImageInt64Atomics"); }
                if(pFeatures->sparseImageInt64Atomics) { enabledFeatureNames.emplace_back("sparseImageInt64Atomics"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMemoryPriorityFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMemoryPriorityFeaturesEXT*>(header);
                if(pFeatures->memoryPriority) { enabledFeatureNames.emplace_back("memoryPriority"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV*>(header);
                if(pFeatures->dedicatedAllocationImageAliasing) { enabledFeatureNames.emplace_back("dedicatedAllocationImageAliasing"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceBufferDeviceAddressFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceBufferDeviceAddressFeaturesEXT*>(header);
                if(pFeatures->bufferDeviceAddress) { enabledFeatureNames.emplace_back("bufferDeviceAddress"); }
                if(pFeatures->bufferDeviceAddressCaptureReplay) { enabledFeatureNames.emplace_back("bufferDeviceAddressCaptureReplay"); }
                if(pFeatures->bufferDeviceAddressMultiDevice) { enabledFeatureNames.emplace_back("bufferDeviceAddressMultiDevice"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCooperativeMatrixFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCooperativeMatrixFeaturesNV*>(header);
                if(pFeatures->cooperativeMatrix) { enabledFeatureNames.emplace_back("cooperativeMatrix"); }
                if(pFeatures->cooperativeMatrixRobustBufferAccess) { enabledFeatureNames.emplace_back("cooperativeMatrixRobustBufferAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCoverageReductionModeFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCoverageReductionModeFeaturesNV*>(header);
                if(pFeatures->coverageReductionMode) { enabledFeatureNames.emplace_back("coverageReductionMode"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT*>(header);
                if(pFeatures->fragmentShaderSampleInterlock) { enabledFeatureNames.emplace_back("fragmentShaderSampleInterlock"); }
                if(pFeatures->fragmentShaderPixelInterlock) { enabledFeatureNames.emplace_back("fragmentShaderPixelInterlock"); }
                if(pFeatures->fragmentShaderShadingRateInterlock) { enabledFeatureNames.emplace_back("fragmentShaderShadingRateInterlock"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceYcbcrImageArraysFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceYcbcrImageArraysFeaturesEXT*>(header);
                if(pFeatures->ycbcrImageArrays) { enabledFeatureNames.emplace_back("ycbcrImageArrays"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceProvokingVertexFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceProvokingVertexFeaturesEXT*>(header);
                if(pFeatures->provokingVertexLast) { enabledFeatureNames.emplace_back("provokingVertexLast"); }
                if(pFeatures->transformFeedbackPreservesProvokingVertex) { enabledFeatureNames.emplace_back("transformFeedbackPreservesProvokingVertex"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderAtomicFloatFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderAtomicFloatFeaturesEXT*>(header);
                if(pFeatures->shaderBufferFloat32Atomics) { enabledFeatureNames.emplace_back("shaderBufferFloat32Atomics"); }
                if(pFeatures->shaderBufferFloat32AtomicAdd) { enabledFeatureNames.emplace_back("shaderBufferFloat32AtomicAdd"); }
                if(pFeatures->shaderBufferFloat64Atomics) { enabledFeatureNames.emplace_back("shaderBufferFloat64Atomics"); }
                if(pFeatures->shaderBufferFloat64AtomicAdd) { enabledFeatureNames.emplace_back("shaderBufferFloat64AtomicAdd"); }
                if(pFeatures->shaderSharedFloat32Atomics) { enabledFeatureNames.emplace_back("shaderSharedFloat32Atomics"); }
                if(pFeatures->shaderSharedFloat32AtomicAdd) { enabledFeatureNames.emplace_back("shaderSharedFloat32AtomicAdd"); }
                if(pFeatures->shaderSharedFloat64Atomics) { enabledFeatureNames.emplace_back("shaderSharedFloat64Atomics"); }
                if(pFeatures->shaderSharedFloat64AtomicAdd) { enabledFeatureNames.emplace_back("shaderSharedFloat64AtomicAdd"); }
                if(pFeatures->shaderImageFloat32Atomics) { enabledFeatureNames.emplace_back("shaderImageFloat32Atomics"); }
                if(pFeatures->shaderImageFloat32AtomicAdd) { enabledFeatureNames.emplace_back("shaderImageFloat32AtomicAdd"); }
                if(pFeatures->sparseImageFloat32Atomics) { enabledFeatureNames.emplace_back("sparseImageFloat32Atomics"); }
                if(pFeatures->sparseImageFloat32AtomicAdd) { enabledFeatureNames.emplace_back("sparseImageFloat32AtomicAdd"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExtendedDynamicStateFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExtendedDynamicStateFeaturesEXT*>(header);
                if(pFeatures->extendedDynamicState) { enabledFeatureNames.emplace_back("extendedDynamicState"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMapMemoryPlacedFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMapMemoryPlacedFeaturesEXT*>(header);
                if(pFeatures->memoryMapPlaced) { enabledFeatureNames.emplace_back("memoryMapPlaced"); }
                if(pFeatures->memoryMapRangePlaced) { enabledFeatureNames.emplace_back("memoryMapRangePlaced"); }
                if(pFeatures->memoryUnmapReserve) { enabledFeatureNames.emplace_back("memoryUnmapReserve"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT*>(header);
                if(pFeatures->shaderBufferFloat16Atomics) { enabledFeatureNames.emplace_back("shaderBufferFloat16Atomics"); }
                if(pFeatures->shaderBufferFloat16AtomicAdd) { enabledFeatureNames.emplace_back("shaderBufferFloat16AtomicAdd"); }
                if(pFeatures->shaderBufferFloat16AtomicMinMax) { enabledFeatureNames.emplace_back("shaderBufferFloat16AtomicMinMax"); }
                if(pFeatures->shaderBufferFloat32AtomicMinMax) { enabledFeatureNames.emplace_back("shaderBufferFloat32AtomicMinMax"); }
                if(pFeatures->shaderBufferFloat64AtomicMinMax) { enabledFeatureNames.emplace_back("shaderBufferFloat64AtomicMinMax"); }
                if(pFeatures->shaderSharedFloat16Atomics) { enabledFeatureNames.emplace_back("shaderSharedFloat16Atomics"); }
                if(pFeatures->shaderSharedFloat16AtomicAdd) { enabledFeatureNames.emplace_back("shaderSharedFloat16AtomicAdd"); }
                if(pFeatures->shaderSharedFloat16AtomicMinMax) { enabledFeatureNames.emplace_back("shaderSharedFloat16AtomicMinMax"); }
                if(pFeatures->shaderSharedFloat32AtomicMinMax) { enabledFeatureNames.emplace_back("shaderSharedFloat32AtomicMinMax"); }
                if(pFeatures->shaderSharedFloat64AtomicMinMax) { enabledFeatureNames.emplace_back("shaderSharedFloat64AtomicMinMax"); }
                if(pFeatures->shaderImageFloat32AtomicMinMax) { enabledFeatureNames.emplace_back("shaderImageFloat32AtomicMinMax"); }
                if(pFeatures->sparseImageFloat32AtomicMinMax) { enabledFeatureNames.emplace_back("sparseImageFloat32AtomicMinMax"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV*>(header);
                if(pFeatures->deviceGeneratedCommands) { enabledFeatureNames.emplace_back("deviceGeneratedCommands"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceInheritedViewportScissorFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceInheritedViewportScissorFeaturesNV*>(header);
                if(pFeatures->inheritedViewportScissor2D) { enabledFeatureNames.emplace_back("inheritedViewportScissor2D"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT*>(header);
                if(pFeatures->texelBufferAlignment) { enabledFeatureNames.emplace_back("texelBufferAlignment"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDepthBiasControlFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDepthBiasControlFeaturesEXT*>(header);
                if(pFeatures->depthBiasControl) { enabledFeatureNames.emplace_back("depthBiasControl"); }
                if(pFeatures->leastRepresentableValueForceUnormRepresentation) { enabledFeatureNames.emplace_back("leastRepresentableValueForceUnormRepresentation"); }
                if(pFeatures->floatRepresentation) { enabledFeatureNames.emplace_back("floatRepresentation"); }
                if(pFeatures->depthBiasExact) { enabledFeatureNames.emplace_back("depthBiasExact"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDeviceMemoryReportFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDeviceMemoryReportFeaturesEXT*>(header);
                if(pFeatures->deviceMemoryReport) { enabledFeatureNames.emplace_back("deviceMemoryReport"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCustomBorderColorFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCustomBorderColorFeaturesEXT*>(header);
                if(pFeatures->customBorderColors) { enabledFeatureNames.emplace_back("customBorderColors"); }
                if(pFeatures->customBorderColorWithoutFormat) { enabledFeatureNames.emplace_back("customBorderColorWithoutFormat"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTextureCompressionASTC3DFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTextureCompressionASTC3DFeaturesEXT*>(header);
                if(pFeatures->textureCompressionASTC_3D) { enabledFeatureNames.emplace_back("textureCompressionASTC_3D"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentBarrierFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentBarrierFeaturesNV*>(header);
                if(pFeatures->presentBarrier) { enabledFeatureNames.emplace_back("presentBarrier"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDiagnosticsConfigFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDiagnosticsConfigFeaturesNV*>(header);
                if(pFeatures->diagnosticsConfig) { enabledFeatureNames.emplace_back("diagnosticsConfig"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceQueuePerfHintFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceQueuePerfHintFeaturesQCOM*>(header);
                if(pFeatures->queuePerfHint) { enabledFeatureNames.emplace_back("queuePerfHint"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTileShadingFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTileShadingFeaturesQCOM*>(header);
                if(pFeatures->tileShading) { enabledFeatureNames.emplace_back("tileShading"); }
                if(pFeatures->tileShadingFragmentStage) { enabledFeatureNames.emplace_back("tileShadingFragmentStage"); }
                if(pFeatures->tileShadingColorAttachments) { enabledFeatureNames.emplace_back("tileShadingColorAttachments"); }
                if(pFeatures->tileShadingDepthAttachments) { enabledFeatureNames.emplace_back("tileShadingDepthAttachments"); }
                if(pFeatures->tileShadingStencilAttachments) { enabledFeatureNames.emplace_back("tileShadingStencilAttachments"); }
                if(pFeatures->tileShadingInputAttachments) { enabledFeatureNames.emplace_back("tileShadingInputAttachments"); }
                if(pFeatures->tileShadingSampledAttachments) { enabledFeatureNames.emplace_back("tileShadingSampledAttachments"); }
                if(pFeatures->tileShadingPerTileDraw) { enabledFeatureNames.emplace_back("tileShadingPerTileDraw"); }
                if(pFeatures->tileShadingPerTileDispatch) { enabledFeatureNames.emplace_back("tileShadingPerTileDispatch"); }
                if(pFeatures->tileShadingDispatchTile) { enabledFeatureNames.emplace_back("tileShadingDispatchTile"); }
                if(pFeatures->tileShadingApron) { enabledFeatureNames.emplace_back("tileShadingApron"); }
                if(pFeatures->tileShadingAnisotropicApron) { enabledFeatureNames.emplace_back("tileShadingAnisotropicApron"); }
                if(pFeatures->tileShadingAtomicOps) { enabledFeatureNames.emplace_back("tileShadingAtomicOps"); }
                if(pFeatures->tileShadingImageProcessing) { enabledFeatureNames.emplace_back("tileShadingImageProcessing"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDescriptorBufferFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDescriptorBufferFeaturesEXT*>(header);
                if(pFeatures->descriptorBuffer) { enabledFeatureNames.emplace_back("descriptorBuffer"); }
                if(pFeatures->descriptorBufferCaptureReplay) { enabledFeatureNames.emplace_back("descriptorBufferCaptureReplay"); }
                if(pFeatures->descriptorBufferImageLayoutIgnored) { enabledFeatureNames.emplace_back("descriptorBufferImageLayoutIgnored"); }
                if(pFeatures->descriptorBufferPushDescriptors) { enabledFeatureNames.emplace_back("descriptorBufferPushDescriptors"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT*>(header);
                if(pFeatures->graphicsPipelineLibrary) { enabledFeatureNames.emplace_back("graphicsPipelineLibrary"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD*>(header);
                if(pFeatures->shaderEarlyAndLateFragmentTests) { enabledFeatureNames.emplace_back("shaderEarlyAndLateFragmentTests"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV*>(header);
                if(pFeatures->fragmentShadingRateEnums) { enabledFeatureNames.emplace_back("fragmentShadingRateEnums"); }
                if(pFeatures->supersampleFragmentShadingRates) { enabledFeatureNames.emplace_back("supersampleFragmentShadingRates"); }
                if(pFeatures->noInvocationFragmentShadingRates) { enabledFeatureNames.emplace_back("noInvocationFragmentShadingRates"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingMotionBlurFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingMotionBlurFeaturesNV*>(header);
                if(pFeatures->rayTracingMotionBlur) { enabledFeatureNames.emplace_back("rayTracingMotionBlur"); }
                if(pFeatures->rayTracingMotionBlurPipelineTraceRaysIndirect) { enabledFeatureNames.emplace_back("rayTracingMotionBlurPipelineTraceRaysIndirect"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT*>(header);
                if(pFeatures->ycbcr2plane444Formats) { enabledFeatureNames.emplace_back("ycbcr2plane444Formats"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentDensityMap2FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentDensityMap2FeaturesEXT*>(header);
                if(pFeatures->fragmentDensityMapDeferred) { enabledFeatureNames.emplace_back("fragmentDensityMapDeferred"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageCompressionControlFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageCompressionControlFeaturesEXT*>(header);
                if(pFeatures->imageCompressionControl) { enabledFeatureNames.emplace_back("imageCompressionControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT*>(header);
                if(pFeatures->attachmentFeedbackLoopLayout) { enabledFeatureNames.emplace_back("attachmentFeedbackLoopLayout"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevice4444FormatsFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevice4444FormatsFeaturesEXT*>(header);
                if(pFeatures->formatA4R4G4B4) { enabledFeatureNames.emplace_back("formatA4R4G4B4"); }
                if(pFeatures->formatA4B4G4R4) { enabledFeatureNames.emplace_back("formatA4B4G4R4"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFaultFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFaultFeaturesEXT*>(header);
                if(pFeatures->deviceFault) { enabledFeatureNames.emplace_back("deviceFault"); }
                if(pFeatures->deviceFaultVendorBinary) { enabledFeatureNames.emplace_back("deviceFaultVendorBinary"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT*>(header);
                if(pFeatures->rasterizationOrderColorAttachmentAccess) { enabledFeatureNames.emplace_back("rasterizationOrderColorAttachmentAccess"); }
                if(pFeatures->rasterizationOrderDepthAttachmentAccess) { enabledFeatureNames.emplace_back("rasterizationOrderDepthAttachmentAccess"); }
                if(pFeatures->rasterizationOrderStencilAttachmentAccess) { enabledFeatureNames.emplace_back("rasterizationOrderStencilAttachmentAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRGBA10X6FormatsFeaturesEXT*>(header);
                if(pFeatures->formatRgba10x6WithoutYCbCrSampler) { enabledFeatureNames.emplace_back("formatRgba10x6WithoutYCbCrSampler"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT*>(header);
                if(pFeatures->mutableDescriptorType) { enabledFeatureNames.emplace_back("mutableDescriptorType"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT*>(header);
                if(pFeatures->vertexInputDynamicState) { enabledFeatureNames.emplace_back("vertexInputDynamicState"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAddressBindingReportFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAddressBindingReportFeaturesEXT*>(header);
                if(pFeatures->reportAddressBinding) { enabledFeatureNames.emplace_back("reportAddressBinding"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDepthClipControlFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDepthClipControlFeaturesEXT*>(header);
                if(pFeatures->depthClipControl) { enabledFeatureNames.emplace_back("depthClipControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePrimitiveTopologyListRestartFeaturesEXT*>(header);
                if(pFeatures->primitiveTopologyListRestart) { enabledFeatureNames.emplace_back("primitiveTopologyListRestart"); }
                if(pFeatures->primitiveTopologyPatchListRestart) { enabledFeatureNames.emplace_back("primitiveTopologyPatchListRestart"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceInvocationMaskFeaturesHUAWEI>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceInvocationMaskFeaturesHUAWEI*>(header);
                if(pFeatures->invocationMask) { enabledFeatureNames.emplace_back("invocationMask"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExternalMemoryRDMAFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExternalMemoryRDMAFeaturesNV*>(header);
                if(pFeatures->externalMemoryRDMA) { enabledFeatureNames.emplace_back("externalMemoryRDMA"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFrameBoundaryFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFrameBoundaryFeaturesEXT*>(header);
                if(pFeatures->frameBoundary) { enabledFeatureNames.emplace_back("frameBoundary"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT*>(header);
                if(pFeatures->multisampledRenderToSingleSampled) { enabledFeatureNames.emplace_back("multisampledRenderToSingleSampled"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExtendedDynamicState2FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExtendedDynamicState2FeaturesEXT*>(header);
                if(pFeatures->extendedDynamicState2) { enabledFeatureNames.emplace_back("extendedDynamicState2"); }
                if(pFeatures->extendedDynamicState2LogicOp) { enabledFeatureNames.emplace_back("extendedDynamicState2LogicOp"); }
                if(pFeatures->extendedDynamicState2PatchControlPoints) { enabledFeatureNames.emplace_back("extendedDynamicState2PatchControlPoints"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceColorWriteEnableFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceColorWriteEnableFeaturesEXT*>(header);
                if(pFeatures->colorWriteEnable) { enabledFeatureNames.emplace_back("colorWriteEnable"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePrimitivesGeneratedQueryFeaturesEXT*>(header);
                if(pFeatures->primitivesGeneratedQuery) { enabledFeatureNames.emplace_back("primitivesGeneratedQuery"); }
                if(pFeatures->primitivesGeneratedQueryWithRasterizerDiscard) { enabledFeatureNames.emplace_back("primitivesGeneratedQueryWithRasterizerDiscard"); }
                if(pFeatures->primitivesGeneratedQueryWithNonZeroStreams) { enabledFeatureNames.emplace_back("primitivesGeneratedQueryWithNonZeroStreams"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE*>(header);
                if(pFeatures->videoEncodeRgbConversion) { enabledFeatureNames.emplace_back("videoEncodeRgbConversion"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageViewMinLodFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageViewMinLodFeaturesEXT*>(header);
                if(pFeatures->minLod) { enabledFeatureNames.emplace_back("minLod"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMultiDrawFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMultiDrawFeaturesEXT*>(header);
                if(pFeatures->multiDraw) { enabledFeatureNames.emplace_back("multiDraw"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImage2DViewOf3DFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImage2DViewOf3DFeaturesEXT*>(header);
                if(pFeatures->image2DViewOf3D) { enabledFeatureNames.emplace_back("image2DViewOf3D"); }
                if(pFeatures->sampler2DViewOf3D) { enabledFeatureNames.emplace_back("sampler2DViewOf3D"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderTileImageFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderTileImageFeaturesEXT*>(header);
                if(pFeatures->shaderTileImageColorReadAccess) { enabledFeatureNames.emplace_back("shaderTileImageColorReadAccess"); }
                if(pFeatures->shaderTileImageDepthReadAccess) { enabledFeatureNames.emplace_back("shaderTileImageDepthReadAccess"); }
                if(pFeatures->shaderTileImageStencilReadAccess) { enabledFeatureNames.emplace_back("shaderTileImageStencilReadAccess"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceOpacityMicromapFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceOpacityMicromapFeaturesEXT*>(header);
                if(pFeatures->micromap) { enabledFeatureNames.emplace_back("micromap"); }
                if(pFeatures->micromapCaptureReplay) { enabledFeatureNames.emplace_back("micromapCaptureReplay"); }
                if(pFeatures->micromapHostCommands) { enabledFeatureNames.emplace_back("micromapHostCommands"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDisplacementMicromapFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDisplacementMicromapFeaturesNV*>(header);
                if(pFeatures->displacementMicromap) { enabledFeatureNames.emplace_back("displacementMicromap"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceClusterCullingShaderFeaturesHUAWEI*>(header);
                if(pFeatures->clustercullingShader) { enabledFeatureNames.emplace_back("clustercullingShader"); }
                if(pFeatures->multiviewClusterCullingShader) { enabledFeatureNames.emplace_back("multiviewClusterCullingShader"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI*>(header);
                if(pFeatures->clusterShadingRate) { enabledFeatureNames.emplace_back("clusterShadingRate"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceBorderColorSwizzleFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceBorderColorSwizzleFeaturesEXT*>(header);
                if(pFeatures->borderColorSwizzle) { enabledFeatureNames.emplace_back("borderColorSwizzle"); }
                if(pFeatures->borderColorSwizzleFromImage) { enabledFeatureNames.emplace_back("borderColorSwizzleFromImage"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT*>(header);
                if(pFeatures->pageableDeviceLocalMemory) { enabledFeatureNames.emplace_back("pageableDeviceLocalMemory"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSchedulingControlsFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSchedulingControlsFeaturesARM*>(header);
                if(pFeatures->schedulingControls) { enabledFeatureNames.emplace_back("schedulingControls"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageSlicedViewOf3DFeaturesEXT*>(header);
                if(pFeatures->imageSlicedViewOf3D) { enabledFeatureNames.emplace_back("imageSlicedViewOf3D"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDescriptorSetHostMappingFeaturesVALVE*>(header);
                if(pFeatures->descriptorSetHostMapping) { enabledFeatureNames.emplace_back("descriptorSetHostMapping"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceNonSeamlessCubeMapFeaturesEXT*>(header);
                if(pFeatures->nonSeamlessCubeMap) { enabledFeatureNames.emplace_back("nonSeamlessCubeMap"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRenderPassStripedFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRenderPassStripedFeaturesARM*>(header);
                if(pFeatures->renderPassStriped) { enabledFeatureNames.emplace_back("renderPassStriped"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentDensityMapOffsetFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentDensityMapOffsetFeaturesEXT*>(header);
                if(pFeatures->fragmentDensityMapOffset) { enabledFeatureNames.emplace_back("fragmentDensityMapOffset"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV*>(header);
                if(pFeatures->deviceGeneratedCompute) { enabledFeatureNames.emplace_back("deviceGeneratedCompute"); }
                if(pFeatures->deviceGeneratedComputePipelines) { enabledFeatureNames.emplace_back("deviceGeneratedComputePipelines"); }
                if(pFeatures->deviceGeneratedComputeCaptureReplay) { enabledFeatureNames.emplace_back("deviceGeneratedComputeCaptureReplay"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV*>(header);
                if(pFeatures->spheres) { enabledFeatureNames.emplace_back("spheres"); }
                if(pFeatures->linearSweptSpheres) { enabledFeatureNames.emplace_back("linearSweptSpheres"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceLinearColorAttachmentFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceLinearColorAttachmentFeaturesNV*>(header);
                if(pFeatures->linearColorAttachment) { enabledFeatureNames.emplace_back("linearColorAttachment"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageCompressionControlSwapchainFeaturesEXT*>(header);
                if(pFeatures->imageCompressionControlSwapchain) { enabledFeatureNames.emplace_back("imageCompressionControlSwapchain"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageProcessingFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageProcessingFeaturesQCOM*>(header);
                if(pFeatures->textureSampleWeighted) { enabledFeatureNames.emplace_back("textureSampleWeighted"); }
                if(pFeatures->textureBoxFilter) { enabledFeatureNames.emplace_back("textureBoxFilter"); }
                if(pFeatures->textureBlockMatch) { enabledFeatureNames.emplace_back("textureBlockMatch"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceNestedCommandBufferFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceNestedCommandBufferFeaturesEXT*>(header);
                if(pFeatures->nestedCommandBuffer) { enabledFeatureNames.emplace_back("nestedCommandBuffer"); }
                if(pFeatures->nestedCommandBufferRendering) { enabledFeatureNames.emplace_back("nestedCommandBufferRendering"); }
                if(pFeatures->nestedCommandBufferSimultaneousUse) { enabledFeatureNames.emplace_back("nestedCommandBufferSimultaneousUse"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExtendedDynamicState3FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExtendedDynamicState3FeaturesEXT*>(header);
                if(pFeatures->extendedDynamicState3TessellationDomainOrigin) { enabledFeatureNames.emplace_back("extendedDynamicState3TessellationDomainOrigin"); }
                if(pFeatures->extendedDynamicState3DepthClampEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3DepthClampEnable"); }
                if(pFeatures->extendedDynamicState3PolygonMode) { enabledFeatureNames.emplace_back("extendedDynamicState3PolygonMode"); }
                if(pFeatures->extendedDynamicState3RasterizationSamples) { enabledFeatureNames.emplace_back("extendedDynamicState3RasterizationSamples"); }
                if(pFeatures->extendedDynamicState3SampleMask) { enabledFeatureNames.emplace_back("extendedDynamicState3SampleMask"); }
                if(pFeatures->extendedDynamicState3AlphaToCoverageEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3AlphaToCoverageEnable"); }
                if(pFeatures->extendedDynamicState3AlphaToOneEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3AlphaToOneEnable"); }
                if(pFeatures->extendedDynamicState3LogicOpEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3LogicOpEnable"); }
                if(pFeatures->extendedDynamicState3ColorBlendEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3ColorBlendEnable"); }
                if(pFeatures->extendedDynamicState3ColorBlendEquation) { enabledFeatureNames.emplace_back("extendedDynamicState3ColorBlendEquation"); }
                if(pFeatures->extendedDynamicState3ColorWriteMask) { enabledFeatureNames.emplace_back("extendedDynamicState3ColorWriteMask"); }
                if(pFeatures->extendedDynamicState3RasterizationStream) { enabledFeatureNames.emplace_back("extendedDynamicState3RasterizationStream"); }
                if(pFeatures->extendedDynamicState3ConservativeRasterizationMode) { enabledFeatureNames.emplace_back("extendedDynamicState3ConservativeRasterizationMode"); }
                if(pFeatures->extendedDynamicState3ExtraPrimitiveOverestimationSize) { enabledFeatureNames.emplace_back("extendedDynamicState3ExtraPrimitiveOverestimationSize"); }
                if(pFeatures->extendedDynamicState3DepthClipEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3DepthClipEnable"); }
                if(pFeatures->extendedDynamicState3SampleLocationsEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3SampleLocationsEnable"); }
                if(pFeatures->extendedDynamicState3ColorBlendAdvanced) { enabledFeatureNames.emplace_back("extendedDynamicState3ColorBlendAdvanced"); }
                if(pFeatures->extendedDynamicState3ProvokingVertexMode) { enabledFeatureNames.emplace_back("extendedDynamicState3ProvokingVertexMode"); }
                if(pFeatures->extendedDynamicState3LineRasterizationMode) { enabledFeatureNames.emplace_back("extendedDynamicState3LineRasterizationMode"); }
                if(pFeatures->extendedDynamicState3LineStippleEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3LineStippleEnable"); }
                if(pFeatures->extendedDynamicState3DepthClipNegativeOneToOne) { enabledFeatureNames.emplace_back("extendedDynamicState3DepthClipNegativeOneToOne"); }
                if(pFeatures->extendedDynamicState3ViewportWScalingEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3ViewportWScalingEnable"); }
                if(pFeatures->extendedDynamicState3ViewportSwizzle) { enabledFeatureNames.emplace_back("extendedDynamicState3ViewportSwizzle"); }
                if(pFeatures->extendedDynamicState3CoverageToColorEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageToColorEnable"); }
                if(pFeatures->extendedDynamicState3CoverageToColorLocation) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageToColorLocation"); }
                if(pFeatures->extendedDynamicState3CoverageModulationMode) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageModulationMode"); }
                if(pFeatures->extendedDynamicState3CoverageModulationTableEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageModulationTableEnable"); }
                if(pFeatures->extendedDynamicState3CoverageModulationTable) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageModulationTable"); }
                if(pFeatures->extendedDynamicState3CoverageReductionMode) { enabledFeatureNames.emplace_back("extendedDynamicState3CoverageReductionMode"); }
                if(pFeatures->extendedDynamicState3RepresentativeFragmentTestEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3RepresentativeFragmentTestEnable"); }
                if(pFeatures->extendedDynamicState3ShadingRateImageEnable) { enabledFeatureNames.emplace_back("extendedDynamicState3ShadingRateImageEnable"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceSubpassMergeFeedbackFeaturesEXT*>(header);
                if(pFeatures->subpassMergeFeedback) { enabledFeatureNames.emplace_back("subpassMergeFeedback"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderModuleIdentifierFeaturesEXT*>(header);
                if(pFeatures->shaderModuleIdentifier) { enabledFeatureNames.emplace_back("shaderModuleIdentifier"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceOpticalFlowFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceOpticalFlowFeaturesNV*>(header);
                if(pFeatures->opticalFlow) { enabledFeatureNames.emplace_back("opticalFlow"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceLegacyDitheringFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceLegacyDitheringFeaturesEXT*>(header);
                if(pFeatures->legacyDithering) { enabledFeatureNames.emplace_back("legacyDithering"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExternalFormatResolveFeaturesANDROID>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExternalFormatResolveFeaturesANDROID*>(header);
                if(pFeatures->externalFormatResolve) { enabledFeatureNames.emplace_back("externalFormatResolve"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAntiLagFeaturesAMD>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAntiLagFeaturesAMD*>(header);
                if(pFeatures->antiLag) { enabledFeatureNames.emplace_back("antiLag"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderObjectFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderObjectFeaturesEXT*>(header);
                if(pFeatures->shaderObject) { enabledFeatureNames.emplace_back("shaderObject"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTilePropertiesFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTilePropertiesFeaturesQCOM*>(header);
                if(pFeatures->tileProperties) { enabledFeatureNames.emplace_back("tileProperties"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAmigoProfilingFeaturesSEC>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAmigoProfilingFeaturesSEC*>(header);
                if(pFeatures->amigoProfiling) { enabledFeatureNames.emplace_back("amigoProfiling"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM*>(header);
                if(pFeatures->multiviewPerViewViewports) { enabledFeatureNames.emplace_back("multiviewPerViewViewports"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingInvocationReorderFeaturesNV*>(header);
                if(pFeatures->rayTracingInvocationReorder) { enabledFeatureNames.emplace_back("rayTracingInvocationReorder"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCooperativeVectorFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCooperativeVectorFeaturesNV*>(header);
                if(pFeatures->cooperativeVector) { enabledFeatureNames.emplace_back("cooperativeVector"); }
                if(pFeatures->cooperativeVectorTraining) { enabledFeatureNames.emplace_back("cooperativeVectorTraining"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceExtendedSparseAddressSpaceFeaturesNV*>(header);
                if(pFeatures->extendedSparseAddressSpace) { enabledFeatureNames.emplace_back("extendedSparseAddressSpace"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceLegacyVertexAttributesFeaturesEXT*>(header);
                if(pFeatures->legacyVertexAttributes) { enabledFeatureNames.emplace_back("legacyVertexAttributes"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderCoreBuiltinsFeaturesARM*>(header);
                if(pFeatures->shaderCoreBuiltins) { enabledFeatureNames.emplace_back("shaderCoreBuiltins"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT*>(header);
                if(pFeatures->pipelineLibraryGroupHandles) { enabledFeatureNames.emplace_back("pipelineLibraryGroupHandles"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT*>(header);
                if(pFeatures->dynamicRenderingUnusedAttachments) { enabledFeatureNames.emplace_back("dynamicRenderingUnusedAttachments"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDataGraphFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDataGraphFeaturesARM*>(header);
                if(pFeatures->dataGraph) { enabledFeatureNames.emplace_back("dataGraph"); }
                if(pFeatures->dataGraphUpdateAfterBind) { enabledFeatureNames.emplace_back("dataGraphUpdateAfterBind"); }
                if(pFeatures->dataGraphSpecializationConstants) { enabledFeatureNames.emplace_back("dataGraphSpecializationConstants"); }
                if(pFeatures->dataGraphDescriptorBuffer) { enabledFeatureNames.emplace_back("dataGraphDescriptorBuffer"); }
                if(pFeatures->dataGraphShaderModule) { enabledFeatureNames.emplace_back("dataGraphShaderModule"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM*>(header);
                if(pFeatures->multiviewPerViewRenderAreas) { enabledFeatureNames.emplace_back("multiviewPerViewRenderAreas"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePerStageDescriptorSetFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePerStageDescriptorSetFeaturesNV*>(header);
                if(pFeatures->perStageDescriptorSet) { enabledFeatureNames.emplace_back("perStageDescriptorSet"); }
                if(pFeatures->dynamicPipelineLayout) { enabledFeatureNames.emplace_back("dynamicPipelineLayout"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageProcessing2FeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageProcessing2FeaturesQCOM*>(header);
                if(pFeatures->textureBlockMatch2) { enabledFeatureNames.emplace_back("textureBlockMatch2"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCubicWeightsFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCubicWeightsFeaturesQCOM*>(header);
                if(pFeatures->selectableCubicWeights) { enabledFeatureNames.emplace_back("selectableCubicWeights"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceYcbcrDegammaFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceYcbcrDegammaFeaturesQCOM*>(header);
                if(pFeatures->ycbcrDegamma) { enabledFeatureNames.emplace_back("ycbcrDegamma"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCubicClampFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCubicClampFeaturesQCOM*>(header);
                if(pFeatures->cubicRangeClamp) { enabledFeatureNames.emplace_back("cubicRangeClamp"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT*>(header);
                if(pFeatures->attachmentFeedbackLoopDynamicState) { enabledFeatureNames.emplace_back("attachmentFeedbackLoopDynamicState"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDescriptorPoolOverallocationFeaturesNV*>(header);
                if(pFeatures->descriptorPoolOverallocation) { enabledFeatureNames.emplace_back("descriptorPoolOverallocation"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceTileMemoryHeapFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceTileMemoryHeapFeaturesQCOM*>(header);
                if(pFeatures->tileMemoryHeap) { enabledFeatureNames.emplace_back("tileMemoryHeap"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMemoryDecompressionFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMemoryDecompressionFeaturesEXT*>(header);
                if(pFeatures->memoryDecompression) { enabledFeatureNames.emplace_back("memoryDecompression"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRawAccessChainsFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRawAccessChainsFeaturesNV*>(header);
                if(pFeatures->shaderRawAccessChains) { enabledFeatureNames.emplace_back("shaderRawAccessChains"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCommandBufferInheritanceFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCommandBufferInheritanceFeaturesNV*>(header);
                if(pFeatures->commandBufferInheritance) { enabledFeatureNames.emplace_back("commandBufferInheritance"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderAtomicFloat16VectorFeaturesNV*>(header);
                if(pFeatures->shaderFloat16VectorAtomics) { enabledFeatureNames.emplace_back("shaderFloat16VectorAtomics"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderReplicatedCompositesFeaturesEXT*>(header);
                if(pFeatures->shaderReplicatedComposites) { enabledFeatureNames.emplace_back("shaderReplicatedComposites"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderFloat8FeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderFloat8FeaturesEXT*>(header);
                if(pFeatures->shaderFloat8) { enabledFeatureNames.emplace_back("shaderFloat8"); }
                if(pFeatures->shaderFloat8CooperativeMatrix) { enabledFeatureNames.emplace_back("shaderFloat8CooperativeMatrix"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingValidationFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingValidationFeaturesNV*>(header);
                if(pFeatures->rayTracingValidation) { enabledFeatureNames.emplace_back("rayTracingValidation"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePartitionedAccelerationStructureFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePartitionedAccelerationStructureFeaturesNV*>(header);
                if(pFeatures->partitionedAccelerationStructure) { enabledFeatureNames.emplace_back("partitionedAccelerationStructure"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDeviceGeneratedCommandsFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDeviceGeneratedCommandsFeaturesEXT*>(header);
                if(pFeatures->deviceGeneratedCommands) { enabledFeatureNames.emplace_back("deviceGeneratedCommands"); }
                if(pFeatures->dynamicGeneratedPipelineLayout) { enabledFeatureNames.emplace_back("dynamicGeneratedPipelineLayout"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceImageAlignmentControlFeaturesMESA>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceImageAlignmentControlFeaturesMESA*>(header);
                if(pFeatures->imageAlignmentControl) { enabledFeatureNames.emplace_back("imageAlignmentControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePushConstantBankFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePushConstantBankFeaturesNV*>(header);
                if(pFeatures->pushConstantBank) { enabledFeatureNames.emplace_back("pushConstantBank"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingInvocationReorderFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingInvocationReorderFeaturesEXT*>(header);
                if(pFeatures->rayTracingInvocationReorder) { enabledFeatureNames.emplace_back("rayTracingInvocationReorder"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDepthClampControlFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDepthClampControlFeaturesEXT*>(header);
                if(pFeatures->depthClampControl) { enabledFeatureNames.emplace_back("depthClampControl"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceHdrVividFeaturesHUAWEI>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceHdrVividFeaturesHUAWEI*>(header);
                if(pFeatures->hdrVivid) { enabledFeatureNames.emplace_back("hdrVivid"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCooperativeMatrix2FeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCooperativeMatrix2FeaturesNV*>(header);
                if(pFeatures->cooperativeMatrixWorkgroupScope) { enabledFeatureNames.emplace_back("cooperativeMatrixWorkgroupScope"); }
                if(pFeatures->cooperativeMatrixFlexibleDimensions) { enabledFeatureNames.emplace_back("cooperativeMatrixFlexibleDimensions"); }
                if(pFeatures->cooperativeMatrixReductions) { enabledFeatureNames.emplace_back("cooperativeMatrixReductions"); }
                if(pFeatures->cooperativeMatrixConversions) { enabledFeatureNames.emplace_back("cooperativeMatrixConversions"); }
                if(pFeatures->cooperativeMatrixPerElementOperations) { enabledFeatureNames.emplace_back("cooperativeMatrixPerElementOperations"); }
                if(pFeatures->cooperativeMatrixTensorAddressing) { enabledFeatureNames.emplace_back("cooperativeMatrixTensorAddressing"); }
                if(pFeatures->cooperativeMatrixBlockLoads) { enabledFeatureNames.emplace_back("cooperativeMatrixBlockLoads"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineOpacityMicromapFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineOpacityMicromapFeaturesARM*>(header);
                if(pFeatures->pipelineOpacityMicromap) { enabledFeatureNames.emplace_back("pipelineOpacityMicromap"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePerformanceCountersByRegionFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePerformanceCountersByRegionFeaturesARM*>(header);
                if(pFeatures->performanceCountersByRegion) { enabledFeatureNames.emplace_back("performanceCountersByRegion"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceVertexAttributeRobustnessFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceVertexAttributeRobustnessFeaturesEXT*>(header);
                if(pFeatures->vertexAttributeRobustness) { enabledFeatureNames.emplace_back("vertexAttributeRobustness"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFormatPackFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFormatPackFeaturesARM*>(header);
                if(pFeatures->formatPack) { enabledFeatureNames.emplace_back("formatPack"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE*>(header);
                if(pFeatures->fragmentDensityMapLayered) { enabledFeatureNames.emplace_back("fragmentDensityMapLayered"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePresentMeteringFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePresentMeteringFeaturesNV*>(header);
                if(pFeatures->presentMetering) { enabledFeatureNames.emplace_back("presentMetering"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT*>(header);
                if(pFeatures->zeroInitializeDeviceMemory) { enabledFeatureNames.emplace_back("zeroInitializeDeviceMemory"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShader64BitIndexingFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShader64BitIndexingFeaturesEXT*>(header);
                if(pFeatures->shader64BitIndexing) { enabledFeatureNames.emplace_back("shader64BitIndexing"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceCustomResolveFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceCustomResolveFeaturesEXT*>(header);
                if(pFeatures->customResolve) { enabledFeatureNames.emplace_back("customResolve"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDataGraphModelFeaturesQCOM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDataGraphModelFeaturesQCOM*>(header);
                if(pFeatures->dataGraphModel) { enabledFeatureNames.emplace_back("dataGraphModel"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderLongVectorFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderLongVectorFeaturesEXT*>(header);
                if(pFeatures->longVector) { enabledFeatureNames.emplace_back("longVector"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePipelineCacheIncrementalModeFeaturesSEC>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePipelineCacheIncrementalModeFeaturesSEC*>(header);
                if(pFeatures->pipelineCacheIncrementalMode) { enabledFeatureNames.emplace_back("pipelineCacheIncrementalMode"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT*>(header);
                if(pFeatures->shaderUniformBufferUnsizedArray) { enabledFeatureNames.emplace_back("shaderUniformBufferUnsizedArray"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceComputeOccupancyPriorityFeaturesNV>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceComputeOccupancyPriorityFeaturesNV*>(header);
                if(pFeatures->computeOccupancyPriority) { enabledFeatureNames.emplace_back("computeOccupancyPriority"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderSubgroupPartitionedFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderSubgroupPartitionedFeaturesEXT*>(header);
                if(pFeatures->shaderSubgroupPartitioned) { enabledFeatureNames.emplace_back("shaderSubgroupPartitioned"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE*>(header);
                if(pFeatures->shaderMixedFloatDotProductFloat16AccFloat32) { enabledFeatureNames.emplace_back("shaderMixedFloatDotProductFloat16AccFloat32"); }
                if(pFeatures->shaderMixedFloatDotProductFloat16AccFloat16) { enabledFeatureNames.emplace_back("shaderMixedFloatDotProductFloat16AccFloat16"); }
                if(pFeatures->shaderMixedFloatDotProductBFloat16Acc) { enabledFeatureNames.emplace_back("shaderMixedFloatDotProductBFloat16Acc"); }
                if(pFeatures->shaderMixedFloatDotProductFloat8AccFloat32) { enabledFeatureNames.emplace_back("shaderMixedFloatDotProductFloat8AccFloat32"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceThrottleHintFeaturesSEC>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceThrottleHintFeaturesSEC*>(header);
                if(pFeatures->throttleHint) { enabledFeatureNames.emplace_back("throttleHint"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM*>(header);
                if(pFeatures->dataGraphNeuralAcceleratorStatistics) { enabledFeatureNames.emplace_back("dataGraphNeuralAcceleratorStatistics"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDevicePrimitiveRestartIndexFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDevicePrimitiveRestartIndexFeaturesEXT*>(header);
                if(pFeatures->primitiveRestartIndex) { enabledFeatureNames.emplace_back("primitiveRestartIndex"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceAccelerationStructureFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceAccelerationStructureFeaturesKHR*>(header);
                if(pFeatures->accelerationStructure) { enabledFeatureNames.emplace_back("accelerationStructure"); }
                if(pFeatures->accelerationStructureCaptureReplay) { enabledFeatureNames.emplace_back("accelerationStructureCaptureReplay"); }
                if(pFeatures->accelerationStructureIndirectBuild) { enabledFeatureNames.emplace_back("accelerationStructureIndirectBuild"); }
                if(pFeatures->accelerationStructureHostCommands) { enabledFeatureNames.emplace_back("accelerationStructureHostCommands"); }
                if(pFeatures->descriptorBindingAccelerationStructureUpdateAfterBind) { enabledFeatureNames.emplace_back("descriptorBindingAccelerationStructureUpdateAfterBind"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayTracingPipelineFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayTracingPipelineFeaturesKHR*>(header);
                if(pFeatures->rayTracingPipeline) { enabledFeatureNames.emplace_back("rayTracingPipeline"); }
                if(pFeatures->rayTracingPipelineShaderGroupHandleCaptureReplay) { enabledFeatureNames.emplace_back("rayTracingPipelineShaderGroupHandleCaptureReplay"); }
                if(pFeatures->rayTracingPipelineShaderGroupHandleCaptureReplayMixed) { enabledFeatureNames.emplace_back("rayTracingPipelineShaderGroupHandleCaptureReplayMixed"); }
                if(pFeatures->rayTracingPipelineTraceRaysIndirect) { enabledFeatureNames.emplace_back("rayTracingPipelineTraceRaysIndirect"); }
                if(pFeatures->rayTraversalPrimitiveCulling) { enabledFeatureNames.emplace_back("rayTraversalPrimitiveCulling"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceRayQueryFeaturesKHR>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceRayQueryFeaturesKHR*>(header);
                if(pFeatures->rayQuery) { enabledFeatureNames.emplace_back("rayQuery"); }
                // clang-format on
                break;
            }
            case gfxrecon::util::GetSType<VkPhysicalDeviceMeshShaderFeaturesEXT>():
            {
                // clang-format off
                const auto* pFeatures = reinterpret_cast<const VkPhysicalDeviceMeshShaderFeaturesEXT*>(header);
                if(pFeatures->taskShader) { enabledFeatureNames.emplace_back("taskShader"); }
                if(pFeatures->meshShader) { enabledFeatureNames.emplace_back("meshShader"); }
                if(pFeatures->multiviewMeshShader) { enabledFeatureNames.emplace_back("multiviewMeshShader"); }
                if(pFeatures->primitiveFragmentShadingRateMeshShader) { enabledFeatureNames.emplace_back("primitiveFragmentShadingRateMeshShader"); }
                if(pFeatures->meshShaderQueries) { enabledFeatureNames.emplace_back("meshShaderQueries"); }
                // clang-format on
                break;
            }
            default:
            {
                LogUnsupportedPNext(*header->sType);
                break;
            }
        }
        pnext = header->pNext;
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
