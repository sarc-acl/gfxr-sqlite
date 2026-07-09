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

#include "vulkan_sqlite_prepared_statements.h"
#include "vulkan_sqlite_consumer_context.h"
#include "decode/api_event_types.h"
#include "decode/consumer_utils.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void VulkanSqlitePreparedStatements::CreateBasePreparedStatements()
{
    PrepareStatement(db, "INSERT INTO frames VALUES (?, ?, NULL);", &frameInsertStatement);

    PrepareStatement(
        db,
        "INSERT INTO apiEvents VALUES (?, " + std::to_string(APIEventTypes::VULKAN_API) + ", ?, ?, ?);",
        &apiEventVkInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO apiEvents VALUES (?, " + std::to_string(APIEventTypes::META_COMMAND) + ", ?, ?, 0);",
        &apiEventMetaInsertStatement
    );
    PrepareStatement(db, "INSERT INTO apiEventReturns VALUES (?, ?, ?);", &apiEventReturnsInsertStatement);

    PrepareStatement(db, "INSERT INTO functionNames VALUES (?, ?);", &functionNameInsertStatement);

    PrepareStatement(db, "INSERT INTO commandPools VALUES (?, ?, ?, ?, ?, ?, NULL);", &commandPoolInsertStatement);

    PrepareStatement(db, "INSERT INTO commandBuffers VALUES (?, ?, ?, ?, ?, ?, NULL);", &commandBufferInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO commandBufferInheritanceInfos VALUES (?, ?, ?, ?, ?, ?, ?);",
        &commandBufferInheritanceInfoInsertStatement
    );

    PrepareStatement(db, "INSERT INTO commandBufferCommands VALUES (?, ?);", &commandBufferCommandInsertStatement);

    PrepareStatement(db, "INSERT INTO trackedCmdCommands VALUES(?, ?, ?, ?, ?, ?);", &trackedCmdCommandInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO commandBufferRecordings VALUES(?, ?, ?, ?, ?, NULL, NULL, NULL);",
        &commandBufferRecordingInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE commandBufferRecordings SET endApiEventId = ?, endStateGroupId = ? "
        "WHERE(commandBufferRecordings.id = ?);",
        &commandBufferRecordingEndStatement
    );
    PrepareStatement(
        db,
        "UPDATE commandBufferRecordings SET resetApiEventId = ?"
        " WHERE(commandBufferRecordings.resetApiEventId IS NULL"
        " AND commandBufferRecordings.id = ?);",
        &commandBufferRecordingResetStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO renderPassRecordings VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &renderPassRecordingInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderPassRecordings SET endApiEventId = ? "
        "WHERE(renderPassRecordings.id = ?);",
        &renderPassRecordingEndStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO renderPassRecordingClearValues VALUES(?, ?, ?, ?, ?);",
        &renderPassRecordingClearValueInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO renderSubpassRecordings VALUES(?, ?, ?, ?, ?, NULL);", &renderSubpassRecordingInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassRecordings SET endApiEventId = ? "
        "WHERE(renderSubpassRecordings.id = ?);",
        &renderSubpassRecordingEndStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO secondaryCommandBufferExecutionRecordings VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &secondaryCommandBufferExecutionRecordingInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO cmdDrawRecordings VALUES(?, ?, ?, ?, ?, ?, ?, ?);", &cmdDrawRecordingInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdMeshTaskRecordings VALUES(?, ?, ?, ?, ?, ?, ?);", &cmdMeshTaskRecordingInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdClusterRecordings VALUES(?, ?, ?, ?, ?, ?, ?);", &cmdClusterRecordingInsertStatement
    );
    PrepareStatement(db, "INSERT INTO cmdDispatchRecordings VALUES(?, ?, ?, ?);", &cmdDispatchRecordingInsertStatement);
    PrepareStatement(
        db, "INSERT INTO cmdRaytracingRecordings VALUES(?, ?, ?, ?);", &cmdRaytracingRecordingInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO cmdDrawRecordingIndirectInfos VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &cmdDrawRecordingIndirectInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdDrawRecordingInfos VALUES(?, ?, ?, ?, ?, ?, ?, ?);", &cmdDrawRecordingInfoInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO cmdMeshTaskRecordingIndirectInfos VALUES(?, ?, ?, ?, ?, ?, ?, ?);",
        &cmdMeshTaskRecordingIndirectInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdMeshTaskRecordingInfos VALUES(?, ?, ?, ?);", &cmdMeshTaskRecordingInfoInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO cmdClusterRecordingIndirectInfos VALUES(?, ?, ?);",
        &cmdClusterRecordingIndirectInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdClusterRecordingInfos VALUES(?, ?, ?, ?);", &cmdClusterRecordingInfoInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO cmdDispatchRecordingIndirectInfos VALUES(?, ?, ?);",
        &cmdDispatchRecordingIndirectInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO cmdDispatchRecordingBaseInfos VALUES(?, ?, ?, ?);",
        &cmdDispatchRecordingBaseInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO cmdDispatchRecordingInfos VALUES(?, ?, ?, ?);", &cmdDispatchRecordingInfoInsertStatement
    );

    PrepareStatement(db, "INSERT INTO structMembers VALUES (?, ?, ?, ?, ?);", &structMemberInsertStatement);
    PrepareStatement(db, "INSERT INTO arrayMembers VALUES (?, ?, ?, ?);", &arrayMemberInsertStatement);
    PrepareStatement(db, "INSERT INTO apiEventArguments VALUES (?, ?, ?, ?, ?);", &apiEventArgumentInsertStatement);
    PrepareStatement(db, "INSERT INTO structs VALUES (?, ?);", &structInsertStatement);
    PrepareStatement(db, "INSERT INTO arrays VALUES (?, ?);", &arrayInsertStatement);

    PrepareStatement(db, "INSERT INTO displayMessages VALUES (?, ?, ?);", &displayMessageInsertStatement);
    PrepareStatement(db, "INSERT INTO memory VALUES (?, ?, ?, NULL, ?);", &memoryInsertStatement);
    PrepareStatement(db, "INSERT INTO annotations VALUES (?, ?, ?, ?, ?);", &annotationInsertStatement);

    PrepareStatement(
        db,
        "UPDATE commandBuffers SET freeApiEventId = ? WHERE (commandBuffers.id = ?);",
        &freeCommandBufferUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE commandPools SET destroyApiEventId = ? WHERE (commandPools.id = ?);",
        &destroyCommandPoolUpdateStatement
    );
    PrepareStatement(db, "INSERT INTO surfaces VALUES (?, ?, ?, ?, NULL);", &surfaceInsertStatement);
    PrepareStatement(
        db, "UPDATE surfaces SET destroyApiEventId = ? WHERE (surfaces.id = ?);", &destroySurfaceUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderPasses SET destroyApiEventId = ? WHERE (renderPasses.id = ?);",
        &destroyRenderPassUpdateStatement
    );
}

void VulkanSqlitePreparedStatements::CreateAdvancedPreparedStatements()
{
    PrepareStatement(db, "INSERT INTO instances VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);", &instanceInsertStatement);

    PrepareStatement(db, "INSERT INTO instanceEnabledLayers VALUES (?, ?, ?);", &instanceEnabledLayerInsertStatement);

    PrepareStatement(
        db, "INSERT INTO instanceEnabledLayerSettings VALUES (?, ?, ?, ?);", &instanceEnabledLayerSettingInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO instanceEnabledLayerSettingValues VALUES (?, ?, ?);",
        &instanceEnabledLayerSettingValueInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO instanceEnabledExtensions VALUES (?, ?);", &instanceEnabledExtensionInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO instanceValidationEnabledFeatures VALUES (?, ?);",
        &instanceValidationEnabledFeatureInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO instanceValidationDisabledFeatures VALUES (?, ?);",
        &instanceValidationDisabledFeatureInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO instanceValidationDisabledChecks VALUES (?, ?);",
        &instanceValidationDisabledCheckInsertStatement
    );

    PrepareStatement(db, "INSERT INTO devices VALUES (?, ?, ?, ?, ?, NULL);", &deviceInsertStatement);

    PrepareStatement(db, "INSERT INTO deviceEnabledLayers VALUES (?, ?);", &deviceEnabledLayerInsertStatement);

    PrepareStatement(db, "INSERT INTO deviceEnabledExtensions VALUES (?, ?);", &deviceEnabledExtensionInsertStatement);

    PrepareStatement(db, "INSERT INTO deviceEnabledFeatures VALUES (?, ?);", &deviceEnabledFeatureInsertStatement);

    PrepareStatement(
        db, "INSERT INTO trackedDeviceCommands VALUES (?, ?, ?, ?);", &trackedDeviceCommandInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO dynamicRenderPassRecordings VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &dynamicRenderPassRecordingInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE dynamicRenderPassRecordings SET endApiEventId = ? "
        "WHERE(dynamicRenderPassRecordings.id = ?);",
        &dynamicRenderPassRecordingEndStatement
    );
    PrepareStatement(
        db, "INSERT INTO unionColors VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", &unionColorInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO renderingAttachments VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &renderingAttachmentInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO dynamicColorAttachments VALUES(?, ?, ?);", &dynamicColorAttachmentInsertStatement
    );

    PrepareStatement(db, "INSERT INTO stateIds VALUES(?, ?);", &stateIdInsertStatement);
    PrepareStatement(db, "INSERT INTO stateGroupEntries VALUES(?, ?, ?, ?, ?);", &stateGroupEntryInsertStatement);

    PrepareStatement(db, "INSERT INTO statePipelineBindings VALUES(?, ?, ?, ?);", &statePipelineBindingInsertStatement);
    PrepareStatement(
        db, "INSERT INTO stateShaderObjectBindings VALUES(?, ?, ?, ?);", &stateShaderObjectBindingInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO stateIndexBufferBindings VALUES (?, ?, ?, ?, ?, ?);", &stateIndexBufferBindingInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateVertexBufferBindings VALUES (?, ?, ?, ?, ?, ?, ?);",
        &stateVertexBufferBindingInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetBindings VALUES (?, ?, ?, ?, ?, ?);",
        &stateDescriptorSetBindingInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetBindingDynamicOffsets VALUES (?, ?, ?, ?);",
        &stateDescriptorSetBindingDynamicOffsetInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO stateDescriptorSetPushes VALUES (?, ?, ?, ?, ?, ?);", &stateDescriptorSetPushInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO stateDynamicVertexInputBindingDescriptions VALUES (?, ?, ?, ?, ?);",
        &stateDynamicVertexInputBindingDescriptionInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicVertexInputAttributeDescriptions VALUES (?, ?, ?, ?, ?, ?);",
        &stateDynamicVertexInputAttributeDescriptionInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicViewports VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &stateDynamicViewportInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicScissors VALUES (?, ?, ?, ?, ?, ?, ?);", &stateDynamicScissorInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO stateDynamicRenderingColorAttachmentLocations VALUES (?, ?, ?, ?);",
        &stateDynamicRenderingColorAttachmentLocationInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicRenderingInputColorAttachmentIndices VALUES (?, ?, ?, ?);",
        &stateDynamicRenderingInputColorAttachmentIndexInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicRenderingInputDepthAttachmentIndices VALUES (?, ?, ?);",
        &stateDynamicRenderingInputDepthAttachmentIndexInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicRenderingInputStencilAttachmentIndices VALUES (?, ?, ?);",
        &stateDynamicRenderingInputStencilAttachmentIndexInsertStatement
    );
    PrepareStatement(db, "INSERT INTO stateDynamicLineWidths VALUES (?, ?, ?);", &stateDynamicLineWidthInsertStatement);
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthBounds VALUES (?, ?, ?, ?);", &stateDynamicDepthBoundsInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicDepthBoundsTestEnable VALUES (?, ?, ?);",
        &stateDynamicDepthBoundsTestEnableInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthBias VALUES (?, ?, ?, ?, ?, ?, ?);", &stateDynamicDepthBiasInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthBiasEnable VALUES (?, ?, ?);", &stateDynamicDepthBiasEnableInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthTestEnable VALUES (?, ?, ?);", &stateDynamicDepthTestEnableInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthWriteEnable VALUES (?, ?, ?);", &stateDynamicDepthWriteEnableInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicDepthCompareOps VALUES (?, ?, ?);", &stateDynamicDepthCompareOpInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilCompareMasksFront VALUES (?, ?, ?);",
        &stateDynamicStencilCompareMaskFrontInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilCompareMasksBack VALUES (?, ?, ?);",
        &stateDynamicStencilCompareMaskBackInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilWriteMasksFront VALUES (?, ?, ?);",
        &stateDynamicStencilWriteMaskFrontInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilWriteMasksBack VALUES (?, ?, ?);",
        &stateDynamicStencilWriteMaskBackInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilReferencesFront VALUES (?, ?, ?);",
        &stateDynamicStencilReferenceFrontInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilReferencesBack VALUES (?, ?, ?);",
        &stateDynamicStencilReferenceBackInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO stateDynamicStencilTestEnable VALUES (?, ?, ?);", &stateDynamicStencilTestEnableInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilOpsFront VALUES (?, ?, ?, ?, ?, ?);",
        &stateDynamicStencilOpsFrontInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicStencilOpsBack VALUES (?, ?, ?, ?, ?, ?);",
        &stateDynamicStencilOpsBackInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicColorWriteEnable VALUES (?, ?, ?, ?);",
        &stateDynamicColorWriteEnableInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicBlendConstants VALUES (?, ?, ?, ?, ?, ?);",
        &stateDynamicBlendConstantInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicPrimitiveTopologies VALUES (?, ?, ?);",
        &stateDynamicPrimitiveTopologyInsertStatement
    );
    PrepareStatement(db, "INSERT INTO stateDynamicCullModes VALUES (?, ?, ?);", &stateDynamicCullModeInsertStatement);
    PrepareStatement(db, "INSERT INTO stateDynamicFrontFaces VALUES (?, ?, ?);", &stateDynamicFrontFaceInsertStatement);
    PrepareStatement(db, "INSERT INTO stateDynamicLogicOps VALUES (?, ?, ?);", &stateDynamicLogicOpInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicRasterizerDiscardEnable VALUES (?, ?, ?);",
        &stateDynamicRasterizerDiscardEnableInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicPatchControlPoints VALUES (?, ?, ?);",
        &stateDynamicPatchControlPointInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDynamicPrimitiveRestartEnable VALUES (?, ?, ?);",
        &stateDynamicPrimitiveRestartEnableInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO images VALUES (?, ?, ?, NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &imageInsertStatement
    );
    PrepareStatement(db, "INSERT INTO imageViewFormats VALUES (?, ?);", &imageViewFormatInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO imageViews VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &imageViewInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO samplers VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &samplerInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO swapchains VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &swapchainInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO images"
        " SELECT ?, ?, ?, ?, NULL, ?,"
        " swapchains.imageFormat, swapchains.imageWidth, swapchains.imageHeight,"
        " ?, ?, swapchains.imageLayers, ?, ?, swapchains.imageUsage, swapchains.imageSharing,"
        " ?, NULL, NULL, swapchains.createApiEventId, NULL"
        " FROM swapchains WHERE swapchains.id = ?;",
        &swapchainImageInsertStatement
    );
    PrepareStatement(db, "INSERT INTO buffers VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);", &bufferInsertStatement);
    PrepareStatement(db, "INSERT INTO bufferViews VALUES (?, ?, ?, ?, ?, ?, ?, ?, NULL);", &bufferViewInsertStatement);

    PrepareStatement(
        db,
        "INSERT INTO descriptorUpdateTemplates VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &descriptorUpdateTemplateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO descriptorUpdateTemplateEntries VALUES (?, ?, ?, ?, ?, ?, ?);",
        &descriptorUpdateTemplateEntryInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO descriptorSetWrites VALUES (?, ?, ?, ?, ?, ?);", &descriptorSetWriteInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO descriptorSetWriteImageInfos VALUES (?, ?, ?, ?);", &descriptorSetWriteImageInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO descriptorSetWriteBufferInfos VALUES (?, ?, ?, ?);",
        &descriptorSetWriteBufferInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO descriptorSetWriteTexelInfos VALUES (?, ?);", &descriptorSetWriteTexelInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO descriptorSetWriteAccelerationInfos VALUES (?, ?);",
        &descriptorSetWriteAccelerationInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO descriptorSetWriteAccelerationNvInfos VALUES (?, ?);",
        &descriptorSetWriteAccelerationNvInfoInsertStatement
    );
    PrepareStatement(
        db,
        "WITH image_info (samplerId, imageViewId, imageLayout, max_write) AS ("
        "  SELECT dswii.samplerId, dswii.imageViewId, dswii.imageLayout, max(dsw.id)"
        "  FROM descriptorSetWrites AS dsw"
        "  JOIN descriptorSetWriteImageInfos AS dswii"
        "    ON dswii.descriptorSetWriteId = dsw.id"
        "  WHERE dsw.descriptorSetId = ?"
        "    AND binding = ?"
        "    AND arrayElement = ?"
        "  LIMIT 1)"
        "INSERT OR IGNORE INTO descriptorSetWriteImageInfos"
        "  SELECT ?, samplerId, imageViewId, imageLayout"
        "  FROM image_info;",
        &descriptorSetCopyImageInfoInsertStatement
    );
    PrepareStatement(
        db,
        "WITH buffer_info (bufferId, offset, range, max_write) AS ("
        "  SELECT dswbi.bufferId, dswbi.offset, dswbi.range, max(dsw.id)"
        "  FROM descriptorSetWrites AS dsw"
        "  JOIN descriptorSetWriteBufferInfos AS dswbi"
        "    ON dswbi.descriptorSetWriteId = dsw.id"
        "  WHERE dsw.descriptorSetId = ?"
        "    AND binding = ?"
        "    AND arrayElement = ?"
        "  LIMIT 1)"
        "INSERT OR IGNORE INTO descriptorSetWriteBufferInfos"
        "  SELECT ?, bufferId, offset, range"
        "  FROM buffer_info;",
        &descriptorSetCopyBufferInfoInsertStatement
    );
    PrepareStatement(
        db,
        "WITH texel_info (texelBufferViewId, max_write) AS ("
        "  SELECT dswti.texelBufferViewId, max(dsw.id)"
        "  FROM descriptorSetWrites AS dsw"
        "  JOIN descriptorSetWriteTexelInfos AS dswti"
        "    ON dswti.descriptorSetWriteId = dsw.id"
        "  WHERE dsw.descriptorSetId = ?"
        "    AND binding = ?"
        "    AND arrayElement = ?"
        "  LIMIT 1)"
        "INSERT OR IGNORE INTO descriptorSetWriteTexelInfos"
        "  SELECT ?, texelBufferViewId"
        "  FROM texel_info;",
        &descriptorSetCopyTexelInfoInsertStatement
    );
    PrepareStatement(
        db,
        "WITH acceleration_info (accelerationStructureId, max_write) AS ("
        "  SELECT dsas.accelerationStructureId, max(dsw.id)"
        "  FROM descriptorSetWrites AS dsw"
        "  JOIN descriptorSetWriteAccelerationInfos AS dsas"
        "    ON dsas.descriptorSetWriteId = dsw.id"
        "  WHERE dsw.descriptorSetId = ?"
        "    AND binding = ?"
        "    AND arrayElement = ?"
        "  LIMIT 1)"
        "INSERT OR IGNORE INTO descriptorSetWriteAccelerationInfos"
        "  SELECT ?, accelerationStructureId"
        "  FROM acceleration_info;",
        &descriptorSetCopyAccelerationInfoInsertStatement
    );
    PrepareStatement(
        db,
        "WITH acceleration_info (accelerationStructureNvId, max_write) AS ("
        "  SELECT dsas.accelerationStructureNvId, max(dsw.id)"
        "  FROM descriptorSetWrites AS dsw"
        "  JOIN descriptorSetWriteAccelerationNvInfos AS dsas"
        "    ON dsas.descriptorSetWriteId = dsw.id"
        "  WHERE dsw.descriptorSetId = ?"
        "    AND binding = ?"
        "    AND arrayElement = ?"
        "  LIMIT 1)"
        "INSERT OR IGNORE INTO descriptorSetWriteAccelerationNvInfos"
        "  SELECT ?, accelerationStructureNvId"
        "  FROM acceleration_info;",
        &descriptorSetCopyAccelerationNvInfoInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetPushImageInfos VALUES (?, ?, ?, ?);",
        &stateDescriptorSetPushImageInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetPushBufferInfos VALUES (?, ?, ?, ?);",
        &stateDescriptorSetPushBufferInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetPushTexelInfos VALUES (?, ?);",
        &stateDescriptorSetPushTexelInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetPushAccelerationInfos VALUES (?, ?);",
        &stateDescriptorSetPushAccelerationInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO stateDescriptorSetPushAccelerationNvInfos VALUES (?, ?);",
        &stateDescriptorSetPushAccelerationNvInfoInsertStatement
    );

    PrepareStatement(
        db,
        "UPDATE descriptorSets SET freeApiEventId = ?"
        " WHERE (descriptorSets.descriptorPoolId = ? AND descriptorSets.freeApiEventId IS NULL);",
        &freePoolDescriptorSetsUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE descriptorSets SET freeApiEventId = ? WHERE (descriptorSets.id = ?);",
        &freeDescriptorSetUpdateStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO accelerationStructures VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &accelerationStructureInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructuresNv VALUES(?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &accelerationStructureNvInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuilds VALUES(?, ?, ?, ?, ?, ?);",
        &accelerationStructureBuildInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildGeometryInfos VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &accelerationStructureBuildGeometryInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildGeometries VALUES(?, ?, ?, ?, ?, ?, ?);",
        &accelerationStructureBuildGeometryInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildRangeInfos VALUES(?, ?, ?, ?, ?, ?);",
        &accelerationStructureBuildRangeInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildTriangleDatas VALUES(?, ?, ?, ?, ?, ?, ?, ?);",
        &accelerationStructureBuildTriangleDataInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildAABBDatas VALUES(?, ?, ?);",
        &accelerationStructureBuildAabbDataInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureBuildInstanceDatas VALUES(?, ?, ?);",
        &accelerationStructureBuildInstanceDataInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO accelerationStructureCopies VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &accelerationStructureCopyInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO transferCommands (apiEventId, commandBufferRecordingId, frameId) VALUES(?, ?, ?);",
        &transferCommandInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE transferCommands SET srcBufferId = ?, dstBufferId = ? WHERE id = ?;",
        &transferCommandBufferCopyUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE transferCommands SET srcImageId = ?, dstImageId = ?, srcImageLayoutId = ?, dstImageLayoutId = ? WHERE "
        "id = ?;",
        &transferCommandImageCopyUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE transferCommands SET bufferImageSrcBufferId = ?, bufferImageDstImageId = ?, dstImageLayoutId = ? "
        "WHERE id = ?;",
        &transferCommandBufferToImageUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE transferCommands SET bufferImageSrcImageId = ?, bufferImageDstBufferId = ?, srcImageLayoutId = ? "
        "WHERE id = ?;",
        &transferCommandImageToBufferUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE transferCommands SET srcImageId = ?, dstImageId = ?, srcImageLayoutId = ?, dstImageLayoutId = ?, "
        "blitFilter = ? WHERE id = ?;",
        &transferCommandBlitUpdateStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO transferCommandRegionBufferCopies VALUES(?, ?, ?, ?, ?, ?, ?);",
        &transferCommandRegionBufferCopiesInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO transferCommandRegionImageCopies VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
        "?, ?, "
        "?);",
        &transferCommandRegionImageCopiesInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO transferCommandRegionBufferImageCopies VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &transferCommandRegionBufferImageCopiesInsertStatement
    );

    PrepareStatement(
        db,
        "UPDATE debugReportCallbacks SET destroyApiEventId = ? WHERE (debugReportCallbacks.id = ?);",
        &destroyDebugReportCallbackUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE debugMessengers SET destroyApiEventId = ? WHERE (debugMessengers.id = ?);",
        &destroyDebugMessengerUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE instances SET destroyApiEventId = ? WHERE (instances.id = ?);", &destroyInstanceUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE devices SET destroyApiEventId = ? WHERE (devices.id = ?);", &destroyDeviceUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE fences SET destroyApiEventId = ? WHERE (fences.id = ?);", &destroyFenceUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE semaphores SET destroyApiEventId = ? WHERE (semaphores.id = ?);", &destroySemaphoreUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE events SET destroyApiEventId = ? WHERE (events.id = ?);", &destroyEventUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE queryPools SET destroyApiEventId = ? WHERE (queryPools.id = ?);", &destroyQueryPoolUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE shaderObjects SET destroyApiEventId = ? WHERE (shaderObjects.id = ?);",
        &destroyShaderObjectUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE shaderModules SET destroyApiEventId = ? WHERE (shaderModules.id = ?);",
        &destroyShaderModuleUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE shaderModules SET destroyApiEventId = ?"
        " WHERE shaderModules.createApiEventId = (SELECT createApiEventId"
        " FROM pipelines WHERE pipelines.id = ?);",
        &destroyPipelineAnonymousShaderModulesUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE validationCaches SET destroyApiEventId = ? WHERE (validationCaches.id = ?);",
        &destroyValidationCacheUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE pipelineCaches SET destroyApiEventId = ? WHERE (pipelineCaches.id = ?);",
        &destroyPipelineCacheUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE pipelines SET destroyApiEventId = ? WHERE (pipelines.id = ?);", &destroyPipelineUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE pipelineLayouts SET destroyApiEventId = ? WHERE (pipelineLayouts.id = ?);",
        &destroyPipelineLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE descriptorSetLayouts SET destroyApiEventId = ? WHERE (descriptorSetLayouts.id = ?);",
        &destroyDescriptorSetLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE descriptorPools SET destroyApiEventId = ? WHERE (descriptorPools.id = ?);",
        &destroyDescriptorPoolUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE samplerYcbcrConversions SET destroyApiEventId = ? WHERE (samplerYcbcrConversions.id = ?);",
        &destroySamplerYcbcrConversionUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE privateDataSlots SET destroyApiEventId = ? WHERE (privateDataSlots.id = ?);",
        &destroyPrivateDataSlotUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE descriptorUpdateTemplates SET destroyApiEventId = ? WHERE (descriptorUpdateTemplates.id = ?);",
        &destroyDescriptorUpdateTemplateUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE buffers SET destroyApiEventId = ? WHERE (buffers.id = ?);", &destroyBufferUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE bufferViews SET destroyApiEventId = ? WHERE (bufferViews.id = ?);",
        &destroyBufferViewUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE images SET destroyApiEventId = ? WHERE (images.id = ?);", &destroyImageUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE imageViews SET destroyApiEventId = ? WHERE (imageViews.id = ?);", &destroyImageViewUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE samplers SET destroyApiEventId = ? WHERE (samplers.id = ?);", &destroySamplerUpdateStatement
    );
    PrepareStatement(
        db, "UPDATE swapchains SET destroyApiEventId = ? WHERE (swapchains.id = ?);", &destroySwapchainUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE images SET destroyApiEventId = ? WHERE (images.swapchainId = ?);",
        &destroySwapchainImagesUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE framebuffers SET destroyApiEventId = ? WHERE (framebuffers.id = ?);",
        &destroyFramebufferUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE accelerationStructures SET destroyApiEventId = ? WHERE (accelerationStructures.id = ?);",
        &destroyAccelerationStructureUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE accelerationStructuresNv SET destroyApiEventId = ? WHERE (accelerationStructuresNv.id = ?);",
        &destroyAccelerationStructureNvUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE deferredOperations SET destroyApiEventId = ? WHERE (deferredOperations.id = ?);",
        &destroyDeferredOperationUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE pipelineBinaries SET destroyApiEventId = ? WHERE (pipelineBinaries.id = ?);",
        &destroyPipelineBinaryUpdateStatement
    );

    PrepareStatement(db, "INSERT INTO renderPasses VALUES (?, ?, ?, ?, ?, NULL);", &renderPassInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO renderPassAttachments VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &renderPassAttachmentInsertStatement
    );
    PrepareStatement(db, "INSERT INTO renderSubpasses VALUES (?, ?, ?, ?);", &renderSubpassInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO renderSubpassAttachmentReferences VALUES (?, ?, ?, NULL, NULL, NULL, NULL, 0);",
        &renderSubpassBlankAttachmentReferencesInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO renderSubpassDependencies VALUES (?, ?, ?, ?, ?, ?, ?, ?);",
        &renderSubpassDependenciesInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassAttachmentReferences SET inputLayout = ?"
        " WHERE renderSubpassAttachmentReferences.renderPassId = ?"
        "  AND renderSubpassAttachmentReferences.subpassIndex = ?"
        "  AND renderSubpassAttachmentReferences.attachmentIndex = ?;",
        &renderSubpassSetAttachmentReferenceInputLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassAttachmentReferences SET colorLayout = ?"
        " WHERE renderSubpassAttachmentReferences.renderPassId = ?"
        "  AND renderSubpassAttachmentReferences.subpassIndex = ?"
        "  AND renderSubpassAttachmentReferences.attachmentIndex = ?;",
        &renderSubpassSetAttachmentReferenceColorLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassAttachmentReferences SET resolveLayout = ?"
        " WHERE renderSubpassAttachmentReferences.renderPassId = ?"
        "  AND renderSubpassAttachmentReferences.subpassIndex = ?"
        "  AND renderSubpassAttachmentReferences.attachmentIndex = ?;",
        &renderSubpassSetAttachmentReferenceResolveLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassAttachmentReferences SET depthStencilLayout = ?"
        " WHERE renderSubpassAttachmentReferences.renderPassId = ?"
        "  AND renderSubpassAttachmentReferences.subpassIndex = ?"
        "  AND renderSubpassAttachmentReferences.attachmentIndex = ?;",
        &renderSubpassSetAttachmentReferenceDepthStencilLayoutUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE renderSubpassAttachmentReferences SET preserveAttachment = True"
        " WHERE renderSubpassAttachmentReferences.renderPassId = ?"
        "  AND renderSubpassAttachmentReferences.subpassIndex = ?"
        "  AND renderSubpassAttachmentReferences.attachmentIndex = ?;",
        &renderSubpassSetAttachmentReferencePreserveUpdateStatement
    );

    PrepareStatement(db, "INSERT INTO queuePresents VALUES (?, ?, ?, ?);", &queuePresentInsertStatement);
    PrepareStatement(
        db, "INSERT INTO queuePresentSemaphoreWaits VALUES (?, ?, ?);", &queuePresentSemaphoreWaitInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO queuePresentSwapchains VALUES (?, ?, ?, ?);", &queuePresentSwapchainInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO debugReportCallbacks VALUES (?, ?, ?, ?, NULL);", &debugReportCallbackInsertStatement
    );
    PrepareStatement(db, "INSERT INTO debugMessengers VALUES (?, ?, ?, ?, ?, NULL);", &debugMessengerInsertStatement);
    PrepareStatement(db, "INSERT INTO debugNames VALUES (?, ?, ?, ?, ?, ?, ?);", &debugNameInsertStatement);
    PrepareStatement(db, "INSERT INTO debugTags VALUES (?, ?, ?, ?, ?, ?, ?, ?);", &debugTagInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO debugLabels VALUES (?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ?, ?, NULL);",
        &debugLabelQueueBeginInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO debugLabels VALUES (?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ?, ?, ?);",
        &debugLabelQueueInsertInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO debugLabels VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, NULL);",
        &debugLabelCmdBeginInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO debugLabels VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, ?);",
        &debugLabelCmdInsertInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO debugLabels VALUES (NULL, NULL, NULL, NULL, NULL, NULL, ?, NULL, NULL, NULL, ?, ?, ?, NULL, ?, "
        "NULL);",
        &debugLabelCmdEndStubInsertStatement
    );
    PrepareStatement(
        db, "UPDATE debugLabels SET endApiEventId = ? WHERE (debugLabels.id = ?);", &debugLabelQueueEndUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE debugLabels SET endApiEventId = ?, endRenderPassRecordingId = ?, endRenderSubpassRecordingId = ?, "
        "endDynamicRenderPassRecordingId = ? WHERE (debugLabels.id = ?);",
        &debugLabelCmdEndUpdateStatement
    );
    PrepareStatement(db, "INSERT INTO physicalDevices VALUES (?, ?, ?, ?);", &physicalDeviceInsertStatement);
    PrepareStatement(db, "INSERT INTO queues VALUES (?, ?, ?, ?, ?, ?, ?);", &queueInsertStatement);
    PrepareStatement(db, "INSERT INTO queueSubmits VALUES (?, ?, ?, ?, ?);", &queueSubmitInsertStatement);
    PrepareStatement(db, "INSERT INTO queueSubmitBatches VALUES (?, ?, ?, ?, ?);", &queueSubmitBatchInsertStatement);
    PrepareStatement(db, "INSERT INTO queueSubmitBuffers VALUES (?, ?, ?);", &queueSubmitBufferInsertStatement);
    PrepareStatement(
        db, "INSERT INTO queueSubmitSemaphoreWaits VALUES (?, ?, ?, ?, ?);", &queueSubmitSemaphoreWaitInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO queueSubmitSemaphoreSignals VALUES (?, ?, ?, ?);", &queueSubmitSemaphoreSignalInsertStatement
    );
    PrepareStatement(db, "INSERT INTO fences VALUES (?, ?, ?, ?, ?, NULL);", &fenceInsertStatement);
    PrepareStatement(db, "INSERT INTO fenceSyncScopes VALUES (?, ?, ?, NULL, NULL);", &fenceSyncScopeInsertStatement);
    PrepareStatement(
        db,
        "UPDATE fenceSyncScopes SET resetApiEventId = ? WHERE (fenceSyncScopes.id = ?);",
        &resetFenceSyncScopeUpdateStatement
    );
    PrepareStatement(
        db,
        "UPDATE fenceSyncScopes SET waitApiEventId = ? WHERE (fenceSyncScopes.id = ?);",
        &waitFenceSyncScopeUpdateStatement
    );
    PrepareStatement(db, "INSERT INTO semaphores VALUES (?, ?, ?, ?, ?, ?, ?, NULL);", &semaphoreInsertStatement);
    PrepareStatement(db, "INSERT INTO semaphoreSignals VALUES (?, ?, ?);", &semaphoreSignalInsertStatement);
    PrepareStatement(db, "INSERT INTO semaphoreWaits VALUES (?, ?, ?, ?, ?, ?);", &semaphoreWaitInsertStatement);
    PrepareStatement(db, "INSERT INTO events VALUES (?, ?, ?, ?, ?, NULL);", &eventInsertStatement);
    PrepareStatement(db, "INSERT INTO queryPools VALUES (?, ?, ?, ?, ?, ?, ?, ?, NULL);", &queryPoolInsertStatement);

    PrepareStatement(
        db, "INSERT INTO shaderObjects VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);", &shaderObjectInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO shaderObjectDescriptorSetLayouts VALUES (?, ?, ?);",
        &shaderObjectDescriptorSetLayoutInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO shaderObjectPushConstantRanges VALUES (?, ?, ?, ?, ?);",
        &shaderObjectPushConstantRangeInsertStatement
    );

    PrepareStatement(db, "INSERT INTO shaderModules VALUES (?, ?, ?, ?, ?, NULL);", &shaderModuleInsertStatement);
    PrepareStatement(
        db, "INSERT INTO shaderModules VALUES (?, ?, ?, ?, ?, NULL);", &shaderModuleWithStringHandleInsertStatement
    );
    PrepareStatement(db, "INSERT INTO pipelineStages VALUES (?, ?, ?, ?, ?, ?, ?, ?);", &pipelineStageInsertStatement);

    PrepareStatement(db, "INSERT INTO validationCaches VALUES (?, ?, ?, ?, ?, NULL);", &validationCacheInsertStatement);
    PrepareStatement(db, "INSERT INTO pipelineCaches VALUES (?, ?, ?, ?, ?, ?, NULL);", &pipelineCacheInsertStatement);
    PrepareStatement(db, "INSERT INTO pipelineLayouts VALUES (?, ?, ?, ?, ?, NULL);", &pipelineLayoutInsertStatement);
    PrepareStatement(
        db, "INSERT INTO pipelineDescriptorSetLayouts VALUES (?, ?, ?);", &pipelineDescriptorSetLayoutInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO pipelinePushConstantRanges VALUES (?, ?, ?, ?, ?);", &pipelinePushConstantRangeInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO descriptorSetLayouts VALUES (?, ?, ?, ?, ?, NULL);", &descriptorSetLayoutInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO descriptorSetLayoutBindings VALUES (?, ?, ?, ?, ?, ?);",
        &descriptorSetLayoutBindingInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO descriptorPools VALUES (?, ?, ?, ?, ?, ?, NULL);", &descriptorPoolInsertStatement
    );
    PrepareStatement(db, "INSERT INTO descriptorSets VALUES (?, ?, ?, ?, ?, NULL);", &descriptorSetInsertStatement);

    PrepareStatement(db, "INSERT INTO vertexInputStates VALUES (?, ?);", &vertexInputStateInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO vertexInputStateBindingDescriptions VALUES (?, ?, ?, ?, ?);",
        &vertexInputStateBindingDescriptionInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO vertexInputStateBindingDescriptions SELECT ?, binding, stride, inputRate, divisor"
        " FROM vertexInputStateBindingDescriptions WHERE vertexInputStateId = ?;",
        &vertexInputStateBindingDescriptionFromLibraryInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO vertexInputStateAttributeDescriptions VALUES (?, ?, ?, ?, ?);",
        &vertexInputStateAttributeDescriptionInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO vertexInputStateAttributeDescriptions SELECT ?, location, binding, format, offset"
        " FROM vertexInputStateAttributeDescriptions WHERE vertexInputStateId = ?;",
        &vertexInputStateAttributeDescriptionFromLibraryInsertStatement
    );
    PrepareStatement(db, "INSERT INTO inputAssemblyStates VALUES (?, ?, ?, ?);", &inputAssemblyStateInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO inputAssemblyStates SELECT ?, ?, topology, primitiveRestartEnable"
        " FROM inputAssemblyStates WHERE id = ?;",
        &inputAssemblyStateFromLibraryInsertStatement
    );
    PrepareStatement(db, "INSERT INTO tessellationStates VALUES (?, ?, ?);", &tessellationStateInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO tessellationStates SELECT ?, ?, patchControlPoints"
        " FROM tessellationStates WHERE id = ?;",
        &tessellationStateFromLibraryInsertStatement
    );
    PrepareStatement(db, "INSERT INTO viewportStates VALUES (?, ?, ?, ?, ?, ?);", &viewportStateInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO viewportStates"
        " SELECT ?, ?, depthClipNegativeToOne, depthClampMode, minDepthClamp, maxDepthClamp"
        " FROM viewportStates WHERE id = ?;",
        &viewportStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO viewportStateViewports VALUES (?, ?, ?, ?, ?, ?, ?, ?);", &viewportStateViewportInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO viewportStateViewports SELECT ?, idx, x, y, width, height, minDepth, maxDepth"
        " FROM viewportStateViewports WHERE viewportStateId = ?;",
        &viewportStateViewportFromLibraryInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO viewportStateScissors VALUES (?, ?, ?, ?, ?, ?);", &viewportStateScissorInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO viewportStateScissors SELECT ?, idx, x, y, width, height"
        " FROM viewportStateScissors WHERE viewportStateId = ?;",
        &viewportStateScissorFromLibraryInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO rasterizationStates VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &rasterizationStateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO rasterizationStates SELECT ?, ?, depthClampEnable, rasterizerDiscardEnable,"
        " polygonMode, cullMode, frontFace, depthBiasEnable, depthBiasConstantFactor,"
        " depthBiasClamp, depthBiasSlopeFactor, lineWidth, lineRasterizationMode, stippledLineEnabled,"
        " lineStippleFactor, lineStipplePattern, provokingVertexMode, rasterizationStream"
        " FROM rasterizationStates WHERE id = ?;",
        &rasterizationStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO depthStencilStates VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
        "?);",
        &depthStencilStateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO depthStencilStates SELECT ?, ?, flags, depthTestEnable, depthWriteEnable,"
        " depthCompareOp, depthBoundsTestEnable, stencilTestEnable,"
        " frontFailOp, frontPassOp, frontDepthFailOp, frontCompareOp, frontCompareMask, frontWriteMask, frontReference,"
        " backFailOp, backPassOp, backDepthFailOp, backCompareOp, backCompareMask, backWriteMask, backReference,"
        " minDepthBounds, maxDepthBounds"
        " FROM depthStencilStates WHERE id = ?;",
        &depthStencilStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO colorBlendStates VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);", &colorBlendStateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO colorBlendStates SELECT ?, ?, flags, logicOpEnable, logicOp,"
        " blendConstantsR, blendConstantsG, blendConstantsB, blendConstantsA"
        " FROM colorBlendStates WHERE id = ?;",
        &colorBlendStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO colorBlendStateAttachmentStates VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &colorBlendStateAttachmentStateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO colorBlendStateAttachmentStates SELECT ?, idx, blendEnable,"
        " srcColorBlendFactor, dstColorBlendFactor, colorBlendOp,"
        " srcAlphaBlendFactor, dstAlphaBlendFactor, alphaBlendOp, colorWriteMask, colorWriteEnable"
        " FROM colorBlendStateAttachmentStates WHERE colorBlendStateId = ?;",
        &colorBlendStateAttachmentStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db, "INSERT OR IGNORE INTO pipelineDynamicStates VALUES (?, ?);", &pipelineDynamicStateInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO multisampleStates VALUES (?, ?, ?, ?, ?, ?, ?);", &multisampleStateInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO multisampleStates SELECT ?, ?, rasterizationSamples, sampleShadingEnable, minSampleShading,"
        " alphaToCoverageEnable, alphaToOneEnable FROM multisampleStates WHERE id = ?;",
        &multisampleStateFromLibraryInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO multisampleStateSampleMasks VALUES (?, ?, ?);", &multisampleStateSampleMaskInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO multisampleStateSampleMasks SELECT ?, idx, sampleMask"
        " FROM multisampleStateSampleMasks WHERE multisampleStateId = ?;",
        &multisampleStateSampleMasksFromLibraryInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO pipelines VALUES (?, ?, 'Graphics', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &pipelineGraphicsInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO pipelines VALUES (?, ?, 'Compute', ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, ?, ?, NULL);",
        &pipelineComputeInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO pipelines VALUES (?, ?, 'Ray Tracing (NV)', ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, ?, ?, NULL);",
        &pipelineRayTracingNVInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO pipelines VALUES (?, ?, 'Ray Tracing', ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, ?, ?, NULL);",
        &pipelineRayTracingInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO pipelineColorAttachmentFormats VALUES (?, ?, ?);",
        &pipelineColorAttachmentFormatInsertStatement
    );
    PrepareStatement(db, "INSERT INTO pipelineLibraries VALUES (?, ?);", &pipelineLibraryInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO graphicsPipelineInfos VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
        &graphicsPipelineInfoInsertStatement
    );
    PrepareStatement(db, "INSERT INTO computePipelineInfos VALUES (?, ?);", &computePipelineInfoInsertStatement);
    PrepareStatement(
        db, "INSERT INTO raytracingPipelineInfos VALUES (?, ?, ?, ?, ?);", &raytracingPipelineInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO raytracingShaderGroups VALUES (?, ?, ?, ?, ?, ?, ?);", &raytracingShaderGroupInsertStatement
    );

    PrepareStatement(
        db,
        "INSERT INTO pipelines VALUES (?, ?, 'Data Graph', ?, ?, ?, ?, NULL, NULL, NULL, NULL, ?, ?, ?, NULL);",
        &pipelineDataGraphInsertStatement
    );
    PrepareStatement(db, "INSERT INTO dataGraphPipelineInfos VALUES (?, ?);", &dataGraphPipelineInfoInsertStatement);
    PrepareStatement(
        db,
        "INSERT INTO dataGraphPipelineResourceInfos VALUES (?, ?, ?, ?, ?);",
        &dataGraphPipelineResourceInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO dataGraphPipelineSessions VALUES (?, ?, ?, ?, ?, ?, NULL);",
        &dataGraphPipelineSessionInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE dataGraphPipelineSessions SET destroyApiEventId = ? WHERE (dataGraphPipelineSessions.id = ?);",
        &destroyDataGraphPipelineSessionUpdateStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO cmdDataGraphDispatchRecordings VALUES (?, ?, ?, ?, ?);",
        &cmdDataGraphDispatchRecordingInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO cmdDataGraphDispatchRecordingInfos VALUES (?, ?);",
        &cmdDataGraphDispatchRecordingInfoInsertStatement
    );

    PrepareStatement(db, "INSERT INTO displays VALUES (?, ?, ?, ?);", &displayInsertStatement);
    PrepareStatement(db, "INSERT INTO displayModes VALUES (?, ?, ?, ?, ?, ?, ?, ?);", &displayModeInsertStatement);
    PrepareStatement(db, "INSERT INTO acquireNextImages VALUES (?, ?, ?, ?, ?, ?);", &acquireNextImageInsertStatement);

    PrepareStatement(
        db, "INSERT INTO framebuffers VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);", &framebufferInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO framebufferAttachmentInfos VALUES (?, ?, ?, ?, ?, ?);",
        &framebufferAttachmentInfoInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO framebufferAttachments VALUES (?, ?, NULL, ?);", &framebufferAttachmentWithInfoInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO framebufferAttachments VALUES (?, ?, ?, NULL);",
        &framebufferAttachmentWithImageViewInsertStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO samplerYcbcrConversions VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL);",
        &samplerYcbcrConversionInsertStatement
    );
    PrepareStatement(db, "INSERT INTO privateDataSlots VALUES (?, ?, ?, ?, NULL);", &privateDataSlotInsertStatement);
    PrepareStatement(
        db, "INSERT INTO deferredOperations VALUES (?, ?, ?, ?, NULL);", &deferredOperationInsertStatement
    );
    PrepareStatement(
        db, "INSERT INTO pipelineBinaries VALUES (?, ?, ?, ?, ?, ?, ?, NULL);", &pipelineBinaryInsertStatement
    );

    PrepareStatement(
        db, "INSERT INTO videoSessions VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,NULL);", &videoSessionInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE videoSessions SET destroyApiEventId = ? WHERE (videoSessions.id = ?);",
        &destroyVideoSessionUpdateStatement
    );
    PrepareStatement(
        db, "INSERT INTO videoSessionParameters VALUES (?,?,?,?,?,?,?,NULL);", &videoSessionParametersInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE videoSessionParameters SET destroyApiEventId = ?"
        " WHERE (videoSessionParameters.id = ?);",
        &destroyVideoSessionParametersUpdateStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO indirectCommandsLayouts VALUES (?,?,?,?,?,?,?,?,?,NULL);",
        &indirectCommandsLayoutInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE indirectCommandsLayouts SET destroyApiEventId = ?"
        " WHERE (indirectCommandsLayouts.id = ?);",
        &destroyIndirectCommandsLayoutUpdateStatement
    );
    PrepareStatement(db, "INSERT INTO micromaps VALUES (?,?,?,?,?,?,?,?,?,?,NULL);", &micromapInsertStatement);
    PrepareStatement(
        db, "UPDATE micromaps SET destroyApiEventId = ? WHERE (micromaps.id = ?);", &destroyMicromapUpdateStatement
    );
    PrepareStatement(
        db,
        "INSERT INTO opticalFlowSessions VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,NULL);",
        &opticalFlowSessionInsertStatement
    );
    PrepareStatement(
        db,
        "UPDATE opticalFlowSessions SET destroyApiEventId = ?"
        " WHERE (opticalFlowSessions.id = ?);",
        &destroyOpticalFlowSessionUpdateStatement
    );
}

// Template implementations are now in the header file

// Helper function implementations originally from VulkanSqliteConsumerBase

void VulkanSqlitePreparedStatements::InsertFrame(const uint64_t frameIndex, const uint64_t beginApiEventId)
{
    auto& statement = frameInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(frameIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(beginApiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    sqlite3_clear_bindings(statement);
}

int64_t VulkanSqlitePreparedStatements::InsertFunctionName(const std::string_view functionName)
{
    std::string functionNameStr = std::string(functionName);
    auto functionIdIter = context->customFunctionNamesToFunctionNameId.find(functionNameStr);
    if (functionIdIter == context->customFunctionNamesToFunctionNameId.end())
    {
        auto functionId = ++context->currentFunctionNameId;
        context->customFunctionNamesToFunctionNameId[functionNameStr] = functionId;
        auto& statement = functionNameInsertStatement;
        GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(functionId)));
        GFXRECON_SQLITE_CHECK(
            db, sqlite3_bind_text64(statement, 2, functionName.data(), functionName.size(), SQLITE_STATIC, SQLITE_UTF8)
        );
        GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

        return functionId;
    }
    return functionIdIter->second;
}

void VulkanSqlitePreparedStatements::InsertApiEvent(
    const uint64_t apiEventId, const int64_t functionNameId, const format::ThreadId threadId
)
{
    auto& statement = apiEventVkInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(context->currentFrame)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(functionNameId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(threadId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    sqlite3_clear_bindings(statement);
}

void VulkanSqlitePreparedStatements::InsertMetaApiEvent(
    const uint64_t apiEventId, const int64_t functionNameId, const uint64_t frame_number
)
{
    auto& statement = apiEventMetaInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(frame_number)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(functionNameId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    sqlite3_clear_bindings(statement);
}

int64_t VulkanSqlitePreparedStatements::InsertInstance(
    const uint64_t apiEventId,
    const int64_t instance,
    const VkInstanceCreateFlags flags,
    const std::string_view applicationName,
    const uint32_t applicationVersion,
    const std::string_view engineName,
    const uint32_t engineVersion,
    const uint32_t apiVersion
)
{
    auto id = ++context->currentInstanceId;
    context->instanceHandleToId[instance] = id;
    auto& statement = instanceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(id)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instance)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(
        db,
        sqlite3_bind_text64(statement, 4, applicationName.data(), applicationName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(applicationVersion)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 6, engineName.data(), engineName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(engineVersion)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiVersion)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return id;
}

int64_t VulkanSqlitePreparedStatements::InsertInstanceEnabledLayer(
    const int64_t instanceId, const std::string_view layerName
)
{
    auto id = ++context->currentInstanceEnabledLayerId;
    auto& statement = instanceEnabledLayerInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(id)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, layerName.data(), layerName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return id;
}

int64_t VulkanSqlitePreparedStatements::InsertInstanceEnabledLayerSetting(
    const int64_t instanceEnabledLayerId, const std::string_view name, const int64_t type
)
{
    auto id = ++context->currentInstanceEnabledLayerSettingId;
    auto& statement = instanceEnabledLayerSettingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(id)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instanceEnabledLayerId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 3, name.data(), name.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(type)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return id;
}

void VulkanSqlitePreparedStatements::InsertInstanceEnabledLayerSettingValue(
    const int64_t instanceEnabledLayerSettingId, const int64_t idx, const std::string_view value
)
{
    auto& statement = instanceEnabledLayerSettingValueInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instanceEnabledLayerSettingId))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(idx)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, value.data(), value.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertInstanceEnabledExtension(
    const int64_t instanceId, const std::string_view extensionName
)
{
    auto& statement = instanceEnabledExtensionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, extensionName.data(), extensionName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertInstanceValidationEnabledFeature(
    const int64_t instanceId, const int64_t feature
)
{
    auto& statement = instanceValidationEnabledFeatureInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(feature)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertInstanceValidationDisabledFeature(
    const int64_t instanceId, const int64_t feature
)
{
    auto& statement = instanceValidationDisabledFeatureInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(feature)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertInstanceValidationDisabledCheck(
    const int64_t instanceId, const int64_t check
)
{
    auto& statement = instanceValidationDisabledCheckInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(check)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDevice(
    const uint64_t apiEventId,
    const format::HandleId device,
    std::optional<int64_t> physical_device,
    const int64_t overallocationBehavior
)
{
    auto deviceHandle = ToInt64(device);
    auto deviceId = ++context->currentDeviceId;
    context->deviceHandleToId[deviceHandle] = deviceId;
    auto& statement = deviceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(deviceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(deviceHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, physical_device));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(overallocationBehavior)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return deviceId;
}

void VulkanSqlitePreparedStatements::InsertDeviceEnabledLayer(const int64_t deviceId, const std::string_view layerName)
{
    auto& statement = deviceEnabledLayerInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(deviceId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, layerName.data(), layerName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDeviceEnabledExtension(
    const int64_t deviceId, const std::string_view extensionName
)
{
    auto& statement = deviceEnabledExtensionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(deviceId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, extensionName.data(), extensionName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDeviceEnabledFeature(
    const int64_t deviceId, const std::string_view featureName
)
{
    context->deviceIdToEnabledFeatures[deviceId].insert(featureName.data());
    auto& statement = deviceEnabledFeatureInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(deviceId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, featureName.data(), featureName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertTrackedDeviceCommand(const int64_t deviceId, const uint64_t apiEventId)
{
    auto commandId = ++context->currentTrackedDeviceCommandId;
    auto& statement = trackedDeviceCommandInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(deviceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(context->currentFrame)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertRenderTrackedCmdCommand(
    const uint64_t apiEventId,
    sqlite3_stmt* statement,
    const int64_t instance,
    const int64_t stateGroupId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId,
    const bool indexed
)
{
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(instance)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, renderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, renderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, dynamicRenderPassRecordingId));
    if (statement == cmdDrawRecordingInsertStatement)
    {
        GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, indexed));
    }
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertTrackedCmdCommand(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId
)
{
    auto trackedCmdCommandId = ++context->currentTrackedCmdCommandId;
    auto& statement = trackedCmdCommandInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(trackedCmdCommandId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, renderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, renderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, dynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return trackedCmdCommandId;
}

int64_t VulkanSqlitePreparedStatements::InsertCommandPool(
    const uint64_t apiEventId,
    const format::HandleId commandPool,
    const format::HandleId device,
    const VkCommandPoolCreateFlags flags,
    const uint32_t queueFamilyIndex
)
{
    auto commandPoolId = ++context->currentCommandPoolId;
    auto deviceId = context->GetDeviceId(device);
    auto commandPoolHandle = ToInt64(commandPool);
    context->commandPoolHandleToId[commandPoolHandle] = commandPoolId;
    auto& statement = commandPoolInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandPoolId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(commandPoolHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(queueFamilyIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return commandPoolId;
}

int64_t VulkanSqlitePreparedStatements::InsertCommandBuffer(
    const uint64_t apiEventId,
    const format::HandleId commandBuffer,
    const format::HandleId device,
    const format::HandleId commandPool,
    const VkCommandBufferLevel level
)
{
    auto commandBufferId = ++context->currentCommandBufferId;
    auto deviceId = context->GetDeviceId(device);
    auto commandPoolId = context->GetCommandPoolId(commandPool);
    auto commandBufferHandle = ToInt64(commandBuffer);
    context->commandBufferHandleToId[commandBufferHandle] = commandBufferId;
    context->commandBufferHandleToLevel[commandBufferHandle] = level;
    if (deviceId.has_value())
    {
        context->commandBufferHandleToDeviceId[commandBufferHandle] = deviceId.value();
    }
    context->commandBufferHandleToDevice[commandBufferHandle] = device;
    context->commandPoolHandleToCommandBufferHandles[ToInt64(commandPool)].push_back(commandBufferHandle);
    auto& statement = commandBufferInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandBufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(commandBufferHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, commandPoolId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(level)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return commandBufferId;
}

int64_t VulkanSqlitePreparedStatements::InsertCommandBufferRecording(
    const uint64_t apiEventId,
    const int64_t commandBuffer,
    const VkCommandBufferUsageFlags flags,
    const std::optional<int64_t> inheritanceInfo
)
{
    auto commandBufferRecordingId = ++context->currentCommandBufferRecordingId;
    auto& statement = commandBufferRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(commandBuffer)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, inheritanceInfo));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return commandBufferRecordingId;
}

void VulkanSqlitePreparedStatements::EndCommandBufferRecording(
    uint64_t apiEventId, const int64_t commandBufferRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto& statement = commandBufferRecordingEndStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(stateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::ResetCommandBufferRecording(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId
)
{
    auto& statement = commandBufferRecordingResetStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertRenderPassRecording(
    const uint64_t apiEventId,
    const std::optional<int64_t> renderPass,
    const uint64_t passIndex,
    const std::optional<int64_t> commandBufferRecordingId,
    const std::optional<int64_t> framebuffer,
    const int32_t renderOffsetX,
    const int32_t renderOffsetY,
    const int32_t renderWidth,
    const int32_t renderHeight
)
{
    auto renderPassRecordingId = ++context->currentRenderPassRecordingId;
    auto& statement = renderPassRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(passIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, renderPass));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, framebuffer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(renderOffsetX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(renderOffsetY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(renderWidth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(renderHeight)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return renderPassRecordingId;
}

void VulkanSqlitePreparedStatements::EndRenderPassRecording(uint64_t apiEventId, const int64_t renderPassRecordingId)
{
    auto& statement = renderPassRecordingEndStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(renderPassRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertRenderPassRecordingClearValues(
    const int64_t renderPassRecordingId,
    const uint64_t attachmentIndex,
    const int64_t clearColorId,
    const float clearDepth,
    const uint32_t clearStencil
)
{
    auto& statement = renderPassRecordingClearValueInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(clearColorId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, clearDepth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(clearStencil)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertRenderSubpassRecording(
    const uint64_t apiEventId, const int64_t renderPassRecordingId, const uint32_t contents
)
{
    auto renderSubpassRecordingId = ++context->currentRenderSubpassRecordingId;
    auto& subpassIndexRef = context->renderPassRecordingIdToSubpassIndex[renderPassRecordingId];
    auto subpassIndex = context->renderPassRecordingIdToRenderSubpassRecordingId.contains(renderPassRecordingId)
        ? ++subpassIndexRef
        : subpassIndexRef;
    auto& statement = renderSubpassRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderSubpassRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(renderPassRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(contents)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    context->renderPassRecordingIdToRenderSubpassRecordingId[renderPassRecordingId] = renderSubpassRecordingId;
}

void VulkanSqlitePreparedStatements::EndRenderSubpassRecording(
    uint64_t apiEventId, const int64_t renderSubpassRecordingId
)
{
    auto& statement = renderSubpassRecordingEndStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(renderSubpassRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDynamicRenderPassRecording(
    const uint64_t apiEventId,
    const uint64_t passIndex,
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
)
{
    auto dynamicRenderPassRecordingId = ++context->currentDynamicRenderPassRecordingId;
    auto& statement = dynamicRenderPassRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(dynamicRenderPassRecordingId))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(passIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(renderOffsetX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(renderOffsetY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(renderWidth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(renderHeight)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(layerCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(viewMask)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 11, depthAttachment));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 12, stencilAttachment));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return dynamicRenderPassRecordingId;
}

void VulkanSqlitePreparedStatements::EndDynamicRenderPassRecording(
    const uint64_t apiEventId, const int64_t dynamicRenderPassRecordingId
)
{
    auto& statement = dynamicRenderPassRecordingEndStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(dynamicRenderPassRecordingId))
    );
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertUnionColor(const VkClearColorValue& color)
{
    auto clearColorIter = context->unionColorValueToId.find(color);
    if (clearColorIter != context->unionColorValueToId.end())
    {
        return clearColorIter->second;
    }
    auto clearColorId = ++context->currentUnionColorId;
    context->unionColorValueToId[color] = clearColorId;
    auto& statement = unionColorInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(clearColorId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 2, color.float32[0]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, color.float32[1]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, color.float32[2]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, color.float32[3]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(color.int32[0])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(color.int32[1])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(color.int32[2])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(color.int32[3])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(color.uint32[0])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(color.uint32[1])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(color.uint32[2])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(color.uint32[3])));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return clearColorId;
}

int64_t VulkanSqlitePreparedStatements::InsertRenderingAttachment(
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
)
{
    auto renderingAttachmentId = ++context->currentRenderingAttachmentId;
    auto& statement = renderingAttachmentInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderingAttachmentId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, imageView));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(imageLayout)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(resolveMode)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, resolveImageViewId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(resolveImageLayout)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(loadOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(storeOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(clearColorId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 10, clearDepth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(clearStencil)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return renderingAttachmentId;
}

void VulkanSqlitePreparedStatements::InsertDynamicColorAttachment(
    const int64_t dynamicRenderPassRecordingId, const uint64_t attachmentIndex, const int64_t renderingAttachmentId
)
{
    auto& statement = dynamicColorAttachmentInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(dynamicRenderPassRecordingId))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(renderingAttachmentId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertOverrideStateGroup(
    const int64_t parentCommandBufferRecordingId, const int64_t secondaryCommandBufferRecordingId
)
{
    // get the end state of the previously recorded secondary command buffer
    auto secondaryCommandBufferEndDynamicStateIter =
        context->commandBufferRecordingPreviousStateEntries.find(secondaryCommandBufferRecordingId);
    if (secondaryCommandBufferEndDynamicStateIter != context->commandBufferRecordingPreviousStateEntries.end())
    {
        if (!secondaryCommandBufferEndDynamicStateIter->second.empty())
        {
            context->commandBufferRecordingWithDirtyState.insert(parentCommandBufferRecordingId);
            for (const auto& entry : secondaryCommandBufferEndDynamicStateIter->second)
            {
                switch (entry.stateTypeId)
                {
                    case StateType::PIPELINE_BINDING:
                        context->commandBufferRecordingPipelineBindings[parentCommandBufferRecordingId]
                                                                       [static_cast<VkPipelineBindPoint>(entry.idx)] =
                            entry.stateId;
                        break;
                    case StateType::SHADER_OBJECT_BINDING:
                        context->commandBufferRecordingShaderObjectBindings
                            [parentCommandBufferRecordingId][static_cast<VkShaderStageFlagBits>(entry.idx)] =
                            entry.stateId;
                        break;
                    case StateType::DESCRIPTOR_SET_BINDING:
                        context
                            ->commandBufferRecordingDescriptorSetBindings[parentCommandBufferRecordingId]
                                                                         [static_cast<VkPipelineBindPoint>(entry.idx)]
                                                                         [entry.subIndex] = entry.stateId;
                        break;
                    case StateType::DESCRIPTOR_SET_PUSH:
                        context->commandBufferRecordingDescriptorSetPushes[parentCommandBufferRecordingId][entry.idx]
                                                                          [entry.subIndex] = entry.stateId;
                        break;
                    case StateType::INDEX_BUFFER_BINDING:
                        context->commandBufferRecordingIndexBindings[parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::VERTEX_BUFFER_BINDING:
                        context->commandBufferRecordingVertexBindings[parentCommandBufferRecordingId][entry.idx] =
                            entry.stateId;
                        break;
                    case StateType::VERTEX_INPUT_BINDING_DESCRIPTION:
                        context->commandBufferRecordingVertexInputBindingDescriptions[parentCommandBufferRecordingId]
                                                                                     [entry.idx] = entry.stateId;
                        break;
                    case StateType::VERTEX_INPUT_ATTRIBUTE_DESCRIPTION:
                        context->commandBufferRecordingVertexInputAttributeDescriptions[parentCommandBufferRecordingId]
                                                                                       [entry.idx] = entry.stateId;
                        break;
                    case StateType::VIEWPORT:
                        context->commandBufferRecordingDynamicViewports[parentCommandBufferRecordingId][entry.idx] =
                            entry.stateId;
                        break;
                    case StateType::SCISSOR:
                        context->commandBufferRecordingDynamicScissors[parentCommandBufferRecordingId][entry.idx] =
                            entry.stateId;
                        break;
                    case StateType::LINE_WIDTH:
                        context->commandBufferRecordingDynamicLineWidths[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::RENDERING_COLOR_ATTACHMENT_LOCATION:
                        context->commandBufferRecordingDynamicRenderingColorAttachmentLocations
                            [parentCommandBufferRecordingId][entry.idx] = entry.stateId;
                        break;
                    case StateType::RENDERING_INPUT_COLOR_ATTACHMENT_INDEX:
                        context->commandBufferRecordingDynamicRenderingInputColorAttachmentIndices
                            [parentCommandBufferRecordingId][entry.idx] = entry.stateId;
                        break;
                    case StateType::RENDERING_INPUT_DEPTH_ATTACHMENT_INDEX:
                        context->commandBufferRecordingDynamicRenderingInputDepthAttachmentIndices
                            [parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::RENDERING_INPUT_STENCIL_ATTACHMENT_INDEX:
                        context->commandBufferRecordingDynamicRenderingInputStencilAttachmentIndices
                            [parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::DEPTH_BOUNDS:
                        context->commandBufferRecordingDynamicDepthBounds[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::DEPTH_BOUNDS_TEST_ENABLE:
                        context->commandBufferRecordingDynamicDepthBoundsTestEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::DEPTH_BIAS:
                        context->commandBufferRecordingDynamicDepthBias[parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::DEPTH_BIAS_ENABLE:
                        context->commandBufferRecordingDynamicDepthBiasEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::DEPTH_TEST_ENABLE:
                        context->commandBufferRecordingDynamicDepthTestEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::DEPTH_WRITE_ENABLE:
                        context->commandBufferRecordingDynamicDepthWriteEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::DEPTH_COMPARE_OPS:
                        context->commandBufferRecordingDynamicDepthCompareOps[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_COMPARE_MASK_FRONT:
                        context->commandBufferRecordingDynamicStencilCompareMaskFront[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_COMPARE_MASK_BACK:
                        context->commandBufferRecordingDynamicStencilCompareMaskBack[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_WRITE_MASK_FRONT:
                        context->commandBufferRecordingDynamicStencilWriteMaskFront[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_WRITE_MASK_BACK:
                        context->commandBufferRecordingDynamicStencilWriteMaskBack[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_REFERENCE_FRONT:
                        context->commandBufferRecordingDynamicStencilReferenceFront[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_REFERENCE_BACK:
                        context->commandBufferRecordingDynamicStencilReferenceBack[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_TEST_ENABLE:
                        context->commandBufferRecordingDynamicStencilTestEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_OPS_FRONT:
                        context->commandBufferRecordingDynamicStencilOpsFront[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::STENCIL_OPS_BACK:
                        context->commandBufferRecordingDynamicStencilOpsBack[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::COLOR_WRITE_ENABLE:
                        context
                            ->commandBufferRecordingDynamicColorWriteEnable[parentCommandBufferRecordingId][entry.idx] =
                            entry.stateId;
                        break;
                    case StateType::BLEND_CONSTANTS:
                        context->commandBufferRecordingDynamicBlendConstants[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::PRIMITIVE_TOPOLOGY:
                        context->commandBufferRecordingDynamicPrimitiveTopologies[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::CULL_MODE:
                        context->commandBufferRecordingDynamicCullModes[parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::FRONT_FACE:
                        context->commandBufferRecordingDynamicFrontFaces[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::LOGIC_OP:
                        context->commandBufferRecordingDynamicLogicOps[parentCommandBufferRecordingId] = entry.stateId;
                        break;
                    case StateType::RASTERIZER_DISCARD_ENABLE:
                        context->commandBufferRecordingDynamicRasterizerDiscardEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::PATCH_CONTROL_POINTS:
                        context->commandBufferRecordingDynamicPatchControlPoints[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    case StateType::PRIMITIVE_RESTART_ENABLE:
                        context->commandBufferRecordingDynamicPrimitiveRestartEnable[parentCommandBufferRecordingId] =
                            entry.stateId;
                        break;
                    default:
                        GFXRECON_SQLITE_LOG_WARNING("Failed to properly override state instance, invalid stateType");
                }
            }
        }
    }

    return InsertStateGroup(parentCommandBufferRecordingId);
}

int64_t VulkanSqlitePreparedStatements::InsertSecondaryCommandBufferExecutionRecording(
    const uint64_t apiEventId,
    const int64_t parentCommandBufferRecordingId,
    const int64_t secondaryCommandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId,
    const int64_t index
)
{
    auto beginStateGroupId = InsertStateGroup(parentCommandBufferRecordingId);
    auto endStateGroupId = InsertOverrideStateGroup(parentCommandBufferRecordingId, secondaryCommandBufferRecordingId);

    auto secondaryCommandBufferExecutionRecording = ++context->currentSecondaryCommandBufferExecutionRecordingId;
    auto& statement = secondaryCommandBufferExecutionRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(secondaryCommandBufferExecutionRecording))
    );
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(parentCommandBufferRecordingId))
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, renderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, renderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, dynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(secondaryCommandBufferRecordingId))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(index)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(beginStateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(endStateGroupId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return secondaryCommandBufferExecutionRecording;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdDrawRecording(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId,
    const bool indexed
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto cmdDrawRecordingId = ++context->currentCmdDrawRecordingId;
    InsertRenderTrackedCmdCommand(
        apiEventId,
        cmdDrawRecordingInsertStatement,
        cmdDrawRecordingId,
        stateGroupId,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        indexed
    );
    return cmdDrawRecordingId;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdMeshTaskRecording(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto cmdMeshTaskRecordingId = ++context->currentCmdMeshTaskRecordingId;
    InsertRenderTrackedCmdCommand(
        apiEventId,
        cmdMeshTaskRecordingInsertStatement,
        cmdMeshTaskRecordingId,
        stateGroupId,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        false
    );
    return cmdMeshTaskRecordingId;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdClusterRecording(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto cmdClusterRecordingId = ++context->currentCmdClusterRecordingId;
    InsertRenderTrackedCmdCommand(
        apiEventId,
        cmdClusterRecordingInsertStatement,
        cmdClusterRecordingId,
        stateGroupId,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        false
    );
    return cmdClusterRecordingId;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdDispatchRecording(
    uint64_t apiEventId, const int64_t commandBufferRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto cmdDispatchRecordingId = ++context->currentCmdDispatchRecordingId;
    // We can't use InsertRenderTrackedCmdCommand here as dispatches don't have a render pass, and it's illegal to bind
    // to an out of bounds parameter index (even when binding null).
    auto& statement = cmdDispatchRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDispatchRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return cmdDispatchRecordingId;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdRaytracingRecording(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto cmdRaytracingRecordingId = ++context->currentCmdRaytracingRecordingId;
    // We can't use InsertRenderTrackedCmdCommand here as tracerays don't have a render pass, and it's illegal to bind
    // to an out of bounds parameter index (even when binding null).
    auto& statement = cmdRaytracingRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdRaytracingRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return cmdRaytracingRecordingId;
}

void VulkanSqlitePreparedStatements::InsertCmdDrawRecordingIndirectInfo(
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
)
{
    auto& statement = cmdDrawRecordingIndirectInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDrawRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, indirectBuffer));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, static_cast<std::optional<int64_t>>(indirectBufferOffset)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, indirectCountBuffer));
    GFXRECON_SQLITE_CHECK(
        db, BindOptInt64(statement, 5, static_cast<std::optional<int64_t>>(indirectCountBufferOffset))
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, indirectCountOffset));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, indirectDrawCount));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, indirectMaxDrawCount));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, indirectStride));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 10, indirectVertexStride));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdDrawRecordingInfo(
    const int64_t cmdDrawRecordingId,
    const std::optional<uint32_t> vertexCount,
    const std::optional<uint32_t> firstVertex,
    const std::optional<int32_t> vertexOffset,
    const std::optional<uint32_t> indexCount,
    const std::optional<uint32_t> firstIndex,
    const uint32_t instanceCount,
    const uint32_t firstInstance
)
{
    auto& statement = cmdDrawRecordingInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDrawRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, vertexCount));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, firstVertex));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, vertexOffset));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, indexCount));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, firstIndex));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(instanceCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(firstInstance)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdMeshTaskRecordingIndirectInfo(
    const int64_t cmdMeshTaskRecordingId,
    const std::optional<int64_t> indirectBuffer,
    const uint64_t indirectBufferOffset,
    const std::optional<int64_t> indirectCountBuffer,
    const std::optional<uint64_t> indirectCountBufferOffset,
    const std::optional<uint32_t> indirectDrawCount,
    const std::optional<uint32_t> indirectMaxDrawCount,
    const uint32_t indirectStride
)
{
    auto& statement = cmdMeshTaskRecordingIndirectInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdMeshTaskRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, indirectBuffer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(indirectBufferOffset)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, indirectCountBuffer));
    GFXRECON_SQLITE_CHECK(
        db, BindOptInt64(statement, 5, static_cast<std::optional<int64_t>>(indirectCountBufferOffset))
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, indirectDrawCount));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, indirectMaxDrawCount));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(indirectStride)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdMeshTaskRecordingInfo(
    const int64_t cmdMeshTaskRecordingId,
    const uint32_t groupCountX,
    const uint32_t groupCountY,
    const uint32_t groupCountZ
)
{
    auto& statement = cmdMeshTaskRecordingInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdMeshTaskRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(groupCountX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(groupCountY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(groupCountZ)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdClusterRecordingIndirectInfo(
    const int64_t cmdClusterRecordingId,
    const std::optional<int64_t> indirectBuffer,
    const uint64_t indirectBufferOffset
)
{
    auto& statement = cmdClusterRecordingIndirectInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdClusterRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, indirectBuffer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(indirectBufferOffset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdClusterRecordingInfo(
    const int64_t cmdClusterRecordingId,
    const uint32_t groupCountX,
    const uint32_t groupCountY,
    const uint32_t groupCountZ
)
{
    auto& statement = cmdClusterRecordingInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdClusterRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(groupCountX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(groupCountY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(groupCountZ)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdDispatchRecordingIndirectInfo(
    const int64_t cmdDispatchRecordingId,
    const std::optional<int64_t> indirectBuffer,
    const uint64_t indirectBufferOffset
)
{
    auto& statement = cmdDispatchRecordingIndirectInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDispatchRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, indirectBuffer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(indirectBufferOffset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdDispatchRecordingBaseInfo(
    const int64_t cmdDispatchRecordingId,
    const uint32_t baseGroupX,
    const uint32_t baseGroupY,
    const uint32_t baseGroupZ
)
{
    auto& statement = cmdDispatchRecordingBaseInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDispatchRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(baseGroupX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(baseGroupY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(baseGroupZ)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCmdDispatchRecordingInfo(
    const int64_t cmdDispatchRecordingId,
    const uint32_t groupCountX,
    const uint32_t groupCountY,
    const uint32_t groupCountZ
)
{
    auto& statement = cmdDispatchRecordingInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDispatchRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(groupCountX)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(groupCountY)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(groupCountZ)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertStateId(const uint64_t apiEventId)
{
    auto stateId = ++context->currentStateId;
    auto& statement = stateIdInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateGroup(const int64_t commandBufferRecordingId)
{
    auto stateDirty = context->commandBufferRecordingWithDirtyState.erase(commandBufferRecordingId);
    if (!stateDirty)
    {
        auto prevStateIter = context->commandBufferRecordingPreviousState.find(commandBufferRecordingId);
        if (prevStateIter != context->commandBufferRecordingPreviousState.end())
        {
            // reuse the state instance since the state hasn't changed
            return prevStateIter->second;
        }
    }

    auto stateGroupId = ++context->currentStateGroupId;
    context->commandBufferRecordingPreviousState[commandBufferRecordingId] = stateGroupId;

    InsertStateGroupEntries(stateGroupId, commandBufferRecordingId);
    return stateGroupId;
}

void VulkanSqlitePreparedStatements::InsertStateGroupEntries(
    const int64_t stateGroupId, const int64_t commandBufferRecordingId
)
{
    std::vector<VulkanSqliteConsumerContext::StateGroupEntry> entries;

    // pipeline bindings
    if (auto pipelineBindingsIter = context->commandBufferRecordingPipelineBindings.find(commandBufferRecordingId);
        pipelineBindingsIter != context->commandBufferRecordingPipelineBindings.end())
    {
        for (const auto& [bindPoint, stateId] : pipelineBindingsIter->second)
        {
            entries.emplace_back(stateId, StateType::PIPELINE_BINDING, bindPoint);
        }
    }

    // shader object bindings
    if (auto shaderObjectBindingsIter =
            context->commandBufferRecordingShaderObjectBindings.find(commandBufferRecordingId);
        shaderObjectBindingsIter != context->commandBufferRecordingShaderObjectBindings.end())
    {
        for (const auto& [stage, stateId] : shaderObjectBindingsIter->second)
        {
            entries.emplace_back(stateId, StateType::SHADER_OBJECT_BINDING, stage);
        }
    }

    // descriptor set bindings
    if (auto descriptorSetBindingsIter =
            context->commandBufferRecordingDescriptorSetBindings.find(commandBufferRecordingId);
        descriptorSetBindingsIter != context->commandBufferRecordingDescriptorSetBindings.end())
    {
        for (const auto& [bindPoint, setIndexes] : descriptorSetBindingsIter->second)
        {
            for (const auto& [setIndex, stateId] : setIndexes)
            {
                entries.emplace_back(stateId, StateType::DESCRIPTOR_SET_BINDING, bindPoint, setIndex);
            }
        }
    }

    // descriptor set pushes
    if (auto descriptorSetPushesIter =
            context->commandBufferRecordingDescriptorSetPushes.find(commandBufferRecordingId);
        descriptorSetPushesIter != context->commandBufferRecordingDescriptorSetPushes.end())
    {
        for (const auto& [binding, arrayElements] : descriptorSetPushesIter->second)
        {
            for (const auto& [arrayElement, stateId] : arrayElements)
            {
                entries.emplace_back(stateId, StateType::DESCRIPTOR_SET_PUSH, binding, arrayElement);
            }
        }
    }

    // index buffer bindings
    if (auto indexBufferBindingsIter = context->commandBufferRecordingIndexBindings.find(commandBufferRecordingId);
        indexBufferBindingsIter != context->commandBufferRecordingIndexBindings.end())
    {
        entries.emplace_back(indexBufferBindingsIter->second, StateType::INDEX_BUFFER_BINDING);
    }

    // vertex buffer bindings
    if (auto vertexBufferBindingsIter = context->commandBufferRecordingVertexBindings.find(commandBufferRecordingId);
        vertexBufferBindingsIter != context->commandBufferRecordingVertexBindings.end())
    {
        for (const auto& [binding, stateId] : vertexBufferBindingsIter->second)
        {
            entries.emplace_back(stateId, StateType::VERTEX_BUFFER_BINDING, binding);
        }
    }

    // vertex input binding descriptions
    if (auto vertexInputBindingIter =
            context->commandBufferRecordingVertexInputBindingDescriptions.find(commandBufferRecordingId);
        vertexInputBindingIter != context->commandBufferRecordingVertexInputBindingDescriptions.end())
    {
        for (const auto& [binding, stateId] : vertexInputBindingIter->second)
        {
            entries.emplace_back(stateId, StateType::VERTEX_INPUT_BINDING_DESCRIPTION, binding);
        }
    }

    // vertex input attribute descriptions
    if (auto vertexInputAttributeIter =
            context->commandBufferRecordingVertexInputAttributeDescriptions.find(commandBufferRecordingId);
        vertexInputAttributeIter != context->commandBufferRecordingVertexInputAttributeDescriptions.end())
    {
        for (const auto& [location, stateId] : vertexInputAttributeIter->second)
        {
            entries.emplace_back(stateId, StateType::VERTEX_INPUT_ATTRIBUTE_DESCRIPTION, location);
        }
    }

    // dynamic viewports
    if (auto viewportsIter = context->commandBufferRecordingDynamicViewports.find(commandBufferRecordingId);
        viewportsIter != context->commandBufferRecordingDynamicViewports.end())
    {
        for (const auto& [viewportIndex, stateId] : viewportsIter->second)
        {
            entries.emplace_back(stateId, StateType::VIEWPORT, viewportIndex);
        }
    }

    // dynamic scissors
    if (auto scissorsIter = context->commandBufferRecordingDynamicScissors.find(commandBufferRecordingId);
        scissorsIter != context->commandBufferRecordingDynamicScissors.end())
    {
        for (const auto& [scissorIndex, stateId] : scissorsIter->second)
        {
            entries.emplace_back(stateId, StateType::SCISSOR, scissorIndex);
        }
    }

    // dynamic line width
    if (auto lineWidthIter = context->commandBufferRecordingDynamicLineWidths.find(commandBufferRecordingId);
        lineWidthIter != context->commandBufferRecordingDynamicLineWidths.end())
    {
        entries.emplace_back(lineWidthIter->second, StateType::LINE_WIDTH);
    }

    // dynamic rendering color attachment locations
    if (auto renderingColorAttachmentLocationsIter =
            context->commandBufferRecordingDynamicRenderingColorAttachmentLocations.find(commandBufferRecordingId);
        renderingColorAttachmentLocationsIter !=
        context->commandBufferRecordingDynamicRenderingColorAttachmentLocations.end())
    {
        for (const auto& [oldLocation, stateId] : renderingColorAttachmentLocationsIter->second)
        {
            entries.emplace_back(stateId, StateType::RENDERING_COLOR_ATTACHMENT_LOCATION, oldLocation);
        }
    }

    // dynamic rendering color input attachment indices
    if (auto renderingColorInputAttachmentIndicesIter =
            context->commandBufferRecordingDynamicRenderingInputColorAttachmentIndices.find(commandBufferRecordingId);
        renderingColorInputAttachmentIndicesIter !=
        context->commandBufferRecordingDynamicRenderingInputColorAttachmentIndices.end())
    {
        for (const auto& [oldInputIdx, stateId] : renderingColorInputAttachmentIndicesIter->second)
        {
            entries.emplace_back(stateId, StateType::RENDERING_INPUT_COLOR_ATTACHMENT_INDEX, oldInputIdx);
        }
    }

    // dynamic rendering depth input attachment indices
    if (auto renderingDepthInputAttachmentIndicesIter =
            context->commandBufferRecordingDynamicRenderingInputDepthAttachmentIndices.find(commandBufferRecordingId);
        renderingDepthInputAttachmentIndicesIter !=
        context->commandBufferRecordingDynamicRenderingInputDepthAttachmentIndices.end())
    {
        entries.emplace_back(
            renderingDepthInputAttachmentIndicesIter->second, StateType::RENDERING_INPUT_DEPTH_ATTACHMENT_INDEX
        );
    }

    // dynamic rendering stencil input attachment indices
    if (auto renderingStencilInputAttachmentIndicesIter =
            context->commandBufferRecordingDynamicRenderingInputStencilAttachmentIndices.find(commandBufferRecordingId);
        renderingStencilInputAttachmentIndicesIter !=
        context->commandBufferRecordingDynamicRenderingInputStencilAttachmentIndices.end())
    {
        entries.emplace_back(
            renderingStencilInputAttachmentIndicesIter->second, StateType::RENDERING_INPUT_STENCIL_ATTACHMENT_INDEX
        );
    }

    // dynamic depth bounds
    if (auto depthBoundsIter = context->commandBufferRecordingDynamicDepthBounds.find(commandBufferRecordingId);
        depthBoundsIter != context->commandBufferRecordingDynamicDepthBounds.end())
    {
        entries.emplace_back(depthBoundsIter->second, StateType::DEPTH_BOUNDS);
    }

    // dynamic depth bounds test enable
    if (auto depthBoundsTestEnableIter =
            context->commandBufferRecordingDynamicDepthBoundsTestEnable.find(commandBufferRecordingId);
        depthBoundsTestEnableIter != context->commandBufferRecordingDynamicDepthBoundsTestEnable.end())
    {
        entries.emplace_back(depthBoundsTestEnableIter->second, StateType::DEPTH_BOUNDS_TEST_ENABLE);
    }

    // dynamic depth bias
    if (auto depthBiasIter = context->commandBufferRecordingDynamicDepthBias.find(commandBufferRecordingId);
        depthBiasIter != context->commandBufferRecordingDynamicDepthBias.end())
    {
        entries.emplace_back(depthBiasIter->second, StateType::DEPTH_BIAS);
    }

    // dynamic depth bias enable
    if (auto depthBiasEnableIter = context->commandBufferRecordingDynamicDepthBiasEnable.find(commandBufferRecordingId);
        depthBiasEnableIter != context->commandBufferRecordingDynamicDepthBiasEnable.end())
    {
        entries.emplace_back(depthBiasEnableIter->second, StateType::DEPTH_BIAS_ENABLE);
    }

    // dynamic depth test enable
    if (auto depthTestEnableIter = context->commandBufferRecordingDynamicDepthTestEnable.find(commandBufferRecordingId);
        depthTestEnableIter != context->commandBufferRecordingDynamicDepthTestEnable.end())
    {
        entries.emplace_back(depthTestEnableIter->second, StateType::DEPTH_TEST_ENABLE);
    }

    // dynamic depth write enable
    if (auto depthWriteEnableIter =
            context->commandBufferRecordingDynamicDepthWriteEnable.find(commandBufferRecordingId);
        depthWriteEnableIter != context->commandBufferRecordingDynamicDepthWriteEnable.end())
    {
        entries.emplace_back(depthWriteEnableIter->second, StateType::DEPTH_WRITE_ENABLE);
    }

    // dynamic depth compare op
    if (auto depthCompareOpIter = context->commandBufferRecordingDynamicDepthCompareOps.find(commandBufferRecordingId);
        depthCompareOpIter != context->commandBufferRecordingDynamicDepthCompareOps.end())
    {
        entries.emplace_back(depthCompareOpIter->second, StateType::DEPTH_COMPARE_OPS);
    }

    // dynamic stencil compare mask front
    if (auto stencilCompareMaskFrontIter =
            context->commandBufferRecordingDynamicStencilCompareMaskFront.find(commandBufferRecordingId);
        stencilCompareMaskFrontIter != context->commandBufferRecordingDynamicStencilCompareMaskFront.end())
    {
        entries.emplace_back(stencilCompareMaskFrontIter->second, StateType::STENCIL_COMPARE_MASK_FRONT);
    }

    // dynamic stencil compare mask back
    if (auto stencilCompareMaskBackIter =
            context->commandBufferRecordingDynamicStencilCompareMaskBack.find(commandBufferRecordingId);
        stencilCompareMaskBackIter != context->commandBufferRecordingDynamicStencilCompareMaskBack.end())
    {
        entries.emplace_back(stencilCompareMaskBackIter->second, StateType::STENCIL_COMPARE_MASK_BACK);
    }

    // dynamic stencil write mask front
    if (auto stencilWriteMaskFrontIter =
            context->commandBufferRecordingDynamicStencilWriteMaskFront.find(commandBufferRecordingId);
        stencilWriteMaskFrontIter != context->commandBufferRecordingDynamicStencilWriteMaskFront.end())
    {
        entries.emplace_back(stencilWriteMaskFrontIter->second, StateType::STENCIL_WRITE_MASK_FRONT);
    }

    // dynamic stencil write mask back
    if (auto stencilWriteMaskBackIter =
            context->commandBufferRecordingDynamicStencilWriteMaskBack.find(commandBufferRecordingId);
        stencilWriteMaskBackIter != context->commandBufferRecordingDynamicStencilWriteMaskBack.end())
    {
        entries.emplace_back(stencilWriteMaskBackIter->second, StateType::STENCIL_WRITE_MASK_BACK);
    }

    // dynamic stencil reference front
    if (auto stencilReferenceFrontIter =
            context->commandBufferRecordingDynamicStencilReferenceFront.find(commandBufferRecordingId);
        stencilReferenceFrontIter != context->commandBufferRecordingDynamicStencilReferenceFront.end())
    {
        entries.emplace_back(stencilReferenceFrontIter->second, StateType::STENCIL_REFERENCE_FRONT);
    }

    // dynamic stencil write mask back
    if (auto stencilReferenceBackIter =
            context->commandBufferRecordingDynamicStencilReferenceBack.find(commandBufferRecordingId);
        stencilReferenceBackIter != context->commandBufferRecordingDynamicStencilReferenceBack.end())
    {
        entries.emplace_back(stencilReferenceBackIter->second, StateType::STENCIL_REFERENCE_BACK);
    }

    // dynamic stencil test enable
    if (auto stencilTestEnableIter =
            context->commandBufferRecordingDynamicStencilTestEnable.find(commandBufferRecordingId);
        stencilTestEnableIter != context->commandBufferRecordingDynamicStencilTestEnable.end())
    {
        entries.emplace_back(stencilTestEnableIter->second, StateType::STENCIL_TEST_ENABLE);
    }

    // dynamic stencil ops front
    if (auto stencilOpsFrontIter = context->commandBufferRecordingDynamicStencilOpsFront.find(commandBufferRecordingId);
        stencilOpsFrontIter != context->commandBufferRecordingDynamicStencilOpsFront.end())
    {
        entries.emplace_back(stencilOpsFrontIter->second, StateType::STENCIL_OPS_FRONT);
    }

    // dynamic stencil ops back
    if (auto stencilOpsBackIter = context->commandBufferRecordingDynamicStencilOpsBack.find(commandBufferRecordingId);
        stencilOpsBackIter != context->commandBufferRecordingDynamicStencilOpsBack.end())
    {
        entries.emplace_back(stencilOpsBackIter->second, StateType::STENCIL_OPS_BACK);
    }

    // dynamic color write enable
    if (auto colorWriteEnableAttachmentIndicesIter =
            context->commandBufferRecordingDynamicColorWriteEnable.find(commandBufferRecordingId);
        colorWriteEnableAttachmentIndicesIter != context->commandBufferRecordingDynamicColorWriteEnable.end())
    {
        for (const auto& [attachmentIndex, stateId] : colorWriteEnableAttachmentIndicesIter->second)
        {
            entries.emplace_back(stateId, StateType::COLOR_WRITE_ENABLE, attachmentIndex);
        }
    }

    // dynamic blend constants
    if (auto blendConstantsIter = context->commandBufferRecordingDynamicBlendConstants.find(commandBufferRecordingId);
        blendConstantsIter != context->commandBufferRecordingDynamicBlendConstants.end())
    {
        entries.emplace_back(blendConstantsIter->second, StateType::BLEND_CONSTANTS);
    }

    // dynamic primitive topologies
    if (auto primitiveTopologiesIter =
            context->commandBufferRecordingDynamicPrimitiveTopologies.find(commandBufferRecordingId);
        primitiveTopologiesIter != context->commandBufferRecordingDynamicPrimitiveTopologies.end())
    {
        entries.emplace_back(primitiveTopologiesIter->second, StateType::PRIMITIVE_TOPOLOGY);
    }

    // dynamic cull modes
    if (auto cullModesIter = context->commandBufferRecordingDynamicCullModes.find(commandBufferRecordingId);
        cullModesIter != context->commandBufferRecordingDynamicCullModes.end())
    {
        entries.emplace_back(cullModesIter->second, StateType::CULL_MODE);
    }

    // dynamic front faces
    if (auto frontFacesIter = context->commandBufferRecordingDynamicFrontFaces.find(commandBufferRecordingId);
        frontFacesIter != context->commandBufferRecordingDynamicFrontFaces.end())
    {
        entries.emplace_back(frontFacesIter->second, StateType::FRONT_FACE);
    }

    // dynamic logic ops
    if (auto logicOpsIter = context->commandBufferRecordingDynamicLogicOps.find(commandBufferRecordingId);
        logicOpsIter != context->commandBufferRecordingDynamicLogicOps.end())
    {
        entries.emplace_back(logicOpsIter->second, StateType::LOGIC_OP);
    }

    // dynamic rasterizer discard enable
    if (auto rasterizerDiscardIter =
            context->commandBufferRecordingDynamicRasterizerDiscardEnable.find(commandBufferRecordingId);
        rasterizerDiscardIter != context->commandBufferRecordingDynamicRasterizerDiscardEnable.end())
    {
        entries.emplace_back(rasterizerDiscardIter->second, StateType::RASTERIZER_DISCARD_ENABLE);
    }

    // dynamic patch control points
    if (auto patchControlPointsIter =
            context->commandBufferRecordingDynamicPatchControlPoints.find(commandBufferRecordingId);
        patchControlPointsIter != context->commandBufferRecordingDynamicPatchControlPoints.end())
    {
        entries.emplace_back(patchControlPointsIter->second, StateType::PATCH_CONTROL_POINTS);
    }

    // dynamic primitive restart enable
    if (auto primitiveRestartIter =
            context->commandBufferRecordingDynamicPrimitiveRestartEnable.find(commandBufferRecordingId);
        primitiveRestartIter != context->commandBufferRecordingDynamicPrimitiveRestartEnable.end())
    {
        entries.emplace_back(primitiveRestartIter->second, StateType::PRIMITIVE_RESTART_ENABLE);
    }

    auto& statement = stateGroupEntryInsertStatement;
    for (const auto& entry : entries)
    {
        GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateGroupId)));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(entry.stateId)));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(entry.stateTypeId)));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(entry.idx)));
        GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(entry.subIndex)));
        GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    }
    context->commandBufferRecordingPreviousStateEntries[commandBufferRecordingId] = std::move(entries);
}

int64_t VulkanSqlitePreparedStatements::InsertStatePipelineBinding(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const int64_t pipelineId,
    const VkPipelineBindPoint bindPoint
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingPipelineBindings[commandBufferRecordingId][bindPoint] = stateId;

    // Clear any dynamic state entries for states not declared dynamic by the pipeline being bound.
    // If the pipeline is not found (e.g. not yet created), treat as if it declares no dynamic states,
    // which will clear all tracked dynamic state for this bind point.
    const auto pipelineStatesIter = context->pipelineIdToDynamicStates.find(pipelineId);
    static const std::unordered_set<VkDynamicState> kEmptyDynamicStates;
    const auto& declaredDynamicStates = (pipelineStatesIter != context->pipelineIdToDynamicStates.end())
        ? pipelineStatesIter->second
        : kEmptyDynamicStates;
    context->InvalidateDynamicStates(commandBufferRecordingId, bindPoint, declaredDynamicStates);

    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = statePipelineBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(bindPoint)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateShaderObjectBinding(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const int64_t shaderObjectId,
    const VkShaderStageFlagBits stage
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingShaderObjectBindings[commandBufferRecordingId][stage] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateShaderObjectBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stage)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(shaderObjectId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateIndexBufferBinding(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> bufferId,
    const uint64_t offset,
    const VkIndexType indexType,
    const std::optional<uint64_t> size
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingIndexBindings[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateIndexBufferBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, bufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(indexType)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, size));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateVertexBufferBinding(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t binding,
    const std::optional<int64_t> bufferId,
    const uint64_t offset,
    const std::optional<uint64_t> size,
    const std::optional<uint64_t> stride
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingVertexBindings[commandBufferRecordingId][binding] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateVertexBufferBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, bufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, size));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, stride));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDescriptorSetBinding(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t setIndex,
    const VkShaderStageFlags stageFlags,
    const int64_t pipelineLayoutId,
    const int64_t descriptorSetId
)
{
    auto stateId = InsertStateId(apiEventId);
    // we store the stage flags but we actually track at the pipeline bind point level since that is
    // what would be reset if somthing is changed. Thus we need to map back to the bind point that the given
    // shader stage flags apply to.
    if (stageFlags &
        (VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT |
         VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT | VK_SHADER_STAGE_GEOMETRY_BIT | VK_SHADER_STAGE_FRAGMENT_BIT |
         VK_SHADER_STAGE_TASK_BIT_EXT | VK_SHADER_STAGE_MESH_BIT_EXT | VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI))
    {
        context->commandBufferRecordingDescriptorSetBindings[commandBufferRecordingId][VK_PIPELINE_BIND_POINT_GRAPHICS]
                                                            [setIndex] = stateId;
    }
    if (stageFlags & VK_SHADER_STAGE_COMPUTE_BIT)
    {
        context->commandBufferRecordingDescriptorSetBindings[commandBufferRecordingId][VK_PIPELINE_BIND_POINT_COMPUTE]
                                                            [setIndex] = stateId;
    }
    if (stageFlags &
        (VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR |
         VK_SHADER_STAGE_MISS_BIT_KHR | VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR))
    {
        context->commandBufferRecordingDescriptorSetBindings[commandBufferRecordingId]
                                                            [VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR][setIndex] =
            stateId;
    }
    if (stageFlags & VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI)
    {
        context->commandBufferRecordingDescriptorSetBindings[commandBufferRecordingId]
                                                            [VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI][setIndex] =
            stateId;
    }

    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDescriptorSetBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(setIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(stageFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(pipelineLayoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(descriptorSetId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

void VulkanSqlitePreparedStatements::InsertStateDescriptorSetBindingDynamicOffset(
    const uint64_t stateId, const uint32_t binding, const uint32_t arrayElement, const uint32_t dynamicOffset
)
{
    auto& statement = stateDescriptorSetBindingDynamicOffsetInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(arrayElement)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(dynamicOffset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertStateDescriptorSetPush(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t setIndex,
    const uint32_t binding,
    const uint32_t arrayElement,
    const VkDescriptorType descriptorType
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDescriptorSetPushes[commandBufferRecordingId][binding][arrayElement] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDescriptorSetPushInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(setIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(arrayElement)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(descriptorType)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateVertexInputBindingDescription(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t binding,
    const uint32_t stride,
    const VkVertexInputRate inputRate
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingVertexInputBindingDescriptions[commandBufferRecordingId][binding] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicVertexInputBindingDescriptionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(stride)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(inputRate)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateVertexInputAttributeDescription(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t location,
    const uint32_t binding,
    const VkFormat format,
    const uint32_t offset
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingVertexInputAttributeDescriptions[commandBufferRecordingId][location] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicVertexInputAttributeDescriptionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(location)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicViewport(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t viewportIndex,
    const float x,
    const float y,
    const float width,
    const float height,
    const float minDepth,
    const float maxDepth
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicViewports[commandBufferRecordingId][viewportIndex] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicViewportInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(viewportIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, x));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, y));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, width));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 7, height));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 8, minDepth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 9, maxDepth));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicScissor(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const uint32_t scissorIndex,
    const VkOffset2D& offset,
    const VkExtent2D& extent
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicScissors[commandBufferRecordingId][scissorIndex] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicScissorInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(scissorIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, offset.x));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, offset.y));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(extent.width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(extent.height)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicRenderingColorAttachmentLocation(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t oldLocation, uint32_t newLocation
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicRenderingColorAttachmentLocations[commandBufferRecordingId][oldLocation] =
        stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicRenderingColorAttachmentLocationInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(oldLocation)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(newLocation)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicRenderingInputColorAttachmentIndex(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t oldIndex, const uint32_t newIndex
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicRenderingInputColorAttachmentIndices[commandBufferRecordingId][oldIndex] =
        stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicRenderingInputColorAttachmentIndexInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(oldIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(newIndex)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicRenderingInputDepthAttachmentIndex(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t newIndex
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicRenderingInputDepthAttachmentIndices[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicRenderingInputDepthAttachmentIndexInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(newIndex)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicRenderingInputStencilAttachmentIndex(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t newIndex
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicRenderingInputStencilAttachmentIndices[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicRenderingInputStencilAttachmentIndexInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(newIndex)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicLineWidth(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, float lineWidth
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicLineWidths[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicLineWidthInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, lineWidth));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthBounds(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const float minDepthBounds, float maxDepthBounds
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthBounds[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthBoundsInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, minDepthBounds));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, maxDepthBounds));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthBoundsTestEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enabled
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthBoundsTestEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthBoundsTestEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enabled)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthBias(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const float constantFactor,
    const float clamp,
    const float slopeFactor,
    const VkDepthBiasRepresentationEXT representation,
    VkBool32 exact
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthBias[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthBiasInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, constantFactor));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, clamp));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, slopeFactor));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(representation)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(exact)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthBiasEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enabled
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthBiasEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthBiasEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enabled)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthTestEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enabled
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthTestEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthTestEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enabled)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthWriteEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enabled
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthWriteEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthWriteEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enabled)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicDepthCompareOp(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, VkCompareOp compareOp
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicDepthCompareOps[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicDepthCompareOpInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(compareOp)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilCompareMaskFront(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t frontMask
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilCompareMaskFront[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilCompareMaskFrontInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(frontMask)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilCompareMaskBack(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t backMask
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilCompareMaskBack[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilCompareMaskBackInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(backMask)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilWriteMaskFront(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t frontMask
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilWriteMaskFront[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilWriteMaskFrontInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(frontMask)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilWriteMaskBack(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t backMask
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilWriteMaskBack[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilWriteMaskBackInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(backMask)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilReferenceFront(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t reference
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilReferenceFront[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilReferenceFrontInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(reference)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilReferenceBack(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, uint32_t reference
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilReferenceBack[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilReferenceBackInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(reference)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilTestEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enabled
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilTestEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilTestEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enabled)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilOpsFront(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const VkStencilOp failOp,
    const VkStencilOp passOp,
    const VkStencilOp depthFailOp,
    VkCompareOp compareOp
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilOpsFront[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilOpsFrontInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(failOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(passOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(depthFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(compareOp)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicStencilOpsBack(
    const uint64_t apiEventId,
    const int64_t commandBufferRecordingId,
    const VkStencilOp failOp,
    const VkStencilOp passOp,
    const VkStencilOp depthFailOp,
    VkCompareOp compareOp
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicStencilOpsBack[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicStencilOpsBackInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(failOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(passOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(depthFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(compareOp)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicColorWriteEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, const uint32_t attachmentIndex, bool enable
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicColorWriteEnable[commandBufferRecordingId][attachmentIndex] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicColorWriteEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(enable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicBlendConstants(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, std::span<const float, 4> blendConstants
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicBlendConstants[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicBlendConstantInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(blendConstants[0])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(blendConstants[1])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(blendConstants[2])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(blendConstants[3])));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicPrimitiveTopology(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, VkPrimitiveTopology topology
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicPrimitiveTopologies[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicPrimitiveTopologyInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(topology)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicCullMode(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, VkCullModeFlags cullMode
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicCullModes[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicCullModeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(cullMode)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicFrontFace(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, VkFrontFace frontFace
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicFrontFaces[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicFrontFaceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(frontFace)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicLogicOp(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, VkLogicOp logicOp
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicLogicOps[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicLogicOpInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(logicOp)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicRasterizerDiscardEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enable
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicRasterizerDiscardEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicRasterizerDiscardEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicPatchControlPoints(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool patchControlPoints
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicPatchControlPoints[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicPatchControlPointInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(patchControlPoints)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertStateDynamicPrimitiveRestartEnable(
    const uint64_t apiEventId, const int64_t commandBufferRecordingId, bool enable
)
{
    auto stateId = InsertStateId(apiEventId);
    context->commandBufferRecordingDynamicPrimitiveRestartEnable[commandBufferRecordingId] = stateId;
    context->commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);

    auto& statement = stateDynamicPrimitiveRestartEnableInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(enable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertQueuePresent(
    int64_t queueId, const int64_t frame, const int64_t apiEventId
)
{
    auto presentId = ++context->currentQueuePresentId;

    auto& statement = queuePresentInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(presentId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(queueId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(frame)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return presentId;
}

void VulkanSqlitePreparedStatements::InsertQueuePresentSemaphoreWait(
    const int64_t presentId, const size_t waitIndex, std::optional<int64_t> semaphoreId
)
{
    auto& statement = queuePresentSemaphoreWaitInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(presentId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(waitIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, semaphoreId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertQueuePresentSwapchain(
    const int64_t presentId,
    const std::optional<int64_t> swapchainId,
    uint32_t imageIndex,
    const std::optional<int64_t> fenceId
)
{
    auto& statement = queuePresentSwapchainInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(presentId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, swapchainId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(imageIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, fenceId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertRenderPass(
    const format::HandleId handle,
    const std::optional<int64_t> deviceId,
    const VkRenderPassCreateFlags flags,
    uint64_t apiEventId
)
{
    auto renderPassId = ++context->currentRenderPassId;
    auto renderPassHandle = ToInt64(handle);
    context->renderPassHandleToId[renderPassHandle] = renderPassId;

    auto& statement = renderPassInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(renderPassHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return renderPassId;
}

void VulkanSqlitePreparedStatements::InsertRenderPassAttachment(
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
)
{
    auto& statement = renderPassAttachmentInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPass)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(index)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(samples)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(loadOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(storeOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(stencilLoadOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(stencilStoreOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(initialLayout)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(finalLayout)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertRenderSubpass(
    const int64_t renderPassId,
    const size_t subpassIndex,
    const VkSubpassDescriptionFlags flags,
    VkPipelineBindPoint pipelineBindPoint
)
{
    auto& statement = renderSubpassInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(pipelineBindPoint)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertBlankRenderSubpassAttachmentReference(
    const int64_t renderPassId, const size_t subpassIndex, size_t attachmentIndex
)
{
    auto& statement = renderSubpassBlankAttachmentReferencesInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertSubpassDependencies(
    const int64_t renderPassId,
    const uint32_t srcSubpass,
    const uint32_t dstSubpass,
    const VkPipelineStageFlags srcStageMask,
    const VkPipelineStageFlags dstStageMask,
    const VkAccessFlags srcAccessMask,
    const VkAccessFlags dstAccessMask,
    VkDependencyFlags dependencyFlags
)
{
    auto& statement = renderSubpassDependenciesInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(srcSubpass)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(dstSubpass)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(srcStageMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(dstStageMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(srcAccessMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(dstAccessMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(dependencyFlags)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateSubpassAttachmentReferenceLayout(
    const SqliteStatement& statement,
    const int64_t renderPassId,
    const size_t subpassIndex,
    const uint32_t attachment,
    const VkImageLayout layout
)
{
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(layout)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(attachment)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateSubpassAttachmentReferencePreserve(
    const int64_t renderPassId, const size_t subpassIndex, const uint32_t attachment
)
{
    auto& statement = renderSubpassSetAttachmentReferencePreserveUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(renderPassId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(attachment)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorUpdateTemplateEntry(
    const int64_t templateId, const VkDescriptorUpdateTemplateEntry* entry
)
{
    auto& statement = descriptorUpdateTemplateEntryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(templateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(entry->dstBinding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(entry->dstArrayElement)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(entry->descriptorCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(entry->descriptorType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(entry->offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(entry->stride)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDescriptorUpdateTemplate(
    const format::HandleId updateTemplate,
    const format::HandleId device,
    const VkDescriptorUpdateTemplateCreateFlags flags,
    const VkDescriptorUpdateTemplateType templateType,
    const std::optional<int64_t> descriptorSetLayout,
    const std::optional<VkPipelineBindPoint> pipelineBindPoint,
    const std::optional<int64_t> pipelineLayout,
    const std::optional<uint32_t> setIndex,
    const uint64_t apiEventId
)
{
    auto templateHandle = ToInt64(updateTemplate);
    auto deviceId = context->GetDeviceId(device);
    auto descriptorUpdateTemplateId = ++context->currentDescriptorUpdateTemplateId;
    context->descriptorUpdateTemplateHandleToId[templateHandle] = descriptorUpdateTemplateId;

    auto& statement = descriptorUpdateTemplateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(descriptorUpdateTemplateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(templateHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(templateType)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, descriptorSetLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, pipelineBindPoint));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, setIndex));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return descriptorUpdateTemplateId;
}

int64_t VulkanSqlitePreparedStatements::InsertDescriptorSetWrite(
    const int64_t descriptorSet,
    const uint32_t binding,
    const int64_t arrayElement,
    const VkDescriptorType descriptorType,
    uint64_t apiEventId
)
{
    auto writeId = ++context->currentDescriptorSetWrite;

    const auto& statement = descriptorSetWriteInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(descriptorSet)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(arrayElement)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(descriptorType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));

    return writeId;
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetWriteImageInfo(
    const int64_t writeId,
    const std::optional<int64_t> sampler,
    const std::optional<int64_t> imageView,
    const int64_t imageLayout,
    bool isPush
)
{
    const auto& statement =
        isPush ? stateDescriptorSetPushImageInfoInsertStatement : descriptorSetWriteImageInfoInsertStatement;

    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, sampler));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, imageView));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(imageLayout)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetWriteBufferInfo(
    const int64_t writeId,
    const std::optional<int64_t> buffer,
    const VkDeviceSize offset,
    const VkDeviceSize range,
    bool isPush
)
{
    const auto& statement =
        isPush ? stateDescriptorSetPushBufferInfoInsertStatement : descriptorSetWriteBufferInfoInsertStatement;

    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, buffer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(range)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetWriteTexelInfo(
    const int64_t writeId, const std::optional<int64_t> bufferView, bool isPush
)
{
    const auto& statement =
        isPush ? stateDescriptorSetPushTexelInfoInsertStatement : descriptorSetWriteTexelInfoInsertStatement;

    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, bufferView));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetWriteAccelerationInfo(
    const int64_t writeId, const std::optional<int64_t> accelerationStructure, bool isPush
)
{
    const auto& statement = isPush ? stateDescriptorSetPushAccelerationInfoInsertStatement
                                   : descriptorSetWriteAccelerationInfoInsertStatement;

    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, accelerationStructure));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetWriteAccelerationNvInfo(
    const int64_t writeId, const std::optional<int64_t> accelerationStructureNv, bool isPush
)
{
    const auto& statement = isPush ? stateDescriptorSetPushAccelerationNvInfoInsertStatement
                                   : descriptorSetWriteAccelerationNvInfoInsertStatement;

    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, accelerationStructureNv));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::CopyDescriptorSetInfo(
    const SqliteStatement& statement,
    const int64_t descriptorSetId,
    const uint32_t readBinding,
    const uint32_t srcElement,
    const int64_t writeId
)
{
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(descriptorSetId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(readBinding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(srcElement)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(writeId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertBuffer(
    const format::HandleId buffer,
    const format::HandleId device,
    const VkBufferCreateFlags flags,
    const VkDeviceSize size,
    const VkBufferUsageFlags usage,
    const std::optional<int64_t> usage2,
    const VkSharingMode sharing,
    const uint64_t apiEventId
)
{
    auto bufferHandle = ToInt64(buffer);
    auto deviceId = context->GetDeviceId(device);
    auto bufferId = ++context->currentBufferId;
    context->bufferHandleToId[bufferHandle] = bufferId;

    auto& statement = bufferInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(bufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(bufferHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(usage)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, usage2));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(sharing)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertBufferView(
    const format::HandleId view,
    const format::HandleId device,
    const std::optional<int64_t> bufferId,
    const VkFormat format,
    const VkDeviceSize offset,
    const int64_t range,
    const uint64_t apiEventId
)
{
    auto viewHandle = ToInt64(view);
    auto deviceId = context->GetDeviceId(device);
    auto bufferViewId = ++context->currentBufferViewId;
    context->bufferViewHandleToId[viewHandle] = bufferViewId;

    auto& statement = bufferViewInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(bufferViewId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(viewHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, bufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(range)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return bufferViewId;
}

void VulkanSqlitePreparedStatements::InsertImage(
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
)
{
    auto imageHandle = ToInt64(image);
    auto deviceId = context->GetDeviceId(device);
    auto imageId = ++context->currentImageId;
    context->imageHandleToId[imageHandle] = imageId;

    auto& statement = imageInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(imageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(imageHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(imageType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(extent.width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(extent.height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(extent.depth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(mipLevels)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(layers)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(samples)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(tiling)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(usage)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(sharing)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 16, static_cast<sqlite_int64>(initialLayout)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 17, externalFormat));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 18, externalMemoryHandleTypes));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 19, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertImageViewFormat(const int64_t imageId, const int64_t viewFormat)
{
    auto& statement = imageViewFormatInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(imageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(viewFormat)));

    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertImageView(
    const format::HandleId view,
    const format::HandleId device,
    const VkImageViewCreateFlags flags,
    const std::optional<int64_t> imageId,
    const VkImageViewType viewType,
    const VkFormat format,
    const VkComponentMapping& components,
    const VkImageSubresourceRange& srRange,
    const std::optional<int64_t> usage,
    const uint64_t apiEventId
)
{
    auto viewHandle = ToInt64(view);
    auto deviceId = context->GetDeviceId(device);
    auto imageViewId = ++context->currentImageViewId;
    context->imageViewHandleToId[viewHandle] = imageViewId;

    auto& statement = imageViewInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(imageViewId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(viewHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, imageId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(viewType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(components.r)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(components.g)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(components.b)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(components.a)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(srRange.aspectMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(srRange.baseMipLevel)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(srRange.levelCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(srRange.baseArrayLayer)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 16, static_cast<sqlite_int64>(srRange.layerCount)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 17, usage));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 18, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertSampler(
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
    const uint64_t apiEventId
)
{
    auto samplerHandle = ToInt64(sampler);
    auto deviceId = context->GetDeviceId(device);
    auto samplerId = ++context->currentSamplerId;
    context->samplerHandleToId[samplerHandle] = samplerId;

    auto& statement = samplerInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(samplerId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(samplerHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(magFilter)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(minFilter)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(mipmapMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(addressModeU)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(addressModeV)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(addressModeW)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(mipLodBias)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(anisotropyEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(maxAnisotropy)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(compareEnable)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 15, compareOp));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 16, minLod));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 17, maxLod));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 18, borderColor));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 19, static_cast<sqlite_int64>(unnormalizedCoordinates)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 20, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertCommandBufferCommand(
    int64_t commandBufferRecordingId, const uint64_t apiEventId
)
{
    auto& statement = commandBufferCommandInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDisplayMessage(int64_t frame, const std::string_view message)
{
    auto displayMessageId = ++context->currentDisplayMessageId;
    auto& statement = displayMessageInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(displayMessageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(frame)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 3, message.data(), message.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_clear_bindings(statement));
    return displayMessageId;
}

void VulkanSqlitePreparedStatements::InsertSwapchainImage(
    const format::HandleId image, const format::HandleId device, const int64_t swapchainId
)
{
    auto imageHandle = ToInt64(image);
    auto deviceId = context->GetDeviceId(device);
    auto imageId = ++context->currentImageId;
    context->imageHandleToId[imageHandle] = imageId;

    auto& statement = swapchainImageInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(imageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(imageHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(swapchainId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(VK_IMAGE_TYPE_2D)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, 1)); // imageDepth: swapchain is always 2D
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, 1)); // mipLevels: swapchain generates none
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, 1)); // sampleCount: swapchain does not configure
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(VK_IMAGE_TILING_OPTIMAL)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(VK_IMAGE_LAYOUT_UNDEFINED)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(swapchainId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertSwapchain(
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
    const uint64_t apiEventId
)
{
    auto swapchainHandle = ToInt64(swapchain);
    auto deviceId = context->GetDeviceId(device);
    auto swapchainId = ++context->currentSwapchainId;
    context->swapchainHandleToId[swapchainHandle] = swapchainId;

    auto& statement = swapchainInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(swapchainId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(swapchainHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(minImageCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(imageFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(imageColorSpace)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(imageExtent.width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(imageExtent.height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(imageLayers)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(imageUsage)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(imageSharingMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(preTransform)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(compositeAlpha)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(presentMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 16, static_cast<sqlite_int64>(clipped)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 17, oldSwapchainId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 18, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructure(
    const format::HandleId accelerationStructure,
    const format::HandleId device,
    const VkAccelerationStructureCreateFlagsKHR flags,
    const VkAccelerationStructureTypeKHR type,
    const format::HandleId buffer,
    const uint64_t offset,
    const uint64_t size,
    const VkDeviceAddress deviceAddress,
    const uint64_t apiEventId
)
{
    auto accelerationStructureId = ++context->currentAccelerationStructureId;
    auto deviceId = context->GetDeviceId(device);
    auto accelerationStructureHandle = ToInt64(accelerationStructure);
    context->accelerationStructureHandleToId[accelerationStructureHandle] = accelerationStructureId;
    auto bufferId = context->GetBufferId(buffer);
    auto& statement = accelerationStructureInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(accelerationStructureId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(accelerationStructureHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, bufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(deviceAddress)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return accelerationStructureId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureNv(
    const format::HandleId accelerationStructure,
    const format::HandleId device,
    const VkBuildAccelerationStructureFlagsNV flags,
    const VkAccelerationStructureTypeNV type,
    const uint64_t compactSize,
    const uint64_t instanceCount,
    const uint64_t apiEventId
)
{
    auto accelerationStructureId = ++context->currentAccelerationStructureNvId;
    auto deviceId = context->GetDeviceId(device);
    auto accelerationStructureHandle = ToInt64(accelerationStructure);
    context->accelerationStructureNvHandleToId[accelerationStructureHandle] = accelerationStructureId;
    auto& statement = accelerationStructureNvInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(accelerationStructureId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(accelerationStructureHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(compactSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(instanceCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return accelerationStructureId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureBuild(
    const std::optional<format::HandleId> device,
    const std::optional<format::HandleId> deferredOperation,
    const std::optional<format::HandleId> commandBuffer,
    const uint64_t apiEventId
)
{
    auto buildId = ++context->currentAccelerationStructureBuildId;
    std::optional<int64_t> deviceId = std::nullopt;
    std::optional<int64_t> frameNumber = std::nullopt;
    if (device.has_value())
    {
        deviceId = context->GetDeviceId(device.value());
        frameNumber = context->currentFrame;
    }
    std::optional<int64_t> deferredOperationId = std::nullopt;
    if (deferredOperation.has_value())
    {
        deferredOperationId = context->GetDeferredOperationId(deferredOperation.value());
    }
    std::optional<int64_t> commandBufferRecordingId = std::nullopt;
    if (commandBuffer.has_value())
    {
        commandBufferRecordingId = context->GetCommandBufferRecordingId(commandBuffer.value());
    }
    auto& statement = accelerationStructureBuildInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(buildId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, deviceId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, frameNumber));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, deferredOperationId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return buildId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildGeometryInfo(
    const int64_t buildId,
    const size_t infoIndex,
    const VkAccelerationStructureTypeKHR type,
    const VkBuildAccelerationStructureFlagsKHR flags,
    const VkBuildAccelerationStructureModeKHR mode,
    const format::HandleId srcAccelStruct,
    const format::HandleId dstAccelStruct,
    const VkDeviceOrHostAddressKHR scratchDataAddress
)
{
    auto infoId = ++context->currentAccelerationStructureBuildGeometryInfoId;
    std::optional<int64_t> srcAccelStructId = context->GetAccelerationStructureId(srcAccelStruct, true);
    std::optional<int64_t> dstAccelStructId = context->GetAccelerationStructureId(dstAccelStruct);
    auto& statement = accelerationStructureBuildGeometryInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, infoId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, buildId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(infoIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(mode)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, srcAccelStructId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, dstAccelStructId));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(scratchDataAddress.deviceAddress))
    );
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return infoId;
}

void VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildGeometry(
    const int64_t infoId,
    const size_t geometryIndex,
    const VkGeometryTypeKHR type,
    const VkGeometryFlagsKHR flags,
    const std::optional<int64_t> triangleDataId,
    const std::optional<int64_t> aabbDataId,
    const std::optional<int64_t> instanceDataId
)
{
    auto& statement = accelerationStructureBuildGeometryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, infoId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(geometryIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, triangleDataId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, aabbDataId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, instanceDataId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildRangeInfo(
    const int64_t infoId,
    const size_t rangeIndex,
    const uint32_t primitiveCount,
    const uint32_t primitiveOffset,
    const uint32_t firstVertex,
    const uint32_t transformOffset
)
{
    auto& statement = accelerationStructureBuildRangeInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, infoId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(rangeIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(primitiveCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(primitiveOffset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(firstVertex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(transformOffset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildTriangleData(
    const VkAccelerationStructureGeometryTrianglesDataKHR& triangles
)
{
    auto triangleDataId = ++context->currentAccelerationStructureBuildTriangleDataId;
    auto& statement = accelerationStructureBuildTriangleDataInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, triangleDataId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(triangles.vertexFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(triangles.vertexStride)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(triangles.vertexData.deviceAddress))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(triangles.maxVertex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(triangles.indexType)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(triangles.indexData.deviceAddress))
    );
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(triangles.transformData.deviceAddress))
    );
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return triangleDataId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildAABBData(
    const VkAccelerationStructureGeometryAabbsDataKHR& aabbs
)
{
    auto aabbDataId = ++context->currentAccelerationStructureBuildAABBDataId;
    auto& statement = accelerationStructureBuildAabbDataInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, aabbDataId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(aabbs.data.deviceAddress)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(aabbs.stride)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return aabbDataId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureBuildInstanceData(
    const VkAccelerationStructureGeometryInstancesDataKHR& instances
)
{
    auto instanceDataId = ++context->currentAccelerationStructureBuildInstanceDataId;
    auto& statement = accelerationStructureBuildInstanceDataInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, instanceDataId));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instances.data.deviceAddress))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(instances.arrayOfPointers)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return instanceDataId;
}

int64_t VulkanSqlitePreparedStatements::InsertAccelerationStructureCopy(
    const std::optional<format::HandleId> device,
    const std::optional<format::HandleId> deferredOperation,
    const std::optional<format::HandleId> commandBuffer,
    const std::optional<format::HandleId> srcAccelerationStructure,
    const std::optional<format::HandleId> dstAccelerationStructure,
    const std::optional<VkDeviceOrHostAddressConstKHR> srcAddress,
    const std::optional<VkDeviceOrHostAddressKHR> dstAddress,
    const VkCopyAccelerationStructureModeKHR mode,
    const uint64_t apiEventId
)
{
    auto copyId = ++context->currentAccelerationStructureCopyId;
    std::optional<int64_t> deviceId = std::nullopt;
    std::optional<int64_t> frameNumber = std::nullopt;
    if (device.has_value())
    {
        deviceId = context->GetDeviceId(device.value());
        frameNumber = context->currentFrame;
    }
    std::optional<int64_t> deferredOperationId = std::nullopt;
    if (deferredOperation.has_value())
    {
        deferredOperationId = context->GetDeferredOperationId(deferredOperation.value());
    }
    std::optional<int64_t> commandBufferRecordingId = std::nullopt;
    if (commandBuffer.has_value())
    {
        commandBufferRecordingId = context->GetCommandBufferRecordingId(commandBuffer.value());
    }
    std::optional<int64_t> srcAccelerationStructureId = std::nullopt;
    if (srcAccelerationStructure.has_value())
    {
        srcAccelerationStructureId = context->GetAccelerationStructureId(srcAccelerationStructure.value());
    }
    std::optional<int64_t> dstAccelerationStructureId = std::nullopt;
    if (dstAccelerationStructure.has_value())
    {
        dstAccelerationStructureId = context->GetAccelerationStructureId(dstAccelerationStructure.value());
    }
    std::optional<uint64_t> srcDeviceAddress = std::nullopt;
    if (srcAddress.has_value())
    {
        srcDeviceAddress = srcAddress.value().deviceAddress;
    }
    std::optional<uint64_t> dstDeviceAddress = std::nullopt;
    if (dstAddress.has_value())
    {
        dstDeviceAddress = dstAddress.value().deviceAddress;
    }
    auto& statement = accelerationStructureCopyInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, copyId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, deviceId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, frameNumber));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, deferredOperationId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, srcAccelerationStructureId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, dstAccelerationStructureId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, srcDeviceAddress));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, dstDeviceAddress));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(mode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return copyId;
}

int64_t VulkanSqlitePreparedStatements::InsertTransferCommand(
    const uint64_t apiEventId, const std::optional<int64_t> commandBufferRecordingId
)
{
    auto& statement = transferCommandInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, context->currentFrame));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return sqlite3_last_insert_rowid(db);
}

void VulkanSqlitePreparedStatements::UpdateTransferCommandBufferCopy(
    const int64_t instanceId, const std::optional<int64_t> srcBufferId, const std::optional<int64_t> dstBufferId
)
{
    auto& statement = transferCommandBufferCopyUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, srcBufferId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, dstBufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, instanceId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateTransferCommandImageCopy(
    const int64_t instanceId,
    const std::optional<int64_t> srcImageId,
    const std::optional<int64_t> dstImageId,
    const int32_t srcImageLayoutId,
    const int32_t dstImageLayoutId
)
{
    auto& statement = transferCommandImageCopyUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, srcImageId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, dstImageId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 3, srcImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 4, dstImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, instanceId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateTransferCommandBufferToImage(
    const int64_t instanceId,
    const std::optional<int64_t> srcBufferId,
    const std::optional<int64_t> dstImageId,
    const int32_t dstImageLayoutId
)
{
    auto& statement = transferCommandBufferToImageUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, srcBufferId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, dstImageId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 3, dstImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, instanceId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateTransferCommandImageToBuffer(
    const int64_t instanceId,
    const std::optional<int64_t> srcImageId,
    const std::optional<int64_t> dstBufferId,
    const int32_t srcImageLayoutId
)
{
    auto& statement = transferCommandImageToBufferUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, srcImageId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, dstBufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 3, srcImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateTransferCommandBlit(
    const int64_t instanceId,
    const std::optional<int64_t> srcImageId,
    const std::optional<int64_t> dstImageId,
    const int32_t srcImageLayoutId,
    const int32_t dstImageLayoutId,
    const int32_t filter
)
{
    auto& statement = transferCommandBlitUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, srcImageId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, dstImageId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 3, srcImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 4, dstImageLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 5, filter));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertTransferCommandRegionBufferCopy(
    const int64_t transferCommandId,
    const int32_t idx,
    const int64_t srcBufferId,
    const int64_t dstBufferId,
    const VkBufferCopy& region
)
{
    auto& statement = transferCommandRegionBufferCopiesInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(transferCommandId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 2, idx));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(srcBufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(dstBufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(region.srcOffset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(region.dstOffset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(region.size)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertTransferCommandRegionImageCopy(
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
)
{
    auto& statement = transferCommandRegionImageCopiesInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(transferCommandId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 2, idx));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(srcImageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(dstImageId)));

    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 5, srcBaseArrayLayer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 6, srcLayerCount));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 7, srcMipLevel));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 8, dstBaseArrayLayer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 9, dstLayerCount));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 10, dstMipLevel));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 11, srcOffsetX));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 12, srcOffsetY));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 13, srcOffsetZ));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 14, dstOffsetX));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 15, dstOffsetY));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 16, dstOffsetZ));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 17, srcExtentWidth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 18, srcExtentHeight));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 19, srcExtentDepth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 20, dstExtentWidth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 21, dstExtentHeight));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 22, dstExtentDepth));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertTransferCommandRegionBufferImageCopy(
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
)
{
    auto& statement = transferCommandRegionBufferImageCopiesInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(transferCommandId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 2, idx));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(bufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(imageId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 5, isBufferSource));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(bufferOffset)));

    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 7, imageBaseArrayLayer));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 8, imageLayerCount));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 9, imageMipLevel));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 10, imageOffsetX));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 11, imageOffsetY));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 12, imageOffsetZ));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 13, extentWidth));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 14, extentHeight));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int(statement, 15, extentDepth));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::DestroyObject(
    const SqliteStatement& statement, const uint64_t apiEventId, const uint64_t objectId
)
{
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(objectId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertStruct(const std::string_view type)
{
    auto structId = ++context->currentStructId;
    auto& statement = structInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(structId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, type.data(), type.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return structId;
}

int64_t VulkanSqlitePreparedStatements::InsertArray(const std::string_view type)
{
    auto arrayId = ++context->currentArrayId;
    auto& statement = arrayInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(arrayId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, type.data(), type.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return arrayId;
}

int64_t VulkanSqlitePreparedStatements::InsertDebugReportCallback(
    const int64_t callbackHandle, const uint32_t flags, const uint64_t apiEventId
)
{
    auto callbackId = ++context->currentDebugReportCallbackId;
    auto& statement = debugReportCallbackInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(callbackId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(callbackHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return callbackId;
}

void VulkanSqlitePreparedStatements::InsertDebugMessenger(
    const format::HandleId messenger, const uint32_t severity, const uint32_t type, const uint64_t apiEventId
)
{
    auto messengerHandle = ToInt64(messenger);
    auto messengerId = ++context->currentDebugMessengerId;
    context->debugMessengerHandleToId[messengerHandle] = messengerId;
    auto& statement = debugMessengerInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(messengerId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(messengerHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(severity)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugName(
    const std::string_view objectName,
    const int64_t objectHandle,
    const std::optional<int64_t> objectType,
    const std::optional<int64_t> objectMarkerType,
    const format::HandleId device,
    const uint64_t apiEventId
)
{
    auto deviceId = context->GetDeviceId(device);
    auto nameId = ++context->currentDebugNameId;
    auto& statement = debugNameInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(nameId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, objectName.data(), objectName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(objectHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, objectType));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, objectMarkerType));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugTag(
    const uint64_t name,
    const uint64_t size,
    const int64_t objectHandle,
    const std::optional<int64_t> objectType,
    const std::optional<int64_t> objectMarkerType,
    const format::HandleId device,
    const uint64_t apiEventId
)
{
    auto deviceId = context->GetDeviceId(device);
    auto tagId = ++context->currentDebugTagId;
    auto& statement = debugTagInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(tagId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(name)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(objectHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, objectType));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, objectMarkerType));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugLabelQueueBegin(
    const format::HandleId queue,
    const std::string_view name,
    std::span<const float, 4> color,
    const uint64_t apiEventId
)
{
    auto queueId = context->GetQueueId(queue);
    if (!queueId)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "<%" PRIu64 ">- Failed to create queue debug label, no queue found for handle %" PRIu64, apiEventId, queue
        );
        return;
    }
    auto labelId = ++context->currentDebugLabelId;
    context->queueHandleToDebugLabelIdStack[ToInt64(queue)].push(labelId);

    auto& statement = debugLabelQueueBeginInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, name.data(), name.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, color[0]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, color[1]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, color[2]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, color[3]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(*queueId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugLabelQueueInsert(
    const format::HandleId queue,
    const std::string_view name,
    std::span<const float, 4> color,
    const uint64_t apiEventId
)
{
    auto queueId = context->GetQueueId(queue);
    if (!queueId)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "<%" PRIu64 ">- Failed to insert queue debug label, no queue found for handle %" PRIu64, apiEventId, queue
        );
        return;
    }
    auto labelId = ++context->currentDebugLabelId;

    auto& statement = debugLabelQueueInsertInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, name.data(), name.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, color[0]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, color[1]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, color[2]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, color[3]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(*queueId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugLabelCmdBegin(
    const std::string_view name,
    std::span<const float, 4> color,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId,
    const uint64_t apiEventId
)
{
    auto labelId = ++context->currentDebugLabelId;
    context->commandBufferRecordingToDebugLabelIdStack[commandBufferRecordingId].push(labelId);
    auto& statement = debugLabelCmdBeginInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, name.data(), name.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, color[0]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, color[1]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, color[2]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, color[3]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, renderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, renderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 10, dynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugLabelCmdInsert(
    const std::string_view name,
    std::span<const float, 4> color,
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> renderPassRecordingId,
    const std::optional<int64_t> renderSubpassRecordingId,
    const std::optional<int64_t> dynamicRenderPassRecordingId,
    const uint64_t apiEventId
)
{
    auto labelId = ++context->currentDebugLabelId;
    auto& statement = debugLabelCmdInsertInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text64(statement, 2, name.data(), name.size(), SQLITE_STATIC, SQLITE_UTF8));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, color[0]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, color[1]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, color[2]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, color[3]));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, renderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, renderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 10, dynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDebugLabelCmdEndStub(
    const int64_t commandBufferRecordingId,
    const std::optional<int64_t> endRenderPassRecordingId,
    const std::optional<int64_t> endRenderSubpassRecordingId,
    const std::optional<int64_t> endDynamicRenderPassRecordingId,
    const uint64_t apiEventId
)
{
    auto labelId = ++context->currentDebugLabelId;
    context->commandBufferRecordingToDebugLabelIdStack[commandBufferRecordingId].push(labelId);
    auto& statement = debugLabelCmdEndStubInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, endRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, endRenderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, endDynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateDebugLabelEnd(const int64_t labelId, const uint64_t apiEventId)
{
    // UPDATE debugLabels SET endApiEventId = ? WHERE (debugLabels.id = ?)
    auto& statement = debugLabelQueueEndUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::UpdateDebugLabelCmdEnd(
    const int64_t labelId,
    const uint64_t apiEventId,
    const std::optional<int64_t> endRenderPassRecordingId,
    const std::optional<int64_t> endRenderSubpassRecordingId,
    const std::optional<int64_t> endDynamicRenderPassRecordingId
)
{
    // UPDATE debugLabels SET endApiEventId = ?, endRenderPassRecordingId = ?, endRenderSubpassRecordingId = ?,
    //   endDynamicRenderPassRecordingId = ? WHERE (debugLabels.id = ?)
    auto& statement = debugLabelCmdEndUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, endRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, endRenderSubpassRecordingId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, endDynamicRenderPassRecordingId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(labelId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertPhysicalDevice(
    const format::HandleId physicalDevice, const std::optional<int64_t> instanceId, const uint64_t apiEventId
)
{
    auto physicalDeviceHandle = ToInt64(physicalDevice);
    auto physicalDeviceId = ++context->currentPhysicalDeviceId;
    context->physicalDeviceHandleToId[physicalDeviceHandle] = physicalDeviceId;
    auto& statement = physicalDeviceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(physicalDeviceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(physicalDeviceHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, instanceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return physicalDeviceId;
}

int64_t VulkanSqlitePreparedStatements::InsertQueue(
    const int64_t queueHandle,
    const uint32_t flags,
    const uint32_t queueFamilyIndex,
    const uint32_t queueIndex,
    const float priority,
    const format::HandleId device
)
{
    auto deviceId = context->GetDeviceId(device);
    auto queueId = ++context->currentQueueId;
    context->queueHandleToId[queueHandle] = queueId;
    auto& statement = queueInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(queueHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(queueFamilyIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(queueIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, priority));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, deviceId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return queueId;
}

int64_t VulkanSqlitePreparedStatements::InsertQueueSubmit(
    const int64_t queueId,
    const std::optional<int64_t> fenceSyncScopeId,
    const uint64_t frame,
    const uint64_t apiEventId
)
{
    auto queueSubmitId = ++context->currentQueueSubmissionId;
    auto& statement = queueSubmitInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueSubmitId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(queueId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, fenceSyncScopeId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(frame)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return queueSubmitId;
}

int64_t VulkanSqlitePreparedStatements::InsertQueueSubmitBatch(
    const int64_t queueSubmitId,
    const uint64_t batchIndex,
    const std::optional<int64_t> firstDrawTimestamp,
    const std::optional<int64_t> swapBufferTimestamp
)
{
    auto queueSubmitBatchId = ++context->currentQueueSubmissionBatchId;
    auto& statement = queueSubmitBatchInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueSubmitBatchId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(batchIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(queueSubmitId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, firstDrawTimestamp));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, swapBufferTimestamp));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return queueSubmitBatchId;
}

void VulkanSqlitePreparedStatements::InsertQueueSubmitBuffer(
    const int64_t queueSubmitBatchId, const uint64_t bufferIndex, const std::optional<int64_t> commandBufferRecordingId
)
{
    auto& statement = queueSubmitBufferInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueSubmitBatchId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(bufferIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, commandBufferRecordingId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertQueueSubmitSemaphoreWait(
    const int64_t queueSubmitBatchId,
    const uint64_t waitIndex,
    const std::optional<int64_t> waitStage,
    const std::optional<int64_t> value,
    const std::optional<int64_t> semaphoreId
)
{
    auto& statement = queueSubmitSemaphoreWaitInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueSubmitBatchId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(waitIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, waitStage));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, value));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, semaphoreId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertQueueSubmitSemaphoreSignal(
    const int64_t queueSubmitBatchId,
    const uint64_t signalIndex,
    const std::optional<int64_t> value,
    const std::optional<int64_t> semaphoreId
)
{
    auto& statement = queueSubmitSemaphoreSignalInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queueSubmitBatchId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(signalIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, value));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, semaphoreId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertFence(
    const format::HandleId fence, const format::HandleId device, const uint32_t flags, const uint64_t apiEventId
)
{
    auto fenceHandle = ToInt64(fence);
    auto deviceId = context->GetDeviceId(device);
    auto fenceId = ++context->currentFenceId;
    context->fenceHandleToId[fenceHandle] = fenceId;
    auto& statement = fenceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(fenceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(fenceHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return fenceId;
}

void VulkanSqlitePreparedStatements::InsertFenceSyncScope(
    const int64_t fenceHandle, const int64_t fenceId, const uint64_t apiEventId
)
{
    auto fenceSyncScopeId = ++context->currentFenceSyncScopeId;
    context->fenceHandleToSyncScopeId[fenceHandle] = fenceSyncScopeId;
    auto& statement = fenceSyncScopeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(fenceSyncScopeId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(fenceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::ResetFenceSyncScope(const int64_t instanceId, const uint64_t apiEventId)
{
    auto& statement = resetFenceSyncScopeUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::WaitFenceSyncScope(const int64_t instanceId, const uint64_t apiEventId)
{
    auto& statement = waitFenceSyncScopeUpdateStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(instanceId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertSemaphore(
    const format::HandleId semaphore,
    const format::HandleId device,
    const uint32_t semaphoreType,
    const uint64_t initialValue,
    const std::optional<int64_t> handleTypes,
    const uint64_t apiEventId
)
{
    auto semaphoreHandle = ToInt64(semaphore);
    auto deviceId = context->GetDeviceId(device);
    auto semaphoreId = ++context->currentSemaphoreId;
    context->semaphoreHandleToId[semaphoreHandle] = semaphoreId;
    auto& statement = semaphoreInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(semaphoreId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(semaphoreHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(semaphoreType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(initialValue)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, handleTypes));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return semaphoreId;
}

void VulkanSqlitePreparedStatements::InsertSemaphoreSignal(
    const std::optional<int64_t> semaphoreId, const uint64_t value, const uint64_t apiEventId
)
{
    auto& statement = semaphoreSignalInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, semaphoreId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(value)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertSemaphoreWait(
    const format::HandleId semaphore,
    const uint64_t value,
    const uint64_t waitIndex,
    const uint32_t waitFlags,
    const uint64_t timeout,
    const uint64_t apiEventId
)
{
    auto semaphoreId = context->GetSemaphoreId(semaphore);
    auto& statement = semaphoreWaitInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 1, semaphoreId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(value)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(waitIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(waitFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(timeout)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertEvent(
    const format::HandleId event, const format::HandleId device, const uint32_t flags, const uint64_t apiEventId
)
{
    auto eventHandle = ToInt64(event);
    auto deviceId = context->GetDeviceId(device);
    auto eventId = ++context->currentEventId;
    context->eventHandleToId[eventHandle] = eventId;
    auto& statement = eventInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(eventId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(eventHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertQueryPool(
    const format::HandleId queryPool,
    const format::HandleId device,
    const uint32_t flags,
    const uint32_t queryType,
    const uint32_t queryCount,
    const uint32_t pipelineStatistics,
    const uint64_t apiEventId
)
{
    auto queryPoolHandle = ToInt64(queryPool);
    auto deviceId = context->GetDeviceId(device);
    auto queryPoolId = ++context->currentQueryPoolId;
    context->queryPoolHandleToId[queryPoolHandle] = queryPoolId;
    auto& statement = queryPoolInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(queryPoolId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(queryPoolHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(queryType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(queryCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(pipelineStatistics)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertShaderObject(
    const format::HandleId shader,
    const format::HandleId device,
    const uint32_t flags,
    const uint32_t stage,
    const uint32_t nextStage,
    const uint32_t codeType,
    const uint64_t codeSize,
    const std::string_view entryPointName,
    const uint64_t apiEventId
)
{
    auto shaderHandle = ToInt64(shader);
    auto deviceId = context->GetDeviceId(device);
    auto shaderObjectId = ++context->currentShaderObjectId;
    context->shaderObjectHandleToId[shaderHandle] = shaderObjectId;
    auto& statement = shaderObjectInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(shaderObjectId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(shaderHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(stage)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(nextStage)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(codeType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(codeSize)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 9, entryPointName.data(), entryPointName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return shaderObjectId;
}

void VulkanSqlitePreparedStatements::InsertShaderObjectDescriptorSetLayout(
    const int64_t shaderObjectId, const uint64_t setIndex, const std::optional<int64_t> layoutId
)
{
    auto& statement = shaderObjectDescriptorSetLayoutInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(shaderObjectId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(setIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, layoutId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertShaderObjectPushConstantRange(
    const int64_t shaderObjectId,
    const uint64_t rangeIndex,
    const uint32_t stageFlags,
    const uint32_t offset,
    const uint32_t size
)
{
    auto& statement = shaderObjectPushConstantRangeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(shaderObjectId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(rangeIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stageFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertShaderModule(
    const format::HandleId shaderModule,
    const format::HandleId device,
    const uint64_t codeSize,
    const uint64_t apiEventId
)
{
    auto moduleHandle = ToInt64(shaderModule);
    auto deviceId = context->GetDeviceId(device);
    auto shaderModuleId = ++context->currentShaderModuleId;
    context->shaderModuleHandleToId[moduleHandle] = shaderModuleId;
    auto& statement = shaderModuleInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(shaderModuleId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(moduleHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(codeSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertShaderModuleWithStringHandle(
    const std::string_view moduleHandle,
    const std::optional<int64_t> deviceId,
    const uint64_t codeSize,
    const uint64_t apiEventId
)
{
    auto shaderModuleId = ++context->currentShaderModuleId;
    auto& statement = shaderModuleWithStringHandleInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(shaderModuleId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 2, moduleHandle.data(), moduleHandle.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(codeSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return shaderModuleId;
}

void VulkanSqlitePreparedStatements::InsertPipelineStage(
    const int64_t pipelineId,
    const uint64_t stageIndex,
    const uint32_t flags,
    const uint32_t stage,
    const std::optional<int64_t> shaderModule,
    const std::string_view entryPointName,
    const std::optional<int64_t> feedbackFlags,
    const std::optional<int64_t> createDuration
)
{
    auto& statement = pipelineStageInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(stageIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(stage)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, shaderModule));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_text64(statement, 6, entryPointName.data(), entryPointName.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, createDuration));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertValidationCache(
    const format::HandleId validationCache,
    const format::HandleId device,
    const uint64_t initialDataSize,
    const uint64_t apiEventId
)
{
    auto cacheHandle = ToInt64(validationCache);
    auto deviceId = context->GetDeviceId(device);
    auto cacheId = ++context->currentValidationCacheId;
    context->validationCacheHandleToId[cacheHandle] = cacheId;
    auto& statement = validationCacheInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cacheId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(cacheHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(initialDataSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPipelineCache(
    const format::HandleId pipelineCache,
    const format::HandleId device,
    const uint32_t flags,
    const uint64_t initialDataSize,
    const uint64_t apiEventId
)
{
    auto cacheHandle = ToInt64(pipelineCache);
    auto deviceId = context->GetDeviceId(device);
    auto cacheId = ++context->currentPipelineCacheId;
    context->pipelineCacheHandleToId[cacheHandle] = cacheId;
    auto& statement = pipelineCacheInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cacheId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(cacheHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(initialDataSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineLayout(
    const int64_t layoutHandle, const std::optional<int64_t> deviceId, const uint32_t flags, const uint64_t apiEventId
)
{
    auto layoutId = ++context->currentPipelineLayoutId;
    context->pipelineLayoutHandleToId[layoutHandle] = layoutId;
    auto& statement = pipelineLayoutInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(layoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(layoutHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return layoutId;
}

void VulkanSqlitePreparedStatements::InsertPipelineDescriptorSetLayout(
    const int64_t pipelineLayoutId, const uint64_t setIndex, const std::optional<int64_t> layoutId
)
{
    auto& statement = pipelineDescriptorSetLayoutInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineLayoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(setIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, layoutId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPipelinePushConstantRange(
    const int64_t pipelineLayoutId,
    const uint64_t rangeIndex,
    const uint32_t stageFlags,
    const uint32_t offset,
    const uint32_t size
)
{
    auto& statement = pipelinePushConstantRangeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineLayoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(rangeIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stageFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDescriptorSetLayout(
    const int64_t layoutHandle, const std::optional<int64_t> deviceId, const uint32_t flags, const uint64_t apiEventId
)
{
    auto layoutId = ++context->currentDescriptorSetLayoutId;
    context->descriptorSetLayoutHandleToId[layoutHandle] = layoutId;
    auto& statement = descriptorSetLayoutInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(layoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(layoutHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return layoutId;
}

void VulkanSqlitePreparedStatements::InsertDescriptorSetLayoutBinding(
    const int64_t layoutId,
    const uint32_t binding,
    const uint32_t descriptorType,
    const uint32_t descriptorCount,
    const uint32_t stageFlags,
    const uint32_t bindingFlags
)
{
    auto& statement = descriptorSetLayoutBindingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(layoutId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(descriptorType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(descriptorCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(stageFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(bindingFlags)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDescriptorPool(
    const format::HandleId pool,
    const format::HandleId device,
    const uint32_t flags,
    const uint32_t maxSets,
    const uint64_t apiEventId
)
{
    auto poolHandle = ToInt64(pool);
    auto deviceId = context->GetDeviceId(device);
    auto poolId = ++context->currentDescriptorPoolId;
    context->descriptorPoolHandleToId[poolHandle] = poolId;
    auto& statement = descriptorPoolInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(poolId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(poolHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(maxSets)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDescriptorSet(
    const int64_t setHandle,
    const std::optional<int64_t> poolId,
    const std::optional<int64_t> layoutId,
    const uint64_t apiEventId
)
{
    auto setId = ++context->currentDescriptorSetId;
    context->descriptorSetHandleToInfo[setHandle] = { .descriptorSetId = setId, .layoutId = layoutId.value_or(0) };
    auto& statement = descriptorSetInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(setId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(setHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, poolId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, layoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return setId;
}

int64_t VulkanSqlitePreparedStatements::InsertVertexInputState(const int64_t pipelineId)
{
    auto stateId = ++context->currentVertexInputStateId;
    auto& statement = vertexInputStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

void VulkanSqlitePreparedStatements::InsertVertexInputStateBindingDescription(
    const int64_t stateId,
    const uint32_t binding,
    const uint32_t stride,
    const uint32_t inputRate,
    const uint32_t divisor
)
{
    auto& statement = vertexInputStateBindingDescriptionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(stride)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(inputRate)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(divisor)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertVertexInputStateBindingDescriptionFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = vertexInputStateBindingDescriptionFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertVertexInputStateAttributeDescription(
    const int64_t stateId, const uint32_t location, const uint32_t binding, const uint32_t format, const uint32_t offset
)
{
    auto& statement = vertexInputStateAttributeDescriptionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(location)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertVertexInputStateAttributeDescriptionFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = vertexInputStateAttributeDescriptionFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertInputAssemblyState(
    const int64_t pipelineId, const uint32_t topology, const uint32_t primitiveRestartEnable
)
{
    auto stateId = ++context->currentInputAssemblyStateId;
    auto& statement = inputAssemblyStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(topology)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(primitiveRestartEnable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertInputAssemblyStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentInputAssemblyStateId;
    auto& statement = inputAssemblyStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertTessellationState(
    const int64_t pipelineId, const uint32_t patchControlPoints
)
{
    auto stateId = ++context->currentTessellationStateId;
    auto& statement = tessellationStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(patchControlPoints)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertTessellationStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentTessellationStateId;
    auto& statement = tessellationStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertViewportState(
    const int64_t pipelineId,
    const uint32_t depthClipNegativeToOne,
    const uint32_t depthClampMode,
    const std::optional<float> minDepthClamp,
    const std::optional<float> maxDepthClamp
)
{
    auto stateId = ++context->currentViewportStateId;
    auto& statement = viewportStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(depthClipNegativeToOne)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(depthClampMode)));
    GFXRECON_SQLITE_CHECK(
        db,
        BindOptDouble(
            statement, 5, minDepthClamp.has_value() ? std::optional<double>(minDepthClamp.value()) : std::nullopt
        )
    );
    GFXRECON_SQLITE_CHECK(
        db,
        BindOptDouble(
            statement, 6, maxDepthClamp.has_value() ? std::optional<double>(maxDepthClamp.value()) : std::nullopt
        )
    );
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertViewportStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentViewportStateId;
    auto& statement = viewportStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

void VulkanSqlitePreparedStatements::InsertViewportStateViewport(
    const int64_t stateId,
    const uint64_t viewportIndex,
    const float x,
    const float y,
    const float width,
    const float height,
    const float minDepth,
    const float maxDepth
)
{
    auto& statement = viewportStateViewportInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(viewportIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 3, static_cast<double>(x)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 4, static_cast<double>(y)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, static_cast<double>(width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, static_cast<double>(height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 7, static_cast<double>(minDepth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 8, static_cast<double>(maxDepth)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertViewportStateViewportFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = viewportStateViewportFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertViewportStateScissor(
    const int64_t stateId,
    const uint64_t scissorIndex,
    const int32_t x,
    const int32_t y,
    const uint32_t width,
    const uint32_t height
)
{
    auto& statement = viewportStateScissorInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(scissorIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(x)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(y)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(height)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertViewportStateScissorFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = viewportStateScissorFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertRasterizationState(
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
)
{
    auto stateId = ++context->currentRasterizationStateId;
    auto& statement = rasterizationStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(depthClampEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(rasterizerDiscardEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(polygonMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(cullMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(frontFace)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(depthBiasEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 9, static_cast<double>(depthBiasConstantFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 10, static_cast<double>(depthBiasClamp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 11, static_cast<double>(depthBiasSlopeFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 12, static_cast<double>(lineWidth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(lineRasterizationMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(stippledLineEnable)));
    GFXRECON_SQLITE_CHECK(
        db,
        BindOptInt64(
            statement,
            15,
            lineStippleFactor.has_value() ? std::optional<int64_t>(lineStippleFactor.value()) : std::nullopt
        )
    );
    GFXRECON_SQLITE_CHECK(
        db,
        BindOptInt64(
            statement,
            16,
            lineStipplePattern.has_value() ? std::optional<int64_t>(lineStipplePattern.value()) : std::nullopt
        )
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 17, static_cast<sqlite_int64>(provokingVertexMode)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 18, static_cast<sqlite_int64>(rasterizationStream)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertRasterizationStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentRasterizationStateId;
    auto& statement = rasterizationStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertDepthStencilState(
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
)
{
    auto stateId = ++context->currentDepthStencilStateId;
    auto& statement = depthStencilStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(depthTestEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(depthWriteEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(depthCompareOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(depthBoundsTestEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(stencilTestEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(frontFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(frontPassOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(frontDepthFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(frontCompareOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(frontCompareMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(frontWriteMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(frontReference)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 16, static_cast<sqlite_int64>(backFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 17, static_cast<sqlite_int64>(backPassOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 18, static_cast<sqlite_int64>(backDepthFailOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 19, static_cast<sqlite_int64>(backCompareOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 20, static_cast<sqlite_int64>(backCompareMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 21, static_cast<sqlite_int64>(backWriteMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 22, static_cast<sqlite_int64>(backReference)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 23, static_cast<double>(minDepthBounds)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 24, static_cast<double>(maxDepthBounds)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertDepthStencilStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentDepthStencilStateId;
    auto& statement = depthStencilStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertColorBlendState(
    const int64_t pipelineId,
    const uint32_t flags,
    const uint32_t logicOpEnable,
    const std::optional<int64_t> logicOp,
    std::span<const float, 4> blendConstants
)
{
    auto stateId = ++context->currentColorBlendStateId;
    auto& statement = colorBlendStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(logicOpEnable)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, logicOp));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 6, static_cast<double>(blendConstants[0])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 7, static_cast<double>(blendConstants[1])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 8, static_cast<double>(blendConstants[2])));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 9, static_cast<double>(blendConstants[3])));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertColorBlendStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentColorBlendStateId;
    auto& statement = colorBlendStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

void VulkanSqlitePreparedStatements::InsertColorBlendStateAttachmentState(
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
)
{
    auto& statement = colorBlendStateAttachmentStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(colorBlendStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(blendEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(srcColorBlendFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(dstColorBlendFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(colorBlendOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(srcAlphaBlendFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(dstAlphaBlendFactor)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(alphaBlendOp)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(colorWriteMask)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(colorWriteEnable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertColorBlendStateAttachmentStateFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = colorBlendStateAttachmentStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPipelineDynamicState(const int64_t pipelineId, const uint32_t dynamicState)
{
    auto& statement = pipelineDynamicStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(dynamicState)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineGraphics(
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
)
{
    auto pipelineId = ++context->currentPipelineId;
    context->pipelineHandleToId[pipelineHandle] = pipelineId;
    auto& statement = pipelineGraphicsInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, basePipelineId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, renderPass));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, viewMask));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, depthAttachmentFormat));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 10, stencilAttachmentFormat));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 11, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 12, createDuration));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return pipelineId;
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineCompute(
    const int64_t pipelineHandle,
    const std::optional<int64_t> deviceId,
    const uint32_t flags,
    const std::optional<int64_t> basePipelineId,
    const std::optional<int64_t> pipelineLayout,
    const std::optional<int64_t> feedbackFlags,
    const std::optional<int64_t> createDuration,
    const uint64_t apiEventId
)
{
    auto pipelineId = ++context->currentPipelineId;
    context->pipelineHandleToId[pipelineHandle] = pipelineId;
    auto& statement = pipelineComputeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, basePipelineId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, createDuration));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return pipelineId;
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineRayTracingNV(
    const int64_t pipelineHandle,
    const std::optional<int64_t> deviceId,
    const uint32_t flags,
    const std::optional<int64_t> basePipelineId,
    const std::optional<int64_t> pipelineLayout,
    const std::optional<int64_t> feedbackFlags,
    const std::optional<int64_t> createDuration,
    const uint64_t apiEventId
)
{
    auto pipelineId = ++context->currentPipelineId;
    context->pipelineHandleToId[pipelineHandle] = pipelineId;
    auto& statement = pipelineRayTracingNVInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, basePipelineId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, createDuration));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return pipelineId;
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineRayTracing(
    const int64_t pipelineHandle,
    const std::optional<int64_t> deviceId,
    const uint32_t flags,
    const std::optional<int64_t> basePipelineId,
    const std::optional<int64_t> pipelineLayout,
    const std::optional<int64_t> feedbackFlags,
    const std::optional<int64_t> createDuration,
    const uint64_t apiEventId
)
{
    auto pipelineId = ++context->currentPipelineId;
    context->pipelineHandleToId[pipelineHandle] = pipelineId;
    auto& statement = pipelineRayTracingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, basePipelineId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, createDuration));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return pipelineId;
}

void VulkanSqlitePreparedStatements::InsertPipelineColorAttachmentFormat(
    const int64_t pipelineId, const uint64_t attachmentIndex, const uint32_t format
)
{
    auto& statement = pipelineColorAttachmentFormatInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPipelineLibrary(const int64_t pipelineId, const int64_t libraryPipelineId)
{
    auto& statement = pipelineLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(libraryPipelineId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertGraphicsPipelineInfo(
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
)
{
    auto graphicsPipelineInfoId = ++context->currentGraphicsPipelineId;
    auto& statement = graphicsPipelineInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(graphicsPipelineInfoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(libraryFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, inputAssemblyStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, vertexInputStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, tessellationStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, viewportStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 9, rasterizationStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 10, multisampleStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 11, depthStencilStateId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 12, colorBlendStateId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertComputePipelineInfo(const int64_t pipelineId)
{
    auto computePipelineInfoId = ++context->currentComputePipelineId;
    auto& statement = computePipelineInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(computePipelineInfoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertPipelineDataGraph(
    const int64_t pipelineHandle,
    const std::optional<int64_t> deviceId,
    const uint64_t flags,
    const std::optional<int64_t> basePipeline,
    const std::optional<int64_t> pipelineLayout,
    const std::optional<int64_t> feedbackFlags,
    const std::optional<int64_t> createDuration,
    const uint64_t apiEventId
)
{
    auto pipelineId = ++context->currentPipelineId;
    context->pipelineHandleToId[pipelineHandle] = pipelineId;
    auto& statement = pipelineDataGraphInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, basePipeline));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineLayout));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, feedbackFlags));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 8, createDuration));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return pipelineId;
}

int64_t VulkanSqlitePreparedStatements::InsertDataGraphPipelineInfo(const int64_t pipelineId)
{
    auto infoId = ++context->currentDataGraphPipelineInfoId;
    auto& statement = dataGraphPipelineInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(infoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return infoId;
}

void VulkanSqlitePreparedStatements::InsertDataGraphPipelineResourceInfo(
    const int64_t infoId,
    const uint32_t idx,
    const uint32_t descriptorSet,
    const uint32_t binding,
    const uint32_t arrayElement
)
{
    auto& statement = dataGraphPipelineResourceInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(infoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(idx)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(descriptorSet)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(binding)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(arrayElement)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDataGraphPipelineSession(
    const int64_t sessionHandle,
    const std::optional<int64_t> deviceId,
    const uint64_t flags,
    const int64_t pipelineId,
    const uint64_t apiEventId
)
{
    auto sessionId = ++context->currentDataGraphPipelineSessionId;
    context->dataGraphPipelineSessionHandleToId[sessionHandle] = sessionId;
    auto& statement = dataGraphPipelineSessionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(sessionId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sessionHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return sessionId;
}

int64_t VulkanSqlitePreparedStatements::InsertCmdDataGraphDispatchRecording(
    const uint64_t apiEventId, const std::optional<int64_t> sessionId, const int64_t commandBufferRecordingId
)
{
    auto stateGroupId = InsertStateGroup(commandBufferRecordingId);
    auto recordingId = ++context->currentCmdDataGraphDispatchRecordingId;
    auto& statement = cmdDataGraphDispatchRecordingInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(recordingId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, sessionId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(stateGroupId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(commandBufferRecordingId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return recordingId;
}

void VulkanSqlitePreparedStatements::InsertCmdDataGraphDispatchRecordingInfo(
    const int64_t cmdDataGraphDispatchRecordingId, const uint64_t flags
)
{
    auto& statement = cmdDataGraphDispatchRecordingInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(cmdDataGraphDispatchRecordingId))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertRaytracingPipelineInfo(
    const int64_t pipelineId,
    const uint32_t maxRecursionDepth,
    const std::optional<int64_t> maxPipelineRayPayloadSize,
    const std::optional<int64_t> maxPipelineRayHitAttributeSize
)
{
    auto raytracingPipelineId = ++context->currentRaytracingPipelineId;
    auto& statement = raytracingPipelineInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(raytracingPipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(maxRecursionDepth)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, maxPipelineRayPayloadSize));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, maxPipelineRayHitAttributeSize));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return raytracingPipelineId;
}

void VulkanSqlitePreparedStatements::InsertRaytracingShaderGroup(
    const int64_t raytracingPipelineInfoId,
    const int64_t pipelineId,
    const uint32_t groupType,
    const uint32_t generalShaderIndex,
    const uint32_t closestHitShaderIndex,
    const uint32_t anyHitShaderIndex,
    const uint32_t intersectionShaderIndex
)
{
    auto& statement = raytracingShaderGroupInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(raytracingPipelineInfoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(groupType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(generalShaderIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(closestHitShaderIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(anyHitShaderIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(intersectionShaderIndex)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertDisplay(
    const int64_t displayHandle, const int64_t physicalDeviceId, const uint64_t apiEventId
)
{
    auto displayId = ++context->currentDisplayId;
    context->displayHandleToId[displayHandle] = displayId;
    auto& statement = displayInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(displayId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(displayHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(physicalDeviceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return displayId;
}

void VulkanSqlitePreparedStatements::InsertDisplayMode(
    const format::HandleId mode,
    const int64_t physicalDeviceId,
    const int64_t displayId,
    const uint32_t visibleRegionWidth,
    const uint32_t visibleRegionHeight,
    const uint32_t refreshRate,
    const uint64_t apiEventId
)
{
    auto modeHandle = ToInt64(mode);
    auto modeId = ++context->currentDisplayModeId;
    context->displayModeHandleToId[modeHandle] = modeId;
    auto& statement = displayModeInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(modeId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(modeHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(physicalDeviceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(displayId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(visibleRegionWidth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(visibleRegionHeight)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(refreshRate)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertAcquireNextImage(
    const std::optional<int64_t> swapchainId,
    const std::optional<int64_t> fenceSyncScopeId,
    const std::optional<int64_t> semaphoreId,
    const uint64_t frame,
    const uint64_t apiEventId
)
{
    auto acquireId = ++context->currentAcquireNextImageId;
    auto& statement = acquireNextImageInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(acquireId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, swapchainId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, fenceSyncScopeId));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, semaphoreId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(frame)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertFramebuffer(
    const format::HandleId framebuffer,
    const format::HandleId device,
    const uint32_t flags,
    const std::optional<int64_t> renderPassId,
    const uint32_t width,
    const uint32_t height,
    const uint32_t layers,
    const uint64_t apiEventId
)
{
    auto framebufferHandle = ToInt64(framebuffer);
    auto deviceId = context->GetDeviceId(device);
    auto framebufferId = ++context->currentFramebufferId;
    context->framebufferHandleToId[framebufferHandle] = framebufferId;
    auto& statement = framebufferInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(framebufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(framebufferHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, renderPassId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(layers)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return framebufferId;
}

int64_t VulkanSqlitePreparedStatements::InsertFramebufferAttachmentInfo(
    const uint32_t flags, const uint32_t width, const uint32_t height, const uint32_t layerCount, const uint32_t usage
)
{
    auto attachmentInfoId = ++context->currentFramebufferAttachmentInfoId;
    auto& statement = framebufferAttachmentInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(attachmentInfoId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(layerCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(usage)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return attachmentInfoId;
}

void VulkanSqlitePreparedStatements::InsertFramebufferAttachmentWithInfo(
    const int64_t framebufferId, const uint64_t attachmentIndex, const int64_t attachmentInfoId
)
{
    auto& statement = framebufferAttachmentWithInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(framebufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(attachmentInfoId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertFramebufferAttachmentWithImageView(
    const int64_t framebufferId, const uint64_t attachmentIndex, const std::optional<int64_t> imageViewId
)
{
    auto& statement = framebufferAttachmentWithImageViewInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(framebufferId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(attachmentIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, imageViewId));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertSamplerYcbcrConversion(
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
)
{
    auto conversionHandle = ToInt64(conversion);
    auto deviceId = context->GetDeviceId(device);
    auto conversionId = ++context->currentSamplerYcbcrConversionId;
    context->samplerYcbcrConversionHandleToId[conversionHandle] = conversionId;
    auto& statement = samplerYcbcrConversionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(conversionId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(conversionHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(format)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(ycbcrModel)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(ycbcrRange)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(components.r)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(components.g)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(components.b)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(components.a)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(xChromaOffset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(yChromaOffset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(chromaFilter)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(forceExplicitReconstruction))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPrivateDataSlot(
    const format::HandleId slot, const format::HandleId device, const uint64_t apiEventId
)
{
    auto slotHandle = ToInt64(slot);
    auto deviceId = context->GetDeviceId(device);
    auto slotId = ++context->currentPrivateDataSlotId;
    context->privateDataSlotHandleToId[slotHandle] = slotId;
    auto& statement = privateDataSlotInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(slotId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(slotHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertDeferredOperation(
    const format::HandleId operation, const format::HandleId device, const uint64_t apiEventId
)
{
    auto operationHandle = ToInt64(operation);
    auto deviceId = context->GetDeviceId(device);
    auto operationId = ++context->currentDeferredOperationId;
    context->deferredOperationHandleToId[operationHandle] = operationId;
    auto& statement = deferredOperationInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(operationId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(operationHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertPipelineBinary(
    const format::HandleId binary,
    const format::HandleId device,
    const uint32_t keySize,
    const uint64_t dataSize,
    const std::optional<int64_t> pipelineId,
    const uint64_t apiEventId
)
{
    auto binaryHandle = ToInt64(binary);
    auto deviceId = context->GetDeviceId(device);
    auto binaryId = ++context->currentPipelineBinaryId;
    context->pipelineBinaryHandleToId[binaryHandle] = binaryId;
    auto& statement = pipelineBinaryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(binaryId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(binaryHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(keySize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(dataSize)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 6, pipelineId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertVideoSession(
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
)
{
    auto videoSessionHandle = ToInt64(videoSession);
    auto deviceId = context->GetDeviceId(device);
    auto videoSessionId = ++context->currentVideoSessionId;
    context->videoSessionHandleToId[videoSessionHandle] = videoSessionId;
    auto& statement = videoSessionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(videoSessionId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(videoSessionHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(queueFamilyIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(videoCodecOperation)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(chromaSubsampling)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(lumaBitDepth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(chromaBitDepth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(pictureFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(maxCodedWidth)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(maxCodedHeight)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(referencePictureFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 14, static_cast<sqlite_int64>(maxDpbSlots)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 15, static_cast<sqlite_int64>(maxActiveReferencePictures)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_text(statement, 16, stdHeaderVersionName, -1, SQLITE_TRANSIENT));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 17, static_cast<sqlite_int64>(stdHeaderVersionSpecVersion))
    );
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 18, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertVideoSessionParameters(
    const format::HandleId videoSessionParameters,
    const format::HandleId device,
    const uint32_t flags,
    const std::optional<int64_t> videoSessionParametersTemplateId,
    const int64_t videoSessionId,
    const uint64_t apiEventId
)
{
    auto videoSessionParametersHandle = ToInt64(videoSessionParameters);
    auto deviceId = context->GetDeviceId(device);
    auto videoSessionParametersId = ++context->currentVideoSessionParametersId;
    context->videoSessionParametersHandleToId[videoSessionParametersHandle] = videoSessionParametersId;
    auto& statement = videoSessionParametersInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(videoSessionParametersId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(videoSessionParametersHandle))
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, videoSessionParametersTemplateId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(videoSessionId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertIndirectCommandsLayout(
    const format::HandleId indirectCommandsLayout,
    const format::HandleId device,
    const uint32_t flags,
    const uint32_t shaderStages,
    const uint32_t indirectStride,
    const std::optional<int64_t> pipelineLayoutId,
    const uint32_t tokenCount,
    const uint64_t apiEventId
)
{
    auto indirectCommandsLayoutHandle = ToInt64(indirectCommandsLayout);
    auto deviceId = context->GetDeviceId(device);
    auto indirectCommandsLayoutId = ++context->currentIndirectCommandsLayoutId;
    context->indirectCommandsLayoutHandleToId[indirectCommandsLayoutHandle] = indirectCommandsLayoutId;
    auto& statement = indirectCommandsLayoutInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(indirectCommandsLayoutId)));
    GFXRECON_SQLITE_CHECK(
        db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(indirectCommandsLayoutHandle))
    );
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(shaderStages)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(indirectStride)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 7, pipelineLayoutId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(tokenCount)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertMicromap(
    const format::HandleId micromap,
    const format::HandleId device,
    const uint32_t createFlags,
    const std::optional<int64_t> bufferId,
    const uint64_t offset,
    const uint64_t size,
    const uint32_t type,
    const uint64_t deviceAddress,
    const uint64_t apiEventId
)
{
    auto micromapHandle = ToInt64(micromap);
    auto deviceId = context->GetDeviceId(device);
    auto micromapId = ++context->currentMicromapId;
    context->micromapHandleToId[micromapHandle] = micromapId;
    auto& statement = micromapInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(micromapId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(micromapHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(createFlags)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 5, bufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(type)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(deviceAddress)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertOpticalFlowSession(
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
)
{
    auto opticalFlowSessionHandle = ToInt64(opticalFlowSession);
    auto deviceId = context->GetDeviceId(device);
    auto opticalFlowSessionId = ++context->currentOpticalFlowSessionId;
    context->opticalFlowSessionHandleToId[opticalFlowSessionHandle] = opticalFlowSessionId;
    auto& statement = opticalFlowSessionInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(opticalFlowSessionId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(opticalFlowSessionHandle)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 3, deviceId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(width)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(height)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(imageFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(flowVectorFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 8, static_cast<sqlite_int64>(costFormat)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 9, static_cast<sqlite_int64>(outputGridSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 10, static_cast<sqlite_int64>(hintGridSize)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 11, static_cast<sqlite_int64>(performanceLevel)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 12, static_cast<sqlite_int64>(flags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 13, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

int64_t VulkanSqlitePreparedStatements::InsertSurface(
    const int64_t surfaceHandle, const uint32_t createInfoType, const uint64_t apiEventId
)
{
    auto surfaceId = ++context->currentSurfaceId;
    context->surfaceHandleToId[surfaceHandle] = surfaceId;
    auto& statement = surfaceInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(surfaceId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(surfaceHandle)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(createInfoType)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(apiEventId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return surfaceId;
}

int64_t VulkanSqlitePreparedStatements::InsertCommandBufferInheritanceInfo(
    const std::optional<int64_t> renderPassId,
    const uint32_t subpassIndex,
    const std::optional<int64_t> framebufferId,
    const uint32_t occlusionQueryEnable,
    const uint32_t queryFlags,
    const uint32_t pipelineStatisticsFlags
)
{
    auto infoId = ++context->currentCommandBufferInheritanceInfoId;
    auto& statement = commandBufferInheritanceInfoInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(infoId)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 2, renderPassId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(subpassIndex)));
    GFXRECON_SQLITE_CHECK(db, BindOptInt64(statement, 4, framebufferId));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 5, static_cast<sqlite_int64>(occlusionQueryEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(queryFlags)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(pipelineStatisticsFlags)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return infoId;
}

int64_t VulkanSqlitePreparedStatements::InsertMultisampleState(
    const int64_t pipelineId,
    const uint32_t rasterizationSamples,
    const uint32_t sampleShadingEnable,
    const float minSampleShading,
    const uint32_t alphaToCoverageEnable,
    const uint32_t alphaToOneEnable
)
{
    auto stateId = ++context->currentMultisampleStateId;
    auto& statement = multisampleStateInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(rasterizationSamples)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(sampleShadingEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_double(statement, 5, static_cast<double>(minSampleShading)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 6, static_cast<sqlite_int64>(alphaToCoverageEnable)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 7, static_cast<sqlite_int64>(alphaToOneEnable)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

int64_t VulkanSqlitePreparedStatements::InsertMultisampleStateFromLibrary(
    const int64_t pipelineId, const int64_t sourceStateId
)
{
    auto stateId = ++context->currentMultisampleStateId;
    auto& statement = multisampleStateFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(pipelineId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
    return stateId;
}

void VulkanSqlitePreparedStatements::InsertMultisampleStateSampleMask(
    const int64_t stateId, const uint64_t maskIndex, const uint32_t sampleMask
)
{
    auto& statement = multisampleStateSampleMaskInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(stateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(maskIndex)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(sampleMask)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

void VulkanSqlitePreparedStatements::InsertMultisampleStateSampleMasksFromLibrary(
    const int64_t newStateId, const int64_t sourceStateId
)
{
    auto& statement = multisampleStateSampleMasksFromLibraryInsertStatement;
    GFXRECON_SQLITE_CHECK(db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(newStateId)));
    GFXRECON_SQLITE_CHECK(db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(sourceStateId)));
    GFXRECON_SQLITE_CHECK_DONE(db, sqlite3_step(statement));
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
