/********************************************************************************
    Copyright 2024-2025 The Sokatoa Project Authors

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

#include "vulkan_sqlite_consumer_base_tables.h"

#include "sqlite_utils.h"
#include "generated/generated_vulkan_enum_to_sqlite.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)
using namespace util::platform;

static void CreateCoreDataTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE metaData("
        "   key TEXT UNIQUE NOT NULL PRIMARY KEY,"
        "   value TEXT NOT NULL) WITHOUT ROWID, STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE annotations("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   type TEXT NOT NULL,"
        "   label TEXT NOT NULL,"
        "   data TEXT NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE displayMessages("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   frameId INT,"
        "   message TEXT NOT NULL,"
        "   FOREIGN KEY(frameId) REFERENCES frames(id) ON DELETE SET NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE frames("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   beginApiEventId INT NOT NULL,"
        "   endApiEventId INT,"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id) DEFERRABLE INITIALLY DEFERRED,"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE apiEventTypes("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   name TEXT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE functionNames("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   name TEXT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE apiEvents("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventTypeId INT NOT NULL,"
        "   frameId INT,"
        "   functionNameId INT NOT NULL,"
        "   threadId INT NOT NULL,"
        "   FOREIGN KEY(apiEventTypeId) REFERENCES apiEventTypes(id),"
        "   FOREIGN KEY(functionNameId) REFERENCES functionNames(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE apiEventReturns("
        "   apiEventId INT UNIQUE NOT NULL,"
        "   type TEXT NOT NULL,"
        "   value ANY,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE apiEventArguments("
        "   apiEventId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   type TEXT NOT NULL,"
        "   value ANY,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE structs ("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   type TEXT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE structMembers ("
        "   structId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   name TEXT NOT NULL,"
        "   type TEXT NOT NULL,"
        "   value ANY,"
        "   FOREIGN KEY(structId) REFERENCES structs(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE arrays ("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   type TEXT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE arrayMembers ("
        "   arrayId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   type TEXT NOT NULL,"
        "   value ANY,"
        "   FOREIGN KEY(arrayId) REFERENCES arrays(id)) STRICT;"
    );
}

static void CreateVulkanInstanceTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE instances("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   applicationName TEXT,"
        "   applicationVersion INT,"
        "   engineName TEXT,"
        "   engineVersion INT,"
        "   apiVersion INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE physicalDevices("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   instanceId INT,"
        "   enumerateApiEventId INT,"
        "   FOREIGN KEY(instanceId) REFERENCES instances(id),"
        "   FOREIGN KEY(enumerateApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE devices("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   physicalDeviceId INT,"
        "   overallocationBehavior INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(physicalDeviceId) REFERENCES physicalDevices(id),"
        "   FOREIGN KEY(overallocationBehavior) REFERENCES VkMemoryOverallocationBehaviorAMD(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE trackedDeviceCommands("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   deviceId INT NOT NULL,"
        "   frameId INT,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(frameId) REFERENCES frames(id) ON DELETE SET NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateVulkanObjectTables(sqlite3* db)
{
    // TODO Maybe this should be a file? export JSON consumer wrote the blob to disk
    // optionally we could skip the data and not display it to the user, or if we do,
    // as a separate consumer load?
    // Note: There can be multiple load memory commands so we cannot make memoryId
    // unique or primary key which could also have implications to writing data to
    // a file. Offset/Size is used to write into a subset of the memory.
    ExecSQL(
        db,
        "CREATE TABLE memory("
        "   memoryId INT NOT NULL,"
        "   offset INT NOT NULL,"
        "   size INT NOT NULL,"
        "   data BLOB,"
        "   createFrame INT,"
        "   FOREIGN KEY(createFrame) REFERENCES frames(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE surfaces("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   createInfoType INT,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(createInfoType) REFERENCES VkStructureType(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE commandPools("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   queueFamily INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE buffers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   size INT NOT NULL,"
        "   usage INT NOT NULL,"
        "   usage2 INT,"
        "   sharing INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(sharing) REFERENCES VkSharingMode(value),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateCommandBufferTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE commandBuffers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   commandPoolId INT,"
        "   level INT NOT NULL,"
        "   allocateApiEventId INT NOT NULL,"
        "   freeApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(commandPoolId) REFERENCES commandPools(id),"
        "   FOREIGN KEY(level) REFERENCES VkCommandBufferLevel(value),"
        "   FOREIGN KEY(allocateApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(freeApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE commandBufferRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   commandBufferId INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   commandBufferInheritanceInfoId INT,"
        "   beginApiEventId INT NOT NULL,"
        "   endApiEventId INT,"
        "   resetApiEventId INT,"
        "   endStateGroupId INT,"
        "   FOREIGN KEY(commandBufferId) REFERENCES commandBuffers(id),"
        "   FOREIGN KEY(commandBufferInheritanceInfoId) REFERENCES commandBufferInheritanceInfos(id),"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(resetApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE commandBufferInheritanceInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   renderPassId INT,"
        "   subpassIndex INT NOT NULL,"
        "   framebufferId INT,"
        "   occlusionQueryEnable INT NOT NULL,"
        "   queryFlags INT NOT NULL,"
        "   pipelineStatisticsFlags INT NOT NULL,"
        "   FOREIGN KEY(renderPassId) REFERENCES renderPasses(id),"
        "   FOREIGN KEY(framebufferId) REFERENCES framebuffers(id),"
        "   FOREIGN KEY(occlusionQueryEnable) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE commandBufferCommands("
        "   commandBufferRecordingId INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE secondaryCommandBufferExecutionRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   parentCommandBufferRecordingId INT,"
        "   parentRenderPassRecordingId INT,"
        "   parentRenderSubpassRecordingId INT,"
        "   parentDynamicRenderPassRecordingId INT,"
        "   secondaryCommandBufferRecordingId INT,"
        "   idx INT NOT NULL,"
        "   apiEventId INT NOT NULL,"
        "   beginStateGroupId INT NOT NULL,"
        "   endStateGroupId INT NOT NULL,"
        "   FOREIGN KEY(parentCommandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(parentRenderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(parentRenderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(secondaryCommandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id)) STRICT;"
    );
}

static void CreateFramebufferTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE framebuffers("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   handle INT NOT NULL,"
        "   deviceId INT,"
        "   flags INT NOT NULL,"
        "   renderPassId INT,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   layers INT NOT NULL,"
        "   createApiEventId INT NOT NULL,"
        "   destroyApiEventId INT,"
        "   FOREIGN KEY(deviceId) REFERENCES devices(id),"
        "   FOREIGN KEY(renderPassId) REFERENCES renderPasses(id),"
        "   FOREIGN KEY(createApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(destroyApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE framebufferAttachments("
        "   framebufferId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   imageViewId INT,"
        "   framebufferAttachmentInfoId INT,"
        "   FOREIGN KEY(framebufferId) REFERENCES framebuffers(id),"
        "   FOREIGN KEY(imageViewId) REFERENCES imageViews(id),"
        "   FOREIGN KEY(framebufferAttachmentInfoId) REFERENCES framebufferAttachmentInfos(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE framebufferAttachmentInfos("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   flags INT NOT NULL,"
        "   width INT NOT NULL,"
        "   height INT NOT NULL,"
        "   layers INT NOT NULL,"
        "   usage INT NOT NULL) STRICT;"
    );
}

static void CreateRenderPassTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE renderPasses("
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
        "CREATE TABLE renderPassAttachments("
        "   renderPassId INT NOT NULL,"
        "   attachmentIndex INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   format INT NOT NULL,"
        "   samples INT NOT NULL,"
        "   loadOp INT NOT NULL,"
        "   storeOp INT NOT NULL,"
        "   stencilLoadOp INT NOT NULL,"
        "   stencilStoreOp INT NOT NULL,"
        "   initialLayout INT NOT NULL,"
        "   finalLayout INT NOT NULL,"
        "   FOREIGN KEY(format) REFERENCES VkFormat(value),"
        "   FOREIGN KEY(samples) REFERENCES VkSampleCountFlagBits(value),"
        "   FOREIGN KEY(loadOp) REFERENCES VkAttachmentLoadOp(value),"
        "   FOREIGN KEY(storeOp) REFERENCES VkAttachmentStoreOp(value),"
        "   FOREIGN KEY(stencilLoadOp) REFERENCES VkAttachmentLoadOp(value),"
        "   FOREIGN KEY(stencilStoreOp) REFERENCES VkAttachmentStoreOp(value),"
        "   FOREIGN KEY(initialLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(finalLayout) REFERENCES VkImageLayout(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderSubpasses("
        "   renderPassId INT NOT NULL,"
        "   subpassIndex INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   pipelineBindPoint INT NOT NULL,"
        "   FOREIGN KEY(pipelineBindPoint) REFERENCES VkPipelineBindPoint(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderSubpassDependencies("
        "   renderPassId INT NOT NULL,"
        "   srcSubpassIndex INT NOT NULL,"
        "   dstSubpassIndex INT NOT NULL,"
        "   srcStageMask INT NOT NULL,"
        "   dstStageMask INT NOT NULL,"
        "   srcAccessMask INT NOT NULL,"
        "   dstAccessMask INT NOT NULL,"
        "   dependencyFlags INT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderSubpassAttachmentReferences("
        "   renderPassId INT NOT NULL,"
        "   subpassIndex INT NOT NULL,"
        "   attachmentIndex INT NOT NULL,"
        "   inputLayout INT,"
        "   colorLayout INT,"
        "   resolveLayout INT,"
        "   depthStencilLayout INT,"
        "   preserveAttachment INT NOT NULL,"
        "   FOREIGN KEY(inputLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(colorLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(resolveLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(depthStencilLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(preserveAttachment) REFERENCES VkBool32(value)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderPassRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   idx INT NOT NULL,"
        "   renderPassId INT,"
        "   commandBufferRecordingId INT,"
        "   framebufferId INT,"
        "   renderX INT NOT NULL,"
        "   renderY INT NOT NULL,"
        "   renderWidth INT NOT NULL,"
        "   renderHeight INT NOT NULL,"
        "   beginApiEventId INT NOT NULL,"
        "   endApiEventId INT,"
        "   FOREIGN KEY(renderPassId) REFERENCES renderPasses(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(framebufferId) REFERENCES framebuffers(id),"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderPassRecordingClearValues("
        "   renderPassRecordingId INT NOT NULL,"
        "   attachmentIndex INT NOT NULL,"
        "   clearColorId INT,"
        "   clearDepth REAL,"
        "   clearStencil INT,"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(clearColorId) REFERENCES unionColors(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderSubpassRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   renderPassRecordingId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   contents INT NOT NULL,"
        "   beginApiEventId INT NOT NULL,"
        "   endApiEventId INT,"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(contents) REFERENCES VkSubpassContents(value),"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE unionColors("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   floatR REAL," /* Using NULL to represent NaN */
        "   floatG REAL," /* Using NULL to represent NaN */
        "   floatB REAL," /* Using NULL to represent NaN */
        "   floatA REAL," /* Using NULL to represent NaN */
        "   intR INT NOT NULL,"
        "   intG INT NOT NULL,"
        "   intB INT NOT NULL,"
        "   intA INT NOT NULL,"
        "   uintR INT NOT NULL,"
        "   uintG INT NOT NULL,"
        "   uintB INT NOT NULL,"
        "   uintA INT NOT NULL) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE renderingAttachments("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   imageViewId INT,"
        "   imageLayout INT NOT NULL,"
        "   resolveMode INT NOT NULL,"
        "   resolveImageViewId INT,"
        "   resolveImageLayout INT NOT NULL,"
        "   loadOp INT NOT NULL,"
        "   storeOp INT NOT NULL,"
        "   clearColorId INT NOT NULL,"
        "   clearDepth REAL NOT NULL,"
        "   clearStencil INT NOT NULL,"
        "   FOREIGN KEY(imageViewId) REFERENCES imageViews(id),"
        "   FOREIGN KEY(imageLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(resolveImageViewId) REFERENCES imageViews(id),"
        "   FOREIGN KEY(resolveImageLayout) REFERENCES VkImageLayout(value),"
        "   FOREIGN KEY(loadOp) REFERENCES VkAttachmentLoadOp(value),"
        "   FOREIGN KEY(storeOp) REFERENCES VkAttachmentStoreOp(value),"
        "   FOREIGN KEY(clearColorId) REFERENCES unionColors(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE dynamicRenderPassRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   idx INT NOT NULL,"
        "   commandBufferRecordingId INT,"
        "   flags INT,"
        "   renderX INT NOT NULL,"
        "   renderY INT NOT NULL,"
        "   renderWidth INT NOT NULL,"
        "   renderHeight INT NOT NULL,"
        "   layerCount INT NOT NULL,"
        "   viewMask INT NOT NULL,"
        "   depthRenderingAttachmentId INT,"
        "   stencilRenderingAttachmentId INT,"
        "   beginApiEventId INT NOT NULL,"
        "   endApiEventId INT,"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(depthRenderingAttachmentId) REFERENCES renderingAttachments(id),"
        "   FOREIGN KEY(stencilRenderingAttachmentId) REFERENCES renderingAttachments(id),"
        "   FOREIGN KEY(beginApiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(endApiEventId) REFERENCES apiEvents(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE dynamicColorAttachments("
        "   dynamicRenderPassRecordingId INT NOT NULL,"
        "   idx INT NOT NULL,"
        "   renderingAttachmentId INT NOT NULL,"
        "   FOREIGN KEY(dynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id),"
        "   FOREIGN KEY(renderingAttachmentId) REFERENCES renderingAttachments(id)) STRICT;"
    );
}

static void CreateTrackedCmdCommandTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE trackedCmdCommands("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   renderPassRecordingId INT,"
        "   renderSubpassRecordingId INT,"
        "   dynamicRenderPassRecordingId INT,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(renderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(dynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id)) STRICT;"
    );
}

static void CreateCmdDrawRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdDrawRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   renderPassRecordingId INT,"
        "   renderSubpassRecordingId INT,"
        "   dynamicRenderPassRecordingId INT,"
        "   isIndexed INT,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(renderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(dynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDrawRecordingIndirectInfos("
        "   cmdDrawRecordingId INT NOT NULL,"
        "   indirectBuffer INT,"
        "   indirectBufferOffset INT,"
        "   indirectCountBuffer INT,"
        "   indirectCountBufferOffset INT,"
        "   indirectCountOffset INT,"
        "   indirectDrawCount INT,"
        "   indirectMaxDrawCount INT,"
        "   indirectStride INT,"
        "   indirectVertexStride INT,"
        "   FOREIGN KEY(cmdDrawRecordingId) REFERENCES cmdDrawRecordings(id),"
        "   FOREIGN KEY(indirectBuffer) REFERENCES buffers(id),"
        "   FOREIGN KEY(indirectCountBuffer) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDrawRecordingInfos("
        "   cmdDrawRecordingId INT NOT NULL,"
        "   vertexCount INT,"
        "   firstVertex INT,"
        "   vertexOffset INT,"
        "   indexCount INT,"
        "   firstIndex INT,"
        "   instanceCount INT NOT NULL,"
        "   firstInstance INT NOT NULL,"
        "   FOREIGN KEY(cmdDrawRecordingId) REFERENCES cmdDrawRecordings(id)) STRICT;"
    );
}

static void CreateCmdDispatchRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdDispatchRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDispatchRecordingIndirectInfos("
        "   cmdDispatchRecordingId INT NOT NULL,"
        "   indirectBuffer INT,"
        "   indirectBufferOffset INT,"
        "   FOREIGN KEY(cmdDispatchRecordingId) REFERENCES cmdDispatchRecordings(id),"
        "   FOREIGN KEY(indirectBuffer) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDispatchRecordingBaseInfos("
        "   cmdDispatchRecordingId INT NOT NULL,"
        "   baseGroupX INT,"
        "   baseGroupY INT,"
        "   baseGroupZ INT,"
        "   FOREIGN KEY(cmdDispatchRecordingId) REFERENCES cmdDispatchRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDispatchRecordingInfos("
        "   cmdDispatchRecordingId INT NOT NULL,"
        "   groupCountX INT,"
        "   groupCountY INT,"
        "   groupCountZ INT,"
        "   FOREIGN KEY(cmdDispatchRecordingId) REFERENCES cmdDispatchRecordings(id)) STRICT;"
    );
}

static void CreateCmdMeshTaskRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdMeshTaskRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   renderPassRecordingId INT,"
        "   renderSubpassRecordingId INT,"
        "   dynamicRenderPassRecordingId INT,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(renderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(dynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdMeshTaskRecordingIndirectInfos("
        "   cmdMeshTaskRecordingId INT NOT NULL,"
        "   indirectBuffer INT,"
        "   indirectBufferOffset INT NOT NULL,"
        "   indirectCountBuffer INT,"
        "   indirectCountBufferOffset INT,"
        "   indirectDrawCount INT,"
        "   indirectMaxDrawCount INT,"
        "   indirectStride INT NOT NULL,"
        "   FOREIGN KEY(indirectBuffer) REFERENCES buffers(id),"
        "   FOREIGN KEY(indirectCountBuffer) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdMeshTaskRecordingInfos("
        "   cmdMeshTaskRecordingId INT NOT NULL,"
        "   groupCountX INT NOT NULL,"
        "   groupCountY INT NOT NULL,"
        "   groupCountZ INT NOT NULL,"
        "   FOREIGN KEY(cmdMeshTaskRecordingId) REFERENCES cmdMeshTaskRecordings(id)) STRICT;"
    );
}

static void CreateCmdClusterRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdClusterRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   renderPassRecordingId INT,"
        "   renderSubpassRecordingId INT,"
        "   dynamicRenderPassRecordingId INT,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id),"
        "   FOREIGN KEY(renderPassRecordingId) REFERENCES renderPassRecordings(id),"
        "   FOREIGN KEY(renderSubpassRecordingId) REFERENCES renderSubpassRecordings(id),"
        "   FOREIGN KEY(dynamicRenderPassRecordingId) REFERENCES dynamicRenderPassRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdClusterRecordingIndirectInfos("
        "   cmdClusterRecordingId INT NOT NULL,"
        "   indirectBuffer INT,"
        "   indirectBufferOffset INT NOT NULL,"
        "   FOREIGN KEY(cmdClusterRecordingId) REFERENCES cmdClusterRecordings(id),"
        "   FOREIGN KEY(indirectBuffer) REFERENCES buffers(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdClusterRecordingInfos("
        "   cmdClusterRecordingId INT NOT NULL,"
        "   groupCountX INT NOT NULL,"
        "   groupCountY INT NOT NULL,"
        "   groupCountZ INT NOT NULL,"
        "   FOREIGN KEY(cmdClusterRecordingId) REFERENCES cmdClusterRecordings(id)) STRICT;"
    );
}

static void CreateCmdRaytracingRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdRaytracingRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id)) STRICT;"
    );
}

static void CreateCmdDataGraphDispatchRecordingTables(sqlite3* db)
{
    ExecSQL(
        db,
        "CREATE TABLE cmdDataGraphDispatchRecordings("
        "   id INTEGER UNIQUE NOT NULL PRIMARY KEY,"
        "   apiEventId INT NOT NULL,"
        "   dataGraphPipelineSessionId INT,"
        "   stateGroupId INT NOT NULL,"
        "   commandBufferRecordingId INT NOT NULL,"
        "   FOREIGN KEY(apiEventId) REFERENCES apiEvents(id),"
        "   FOREIGN KEY(dataGraphPipelineSessionId) REFERENCES dataGraphPipelineSessions(id),"
        "   FOREIGN KEY(commandBufferRecordingId) REFERENCES commandBufferRecordings(id)) STRICT;"
    );

    ExecSQL(
        db,
        "CREATE TABLE cmdDataGraphDispatchRecordingInfos("
        "   cmdDataGraphDispatchRecordingId INT NOT NULL,"
        "   flags INT NOT NULL,"
        "   FOREIGN KEY(cmdDataGraphDispatchRecordingId) REFERENCES cmdDataGraphDispatchRecordings(id)) STRICT;"
    );
}

void CreateBaseTables(sqlite3* db)
{
    ExecSQL(db, "BEGIN TRANSACTION");

    CreateCoreDataTables(db);
    CreateVulkanInstanceTables(db);
    CreateVulkanObjectTables(db);
    CreateCommandBufferTables(db);
    CreateFramebufferTables(db);
    CreateRenderPassTables(db);
    CreateTrackedCmdCommandTables(db);
    CreateCmdDrawRecordingTables(db);
    CreateCmdDispatchRecordingTables(db);
    CreateCmdMeshTaskRecordingTables(db);
    CreateCmdClusterRecordingTables(db);
    CreateCmdRaytracingRecordingTables(db);
    CreateCmdDataGraphDispatchRecordingTables(db);

    RecordEnums(db);

    ExecSQL(db, "END TRANSACTION");
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
