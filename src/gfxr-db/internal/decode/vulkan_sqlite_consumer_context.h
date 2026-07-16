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

#ifndef GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_CONTEXT_H
#define GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_CONTEXT_H

#include "decode/consumer_utils.h"
#include "decode/field_info.h"
#include "util/defines.h"
#include "sqlite_utils.h"

#include <vulkan/vulkan.h>

#include <optional>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stack>
#include <unordered_set>
#include "sqlite3.h"

inline bool operator<(const VkClearColorValue& l, const VkClearColorValue& r)
{
    const auto& lInt = l.int32;
    const auto& rInt = r.int32;
    if (lInt[0] < rInt[0])
    {
        return true;
    }
    else if (lInt[0] == rInt[0])
    {
        if (lInt[1] < rInt[1])
        {
            return true;
        }
        else if (lInt[1] == rInt[1])
        {
            if (lInt[2] < rInt[2])
            {
                return true;
            }
            else if (lInt[2] == rInt[2] && lInt[3] < rInt[3])
            {
                return true;
            }
        }
    }
    return false;
}

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

enum class StateType : uint32_t
{
    PIPELINE_BINDING = 1,
    SHADER_OBJECT_BINDING = 2,
    DESCRIPTOR_SET_BINDING = 3,
    INDEX_BUFFER_BINDING = 4,
    VERTEX_BUFFER_BINDING = 5,
    VERTEX_INPUT_BINDING_DESCRIPTION = 6,
    VERTEX_INPUT_ATTRIBUTE_DESCRIPTION = 7,
    VIEWPORT = 8,
    SCISSOR = 9,
    LINE_WIDTH = 10,
    RENDERING_COLOR_ATTACHMENT_LOCATION = 11,
    RENDERING_INPUT_COLOR_ATTACHMENT_INDEX = 12,
    RENDERING_INPUT_DEPTH_ATTACHMENT_INDEX = 13,
    RENDERING_INPUT_STENCIL_ATTACHMENT_INDEX = 14,
    DEPTH_BOUNDS = 15,
    DEPTH_BOUNDS_TEST_ENABLE = 16,
    DEPTH_BIAS = 17,
    DEPTH_BIAS_ENABLE = 18,
    DEPTH_TEST_ENABLE = 19,
    DEPTH_WRITE_ENABLE = 20,
    DEPTH_COMPARE_OPS = 21,
    STENCIL_COMPARE_MASK_FRONT = 22,
    STENCIL_COMPARE_MASK_BACK = 23,
    STENCIL_WRITE_MASK_FRONT = 24,
    STENCIL_WRITE_MASK_BACK = 25,
    STENCIL_REFERENCE_FRONT = 26,
    STENCIL_REFERENCE_BACK = 27,
    STENCIL_TEST_ENABLE = 28,
    STENCIL_OPS_FRONT = 29,
    STENCIL_OPS_BACK = 30,
    COLOR_WRITE_ENABLE = 31,
    BLEND_CONSTANTS = 32,
    PRIMITIVE_TOPOLOGY = 33,
    CULL_MODE = 34,
    FRONT_FACE = 35,
    LOGIC_OP = 36,
    RASTERIZER_DISCARD_ENABLE = 37,
    PATCH_CONTROL_POINTS = 38,
    PRIMITIVE_RESTART_ENABLE = 39,
    DESCRIPTOR_SET_PUSH = 40
    // TODO add more as more state types are enabled,
    // this should match the values populated in RecordStateTypes() and the enum in gfxr-data-service.ts
};

struct VulkanSqliteConsumerContext final
{
  public:
    VulkanSqliteConsumerContext(sqlite3* db) : db(db) {}

    sqlite3* db = nullptr;

    std::map<int64_t, std::set<std::string>> deviceIdToEnabledFeatures;

    int64_t currentFunctionNameId = 0;
    std::map<std::string, int64_t> customFunctionNamesToFunctionNameId;

    uint64_t currentFrame = 0;

    int64_t currentAnnotationId = 0;
    int64_t currentDisplayMessageId = 0;
    int64_t currentStructId = 0;
    int64_t currentArrayId = 0;

    int64_t currentDebugNameId = 0;
    int64_t currentDebugTagId = 0;
    int64_t currentDebugLabelId = 0;
    std::map<int64_t, std::stack<int64_t>> queueHandleToDebugLabelIdStack;
    std::map<int64_t, std::stack<int64_t>> commandBufferRecordingToDebugLabelIdStack;

    int64_t currentDebugReportCallbackId = 0;
    std::map<int64_t, int64_t> debugReportCallbackHandleToId;

    int64_t currentDebugMessengerId = 0;
    std::map<int64_t, int64_t> debugMessengerHandleToId;

    int64_t currentPhysicalDeviceId = 0;
    std::map<int64_t, int64_t> physicalDeviceHandleToId;

    int64_t currentDeviceId = 0;
    std::map<int64_t, int64_t> deviceHandleToId;

    int64_t currentTrackedDeviceCommandId = 0;

    int64_t currentInstanceId = 0;
    std::map<int64_t, int64_t> instanceHandleToId;
    
    int64_t currentInstanceEnabledLayerId = 0;

    int64_t currentInstanceEnabledLayerSettingId = 0;

    int64_t currentSurfaceId = 0;
    std::map<int64_t, int64_t> surfaceHandleToId;

    int64_t currentFenceId = 0;
    std::map<int64_t, int64_t> fenceHandleToId;

    int64_t currentFenceSyncScopeId = 0;
    std::map<int64_t, int64_t> fenceHandleToSyncScopeId;

    int64_t currentSemaphoreId = 0;
    std::map<int64_t, int64_t> semaphoreHandleToId;

    int64_t currentEventId = 0;
    std::map<int64_t, int64_t> eventHandleToId;

    int64_t currentQueryPoolId = 0;
    std::map<int64_t, int64_t> queryPoolHandleToId;

    // Map of device id -> queue family index -> queue flags -> priorities
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkDeviceCreateInfo.html#VUID-VkDeviceCreateInfo-queueFamilyIndex-02802
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkDeviceQueueInfo2.html#_description
    std::map<int64_t, std::map<int64_t, std::map<VkDeviceQueueCreateFlags, std::vector<float>>>>
        deviceHandleToQueuePriority;

    int64_t currentCommandPoolId = 0;
    std::map<int64_t, int64_t> commandPoolHandleToId;
    std::map<int64_t, std::vector<int64_t>> commandPoolHandleToCommandBufferHandles;

    int64_t currentCommandBufferId = 0;
    std::map<int64_t, int64_t> commandBufferHandleToId;
    std::map<int64_t, VkCommandBufferLevel> commandBufferHandleToLevel;
    std::map<int64_t, int64_t> commandBufferHandleToDeviceId;
    std::map<int64_t, format::HandleId> commandBufferHandleToDevice;

    int64_t currentCommandBufferRecordingId = 0;
    std::map<int64_t, int64_t> commandBufferHandleToRecordingId;

    int64_t currentSecondaryCommandBufferExecutionRecordingId = 0;
    int64_t currentCommandBufferInheritanceInfoId = 0;

    int64_t currentRenderPassId = 0;
    std::map<int64_t, int64_t> renderPassHandleToId;

    int64_t currentRenderPassRecordingId = 0;
    std::map<int64_t, std::stack<int64_t>> commandBufferHandleToRenderPassRecordingIdStack;
    std::map<int64_t, int64_t> commandBufferRecordingIdToRenderPassIndex;

    int64_t currentDynamicRenderPassRecordingId = 0;
    std::map<int64_t, std::stack<int64_t>> commandBufferHandleToDynamicRenderPassRecordingIdStack;
    std::map<int64_t, int64_t> commandBufferRecordingIdToDynamicRenderPassIndex;

    int64_t currentUnionColorId = 0;
    std::map<VkClearColorValue, int64_t> unionColorValueToId;
    int64_t currentRenderingAttachmentId = 0;

    int64_t currentRenderSubpassRecordingId = 0;
    std::map<int64_t, int64_t> renderPassRecordingIdToRenderSubpassRecordingId;
    std::map<int64_t, int64_t> renderPassRecordingIdToSubpassIndex;

    int64_t currentTrackedCmdCommandId = 0;
    int64_t currentCmdDrawRecordingId = 0;
    int64_t currentCmdDispatchRecordingId = 0;
    int64_t currentCmdMeshTaskRecordingId = 0;
    int64_t currentCmdClusterRecordingId = 0;
    int64_t currentCmdRaytracingRecordingId = 0;
    int64_t currentCmdDataGraphDispatchRecordingId = 0;

    int64_t currentShaderModuleId = 0;
    std::map<int64_t, int64_t> shaderModuleHandleToId;

    int64_t currentShaderObjectId = 0;
    std::map<int64_t, int64_t> shaderObjectHandleToId;

    int64_t currentValidationCacheId = 0;
    std::map<int64_t, int64_t> validationCacheHandleToId;

    int64_t currentDescriptorPoolId = 0;
    std::map<int64_t, int64_t> descriptorPoolHandleToId;

    int64_t currentDescriptorSetId = 0;
    struct DescriptorSetInfo
    {
        int64_t descriptorSetId;
        int64_t layoutId;
    };
    std::map<int64_t, DescriptorSetInfo> descriptorSetHandleToInfo;

    int64_t currentDescriptorSetLayoutId = 0;
    std::map<int64_t, int64_t> descriptorSetLayoutHandleToId;
    struct DescriptorSetLayoutBindingInfo
    {
        VkDescriptorType descriptorType;
        VkShaderStageFlags stageFlags;
        uint32_t descriptorCount;
        VkDescriptorBindingFlags flags;
    };
    struct DescriptorSetLayoutInfo
    {
        VkDescriptorSetLayoutCreateFlags flags;
        std::map<int64_t, DescriptorSetLayoutBindingInfo> bindings;
    };
    // map of descriptor set layout id -> layout info
    std::map<int64_t, DescriptorSetLayoutInfo> descriptorSetLayoutToInfo;
    int64_t currentDescriptorSetWrite = 0;

    int64_t currentDescriptorUpdateTemplateId = 0;
    std::map<int64_t, int64_t> descriptorUpdateTemplateHandleToId;
    std::map<int64_t, std::pair<const VkDescriptorUpdateTemplateCreateInfo*, std::unique_ptr<uint8_t[]>>>
        descriptorUpdateTemplateInfo;

    int64_t currentPrivateDataSlotId = 0;
    std::map<int64_t, int64_t> privateDataSlotHandleToId;

    int64_t currentPipelineId = 0;
    std::map<int64_t, int64_t> pipelineHandleToId;

    int64_t currentGraphicsPipelineId = 0;
    int64_t currentRaytracingPipelineId = 0;
    int64_t currentComputePipelineId = 0;

    int64_t currentPipelineCacheId = 0;
    std::map<int64_t, int64_t> pipelineCacheHandleToId;

    int64_t currentStateId = 0;
    int64_t currentStateGroupId = 0;

    std::unordered_set<int64_t> commandBufferRecordingWithDirtyState;
    std::map<int64_t, int64_t> commandBufferRecordingPreviousState;
    struct StateGroupEntry
    {
        StateGroupEntry(int64_t stateId_, StateType stateTypeId_, uint32_t idx_ = 0, uint32_t subIndex_ = 0) :
            stateId(stateId_), stateTypeId(stateTypeId_), idx(idx_), subIndex(subIndex_)
        {}
        int64_t stateId;
        StateType stateTypeId;
        uint32_t idx;
        uint32_t subIndex;
    };
    std::map<int64_t, std::vector<StateGroupEntry>> commandBufferRecordingPreviousStateEntries;

    // maps of command buffer recording id -> pipeline bind point (pipeline type) -> pipeline binding state ids
    std::map<int64_t, std::map<VkPipelineBindPoint, int64_t>> commandBufferRecordingPipelineBindings;

    // maps of command buffer recording id -> shader stage -> shader object state ids
    std::map<int64_t, std::map<VkShaderStageFlagBits, int64_t>> commandBufferRecordingShaderObjectBindings;

    // maps of command buffer recording id -> pipeline bind point -> descriptor set index -> descriptor set binding
    // state id
    std::map<int64_t, std::map<VkPipelineBindPoint, std::map<uint32_t, int64_t>>>
        commandBufferRecordingDescriptorSetBindings;

    // map of command buffer recording id -> binding -> array element push descriptor state id
    // descriptor set index doesn't need to be tracked here, as there can be at most one:
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkPipelineLayoutCreateInfo.html#VUID-VkPipelineLayoutCreateInfo-pSetLayouts-00293
    std::map<int64_t, std::map<uint32_t, std::map<uint32_t, int64_t>>> commandBufferRecordingDescriptorSetPushes;

    // maps of command buffer recording id -> binding index -> vertex buffer binding state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingVertexBindings;

    // map of command buffer recording id -> index buffer binding state id
    std::map<int64_t, int64_t> commandBufferRecordingIndexBindings;

    // maps of command buffer recording id -> binding index -> description state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingVertexInputBindingDescriptions;

    // maps of command buffer recording id -> location index -> description state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingVertexInputAttributeDescriptions;

    // maps of command buffer recording id -> viewport index -> dynamic viewport state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingDynamicViewports;

    // maps of command buffer recording id -> scissor index -> dynamic scissor state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingDynamicScissors;

    // maps of command buffer recording id -> old attachment location -> dynamic rendering color attachment location
    // state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingDynamicRenderingColorAttachmentLocations;

    // maps of command buffer recording id -> old attachment input index -> dynamic rendering color input attachment
    // index state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingDynamicRenderingInputColorAttachmentIndices;

    // maps of command buffer recording id -> dynamic rendering depth input attachment
    // index state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicRenderingInputDepthAttachmentIndices;

    // maps of command buffer recording id -> dynamic rendering stencil input attachment
    // index state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicRenderingInputStencilAttachmentIndices;

    // maps of command buffer recording id -> dynamic line width state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicLineWidths;

    // maps of command buffer recording id -> dynamic depth bounds state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthBounds;

    // maps of command buffer recording id -> dynamic depth bounds test enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthBoundsTestEnable;

    // maps of command buffer recording id -> dynamic depth bias state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthBias;

    // maps of command buffer recording id -> dynamic depth bias enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthBiasEnable;

    // maps of command buffer recording id -> dynamic depth test enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthTestEnable;

    // maps of command buffer recording id -> dynamic depth write enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthWriteEnable;

    // maps of command buffer recording id -> dynamic depth compare op state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicDepthCompareOps;

    // maps of command buffer recording id -> dynamic stencil compare mask front state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilCompareMaskFront;

    // maps of command buffer recording id -> dynamic stencil compare mask back state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilCompareMaskBack;

    // maps of command buffer recording id -> dynamic stencil write mask front state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilWriteMaskFront;

    // maps of command buffer recording id -> dynamic stencil write mask back state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilWriteMaskBack;

    // maps of command buffer recording id -> dynamic stencil reference front state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilReferenceFront;

    // maps of command buffer recording id -> dynamic stencil Reference back state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilReferenceBack;

    // maps of command buffer recording id -> dynamic stencil test enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilTestEnable;

    // maps of command buffer recording id -> dynamic stencil ops front state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilOpsFront;

    // maps of command buffer recording id -> dynamic stencil ops back state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicStencilOpsBack;

    // maps of command buffer recording id -> attachment index -> dynamic color write enable state id
    std::map<int64_t, std::map<uint32_t, int64_t>> commandBufferRecordingDynamicColorWriteEnable;

    // maps of command buffer recording id -> dynamic blend constant state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicBlendConstants;

    // maps of command buffer recording id -> dynamic primitive topology state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicPrimitiveTopologies;

    // maps of command buffer recording id -> dynamic cull mode state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicCullModes;

    // maps of command buffer recording id -> dynamic front face state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicFrontFaces;

    // maps of command buffer recording id -> dynamic logic op state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicLogicOps;

    // maps of command buffer recording id -> dynamic rasterizer discard enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicRasterizerDiscardEnable;

    // maps of command buffer recording id -> dynamic patch control points state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicPatchControlPoints;

    // maps of command buffer recording id -> dynamic primitive restart enable state id
    std::map<int64_t, int64_t> commandBufferRecordingDynamicPrimitiveRestartEnable;

    int64_t currentPipelineLayoutId = 0;
    std::map<int64_t, int64_t> pipelineLayoutHandleToId;

    // map of pipeline layout id -> descriptor set index -> descriptor set layout id
    // will not have an entry if a null descriptor set layout was used
    std::map<int64_t, std::map<int64_t, int64_t>> pipelineLayoutSetIndexToLayoutId;

    int64_t currentVertexInputStateId = 0;
    int64_t currentInputAssemblyStateId = 0;
    int64_t currentTessellationStateId = 0;
    int64_t currentViewportStateId = 0;
    int64_t currentRasterizationStateId = 0;
    int64_t currentMultisampleStateId = 0;
    int64_t currentDepthStencilStateId = 0;
    int64_t currentColorBlendStateId = 0;

    int64_t currentQueueId = 0;
    std::map<int64_t, int64_t> queueHandleToId;

    int64_t currentQueueSubmissionId = 0;
    int64_t currentQueueSubmissionBatchId = 0;
    int64_t currentQueuePresentId = 0;
    int64_t currentQueuePresentSwapchainId = 0;

    int64_t currentFramebufferId = 0;
    std::map<int64_t, int64_t> framebufferHandleToId;

    int64_t currentFramebufferAttachmentInfoId = 0;

    int64_t currentDisplayId = 0;
    std::map<int64_t, int64_t> displayHandleToId;

    int64_t currentDisplayModeId = 0;
    std::map<int64_t, int64_t> displayModeHandleToId;

    int64_t currentSwapchainId = 0;
    std::map<int64_t, int64_t> swapchainHandleToId;

    int64_t currentAcquireNextImageId = 0;

    int64_t currentSamplerId = 0;
    std::map<int64_t, int64_t> samplerHandleToId;

    int64_t currentSamplerYcbcrConversionId = 0;
    std::map<int64_t, int64_t> samplerYcbcrConversionHandleToId;

    int64_t currentImageId = 0;
    std::map<int64_t, int64_t> imageHandleToId;

    int64_t currentImageViewId = 0;
    std::map<int64_t, int64_t> imageViewHandleToId;

    int64_t currentBufferId = 0;
    std::map<int64_t, int64_t> bufferHandleToId;

    int64_t currentBufferViewId = 0;
    std::map<int64_t, int64_t> bufferViewHandleToId;

    int64_t currentAccelerationStructureId = 0;
    std::map<int64_t, int64_t> accelerationStructureHandleToId;

    int64_t currentAccelerationStructureNvId = 0;
    std::map<int64_t, int64_t> accelerationStructureNvHandleToId;

    int64_t currentAccelerationStructureBuildId = 0;
    int64_t currentAccelerationStructureBuildGeometryInfoId = 0;
    int64_t currentAccelerationStructureBuildTriangleDataId = 0;
    int64_t currentAccelerationStructureBuildAABBDataId = 0;
    int64_t currentAccelerationStructureBuildInstanceDataId = 0;
    int64_t currentAccelerationStructureCopyId = 0;

    int64_t currentDeferredOperationId = 0;
    std::map<int64_t, int64_t> deferredOperationHandleToId;

    int64_t currentPipelineBinaryId = 0;
    std::map<int64_t, int64_t> pipelineBinaryHandleToId;

    int64_t currentVideoSessionId = 0;
    std::map<int64_t, int64_t> videoSessionHandleToId;

    int64_t currentVideoSessionParametersId = 0;
    std::map<int64_t, int64_t> videoSessionParametersHandleToId;

    int64_t currentIndirectCommandsLayoutId = 0;
    std::map<int64_t, int64_t> indirectCommandsLayoutHandleToId;

    int64_t currentMicromapId = 0;
    std::map<int64_t, int64_t> micromapHandleToId;

    int64_t currentOpticalFlowSessionId = 0;
    std::map<int64_t, int64_t> opticalFlowSessionHandleToId;

    int64_t currentDataGraphPipelineInfoId = 0;
    int64_t currentDataGraphPipelineSessionId = 0;
    std::map<int64_t, int64_t> dataGraphPipelineSessionHandleToId;

    // Cache of pipeline ID -> set of dynamic states declared by that pipeline
    // Populated during pipeline creation, used during pipeline binding to invalidate static states
    std::map<int64_t, std::unordered_set<VkDynamicState>> pipelineIdToDynamicStates;

    std::unordered_set<uint64_t> pNextWarnings;

    bool IsDeviceFeatureEnabled(int64_t deviceId, const std::string& feature)
    {
        auto enabledDeviceFeaturesIter = deviceIdToEnabledFeatures.find(deviceId);
        if (enabledDeviceFeaturesIter != deviceIdToEnabledFeatures.end())
        {
            auto featureIter = enabledDeviceFeaturesIter->second.find(feature);
            if (featureIter != enabledDeviceFeaturesIter->second.end())
            {
                return true;
            }
        }
        return false;
    }

    void InvalidateDynamicStates(
        int64_t commandBufferRecordingId,
        VkPipelineBindPoint bindPoint,
        const std::unordered_set<VkDynamicState>& declaredDynamicStates
    )
    {
        // Helper lambda to check if a dynamic state is NOT declared (should be invalidated)
        auto shouldInvalidate = [&declaredDynamicStates](VkDynamicState state) {
            return declaredDynamicStates.find(state) == declaredDynamicStates.end();
        };

        // ===== GRAPHICS PIPELINE DYNAMIC STATES =====
        if (bindPoint == VK_PIPELINE_BIND_POINT_GRAPHICS)
        {
            // Viewport and Scissor
            if (shouldInvalidate(VK_DYNAMIC_STATE_VIEWPORT))
            {
                commandBufferRecordingDynamicViewports.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_SCISSOR))
            {
                commandBufferRecordingDynamicScissors.erase(commandBufferRecordingId);
            }

            // Rasterization
            if (shouldInvalidate(VK_DYNAMIC_STATE_LINE_WIDTH))
            {
                commandBufferRecordingDynamicLineWidths.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_CULL_MODE))
            {
                commandBufferRecordingDynamicCullModes.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_FRONT_FACE))
            {
                commandBufferRecordingDynamicFrontFaces.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE))
            {
                commandBufferRecordingDynamicRasterizerDiscardEnable.erase(commandBufferRecordingId);
            }

            // Depth Bias
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_BIAS))
            {
                commandBufferRecordingDynamicDepthBias.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE))
            {
                commandBufferRecordingDynamicDepthBiasEnable.erase(commandBufferRecordingId);
            }

            // Depth Testing
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_BOUNDS))
            {
                commandBufferRecordingDynamicDepthBounds.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE))
            {
                commandBufferRecordingDynamicDepthBoundsTestEnable.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE))
            {
                commandBufferRecordingDynamicDepthTestEnable.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE))
            {
                commandBufferRecordingDynamicDepthWriteEnable.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_DEPTH_COMPARE_OP))
            {
                commandBufferRecordingDynamicDepthCompareOps.erase(commandBufferRecordingId);
            }

            // Stencil Testing
            if (shouldInvalidate(VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK))
            {
                commandBufferRecordingDynamicStencilCompareMaskFront.erase(commandBufferRecordingId);
                commandBufferRecordingDynamicStencilCompareMaskBack.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_STENCIL_WRITE_MASK))
            {
                commandBufferRecordingDynamicStencilWriteMaskFront.erase(commandBufferRecordingId);
                commandBufferRecordingDynamicStencilWriteMaskBack.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_STENCIL_REFERENCE))
            {
                commandBufferRecordingDynamicStencilReferenceFront.erase(commandBufferRecordingId);
                commandBufferRecordingDynamicStencilReferenceBack.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE))
            {
                commandBufferRecordingDynamicStencilTestEnable.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_STENCIL_OP))
            {
                commandBufferRecordingDynamicStencilOpsFront.erase(commandBufferRecordingId);
                commandBufferRecordingDynamicStencilOpsBack.erase(commandBufferRecordingId);
            }

            // Blending
            if (shouldInvalidate(VK_DYNAMIC_STATE_BLEND_CONSTANTS))
            {
                commandBufferRecordingDynamicBlendConstants.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_LOGIC_OP_EXT))
            {
                commandBufferRecordingDynamicLogicOps.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT))
            {
                commandBufferRecordingDynamicColorWriteEnable.erase(commandBufferRecordingId);
            }

            // Input Assembly
            if (shouldInvalidate(VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY))
            {
                commandBufferRecordingDynamicPrimitiveTopologies.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE))
            {
                commandBufferRecordingDynamicPrimitiveRestartEnable.erase(commandBufferRecordingId);
            }

            // Tessellation
            if (shouldInvalidate(VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT))
            {
                commandBufferRecordingDynamicPatchControlPoints.erase(commandBufferRecordingId);
            }

            // Vertex Input
            if (shouldInvalidate(VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE))
            {
                commandBufferRecordingVertexInputBindingDescriptions.erase(commandBufferRecordingId);
            }
            if (shouldInvalidate(VK_DYNAMIC_STATE_VERTEX_INPUT_EXT))
            {
                commandBufferRecordingVertexInputBindingDescriptions.erase(commandBufferRecordingId);
                commandBufferRecordingVertexInputAttributeDescriptions.erase(commandBufferRecordingId);
            }
        }
        // ===== COMPUTE PIPELINE DYNAMIC STATES =====
        else if (bindPoint == VK_PIPELINE_BIND_POINT_COMPUTE)
        {
            // Currently no dynamic states specific to compute pipelines in Vulkan spec
            // This section is for future extensibility
        }
        // ===== RAY TRACING PIPELINE DYNAMIC STATES =====
        else if (bindPoint == VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR)
        {
            // Currently no dynamic states specific to ray tracing pipelines in Vulkan spec
            // This section is for future extensibility
        }
        // ===== DATA GRAPH PIPELINE DYNAMIC STATES =====
        else if (bindPoint == VK_PIPELINE_BIND_POINT_DATA_GRAPH_ARM)
        {
            // Currently no dynamic states specific to data graph pipelines
            // This section is for future extensibility
        }
    }

    std::optional<int64_t> GetDeviceId(format::HandleId device, bool allowNull = false) const
    {
        return GetId(device, deviceHandleToId, "device", allowNull);
    }

    std::optional<int64_t> GetDeviceId(int64_t deviceHandle, bool allowNull = false) const
    {
        // this will just end up getting cast back to int64_t which is fine
        return GetId(static_cast<format::HandleId>(deviceHandle), deviceHandleToId, "device", allowNull);
    }

    std::optional<int64_t> GetPhysicalDeviceId(format::HandleId physicalDevice, bool allowNull = false) const
    {
        return GetId(physicalDevice, physicalDeviceHandleToId, "physical device", allowNull);
    }

    std::optional<int64_t> GetQueueId(format::HandleId queue, bool allowNull = false) const
    {
        return GetId(queue, queueHandleToId, "queue", allowNull);
    }

    std::optional<int64_t> GetFenceId(format::HandleId fence, bool allowNull = false) const
    {
        return GetId(fence, fenceHandleToId, "fence", allowNull);
    }

    std::optional<int64_t> GetFenceSyncScopeId(format::HandleId fence, bool allowNull = false) const
    {
        return GetId(fence, fenceHandleToSyncScopeId, "fence instance", allowNull);
    }

    format::HandleId GetDeviceFromCommandBuffer(const format::HandleId commandBuffer) const
    {
        auto it = commandBufferHandleToDevice.find(ToInt64(commandBuffer));
        return it != commandBufferHandleToDevice.end() ? it->second : gfxrecon::format::kNullHandleId;
    }

    std::optional<int64_t> GetSemaphoreId(format::HandleId semaphore, bool allowNull = false) const
    {
        return GetId(semaphore, semaphoreHandleToId, "semaphore", allowNull);
    }

    std::optional<int64_t> GetPipelineLayoutId(format::HandleId layout, bool allowNull = false) const
    {
        return GetId(layout, pipelineLayoutHandleToId, "pipeline layout", allowNull);
    }

    std::optional<int64_t> GetDescriptorSetLayoutId(format::HandleId layout, bool allowNull = false) const
    {
        return GetId(layout, descriptorSetLayoutHandleToId, "descriptor set layout", allowNull);
    }

    std::optional<int64_t> GetCommandPoolId(format::HandleId commandPool, bool allowNull = false) const
    {
        return GetId(commandPool, commandPoolHandleToId, "command pool", allowNull);
    }

    std::optional<int64_t> GetBufferId(format::HandleId buffer, bool allowNull = false) const
    {
        return GetId(buffer, bufferHandleToId, "buffer", allowNull);
    }

    std::optional<int64_t> GetBufferViewId(format::HandleId bufferView, bool allowNull = false) const
    {
        return GetId(bufferView, bufferViewHandleToId, "buffer view", allowNull);
    }

    std::optional<int64_t> GetImageId(format::HandleId image, bool allowNull = false) const
    {
        return GetId(image, imageHandleToId, "image", allowNull);
    }

    std::optional<int64_t> GetImageViewId(format::HandleId image, bool allowNull = false) const
    {
        return GetId(image, imageViewHandleToId, "image view", allowNull);
    }

    std::optional<int64_t> GetSamplerId(format::HandleId image, bool allowNull = false) const
    {
        return GetId(image, samplerHandleToId, "sampler", allowNull);
    }

    std::optional<int64_t> GetSamplerYcbcrConversionId(
        format::HandleId samplerYcbcrConversion, bool allowNull = false
    ) const
    {
        return GetId(samplerYcbcrConversion, samplerYcbcrConversionHandleToId, "sampler ycbcr conversion", allowNull);
    }

    std::optional<int64_t> GetAccelerationStructureId(
        format::HandleId accelerationStructure, bool allowNull = false
    ) const
    {
        return GetId(accelerationStructure, accelerationStructureHandleToId, "acceleration structure", allowNull);
    }

    std::optional<int64_t> GetAccelerationStructureNvId(
        format::HandleId accelerationStructureNv, bool allowNull = false
    ) const
    {
        return GetId(
            accelerationStructureNv, accelerationStructureNvHandleToId, "acceleration structure nv", allowNull
        );
    }

    std::optional<int64_t> GetFramebufferId(format::HandleId framebuffer, bool allowNull = false) const
    {
        return GetId(framebuffer, framebufferHandleToId, "framebuffer", allowNull);
    }

    std::optional<int64_t> GetCommandBufferId(format::HandleId commandBuffer, bool allowNull = false) const
    {
        return GetId(commandBuffer, commandBufferHandleToId, "command buffer", allowNull);
    }

    std::optional<int64_t> GetCommandBufferRecordingId(format::HandleId commandBuffer, bool allowNull = false) const
    {
        return GetId(commandBuffer, commandBufferHandleToRecordingId, "command buffer recording", allowNull);
    }

    std::optional<int64_t> GetRenderPassId(format::HandleId renderPass, bool allowNull = false) const
    {
        return GetId(renderPass, renderPassHandleToId, "render pass", allowNull);
    }

    std::optional<int64_t> GetDeferredOperationId(format::HandleId deferredOperation, bool allowNull = false) const
    {
        return GetId(deferredOperation, deferredOperationHandleToId, "deferred operation", allowNull);
    }

    std::optional<int64_t> GetSwapchainId(format::HandleId swapchain, bool allowNull = false) const
    {
        return GetId(swapchain, swapchainHandleToId, "swapchain", allowNull);
    }

    std::optional<int64_t> GetVideoSessionId(format::HandleId videoSession, bool allowNull = false) const
    {
        return GetId(videoSession, videoSessionHandleToId, "video session", allowNull);
    }

    std::optional<int64_t> GetVideoSessionParametersId(
        format::HandleId videoSessionParameters, bool allowNull = false
    ) const
    {
        return GetId(videoSessionParameters, videoSessionParametersHandleToId, "video session parameters", allowNull);
    }

    std::optional<int64_t> GetIndirectCommandsLayoutId(
        format::HandleId indirectCommandsLayout, bool allowNull = false
    ) const
    {
        return GetId(indirectCommandsLayout, indirectCommandsLayoutHandleToId, "indirect commands layout", allowNull);
    }

    std::optional<int64_t> GetMicromapId(format::HandleId micromap, bool allowNull = false) const
    {
        return GetId(micromap, micromapHandleToId, "micromap", allowNull);
    }

    std::optional<int64_t> GetOpticalFlowSessionId(format::HandleId opticalFlowSession, bool allowNull = false) const
    {
        return GetId(opticalFlowSession, opticalFlowSessionHandleToId, "optical flow session", allowNull);
    }

    std::optional<int64_t> GetDataGraphPipelineSessionId(format::HandleId session, bool allowNull = false) const
    {
        return GetId(session, dataGraphPipelineSessionHandleToId, "data graph pipeline session", allowNull);
    }

    std::optional<int64_t> ExtractId(
        format::HandleId handle, std::map<int64_t, int64_t>& handleToId, const char* typeName, uint64_t blockIndex
    )
    {
        if (handle == gfxrecon::format::kNullHandleId)
        {
            return std::nullopt;
        }
        auto iter = handleToId.find(ToInt64(handle));
        if (iter == handleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "<%" PRIu64 ">- Failed to destroy %s, no %s found with handle %" PRIu64,
                blockIndex,
                typeName,
                typeName,
                handle
            );
            return std::nullopt;
        }
        auto id = iter->second;
        handleToId.erase(iter);
        return id;
    }

  private:
    std::optional<int64_t> GetId(
        format::HandleId handle, const std::map<int64_t, int64_t>& handleToId, const char* type, bool allowNull
    ) const
    {
        std::optional<int64_t> id = std::nullopt;
        if (handle == gfxrecon::format::kNullHandleId)
        {
            if (!allowNull)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Null %s handle provided when not allowed; still setting foreign key to NULL", type
                );
            }
            return id;
        }
        auto bufferIter = handleToId.find(ToInt64(handle));
        if (bufferIter == handleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to find %s for handle %" PRIu64 ", setting foreign key to NULL", type, handle
            );
        }
        else
        {
            id = bufferIter->second;
        }
        return id;
    }
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_CONTEXT_H
