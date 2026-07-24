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

#ifndef VULKAN_SQLITE_PREPARED_STATEMENTS_H
#define VULKAN_SQLITE_PREPARED_STATEMENTS_H

#include "util/defines.h"
#include "sqlite_utils.h"
#include "decode/field_info.h"
#include "decode/consumer_utils.h"
#include "format/platform_types.h"
#include "vulkan/vulkan.h"

#include <span>
#include <string_view>
#include <optional>

#include "sqlite3.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

struct VulkanSqliteConsumerContext;

struct PipelineLibraryFlagsLookup
{
    bool found = false;
    std::optional<int64_t> flags;
    std::optional<int64_t> libraryFlags;
    std::optional<int64_t> renderPassId;
};

struct GraphicsPipelineVertexInputStateLookup
{
    bool found = false;
    std::optional<int64_t> vertexInputStateId;
    std::optional<int64_t> inputAssemblyStateId;
};

struct GraphicsPipelinePreRasterizationShaderStateLookup
{
    bool found = false;
    std::optional<int64_t> viewportStateId;
    std::optional<int64_t> rasterizationStateId;
    std::optional<int64_t> tessellationStateId;
    int64_t numShaderStages = 0;
};

struct GraphicsPipelineFragmentShaderStateLookup
{
    bool found = false;
    std::optional<int64_t> depthStencilStateId;
    int64_t numShaderStages = 0;
};

struct GraphicsPipelineFragmentOutputStateLookup
{
    bool found = false;
    std::optional<int64_t> colorBlendStateId;
};

struct GraphicsPipelineMultisampleStateLookup
{
    bool found = false;
    std::optional<int64_t> multisampleStateId;
};

struct VulkanSqlitePreparedStatements
{
    VulkanSqlitePreparedStatements(sqlite3* db) : db(db) {}

    sqlite3* db = nullptr;
    VulkanSqliteConsumerContext* context = nullptr;

    // Base statements (originally from VulkanSqliteConsumerBase)
    SqliteStatement frameInsertStatement;
    SqliteStatement apiEventVkInsertStatement;
    SqliteStatement apiEventMetaInsertStatement;
    SqliteStatement apiEventReturnsInsertStatement;
    SqliteStatement functionNameInsertStatement;
    SqliteStatement commandPoolInsertStatement;
    SqliteStatement commandBufferInsertStatement;
    SqliteStatement commandBufferInheritanceInfoInsertStatement;
    SqliteStatement commandBufferCommandInsertStatement;
    SqliteStatement trackedCmdCommandInsertStatement;
    SqliteStatement commandBufferRecordingInsertStatement;
    SqliteStatement commandBufferRecordingEndStatement;
    SqliteStatement commandBufferRecordingResetStatement;
    SqliteStatement renderPassRecordingInsertStatement;
    SqliteStatement renderPassRecordingEndStatement;
    SqliteStatement renderPassRecordingClearValueInsertStatement;
    SqliteStatement renderSubpassRecordingInsertStatement;
    SqliteStatement renderSubpassRecordingEndStatement;
    SqliteStatement secondaryCommandBufferExecutionRecordingInsertStatement;
    SqliteStatement cmdDrawRecordingInsertStatement;
    SqliteStatement cmdMeshTaskRecordingInsertStatement;
    SqliteStatement cmdClusterRecordingInsertStatement;
    SqliteStatement cmdDispatchRecordingInsertStatement;
    SqliteStatement cmdRaytracingRecordingInsertStatement;
    SqliteStatement cmdDrawRecordingIndirectInfoInsertStatement;
    SqliteStatement cmdDrawRecordingInfoInsertStatement;
    SqliteStatement cmdMeshTaskRecordingIndirectInfoInsertStatement;
    SqliteStatement cmdMeshTaskRecordingInfoInsertStatement;
    SqliteStatement cmdClusterRecordingIndirectInfoInsertStatement;
    SqliteStatement cmdClusterRecordingInfoInsertStatement;
    SqliteStatement cmdDispatchRecordingIndirectInfoInsertStatement;
    SqliteStatement cmdDispatchRecordingBaseInfoInsertStatement;
    SqliteStatement cmdDispatchRecordingInfoInsertStatement;
    SqliteStatement displayMessageInsertStatement;
    SqliteStatement memoryInsertStatement;
    SqliteStatement annotationInsertStatement;
    SqliteStatement freeCommandBufferUpdateStatement;
    SqliteStatement destroyCommandPoolUpdateStatement;
    SqliteStatement surfaceInsertStatement;
    SqliteStatement destroySurfaceUpdateStatement;
    SqliteStatement destroyRenderPassUpdateStatement;

    // Base statements (originally from VulkanSqliteConsumerContext)
    SqliteStatement structMemberInsertStatement;
    SqliteStatement arrayMemberInsertStatement;
    SqliteStatement apiEventArgumentInsertStatement;
    SqliteStatement structInsertStatement;
    SqliteStatement arrayInsertStatement;

    // Advanced statements (originally from VulkanSqliteConsumerExt)
    SqliteStatement instanceInsertStatement;
    SqliteStatement instanceEnabledLayerInsertStatement;
    SqliteStatement instanceEnabledLayerSettingInsertStatement;
    SqliteStatement instanceEnabledLayerSettingValueInsertStatement;
    SqliteStatement instanceEnabledExtensionInsertStatement;
    SqliteStatement instanceValidationEnabledFeatureInsertStatement;
    SqliteStatement instanceValidationDisabledFeatureInsertStatement;
    SqliteStatement instanceValidationDisabledCheckInsertStatement;
    SqliteStatement deviceInsertStatement;
    SqliteStatement deviceEnabledLayerInsertStatement;
    SqliteStatement deviceEnabledExtensionInsertStatement;
    SqliteStatement deviceEnabledFeatureInsertStatement;
    SqliteStatement trackedDeviceCommandInsertStatement;
    SqliteStatement dynamicRenderPassRecordingInsertStatement;
    SqliteStatement dynamicRenderPassRecordingEndStatement;
    SqliteStatement unionColorInsertStatement;
    SqliteStatement renderingAttachmentInsertStatement;
    SqliteStatement dynamicColorAttachmentInsertStatement;
    SqliteStatement renderPassRecordingAttachmentInsertStatement;
    SqliteStatement stateIdInsertStatement;
    SqliteStatement stateGroupEntryInsertStatement;
    SqliteStatement statePipelineBindingInsertStatement;
    SqliteStatement stateShaderObjectBindingInsertStatement;
    SqliteStatement stateIndexBufferBindingInsertStatement;
    SqliteStatement stateVertexBufferBindingInsertStatement;
    SqliteStatement stateDescriptorSetBindingInsertStatement;
    SqliteStatement stateDescriptorSetBindingDynamicOffsetInsertStatement;
    SqliteStatement stateDescriptorSetPushInsertStatement;
    SqliteStatement stateDynamicVertexInputBindingDescriptionInsertStatement;
    SqliteStatement stateDynamicVertexInputAttributeDescriptionInsertStatement;
    SqliteStatement stateDynamicViewportInsertStatement;
    SqliteStatement stateDynamicScissorInsertStatement;
    SqliteStatement stateDynamicRenderingColorAttachmentLocationInsertStatement;
    SqliteStatement stateDynamicRenderingInputColorAttachmentIndexInsertStatement;
    SqliteStatement stateDynamicRenderingInputDepthAttachmentIndexInsertStatement;
    SqliteStatement stateDynamicRenderingInputStencilAttachmentIndexInsertStatement;
    SqliteStatement stateDynamicLineWidthInsertStatement;
    SqliteStatement stateDynamicDepthBoundsInsertStatement;
    SqliteStatement stateDynamicDepthBoundsTestEnableInsertStatement;
    SqliteStatement stateDynamicDepthBiasInsertStatement;
    SqliteStatement stateDynamicDepthBiasEnableInsertStatement;
    SqliteStatement stateDynamicDepthTestEnableInsertStatement;
    SqliteStatement stateDynamicDepthWriteEnableInsertStatement;
    SqliteStatement stateDynamicDepthCompareOpInsertStatement;
    SqliteStatement stateDynamicStencilCompareMaskFrontInsertStatement;
    SqliteStatement stateDynamicStencilCompareMaskBackInsertStatement;
    SqliteStatement stateDynamicStencilWriteMaskFrontInsertStatement;
    SqliteStatement stateDynamicStencilWriteMaskBackInsertStatement;
    SqliteStatement stateDynamicStencilReferenceFrontInsertStatement;
    SqliteStatement stateDynamicStencilReferenceBackInsertStatement;
    SqliteStatement stateDynamicStencilTestEnableInsertStatement;
    SqliteStatement stateDynamicStencilOpsFrontInsertStatement;
    SqliteStatement stateDynamicStencilOpsBackInsertStatement;
    SqliteStatement stateDynamicColorWriteEnableInsertStatement;
    SqliteStatement stateDynamicBlendConstantInsertStatement;
    SqliteStatement stateDynamicPrimitiveTopologyInsertStatement;
    SqliteStatement stateDynamicCullModeInsertStatement;
    SqliteStatement stateDynamicFrontFaceInsertStatement;
    SqliteStatement stateDynamicLogicOpInsertStatement;
    SqliteStatement stateDynamicRasterizerDiscardEnableInsertStatement;
    SqliteStatement stateDynamicPatchControlPointInsertStatement;
    SqliteStatement stateDynamicPrimitiveRestartEnableInsertStatement;
    SqliteStatement imageInsertStatement;
    SqliteStatement imageViewFormatInsertStatement;
    SqliteStatement imageViewInsertStatement;
    SqliteStatement samplerInsertStatement;
    SqliteStatement swapchainInsertStatement;
    SqliteStatement swapchainImageInsertStatement;
    SqliteStatement bufferInsertStatement;
    SqliteStatement bufferViewInsertStatement;
    SqliteStatement descriptorUpdateTemplateInsertStatement;
    SqliteStatement descriptorUpdateTemplateEntryInsertStatement;
    SqliteStatement descriptorSetWriteInsertStatement;
    SqliteStatement descriptorSetWriteImageInfoInsertStatement;
    SqliteStatement descriptorSetWriteBufferInfoInsertStatement;
    SqliteStatement descriptorSetWriteTexelInfoInsertStatement;
    SqliteStatement descriptorSetWriteAccelerationInfoInsertStatement;
    SqliteStatement descriptorSetWriteAccelerationNvInfoInsertStatement;
    SqliteStatement descriptorSetCopyImageInfoInsertStatement;
    SqliteStatement descriptorSetCopyBufferInfoInsertStatement;
    SqliteStatement descriptorSetCopyTexelInfoInsertStatement;
    SqliteStatement descriptorSetCopyAccelerationInfoInsertStatement;
    SqliteStatement descriptorSetCopyAccelerationNvInfoInsertStatement;
    SqliteStatement stateDescriptorSetPushImageInfoInsertStatement;
    SqliteStatement stateDescriptorSetPushBufferInfoInsertStatement;
    SqliteStatement stateDescriptorSetPushTexelInfoInsertStatement;
    SqliteStatement stateDescriptorSetPushAccelerationInfoInsertStatement;
    SqliteStatement stateDescriptorSetPushAccelerationNvInfoInsertStatement;
    SqliteStatement freePoolDescriptorSetsUpdateStatement;
    SqliteStatement freeDescriptorSetUpdateStatement;
    SqliteStatement destroyDebugReportCallbackUpdateStatement;
    SqliteStatement destroyDebugMessengerUpdateStatement;
    SqliteStatement destroyInstanceUpdateStatement;
    SqliteStatement destroyDeviceUpdateStatement;
    SqliteStatement destroyFenceUpdateStatement;
    SqliteStatement destroySemaphoreUpdateStatement;
    SqliteStatement destroyEventUpdateStatement;
    SqliteStatement destroyQueryPoolUpdateStatement;
    SqliteStatement destroyShaderObjectUpdateStatement;
    SqliteStatement destroyShaderModuleUpdateStatement;
    SqliteStatement destroyPipelineAnonymousShaderModulesUpdateStatement;
    SqliteStatement destroyValidationCacheUpdateStatement;
    SqliteStatement destroyPipelineCacheUpdateStatement;
    SqliteStatement destroyPipelineUpdateStatement;
    SqliteStatement destroyPipelineLayoutUpdateStatement;
    SqliteStatement destroyDescriptorSetLayoutUpdateStatement;
    SqliteStatement destroyDescriptorPoolUpdateStatement;
    SqliteStatement destroySamplerYcbcrConversionUpdateStatement;
    SqliteStatement destroyPrivateDataSlotUpdateStatement;
    SqliteStatement destroyDescriptorUpdateTemplateUpdateStatement;
    SqliteStatement destroyBufferUpdateStatement;
    SqliteStatement destroyBufferViewUpdateStatement;
    SqliteStatement destroyImageUpdateStatement;
    SqliteStatement destroyImageViewUpdateStatement;
    SqliteStatement destroySamplerUpdateStatement;
    SqliteStatement destroySwapchainUpdateStatement;
    SqliteStatement destroySwapchainImagesUpdateStatement;
    SqliteStatement destroyFramebufferUpdateStatement;
    SqliteStatement destroyAccelerationStructureUpdateStatement;
    SqliteStatement destroyAccelerationStructureNvUpdateStatement;
    SqliteStatement accelerationStructureInsertStatement;
    SqliteStatement accelerationStructureNvInsertStatement;
    SqliteStatement accelerationStructureBuildInsertStatement;
    SqliteStatement accelerationStructureBuildGeometryInfoInsertStatement;
    SqliteStatement accelerationStructureBuildGeometryInsertStatement;
    SqliteStatement accelerationStructureBuildRangeInfoInsertStatement;
    SqliteStatement accelerationStructureBuildTriangleDataInsertStatement;
    SqliteStatement accelerationStructureBuildAabbDataInsertStatement;
    SqliteStatement accelerationStructureBuildInstanceDataInsertStatement;
    SqliteStatement accelerationStructureCopyInsertStatement;
    SqliteStatement transferCommandInsertStatement;
    SqliteStatement transferCommandBufferCopyUpdateStatement;
    SqliteStatement transferCommandImageCopyUpdateStatement;
    SqliteStatement transferCommandBufferToImageUpdateStatement;
    SqliteStatement transferCommandImageToBufferUpdateStatement;
    SqliteStatement transferCommandBlitUpdateStatement;
    SqliteStatement transferCommandRegionBufferCopiesInsertStatement;
    SqliteStatement transferCommandRegionImageCopiesInsertStatement;
    SqliteStatement transferCommandRegionBufferImageCopiesInsertStatement;
    SqliteStatement destroyDeferredOperationUpdateStatement;
    SqliteStatement destroyPipelineBinaryUpdateStatement;
    SqliteStatement videoSessionInsertStatement;
    SqliteStatement destroyVideoSessionUpdateStatement;
    SqliteStatement videoSessionParametersInsertStatement;
    SqliteStatement destroyVideoSessionParametersUpdateStatement;
    SqliteStatement indirectCommandsLayoutInsertStatement;
    SqliteStatement destroyIndirectCommandsLayoutUpdateStatement;
    SqliteStatement micromapInsertStatement;
    SqliteStatement destroyMicromapUpdateStatement;
    SqliteStatement opticalFlowSessionInsertStatement;
    SqliteStatement destroyOpticalFlowSessionUpdateStatement;
    SqliteStatement renderPassInsertStatement;
    SqliteStatement renderPassAttachmentInsertStatement;
    SqliteStatement renderSubpassInsertStatement;
    SqliteStatement renderSubpassBlankAttachmentReferencesInsertStatement;
    SqliteStatement renderSubpassSetAttachmentReferenceInputLayoutUpdateStatement;
    SqliteStatement renderSubpassSetAttachmentReferenceColorLayoutUpdateStatement;
    SqliteStatement renderSubpassSetAttachmentReferenceResolveLayoutUpdateStatement;
    SqliteStatement renderSubpassSetAttachmentReferenceDepthStencilLayoutUpdateStatement;
    SqliteStatement renderSubpassSetAttachmentReferencePreserveUpdateStatement;
    SqliteStatement renderSubpassDependenciesInsertStatement;
    SqliteStatement queuePresentInsertStatement;
    SqliteStatement queuePresentRectInsertStatement;
    SqliteStatement queuePresentSemaphoreWaitInsertStatement;
    SqliteStatement queuePresentSwapchainInsertStatement;
    SqliteStatement queuePresentSwapchainRegionInsertStatement;
    SqliteStatement debugReportCallbackInsertStatement;
    SqliteStatement debugMessengerInsertStatement;
    SqliteStatement debugNameInsertStatement;
    SqliteStatement debugTagInsertStatement;
    SqliteStatement debugLabelQueueBeginInsertStatement;
    SqliteStatement debugLabelQueueInsertInsertStatement;
    SqliteStatement debugLabelCmdBeginInsertStatement;
    SqliteStatement debugLabelCmdInsertInsertStatement;
    SqliteStatement debugLabelCmdEndStubInsertStatement;
    SqliteStatement debugLabelQueueEndUpdateStatement;
    SqliteStatement debugLabelCmdEndUpdateStatement;
    SqliteStatement physicalDeviceInsertStatement;
    SqliteStatement queueInsertStatement;
    SqliteStatement queueSubmitInsertStatement;
    SqliteStatement queueSubmitBatchInsertStatement;
    SqliteStatement queueSubmitBufferInsertStatement;
    SqliteStatement queueSubmitSemaphoreWaitInsertStatement;
    SqliteStatement queueSubmitSemaphoreSignalInsertStatement;
    SqliteStatement fenceInsertStatement;
    SqliteStatement fenceSyncScopeInsertStatement;
    SqliteStatement resetFenceSyncScopeUpdateStatement;
    SqliteStatement waitFenceSyncScopeUpdateStatement;
    SqliteStatement semaphoreInsertStatement;
    SqliteStatement semaphoreSignalInsertStatement;
    SqliteStatement semaphoreWaitInsertStatement;
    SqliteStatement eventInsertStatement;
    SqliteStatement queryPoolInsertStatement;

    SqliteStatement shaderObjectInsertStatement;
    SqliteStatement shaderObjectDescriptorSetLayoutInsertStatement;
    SqliteStatement shaderObjectPushConstantRangeInsertStatement;

    SqliteStatement shaderModuleInsertStatement;
    SqliteStatement shaderModuleWithStringHandleInsertStatement;
    SqliteStatement pipelineStageInsertStatement;
    SqliteStatement pipelineStageFromLibraryInsertStatement;
    SqliteStatement pipelineStagesExcludingStageFromLibraryInsertStatement;
    SqliteStatement pipelineLibraryFlagsLookupStatement;
    SqliteStatement graphicsPipelineVertexInputStateLookupStatement;
    SqliteStatement graphicsPipelinePreRasterizationShaderStateLookupStatement;
    SqliteStatement graphicsPipelineFragmentShaderStateLookupStatement;
    SqliteStatement graphicsPipelineFragmentOutputStateLookupStatement;
    SqliteStatement graphicsPipelineMultisampleStateLookupStatement;

    SqliteStatement validationCacheInsertStatement;
    SqliteStatement pipelineCacheInsertStatement;
    SqliteStatement pipelineLayoutInsertStatement;
    SqliteStatement pipelineDescriptorSetLayoutInsertStatement;
    SqliteStatement pipelinePushConstantRangeInsertStatement;

    SqliteStatement descriptorSetLayoutInsertStatement;
    SqliteStatement descriptorSetLayoutBindingInsertStatement;
    SqliteStatement descriptorPoolInsertStatement;
    SqliteStatement descriptorSetInsertStatement;

    SqliteStatement vertexInputStateInsertStatement;
    SqliteStatement vertexInputStateBindingDescriptionInsertStatement;
    SqliteStatement vertexInputStateBindingDescriptionFromLibraryInsertStatement;
    SqliteStatement vertexInputStateAttributeDescriptionInsertStatement;
    SqliteStatement vertexInputStateAttributeDescriptionFromLibraryInsertStatement;
    SqliteStatement inputAssemblyStateInsertStatement;
    SqliteStatement inputAssemblyStateFromLibraryInsertStatement;
    SqliteStatement tessellationStateInsertStatement;
    SqliteStatement tessellationStateFromLibraryInsertStatement;
    SqliteStatement viewportStateInsertStatement;
    SqliteStatement viewportStateFromLibraryInsertStatement;
    SqliteStatement viewportStateViewportInsertStatement;
    SqliteStatement viewportStateViewportFromLibraryInsertStatement;
    SqliteStatement viewportStateScissorInsertStatement;
    SqliteStatement viewportStateScissorFromLibraryInsertStatement;
    SqliteStatement rasterizationStateInsertStatement;
    SqliteStatement rasterizationStateFromLibraryInsertStatement;
    SqliteStatement depthStencilStateInsertStatement;
    SqliteStatement depthStencilStateFromLibraryInsertStatement;
    SqliteStatement colorBlendStateInsertStatement;
    SqliteStatement colorBlendStateFromLibraryInsertStatement;
    SqliteStatement colorBlendStateAttachmentStateInsertStatement;
    SqliteStatement colorBlendStateAttachmentStateFromLibraryInsertStatement;
    SqliteStatement pipelineDynamicStateInsertStatement;
    SqliteStatement pipelineDynamicStateFromLibraryInsertStatement;
    SqliteStatement multisampleStateInsertStatement;
    SqliteStatement multisampleStateFromLibraryInsertStatement;
    SqliteStatement multisampleStateSampleMaskInsertStatement;
    SqliteStatement multisampleStateSampleMasksFromLibraryInsertStatement;

    SqliteStatement pipelineGraphicsInsertStatement;
    SqliteStatement pipelineComputeInsertStatement;
    SqliteStatement pipelineRayTracingNVInsertStatement;
    SqliteStatement pipelineRayTracingInsertStatement;
    SqliteStatement pipelineColorAttachmentFormatInsertStatement;
    SqliteStatement pipelineLibraryInsertStatement;
    SqliteStatement graphicsPipelineInfoInsertStatement;
    SqliteStatement computePipelineInfoInsertStatement;
    SqliteStatement raytracingPipelineInfoInsertStatement;
    SqliteStatement raytracingShaderGroupInsertStatement;

    SqliteStatement pipelineDataGraphInsertStatement;
    SqliteStatement dataGraphPipelineInfoInsertStatement;
    SqliteStatement dataGraphPipelineResourceInfoInsertStatement;
    SqliteStatement dataGraphPipelineSessionInsertStatement;
    SqliteStatement destroyDataGraphPipelineSessionUpdateStatement;
    SqliteStatement cmdDataGraphDispatchRecordingInsertStatement;
    SqliteStatement cmdDataGraphDispatchRecordingInfoInsertStatement;

    SqliteStatement displayInsertStatement;
    SqliteStatement displayModeInsertStatement;
    SqliteStatement acquireNextImageInsertStatement;

    SqliteStatement framebufferInsertStatement;
    SqliteStatement framebufferAttachmentInfoInsertStatement;
    SqliteStatement framebufferAttachmentWithInfoInsertStatement;
    SqliteStatement framebufferAttachmentWithImageViewInsertStatement;
    SqliteStatement samplerYcbcrConversionInsertStatement;
    SqliteStatement privateDataSlotInsertStatement;
    SqliteStatement deferredOperationInsertStatement;
    SqliteStatement pipelineBinaryInsertStatement;

    void CreateBasePreparedStatements();
    void CreateAdvancedPreparedStatements();

    template <typename T>
    void RecordField(
        const FieldInfo& fieldInfo,
        const size_t fieldIndex,
        const std::string_view fieldName,
        const std::string_view fieldType,
        const T value
    );

    template <typename T>
        requires(!invalid_arg_type<T>)
    void InsertStructMember(
        const uint64_t structId,
        const size_t fieldIndex,
        const std::string_view fieldName,
        const std::string_view fieldType,
        const T value
    );

    template <typename T>
    void InsertArrayMember(
        const uint64_t arrayId, const uint64_t arrayIndex, const std::string_view fieldType, const T value
    );

    template <typename T>
    void InsertAPIEventArgument(
        const uint64_t eventId,
        const size_t fieldIndex,
        const std::string_view fieldName,
        const std::string_view fieldType,
        const T value
    );

    int64_t InsertStruct(const std::string_view type);
    int64_t InsertArray(const std::string_view type);
    int64_t InsertDebugReportCallback(const int64_t callbackHandle, const uint32_t flags, const uint64_t apiEventId);
    void InsertDebugMessenger(
        const format::HandleId messenger, const uint32_t severity, const uint32_t type, const uint64_t apiEventId
    );
    void InsertDebugName(
        const std::string_view objectName,
        const int64_t objectHandle,
        const std::optional<int64_t> objectType,
        const std::optional<int64_t> objectMarkerType,
        const format::HandleId device,
        const uint64_t apiEventId
    );
    void InsertDebugTag(
        const uint64_t name,
        const uint64_t size,
        const int64_t objectHandle,
        const std::optional<int64_t> objectType,
        const std::optional<int64_t> objectMarkerType,
        const format::HandleId device,
        const uint64_t apiEventId
    );
    void InsertDebugLabelQueueBegin(
        const format::HandleId queue,
        const std::string_view name,
        std::span<const float, 4> color,
        const uint64_t apiEventId
    );
    void InsertDebugLabelQueueInsert(
        const format::HandleId queue,
        const std::string_view name,
        std::span<const float, 4> color,
        const uint64_t apiEventId
    );
    void InsertDebugLabelCmdBegin(
        const std::string_view name,
        std::span<const float, 4> color,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId,
        const uint64_t apiEventId
    );
    void InsertDebugLabelCmdInsert(
        const std::string_view name,
        std::span<const float, 4> color,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId,
        const uint64_t apiEventId
    );
    void InsertDebugLabelCmdEndStub(
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> endRenderPassRecordingId,
        const std::optional<int64_t> endRenderSubpassRecordingId,
        const std::optional<int64_t> endDynamicRenderPassRecordingId,
        const uint64_t apiEventId
    );
    void UpdateDebugLabelEnd(const int64_t labelId, const uint64_t apiEventId);
    void UpdateDebugLabelCmdEnd(
        const int64_t labelId,
        const uint64_t apiEventId,
        const std::optional<int64_t> endRenderPassRecordingId,
        const std::optional<int64_t> endRenderSubpassRecordingId,
        const std::optional<int64_t> endDynamicRenderPassRecordingId
    );
    int64_t InsertPhysicalDevice(
        const format::HandleId physicalDevice, const std::optional<int64_t> instanceId, const uint64_t apiEventId
    );
    int64_t InsertQueue(
        const int64_t queueHandle,
        const uint32_t flags,
        const uint32_t queueFamilyIndex,
        const uint32_t queueIndex,
        const float priority,
        const format::HandleId device
    );
    int64_t InsertQueueSubmit(
        const int64_t queueId,
        const std::optional<int64_t> fenceSyncScopeId,
        const uint64_t frame,
        const uint64_t apiEventId
    );
    int64_t InsertQueueSubmitBatch(
        const int64_t queueSubmitId,
        const uint64_t batchIndex,
        const std::optional<int64_t> firstDrawTimestamp,
        const std::optional<int64_t> swapBufferTimestamp
    );
    void InsertQueueSubmitBuffer(
        const int64_t queueSubmitBatchId,
        const uint64_t bufferIndex,
        const std::optional<int64_t> commandBufferRecordingId
    );
    void InsertQueueSubmitSemaphoreWait(
        const int64_t queueSubmitBatchId,
        const uint64_t waitIndex,
        const std::optional<int64_t> waitStage,
        const std::optional<int64_t> value,
        const std::optional<int64_t> semaphoreId
    );
    void InsertQueueSubmitSemaphoreSignal(
        const int64_t queueSubmitBatchId,
        const uint64_t signalIndex,
        const std::optional<int64_t> value,
        const std::optional<int64_t> semaphoreId
    );
    int64_t InsertFence(
        const format::HandleId fence,
        const format::HandleId device,
        const uint32_t flags,
        const std::optional<int64_t> handleTypes,
        const uint64_t apiEventId
    );
    void InsertFenceSyncScope(const int64_t fenceHandle, const int64_t fenceId, const uint64_t apiEventId);
    void ResetFenceSyncScope(const int64_t instanceId, const uint64_t apiEventId);
    void WaitFenceSyncScope(const int64_t instanceId, const uint64_t apiEventId);
    int64_t InsertSemaphore(
        const format::HandleId semaphore,
        const format::HandleId device,
        const uint32_t semaphoreType,
        const uint64_t initialValue,
        const std::optional<int64_t> handleTypes,
        const uint64_t apiEventId
    );
    void InsertSemaphoreSignal(
        const std::optional<int64_t> semaphoreId, const uint64_t value, const uint64_t apiEventId
    );
    void InsertSemaphoreWait(
        const format::HandleId semaphore,
        const uint64_t value,
        const uint64_t waitIndex,
        const uint32_t waitFlags,
        const uint64_t timeout,
        const uint64_t apiEventId
    );
    void InsertEvent(
        const format::HandleId event, const format::HandleId device, const uint32_t flags, const uint64_t apiEventId
    );
    void InsertQueryPool(
        const format::HandleId queryPool,
        const format::HandleId device,
        const uint32_t flags,
        const uint32_t queryType,
        const uint32_t queryCount,
        const uint32_t pipelineStatistics,
        const uint64_t apiEventId
    );

    int64_t InsertShaderObject(
        const format::HandleId shader,
        const format::HandleId device,
        const uint32_t flags,
        const uint32_t stage,
        const uint32_t nextStage,
        const uint32_t codeType,
        const uint64_t codeSize,
        const std::string_view entryPointName,
        const uint64_t apiEventId
    );
    void InsertShaderObjectDescriptorSetLayout(
        const int64_t shaderObjectId, const uint64_t setIndex, const std::optional<int64_t> layoutId
    );
    void InsertShaderObjectPushConstantRange(
        const int64_t shaderObjectId,
        const uint64_t rangeIndex,
        const uint32_t stageFlags,
        const uint32_t offset,
        const uint32_t size
    );

    void InsertShaderModule(
        const format::HandleId shaderModule,
        const format::HandleId device,
        const uint64_t codeSize,
        const uint64_t apiEventId
    );
    int64_t InsertShaderModuleWithStringHandle(
        const std::string_view moduleHandle,
        const std::optional<int64_t> deviceId,
        const uint64_t codeSize,
        const uint64_t apiEventId
    );
    void InsertPipelineStage(
        const int64_t pipelineId,
        const uint64_t stageIndex,
        const uint32_t flags,
        const uint32_t stage,
        const std::optional<int64_t> shaderModule,
        const std::string_view entryPointName,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration
    );
    void InsertPipelineStageFromLibrary(
        const int64_t pipelineId, const uint64_t stageIndex, const int64_t sourcePipelineId, const uint32_t stage
    );
    void InsertPipelineStagesExcludingStageFromLibrary(
        const int64_t pipelineId, const int64_t sourcePipelineId, const uint32_t excludedStage
    );
    PipelineLibraryFlagsLookup LookupPipelineLibraryFlags(const int64_t pipelineId);
    GraphicsPipelineVertexInputStateLookup LookupGraphicsPipelineVertexInputState(const int64_t pipelineId);
    GraphicsPipelinePreRasterizationShaderStateLookup LookupGraphicsPipelinePreRasterizationShaderState(
        const int64_t pipelineId, const uint32_t excludedStage
    );
    GraphicsPipelineFragmentShaderStateLookup LookupGraphicsPipelineFragmentShaderState(
        const int64_t pipelineId, const uint32_t stage
    );
    GraphicsPipelineFragmentOutputStateLookup LookupGraphicsPipelineFragmentOutputState(const int64_t pipelineId);
    GraphicsPipelineMultisampleStateLookup LookupGraphicsPipelineMultisampleState(const int64_t pipelineId);

    void InsertValidationCache(
        const format::HandleId validationCache,
        const format::HandleId device,
        const uint64_t initialDataSize,
        const uint64_t apiEventId
    );
    void InsertPipelineCache(
        const format::HandleId pipelineCache,
        const format::HandleId device,
        const uint32_t flags,
        const uint64_t initialDataSize,
        const uint64_t apiEventId
    );
    int64_t InsertPipelineLayout(
        const int64_t layoutHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const uint64_t apiEventId
    );
    void InsertPipelineDescriptorSetLayout(
        const int64_t pipelineLayoutId, const uint64_t setIndex, const std::optional<int64_t> layoutId
    );
    void InsertPipelinePushConstantRange(
        const int64_t pipelineLayoutId,
        const uint64_t rangeIndex,
        const uint32_t stageFlags,
        const uint32_t offset,
        const uint32_t size
    );

    int64_t InsertDescriptorSetLayout(
        const int64_t layoutHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const uint64_t apiEventId
    );
    void InsertDescriptorSetLayoutBinding(
        const int64_t layoutId,
        const uint32_t binding,
        const uint32_t descriptorType,
        const uint32_t descriptorCount,
        const uint32_t stageFlags,
        const uint32_t bindingFlags
    );
    void InsertDescriptorPool(
        const format::HandleId pool,
        const format::HandleId device,
        const uint32_t flags,
        const uint32_t maxSets,
        const uint64_t apiEventId
    );
    int64_t InsertDescriptorSet(
        const int64_t setHandle,
        const std::optional<int64_t> poolId,
        const std::optional<int64_t> layoutId,
        const uint64_t apiEventId
    );

    int64_t InsertVertexInputState(const int64_t pipelineId);
    void InsertVertexInputStateBindingDescription(
        const int64_t stateId,
        const uint32_t binding,
        const uint32_t stride,
        const uint32_t inputRate,
        const uint32_t divisor
    );
    void InsertVertexInputStateBindingDescriptionFromLibrary(const int64_t newStateId, const int64_t sourceStateId);
    void InsertVertexInputStateAttributeDescription(
        const int64_t stateId,
        const uint32_t location,
        const uint32_t binding,
        const uint32_t format,
        const uint32_t offset
    );
    void InsertVertexInputStateAttributeDescriptionFromLibrary(const int64_t newStateId, const int64_t sourceStateId);
    int64_t InsertInputAssemblyState(
        const int64_t pipelineId, const uint32_t topology, const uint32_t primitiveRestartEnable
    );
    int64_t InsertInputAssemblyStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    int64_t InsertTessellationState(const int64_t pipelineId, const uint32_t patchControlPoints);
    int64_t InsertTessellationStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    int64_t InsertViewportState(
        const int64_t pipelineId,
        const uint32_t depthClipNegativeToOne,
        const uint32_t depthClampMode,
        const std::optional<float> minDepthClamp,
        const std::optional<float> maxDepthClamp
    );
    int64_t InsertViewportStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    void InsertViewportStateViewport(
        const int64_t stateId,
        const uint64_t viewportIndex,
        const float x,
        const float y,
        const float width,
        const float height,
        const float minDepth,
        const float maxDepth
    );
    void InsertViewportStateViewportFromLibrary(const int64_t newStateId, const int64_t sourceStateId);
    void InsertViewportStateScissor(
        const int64_t stateId,
        const uint64_t scissorIndex,
        const int32_t x,
        const int32_t y,
        const uint32_t width,
        const uint32_t height
    );
    void InsertViewportStateScissorFromLibrary(const int64_t newStateId, const int64_t sourceStateId);
    int64_t InsertRasterizationState(
        const int64_t pipelineId,
        const uint32_t depthClampEnable,
        const uint32_t rasterizerDiscardEnable,
        const uint32_t polygonMode,
        const uint32_t cullMode,
        const uint32_t frontFace,
        const uint32_t depthBiasEnable,
        const float depthBiasConstantFactor,
        const float depthBiasClamp,
        const float depthBiasSlopeFactor,
        const float lineWidth,
        const uint32_t lineRasterizationMode,
        const uint32_t stippledLineEnable,
        const std::optional<uint32_t> lineStippleFactor,
        const std::optional<uint32_t> lineStipplePattern,
        const uint32_t provokingVertexMode,
        const uint32_t rasterizationStream
    );
    int64_t InsertRasterizationStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    int64_t InsertDepthStencilState(
        const int64_t pipelineId,
        const uint32_t flags,
        const uint32_t depthTestEnable,
        const uint32_t depthWriteEnable,
        const uint32_t depthCompareOp,
        const uint32_t depthBoundsTestEnable,
        const uint32_t stencilTestEnable,
        const uint32_t frontFailOp,
        const uint32_t frontPassOp,
        const uint32_t frontDepthFailOp,
        const uint32_t frontCompareOp,
        const uint32_t frontCompareMask,
        const uint32_t frontWriteMask,
        const uint32_t frontReference,
        const uint32_t backFailOp,
        const uint32_t backPassOp,
        const uint32_t backDepthFailOp,
        const uint32_t backCompareOp,
        const uint32_t backCompareMask,
        const uint32_t backWriteMask,
        const uint32_t backReference,
        const float minDepthBounds,
        const float maxDepthBounds
    );
    int64_t InsertDepthStencilStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    int64_t InsertColorBlendState(
        const int64_t pipelineId,
        const uint32_t flags,
        const uint32_t logicOpEnable,
        const std::optional<int64_t> logicOp,
        std::span<const float, 4> blendConstants
    );
    int64_t InsertColorBlendStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    void InsertColorBlendStateAttachmentState(
        const int64_t colorBlendStateId,
        const uint64_t attachmentIndex,
        const uint32_t blendEnable,
        const uint32_t srcColorBlendFactor,
        const uint32_t dstColorBlendFactor,
        const uint32_t colorBlendOp,
        const uint32_t srcAlphaBlendFactor,
        const uint32_t dstAlphaBlendFactor,
        const uint32_t alphaBlendOp,
        const uint32_t colorWriteMask,
        const uint32_t colorWriteEnable
    );
    void InsertColorBlendStateAttachmentStateFromLibrary(const int64_t newStateId, const int64_t sourceStateId);
    void InsertPipelineDynamicState(const int64_t pipelineId, const uint32_t dynamicState);
    void InsertPipelineDynamicStatesFromLibrary(const int64_t pipelineId, const int64_t sourcePipelineId);
    int64_t InsertMultisampleState(
        const int64_t pipelineId,
        const uint32_t rasterizationSamples,
        const uint32_t sampleShadingEnable,
        const float minSampleShading,
        const uint32_t alphaToCoverageEnable,
        const uint32_t alphaToOneEnable
    );
    int64_t InsertMultisampleStateFromLibrary(const int64_t pipelineId, const int64_t sourceStateId);
    void InsertMultisampleStateSampleMask(const int64_t stateId, const uint64_t maskIndex, const uint32_t sampleMask);
    void InsertMultisampleStateSampleMasksFromLibrary(const int64_t newStateId, const int64_t sourceStateId);

    int64_t InsertPipelineGraphics(
        const int64_t pipelineHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const std::optional<int64_t> basePipelineId,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<int64_t> renderPass,
        const std::optional<int64_t> viewMask,
        const std::optional<int64_t> depthAttachmentFormat,
        const std::optional<int64_t> stencilAttachmentFormat,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration,
        const uint64_t apiEventId
    );
    int64_t InsertPipelineCompute(
        const int64_t pipelineHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const std::optional<int64_t> basePipelineId,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration,
        const uint64_t apiEventId
    );
    int64_t InsertPipelineRayTracingNV(
        const int64_t pipelineHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const std::optional<int64_t> basePipelineId,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration,
        const uint64_t apiEventId
    );
    int64_t InsertPipelineRayTracing(
        const int64_t pipelineHandle,
        const std::optional<int64_t> deviceId,
        const uint32_t flags,
        const std::optional<int64_t> basePipelineId,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration,
        const uint64_t apiEventId
    );
    void InsertPipelineColorAttachmentFormat(
        const int64_t pipelineId, const uint64_t attachmentIndex, const uint32_t format
    );
    void InsertPipelineLibrary(const int64_t pipelineId, const int64_t libraryPipelineId);
    void InsertGraphicsPipelineInfo(
        const int64_t pipelineId,
        const uint32_t libraryFlags,
        const uint32_t subpassIndex,
        const std::optional<int64_t> inputAssemblyStateId,
        const std::optional<int64_t> vertexInputStateId,
        const std::optional<int64_t> tessellationStateId,
        const std::optional<int64_t> viewportStateId,
        const std::optional<int64_t> rasterizationStateId,
        const std::optional<int64_t> multisampleStateId,
        const std::optional<int64_t> depthStencilStateId,
        const std::optional<int64_t> colorBlendStateId
    );
    void InsertComputePipelineInfo(const int64_t pipelineId);
    int64_t InsertPipelineDataGraph(
        const int64_t pipelineHandle,
        const std::optional<int64_t> deviceId,
        const uint64_t flags,
        const std::optional<int64_t> basePipeline,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<int64_t> feedbackFlags,
        const std::optional<int64_t> createDuration,
        const uint64_t apiEventId
    );
    int64_t InsertDataGraphPipelineInfo(const int64_t pipelineId);
    void InsertDataGraphPipelineResourceInfo(
        const int64_t infoId,
        const uint32_t idx,
        const uint32_t descriptorSet,
        const uint32_t binding,
        const uint32_t arrayElement
    );
    int64_t InsertDataGraphPipelineSession(
        const int64_t sessionHandle,
        const std::optional<int64_t> deviceId,
        const uint64_t flags,
        const int64_t pipelineId,
        const uint64_t apiEventId
    );
    int64_t InsertCmdDataGraphDispatchRecording(
        const uint64_t apiEventId, const std::optional<int64_t> sessionId, const int64_t commandBufferRecordingId
    );
    void InsertCmdDataGraphDispatchRecordingInfo(const int64_t cmdDataGraphDispatchRecordingId, const uint64_t flags);
    int64_t InsertRaytracingPipelineInfo(
        const int64_t pipelineId,
        const uint32_t maxRecursionDepth,
        const std::optional<int64_t> maxPipelineRayPayloadSize,
        const std::optional<int64_t> maxPipelineRayHitAttributeSize
    );
    void InsertRaytracingShaderGroup(
        const int64_t raytracingPipelineInfoId,
        const int64_t pipelineId,
        const uint32_t groupType,
        const uint32_t generalShaderIndex,
        const uint32_t closestHitShaderIndex,
        const uint32_t anyHitShaderIndex,
        const uint32_t intersectionShaderIndex
    );

    int64_t InsertDisplay(const int64_t displayHandle, const int64_t physicalDeviceId, const uint64_t apiEventId);
    void InsertDisplayMode(
        const format::HandleId mode,
        const int64_t physicalDeviceId,
        const int64_t displayId,
        const uint32_t visibleRegionWidth,
        const uint32_t visibleRegionHeight,
        const uint32_t refreshRate,
        const uint64_t apiEventId
    );
    void InsertAcquireNextImage(
        const std::optional<int64_t> swapchainId,
        const std::optional<int64_t> fenceSyncScopeId,
        const std::optional<int64_t> semaphoreId,
        const uint64_t frame,
        const uint64_t apiEventId
    );

    int64_t InsertFramebuffer(
        const format::HandleId framebuffer,
        const format::HandleId device,
        const uint32_t flags,
        const std::optional<int64_t> renderPassId,
        const uint32_t width,
        const uint32_t height,
        const uint32_t layers,
        const uint64_t apiEventId
    );
    int64_t InsertFramebufferAttachmentInfo(
        const uint32_t flags,
        const uint32_t width,
        const uint32_t height,
        const uint32_t layerCount,
        const uint32_t usage
    );
    void InsertFramebufferAttachmentWithInfo(
        const int64_t framebufferId, const uint64_t attachmentIndex, const int64_t attachmentInfoId
    );
    void InsertFramebufferAttachmentWithImageView(
        const int64_t framebufferId, const uint64_t attachmentIndex, const std::optional<int64_t> imageViewId
    );
    void InsertSamplerYcbcrConversion(
        const format::HandleId conversion,
        const format::HandleId device,
        const uint32_t format,
        const uint32_t ycbcrModel,
        const uint32_t ycbcrRange,
        const VkComponentMapping& components,
        const uint32_t xChromaOffset,
        const uint32_t yChromaOffset,
        const uint32_t chromaFilter,
        const uint32_t forceExplicitReconstruction,
        const uint64_t apiEventId
    );
    void InsertPrivateDataSlot(const format::HandleId slot, const format::HandleId device, const uint64_t apiEventId);
    void InsertDeferredOperation(
        const format::HandleId operation, const format::HandleId device, const uint64_t apiEventId
    );
    void InsertPipelineBinary(
        const format::HandleId binary,
        const format::HandleId device,
        const uint32_t keySize,
        const uint64_t dataSize,
        const std::optional<int64_t> pipelineId,
        const uint64_t apiEventId
    );

    void InsertVideoSession(
        const format::HandleId videoSession,
        const format::HandleId device,
        const uint32_t queueFamilyIndex,
        const uint32_t flags,
        const uint32_t videoCodecOperation,
        const uint32_t chromaSubsampling,
        const uint32_t lumaBitDepth,
        const uint32_t chromaBitDepth,
        const uint32_t pictureFormat,
        const uint32_t maxCodedWidth,
        const uint32_t maxCodedHeight,
        const uint32_t referencePictureFormat,
        const uint32_t maxDpbSlots,
        const uint32_t maxActiveReferencePictures,
        const char* stdHeaderVersionName,
        const uint32_t stdHeaderVersionSpecVersion,
        const uint64_t apiEventId
    );
    void InsertVideoSessionParameters(
        const format::HandleId videoSessionParameters,
        const format::HandleId device,
        const uint32_t flags,
        const std::optional<int64_t> videoSessionParametersTemplateId,
        const int64_t videoSessionId,
        const uint64_t apiEventId
    );
    void InsertIndirectCommandsLayout(
        const format::HandleId indirectCommandsLayout,
        const format::HandleId device,
        const uint32_t flags,
        const uint32_t shaderStages,
        const uint32_t indirectStride,
        const std::optional<int64_t> pipelineLayoutId,
        const uint32_t tokenCount,
        const uint64_t apiEventId
    );
    void InsertMicromap(
        const format::HandleId micromap,
        const format::HandleId device,
        const uint32_t createFlags,
        const std::optional<int64_t> bufferId,
        const uint64_t offset,
        const uint64_t size,
        const uint32_t type,
        const uint64_t deviceAddress,
        const uint64_t apiEventId
    );
    void InsertOpticalFlowSession(
        const format::HandleId opticalFlowSession,
        const format::HandleId device,
        const uint32_t width,
        const uint32_t height,
        const uint32_t imageFormat,
        const uint32_t flowVectorFormat,
        const uint32_t costFormat,
        const uint32_t outputGridSize,
        const uint32_t hintGridSize,
        const uint32_t performanceLevel,
        const uint32_t flags,
        const uint64_t apiEventId
    );

    // Helper functions originally from VulkanSqliteConsumerBase
    void InsertFrame(const uint64_t frameIndex, const uint64_t beginApiEventId);
    int64_t InsertFunctionName(const std::string_view functionName);
    void InsertApiEvent(const uint64_t apiEventId, const int64_t functionNameId, const format::ThreadId threadId);
    void InsertMetaApiEvent(const uint64_t apiEventId, const int64_t functionNameId, const uint64_t frame_number);

    template <typename T>
        requires(!invalid_arg_type<T>)
    void InsertApiEventReturns(const uint64_t apiEventId, const std::string_view type, const T value);

    int64_t InsertInstance(
        const uint64_t apiEventId,
        const int64_t instance,
        const VkInstanceCreateFlags flags,
        const std::string_view applicationName,
        const uint32_t applicationVersion,
        const std::string_view engineName,
        const uint32_t engineVersion,
        const uint32_t apiVersion
    );
    int64_t InsertInstanceEnabledLayer(const int64_t instanceId, const std::string_view layerName);
    int64_t InsertInstanceEnabledLayerSetting(
        const int64_t instanceEnabledLayerId, const std::string_view name, const int64_t type
    );
    void InsertInstanceEnabledLayerSettingValue(
        const int64_t instanceEnabledLayerSettingId, const int64_t idx, const std::string_view value
    );
    void InsertInstanceEnabledExtension(const int64_t instanceId, const std::string_view extensionName);
    void InsertInstanceValidationEnabledFeature(const int64_t instanceId, const int64_t feature);
    void InsertInstanceValidationDisabledFeature(const int64_t instanceId, const int64_t feature);
    void InsertInstanceValidationDisabledCheck(const int64_t instanceId, const int64_t check);

    int64_t InsertDevice(
        const uint64_t apiEventId,
        const format::HandleId device,
        const std::optional<int64_t> physicalDevice,
        const int64_t overallocationBehavior
    );
    void InsertDeviceEnabledLayer(const int64_t deviceId, const std::string_view layerName);
    void InsertDeviceEnabledExtension(const int64_t deviceId, const std::string_view extensionName);
    void InsertDeviceEnabledFeature(const int64_t deviceId, const std::string_view featureName);
    void InsertTrackedDeviceCommand(const int64_t deviceId, const uint64_t apiEventId);

    int64_t InsertSurface(const int64_t surfaceHandle, const uint32_t createInfoType, const uint64_t apiEventId);
    int64_t InsertCommandBufferInheritanceInfo(
        const std::optional<int64_t> renderPassId,
        const uint32_t subpassIndex,
        const std::optional<int64_t> framebufferId,
        const uint32_t occlusionQueryEnable,
        const uint32_t queryFlags,
        const uint32_t pipelineStatisticsFlags
    );

    int64_t InsertCommandPool(
        const uint64_t apiEventId,
        const format::HandleId commandPool,
        const format::HandleId device,
        const VkCommandPoolCreateFlags flags,
        const uint32_t queueFamilyIndex
    );

    int64_t InsertCommandBuffer(
        const uint64_t apiEventId,
        const format::HandleId commandBuffer,
        const format::HandleId device,
        const format::HandleId commandPool,
        const VkCommandBufferLevel level
    );

    int64_t InsertTrackedCmdCommand(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId
    );
    int64_t InsertCommandBufferRecording(
        const uint64_t apiEventId,
        const int64_t commandBuffer,
        const VkCommandBufferUsageFlags flags,
        const std::optional<int64_t> inheritanceInfo
    );
    void EndCommandBufferRecording(const uint64_t apiEventId, const int64_t commandBufferRecordingId);
    void ResetCommandBufferRecording(const uint64_t apiEventId, const int64_t commandBufferRecordingId);
    int64_t InsertRenderPassRecording(
        const uint64_t apiEventId,
        const std::optional<int64_t> renderPass,
        const uint64_t passIndex,
        const std::optional<int64_t> commandBufferRecordingId,
        const std::optional<int64_t> framebuffer,
        const int32_t renderOffsetX,
        const int32_t renderOffsetY,
        const int32_t renderWidth,
        const int32_t renderHeight
    );
    void EndRenderPassRecording(const uint64_t apiEventId, const int64_t renderPassRecordingId);
    void InsertRenderPassRecordingClearValues(
        const int64_t renderPassRecordingId,
        const uint64_t attachmentIndex,
        const int64_t clearColorId,
        const float clearDepth,
        const uint32_t clearStencil
    );
    void InsertRenderPassRecordingAttachment(
        const int64_t renderPassRecordingId, const uint64_t idx, const int64_t imageViewId
    );
    void InsertRenderSubpassRecording(
        const uint64_t apiEventId, const int64_t renderPassRecordingId, const uint32_t contents
    );
    void EndRenderSubpassRecording(const uint64_t apiEventId, const int64_t renderSubpassRecordingId);
    int64_t InsertDynamicRenderPassRecording(
        const uint64_t apiEventId,
        const uint64_t dynamicPassIndex,
        const std::optional<int64_t> commandBufferRecordingId,
        const uint32_t flags,
        const int32_t renderOffsetX,
        const int32_t renderOffsetY,
        const int32_t renderWidth,
        const int32_t renderHeight,
        const uint32_t layerCount,
        const uint32_t viewMask,
        const std::optional<int64_t> depthAttachment,
        const std::optional<int64_t> stencilAttachment
    );
    void EndDynamicRenderPassRecording(const uint64_t apiEventId, const int64_t renderPassRecordingId);
    int64_t InsertUnionColor(const VkClearColorValue& clearColorId);
    int64_t InsertRenderingAttachment(
        const std::optional<int64_t> imageView,
        const VkImageLayout imageLayout,
        const VkResolveModeFlagBits resolveMode,
        const std::optional<int64_t> resolveImageViewId,
        const VkImageLayout resolveImageLayout,
        const VkAttachmentLoadOp loadOp,
        const VkAttachmentStoreOp storeOp,
        const int64_t clearColorId,
        const float clearDepth,
        const uint32_t clearStencil
    );
    void InsertDynamicColorAttachment(
        const int64_t dynamicRenderPassRecordingId, const uint64_t attachmentIndex, const int64_t renderingAttachmentId
    );
    int64_t InsertSecondaryCommandBufferExecutionRecording(
        const uint64_t apiEventId,
        const int64_t parentCommandBufferRecordingId,
        const int64_t secondaryCommandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId,
        const int64_t index
    );
    int64_t InsertCmdDrawRecording(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId,
        const bool indexed
    );
    int64_t InsertCmdMeshTaskRecording(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId
    );
    int64_t InsertCmdClusterRecording(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId
    );
    int64_t InsertCmdDispatchRecording(const uint64_t apiEventId, const int64_t commandBufferRecordingId);
    int64_t InsertCmdRaytracingRecording(const uint64_t apiEventId, const int64_t commandBufferRecordingId);
    void InsertCmdDrawRecordingIndirectInfo(
        const int64_t cmdDrawRecordingId,
        const std::optional<int64_t> indirectBuffer,
        const std::optional<uint64_t> indirectBufferOffset,
        const std::optional<int64_t> indirectCountBuffer,
        const std::optional<uint64_t> indirectCountBufferOffset,
        const std::optional<uint32_t> indirectCountOffset,
        const std::optional<uint32_t> indirectDrawCount,
        const std::optional<uint32_t> indirectMaxDrawCount,
        const std::optional<uint32_t> indirectStride,
        const std::optional<uint32_t> indirectVertexStride
    );
    void InsertCmdDrawRecordingInfo(
        const int64_t cmdDrawRecordingId,
        const std::optional<uint32_t> vertexCount,
        const std::optional<uint32_t> firstVertex,
        const std::optional<int32_t> vertexOffset,
        const std::optional<uint32_t> indexCount,
        const std::optional<uint32_t> firstIndex,
        const uint32_t instanceCount,
        const uint32_t firstInstance
    );
    void InsertCmdMeshTaskRecordingIndirectInfo(
        const int64_t cmdMeshTaskRecordingId,
        const std::optional<int64_t> indirectBuffer,
        const uint64_t indirectBufferOffset,
        const std::optional<int64_t> indirectCountBuffer,
        const std::optional<uint64_t> indirectCountBufferOffset,
        const std::optional<uint32_t> indirectDrawCount,
        const std::optional<uint32_t> indirectMaxDrawCount,
        const uint32_t indirectStride
    );
    void InsertCmdMeshTaskRecordingInfo(
        const int64_t cmdMeshTaskRecordingId,
        const uint32_t groupCountX,
        const uint32_t groupCountY,
        const uint32_t groupCountZ
    );
    void InsertCmdClusterRecordingIndirectInfo(
        const int64_t cmdClusterRecordingId,
        const std::optional<int64_t> indirectBuffer,
        const uint64_t indirectBufferOffset
    );
    void InsertCmdClusterRecordingInfo(
        const int64_t cmdClusterRecordingId,
        const uint32_t groupCountX,
        const uint32_t groupCountY,
        const uint32_t groupCountZ
    );
    void InsertCmdDispatchRecordingIndirectInfo(
        const int64_t cmdDispatchRecordingId,
        const std::optional<int64_t> indirectBuffer,
        const uint64_t indirectBufferOffset
    );
    void InsertCmdDispatchRecordingBaseInfo(
        const int64_t cmdDispatchRecordingId,
        const uint32_t baseGroupX,
        const uint32_t baseGroupY,
        const uint32_t baseGroupZ
    );
    void InsertCmdDispatchRecordingInfo(
        const int64_t cmdDispatchRecordingId,
        const uint32_t groupCountX,
        const uint32_t groupCountY,
        const uint32_t groupCountZ
    );

    int64_t InsertStatePipelineBinding(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const int64_t pipelineId,
        const VkPipelineBindPoint bindPoint
    );

    int64_t InsertStateShaderObjectBinding(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const int64_t shaderObjectId,
        const VkShaderStageFlagBits stage
    );

    int64_t InsertStateIndexBufferBinding(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> bufferId,
        const uint64_t offset,
        const VkIndexType indexType,
        const std::optional<uint64_t> size
    );

    int64_t InsertStateVertexBufferBinding(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t binding,
        const std::optional<int64_t> bufferId,
        const uint64_t offset,
        const std::optional<uint64_t> size,
        const std::optional<uint64_t> stride
    );

    int64_t InsertStateDescriptorSetBinding(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t setIndex,
        const VkShaderStageFlags stageFlags,
        const int64_t pipelineLayoutId,
        const int64_t descriptorSetId
    );

    void InsertStateDescriptorSetBindingDynamicOffset(
        const uint64_t stateId, const uint32_t binding, const uint32_t arrayElement, const uint32_t dynamicOffset
    );

    int64_t InsertStateDescriptorSetPush(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t setIndex,
        const uint32_t binding,
        const uint32_t arrayElement,
        const VkDescriptorType descriptorType
    );

    int64_t InsertStateVertexInputBindingDescription(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t binding,
        const uint32_t stride,
        const VkVertexInputRate inputRate
    );

    int64_t InsertStateVertexInputAttributeDescription(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t location,
        const uint32_t binding,
        const VkFormat format,
        const uint32_t offset
    );

    int64_t InsertStateDynamicViewport(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t viewportIndex,
        const float x,
        const float y,
        const float width,
        const float height,
        const float minDepth,
        const float maxDepth
    );

    int64_t InsertStateDynamicScissor(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t scissorIndex,
        const VkOffset2D& offset,
        const VkExtent2D& extent
    );

    int64_t InsertStateDynamicRenderingColorAttachmentLocation(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t oldLocation,
        const uint32_t newLocation
    );
    int64_t InsertStateDynamicRenderingInputColorAttachmentIndex(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t oldIndex,
        const uint32_t newIndex
    );
    int64_t InsertStateDynamicRenderingInputDepthAttachmentIndex(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t newIndex
    );
    int64_t InsertStateDynamicRenderingInputStencilAttachmentIndex(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t newIndex
    );

    int64_t InsertStateDynamicLineWidth(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const float lineWidth
    );

    int64_t InsertStateDynamicDepthBounds(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const float minDepthBounds,
        const float maxDepthBounds
    );
    int64_t InsertStateDynamicDepthBoundsTestEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enabled
    );

    int64_t InsertStateDynamicDepthBias(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const float constantFactor,
        const float clamp,
        const float slopeFactor,
        const VkDepthBiasRepresentationEXT representation,
        const VkBool32 exact
    );
    int64_t InsertStateDynamicDepthBiasEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enabled
    );

    int64_t InsertStateDynamicDepthTestEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enabled
    );

    int64_t InsertStateDynamicDepthWriteEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enabled
    );

    int64_t InsertStateDynamicDepthCompareOp(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const VkCompareOp compareOp
    );

    int64_t InsertStateDynamicStencilCompareMaskFront(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t frontMask
    );

    int64_t InsertStateDynamicStencilCompareMaskBack(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t backMask
    );

    int64_t InsertStateDynamicStencilWriteMaskFront(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t frontMask
    );

    int64_t InsertStateDynamicStencilWriteMaskBack(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t backMask
    );

    int64_t InsertStateDynamicStencilReferenceFront(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t reference
    );

    int64_t InsertStateDynamicStencilReferenceBack(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t reference
    );

    int64_t InsertStateDynamicStencilTestEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enabled
    );

    int64_t InsertStateDynamicStencilOpsFront(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const VkStencilOp failOp,
        const VkStencilOp passOp,
        const VkStencilOp depthFailOp,
        const VkCompareOp compareOp
    );

    int64_t InsertStateDynamicStencilOpsBack(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const VkStencilOp failOp,
        const VkStencilOp passOp,
        const VkStencilOp depthFailOp,
        const VkCompareOp compareOp
    );

    int64_t InsertStateDynamicColorWriteEnable(
        const uint64_t apiEventId,
        const int64_t commandBufferRecordingId,
        const uint32_t attachmentIndex,
        const bool enabled
    );

    int64_t InsertStateDynamicBlendConstants(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, std::span<const float, 4> blendConstants
    );

    int64_t InsertStateDynamicPrimitiveTopology(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const VkPrimitiveTopology topology
    );

    int64_t InsertStateDynamicCullMode(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const VkCullModeFlags cullMode
    );

    int64_t InsertStateDynamicFrontFace(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const VkFrontFace frontFace
    );

    int64_t InsertStateDynamicLogicOp(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const VkLogicOp logicOp
    );

    int64_t InsertStateDynamicRasterizerDiscardEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enable
    );

    int64_t InsertStateDynamicPatchControlPoints(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool patchControlPoints
    );

    int64_t InsertStateDynamicPrimitiveRestartEnable(
        const uint64_t apiEventId, const int64_t commandBufferRecordingId, const bool enable
    );

    int64_t InsertQueuePresent(
        const int64_t queueId, const int64_t frame, const int64_t apiEventId, const bool persistent
    );
    void InsertQueuePresentRect(
        const int64_t presentId,
        const int32_t srcX,
        const int32_t srcY,
        const uint32_t srcWidth,
        const uint32_t srcHeight,
        const int32_t dstX,
        const int32_t dstY,
        const uint32_t dstWidth,
        const uint32_t dstHeight
    );
    void InsertQueuePresentSemaphoreWait(
        const int64_t presentId, const size_t waitIndex, const std::optional<int64_t> semaphoreId
    );
    int64_t InsertQueuePresentSwapchain(
        const int64_t presentId,
        const uint32_t idx,
        const std::optional<int64_t> swapchainId,
        const uint32_t imageIndex,
        const std::optional<int64_t> fenceId,
        const std::optional<int64_t> vulkanPresentId,
        const std::optional<int64_t> googlePresentId,
        const std::optional<int64_t> desiredPresentTime,
        const std::optional<int64_t> presentMode
    );
    void InsertQueuePresentSwapchainRegion(
        const int64_t queuePresentSwapchainId,
        const int32_t x,
        const int32_t y,
        const uint32_t width,
        const uint32_t height,
        const uint32_t layer
    );

    int64_t InsertRenderPass(
        const format::HandleId handle,
        const std::optional<int64_t> deviceId,
        const VkRenderPassCreateFlags flags,
        const uint64_t apiEventId
    );
    void InsertRenderPassAttachment(
        const int64_t renderPass,
        const int64_t index,
        const VkAttachmentDescriptionFlags flags,
        const VkFormat format,
        const VkSampleCountFlagBits samples,
        const VkAttachmentLoadOp loadOp,
        const VkAttachmentStoreOp storeOp,
        const VkAttachmentLoadOp stencilLoadOp,
        const VkAttachmentStoreOp stencilStoreOp,
        const VkImageLayout initialLayout,
        const VkImageLayout finalLayout
    );
    void InsertRenderSubpass(
        const int64_t renderPassId,
        const size_t subpassIndex,
        const VkSubpassDescriptionFlags flags,
        const VkPipelineBindPoint pipelineBindPoint
    );
    void InsertBlankRenderSubpassAttachmentReference(
        const int64_t renderPassId, const size_t subpassIndex, const size_t attachmentIndex
    );
    void UpdateSubpassAttachmentReferenceLayout(
        const SqliteStatement& statement,
        const int64_t renderPassId,
        const size_t subpassIndex,
        const uint32_t attachment,
        const VkImageLayout layout
    );
    void UpdateSubpassAttachmentReferencePreserve(
        const int64_t renderPassId, const size_t subpassIndex, const uint32_t attachment
    );
    void InsertSubpassDependencies(
        const int64_t renderPassId,
        const uint32_t srcSubpass,
        const uint32_t dstSubpass,
        const VkPipelineStageFlags srcStageMask,
        const VkPipelineStageFlags dstStageMask,
        const VkAccessFlags srcAccessMask,
        const VkAccessFlags dstAccessMask,
        const VkDependencyFlags dependencyFlags
    );

    void InsertDescriptorUpdateTemplateEntry(const int64_t templateId, const VkDescriptorUpdateTemplateEntry* entry);
    int64_t InsertDescriptorUpdateTemplate(
        const format::HandleId updateTemplate,
        const format::HandleId device,
        const VkDescriptorUpdateTemplateCreateFlags flags,
        const VkDescriptorUpdateTemplateType templateType,
        const std::optional<int64_t> descriptorSetLayout,
        const std::optional<VkPipelineBindPoint> pipelineBindPoint,
        const std::optional<int64_t> pipelineLayout,
        const std::optional<uint32_t> setIndex,
        const uint64_t apiEventId
    );

    [[nodiscard]] int64_t InsertDescriptorSetWrite(
        const int64_t descriptorSet,
        const uint32_t binding,
        const int64_t arrayElement,
        const VkDescriptorType descriptorType,
        const uint64_t apiEventId
    );
    void InsertDescriptorSetWriteImageInfo(
        const int64_t writeId,
        const std::optional<int64_t> sampler,
        const std::optional<int64_t> imageView,
        const int64_t imageLayout,
        const bool isPush
    );
    void InsertDescriptorSetWriteBufferInfo(
        const int64_t writeId,
        const std::optional<int64_t> buffer,
        const VkDeviceSize offset,
        const VkDeviceSize range,
        const bool isPush
    );
    void InsertDescriptorSetWriteTexelInfo(
        const int64_t writeId, const std::optional<int64_t> bufferView, const bool isPush
    );
    void InsertDescriptorSetWriteAccelerationInfo(
        const int64_t writeId, const std::optional<int64_t> accelerationStructure, const bool isPush
    );
    void InsertDescriptorSetWriteAccelerationNvInfo(
        const int64_t writeId, const std::optional<int64_t> accelerationStructureNv, const bool isPush
    );
    void CopyDescriptorSetInfo(
        const SqliteStatement& statement,
        const int64_t descriptorSetId,
        const uint32_t readBinding,
        const uint32_t srcElement,
        const int64_t writeId
    );

    void InsertBuffer(
        const format::HandleId buffer,
        const format::HandleId device,
        const VkBufferCreateFlags flags,
        const VkDeviceSize size,
        const VkBufferUsageFlags usage,
        const std::optional<int64_t> usage2,
        const VkSharingMode sharing,
        const uint64_t apiEventId
    );

    int64_t InsertBufferView(
        const format::HandleId view,
        const format::HandleId device,
        const std::optional<int64_t> bufferId,
        const VkFormat format,
        const VkDeviceSize offset,
        const int64_t range,
        const uint64_t apiEventId
    );

    void InsertImage(
        const format::HandleId image,
        const format::HandleId device,
        const VkImageCreateFlags flags,
        const VkImageType imageType,
        const VkFormat format,
        const VkExtent3D& extent,
        const uint32_t mipLevels,
        const uint32_t layers,
        const VkSampleCountFlagBits samples,
        const VkImageTiling tiling,
        const VkImageUsageFlags usage,
        const VkSharingMode sharing,
        const VkImageLayout initialLayout,
        const std::optional<int64_t> externalFormat,
        const std::optional<int64_t> externalMemoryHandleTypes,
        const uint64_t apiEventId
    );

    void InsertImageViewFormat(const int64_t imageId, const int64_t viewFormat);

    void InsertImageView(
        const format::HandleId view,
        const format::HandleId device,
        const VkImageViewCreateFlags flags,
        const std::optional<int64_t> imageId,
        const VkImageViewType viewType,
        const VkFormat format,
        const VkComponentMapping& components,
        const VkImageSubresourceRange& srRange,
        const std::optional<int64_t> usage,
        const std::optional<int64_t> samplerYcbcrConversionId,
        const std::optional<int64_t> astcDecodeMode,
        const uint64_t apiEventId
    );

    void InsertSampler(
        const format::HandleId sampler,
        const format::HandleId device,
        const VkSamplerCreateFlags flags,
        const VkFilter magFilter,
        const VkFilter minFilter,
        const VkSamplerMipmapMode mipmapMode,
        const VkSamplerAddressMode addressModeU,
        const VkSamplerAddressMode addressModeV,
        const VkSamplerAddressMode addressModeW,
        const float mipLodBias,
        const VkBool32 anisotropyEnable,
        const float maxAnisotropy,
        const VkBool32 compareEnable,
        const std::optional<int64_t> compareOp,
        const float minLod,
        const float maxLod,
        const std::optional<int64_t> borderColor,
        const VkBool32 unnormalizedCoordinates,
        const std::optional<int64_t> samplerYcbcrConversionId,
        const uint64_t apiEventId
    );

    void InsertCommandBufferCommand(const int64_t commandBufferRecordingId, const uint64_t apiEventId);

    int64_t InsertDisplayMessage(const int64_t frame, const std::string_view message);

    void InsertSwapchainImage(const format::HandleId image, const format::HandleId device, const int64_t swapchainId);

    void InsertSwapchain(
        const format::HandleId swapchain,
        const format::HandleId device,
        const VkSwapchainCreateFlagsKHR flags,
        const uint32_t minImageCount,
        const VkFormat imageFormat,
        const VkColorSpaceKHR imageColorSpace,
        const VkExtent2D imageExtent,
        const uint32_t imageLayers,
        const VkImageUsageFlags imageUsage,
        const VkSharingMode imageSharingMode,
        const VkSurfaceTransformFlagBitsKHR preTransform,
        const VkCompositeAlphaFlagBitsKHR compositeAlpha,
        const VkPresentModeKHR presentMode,
        const VkBool32 clipped,
        const std::optional<int64_t> oldSwapchainId,
        const uint64_t blockIndex
    );

    int64_t InsertAccelerationStructure(
        const format::HandleId accelerationStructure,
        const format::HandleId device,
        const VkAccelerationStructureCreateFlagsKHR flags,
        const VkAccelerationStructureTypeKHR type,
        const format::HandleId buffer,
        const uint64_t offset,
        const uint64_t size,
        const VkDeviceAddress deviceAddress,
        const uint64_t apiEventId
    );

    int64_t InsertAccelerationStructureNv(
        const format::HandleId accelerationStructure,
        const format::HandleId device,
        const VkBuildAccelerationStructureFlagsNV flags,
        const VkAccelerationStructureTypeNV type,
        const uint64_t compactSize,
        const uint64_t instanceCount,
        const uint64_t apiEventId
    );

    int64_t InsertAccelerationStructureBuild(
        const std::optional<format::HandleId> device,
        const std::optional<format::HandleId> deferredOperation,
        const std::optional<format::HandleId> commandBuffer,
        const uint64_t apiEventId
    );

    int64_t InsertAccelerationStructureBuildGeometryInfo(
        const int64_t buildId,
        const size_t infoIndex,
        const VkAccelerationStructureTypeKHR type,
        const VkBuildAccelerationStructureFlagsKHR flags,
        const VkBuildAccelerationStructureModeKHR mode,
        const format::HandleId srcAccelStruct,
        const format::HandleId dstAccelStruct,
        const VkDeviceOrHostAddressKHR scratchDataAddress
    );

    void InsertAccelerationStructureBuildGeometry(
        const int64_t infoId,
        const size_t geometryIndex,
        const VkGeometryTypeKHR type,
        const VkGeometryFlagsKHR flags,
        const std::optional<int64_t> triangleDataId,
        const std::optional<int64_t> aabbDataId,
        const std::optional<int64_t> instanceDataId
    );

    void InsertAccelerationStructureBuildRangeInfo(
        const int64_t infoId,
        const size_t rangeIndex,
        const uint32_t primitiveCount,
        const uint32_t primitiveOffset,
        const uint32_t firstVertex,
        const uint32_t transformOffset
    );

    int64_t InsertAccelerationStructureBuildTriangleData(
        const VkAccelerationStructureGeometryTrianglesDataKHR& triangles
    );
    int64_t InsertAccelerationStructureBuildAABBData(const VkAccelerationStructureGeometryAabbsDataKHR& aabbs);
    int64_t InsertAccelerationStructureBuildInstanceData(
        const VkAccelerationStructureGeometryInstancesDataKHR& instances
    );

    int64_t InsertAccelerationStructureCopy(
        const std::optional<format::HandleId> device,
        const std::optional<format::HandleId> deferredOperation,
        const std::optional<format::HandleId> commandBuffer,
        const std::optional<format::HandleId> srcAccelerationStructure,
        const std::optional<format::HandleId> dstAccelerationStructure,
        const std::optional<VkDeviceOrHostAddressConstKHR> srcAddress,
        const std::optional<VkDeviceOrHostAddressKHR> dstAddress,
        const VkCopyAccelerationStructureModeKHR mode,
        const uint64_t apiEventId
    );

    int64_t InsertTransferCommand(const uint64_t apiEventId, const std::optional<int64_t> commandBufferRecordingId);

    void UpdateTransferCommandBufferCopy(
        const int64_t instanceId, const std::optional<int64_t> srcBufferId, const std::optional<int64_t> dstBufferId
    );

    void UpdateTransferCommandImageCopy(
        const int64_t instanceId,
        const std::optional<int64_t> srcImageId,
        const std::optional<int64_t> dstImageId,
        const int32_t srcImageLayoutId,
        const int32_t dstImageLayoutId
    );

    void UpdateTransferCommandBufferToImage(
        const int64_t instanceId,
        const std::optional<int64_t> srcBufferId,
        const std::optional<int64_t> dstImageId,
        const int32_t dstImageLayoutId
    );

    void UpdateTransferCommandImageToBuffer(
        const int64_t instanceId,
        const std::optional<int64_t> srcImageId,
        const std::optional<int64_t> dstBufferId,
        const int32_t srcImageLayoutId
    );

    void UpdateTransferCommandBlit(
        const int64_t instanceId,
        const std::optional<int64_t> srcImageId,
        const std::optional<int64_t> dstImageId,
        const int32_t srcImageLayoutId,
        const int32_t dstImageLayoutId,
        const int32_t filter
    );

    void InsertTransferCommandRegionBufferCopy(
        const int64_t transferCommandId,
        const int32_t idx,
        const int64_t srcBufferId,
        const int64_t dstBufferId,
        const VkBufferCopy& region
    );

    void InsertTransferCommandRegionImageCopy(
        const int64_t transferCommandId,
        const int32_t idx,
        const int64_t srcImageId,
        const int64_t dstImageId,
        const int32_t srcBaseArrayLayer,
        const int32_t srcLayerCount,
        const int32_t srcMipLevel,
        const int32_t dstBaseArrayLayer,
        const int32_t dstLayerCount,
        const int32_t dstMipLevel,
        const int32_t srcOffsetX,
        const int32_t srcOffsetY,
        const int32_t srcOffsetZ,
        const int32_t dstOffsetX,
        const int32_t dstOffsetY,
        const int32_t dstOffsetZ,
        const int32_t srcExtentWidth,
        const int32_t srcExtentHeight,
        const int32_t srcExtentDepth,
        const int32_t dstExtentWidth,
        const int32_t dstExtentHeight,
        const int32_t dstExtentDepth
    );

    void InsertTransferCommandRegionBufferImageCopy(
        const int64_t transferCommandId,
        const int32_t idx,
        const int64_t bufferId,
        const int64_t imageId,
        const int32_t isBufferSource,
        const int64_t bufferOffset,
        const int32_t imageBaseArrayLayer,
        const int32_t imageLayerCount,
        const int32_t imageMipLevel,
        const int32_t imageOffsetX,
        const int32_t imageOffsetY,
        const int32_t imageOffsetZ,
        const int32_t extentWidth,
        const int32_t extentHeight,
        const int32_t extentDepth
    );

    void DestroyObject(const SqliteStatement& statement, const uint64_t apiEventId, const uint64_t objectId);

  private:
    int64_t InsertStateId(const uint64_t apiEventId);
    int64_t InsertStateGroup(const int64_t commandBufferRecordingId);
    int64_t InsertOverrideStateGroup(
        const int64_t parentCommandBufferRecordingId, const int64_t secondaryCommandBufferRecordingId
    );
    void InsertStateGroupEntries(const int64_t stateGroupId, const int64_t commandBufferRecordingId);
    void InsertRenderTrackedCmdCommand(
        const uint64_t apiEventId,
        sqlite3_stmt* statement,
        const int64_t instance,
        const int64_t stateGroupId,
        const int64_t commandBufferRecordingId,
        const std::optional<int64_t> renderPassRecordingId,
        const std::optional<int64_t> renderSubpassRecordingId,
        const std::optional<int64_t> dynamicRenderPassRecordingId,
        const bool indexed
    );
};

// Template implementations (must be in header for instantiation)
template <typename T>
inline void VulkanSqlitePreparedStatements::RecordField(
    const FieldInfo& fieldInfo,
    const size_t fieldIndex,
    const std::string_view fieldName,
    std::string_view fieldType,
    const T value
)
{
    using namespace std::literals::string_view_literals;
    if (fieldInfo.structId != 0)
    {
        InsertStructMember<T>(fieldInfo.structId, fieldIndex, fieldName, fieldType, value);
    }
    else if (fieldInfo.arrayId != 0)
    {
        if (fieldType.starts_with("const "sv) && fieldType.ends_with("*"sv))
        {
            fieldType.remove_prefix(6);
            fieldType.remove_suffix(1);
        }
        InsertArrayMember<to_arg_type<T>>(fieldInfo.arrayId, fieldInfo.arrayIndex, fieldType, value);
    }
    else
    {
        InsertAPIEventArgument<to_arg_type<T>>(fieldInfo.eventId, fieldIndex, fieldName, fieldType, value);
    }
}

template <typename T>
    requires(!invalid_arg_type<T>)
inline void VulkanSqlitePreparedStatements::InsertStructMember(
    const uint64_t structId,
    const size_t fieldIndex,
    const std::string_view fieldName,
    const std::string_view fieldType,
    const T value
)
{
    auto& statement = structMemberInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(structId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(fieldIndex)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, fieldName.data(), fieldName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 4, fieldType.data(), fieldType.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, BindGeneric<to_arg_type<T>>(statement, 5, value));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_clear_bindings(statement));
}

template <typename T>
inline void VulkanSqlitePreparedStatements::InsertArrayMember(
    const uint64_t arrayId, const uint64_t arrayIndex, const std::string_view fieldType, const T value
)
{
    auto& statement = arrayMemberInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(arrayId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(arrayIndex)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, fieldType.data(), fieldType.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, BindGeneric<to_arg_type<T>>(statement, 4, value));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_clear_bindings(statement));
}

template <typename T>
inline void VulkanSqlitePreparedStatements::InsertAPIEventArgument(
    const uint64_t eventId,
    const size_t fieldIndex,
    const std::string_view fieldName,
    const std::string_view fieldType,
    const T value
)
{
    auto& statement = apiEventArgumentInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(eventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(fieldIndex)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, fieldName.data(), fieldName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 4, fieldType.data(), fieldType.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK(db, BindGeneric<to_arg_type<T>>(statement, 5, value));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_clear_bindings(statement));
}

template <typename T>
    requires(!invalid_arg_type<T>)
inline void VulkanSqlitePreparedStatements::InsertApiEventReturns(
    const uint64_t apiEventId, const std::string_view type, const T value
)
{
    auto& statement = apiEventReturnsInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, type.data(), type.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, BindGeneric<T>(statement, 3, value));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_clear_bindings(statement));
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // VULKAN_SQLITE_PREPARED_STATEMENTS_H
