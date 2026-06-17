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
#include "vulkan_sqlite_consumer_tables.h"

#include "sqlite_utils.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

static void CreateDebugTables(sqlite3* db)
{
    // additional database initialization code here or app specific variable initialization
    ExecSQL(
        db,
        "CREATE TABLE debugNames("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   objectName TEXT,"
        "   objectHandle INT,"
        "   objectType INT,"       // only used by VK_EXT_debug_utils
        "   objectMarkerType INT," // only used by VK_EXT_debug_markers
        "   deviceId INT,"
        "   apiEventId INT,"
        "   FOREIGN KEY(objectType) REFERENCES VkObjectType(value),"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE debugTags("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   name INT,"
        "   size INT,"
        "   objectHandle INT,"
        "   objectType INT,"       // only used by VK_EXT_debug_utils
        "   objectMarkerType INT," // only used by VK_EXT_debug_markers
        "   deviceId INT,"
        "   apiEventId INT,"
        "   FOREIGN KEY(objectType) REFERENCES VkObjectType(value),"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE debugLabels("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   name TEXT,"
        "   r REAL,"
        "   g REAL,"
        "   b REAL,"
        "   a REAL,"
        "   commandBufferRecordingId INT,"
        "   beginRenderPassRecordingId INT,"
        "   beginRenderSubpassRecordingId INT,"
        "   beginDynamicRenderPassRecordingId INT,"
        "   endRenderPassRecordingId INT,"
        "   endRenderSubpassRecordingId INT,"
        "   endDynamicRenderPassRecordingId INT,"
        "   queueId INT,"
        "   beginApiEventId INT,"
        "   endApiEventId INT,"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(beginRenderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(beginRenderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(beginDynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id),"
        "   FOREIGN KEY(endRenderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(endRenderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(endDynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id),"
        "   FOREIGN KEY(queueId) REFERENCES queues(id),"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queueDebugLabels("
        "   apiEventId INTEGER NOT NULL,"
        "   label INTEGER  NOT NULL,"
        "   queueId INTEGER NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(label) REFERENCES debugLabels(id),"
        "   FOREIGN KEY(queueId) REFERENCES queues(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE debugReportCallbacks("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE debugMessengers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   severity INT NOT NULL,"
        "   type INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateVulkanInstanceTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE instanceEnabledLayers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   instanceId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id)) STRICT;"
    );
    
    ExecSQL(
        db,
        "CREATE TABLE instanceEnabledLayerSettings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   instanceEnabledLayerId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   type INT NOT NULL,"
        "   FOREIGN KEY(instanceEnabledLayerId) REFERENCES instanceEnabledLayers(id),"
        "   FOREIGN KEY(type) REFERENCES VkLayerSettingTypeEXT(value)) STRICT;"
    );
    
    ExecSQL(
        db,
        "CREATE TABLE instanceEnabledLayerSettingValues("
        "   instanceEnabledLayerSettingId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   value TEXT NOT NULL,"
        "   FOREIGN KEY(instanceEnabledLayerSettingId) REFERENCES instanceEnabledLayerSettings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE instanceEnabledExtensions("
        "   instanceId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id)) STRICT;"
    );
    
    ExecSQL(
        db,
        "CREATE TABLE instanceValidationEnabledFeatures("
        "   instanceId INT NOT NULL,"
        "   feature INT NOT NULL,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id),"
        "   FOREIGN KEY(feature) REFERENCES VkValidationFeatureEnableEXT) STRICT;"
    );
    
    ExecSQL(
        db,
        "CREATE TABLE instanceValidationDisabledFeatures("
        "   instanceId INT NOT NULL,"
        "   feature INT NOT NULL,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id),"
        "   FOREIGN KEY(feature) REFERENCES VkValidationFeatureDisableEXT) STRICT;"
    );
    
    ExecSQL(
        db,
        "CREATE TABLE instanceValidationDisabledChecks("
        "   instanceId INT NOT NULL,"
        "   validationCheck INT NOT NULL,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id),"
        "   FOREIGN KEY(validationCheck) REFERENCES VkValidationCheckEXT) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE deviceEnabledLayers("
        "   deviceId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE deviceEnabledExtensions("
        "   deviceId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE deviceEnabledFeatures("
        "   deviceId INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queues("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   familyIndex INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   priority REAL NOT NULL,"
        "   deviceId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id)) STRICT;"
    );
}

static void CreateQueueSubmitTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE queueSubmits("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   queueId INT NOT NULL,"
        "   fenceSyncScopeId INT,"
        "   frameId INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(queueId) REFERENCES queues(id),"
        "   FOREIGN KEY(fenceSyncScopeId) REFERENCES fenceSyncScopes(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queueSubmitBatches("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   idx INT NOT NULL,"
        "   queueSubmitId INT NOT NULL,"
        "   FOREIGN KEY(queueSubmitId) REFERENCES queueSubmits(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queueSubmitSemaphoreWaits("
        "   queueSubmitBatchId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   waitStage INT,"
        "   value INT,"
        "   semaphoreId INT,"
        "   FOREIGN KEY(queueSubmitBatchId) REFERENCES queueSubmitBatches(id),"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queueSubmitSemaphoreSignals("
        "   queueSubmitBatchId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   value INT,"
        "   semaphoreId INT,"
        "   FOREIGN KEY(queueSubmitBatchId) REFERENCES queueSubmitBatches(id),"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queueSubmitBuffers("
        "   queueSubmitBatchId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   commandBufferRecordingId INT,"
        "   FOREIGN KEY(queueSubmitBatchId) REFERENCES queueSubmitBatches(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id)) STRICT;"
    );
}

static void CreateQueuePresentTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE queuePresents("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   queueId INT NOT NULL,"
        "   frameId INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(queueId) REFERENCES queues(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queuePresentSemaphoreWaits("
        "   queuePresentId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   semaphoreId INT,"
        "   FOREIGN KEY(queuePresentId) REFERENCES queuePresents(id),"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queuePresentSwapchains("
        "   queuePresentId INT NOT NULL,"
        "   swapchainId INT,"
        "   imageIndex INT NOT NULL,"
        "   FOREIGN KEY(queuePresentId) REFERENCES queuePresents(id),"
        "   FOREIGN KEY(swapchainId) REFERENCES swapchains(id)) STRICT;"
    );
}

static void CreateSynchronizationTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE fences("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE fenceSyncScopes("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   fence INT,"
        "   initApiEventId INT,"
        "   waitApiEventId INT,"
        "   resetApiEventId INT,"
        "   FOREIGN KEY(fence) REFERENCES fences(id),"
        "   FOREIGN KEY(initApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(waitApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(resetApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE semaphores("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   type INT NOT NULL,"
        "   initialValue INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(type) REFERENCES VkSemaphoreType(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE semaphoreWaits("
        "   semaphoreId INT,"
        "   value INT,"
        "   idx INT,"
        "   flags INT,"
        "   timeout INT,"
        "   apiEventId INT,"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE semaphoreSignals("
        "   semaphoreId INT,"
        "   value INT,"
        "   apiEventId INT,"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE events("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE queryPools("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   type INT NOT NULL,"
        "   count INT NOT NULL,"
        "   pipelineStatistics INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(type) REFERENCES VkQueryType(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateDescriptorSetTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE descriptorPools("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   maxSets INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetLayouts("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetLayoutBindings("
        "   descriptorSetLayoutId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   descriptorType INT NOT NULL,"
        "   descriptorCount INT NOT NULL,"
        "   stageFlags INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   FOREIGN KEY(descriptorType) REFERENCES VkDescriptorType(value),"
        "   FOREIGN KEY(descriptorSetLayoutId) REFERENCES descriptorSetLayouts(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSets("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   descriptorPoolId INT NOT NULL,"
        "   descriptorSetLayoutId INT,"
        "   allocateApiEventId INT NOT NULL,"
        "   freeApiEventId INT,"
        "   FOREIGN KEY(descriptorPoolId) REFERENCES descriptorPools(id),"
        "   FOREIGN KEY(descriptorSetLayoutId) REFERENCES descriptorSetLayouts(id),"
        "   FOREIGN KEY(allocateApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(freeApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorUpdateTemplates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   templateType INT NOT NULL,"
        "   descriptorSetLayoutId INT,"
        "   pipelineBindPoint INT,"
        "   pipelineLayoutId INT,"
        "   setIndex INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(templateType) REFERENCES VkDescriptorUpdateTemplateType(value),"
        "   FOREIGN KEY(descriptorSetLayoutId) REFERENCES descriptorSetLayouts(id),"
        "   FOREIGN KEY(pipelineBindPoint) REFERENCES VkPipelineBindPoint(value),"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorUpdateTemplateEntries("
        "   templateId INT NOT NULL,"
        "   dstBinding INT NOT NULL,"
        "   dstArrayElement INT NOT NULL,"
        "   descriptorCount INT NOT NULL,"
        "   descriptorType INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   stride INT NOT NULL,"
        "   FOREIGN KEY(templateId) REFERENCES descriptorUpdateTemplates(id),"
        "   FOREIGN KEY(descriptorType) REFERENCES VkDescriptorType(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE privateDataSlots("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWrites("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   descriptorSetId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   arrayElement INT NOT NULL,"
        "   descriptorType INT NOT NULL,"
        "   apiEventId INT,"
        "   FOREIGN KEY(descriptorSetId) REFERENCES descriptorSets(id),"
        "   FOREIGN KEY(descriptorType) REFERENCES VkDescriptorType(value),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWriteImageInfos("
        "   descriptorSetWriteId INT NOT NULL,"
        "   samplerId INT,"
        "   imageViewId INT,"
        "   imageLayout INT NOT NULL,"
        "   FOREIGN KEY(descriptorSetWriteId) REFERENCES descriptorSetWrites(id),"
        "   FOREIGN KEY(samplerId) REFERENCES samplers(id),"
        "   FOREIGN KEY(imageViewId) REFERENCES imageViews(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWriteBufferInfos("
        "   descriptorSetWriteId INT NOT NULL,"
        "   bufferId INT,"
        "   offset INT NOT NULL,"
        "   range INT NOT NULL,"
        "   FOREIGN KEY(descriptorSetWriteId) REFERENCES descriptorSetWrites(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWriteTexelInfos("
        "   descriptorSetWriteId INT NOT NULL,"
        "   texelBufferViewId INT,"
        "   FOREIGN KEY(descriptorSetWriteId) REFERENCES descriptorSetWrites(id),"
        "   FOREIGN KEY(texelBufferViewId) REFERENCES bufferViews(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWriteAccelerationInfos("
        "   descriptorSetWriteId INT NOT NULL,"
        "   accelerationStructureId INT,"
        "   FOREIGN KEY(descriptorSetWriteId) REFERENCES descriptorSetWrites(id),"
        "   FOREIGN KEY(accelerationStructureId) REFERENCES accelerationStructures(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE descriptorSetWriteAccelerationNvInfos("
        "   descriptorSetWriteId INT NOT NULL,"
        "   accelerationStructureNvId INT,"
        "   FOREIGN KEY(descriptorSetWriteId) REFERENCES descriptorSetWrites(id),"
        "   FOREIGN KEY(accelerationStructureNvId) REFERENCES accelerationStructuresNv(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushes("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   setIndex INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   arrayElement INT NOT NULL,"
        "   descriptorType INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(descriptorType) REFERENCES VkDescriptorType(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushImageInfos("
        "   stateId INT NOT NULL,"
        "   samplerId INT,"
        "   imageViewId INT,"
        "   imageLayout INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetPushes(stateId),"
        "   FOREIGN KEY(samplerId) REFERENCES samplers(id),"
        "   FOREIGN KEY(imageViewId) REFERENCES imageViews(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushBufferInfos("
        "   stateId INT NOT NULL,"
        "   bufferId INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   range INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetPushes(stateId),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushTexelInfos("
        "   stateId INT NOT NULL,"
        "   texelBufferViewId INT,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetPushes(stateId),"
        "   FOREIGN KEY(texelBufferViewId) REFERENCES bufferViews(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushAccelerationInfos("
        "   stateId INT NOT NULL,"
        "   accelerationStructureId INT,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetPushes(stateId),"
        "   FOREIGN KEY(accelerationStructureId) REFERENCES accelerationStructures(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetPushAccelerationNvInfos("
        "   stateId INT NOT NULL,"
        "   accelerationStructureNvId INT,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetPushes(stateId),"
        "   FOREIGN KEY(accelerationStructureNvId) REFERENCES accelerationStructuresNv(id)) STRICT;"
    );
}

static void CreateShaderTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE shaderObjects("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   stage INT NOT NULL,"
        "   nextStage INT NOT NULL,"
        "   codeType INT NOT NULL,"
        "   codeSize INT NOT NULL,"
        "   entryPointName TEXT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(stage) REFERENCES VkShaderStageFlagBits(value),"
        "   FOREIGN KEY(codeType) REFERENCES VkShaderCodeTypeEXT(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE shaderObjectDescriptorSetLayouts("
        "   shaderObjectId INT,"
        "   setIndex INT NOT NULL,"
        "   descriptorSetLayoutId INT,"
        "   FOREIGN KEY(shaderObjectId) REFERENCES shaderObjects(id),"
        "   FOREIGN KEY(descriptorSetLayoutId) REFERENCES descriptorSetLayouts(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE shaderObjectPushConstantRanges("
        "   shaderObjectId INT,"
        "   rangeIndex INT NOT NULL,"
        "   stageFlags INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   size INT NOT NULL,"
        "   FOREIGN KEY(shaderObjectId) REFERENCES shaderObjects(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE shaderModules("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   codeSize INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE validationCaches("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   initialDataSize INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateStateTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE stateIds("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateTypes("
        "    id INT NOT NULL PRIMARY KEY,"
        "    name TEXT NOT NULL) STRICT;"
    );

    // stateGroups is a virtual table in the sense that we track the stateGroupId IDs
    // in the consumer but we do not populate a table with the mappings, and no foreign keys map
    // to a stateGroups table but the values we apply to the stateGroupId fields are a
    // primary key mapping that is shared between state tracking tables.
    // Nothing ends up querying a stateGroups table directly, these values are only used for joins.

    ExecSQL(
        db,
        "CREATE TABLE stateGroupEntries("
        "   stateGroupId INT NOT NULL,"
        "   stateId INT NOT NULL,"
        "   stateTypeId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   subIndex INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id)"
        "   FOREIGN KEY(stateTypeId) REFERENCES stateTypes(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE statePipelineBindings("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   bindPoint INT NOT NULL,"
        "   pipelineId INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(bindPoint) REFERENCES VkPipelineBindPoint(value),"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateShaderObjectBindings("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stage INT NOT NULL,"
        "   shader INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(stage) REFERENCES VkShaderStageFlagBits(value),"
        "   FOREIGN KEY(shader) REFERENCES shaderObjects(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateVertexBufferBindings("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   bufferId INT,"
        "   offset INT NOT NULL,"
        "   size INT,"
        "   stride INT,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateIndexBufferBindings("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   bufferId INT,"
        "   offset INT NOT NULL,"
        "   indexType INT NOT NULL,"
        "   size INT,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(indexType) REFERENCES VkIndexType(value),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetBindings("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   setIndex INT NOT NULL,"
        "   stageFlags INT NOT NULL,"
        "   pipelineLayoutId INT NOT NULL,"
        "   descriptorSetId INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id),"
        "   FOREIGN KEY(descriptorSetId) REFERENCES descriptorSets(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDescriptorSetBindingDynamicOffsets("
        "   stateId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   arrayElement INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateDescriptorSetBindings(stateId)) STRICT;"
    );
}

static void CreatePipelineTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE pipelineLayouts("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineDescriptorSetLayouts("
        "   pipelineLayoutId INT NOT NULL,"
        "   setIndex INT NOT NULL,"
        "   descriptorSetLayoutId INT,"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id),"
        "   FOREIGN KEY(descriptorSetLayoutId) REFERENCES descriptorSetLayouts(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelinePushConstantRanges("
        "   pipelineLayoutId INT NOT NULL,"
        "   rangeIndex INT NOT NULL,"
        "   stageFlags INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   size INT NOT NULL,"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelines("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   pipelineType TEXT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   basePipelineId INT,"
        "   pipelineLayoutId INT,"
        "   renderPassId INT,"
        "   viewMask INT,"
        "   depthAttachmentFormat INT,"
        "   stencilAttachmentFormat INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(basePipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id),"
        "   FOREIGN KEY(renderPassId) REFERENCES renderPasses(id),"
        "   FOREIGN KEY(depthAttachmentFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(stencilAttachmentFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineColorAttachmentFormats("
        "   pipelineId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   format INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineDynamicStates("
        "   pipelineId INT NOT NULL,"
        "   dynamicState INT NOT NULL,"
        "   UNIQUE(pipelineId, dynamicState),"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(dynamicState) REFERENCES VkDynamicState(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineStages("
        "   pipelineId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   stage INT NOT NULL,"
        "   shaderModuleId INT,"
        "   entryPointName TEXT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(stage) REFERENCES VkShaderStageFlagBits(value),"
        "   FOREIGN KEY(shaderModuleId) REFERENCES shaderModules(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineCaches("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   initialDataSize INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineBinaries("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   keySize INT NOT NULL,"
        "   dataSize INT NOT NULL,"
        "   pipelineId INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE pipelineLibraries("
        "   pipelineId INT NOT NULL,"
        "   libraryPipelineId INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(libraryPipelineId) REFERENCES pipelines(id)) STRICT;"
    );
}

static void CreateGraphicsPipelineTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE graphicsPipelineInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   libraryFlags INT NOT NULL,"
        "   subpassIndex INT NOT NULL,"
        "   vertexInputStateId INT,"
        "   inputAssemblyStateId INT,"
        "   tessellationStateId INT,"
        "   viewportStateId INT,"
        "   rasterizationStateId INT,"
        "   multisampleStateId INT,"
        "   depthStencilStateId INT,"
        "   colorBlendStateId INT,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(vertexInputStateId) REFERENCES vertexInputStates(id),"
        "   FOREIGN KEY(inputAssemblyStateId) REFERENCES inputAssemblyStates(id),"
        "   FOREIGN KEY(tessellationStateId) REFERENCES tessellationStates(id),"
        "   FOREIGN KEY(viewportStateId) REFERENCES viewportStates(id),"
        "   FOREIGN KEY(rasterizationStateId) REFERENCES rasterizationStates(id),"
        "   FOREIGN KEY(multisampleStateId) REFERENCES multisampleStates(id),"
        "   FOREIGN KEY(depthStencilStateId) REFERENCES depthStencilStates(id),"
        "   FOREIGN KEY(colorBlendStateId) REFERENCES colorBlendStates(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE colorBlendStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   logicOpEnable INT NOT NULL,"
        "   logicOp INT,"
        "   blendConstantsR REAL NOT NULL,"
        "   blendConstantsG REAL NOT NULL,"
        "   blendConstantsB REAL NOT NULL,"
        "   blendConstantsA REAL NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(logicOpEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(logicOp) REFERENCES VkLogicOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE colorBlendStateAttachmentStates("
        "   colorBlendStateId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   blendEnable INT NOT NULL,"
        "   srcColorBlendFactor INT NOT NULL,"
        "   dstColorBlendFactor INT NOT NULL,"
        "   colorBlendOp INT NOT NULL,"
        "   srcAlphaBlendFactor INT NOT NULL,"
        "   dstAlphaBlendFactor INT NOT NULL,"
        "   alphaBlendOp INT NOT NULL,"
        "   colorWriteMask INT NOT NULL,"
        "   colorWriteEnable INT NOT NULL,"
        "   FOREIGN KEY(colorBlendStateId) REFERENCES colorBlendStates(id),"
        "   FOREIGN KEY(blendEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(srcColorBlendFactor) REFERENCES VkBlendFactor(value),"
        "   FOREIGN KEY(dstColorBlendFactor) REFERENCES VkBlendFactor(value),"
        "   FOREIGN KEY(colorBlendOp) REFERENCES VkBlendOp(value),"
        "   FOREIGN KEY(srcAlphaBlendFactor) REFERENCES VkBlendFactor(value),"
        "   FOREIGN KEY(dstAlphaBlendFactor) REFERENCES VkBlendFactor(value),"
        "   FOREIGN KEY(alphaBlendOp) REFERENCES VkBlendOp(value),"
        "   FOREIGN KEY(colorWriteEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE depthStencilStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   depthTestEnable INT NOT NULL,"
        "   depthWriteEnable INT NOT NULL,"
        "   depthCompareOp INT NOT NULL,"
        "   depthBoundsTestEnable INT NOT NULL,"
        "   stencilTestEnable INT NOT NULL,"
        "   frontFailOp INT NOT NULL,"
        "   frontPassOp INT NOT NULL,"
        "   frontDepthFailOp INT NOT NULL,"
        "   frontCompareOp INT NOT NULL,"
        "   frontCompareMask INT NOT NULL,"
        "   frontWriteMask INT NOT NULL,"
        "   frontReference INT NOT NULL,"
        "   backFailOp INT NOT NULL,"
        "   backPassOp INT NOT NULL,"
        "   backDepthFailOp INT NOT NULL,"
        "   backCompareOp INT NOT NULL,"
        "   backCompareMask INT NOT NULL,"
        "   backWriteMask INT NOT NULL,"
        "   backReference INT NOT NULL,"
        "   minDepthBounds REAL NOT NULL,"
        "   maxDepthBounds REAL NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(depthTestEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(depthWriteEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(depthCompareOp) REFERENCES VkCompareOp(value),"
        "   FOREIGN KEY(depthBoundsTestEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(stencilTestEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(frontFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(frontPassOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(frontDepthFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(frontCompareOp) REFERENCES VkCompareOp(value),"
        "   FOREIGN KEY(backFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(backPassOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(backDepthFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(backCompareOp) REFERENCES VkCompareOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE multisampleStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   rasterizationSamples INT NOT NULL,"
        "   sampleShadingEnable INT NOT NULL,"
        "   minSampleShading INT NOT NULL,"
        "   alphaToCoverageEnable INT NOT NULL,"
        "   alphaToOneEnable INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(sampleShadingEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(alphaToCoverageEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(alphaToOneEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE multisampleStateSampleMasks("
        "   multisampleStateId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   sampleMask INT NOT NULL,"
        "   FOREIGN KEY(multisampleStateId) REFERENCES multisampleStates(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE rasterizationStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   depthClampEnable INT NOT NULL,"
        "   rasterizerDiscardEnable INT NOT NULL,"
        "   polygonMode INT NOT NULL,"
        "   cullMode INT NOT NULL,"
        "   frontFace INT NOT NULL,"
        "   depthBiasEnable INT NOT NULL,"
        "   depthBiasConstantFactor REAL NOT NULL,"
        "   depthBiasClamp REAL NOT NULL,"
        "   depthBiasSlopeFactor REAL NOT NULL,"
        "   lineWidth REAL NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(depthClampEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(rasterizerDiscardEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(polygonMode) REFERENCES VkPolygonMode(value),"
        "   FOREIGN KEY(frontFace) REFERENCES VkFrontFace(value),"
        "   FOREIGN KEY(depthBiasEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE viewportStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE viewportStateScissors("
        "   viewportStateId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   x INT NOT NULL,"
        "   y INT NOT NULL,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   FOREIGN KEY(viewportStateId) REFERENCES viewportStates(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE viewportStateViewports("
        "   viewportStateId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   x REAL NOT NULL,"
        "   y REAL NOT NULL,"
        "   width REAL NOT NULL,"
        "   height REAL NOT NULL,"
        "   minDepth REAL NOT NULL,"
        "   maxDepth REAL NOT NULL,"
        "   FOREIGN KEY(viewportStateId) REFERENCES viewportStates(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE tessellationStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   patchControlPoints INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE inputAssemblyStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   topology INT NOT NULL,"
        "   primitiveRestartEnable INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(topology) REFERENCES VkPrimitiveTopology(value),"
        "   FOREIGN KEY(primitiveRestartEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE vertexInputStates("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE vertexInputStateAttributeDescriptions("
        "   vertexInputStateId INT NOT NULL,"
        "   location INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   format INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   FOREIGN KEY(vertexInputStateId) REFERENCES vertexInputStates(id),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE vertexInputStateBindingDescriptions("
        "   vertexInputStateId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   stride INT NOT NULL,"
        "   inputRate INT NOT NULL,"
        "   divisor INT NOT NULL,"
        "   FOREIGN KEY(vertexInputStateId) REFERENCES vertexInputStates(id),"
        "   FOREIGN KEY(inputRate) REFERENCES VkVertexInputRate(value)) STRICT;"
    );
}

static void CreateComputePipelineTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE computePipelineInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );
}

static void CreateDataGraphPipelineTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE dataGraphPipelineInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE dataGraphPipelineResourceInfos("
        "   dataGraphPipelineInfoId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   descriptorSet INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   arrayElement INT NOT NULL,"
        "   FOREIGN KEY(dataGraphPipelineInfoId) REFERENCES dataGraphPipelineInfos(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE dataGraphPipelineSessions("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   pipelineId INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

}

static void CreateRaytracingPipelineTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE raytracingPipelineInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   pipelineId INT NOT NULL,"
        "   maxRecursionDepth INT NOT NULL,"
        "   maxPipelineRayPayloadSize INT,"
        "   maxPipelineRayHitAttributeSize INT,"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE raytracingShaderGroups("
        "   raytracingPipelineInfoId INTEGER NOT NULL,"
        "   pipelineId INT NOT NULL,"
        "   type INT NOT NULL,"
        "   generalShaderIndex INT NOT NULL,"
        "   closestHitShaderIndex INT NOT NULL,"
        "   anyHitShaderIndex INT NOT NULL,"
        "   intersectionShaderIndex INT NOT NULL,"
        "   FOREIGN KEY(raytracingPipelineInfoId) REFERENCES raytracingPipelineInfos(id),"
        "   FOREIGN KEY(pipelineId) REFERENCES pipelines(id),"
        "   FOREIGN KEY(type) REFERENCES VkRayTracingShaderGroupTypeKHR(value)) STRICT;"
    );
}

static void CreateDisplayTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE displays("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   physicalDeviceId INT NOT NULL,"
        "   getApiEventId INT NOT NULL,"
        "   FOREIGN KEY(physicalDeviceId) REFERENCES physicalDevices(id),"
        "   FOREIGN KEY(getApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE displayModes("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   physicalDeviceId INT NOT NULL,"
        "   displayId INT NOT NULL,"
        "   visibleRegionWidth INT NOT NULL,"
        "   visibleRegionHeight INT NOT NULL,"
        "   refreshRate INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   FOREIGN KEY(physicalDeviceId) REFERENCES physicalDevices(id),"
        "   FOREIGN KEY(displayId) REFERENCES displays(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateSwapchainTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE swapchains("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   minImageCount INT NOT NULL,"
        "   imageFormat INT NOT NULL,"
        "   imageColorSpace INT NOT NULL,"
        "   imageWidth INT NOT NULL,"
        "   imageHeight INT NOT NULL,"
        "   imageLayers INT NOT NULL,"
        "   imageUsage INT NOT NULL,"
        "   imageSharing INT NOT NULL,"
        "   preTransform INT NOT NULL,"
        "   compositeAlpha INT NOT NULL,"
        "   presentMode INT NOT NULL,"
        "   clipped INT NOT NULL,"
        "   oldSwapchainId INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(imageFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(imageColorSpace) REFERENCES VkColorSpaceKHR(value),"
        "   FOREIGN KEY(imageSharing) REFERENCES VkSharingMode(value),"
        "   FOREIGN KEY(presentMode) REFERENCES VkPresentModeKHR(value),"
        "   FOREIGN KEY(clipped) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(oldSwapchainId) REFERENCES swapchains(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE acquireNextImages("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   swapchainId INT NOT NULL,"
        "   fenceSyncScopeId INT,"
        "   semaphoreId INT,"
        "   frameId INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(swapchainId) REFERENCES swapchains(id),"
        "   FOREIGN KEY(fenceSyncScopeId) REFERENCES fenceSyncScopes(id),"
        "   FOREIGN KEY(semaphoreId) REFERENCES semaphores(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateBufferTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE images("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   swapchainId INT,"
        "   flags INT,"
        "   imageType INT NOT NULL,"
        "   format INT NOT NULL,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   depth INT NOT NULL,"
        "   mipLevels INT NOT NULL,"
        "   layers INT NOT NULL,"
        "   sampleCount INT NOT NULL,"
        "   tiling INT NOT NULL,"
        "   usage INT NOT NULL,"
        "   sharing INT NOT NULL,"
        "   initialLayout INT NOT NULL,"
        "   externalFormat INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(swapchainId) REFERENCES swapchains(id),"
        "   FOREIGN KEY(imageType) REFERENCES VkImageType(value),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(tiling) REFERENCES VkImageTiling(value),"
        "   FOREIGN KEY(sharing) REFERENCES VkSharingMode(value),"
        "   FOREIGN KEY(initialLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE imageViews("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   imageId INT,"
        "   viewType INT NOT NULL,"
        "   format INT NOT NULL,"
        "   componentR INT NOT NULL,"
        "   componentG INT NOT NULL,"
        "   componentB INT NOT NULL,"
        "   componentA INT NOT NULL,"
        "   subresourceRangeAspectMask INT NOT NULL,"
        "   subresourceRangeBaseMipLevel INT NOT NULL,"
        "   subresourceRangeLevelCount INT NOT NULL,"
        "   subresourceRangeBaseLayer INT NOT NULL,"
        "   subresourceRangeLayerCount INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(imageId) REFERENCES images(id),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(componentR) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentG) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentB) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentA) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE samplers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   magFilter INT NOT NULL,"
        "   minFilter INT NOT NULL,"
        "   mipmapMode INT NOT NULL,"
        "   addressModeU INT NOT NULL,"
        "   addressModeV INT NOT NULL,"
        "   addressModeW INT NOT NULL,"
        "   mipLodBias REAL NOT NULL,"
        "   anisotropyEnable INT NOT NULL,"
        "   maxAnisotropy REAL NOT NULL,"
        "   compareEnable INT NOT NULL,"
        "   compareOp INT,"
        "   minLod REAL NOT NULL,"
        "   maxLod REAL NOT NULL,"
        "   borderColor INT,"
        "   unnormalizedCoordinates INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(magFilter) REFERENCES VkFilter(value),"
        "   FOREIGN KEY(minFilter) REFERENCES VkFilter(value),"
        "   FOREIGN KEY(mipmapMode) REFERENCES VkSamplerMipmapMode(value),"
        "   FOREIGN KEY(addressModeW) REFERENCES VkSamplerAddressMode(value),"
        "   FOREIGN KEY(addressModeU) REFERENCES VkSamplerAddressMode(value),"
        "   FOREIGN KEY(addressModeW) REFERENCES VkSamplerAddressMode(value),"
        "   FOREIGN KEY(anisotropyEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(compareEnable) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(compareOp) REFERENCES VkCompareOp(value),"
        "   FOREIGN KEY(borderColor) REFERENCES VkBorderColor(value),"
        "   FOREIGN KEY(unnormalizedCoordinates) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE samplerYcbcrConversions("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   format INT NOT NULL,"
        "   ycbcrModel INT NOT NULL,"
        "   ycbcrRange INT NOT NULL,"
        "   componentR INT NOT NULL,"
        "   componentG INT NOT NULL,"
        "   componentB INT NOT NULL,"
        "   componentA INT NOT NULL,"
        "   xChromaOffset INT NOT NULL,"
        "   yChromaOffset INT NOT NULL,"
        "   chromaFilter INT NOT NULL,"
        "   forcedExplicitReconstruction INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(ycbcrModel) REFERENCES VkSamplerYcbcrModelConversion(value),"
        "   FOREIGN KEY(ycbcrRange) REFERENCES VkSamplerYcbcrRange(value),"
        "   FOREIGN KEY(componentR) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentG) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentB) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(componentA) REFERENCES VkComponentSwizzle(value),"
        "   FOREIGN KEY(xChromaOffset) REFERENCES VkChromaLocation(value),"
        "   FOREIGN KEY(yChromaOffset) REFERENCES VkChromaLocation(value),"
        "   FOREIGN KEY(chromaFilter) REFERENCES VkFilter(value),"
        "   FOREIGN KEY(forcedExplicitReconstruction) REFERENCES VkBool32(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE bufferViews("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   bufferId INT,"
        "   format INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   range INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateAccelerationStructureTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE accelerationStructures("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   type INT NOT NULL,"
        "   bufferId INT,"
        "   offset INT NOT NULL,"
        "   size INT NOT NULL,"
        "   deviceAddress INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(type) REFERENCES VkAccelerationStructureTypeKHR(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructuresNv("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   type INT NOT NULL,"
        "   compactedSize INT NOT NULL,"
        "   instanceCount INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(type) REFERENCES VkAccelerationStructureTypeKHR(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuilds("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   deviceId INT,"
        "   frameId INT,"
        "   deferredOperation INT,"
        "   commandBufferRecordingId INT,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id) ON DELETE SET NULL,"
        "   FOREIGN KEY(deferredOperation) REFERENCES deferredOperations(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureCopies("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   deviceId INT,"
        "   frameId INT,"
        "   deferredOperation INT,"
        "   commandBufferRecordingId INT,"
        "   srcAccelerationStructureId INT,"
        "   dstAccelerationStructureId INT,"
        "   srcAddress INT,"
        "   dstAddress INT,"
        "   mode INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id) ON DELETE SET NULL,"
        "   FOREIGN KEY(deferredOperation) REFERENCES deferredOperations(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(srcAccelerationStructureId) REFERENCES accelerationStructures(id),"
        "   FOREIGN KEY(dstAccelerationStructureId) REFERENCES accelerationStructures(id),"
        "   FOREIGN KEY(mode) REFERENCES VkCopyAccelerationStructureModeKHR(value),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildGeometryInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   accelerationStructureBuildId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   type INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   mode INT NOT NULL,"
        "   srcAccelerationStructureId INT,"
        "   dstAccelerationStructureId INT NOT NULL,"
        "   scratchDataAddress INT NOT NULL,"
        "   FOREIGN KEY(accelerationStructureBuildId) REFERENCES accelerationStructureBuilds(id),"
        "   FOREIGN KEY(type) REFERENCES VkAccelerationStructureTypeKHR(value),"
        "   FOREIGN KEY(mode) REFERENCES VkBuildAccelerationStructureModeKHR(value),"
        "   FOREIGN KEY (srcAccelerationStructureId) REFERENCES accelerationStructures(id),"
        "   FOREIGN KEY (dstAccelerationStructureId) REFERENCES accelerationStructures(id)) STRICT;"
    );

    // clang-format off
    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildGeometries("
        "   accelerationStructureBuildGeometryInfoId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   type INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   triangleDataId INT,"
        "   aabbDataId INT,"
        "   instanceDataId INT,"
        "   FOREIGN KEY(accelerationStructureBuildGeometryInfoId) REFERENCES accelerationStructureBuildGeometryInfos(id),"
        "   FOREIGN KEY(type) REFERENCES VkGeometryTypeKHR(value),"
        "   FOREIGN KEY(triangleDataId) REFERENCES accelerationStructureBuildTriangleDatas(id),"
        "   FOREIGN KEY(aabbDataId) REFERENCES accelerationStructureBuildAABBDatas(id),"
        "   FOREIGN KEY(instanceDataId) REFERENCES accelerationStructureBuildInstanceDatas(id)) STRICT;"
    );
    // clang-format on

    // clang-format off
    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildRangeInfos("
        "   accelerationStructureBuildGeometryInfoId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   primitiveCount INT NOT NULL,"
        "   primitiveOffset INT NOT NULL,"
        "   firstVertex INT NOT NULL,"
        "   transformOffset INT NOT NULL,"
        "   FOREIGN KEY(accelerationStructureBuildGeometryInfoId) REFERENCES accelerationStructureBuildGeometryInfos(id)) STRICT;"
    );
    // clang-format on

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildTriangleDatas("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   vertexFormat INT NOT NULL,"
        "   vertexStride INT NOT NULL,"
        "   vertexDataAddress INT NOT NULL,"
        "   maxVertex INT NOT NULL,"
        "   indexType INT NOT NULL,"
        "   indexDataAddress INT NOT NULL,"
        "   transformDataAddress INT NOT NULL,"
        "   FOREIGN KEY(vertexFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(indexType) REFERENCES VkIndexType(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildAABBDatas("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   dataAddress INT NOT NULL,"
        "   stride INT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE accelerationStructureBuildInstanceDatas("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   dataAddress INT NOT NULL,"
        "   arrayOfPointers INT NOT NULL,"
        "   FOREIGN KEY(arrayOfPointers) REFERENCES VkBool32(value)) STRICT;"
    );
}

static void CreateTransferCommandTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE transferCommands("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   commandBufferRecordingId INT,"
        "   frameId INT,"
        "   srcBufferId INT,"
        "   dstBufferId INT,"
        "   srcImageId INT,"
        "   dstImageId INT,"
        "   srcImageLayoutId INT,"
        "   dstImageLayoutId INT,"
        "   bufferImageSrcBufferId INT,"
        "   bufferImageDstImageId INT,"
        "   bufferImageSrcImageId INT,"
        "   bufferImageDstBufferId INT,"
        "   blitFilter INT,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(srcBufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(dstBufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(srcImageId) REFERENCES images(id),"
        "   FOREIGN KEY(dstImageId) REFERENCES images(id),"
        "   FOREIGN KEY(srcImageLayoutId) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(dstImageLayoutId) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(bufferImageSrcBufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(bufferImageDstImageId) REFERENCES images(id),"
        "   FOREIGN KEY(bufferImageSrcImageId) REFERENCES images(id),"
        "   FOREIGN KEY(bufferImageDstBufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(blitFilter) REFERENCES VkFilter(value)) STRICT;"
    );

    // Buffer-to-buffer copies (7 columns, all NOT NULL)
    ExecSQL(
        db,
        "CREATE TABLE transferCommandRegionBufferCopies("
        "   transferCommandId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   srcBufferId INT NOT NULL,"
        "   dstBufferId INT NOT NULL,"
        "   srcBufferOffset INT NOT NULL,"
        "   dstBufferOffset INT NOT NULL,"
        "   bufferSize INT NOT NULL,"
        "   FOREIGN KEY(transferCommandId) REFERENCES transferCommands(id),"
        "   FOREIGN KEY(srcBufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(dstBufferId) REFERENCES buffers(id)) STRICT;"
    );

    // Image-to-image copies/blits/resolves (22 columns)
    ExecSQL(
        db,
        "CREATE TABLE transferCommandRegionImageCopies("
        "   transferCommandId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   srcImageId INT NOT NULL,"
        "   dstImageId INT NOT NULL,"
        "   srcBaseArrayLayer INT,"
        "   srcLayerCount INT,"
        "   srcMipLevel INT,"
        "   dstBaseArrayLayer INT,"
        "   dstLayerCount INT,"
        "   dstMipLevel INT,"
        "   srcOffsetX INT NOT NULL,"
        "   srcOffsetY INT NOT NULL,"
        "   srcOffsetZ INT NOT NULL,"
        "   dstOffsetX INT NOT NULL,"
        "   dstOffsetY INT NOT NULL,"
        "   dstOffsetZ INT NOT NULL,"
        "   srcExtentWidth INT NOT NULL,"
        "   srcExtentHeight INT NOT NULL,"
        "   srcExtentDepth INT NOT NULL,"
        "   dstExtentWidth INT NOT NULL,"
        "   dstExtentHeight INT NOT NULL,"
        "   dstExtentDepth INT NOT NULL,"
        "   FOREIGN KEY(transferCommandId) REFERENCES transferCommands(id),"
        "   FOREIGN KEY(srcImageId) REFERENCES images(id),"
        "   FOREIGN KEY(dstImageId) REFERENCES images(id)) STRICT;"
    );

    // Buffer-image copies (15 columns, handles both directions)
    ExecSQL(
        db,
        "CREATE TABLE transferCommandRegionBufferImageCopies("
        "   transferCommandId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   bufferId INT NOT NULL,"
        "   imageId INT NOT NULL,"
        "   isBufferSource INT NOT NULL,"
        "   bufferOffset INT NOT NULL,"
        "   imageBaseArrayLayer INT,"
        "   imageLayerCount INT,"
        "   imageMipLevel INT,"
        "   imageOffsetX INT NOT NULL,"
        "   imageOffsetY INT NOT NULL,"
        "   imageOffsetZ INT NOT NULL,"
        "   extentWidth INT NOT NULL,"
        "   extentHeight INT NOT NULL,"
        "   extentDepth INT NOT NULL,"
        "   FOREIGN KEY(transferCommandId) REFERENCES transferCommands(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(imageId) REFERENCES images(id)) STRICT;"
    );
}

static void CreateDeferredOperationTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE deferredOperations("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateDynamicStateTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE stateDynamicVertexInputBindingDescriptions("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   stride INT NOT NULL,"
        "   inputRate INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(inputRate) REFERENCES VkVertexInputRate(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicVertexInputAttributeDescriptions("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   location INT NOT NULL,"
        "   binding INT NOT NULL,"
        "   format INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicViewports("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   viewportIndex INT NOT NULL,"
        "   x REAL NOT NULL,"
        "   y REAL NOT NULL,"
        "   width REAL NOT NULL,"
        "   height REAL NOT NULL,"
        "   minDepth REAL NOT NULL,"
        "   maxDepth REAL NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicScissors("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   scissorIndex INT NOT NULL,"
        "   x INT NOT NULL,"
        "   y INT NOT NULL,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicLineWidths("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   lineWidth REAL NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicRenderingColorAttachmentLocations("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   oldLocation INT NOT NULL,"
        "   newLocation INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicRenderingInputColorAttachmentIndices("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   oldIndex INT NOT NULL,"
        "   newIndex INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicRenderingInputDepthAttachmentIndices("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicRenderingInputStencilAttachmentIndices("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthBounds("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   min REAL NOT NULL,"
        "   max REAL NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthBoundsTestEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   depthBoundsTestEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(depthBoundsTestEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthBias("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   constantFactor REAL NOT NULL,"
        "   clamp REAL NOT NULL,"
        "   slopeFactor REAL NOT NULL,"
        "   representation INT NOT NULL,"
        "   exact INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(representation) REFERENCES VkDepthBiasRepresentationEXT(value),"
        "   FOREIGN KEY(exact) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthBiasEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   depthBiasEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(depthBiasEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthTestEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   depthTestEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(depthTestEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthWriteEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   depthWriteEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(depthWriteEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicDepthCompareOps("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   depthCompareOp INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(depthCompareOp) REFERENCES VkCompareOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilCompareMasksFront("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   mask INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilCompareMasksBack("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   mask INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilWriteMasksFront("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   mask INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilWriteMasksBack("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   mask INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilReferencesFront("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   reference INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilReferencesBack("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   reference INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilTestEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stencilTestEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(stencilTestEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilOpsFront("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   failOp INT NOT NULL,"
        "   passOp INT NOT NULL,"
        "   depthFailOp INT NOT NULL,"
        "   compareOp INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(failOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(passOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(depthFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(compareOp) REFERENCES VkCompareOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicStencilOpsBack("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   failOp INT NOT NULL,"
        "   passOp INT NOT NULL,"
        "   depthFailOp INT NOT NULL,"
        "   compareOp INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(failOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(passOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(depthFailOp) REFERENCES VkStencilOp(value),"
        "   FOREIGN KEY(compareOp) REFERENCES VkCompareOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicColorWriteEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   attachmentIndex INT NOT NULL,"
        "   colorWriteEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(colorWriteEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicBlendConstants("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   r REAL NOT NULL,"
        "   g REAL NOT NULL,"
        "   b REAL NOT NULL,"
        "   a REAL NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicPrimitiveTopologies("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   primitiveTopology INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(primitiveTopology) REFERENCES VkPrimitiveTopology(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicCullModes("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   cullMode INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicFrontFaces("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   frontFace INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(frontFace) REFERENCES VkFrontFace(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicLogicOps("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   logicOp INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(logicOp) REFERENCES VkLogicOp(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicRasterizerDiscardEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   rasterizerDiscardEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(rasterizerDiscardEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicPrimitiveRestartEnable("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   primitiveRestartEnable INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(primitiveRestartEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE stateDynamicPatchControlPoints("
        "   stateId INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   patchControlPoints INT NOT NULL,"
        "   FOREIGN KEY(stateId) REFERENCES stateIds(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateIndexes(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE INDEX idxStatePipelineBindingBindPoints\n"
        "    ON statePipelineBindings(stateId, bindPoint)"
    );
}

static void RecordStateTypes(sqlite3* db)
{
    // TODO keep this in sync with StateType enum defined in vulkan_sqlite_consumer_context.h and gfxr-data-service.ts
    ExecSQL(
        db,
        "INSERT INTO stateTypes VALUES"
        "(1, 'PIPELINE_BINDING'),"
        "(2, 'SHADER_OBJECT_BINDING'),"
        "(3, 'DESCRIPTOR_SET_BINDING'),"
        "(4, 'INDEX_BUFFER_BINDING'),"
        "(5, 'VERTEX_BUFFER_BINDING'),"
        "(6, 'VERTEX_INPUT_BINDING_DESCRIPTION'),"
        "(7, 'VERTEX_INPUT_ATTRIBUTE_DESCRIPTION'),"
        "(8, 'VIEWPORT'),"
        "(9, 'SCISSOR'),"
        "(10, 'LINE_WIDTH'),"
        "(11, 'RENDERING_COLOR_ATTACHMENT_LOCATION'),"
        "(12, 'RENDERING_INPUT_COLOR_ATTACHMENT_INDEX'),"
        "(13, 'RENDERING_INPUT_DEPTH_ATTACHMENT_INDEX'),"
        "(14, 'RENDERING_INPUT_STENCIL_ATTACHMENT_INDEX'),"
        "(15, 'DEPTH_BOUNDS'),"
        "(16, 'DEPTH_BOUNDS_TEST_ENABLE'),"
        "(17, 'DEPTH_BIAS'),"
        "(18, 'DEPTH_BIAS_ENABLE'),"
        "(19, 'DEPTH_TEST_ENABLE'),"
        "(20, 'DEPTH_WRITE_ENABLE'),"
        "(21, 'DEPTH_COMPARE_OPS'),"
        "(22, 'STENCIL_COMPARE_MASK_FRONT'),"
        "(23, 'STENCIL_COMPARE_MASK_BACK'),"
        "(24, 'STENCIL_WRITE_MASK_FRONT'),"
        "(25, 'STENCIL_WRITE_MASK_BACK'),"
        "(26, 'STENCIL_REFERENCE_FRONT'),"
        "(27, 'STENCIL_REFERENCE_BACK'),"
        "(28, 'STENCIL_TEST_ENABLE'),"
        "(29, 'STENCIL_OPS_FRONT'),"
        "(30, 'STENCIL_OPS_BACK'),"
        "(31, 'COLOR_WRITE_ENABLE'),"
        "(32, 'BLEND_CONSTANTS'),"
        "(33, 'PRIMITIVE_TOPOLOGY'),"
        "(34, 'CULL_MODE'),"
        "(35, 'FRONT_FACE'),"
        "(36, 'LOGIC_OP'),"
        "(37, 'RASTERIZER_DISCARD_ENABLE'),"
        "(38, 'PATCH_CONTROL_POINTS'),"
        "(39, 'PRIMITIVE_RESTART_ENABLE'),"
        "(40, 'DESCRIPTOR_SET_PUSH'),"
        "(41, 'UNKNOWN');"
    );
}

static void CreateVideoTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE videoSessions("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   queueFamilyIndex INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   videoCodecOperation INT NOT NULL,"
        "   chromaSubsampling INT NOT NULL,"
        "   lumaBitDepth INT NOT NULL,"
        "   chromaBitDepth INT NOT NULL,"
        "   pictureFormat INT NOT NULL,"
        "   maxCodedWidth INT NOT NULL,"
        "   maxCodedHeight INT NOT NULL,"
        "   referencePictureFormat INT NOT NULL,"
        "   maxDpbSlots INT NOT NULL,"
        "   maxActiveReferencePictures INT NOT NULL,"
        "   stdHeaderVersionName TEXT NOT NULL,"
        "   stdHeaderVersionSpecVersion INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(videoCodecOperation) REFERENCES VkVideoCodecOperationFlagBitsKHR(value),"
        "   FOREIGN KEY(chromaSubsampling) REFERENCES VkVideoChromaSubsamplingFlagBitsKHR(value),"
        "   FOREIGN KEY(lumaBitDepth) REFERENCES VkVideoComponentBitDepthFlagBitsKHR(value),"
        "   FOREIGN KEY(chromaBitDepth) REFERENCES VkVideoComponentBitDepthFlagBitsKHR(value),"
        "   FOREIGN KEY(pictureFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(referencePictureFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE videoSessionParameters("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   template INT,"
        "   videoSessionId INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(template)"
        "       REFERENCES videoSessionParameters(id),"
        "   FOREIGN KEY(videoSessionId) REFERENCES videoSessions(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateIndirectCommandsTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE indirectCommandsLayouts("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   shaderStages INT NOT NULL,"
        "   indirectStride INT NOT NULL,"
        "   pipelineLayoutId INT,"
        "   tokenCount INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(pipelineLayoutId) REFERENCES pipelineLayouts(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateMicromapTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE micromaps("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   createFlags INT NOT NULL,"
        "   bufferId INT,"
        "   offset INT NOT NULL,"
        "   size INT NOT NULL,"
        "   type INT NOT NULL,"
        "   deviceAddress INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(bufferId) REFERENCES buffers(id),"
        "   FOREIGN KEY(type) REFERENCES VkMicromapTypeEXT(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateOpticalFlowTables(sqlite3* db)
{
    // Note this is an NV extension but no KHR or EXT exists yet
    // so it does not contain NV postfix
    ExecSQL(
        db,
        "CREATE TABLE opticalFlowSessions("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   imageFormat INT NOT NULL,"
        "   flowVectorFormat INT NOT NULL,"
        "   costFormat INT NOT NULL,"
        "   outputGridSize INT NOT NULL,"
        "   hintGridSize INT NOT NULL,"
        "   performanceLevel INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(imageFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(flowVectorFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(costFormat) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

void CreateAdvancedTables(sqlite3* db)
{
    ExecSQL(db, "BEGIN TRANSACTION");

    CreateDebugTables(db);
    CreateVulkanInstanceTables(db);
    CreateQueueSubmitTables(db);
    CreateQueuePresentTables(db);
    CreateSynchronizationTables(db);
    CreateDescriptorSetTables(db);
    CreateShaderTables(db);
    CreateStateTables(db);
    CreatePipelineTables(db);
    CreateGraphicsPipelineTables(db);
    CreateComputePipelineTables(db);
    CreateRaytracingPipelineTables(db);
    CreateDataGraphPipelineTables(db);
    CreateDisplayTables(db);
    CreateSwapchainTables(db);
    CreateBufferTables(db);
    CreateAccelerationStructureTables(db);
    CreateTransferCommandTables(db);
    CreateDeferredOperationTables(db);
    CreateVideoTables(db);
    CreateIndirectCommandsTables(db);
    CreateMicromapTables(db);
    CreateOpticalFlowTables(db);
    CreateDynamicStateTables(db);

    RecordStateTypes(db);

    CreateIndexes(db);

    ExecSQL(db, "END TRANSACTION");
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)