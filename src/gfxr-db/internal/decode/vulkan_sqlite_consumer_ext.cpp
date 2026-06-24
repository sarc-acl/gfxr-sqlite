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

#ifdef _MSC_VER
// Suppress a false warning on "if (semaphoreType == VK_SEMAPHORE_TYPE_TIMELINE)" in Process_vkCreateSemaphore
// The warning needs to be disabled here before Vulkan headers are included; we can't suppress it in that function.
#pragma warning(disable : 26813)
#endif

#include "vulkan_sqlite_consumer_ext.h"
#include "vulkan_sqlite_consumer_tables.h"

#include "sqlite_utils.h"

#include "vulkan/vulkan.h"

#include "decode/consumer_utils.h"
#include "generated/generated_vulkan_enum_to_string.h"
#include "graphics/vulkan_struct_deep_copy.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>
#include <sstream>
#include <string>
#include <cstdint>
#include <cstring>

// Add the GFXR ID in the log message.
// Example output:
// 2026-02-09T23:39:28.029Z root WARN [gfxrecon] WARNING - SQLite Consumer - <4087>-Failed to find queue, no queue data
#define LOG_CMD_WARNING(message, ...) \
    GFXRECON_SQLITE_LOG_WARNING("<%" PRIu64 ">- " message, call_info.index, ##__VA_ARGS__);
GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

#define CREATE_COMMAND_BUFFER_INSTANCE_ID()                                                                    \
    auto commandBufferRecordingIdOpt = context.GetCommandBufferRecordingId(commandBuffer);                     \
    if (!commandBufferRecordingIdOpt)                                                                          \
    {                                                                                                          \
        LOG_CMD_WARNING(                                                                                       \
            "Null command buffer recording not allowed for command buffer with handle %" PRIu64, commandBuffer \
        );                                                                                                     \
        return;                                                                                                \
    }                                                                                                          \
    auto commandBufferRecordingId = commandBufferRecordingIdOpt.value()

// Requires prior call to CREATE_COMMAND_BUFFER_INSTANCE_ID().
// Declares renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId as std::optional<int64_t>.
#define GET_COMMAND_BUFFER_RENDERPASS_SCOPE()                                                                        \
    std::optional<int64_t> renderPassRecordingId = std::nullopt;                                                     \
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;                                                  \
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;                                              \
    {                                                                                                                \
        auto _rpIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(commandBuffer));         \
        if (_rpIter != context.commandBufferHandleToRenderPassRecordingIdStack.end() && !_rpIter->second.empty())    \
        {                                                                                                            \
            auto _rpTop = _rpIter->second.top();                                                                     \
            renderPassRecordingId = _rpTop;                                                                          \
            auto _subpassIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(_rpTop);                \
            if (_subpassIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())                       \
            {                                                                                                        \
                renderSubpassRecordingId = _subpassIter->second;                                                     \
            }                                                                                                        \
        }                                                                                                            \
        auto _drpIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(commandBuffer)); \
        if (_drpIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end() &&                      \
            !_drpIter->second.empty())                                                                               \
        {                                                                                                            \
            dynamicRenderPassRecordingId = _drpIter->second.top();                                                   \
        }                                                                                                            \
    }

VulkanSqliteConsumerExt::VulkanSqliteConsumerExt(sqlite3* db) : VulkanSqliteConsumer(db)
{
    // base tables created in VulkanSqliteConsumerBase
    CreateAdvancedTables(db);

    // base prepared statements created in VulkanSqliteConsumerBase
    statements.CreateAdvancedPreparedStatements();
}

// special handling override functions

void VulkanSqliteConsumerExt::Process_vkSetDebugUtilsObjectNameEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectNameInfoEXT>* pNameInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkSetDebugUtilsObjectNameEXT(call_info, returnValue, device, pNameInfo);

    auto [nameInfoValid, nameInfo] = GetMetaStructPointer(pNameInfo);
    if (!nameInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to set debug object name, invalid pNameInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(nameInfo->pNext);

    auto objectHandle = ToInt64(static_cast<format::HandleId>(nameInfo->objectHandle));
    auto objectType = nameInfo->decoded_value->objectType;
    std::string objectName = nameInfo->decoded_value->pObjectName ? nameInfo->decoded_value->pObjectName : "";
    statements.InsertDebugName(
        objectName, objectHandle, static_cast<int64_t>(objectType), std::nullopt, device, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkSetDebugUtilsObjectTagEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDebugUtilsObjectTagInfoEXT>* pTagInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkSetDebugUtilsObjectTagEXT(call_info, returnValue, device, pTagInfo);

    auto [tagInfoValid, tagInfo] = GetMetaStructPointer(pTagInfo);
    if (!tagInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to set debug object tag, invalid pTagInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(tagInfo->pNext);

    auto objectHandle = ToInt64(static_cast<format::HandleId>(tagInfo->objectHandle));
    auto objectType = tagInfo->decoded_value->objectType;
    auto tagName = tagInfo->decoded_value->tagName;
    auto tagSize = tagInfo->decoded_value->tagSize;
    // TODO handle binary tag data
    statements.InsertDebugTag(
        tagName, tagSize, objectHandle, static_cast<int64_t>(objectType), std::nullopt, device, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkQueueBeginDebugUtilsLabelEXT(
    const ApiCallInfo& call_info, format::HandleId queue, StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueBeginDebugUtilsLabelEXT(call_info, queue, pLabelInfo);

    auto [labelInfoValid, labelInfo] = GetMetaStructPointer(pLabelInfo);
    if (!labelInfoValid)
    {
        LOG_CMD_WARNING("Failed to begin queue debug label, invalid pLabelInfo struct");
        return;
    }

    LogUnsupportedPNext(labelInfo->pNext);

    auto& color = labelInfo->decoded_value->color;
    std::string name = labelInfo->decoded_value->pLabelName ? labelInfo->decoded_value->pLabelName : "";
    statements.InsertDebugLabelQueueBegin(queue, name, color, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkQueueEndDebugUtilsLabelEXT(const ApiCallInfo& call_info, format::HandleId queue)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueEndDebugUtilsLabelEXT(call_info, queue);

    auto stackIter = context.queueHandleToDebugLabelIdStack.find(ToInt64(queue));
    if (stackIter == context.queueHandleToDebugLabelIdStack.end() || stackIter->second.empty())
    {
        LOG_CMD_WARNING("Failed to end queue debug label, no existing debug label for queue handle %" PRIu64, queue);
        return;
    }
    statements.UpdateDebugLabelEnd(stackIter->second.top(), this->block_index_);
    stackIter->second.pop();
}

void VulkanSqliteConsumerExt::Process_vkQueueInsertDebugUtilsLabelEXT(
    const ApiCallInfo& call_info, format::HandleId queue, StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueInsertDebugUtilsLabelEXT(call_info, queue, pLabelInfo);

    auto [labelInfoValid, labelInfo] = GetMetaStructPointer(pLabelInfo);
    if (!labelInfoValid)
    {
        LOG_CMD_WARNING("Failed to insert queue debug label, invalid pLabelInfo struct");
        return;
    }

    LogUnsupportedPNext(labelInfo->pNext);

    auto& color = labelInfo->decoded_value->color;
    std::string name = labelInfo->decoded_value->pLabelName ? labelInfo->decoded_value->pLabelName : "";
    statements.InsertDebugLabelQueueInsert(queue, name, color, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkCmdBeginDebugUtilsLabelEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBeginDebugUtilsLabelEXT(call_info, commandBuffer, pLabelInfo);

    auto [labelInfoValid, labelInfo] = GetMetaStructPointer(pLabelInfo);
    if (!labelInfoValid)
    {
        LOG_CMD_WARNING("Failed to begin command buffer debug label, invalid pLabelInfo struct");
        return;
    }

    LogUnsupportedPNext(labelInfo->pNext);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto& color = labelInfo->decoded_value->color;
    std::string name = labelInfo->decoded_value->pLabelName ? labelInfo->decoded_value->pLabelName : "";
    statements.InsertDebugLabelCmdBegin(
        name,
        color,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdEndDebugUtilsLabelEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdEndDebugUtilsLabelEXT(call_info, commandBuffer);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();
    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto stackIter = context.commandBufferRecordingToDebugLabelIdStack.find(commandBufferRecordingId);
    if (stackIter != context.commandBufferRecordingToDebugLabelIdStack.end() && !stackIter->second.empty())
    {
        // debug util label found within the same command buffer recording, update end scope data
        statements.UpdateDebugLabelCmdEnd(
            stackIter->second.top(),
            this->block_index_,
            renderPassRecordingId,
            renderSubpassRecordingId,
            dynamicRenderPassRecordingId
        );
        stackIter->second.pop();
    }
    else
    {
        // no begin found in this command buffer, assume cross command buffer debug labeling
        // and insert end debug label entry, this entry will have NULL values for all fields
        // except the scope fields and api event id for the end event.
        // Frontend code will need to handle these partial labels by matching them to the last
        // unresolved partial begin label submitted to the same queue (via a stack).
        // see: https://registry.khronos.org/vulkan/specs/latest/man/html/vkCmdEndDebugUtilsLabelEXT.html
        statements.InsertDebugLabelCmdEndStub(
            commandBufferRecordingId,
            renderPassRecordingId,
            renderSubpassRecordingId,
            dynamicRenderPassRecordingId,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdInsertDebugUtilsLabelEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkDebugUtilsLabelEXT>* pLabelInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdInsertDebugUtilsLabelEXT(call_info, commandBuffer, pLabelInfo);

    auto [labelInfoValid, labelInfo] = GetMetaStructPointer(pLabelInfo);
    if (!labelInfoValid)
    {
        LOG_CMD_WARNING("Failed to insert command buffer debug label, invalid pLabelInfo struct");
        return;
    }

    LogUnsupportedPNext(labelInfo->pNext);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();
    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto& color = labelInfo->decoded_value->color;
    std::string name = labelInfo->decoded_value->pLabelName ? labelInfo->decoded_value->pLabelName : "";
    statements.InsertDebugLabelCmdInsert(
        name,
        color,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDebugMarkerSetObjectTagEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectTagInfoEXT>* pTagInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDebugMarkerSetObjectTagEXT(call_info, returnValue, device, pTagInfo);

    auto [tagInfoValid, tagInfo] = GetMetaStructPointer(pTagInfo);
    if (!tagInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to set debug object tag, invalid pTagInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(tagInfo->pNext);

    auto objectHandle = ToInt64(static_cast<format::HandleId>(tagInfo->object));
    auto objectType = tagInfo->decoded_value->objectType;
    auto tagName = tagInfo->decoded_value->tagName;
    auto tagSize = tagInfo->decoded_value->tagSize;
    // TODO handle binary tag data
    statements.InsertDebugTag(
        tagName, tagSize, objectHandle, std::nullopt, static_cast<int64_t>(objectType), device, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDebugMarkerSetObjectNameEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDebugMarkerObjectNameInfoEXT>* pNameInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDebugMarkerSetObjectNameEXT(call_info, returnValue, device, pNameInfo);

    auto [nameInfoValid, nameInfo] = GetMetaStructPointer(pNameInfo);
    if (!nameInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to set debug object name, invalid pNameInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(nameInfo->pNext);

    auto objectHandle = ToInt64(static_cast<format::HandleId>(nameInfo->object));
    auto objectType = nameInfo->decoded_value->objectType;
    std::string objectName = nameInfo->decoded_value->pObjectName ? nameInfo->decoded_value->pObjectName : "";
    statements.InsertDebugName(
        objectName, objectHandle, std::nullopt, static_cast<int64_t>(objectType), device, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdDebugMarkerBeginEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdDebugMarkerBeginEXT(call_info, commandBuffer, pMarkerInfo);

    auto [markerInfoValid, markerInfo] = GetMetaStructPointer(pMarkerInfo);
    if (!markerInfoValid)
    {
        LOG_CMD_WARNING("Failed to begin command buffer debug label, invalid pMarkerInfo struct");
        return;
    }

    LogUnsupportedPNext(markerInfo->pNext);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();
    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto& color = markerInfo->decoded_value->color;
    std::string markerName = markerInfo->decoded_value->pMarkerName ? markerInfo->decoded_value->pMarkerName : "";
    statements.InsertDebugLabelCmdBegin(
        markerName,
        color,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdDebugMarkerEndEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdDebugMarkerEndEXT(call_info, commandBuffer);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();
    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto stackIter = context.commandBufferRecordingToDebugLabelIdStack.find(commandBufferRecordingId);
    if (stackIter != context.commandBufferRecordingToDebugLabelIdStack.end() && !stackIter->second.empty())
    {
        // debug util label found within the same command buffer recording, update end scope data
        statements.UpdateDebugLabelCmdEnd(
            stackIter->second.top(),
            this->block_index_,
            renderPassRecordingId,
            renderSubpassRecordingId,
            dynamicRenderPassRecordingId
        );
        stackIter->second.pop();
    }
    else
    {
        // no begin found in this command buffer, assume cross command buffer debug labeling
        // and insert end debug label entry, this entry will have NULL values for all fields
        // except the scope fields and api event id for the end event.
        // Frontend code will need to handle these partial labels by matching them to the last
        // unresolved partial begin label submitted to the same queue (via a stack).
        // see: https://registry.khronos.org/vulkan/specs/latest/man/html/vkCmdEndDebugUtilsLabelEXT.html
        statements.InsertDebugLabelCmdEndStub(
            commandBufferRecordingId,
            renderPassRecordingId,
            renderSubpassRecordingId,
            dynamicRenderPassRecordingId,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdDebugMarkerInsertEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkDebugMarkerMarkerInfoEXT>* pMarkerInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdDebugMarkerInsertEXT(call_info, commandBuffer, pMarkerInfo);

    auto [markerInfoValid, markerInfo] = GetMetaStructPointer(pMarkerInfo);
    if (!markerInfoValid)
    {
        LOG_CMD_WARNING("Failed to insert command buffer debug label, invalid pMarkerInfo struct");
        return;
    }

    LogUnsupportedPNext(markerInfo->pNext);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();
    GET_COMMAND_BUFFER_RENDERPASS_SCOPE();

    auto& color = markerInfo->decoded_value->color;
    std::string markerName = markerInfo->decoded_value->pMarkerName ? markerInfo->decoded_value->pMarkerName : "";
    statements.InsertDebugLabelCmdInsert(
        markerName,
        color,
        commandBufferRecordingId,
        renderPassRecordingId,
        renderSubpassRecordingId,
        dynamicRenderPassRecordingId,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateDebugReportCallbackEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId instance,
    StructPointerDecoder<Decoded_VkDebugReportCallbackCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugReportCallbackEXT>* pCallback
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDebugReportCallbackEXT(
        call_info, returnValue, instance, pCreateInfo, pAllocator, pCallback
    );

    auto [callbackValid, callback] = GetHandle(pCallback);
    if (!callbackValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create debug report callback, invalid pCallback handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create debug report callback, invalid pCreateInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto flags = createInfo->decoded_value->flags;

    auto callbackHandle = ToInt64(callback);
    auto callbackId = statements.InsertDebugReportCallback(callbackHandle, flags, this->block_index_);
    context.debugReportCallbackHandleToId[callbackHandle] = callbackId;
}

void VulkanSqliteConsumerExt::Process_vkDestroyDebugReportCallbackEXT(
    const ApiCallInfo& call_info,
    format::HandleId instance,
    format::HandleId callback,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDebugReportCallbackEXT(call_info, instance, callback, pAllocator);

    if (auto id = context.ExtractId(
            callback, context.debugReportCallbackHandleToId, "debug report callback", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyDebugReportCallbackUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDebugUtilsMessengerEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId instance,
    StructPointerDecoder<Decoded_VkDebugUtilsMessengerCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDebugUtilsMessengerEXT>* pMessenger
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDebugUtilsMessengerEXT(
        call_info, returnValue, instance, pCreateInfo, pAllocator, pMessenger
    );

    auto [messengerValid, messenger] = GetHandle(pMessenger);
    if (!messengerValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create debug messenger, invalid pMessenger handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create debug messenger, invalid pCreateInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertDebugMessenger(messenger, ci.messageSeverity, ci.messageType, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyDebugUtilsMessengerEXT(
    const ApiCallInfo& call_info,
    format::HandleId instance,
    format::HandleId messenger,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDebugUtilsMessengerEXT(call_info, instance, messenger, pAllocator);

    if (auto id = context.ExtractId(messenger, context.debugMessengerHandleToId, "debug messenger", this->block_index_))
    {
        statements.DestroyObject(statements.destroyDebugMessengerUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateInstance(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    StructPointerDecoder<Decoded_VkInstanceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkInstance>* pInstance
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateInstance(call_info, returnValue, pCreateInfo, pAllocator, pInstance);

    auto [instanceValid, instance] = GetHandle(pInstance);
    if (!instanceValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create instance, invalid pInstance handle");
        }
        return;
    }

    VkInstanceCreateFlags flags = 0;
    auto applicationName = "";
    uint32_t applicationVersion = 0u;
    auto engineName = "";
    uint32_t engineVersion = 0u;
    uint32_t apiVersion = 0u;

    bool layerSettingsValid = false;
    const Decoded_VkLayerSettingEXT* layerSettings = nullptr;
    uint64_t layerSettingsCount = 0;

    bool enabledValidationFeaturesValid = false;
    const VkValidationFeatureEnableEXT* enabledValidationFeatures = nullptr;
    uint64_t enabledValidationFeaturesCount = 0;

    bool disabledValidationFeaturesValid = false;
    const VkValidationFeatureDisableEXT* disabledValidationFeatures = nullptr;
    uint64_t disabledValidationFeaturesCount = 0;

    bool disabledValidationChecksValid = false;
    const VkValidationCheckEXT* disabledValidationChecks = nullptr;
    uint64_t disabledValidationChecksCount = 0;

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to process instance application info, invalid pCreateInfo struct");
        }
    }
    else
    {
        auto pnext = createInfo->pNext;
        while (pnext != nullptr)
        {
            auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
            if (*header->sType == gfxrecon::util::GetSType<VkLayerSettingsCreateInfoEXT>())
            {
                const auto* pLayerSettingsCreateInfoExt =
                    reinterpret_cast<const Decoded_VkLayerSettingsCreateInfoEXT*>(header);
                std::tie(layerSettingsValid, layerSettings, layerSettingsCount) =
                    GetMetaStructArray(pLayerSettingsCreateInfoExt->pSettings);
            }
            else if (*header->sType == gfxrecon::util::GetSType<VkValidationFeaturesEXT>())
            {
                const auto* pValidationFeaturesExt = reinterpret_cast<const Decoded_VkValidationFeaturesEXT*>(header);
                std::tie(enabledValidationFeaturesValid, enabledValidationFeatures, enabledValidationFeaturesCount) =
                    GetPointerArray(&pValidationFeaturesExt->pEnabledValidationFeatures);
                std::tie(disabledValidationFeaturesValid, disabledValidationFeatures, disabledValidationFeaturesCount) =
                    GetPointerArray(&pValidationFeaturesExt->pDisabledValidationFeatures);
            }
            else if (*header->sType == gfxrecon::util::GetSType<VkValidationFlagsEXT>())
            {
                const auto* pValidationFlagsExt = reinterpret_cast<const Decoded_VkValidationFlagsEXT*>(header);
                std::tie(disabledValidationChecksValid, disabledValidationChecks, disabledValidationChecksCount) =
                    GetPointerArray(&pValidationFlagsExt->pDisabledValidationChecks);
            }
            else
            {
                LogUnsupportedPNext(*header->sType);
            }

            pnext = header->pNext;
        }

        flags = createInfo->decoded_value->flags;
        auto applicationInfo = createInfo->decoded_value->pApplicationInfo;
        if (applicationInfo)
        {
            if (applicationInfo->pApplicationName)
            {
                applicationName = applicationInfo->pApplicationName;
            }
            applicationVersion = applicationInfo->applicationVersion;
            if (applicationInfo->pEngineName)
            {
                engineName = applicationInfo->pEngineName;
            }
            engineVersion = applicationInfo->engineVersion;
            apiVersion = applicationInfo->apiVersion;
        }
    }

    int64_t instanceHandle = ToInt64(instance);
    auto instanceId = statements.InsertInstance(
        this->block_index_,
        instanceHandle,
        flags,
        applicationName,
        applicationVersion,
        engineName,
        engineVersion,
        apiVersion
    );

    if (createInfoValid)
    {
        auto [layerNamesValid, layerNames, layerNamesCount] = GetPointerArray(&createInfo->ppEnabledLayerNames);
        if (layerNamesValid)
        {
            for (size_t i = 0; i < layerNamesCount; ++i)
            {
                auto enabledLayerId = statements.InsertInstanceEnabledLayer(instanceId, layerNames[i]);
                if (layerSettingsValid)
                {
                    for (size_t j = 0; j < layerSettingsCount; ++j)
                    {
                        const VkLayerSettingEXT* setting = layerSettings[j].decoded_value;
                        if (setting == nullptr)
                        {
                            continue;
                        }

                        // Only associate a setting with this layer if its layer name matches.
                        if (setting->pLayerName == nullptr || layerNames[i] == nullptr ||
                            std::strcmp(setting->pLayerName, layerNames[i]) != 0)
                        {
                            continue;
                        }

                        auto settingName = setting->pSettingName != nullptr ? setting->pSettingName : "";
                        auto settingId = statements.InsertInstanceEnabledLayerSetting(
                            enabledLayerId, settingName, static_cast<int64_t>(setting->type)
                        );

                        if (setting->pValues == nullptr)
                        {
                            continue;
                        }

                        // Convert each value to text per the setting's type and store it.
                        for (uint32_t k = 0; k < setting->valueCount; ++k)
                        {
                            std::string value;
                            switch (setting->type)
                            {
                                case VK_LAYER_SETTING_TYPE_BOOL32_EXT:
                                case VK_LAYER_SETTING_TYPE_UINT32_EXT:
                                    value = std::to_string(static_cast<const uint32_t*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_INT32_EXT:
                                    value = std::to_string(static_cast<const int32_t*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_INT64_EXT:
                                    value = std::to_string(static_cast<const int64_t*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_UINT64_EXT:
                                    value = std::to_string(static_cast<const uint64_t*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_FLOAT32_EXT:
                                    value = std::to_string(static_cast<const float*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_FLOAT64_EXT:
                                    value = std::to_string(static_cast<const double*>(setting->pValues)[k]);
                                    break;
                                case VK_LAYER_SETTING_TYPE_STRING_EXT:
                                {
                                    const char* str = static_cast<const char* const*>(setting->pValues)[k];
                                    value = str != nullptr ? str : "";
                                    break;
                                }
                                case VK_LAYER_SETTING_TYPE_MAX_ENUM_EXT:
                                default:
                                    continue;
                            }

                            statements.InsertInstanceEnabledLayerSettingValue(
                                settingId, static_cast<int64_t>(k), value
                            );
                        }
                    }
                }
            }
        }
        auto [extensionNamesValid, extensionNames, extensionNamesCount] =
            GetPointerArray(&createInfo->ppEnabledExtensionNames);
        if (extensionNamesValid)
        {
            for (size_t i = 0; i < extensionNamesCount; ++i)
            {
                statements.InsertInstanceEnabledExtension(instanceId, extensionNames[i]);
            }
        }

        if (enabledValidationFeaturesValid)
        {
            for (size_t i = 0; i < enabledValidationFeaturesCount; ++i)
            {
                statements.InsertInstanceValidationEnabledFeature(
                    instanceId, static_cast<int64_t>(enabledValidationFeatures[i])
                );
            }
        }

        if (disabledValidationFeaturesValid)
        {
            for (size_t i = 0; i < disabledValidationFeaturesCount; ++i)
            {
                statements.InsertInstanceValidationDisabledFeature(
                    instanceId, static_cast<int64_t>(disabledValidationFeatures[i])
                );
            }
        }

        if (disabledValidationChecksValid)
        {
            for (size_t i = 0; i < disabledValidationChecksCount; ++i)
            {
                statements.InsertInstanceValidationDisabledCheck(
                    instanceId, static_cast<int64_t>(disabledValidationChecks[i])
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyInstance(
    const ApiCallInfo& call_info,
    format::HandleId instance,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyInstance(call_info, instance, pAllocator);

    if (auto id = context.ExtractId(instance, context.instanceHandleToId, "instance", this->block_index_))
    {
        statements.DestroyObject(statements.destroyInstanceUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkEnumeratePhysicalDevices(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId instance,
    PointerDecoder<uint32_t>* pPhysicalDeviceCount,
    HandlePointerDecoder<VkPhysicalDevice>* pPhysicalDevices
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkEnumeratePhysicalDevices(
        call_info, returnValue, instance, pPhysicalDeviceCount, pPhysicalDevices
    );

    auto [physicalDevicesValid, physicalDevices, physicalDeviceCount] = GetHandleArray(pPhysicalDevices);
    if (!physicalDevicesValid)
    {
        // first call to vkEnumeratePhysicalDevices is used to query count of devices for
        // future call with pPhysicalDevices array allocated, not an error to be NULL, quietly return
        return;
    }

    std::optional<int64_t> instanceId = std::nullopt;
    auto instanceIter = context.instanceHandleToId.find(ToInt64(instance));
    if (instanceIter == context.instanceHandleToId.end())
    {
        LOG_CMD_WARNING("Failed to find instance for handle %" PRIu64 ", setting foreign key to NULL", instance);
    }
    else
    {
        instanceId = instanceIter->second;
    }

    for (size_t i = 0; i < physicalDeviceCount; ++i)
    {
        auto physicalDevice = physicalDevices[i];
        auto physicalDeviceHandle = ToInt64(physicalDevice);
        statements.InsertPhysicalDevice(physicalDeviceHandle, instanceId, this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDevice(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId physicalDevice,
    StructPointerDecoder<Decoded_VkDeviceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDevice>* pDevice
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDevice(
        call_info, returnValue, physicalDevice, pCreateInfo, pAllocator, pDevice
    );

    auto [handleValid, device] = GetHandle(pDevice);
    if (!handleValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create device, invalid pDevice handle");
        }
        return;
    }

    auto deviceHandle = ToInt64(device);
    auto physicalDeviceId = context.GetPhysicalDeviceId(physicalDevice);
    auto deviceId = statements.InsertDevice(this->block_index_, device, physicalDeviceId);
    std::vector<std::string_view> enabledFeatureNames;

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create device info mappings, invalid pCreateInfo struct");
        }
        return;
    }
    else
    {
        auto [enabledFeaturesValid, enabledFeatures] = GetMetaStructPointer(createInfo->pEnabledFeatures);
        if (enabledFeaturesValid)
        {
            ProcessVkPhysicalDeviceFeatures(enabledFeatures->decoded_value, enabledFeatureNames);
        }

        ProcessVkDeviceCreateInfoPNext(createInfo->pNext, enabledFeatureNames);

        auto [queueCreateInfosValid, queueCreateInfos, queueCreateInfosCount] =
            GetMetaStructArray(createInfo->pQueueCreateInfos);
        if (queueCreateInfosValid)
        {
            for (size_t i = 0; i < queueCreateInfosCount; ++i)
            {
                auto& queueCreateInfo = queueCreateInfos[i];

                LogUnsupportedPNext(queueCreateInfo.pNext);

                auto& familyPrioritiesByFlag =
                    context.deviceHandleToQueuePriority[deviceHandle][queueCreateInfo.decoded_value->queueFamilyIndex];
                if (familyPrioritiesByFlag.contains(queueCreateInfo.decoded_value->flags))
                {
                    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkDeviceCreateInfo.html#VUID-VkDeviceCreateInfo-queueFamilyIndex-02802
                    LOG_CMD_WARNING(
                        "Device info contains multiple VkDeviceQueueCreateInfo entries for family index %d and flags "
                        "%d; ignoring entry at array index %" PRIu64,
                        queueCreateInfo.decoded_value->queueFamilyIndex,
                        queueCreateInfo.decoded_value->flags,
                        i
                    );
                    continue;
                }

                auto& priorities = familyPrioritiesByFlag[queueCreateInfo.decoded_value->flags];
                priorities.reserve(queueCreateInfo.decoded_value->queueCount);
                std::copy_n(
                    queueCreateInfo.decoded_value->pQueuePriorities,
                    queueCreateInfo.decoded_value->queueCount,
                    std::back_inserter(priorities)
                );
            }
        }

        auto [layerNamesValid, layerNames, layerNamesCount] = GetPointerArray(&createInfo->ppEnabledLayerNames);
        if (layerNamesValid)
        {
            for (size_t i = 0; i < layerNamesCount; ++i)
            {
                statements.InsertDeviceEnabledLayer(deviceId, layerNames[i]);
            }
        }
        auto [extensionNamesValid, extensionNames, extensionNamesCount] =
            GetPointerArray(&createInfo->ppEnabledExtensionNames);
        if (extensionNamesValid)
        {
            for (size_t i = 0; i < extensionNamesCount; ++i)
            {
                statements.InsertDeviceEnabledExtension(deviceId, extensionNames[i]);
            }
        }
        for (auto enabledFeatureIter = enabledFeatureNames.begin(); enabledFeatureIter != enabledFeatureNames.end();
             ++enabledFeatureIter)
        {
            statements.InsertDeviceEnabledFeature(deviceId, *enabledFeatureIter);
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyDevice(
    const ApiCallInfo& call_info,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDevice(call_info, device, pAllocator);

    if (auto id = context.ExtractId(device, context.deviceHandleToId, "device", this->block_index_))
    {
        statements.DestroyObject(statements.destroyDeviceUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::ProcessQueue(
    const ApiCallInfo& call_info,
    format::HandleId device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkDeviceQueueCreateFlags flags,
    HandlePointerDecoder<VkQueue>* pQueue
)
{
    auto [queueValid, queue] = GetHandle(pQueue);
    if (!queueValid)
    {
        LOG_CMD_WARNING("Failed to find queue, invalid queue handle");
        return;
    }

    auto queueHandle = ToInt64(queue);
    if (context.queueHandleToId.contains(queueHandle))
    {
        // vkGetDeviceQueue was already called with this queue; we don't need to record it a second time.
        return;
    }

    auto deviceQueueDataIter = context.deviceHandleToQueuePriority.find(ToInt64(device));
    if (deviceQueueDataIter == context.deviceHandleToQueuePriority.end())
    {
        LOG_CMD_WARNING("Failed to find queue, no queue data for device handle %" PRIu64, device);
        return;
    }

    auto familyQueueDataIter = deviceQueueDataIter->second.find(queueFamilyIndex);
    if (familyQueueDataIter == deviceQueueDataIter->second.end())
    {
        LOG_CMD_WARNING(
            "Failed to find queue, no queue data for device handle %" PRIu64 ", family index %d",
            device,
            queueFamilyIndex
        );
        return;
    }

    auto flagsQueueDataIter = familyQueueDataIter->second.find(flags);
    if (flagsQueueDataIter == familyQueueDataIter->second.end())
    {
        LOG_CMD_WARNING(
            "Failed to find queue, no queue data for device handle %" PRIu64 ", family index %d, flags %d",
            device,
            queueFamilyIndex,
            flags
        );
        return;
    }

    const std::vector<float>& priorities = flagsQueueDataIter->second;
    float priority = 0.0;
    if (queueIndex < priorities.size())
    {
        priority = priorities[queueIndex];
    }
    else
    {
        LOG_CMD_WARNING(
            "Failed to find queue priority; queue data for device handle %" PRIu64
            ", family index %d, flags %d has %" PRIu64 " queues but index %d requested; setting priority to 0",
            device,
            queueFamilyIndex,
            flags,
            priorities.size(),
            queueIndex
        );
    }

    statements.InsertQueue(queueHandle, flags, queueFamilyIndex, queueIndex, priority, device);
}

void VulkanSqliteConsumerExt::Process_vkGetDeviceQueue(
    const ApiCallInfo& call_info,
    format::HandleId device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    HandlePointerDecoder<VkQueue>* pQueue
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetDeviceQueue(call_info, device, queueFamilyIndex, queueIndex, pQueue);

    // Per https://registry.khronos.org/vulkan/specs/latest/man/html/vkGetDeviceQueue.html#_description
    // Queues with different flags can share the same queue family index and queue index. vkGetDeviceQueue
    // only ever gets queues with flags set to 0.
    // Per https://registry.khronos.org/vulkan/specs/latest/man/html/VkDeviceQueueInfo2.html#_description
    // some older Vulkan drivers did not handle this correctly.
    ProcessQueue(call_info, device, queueFamilyIndex, queueIndex, 0, pQueue);
}

void VulkanSqliteConsumerExt::Process_vkGetDeviceQueue2(
    const ApiCallInfo& call_info,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDeviceQueueInfo2>* pQueueInfo,
    HandlePointerDecoder<VkQueue>* pQueue
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetDeviceQueue2(call_info, device, pQueueInfo, pQueue);

    auto [queueInfoValid, queueInfo] = GetMetaStructPointer(pQueueInfo);
    if (!queueInfoValid)
    {
        LOG_CMD_WARNING("Failed to create queue, invalid pQueueInfo struct");
        return;
    }

    LogUnsupportedPNext(queueInfo->pNext);

    ProcessQueue(
        call_info,
        device,
        queueInfo->decoded_value->queueFamilyIndex,
        queueInfo->decoded_value->queueIndex,
        queueInfo->decoded_value->flags,
        pQueue
    );
}

void VulkanSqliteConsumerExt::Process_vkQueueSubmit(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId queue,
    uint32_t submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo>* pSubmits,
    format::HandleId fence
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueSubmit(call_info, returnValue, queue, submitCount, pSubmits, fence);

    auto queueIter = context.queueHandleToId.find(ToInt64(queue));
    if (queueIter == context.queueHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create queue submit, no queue found for handle %" PRIu64, queue);
        }
        return;
    }

    std::optional<int64_t> fenceSyncScopeId = std::nullopt;
    if (fence != format::kNullHandleId)
    {
        auto fenceSyncScopeIter = context.fenceHandleToSyncScopeId.find(ToInt64(fence));
        if (fenceSyncScopeIter == context.fenceHandleToSyncScopeId.end())
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to find fence instance for handle %" PRIu64 " setting foreign key to NULL", fence
                );
            }
        }
        else
        {
            fenceSyncScopeId = fenceSyncScopeIter->second;
        }
    }

    auto queueSubmitId =
        statements.InsertQueueSubmit(queueIter->second, fenceSyncScopeId, context.currentFrame, this->block_index_);

    auto [submitInfosValid, submitInfos, submitInfoCount] = GetMetaStructArray(pSubmits);
    if (!submitInfosValid)
    {
        // pSubmits can be NULL when only performing pipeline synchronization
        return;
    }
    for (size_t i = 0; i < submitInfoCount; ++i)
    {
        auto queueSubmitBatchId = statements.InsertQueueSubmitBatch(queueSubmitId, i);

        auto& submitInfo = submitInfos[i];
        auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&submitInfo.pCommandBuffers);
        if (!commandBuffersValid)
        {
            // pCommandBuffers can be NULL when only performing pipeline synchronization
        }
        else
        {
            for (size_t j = 0; j < commandBuffersCount; ++j)
            {
                auto commandBuffer = commandBuffers[j];
                auto commandBufferRecordingId = context.GetCommandBufferRecordingId(commandBuffer);

                statements.InsertQueueSubmitBuffer(queueSubmitBatchId, j, commandBufferRecordingId);
            }
        }

        bool waitValuesValid = false;
        uint64_t* waitValues = nullptr;
        uint64_t waitValuesCount = 0;
        bool signalValuesValid = false;
        uint64_t* signalValues = nullptr;
        uint64_t signalValuesCount = 0;

        auto pnext = submitInfo.pNext;
        while (pnext != nullptr)
        {
            auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
            if (*header->sType == gfxrecon::util::GetSType<VkTimelineSemaphoreSubmitInfo>())
            {
                const auto* pTimelineSemaphoreSubmitInfo =
                    reinterpret_cast<const Decoded_VkTimelineSemaphoreSubmitInfo*>(header);
                std::tie(waitValuesValid, waitValues, waitValuesCount) =
                    GetPointerArray(&pTimelineSemaphoreSubmitInfo->pWaitSemaphoreValues);
                std::tie(signalValuesValid, signalValues, signalValuesCount) =
                    GetPointerArray(&pTimelineSemaphoreSubmitInfo->pSignalSemaphoreValues);
            }
            else
            {
                LogUnsupportedPNext(*header->sType);
            }

            pnext = header->pNext;
        }

        auto [waitSemaphoresValid, waitSemaphores, waitSemaphoresCount] = GetHandleArray(&submitInfo.pWaitSemaphores);
        auto [waitDstStagesValid, waitDstStages, waitDstStagesCount] = GetPointerArray(&submitInfo.pWaitDstStageMask);
        if (waitSemaphoresValid)
        {
            for (size_t j = 0; j < waitSemaphoresCount; ++j)
            {
                auto semaphore = waitSemaphores[j];
                auto semaphoreId = context.GetSemaphoreId(semaphore);

                std::optional<int64_t> stage = std::nullopt;
                if (waitDstStagesValid && j < waitDstStagesCount)
                {
                    stage = static_cast<int64_t>(waitDstStages[j]);
                }

                std::optional<int64_t> value = std::nullopt;
                if (waitValuesValid && j < waitValuesCount)
                {
                    value = static_cast<int64_t>(waitValues[j]);
                }

                statements.InsertQueueSubmitSemaphoreWait(queueSubmitBatchId, j, stage, value, semaphoreId);
            }
        }

        auto [signalSemaphoresValid, signalSemaphores, signalSemaphoresCount] =
            GetHandleArray(&submitInfo.pSignalSemaphores);
        if (signalSemaphoresValid)
        {
            for (size_t j = 0; j < signalSemaphoresCount; ++j)
            {
                auto semaphore = signalSemaphores[j];
                auto semaphoreId = context.GetSemaphoreId(semaphore);

                std::optional<int64_t> value = std::nullopt;
                if (signalValuesValid && j < signalValuesCount)
                {
                    value = static_cast<int64_t>(signalValues[j]);
                }

                statements.InsertQueueSubmitSemaphoreSignal(queueSubmitBatchId, j, value, semaphoreId);
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessQueueSubmit2Info(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId queue,
    uint32_t submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId fence
)
{
    auto queueIter = context.queueHandleToId.find(ToInt64(queue));
    if (queueIter == context.queueHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create queue submit, no queue found for handle %" PRIu64, queue);
        }
        return;
    }

    std::optional<int64_t> fenceSyncScopeId = std::nullopt;
    if (fence != format::kNullHandleId)
    {
        auto fenceSyncScopeIter = context.fenceHandleToSyncScopeId.find(ToInt64(fence));
        if (fenceSyncScopeIter == context.fenceHandleToSyncScopeId.end())
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to find fence instance for handle %" PRIu64 " setting foreign key to NULL", fence
                );
            }
        }
        else
        {
            fenceSyncScopeId = fenceSyncScopeIter->second;
        }
    }

    auto queueSubmitId =
        statements.InsertQueueSubmit(queueIter->second, fenceSyncScopeId, context.currentFrame, this->block_index_);

    auto [submitInfosValid, submitInfos, submitInfoCount] = GetMetaStructArray(pSubmits);
    if (!submitInfosValid)
    {
        // pSubmits can be NULL when only performing pipeline synchronization
        return;
    }
    for (size_t i = 0; i < submitInfoCount; ++i)
    {
        auto queueSubmitBatchId = statements.InsertQueueSubmitBatch(queueSubmitId, i);

        // TODO: handle flags (somewhat complicated, as VkSubmitInfo doesn't have flags but instead uses
        // VkProtectedSubmitInfo in the pNext chain)
        auto& submitInfo = submitInfos[i];

        LogUnsupportedPNext(submitInfo.pNext);

        auto [commandBufferInfosValid, commandBufferInfos, commandBufferInfosCount] =
            GetMetaStructArray(submitInfo.pCommandBufferInfos);
        if (!commandBufferInfosValid)
        {
            // pCommandBuffers can be NULL when only performing pipeline synchronization
        }
        else
        {
            for (size_t j = 0; j < commandBufferInfosCount; ++j)
            {
                auto& commandBufferInfo = commandBufferInfos[j];
                auto commandBufferRecordingId = context.GetCommandBufferRecordingId(commandBufferInfo.commandBuffer);

                statements.InsertQueueSubmitBuffer(queueSubmitBatchId, j, commandBufferRecordingId);
            }
        }

        auto [waitSemaphoreInfosValid, waitSemaphoreInfos, waitSemaphoreInfosCount] =
            GetMetaStructArray(submitInfo.pWaitSemaphoreInfos);
        if (waitSemaphoreInfosValid)
        {
            for (size_t j = 0; j < waitSemaphoreInfosCount; ++j)
            {
                auto& semaphoreInfo = waitSemaphoreInfos[j];

                LogUnsupportedPNext(semaphoreInfo.pNext);

                auto semaphoreId = context.GetSemaphoreId(semaphoreInfo.semaphore);

                auto stage = static_cast<int64_t>(semaphoreInfo.decoded_value->stageMask);
                auto value = static_cast<int64_t>(semaphoreInfo.decoded_value->value);
                statements.InsertQueueSubmitSemaphoreWait(queueSubmitBatchId, j, stage, value, semaphoreId);
            }
        }

        auto [signalSemaphoreInfosValid, signalSemaphoreInfos, signalSemaphoreInfosCount] =
            GetMetaStructArray(submitInfo.pSignalSemaphoreInfos);
        if (signalSemaphoreInfosValid)
        {
            for (size_t j = 0; j < signalSemaphoreInfosCount; ++j)
            {
                auto& semaphoreInfo = signalSemaphoreInfos[j];

                LogUnsupportedPNext(semaphoreInfo.pNext);

                auto semaphoreId = context.GetSemaphoreId(semaphoreInfo.semaphore);

                auto value = static_cast<int64_t>(semaphoreInfo.decoded_value->value);
                statements.InsertQueueSubmitSemaphoreSignal(queueSubmitBatchId, j, value, semaphoreId);
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkQueueSubmit2(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId queue,
    uint32_t submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId fence
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueSubmit2(call_info, returnValue, queue, submitCount, pSubmits, fence);

    ProcessQueueSubmit2Info(call_info, returnValue, queue, submitCount, pSubmits, fence);
}

void VulkanSqliteConsumerExt::Process_vkQueueSubmit2KHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId queue,
    uint32_t submitCount,
    StructPointerDecoder<Decoded_VkSubmitInfo2>* pSubmits,
    format::HandleId fence
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueueSubmit2KHR(call_info, returnValue, queue, submitCount, pSubmits, fence);

    ProcessQueueSubmit2Info(call_info, returnValue, queue, submitCount, pSubmits, fence);
}

void VulkanSqliteConsumerExt::Process_vkQueuePresentKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId queue,
    StructPointerDecoder<Decoded_VkPresentInfoKHR>* pPresentInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkQueuePresentKHR(call_info, returnValue, queue, pPresentInfo);

    auto queueIter = context.queueHandleToId.find(ToInt64(queue));
    if (queueIter == context.queueHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create queue debug label, no queue found for handle %" PRIu64, queue);
        }
        return;
    }

    auto presentId = statements.InsertQueuePresent(queueIter->second, context.currentFrame, this->block_index_);

    auto [presentInfoValid, presentInfo] = GetMetaStructPointer(pPresentInfo);
    if (!presentInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create additional queue queuePresentId info, invalid pPresentInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(presentInfo->pNext);

    auto [semaphoreWaitsValid, semaphoreWaits, semaphoreWaitsCount] = GetHandleArray(&presentInfo->pWaitSemaphores);
    if (semaphoreWaitsValid)
    {
        for (size_t i = 0; i < semaphoreWaitsCount; ++i)
        {
            auto semaphore = semaphoreWaits[i];
            auto semaphoreId = context.GetSemaphoreId(semaphore);
            statements.InsertQueuePresentSemaphoreWait(presentId, i, semaphoreId);
        }
    }

    auto [swapchainsValid, swapchains, swapchainsCount] = GetHandleArray(&presentInfo->pSwapchains);
    auto imageIndices = presentInfo->pImageIndices.GetPointer();
    if (swapchainsValid && imageIndices != nullptr)
    {
        for (size_t i = 0; i < swapchainsCount; ++i)
        {
            auto swapchain = swapchains[i];
            auto swapchainId = context.GetSwapchainId(swapchain, true);
            auto imageIndex = imageIndices[i];
            statements.InsertQueuePresentSwapchain(presentId, swapchainId, imageIndex);
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateFence(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkFenceCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFence>* pFence
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateFence(call_info, returnValue, device, pCreateInfo, pAllocator, pFence);

    auto [fenceValid, fence] = GetHandle(pFence);
    if (!fenceValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create fence, invalid pFence");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create fence, invalid pCreateInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto flags = createInfo->decoded_value->flags;

    auto fenceId = statements.InsertFence(fence, device, flags, this->block_index_);

    statements.InsertFenceSyncScope(ToInt64(fence), fenceId, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyFence(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId fence,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyFence(call_info, device, fence, pAllocator);

    if (auto id = context.ExtractId(fence, context.fenceHandleToId, "fence", this->block_index_))
    {
        statements.DestroyObject(statements.destroyFenceUpdateStatement, this->block_index_, *id);
        context.ExtractId(fence, context.fenceHandleToSyncScopeId, "fence instance", this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_vkResetFences(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    uint32_t fenceCount,
    HandlePointerDecoder<VkFence>* pFences
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkResetFences(call_info, returnValue, device, fenceCount, pFences);

    auto [fencesValid, fences, fencesCount] = GetHandleArray(pFences);
    if (!fencesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to reset fences, invalid pFences array");
        }
        return;
    }

    for (size_t i = 0; i < fencesCount; ++i)
    {
        // update the old fence instance
        auto fence = fences[i];
        if (auto fenceSyncScopeId =
                context.ExtractId(fence, context.fenceHandleToSyncScopeId, "fence instance", this->block_index_))
        {
            statements.ResetFenceSyncScope(*fenceSyncScopeId, this->block_index_);
        }

        // create a new fence instance
        auto fenceHandle = ToInt64(fence);
        auto fenceId = context.GetFenceId(fence, returnValue != VK_SUCCESS);
        if (!fenceId)
        {
            return;
        }
        statements.InsertFenceSyncScope(fenceHandle, *fenceId, this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_vkWaitForFences(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    uint32_t fenceCount,
    HandlePointerDecoder<VkFence>* pFences,
    VkBool32 waitAll,
    uint64_t timeout
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkWaitForFences(
        call_info, returnValue, device, fenceCount, pFences, waitAll, timeout
    );

    auto [fencesValid, fences, fencesCount] = GetHandleArray(pFences);
    if (!fencesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to wait for fences, invalid pFences array");
        }
        return;
    }

    for (size_t i = 0; i < fencesCount; ++i)
    {
        // update the old fence instance
        auto fence = fences[i];
        if (auto fenceSyncScopeId = context.GetFenceSyncScopeId(fence))
        {
            statements.WaitFenceSyncScope(*fenceSyncScopeId, this->block_index_);
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateSemaphore(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSemaphore>* pSemaphore
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSemaphore(
        call_info, returnValue, device, pCreateInfo, pAllocator, pSemaphore
    );

    auto [semaphoreValid, semaphore] = GetHandle(pSemaphore);
    if (!semaphoreValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore, invalid pSemaphore");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore, invalid pCreateInfo struct");
        }
        return;
    }

    auto semaphoreType = VK_SEMAPHORE_TYPE_BINARY;
    uint64_t initialValue = 0;

    auto pnext = createInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkSemaphoreTypeCreateInfo>())
        {
            const auto* pSemaphoreCreateInfo = reinterpret_cast<const Decoded_VkSemaphoreTypeCreateInfo*>(header);
            semaphoreType = pSemaphoreCreateInfo->decoded_value->semaphoreType;
            initialValue = pSemaphoreCreateInfo->decoded_value->initialValue;
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    auto semaphoreId = statements.InsertSemaphore(semaphore, device, semaphoreType, initialValue, this->block_index_);

    // This line incorrectly generates warning C26813 "Use 'bitwise and' to check if a flag is set" unless it is
    // suppressed before Vulkan headers are included. VkSemaphoreType is not a bit flag enum (it just only has members
    // with values 0 and 1)
    if (semaphoreType == VK_SEMAPHORE_TYPE_TIMELINE)
    {
        statements.InsertSemaphoreSignal(semaphoreId, initialValue, this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroySemaphore(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId semaphore,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroySemaphore(call_info, device, semaphore, pAllocator);

    if (auto id = context.ExtractId(semaphore, context.semaphoreHandleToId, "semaphore", this->block_index_))
    {
        statements.DestroyObject(statements.destroySemaphoreUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_VkSemaphoreWaitInfo(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t timeout
)
{
    auto [waitInfoValid, waitInfo] = GetMetaStructPointer(pWaitInfo);
    if (!waitInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore wait, invalid pWaitInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(waitInfo->pNext);

    auto [semaphoresValid, semaphores, semaphoresCount] = GetHandleArray(&waitInfo->pSemaphores);
    if (!semaphoresValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore wait, invalid pSemaphores array");
        }
        return;
    }

    auto [valuesValid, values, valuesCount] = GetPointerArray(&waitInfo->pValues);
    if (!valuesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore wait, invalid pValues array");
        }
        return;
    }

    for (size_t i = 0; i < semaphoresCount; ++i)
    {
        auto semaphore = semaphores[i];
        // TODO: waitFlags corresponds to info about this specific wait call, not the specific semaphore; storing it in
        // semaphoreWaits may not make sense
        auto waitFlags = waitInfo->decoded_value->flags;

        // pValues may have fewer elements than pSemaphores (e.g. binary semaphores with NULL pValues decoded as
        // single element), so guard against OOB access
        const auto value = (i < valuesCount) ? values[i] : uint64_t(0);

        statements.InsertSemaphoreWait(semaphore, value, i, waitFlags, timeout, this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_VkSemaphoreSignalInfo(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
)
{
    auto [signalInfoValid, signalInfo] = GetMetaStructPointer(pSignalInfo);
    if (!signalInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create semaphore signal, invalid pSignal struct");
        }
        return;
    }

    LogUnsupportedPNext(signalInfo->pNext);

    auto semaphore = signalInfo->semaphore;
    auto semaphoreId = context.GetSemaphoreId(semaphore);

    auto value = signalInfo->decoded_value->value;

    statements.InsertSemaphoreSignal(semaphoreId, value, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkWaitSemaphores(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t timeout
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkWaitSemaphores(call_info, returnValue, device, pWaitInfo, timeout);

    Process_VkSemaphoreWaitInfo(call_info, returnValue, device, pWaitInfo, timeout);
}

void VulkanSqliteConsumerExt::Process_vkSignalSemaphore(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkSignalSemaphore(call_info, returnValue, device, pSignalInfo);

    Process_VkSemaphoreSignalInfo(call_info, returnValue, device, pSignalInfo);
}

void VulkanSqliteConsumerExt::Process_vkWaitSemaphoresKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreWaitInfo>* pWaitInfo,
    uint64_t timeout
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkWaitSemaphoresKHR(call_info, returnValue, device, pWaitInfo, timeout);

    Process_VkSemaphoreWaitInfo(call_info, returnValue, device, pWaitInfo, timeout);
}

void VulkanSqliteConsumerExt::Process_vkSignalSemaphoreKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSemaphoreSignalInfo>* pSignalInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkSignalSemaphoreKHR(call_info, returnValue, device, pSignalInfo);

    Process_VkSemaphoreSignalInfo(call_info, returnValue, device, pSignalInfo);
}

void VulkanSqliteConsumerExt::Process_vkCreateEvent(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkEventCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkEvent>* pEvent
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateEvent(call_info, returnValue, device, pCreateInfo, pAllocator, pEvent);

    auto [eventValid, event] = GetHandle(pEvent);
    if (!eventValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create event, invalid pEvent");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create event, invalid pCreateInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto flags = createInfo->decoded_value->flags;
    statements.InsertEvent(event, device, flags, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyEvent(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId event,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyEvent(call_info, device, event, pAllocator);

    if (auto id = context.ExtractId(event, context.eventHandleToId, "event", this->block_index_))
    {
        statements.DestroyObject(statements.destroyEventUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateQueryPool(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkQueryPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkQueryPool>* pQueryPool
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateQueryPool(
        call_info, returnValue, device, pCreateInfo, pAllocator, pQueryPool
    );

    auto [queryPoolValid, queryPool] = GetHandle(pQueryPool);
    if (!queryPoolValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create query pool, invalid pQueryPool");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create query pool, invalid pCreateInfo struct");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertQueryPool(
        queryPool, device, ci.flags, ci.queryType, ci.queryCount, ci.pipelineStatistics, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyQueryPool(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId queryPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyQueryPool(call_info, device, queryPool, pAllocator);

    if (auto id = context.ExtractId(queryPool, context.queryPoolHandleToId, "queryPool", this->block_index_))
    {
        statements.DestroyObject(statements.destroyQueryPoolUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateShadersEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkShaderCreateInfoEXT>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkShaderEXT>* pShaders
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateShadersEXT(
        call_info, returnValue, device, createInfoCount, pCreateInfos, pAllocator, pShaders
    );

    auto [shadersValid, shaders, shadersCount] = GetHandleArray(pShaders);
    if (!shadersValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create shader objects, invalid pShaders array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create shader objects, invalid pCreateInfos struct array");
        }
        return;
    }

    for (size_t i = 0; i < createInfosCount; ++i)
    {
        if (shadersCount <= i)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING("Failed to create shader object, invalid pShaders count");
            }
            return;
        }

        auto& createInfo = createInfos[i];

        LogUnsupportedPNext(createInfo.pNext);

        auto flags = createInfo.decoded_value->flags;
        auto stage = createInfo.decoded_value->stage;
        auto nextStage = createInfo.decoded_value->nextStage;
        auto codeType = createInfo.decoded_value->codeType;
        auto codeSize = createInfo.decoded_value->codeSize;
        auto entryPointName = createInfo.decoded_value->pName;

        auto shader = shaders[i];
        auto shaderObjectId = statements.InsertShaderObject(
            shader, device, flags, stage, nextStage, codeType, codeSize, entryPointName, this->block_index_
        );

        auto [layoutsValid, layouts, layoutsCount] = GetHandleArray(&createInfo.pSetLayouts);
        if (!layoutsValid)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING("Failed to create shader object descriptor set layout, invalid pSetLayouts array");
            }
        }
        else
        {
            for (size_t j = 0; j < layoutsCount; ++j)
            {
                auto layout = layouts[j];
                auto layoutId = context.GetDescriptorSetLayoutId(layout);

                statements.InsertShaderObjectDescriptorSetLayout(shaderObjectId, j, layoutId);
            }
        }

        auto [pushConstantRangesValid, pushConstantRanges, pushConstantRangesCount] =
            GetMetaStructArray(createInfo.pPushConstantRanges);
        if (!pushConstantRangesValid)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to create shader object push constant ranges, invalid pPushConstantRanges array"
                );
            }
        }
        else
        {
            for (size_t j = 0; j < pushConstantRangesCount; ++j)
            {
                auto& range = pushConstantRanges[j];
                auto stageFlags = range.decoded_value->stageFlags;
                auto offset = range.decoded_value->offset;
                auto size = range.decoded_value->size;

                statements.InsertShaderObjectPushConstantRange(shaderObjectId, j, stageFlags, offset, size);
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyShaderEXT(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId shader,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyShaderEXT(call_info, device, shader, pAllocator);

    if (auto id = context.ExtractId(shader, context.shaderObjectHandleToId, "shader", this->block_index_))
    {
        statements.DestroyObject(statements.destroyShaderObjectUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateShaderModule(
    const gfxrecon::decode::ApiCallInfo& call_info,
    VkResult returnValue,
    gfxrecon::format::HandleId device,
    gfxrecon::decode::StructPointerDecoder<gfxrecon::decode::Decoded_VkShaderModuleCreateInfo>* pCreateInfo,
    gfxrecon::decode::StructPointerDecoder<gfxrecon::decode::Decoded_VkAllocationCallbacks>* pAllocator,
    gfxrecon::decode::HandlePointerDecoder<VkShaderModule>* pShaderModule
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateShaderModule(
        call_info, returnValue, device, pCreateInfo, pAllocator, pShaderModule
    );

    auto [shaderModuleValid, shaderModule] = GetHandle(pShaderModule);
    if (!shaderModuleValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create shader module, invalid pShaderModule");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create shader module, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto codeSize = createInfo->decoded_value->codeSize;

    statements.InsertShaderModule(shaderModule, device, codeSize, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyShaderModule(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId shaderModule,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyShaderModule(call_info, device, shaderModule, pAllocator);

    if (auto id = context.ExtractId(shaderModule, context.shaderModuleHandleToId, "shaderModule", this->block_index_))
    {
        statements.DestroyObject(statements.destroyShaderModuleUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateValidationCacheEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkValidationCacheCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkValidationCacheEXT>* pValidationCache
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateValidationCacheEXT(
        call_info, returnValue, device, pCreateInfo, pAllocator, pValidationCache
    );

    auto [validationCacheValid, validationCache] = GetHandle(pValidationCache);
    if (!validationCacheValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create validation cache, invalid pValidationCache");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create validation cache, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto initialDataSize = createInfo->decoded_value->initialDataSize;

    statements.InsertValidationCache(validationCache, device, initialDataSize, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyValidationCacheEXT(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId validationCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyValidationCacheEXT(call_info, device, validationCache, pAllocator);

    if (auto id = context.ExtractId(
            validationCache, context.validationCacheHandleToId, "validationCache", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyValidationCacheUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreatePipelineCache(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPipelineCacheCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipelineCache>* pPipelineCache
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreatePipelineCache(
        call_info, returnValue, device, pCreateInfo, pAllocator, pPipelineCache
    );

    auto [pipelineCacheValid, pipelineCache] = GetHandle(pPipelineCache);
    if (!pipelineCacheValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline cache, invalid pPipelineCache");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline cache, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    // TODO need to figure out how to pack the custom structs into the db
    // we may not need the cache data
    // See original vulkan_json_consumer_base.cpp handling for reference

    statements.InsertPipelineCache(pipelineCache, device, ci.flags, ci.initialDataSize, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyPipelineCache(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId pipelineCache,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPipelineCache(call_info, device, pipelineCache, pAllocator);

    if (auto id =
            context.ExtractId(pipelineCache, context.pipelineCacheHandleToId, "pipelineCache", this->block_index_))
    {
        statements.DestroyObject(statements.destroyPipelineCacheUpdateStatement, this->block_index_, *id);
    }
}

std::optional<int64_t> VulkanSqliteConsumerExt::GetBasePipelineId(
    VkResult returnValue,
    const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
    const format::HandleId* pipelines,
    size_t currentPipelineIndex
)
{
    std::optional<int64_t> basePipelineId = std::nullopt;

    if (createInfo.decoded_value->flags & VK_PIPELINE_CREATE_DERIVATIVE_BIT)
    {
        auto basePipelineHandle = createInfo.basePipelineHandle;
        if (basePipelineHandle == format::kNullHandleId)
        {
            if (createInfo.decoded_value->basePipelineIndex < 0)
            {
                if (returnValue == VK_SUCCESS)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is out of range, "
                        "setting foreign key to NULL",
                        createInfo.decoded_value->basePipelineIndex
                    );
                }
            }
            else if (static_cast<size_t>(createInfo.decoded_value->basePipelineIndex) >= currentPipelineIndex)
            {
                if (returnValue == VK_SUCCESS)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is for a "
                        "non-created pipeline at index %" PRIu64 ", setting foreign key to NULL",
                        createInfo.decoded_value->basePipelineIndex,
                        currentPipelineIndex
                    );
                }
            }
            else
            {
                basePipelineHandle = pipelines[createInfo.decoded_value->basePipelineIndex];
            }
        }
        else if (returnValue == VK_SUCCESS && createInfo.decoded_value->basePipelineIndex != -1)
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Derivative pipeline has both basePipelineHandle and basePipelineIndex "
                "set; using basePipelineHandle"
            );
        }

        if (basePipelineHandle != format::kNullHandleId)
        {
            auto basePipelineIter = context.pipelineHandleToId.find(ToInt64(basePipelineHandle));
            if (basePipelineIter == context.pipelineHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find base pipeline with handle %" PRIu64 ", setting foreign key to NULL",
                    basePipelineHandle
                );
            }
            else
            {
                basePipelineId = basePipelineIter->second;
            }
        }
    }

    return basePipelineId;
}

std::unordered_map<VkGraphicsPipelineLibraryFlagBitsEXT, VulkanSqliteConsumerExt::LibraryInfo>
VulkanSqliteConsumerExt::GetPipelineLibraryInfo(
    format::HandleId pipelineHandle, size_t libraryCount, const format::HandleId* libraryHandles
)
{
    std::unordered_map<VkGraphicsPipelineLibraryFlagBitsEXT, VulkanSqliteConsumerExt::LibraryInfo> libraries;

    for (uint64_t libraryIndex = 0; libraryIndex < libraryCount; libraryIndex++)
    {
        auto libraryPipelineIter = context.pipelineHandleToId.find(ToInt64(libraryHandles[libraryIndex]));
        if (libraryPipelineIter == context.pipelineHandleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to find library pipeline with handle %" PRIu64 "; ignoring", libraryHandles[libraryIndex]
            );
            continue;
        }

        std::ostringstream libraryLookupSql;
        libraryLookupSql << "SELECT flags, libraryFlags, renderPassId\n"
                         << "FROM pipelines LEFT JOIN graphicsPipelineInfos\n"
                            "ON pipelines.id = graphicsPipelineInfos.pipelineId\n"
                         << "WHERE pipelines.id = " << libraryPipelineIter->second << ";";
        auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

        if (results.size() != 1 || results[0].size() != 3)
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to look up library pipeline with handle %" PRIu64 "; ignoring", libraryHandles[libraryIndex]
            );
            continue;
        }

        LibraryInfo info{};
        info.pipelineHandle = libraryHandles[libraryIndex];
        info.pipelineId = libraryPipelineIter->second;
        if (const sqlite3_int64* flags = std::get_if<sqlite3_int64>(&results[0][0]))
        {
            info.flags = static_cast<VkPipelineCreateFlagBits2>(*flags);
        }
        else
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to look up library pipeline flags with handle %" PRIu64 "; ignoring",
                libraryHandles[libraryIndex]
            );
            continue;
        }
        if (const sqlite3_int64* libraryFlags = std::get_if<sqlite3_int64>(&results[0][1]))
        {
            info.libraryFlags = static_cast<VkGraphicsPipelineLibraryFlagsEXT>(*libraryFlags);
        }
        else
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to look up library pipeline library flags with handle %" PRIu64 "; ignoring",
                libraryHandles[libraryIndex]
            );
            continue;
        }
        if (const sqlite3_int64* renderPass = std::get_if<sqlite3_int64>(&results[0][2]))
        {
            info.renderPass = static_cast<int64_t>(*renderPass);
        }
        else if (std::holds_alternative<std::nullptr_t>(results[0][2]))
        {
            info.renderPass = std::nullopt;
        }
        else
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to look up library pipeline render pass with handle %" PRIu64 "; ignoring",
                libraryHandles[libraryIndex]
            );
            continue;
        }

        for (auto libraryFlag : { VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT,
                                  VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT,
                                  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT,
                                  VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT })
        {
            if (info.libraryFlags & libraryFlag)
            {
                if (libraries.contains(libraryFlag))
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Pipeline with handle %" PRIu64 " has flag %u on both library %" PRIu64 " and %" PRIu64
                        "; ignoring second",
                        pipelineHandle,
                        libraries[libraryFlag].pipelineHandle,
                        libraryHandles[libraryIndex]
                    );
                    continue;
                }
                else
                {
                    libraries.emplace(libraryFlag, info);
                }
            }
        }
    }

    return libraries;
}

// https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-dynamic-state
// The spec is somewhat vague about how dynamic states work with pipeline libraries, saying that dynamic states that are
// "not otherwise statically set by one of the state subsets used to create the pipeline" must be ignored. It doesn't
// provide a list of dynamic states that correspond to each state subset. I did find 3 implementations, though each one
// is slightly different:
// https://github.com/GPUOpen-Drivers/xgl/blob/f1409335d242ba9007b108f10a8c5bdb7372e275/icd/api/graphics_pipeline_common.cpp#L46-L180
// (+https://github.com/GPUOpen-Drivers/xgl/blob/f1409335d242ba9007b108f10a8c5bdb7372e275/icd/api/graphics_pipeline_common.cpp#L451-L487)
// https://github.com/KhronosGroup/VK-GL-CTS/blob/69ec1790cb7c1b72a758a3562aa4e511caaef780/external/vulkancts/framework/vulkan/vkPipelineConstructionUtil.cpp#L2194-L2335
// https://github.com/KhronosGroup/Vulkan-ValidationLayers/blob/9ff27ff9e3652dc0d13cc6c48dd1c8e2253afaec/layers/state_tracker/pipeline_state.cpp#L219-L369
//
// This is not addressed by the original proposal, either:
// https://github.com/KhronosGroup/Vulkan-Docs/blob/main/proposals/VK_EXT_graphics_pipeline_library.adoc
//
// An additional complication is that the spec states that "Any linked library that has dynamic state enabled that same
// dynamic state must also be enabled in all the other linked libraries to which that dynamic state applies." This does
// not appear to be enforced by any validation rule currently, and the different implementations disagree as to what
// dynamic states apply to multiple pipeline state subsets. We handle this by treating a state dynamic state as enabled
// if it is enabled in any of the linked libraries.
//
// See spec issue at https://github.com/KhronosGroup/Vulkan-Docs/issues/2504
static const std::unordered_set<VkDynamicState> VERTEX_INPUT_DYNAMIC_STATES{
    VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE,
    VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY,
    VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE,
    VK_DYNAMIC_STATE_VERTEX_INPUT_EXT
};
static const std::unordered_set<VkDynamicState> PRE_RASTERIZATION_SHADERS_DYNAMIC_STATES{
    // Only listed here in Vulkan-ValidationLayers. Also listed in fragment shader and fragment output
    VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT,
    VK_DYNAMIC_STATE_CONSERVATIVE_RASTERIZATION_MODE_EXT,
    VK_DYNAMIC_STATE_CULL_MODE,
    VK_DYNAMIC_STATE_DEPTH_BIAS,
    VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE,
    VK_DYNAMIC_STATE_DEPTH_CLAMP_ENABLE_EXT,
    VK_DYNAMIC_STATE_DEPTH_CLAMP_RANGE_EXT,
    VK_DYNAMIC_STATE_DEPTH_CLIP_ENABLE_EXT,
    VK_DYNAMIC_STATE_DEPTH_CLIP_NEGATIVE_ONE_TO_ONE_EXT,
    VK_DYNAMIC_STATE_DISCARD_RECTANGLE_ENABLE_EXT, // Only listed in Vulkan-ValidationLayers
    VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
    VK_DYNAMIC_STATE_DISCARD_RECTANGLE_MODE_EXT,  // Only listed in Vulkan-ValidationLayers
    VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_ENABLE_NV, // Only listed in Vulkan-ValidationLayers
    VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV,
    VK_DYNAMIC_STATE_EXTRA_PRIMITIVE_OVERESTIMATION_SIZE_EXT,
    // Also listed in fragment shader and fragment output
    VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR,
    VK_DYNAMIC_STATE_FRONT_FACE,
    VK_DYNAMIC_STATE_LINE_RASTERIZATION_MODE_EXT,
    VK_DYNAMIC_STATE_LINE_STIPPLE,
    VK_DYNAMIC_STATE_LINE_STIPPLE_ENABLE_EXT,
    VK_DYNAMIC_STATE_LINE_WIDTH,
    VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT,
    VK_DYNAMIC_STATE_POLYGON_MODE_EXT,
    VK_DYNAMIC_STATE_PROVOKING_VERTEX_MODE_EXT,
    VK_DYNAMIC_STATE_RASTERIZATION_STREAM_EXT,
    VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE,
    VK_DYNAMIC_STATE_SCISSOR,
    VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT,
    VK_DYNAMIC_STATE_SHADING_RATE_IMAGE_ENABLE_NV,
    VK_DYNAMIC_STATE_TESSELLATION_DOMAIN_ORIGIN_EXT,
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
    VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV,
    VK_DYNAMIC_STATE_VIEWPORT_SWIZZLE_NV,
    VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT,
    VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_ENABLE_NV,
    VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV
};
static const std::unordered_set<VkDynamicState> FRAGMENT_SHADER_DYNAMIC_STATES{
    VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT, // Also listed in fragment output
    VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT,      // Also listed in fragment output
    // Only listed here in Vulkan-ValidationLayers. Also listed in pre-rasterization shader and fragment output
    VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT,
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_MODE_NV,         // Also listed in fragment output
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV, // Also listed in fragment output
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_NV,        // Also listed in fragment output
    VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV,          // Also listed in fragment output
    VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV,         // Also listed in fragment output
    VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV,       // Also listed in fragment output
    VK_DYNAMIC_STATE_DEPTH_BOUNDS,
    VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE,
    VK_DYNAMIC_STATE_DEPTH_COMPARE_OP,
    VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE,
    VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE,
    // Also listed in pre-rasterization shader and fragment output
    VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR,
    VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT,              // Also listed in fragment output
    VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV, // Also listed in fragment output
    VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT,            // Also listed in fragment output
    VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,                   // Also listed in fragment output
    VK_DYNAMIC_STATE_SAMPLE_MASK_EXT,                        // Also listed in fragment output
    VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
    VK_DYNAMIC_STATE_STENCIL_OP,
    VK_DYNAMIC_STATE_STENCIL_REFERENCE,
    VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE,
    VK_DYNAMIC_STATE_STENCIL_WRITE_MASK
};
static std::unordered_set<VkDynamicState> FRAGMENT_OUTPUT_DYNAMIC_STATES{
    VK_DYNAMIC_STATE_ALPHA_TO_COVERAGE_ENABLE_EXT, // Also listed in fragment shader
    VK_DYNAMIC_STATE_ALPHA_TO_ONE_ENABLE_EXT,      // Also listed in fragment shader
    // Also listed in pre-rasterization shader and fragment shader
    VK_DYNAMIC_STATE_ATTACHMENT_FEEDBACK_LOOP_ENABLE_EXT,
    VK_DYNAMIC_STATE_BLEND_CONSTANTS,
    VK_DYNAMIC_STATE_COLOR_BLEND_ADVANCED_EXT,
    VK_DYNAMIC_STATE_COLOR_BLEND_ENABLE_EXT,
    VK_DYNAMIC_STATE_COLOR_BLEND_EQUATION_EXT,
    VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT,
    VK_DYNAMIC_STATE_COLOR_WRITE_MASK_EXT,
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_MODE_NV,         // Also listed in fragment shader
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_ENABLE_NV, // Also listed in fragment shader
    VK_DYNAMIC_STATE_COVERAGE_MODULATION_TABLE_NV,        // Also listed in fragment shader
    VK_DYNAMIC_STATE_COVERAGE_REDUCTION_MODE_NV,          // Also listed in fragment shader
    VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_ENABLE_NV,         // Also listed in fragment shader
    VK_DYNAMIC_STATE_COVERAGE_TO_COLOR_LOCATION_NV,       // Also listed in fragment shader
    // Only listed here in VK-GL-CTS; also listed in pre-rasterization shader and fragment shader
    VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR,
    VK_DYNAMIC_STATE_LOGIC_OP_ENABLE_EXT,
    VK_DYNAMIC_STATE_LOGIC_OP_EXT,
    VK_DYNAMIC_STATE_RASTERIZATION_SAMPLES_EXT, // Also listed in fragment shader
    // Only listed here in VK-GL-CTS; also listed in fragment shader
    VK_DYNAMIC_STATE_REPRESENTATIVE_FRAGMENT_TEST_ENABLE_NV,
    VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_ENABLE_EXT, // Also listed in fragment shader
    VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,        // Also listed in fragment shader
    VK_DYNAMIC_STATE_SAMPLE_MASK_EXT              // Also listed in fragment shader
};
static std::unordered_set<VkDynamicState> RAY_TRACING_DYNAMIC_STATES{
    VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR
};

void VulkanSqliteConsumerExt::ProcessPipelineDynamicStateCreateInfo(
    const StructPointerDecoder<Decoded_VkPipelineDynamicStateCreateInfo>* createInfo,
    int64_t pipelineId,
    const std::unordered_set<VkDynamicState>& stage_states
)
{
    auto [dynamicStateInfoValid, dynamicStateInfo] = GetMetaStructPointer(createInfo);
    if (dynamicStateInfoValid)
    {
        LogUnsupportedPNext(dynamicStateInfo->pNext);

        auto [dynamicStatesValid, dynamicStates, dynamicStatesCount] =
            GetPointerArray(&dynamicStateInfo->pDynamicStates);
        if (dynamicStatesValid)
        {
            for (size_t j = 0; j < dynamicStatesCount; ++j)
            {
                if (stage_states.contains(dynamicStates[j]))
                {
                    // Although VUID-VkPipelineDynamicStateCreateInfo-pDynamicStates-01442 requires unique states, some
                    // states appear in multiple pipeline state subsets, and thus would be duplicated for non-library
                    // pipelines. INSERT OR IGNORE with a UNIQUE constraint on pipelineDynamicStates avoids this.
                    statements.InsertPipelineDynamicState(pipelineId, dynamicStates[j]);

                    // Also cache the dynamic state in memory for fast lookup during pipeline binding
                    context.pipelineIdToDynamicStates[pipelineId].insert(dynamicStates[j]);
                }
            }
        }
    }
}

void VulkanSqliteConsumerExt::CopyPipelineDynamicStates(int64_t pipelineId, int64_t libraryPipelineId)
{
    // We don't need to do any filtering here because a pipeline library will already be filtered down to dynamic states
    // valid for that library state subset by ProcessPipelineDynamicStateCreateInfo.
    // If a library is created that has multiple pipeline state subsets (e.g. both vertex input and pre-rasterization
    // shaders), this function will be called twice, and will attempt to copy all dynamic states both times; the second
    // time will be ignored due to the UNIQUE constraint on pipelineDynamicStates.
    std::ostringstream dynamicStateSql;
    dynamicStateSql << "INSERT OR IGNORE INTO pipelineDynamicStates SELECT " << pipelineId
                    << ", dynamicState FROM pipelineDynamicStates WHERE pipelineId = " << libraryPipelineId << ";";
    ExecSQL(context.db, dynamicStateSql.str().c_str());

    // Also copy the dynamic states to the in-memory cache
    auto libraryStatesIter = context.pipelineIdToDynamicStates.find(libraryPipelineId);
    if (libraryStatesIter != context.pipelineIdToDynamicStates.end())
    {
        context.pipelineIdToDynamicStates[pipelineId].insert(
            libraryStatesIter->second.begin(), libraryStatesIter->second.end()
        );
    }
}

VulkanSqliteConsumerExt::GraphicsPipelineVertexInputState
VulkanSqliteConsumerExt::ProcessGraphicsPipelineVertexInputState(
    VkResult returnValue, const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
)
{
    GraphicsPipelineVertexInputState result;

    auto [vertexInputStateInfoValid, vertexInputStateInfo] = GetMetaStructPointer(createInfo.pVertexInputState);
    if (!vertexInputStateInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create vertex input state, invalid pVertexInputState struct");
        }
    }
    else
    {
        LogUnsupportedPNext(vertexInputStateInfo->pNext);

        auto vertexInputStateId = statements.InsertVertexInputState(pipelineId);

        result.vertexInputStateId = vertexInputStateId;

        auto [bindingDescriptionsValid, bindingDescriptions, bindingDescriptionsCount] =
            GetMetaStructArray(vertexInputStateInfo->pVertexBindingDescriptions);
        if (bindingDescriptionsValid)
        {
            for (size_t j = 0; j < bindingDescriptionsCount; ++j)
            {
                auto& bindingDescription = bindingDescriptions[j];
                auto binding = bindingDescription.decoded_value->binding;
                auto stride = bindingDescription.decoded_value->stride;
                auto inputRate = bindingDescription.decoded_value->inputRate;
                uint32_t divisor = 1; // to support dynamic state overrides
                statements.InsertVertexInputStateBindingDescription(
                    vertexInputStateId, binding, stride, inputRate, divisor
                );
            }
        }

        auto [attributeDescriptionsValid, attributeDescriptions, attributeDescriptionsCount] =
            GetMetaStructArray(vertexInputStateInfo->pVertexAttributeDescriptions);
        if (attributeDescriptionsValid)
        {
            for (size_t j = 0; j < attributeDescriptionsCount; ++j)
            {
                auto& attributeDescription = attributeDescriptions[j];
                auto location = attributeDescription.decoded_value->location;
                auto binding = attributeDescription.decoded_value->binding;
                auto format = attributeDescription.decoded_value->format;
                auto offset = attributeDescription.decoded_value->offset;
                statements.InsertVertexInputStateAttributeDescription(
                    vertexInputStateId, location, binding, format, offset
                );
            }
        }
    }

    auto [inputAssemblyStateInfoValid, inputAssemblyStateInfo] = GetMetaStructPointer(createInfo.pInputAssemblyState);
    if (inputAssemblyStateInfoValid)
    {
        LogUnsupportedPNext(inputAssemblyStateInfo->pNext);

        auto topology = inputAssemblyStateInfo->decoded_value->topology;
        auto primitiveRestartEnable = inputAssemblyStateInfo->decoded_value->primitiveRestartEnable;
        auto inputAssemblyStateId = statements.InsertInputAssemblyState(pipelineId, topology, primitiveRestartEnable);

        result.inputAssemblyStateId = inputAssemblyStateId;
    }

    ProcessPipelineDynamicStateCreateInfo(createInfo.pDynamicState, pipelineId, VERTEX_INPUT_DYNAMIC_STATES);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelineVertexInputState VulkanSqliteConsumerExt::CopyGraphicsPipelineVertexInputState(
    int64_t pipelineId, int64_t libraryPipelineId
)
{
    GraphicsPipelineVertexInputState libraryState;
    GraphicsPipelineVertexInputState result;

    std::ostringstream libraryLookupSql;
    libraryLookupSql << "SELECT vertexInputStateId, inputAssemblyStateId "
                     << "FROM graphicsPipelineInfos WHERE pipelineId = " << libraryPipelineId << ";";
    auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

    if (results.size() != 1 || results[0].size() != 2)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library vertex input state + input assembly state for pipeline %" PRId64
            "/library %" PRId64 "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
        return result;
    }

    if (const sqlite3_int64* vertexInputStateId = std::get_if<sqlite3_int64>(&results[0][0]))
    {
        libraryState.vertexInputStateId = static_cast<int64_t>(*vertexInputStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][0]))
    {
        // pVertexInputState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library vertex input state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    if (const sqlite3_int64* inputAssemblyStateId = std::get_if<sqlite3_int64>(&results[0][1]))
    {
        libraryState.inputAssemblyStateId = static_cast<int64_t>(*inputAssemblyStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][1]))
    {
        // pInputAssemblyState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library input assembly state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    // We need to do a deep copy, as the existing entries in these tables refer to the original pipeline library
    if (libraryState.inputAssemblyStateId.has_value())
    {
        auto inputAssemblyStateId =
            statements.InsertInputAssemblyStateFromLibrary(pipelineId, libraryState.inputAssemblyStateId.value());
        result.inputAssemblyStateId = inputAssemblyStateId;
    }
    if (libraryState.vertexInputStateId.has_value())
    {
        auto vertexInputStateId = statements.InsertVertexInputState(pipelineId);

        statements.InsertVertexInputStateBindingDescriptionFromLibrary(
            vertexInputStateId, libraryState.vertexInputStateId.value()
        );
        statements.InsertVertexInputStateAttributeDescriptionFromLibrary(
            vertexInputStateId, libraryState.vertexInputStateId.value()
        );

        result.vertexInputStateId = vertexInputStateId;
    }

    CopyPipelineDynamicStates(pipelineId, libraryPipelineId);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelinePreRasterizationShaderState
VulkanSqliteConsumerExt::ProcessGraphicsPipelinePreRasterizationShaderState(
    std::optional<int64_t> deviceId,
    const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
    int64_t pipelineId,
    int64_t pipelineHandle
)
{
    GraphicsPipelinePreRasterizationShaderState result;

    auto [tessellationStateStateInfoValid, tessellationStateInfo] = GetMetaStructPointer(createInfo.pTessellationState);
    if (tessellationStateStateInfoValid)
    {
        LogUnsupportedPNext(tessellationStateInfo->pNext);

        auto patchControlPoints = tessellationStateInfo->decoded_value->patchControlPoints;
        auto tessellationStateId = statements.InsertTessellationState(pipelineId, patchControlPoints);

        result.tessellationStateId = tessellationStateId;
    }

    auto [viewportStateStateInfoValid, viewportStateInfo] = GetMetaStructPointer(createInfo.pViewportState);
    if (viewportStateStateInfoValid)
    {
        LogUnsupportedPNext(viewportStateInfo->pNext);

        auto viewportStateId = statements.InsertViewportState(pipelineId);

        result.viewportStateId = viewportStateId;

        auto [viewportsValid, viewports, viewportsCount] = GetMetaStructArray(viewportStateInfo->pViewports);
        if (viewportsValid)
        {
            for (size_t j = 0; j < viewportsCount; ++j)
            {
                auto& viewport = viewports[j];
                auto x = viewport.decoded_value->x;
                auto y = viewport.decoded_value->y;
                auto width = viewport.decoded_value->width;
                auto height = viewport.decoded_value->height;
                auto minDepth = viewport.decoded_value->minDepth;
                auto maxDepth = viewport.decoded_value->maxDepth;
                statements.InsertViewportStateViewport(viewportStateId, j, x, y, width, height, minDepth, maxDepth);
            }
        }

        auto [scissorsValid, scissors, scissorsCount] = GetMetaStructArray(viewportStateInfo->pScissors);
        if (scissorsValid)
        {
            for (size_t j = 0; j < scissorsCount; ++j)
            {
                auto& scissor = scissors[j];
                auto x = scissor.decoded_value->offset.x;
                auto y = scissor.decoded_value->offset.y;
                auto width = scissor.decoded_value->extent.width;
                auto height = scissor.decoded_value->extent.height;
                statements.InsertViewportStateScissor(viewportStateId, j, x, y, width, height);
            }
        }
    }

    auto [rasterizationStateInfoValid, rasterizationStateInfo] = GetMetaStructPointer(createInfo.pRasterizationState);
    if (rasterizationStateInfoValid)
    {
        LogUnsupportedPNext(rasterizationStateInfo->pNext);

        auto depthClampEnable = rasterizationStateInfo->decoded_value->depthClampEnable;
        auto rasterizationDiscardEnable = rasterizationStateInfo->decoded_value->rasterizerDiscardEnable;
        auto polygonMode = rasterizationStateInfo->decoded_value->polygonMode;
        auto cullMode = rasterizationStateInfo->decoded_value->cullMode;
        auto frontFace = rasterizationStateInfo->decoded_value->frontFace;
        auto depthBiasEnable = rasterizationStateInfo->decoded_value->depthBiasEnable;
        auto depthBiasConstantFactor = rasterizationStateInfo->decoded_value->depthBiasConstantFactor;
        auto depthBiasClamp = rasterizationStateInfo->decoded_value->depthBiasClamp;
        auto depthBiasSlopeFactor = rasterizationStateInfo->decoded_value->depthBiasSlopeFactor;
        auto lineWidth = rasterizationStateInfo->decoded_value->lineWidth;

        auto rasterizationStateId = statements.InsertRasterizationState(
            pipelineId,
            depthClampEnable,
            rasterizationDiscardEnable,
            polygonMode,
            cullMode,
            frontFace,
            depthBiasEnable,
            depthBiasConstantFactor,
            depthBiasClamp,
            depthBiasSlopeFactor,
            lineWidth
        );

        result.rasterizationStateId = rasterizationStateId;
    }

    auto [stagesValid, stages, stageCount] = GetMetaStructArray(createInfo.pStages);
    if (stagesValid)
    {
        for (size_t stageIndex = 0; stageIndex < stageCount; ++stageIndex)
        {
            const auto& stage = stages[stageIndex];
            // Don't use the original stageIndex, as CopyGraphicsPipelineFragmentShaderState assumes that fragment
            // shaders are always after the pre-rasterization shaders, but the spec makes no guarantees on what
            // stage is at what stageIndex, other than uniqueness (VUID-VkGraphicsPipelineCreateInfo-stage-06897).
            if (stage.decoded_value->stage != VK_SHADER_STAGE_FRAGMENT_BIT)
            {
                ProcessPipelineShaderStageCreateInfo(
                    deviceId, pipelineId, pipelineHandle, stages[stageIndex], result.numShaderStages
                );
                result.numShaderStages++;
            }
        }
    }

    ProcessPipelineDynamicStateCreateInfo(
        createInfo.pDynamicState, pipelineId, PRE_RASTERIZATION_SHADERS_DYNAMIC_STATES
    );

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelinePreRasterizationShaderState
VulkanSqliteConsumerExt::CopyGraphicsPipelinePreRasterizationShaderState(int64_t pipelineId, int64_t libraryPipelineId)
{
    GraphicsPipelinePreRasterizationShaderState libraryState;
    GraphicsPipelinePreRasterizationShaderState result;

    // VUID-VkGraphicsPipelineCreateInfo-pStages-06896 requires all stages to either be pre-rasterization or fragment
    // VUID-VkGraphicsPipelineCreateInfo-pStages-06894 says that pre-rasterization only can't have fragment
    // Thus, check stage != VK_SHADER_STAGE_FRAGMENT_BIT instead of using the list at
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-pre-rasterization
    std::ostringstream libraryLookupSql;
    libraryLookupSql << "SELECT viewportStateId, rasterizationStateId, tessellationStateId, count(stage) "
                     << "FROM graphicsPipelineInfos LEFT JOIN pipelineStages USING(pipelineId) "
                     << "WHERE pipelineId = " << libraryPipelineId << " AND stage != " << VK_SHADER_STAGE_FRAGMENT_BIT
                     << ";";
    auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

    if (results.size() != 1 || results[0].size() != 4)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library pre rasterization shader state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
        return result;
    }

    if (const sqlite3_int64* viewportStateId = std::get_if<sqlite3_int64>(&results[0][0]))
    {
        libraryState.viewportStateId = static_cast<int64_t>(*viewportStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][0]))
    {
        // pViewportState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library viewport state for pipeline %" PRId64 "/library %" PRId64 "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    if (const sqlite3_int64* rasterizationStateId = std::get_if<sqlite3_int64>(&results[0][1]))
    {
        libraryState.rasterizationStateId = static_cast<int64_t>(*rasterizationStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][1]))
    {
        // pRasterizationState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library rasterization state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    if (const sqlite3_int64* tessellationStateId = std::get_if<sqlite3_int64>(&results[0][2]))
    {
        libraryState.tessellationStateId = static_cast<int64_t>(*tessellationStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][2]))
    {
        // pTessellationState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library input tessellation state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    if (const sqlite3_int64* numShaderStages = std::get_if<sqlite3_int64>(&results[0][3]))
    {
        libraryState.numShaderStages = static_cast<int64_t>(*numShaderStages);
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library pre-rasterization shader stage count for pipeline %" PRId64 "/library %" PRId64
            "; treating as 0",
            pipelineId,
            libraryPipelineId
        );
    }

    // We need to do a deep copy, as the existing entries in these tables refer to the original pipeline library
    if (libraryState.viewportStateId.has_value())
    {
        auto viewportStateId = statements.InsertViewportState(pipelineId);

        statements.InsertViewportStateViewportFromLibrary(viewportStateId, libraryState.viewportStateId.value());
        statements.InsertViewportStateScissorFromLibrary(viewportStateId, libraryState.viewportStateId.value());

        result.viewportStateId = viewportStateId;
    }
    if (libraryState.rasterizationStateId.has_value())
    {
        auto rasterizationStateId =
            statements.InsertRasterizationStateFromLibrary(pipelineId, libraryState.rasterizationStateId.value());
        result.rasterizationStateId = rasterizationStateId;
    }
    if (libraryState.tessellationStateId.has_value())
    {
        auto tessellationStateId =
            statements.InsertTessellationStateFromLibrary(pipelineId, libraryState.tessellationStateId.value());
        result.tessellationStateId = tessellationStateId;
    }
    if (libraryState.numShaderStages != 0)
    {
        // This logic assumes that the fragment shader has the stageIndex value, and thus the pre-rasterization stages
        // all appear in order before it. The vulkan spec doesn't guarantee seem to make any requirements on the order
        // of entries in pStages (other than uniqueness (VUID-VkGraphicsPipelineCreateInfo-stage-06897)), but we
        // guarantee this by inserting the pre-rasterization shaders in
        // ProcessGraphicsPipelinePreRasterizationShaderState before we insert the fragment shader in
        // ProcessGraphicsPipelineFragmentShaderState.
        std::ostringstream pipelineStagesSql;
        pipelineStagesSql << "INSERT INTO pipelineStages SELECT " << pipelineId
                          << ", idx, flags, stage, shaderModuleId, entryPointName "
                          << "FROM pipelineStages WHERE pipelineId = " << libraryPipelineId
                          << " AND stage != " << VK_SHADER_STAGE_FRAGMENT_BIT << ";";
        ExecSQL(context.db, pipelineStagesSql.str().c_str());

        result.numShaderStages = libraryState.numShaderStages;
    }

    CopyPipelineDynamicStates(pipelineId, libraryPipelineId);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelineFragmentShaderState
VulkanSqliteConsumerExt::ProcessGraphicsPipelineFragmentShaderState(
    std::optional<int64_t> deviceId,
    const Decoded_VkGraphicsPipelineCreateInfo& createInfo,
    int64_t pipelineId,
    int64_t pipelineHandle,
    size_t num_pre_rasterization_shaders
)
{
    GraphicsPipelineFragmentShaderState result;

    auto [depthStencilStateInfoValid, depthStencilStateInfo] = GetMetaStructPointer(createInfo.pDepthStencilState);
    if (depthStencilStateInfoValid)
    {
        LogUnsupportedPNext(depthStencilStateInfo->pNext);

        auto flags = depthStencilStateInfo->decoded_value->flags;
        auto depthTestEnable = depthStencilStateInfo->decoded_value->depthTestEnable;
        auto depthWriteEnable = depthStencilStateInfo->decoded_value->depthWriteEnable;
        auto depthCompareOp = depthStencilStateInfo->decoded_value->depthCompareOp;
        auto depthBoundsTestEnable = depthStencilStateInfo->decoded_value->depthBoundsTestEnable;
        auto stencilTestEnable = depthStencilStateInfo->decoded_value->stencilTestEnable;
        auto frontFailOp = depthStencilStateInfo->decoded_value->front.failOp;
        auto frontPassOp = depthStencilStateInfo->decoded_value->front.passOp;
        auto frontDepthFailOp = depthStencilStateInfo->decoded_value->front.depthFailOp;
        auto frontCompareOp = depthStencilStateInfo->decoded_value->front.compareOp;
        auto frontCompareMask = depthStencilStateInfo->decoded_value->front.compareMask;
        auto frontWriteMask = depthStencilStateInfo->decoded_value->front.writeMask;
        auto frontReference = depthStencilStateInfo->decoded_value->front.reference;
        auto backFailOp = depthStencilStateInfo->decoded_value->back.failOp;
        auto backPassOp = depthStencilStateInfo->decoded_value->back.passOp;
        auto backDepthFailOp = depthStencilStateInfo->decoded_value->back.depthFailOp;
        auto backCompareOp = depthStencilStateInfo->decoded_value->back.compareOp;
        auto backCompareMask = depthStencilStateInfo->decoded_value->back.compareMask;
        auto backWriteMask = depthStencilStateInfo->decoded_value->back.writeMask;
        auto backReference = depthStencilStateInfo->decoded_value->back.reference;
        auto minDepthBounds = depthStencilStateInfo->decoded_value->minDepthBounds;
        auto maxDepthBounds = depthStencilStateInfo->decoded_value->maxDepthBounds;

        auto depthStencilStateId = statements.InsertDepthStencilState(
            pipelineId,
            flags,
            depthTestEnable,
            depthWriteEnable,
            depthCompareOp,
            depthBoundsTestEnable,
            stencilTestEnable,
            frontFailOp,
            frontPassOp,
            frontDepthFailOp,
            frontCompareOp,
            frontCompareMask,
            frontWriteMask,
            frontReference,
            backFailOp,
            backPassOp,
            backDepthFailOp,
            backCompareOp,
            backCompareMask,
            backWriteMask,
            backReference,
            minDepthBounds,
            maxDepthBounds
        );

        result.depthStencilStateId = depthStencilStateId;
    }

    auto [stagesValid, stages, stageCount] = GetMetaStructArray(createInfo.pStages);
    if (stagesValid)
    {
        for (size_t stageIndex = 0; stageIndex < stageCount; ++stageIndex)
        {
            const auto& stage = stages[stageIndex];
            // Don't use the original stageIndex, as CopyGraphicsPipelineFragmentShaderState assumes that fragment
            // shaders are always after the pre-rasterization shaders, but the spec makes no guarantees on what
            // stage is at what stageIndex, other than uniqueness (VUID-VkGraphicsPipelineCreateInfo-stage-06897).
            if (stage.decoded_value->stage == VK_SHADER_STAGE_FRAGMENT_BIT)
            {
                ProcessPipelineShaderStageCreateInfo(
                    deviceId,
                    pipelineId,
                    pipelineHandle,
                    stages[stageIndex],
                    num_pre_rasterization_shaders + result.numShaderStages
                );
                result.numShaderStages++;
            }
        }
    }

    ProcessPipelineDynamicStateCreateInfo(createInfo.pDynamicState, pipelineId, FRAGMENT_SHADER_DYNAMIC_STATES);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelineFragmentShaderState
VulkanSqliteConsumerExt::CopyGraphicsPipelineFragmentShaderState(
    int64_t pipelineId, int64_t libraryPipelineId, size_t num_pre_rasterization_shaders
)
{
    GraphicsPipelineFragmentShaderState libraryState;
    GraphicsPipelineFragmentShaderState result;

    // VUID-VkGraphicsPipelineCreateInfo-pStages-06896 requires all stages to either be pre-rasterization or fragment
    // (at least, I think that applies in this case)
    // VUID-VkGraphicsPipelineCreateInfo-pStages-06895 says that fragment only only can't have pre-rasterization
    // So, for the fragment shader state, the only valid stage is fragment shader, which matches the text at
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-fragment-shader
    std::ostringstream libraryLookupSql;
    libraryLookupSql << "SELECT depthStencilStateId, count(stage) "
                     << "FROM graphicsPipelineInfos LEFT JOIN pipelineStages USING(pipelineId) "
                     << "WHERE pipelineId = " << libraryPipelineId << " AND stage = " << VK_SHADER_STAGE_FRAGMENT_BIT
                     << ";";
    auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

    if (results.size() != 1 || results[0].size() != 2)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library fragment shader state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
        return result;
    }

    if (const sqlite3_int64* depthStencilStateId = std::get_if<sqlite3_int64>(&results[0][0]))
    {
        libraryState.depthStencilStateId = static_cast<int64_t>(*depthStencilStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][0]))
    {
        // pDepthStencilState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library depth/stencil state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }
    if (const sqlite3_int64* numShaderStages = std::get_if<sqlite3_int64>(&results[0][1]))
    {
        if (*numShaderStages <= 1)
        {
            libraryState.numShaderStages = static_cast<int64_t>(*numShaderStages);
        }
        else
        {
            // This is illegal per VUID-VkGraphicsPipelineCreateInfo-stage-06897
            GFXRECON_SQLITE_LOG_WARNING(
                "Library %" PRId64 " for pipeline %" PRId64 " has more than 1 fragment shader stage (%" PRIu64
                "); this breaks stageIndex logic so treating as 0 fragment shader stages",
                libraryPipelineId,
                pipelineId,
                *numShaderStages
            );
        }
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library fragment shader stage count for pipeline %" PRId64 "/library %" PRId64
            "; treating as 0",
            pipelineId,
            libraryPipelineId
        );
    }

    // We need to do a deep copy, as the existing entries in these tables refer to the original pipeline library
    if (libraryState.depthStencilStateId.has_value())
    {
        auto depthStencilStateId =
            statements.InsertDepthStencilStateFromLibrary(pipelineId, libraryState.depthStencilStateId.value());
        result.depthStencilStateId = depthStencilStateId;
    }
    if (libraryState.numShaderStages != 0)
    {
        // We can use num_pre_rasterization_shaders as stageIndex because
        // ProcessGraphicsPipelinePreRasterizationShaderState and CopyGraphicsPipelinePreRasterizationShaderState
        // guarantee that there are no gaps in the stage index before then.
        // VUID-VkGraphicsPipelineCreateInfo-stage-06897 and above checks require that there be at most 1 fragment
        // shader, so num_pre_rasterization_shaders will be used for exactly one shader here.
        std::ostringstream pipelineStageSql;
        pipelineStageSql << "INSERT INTO pipelineStages SELECT " << pipelineId << ", " << num_pre_rasterization_shaders
                         << ", flags, stage, shaderModuleId, entryPointName "
                         << "FROM pipelineStages WHERE pipelineId = " << libraryPipelineId
                         << " AND stage = " << VK_SHADER_STAGE_FRAGMENT_BIT << ";";
        ExecSQL(context.db, pipelineStageSql.str().c_str());

        result.numShaderStages = libraryState.numShaderStages;
    }

    CopyPipelineDynamicStates(pipelineId, libraryPipelineId);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelineFragmentOutputState
VulkanSqliteConsumerExt::ProcessGraphicsPipelineFragmentOutputState(
    const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
)
{
    GraphicsPipelineFragmentOutputState result;

    auto [colorBlendStateInfoValid, colorBlendStateInfo] = GetMetaStructPointer(createInfo.pColorBlendState);
    if (colorBlendStateInfoValid)
    {
        LogUnsupportedPNext(colorBlendStateInfo->pNext);

        auto flags = colorBlendStateInfo->decoded_value->flags;
        auto logicOpEnable = colorBlendStateInfo->decoded_value->logicOpEnable;
        // Allowed to be garbage if logicOpEnable is false:
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkPipelineColorBlendStateCreateInfo.html#VUID-VkPipelineColorBlendStateCreateInfo-logicOpEnable-00606
        auto logicOp =
            logicOpEnable ? std::make_optional<int64_t>(colorBlendStateInfo->decoded_value->logicOp) : std::nullopt;
        auto colorBlendStateId = statements.InsertColorBlendState(
            pipelineId, flags, logicOpEnable, logicOp, colorBlendStateInfo->decoded_value->blendConstants
        );

        result.colorBlendStateId = colorBlendStateId;

        const auto* colorWriteCreateInfo =
            GetPNextMetaStruct<Decoded_VkPipelineColorWriteCreateInfoEXT>(colorBlendStateInfo->pNext);

        bool colorWriteEnablesValid = false;
        VkBool32* colorWriteEnables = nullptr;
        uint64_t colorWriteEnablesCount = 0;
        if (colorWriteCreateInfo != nullptr)
        {
            std::tie(colorWriteEnablesValid, colorWriteEnables, colorWriteEnablesCount) =
                GetPointerArray(&colorWriteCreateInfo->pColorWriteEnables);
        }

        auto [attachmentsValid, attachments, attachmentsCount] = GetMetaStructArray(colorBlendStateInfo->pAttachments);
        if (attachmentsValid)
        {
            for (size_t j = 0; j < attachmentsCount; ++j)
            {
                auto& attachment = attachments[j];
                auto blendEnable = attachment.decoded_value->blendEnable;
                auto srcColorBlendFactor = attachment.decoded_value->srcColorBlendFactor;
                auto dstColorBlendFactor = attachment.decoded_value->dstColorBlendFactor;
                auto colorBlendOp = attachment.decoded_value->colorBlendOp;
                auto srcAlphaBlendFactor = attachment.decoded_value->srcAlphaBlendFactor;
                auto dstAlphaBlendFactor = attachment.decoded_value->dstAlphaBlendFactor;
                auto alphaBlendOp = attachment.decoded_value->alphaBlendOp;
                auto colorWriteMask = attachment.decoded_value->colorWriteMask;
                VkBool32 colorWriteEnable = VK_TRUE;
                if (colorWriteEnablesValid && j < colorWriteEnablesCount)
                {
                    colorWriteEnable = colorWriteEnables[j];
                }
                statements.InsertColorBlendStateAttachmentState(
                    colorBlendStateId,
                    j,
                    blendEnable,
                    srcColorBlendFactor,
                    dstColorBlendFactor,
                    colorBlendOp,
                    srcAlphaBlendFactor,
                    dstAlphaBlendFactor,
                    alphaBlendOp,
                    colorWriteMask,
                    colorWriteEnable
                );
            }
        }
    }

    ProcessPipelineDynamicStateCreateInfo(createInfo.pDynamicState, pipelineId, FRAGMENT_OUTPUT_DYNAMIC_STATES);

    return result;
}

VulkanSqliteConsumerExt::GraphicsPipelineFragmentOutputState
VulkanSqliteConsumerExt::CopyGraphicsPipelineFragmentOutputState(int64_t pipelineId, int64_t libraryPipelineId)
{
    GraphicsPipelineFragmentOutputState libraryState;
    GraphicsPipelineFragmentOutputState result;

    std::ostringstream libraryLookupSql;
    libraryLookupSql << "SELECT colorBlendStateId "
                     << "FROM graphicsPipelineInfos WHERE pipelineId = " << libraryPipelineId << ";";
    auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

    if (results.size() != 1 || results[0].size() != 1)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library fragment output state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
        return result;
    }

    if (const sqlite3_int64* colorBlendStateId = std::get_if<sqlite3_int64>(&results[0][0]))
    {
        libraryState.colorBlendStateId = static_cast<int64_t>(*colorBlendStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][0]))
    {
        // pColorBlendState is allowed to be null with extensions; don't log a warning
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library color blend state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    // We need to do a deep copy, as the existing entries in these tables refer to the original pipeline library
    if (libraryState.colorBlendStateId.has_value())
    {
        auto colorBlendStateId =
            statements.InsertColorBlendStateFromLibrary(pipelineId, libraryState.colorBlendStateId.value());
        statements.InsertColorBlendStateAttachmentStateFromLibrary(
            colorBlendStateId, libraryState.colorBlendStateId.value()
        );

        result.colorBlendStateId = colorBlendStateId;
    }

    CopyPipelineDynamicStates(pipelineId, libraryPipelineId);

    return result;
}

std::optional<int64_t> VulkanSqliteConsumerExt::ProcessGraphicsPipelineMultisampleState(
    const Decoded_VkGraphicsPipelineCreateInfo& createInfo, int64_t pipelineId
)
{
    auto [multisampleStateInfoValid, multisampleStateInfo] = GetMetaStructPointer(createInfo.pMultisampleState);
    if (multisampleStateInfoValid)
    {
        LogUnsupportedPNext(multisampleStateInfo->pNext);

        auto rasterizationSamples = multisampleStateInfo->decoded_value->rasterizationSamples;
        auto sampleShadingEnable = multisampleStateInfo->decoded_value->sampleShadingEnable;
        auto minSampleShading = multisampleStateInfo->decoded_value->minSampleShading;
        auto alphaToCoverageEnable = multisampleStateInfo->decoded_value->alphaToCoverageEnable;
        auto alphaToOneEnable = multisampleStateInfo->decoded_value->alphaToOneEnable;

        auto multisampleStateId = statements.InsertMultisampleState(
            pipelineId,
            rasterizationSamples,
            sampleShadingEnable,
            minSampleShading,
            alphaToCoverageEnable,
            alphaToOneEnable
        );

        auto [sampleMasksValid, sampleMasks, sampleMasksCount] = GetPointerArray(&multisampleStateInfo->pSampleMask);
        if (sampleMasksValid)
        {
            for (size_t j = 0; j < sampleMasksCount; ++j)
            {
                statements.InsertMultisampleStateSampleMask(multisampleStateId, j, sampleMasks[j]);
            }
        }

        return multisampleStateId;
    }
    else
    {
        return std::nullopt;
    }
}

std::optional<int64_t> VulkanSqliteConsumerExt::CopyGraphicsPipelineMultisampleState(
    int64_t pipelineId, int64_t libraryPipelineId
)
{
    std::optional<int64_t> original_multisample_state;

    std::ostringstream libraryLookupSql;
    libraryLookupSql << "SELECT multisampleStateId "
                     << "FROM graphicsPipelineInfos WHERE pipelineId = " << libraryPipelineId << ";";
    auto results = ExecSQLWithResult(context.db, libraryLookupSql.str().c_str());

    if (results.size() != 1 || results[0].size() != 1)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library fragment output state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
        return std::nullopt;
    }

    if (const sqlite3_int64* colorBlendStateId = std::get_if<sqlite3_int64>(&results[0][0]))
    {
        original_multisample_state = static_cast<int64_t>(*colorBlendStateId);
    }
    else if (std::holds_alternative<std::nullptr_t>(results[0][0]))
    {
        // pMultisampleState is allowed to be null with extensions; don't log a warning
        // Multisample state must be identically defined for all libraries, so we don't need to check other libraries if
        // it is null in one.
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to look up library color blend state for pipeline %" PRId64 "/library %" PRId64
            "; treating as NULL",
            pipelineId,
            libraryPipelineId
        );
    }

    if (original_multisample_state.has_value())
    {
        auto multisampleStateId =
            statements.InsertMultisampleStateFromLibrary(pipelineId, original_multisample_state.value());
        statements.InsertMultisampleStateSampleMasksFromLibrary(multisampleStateId, original_multisample_state.value());

        return multisampleStateId;
    }
    else
    {
        return std::nullopt;
    }
}

void VulkanSqliteConsumerExt::ProcessPipelineShaderStageCreateInfo(
    std::optional<int64_t> deviceId,
    int64_t pipelineId,
    int64_t pipelineHandle,
    const Decoded_VkPipelineShaderStageCreateInfo& stage,
    size_t stageIndex
)
{
    auto pnext = stage.pNext;

    std::optional<int64_t> shaderModule;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkShaderModuleCreateInfo>())
        {
            // This comes from VK_EXT_graphics_pipeline_library, and creates an anonymous shader module.
            // https://github.com/KhronosGroup/Vulkan-Docs/blob/main/proposals/VK_EXT_graphics_pipeline_library.adoc#deprecating-shader-modules
            if (stage.module != format::kNullHandleId)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Shader stage has non-null module but also chains VkShaderModuleCreateInfo; using chained shader"
                );
            }

            const auto* moduleCreateInfo = reinterpret_cast<const Decoded_VkShaderModuleCreateInfo*>(header);

            auto codeSize = moduleCreateInfo->decoded_value->codeSize;

            // No VkShaderModule handle exists for this. Instead, use the pipeline ID and the stage, which matches the
            // format shader extraction and replacement uses since https://github.com/LunarG/gfxreconstruct/pull/1758.
            // (There is nothing to store in shaderModuleHandleToId, since nothing can look it up without a handle.)
            std::string shaderModuleHandle =
                std::to_string(pipelineHandle) + "_" + std::to_string(stage.decoded_value->stage);
            // Note that this->block_index_ is the vkCreateGraphicsPipelines (or similar) call
            shaderModule = statements.InsertShaderModuleWithStringHandle(
                shaderModuleHandle, deviceId, codeSize, this->block_index_
            );
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    if (!shaderModule.has_value())
    {
        if (stage.module != format::kNullHandleId)
        {
            auto shaderModuleIter = context.shaderModuleHandleToId.find(ToInt64(stage.module));
            if (shaderModuleIter == context.shaderModuleHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find shader module with handle %" PRIu64 ", setting foreign key to NULL", stage.module
                );
            }
            else
            {
                shaderModule = shaderModuleIter->second;
            }
        }
        else
        {
            // TODO: There are other cases where this can happen beyond chaining VkShaderModuleCreateInfo:
            // https://registry.khronos.org/vulkan/specs/latest/man/html/VkPipelineShaderStageCreateInfo.html#VUID-VkPipelineShaderStageCreateInfo-stage-06845
            GFXRECON_SQLITE_LOG_WARNING(
                "Pipeline stage is missing shader module and lacks chained VkShaderModuleCreateInfo", stage.module
            );
        }
    }

    auto flags = stage.decoded_value->flags;
    auto stageFlag = stage.decoded_value->stage;
    auto entryPointName = stage.pName.GetPointer();
    statements.InsertPipelineStage(pipelineId, stageIndex, flags, stageFlag, shaderModule, entryPointName);
}

void VulkanSqliteConsumerExt::Process_vkCreateGraphicsPipelines(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId pipelineCache,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkGraphicsPipelineCreateInfo>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>* pPipelines
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateGraphicsPipelines(
        call_info, returnValue, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines
    );

    auto [pipelinesValid, pipelines, pipelineCount] = GetHandleArray(pPipelines);
    if (!pipelinesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create graphics pipeline, invalid pPipelines array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create graphics pipeline, invalid pCreateInfos struct array");
        }
        return;
    }

    for (size_t i = 0; i < pipelineCount; ++i)
    {
        auto& createInfo = createInfos[i];

        auto pnext = createInfo.pNext;
        std::optional<VkGraphicsPipelineLibraryFlagsEXT> graphicsLibraryFlagsOptional = std::nullopt;
        const Decoded_VkPipelineRenderingCreateInfo* pipelineRenderingCreateInfo = nullptr;
        format::HandleId* libraryHandles = nullptr;
        uint64_t libraryCount = 0;
        while (pnext != nullptr)
        {
            auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
            if (*header->sType == gfxrecon::util::GetSType<VkPipelineLibraryCreateInfoKHR>())
            {
                const auto* pLibraryCreateInfo =
                    reinterpret_cast<const Decoded_VkPipelineLibraryCreateInfoKHR*>(header);
                bool librariesValid;
                std::tie(librariesValid, libraryHandles, libraryCount) =
                    GetHandleArray(&pLibraryCreateInfo->pLibraries);
                if (!librariesValid)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING("Failed to create graphics pipeline, invalid pLibraries struct array");
                    }
                    return;
                }
            }
            else if (*header->sType == gfxrecon::util::GetSType<VkGraphicsPipelineLibraryCreateInfoEXT>())
            {
                graphicsLibraryFlagsOptional =
                    reinterpret_cast<const Decoded_VkGraphicsPipelineLibraryCreateInfoEXT*>(header)
                        ->decoded_value->flags;
            }
            else if (*header->sType == gfxrecon::util::GetSType<VkPipelineRenderingCreateInfo>())
            {
                pipelineRenderingCreateInfo = reinterpret_cast<const Decoded_VkPipelineRenderingCreateInfo*>(header);
            }
            else
            {
                LogUnsupportedPNext(*header->sType);
            }

            pnext = header->pNext;
        }

        auto pipelineFlags = createInfo.decoded_value->flags;

        VkGraphicsPipelineLibraryFlagsEXT graphicsLibraryFlags;
        if (graphicsLibraryFlagsOptional.has_value())
        {
            graphicsLibraryFlags = graphicsLibraryFlagsOptional.value();
        }
        else
        {
            // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineLibraryCreateInfoEXT.html#_description
            if ((pipelineFlags & VK_PIPELINE_CREATE_LIBRARY_BIT_KHR) || libraryCount > 0)
            {
                graphicsLibraryFlags = 0;
            }
            else
            {
                graphicsLibraryFlags = VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT |
                    VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT |
                    VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT |
                    VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT;
            }
        }

        std::unordered_map<VkGraphicsPipelineLibraryFlagBitsEXT, LibraryInfo> libraries =
            GetPipelineLibraryInfo(pipelines[i], libraryCount, libraryHandles);

        std::optional<int64_t> basePipelineId = GetBasePipelineId(returnValue, createInfo, pipelines, i);

        // When using libraries, there are rules for when the layouts can differ; see info near
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#pipelines-graphics-subsets-complete
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#VUID-VkGraphicsPipelineCreateInfo-flags-06612
        // However, the layout must always be explicitly provided on the linked pipeline and the pre-rasterization and
        // fragment shader libraries; we don't need to implement those rules and can assume the layout is compatible.
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#VUID-VkGraphicsPipelineCreateInfo-layout-07827
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#VUID-VkGraphicsPipelineCreateInfo-None-07826
        std::optional<int64_t> pipelineLayout;
        auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(createInfo.layout));
        if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
        {
            if ((graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT) ||
                (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT) ||
                libraries.contains(VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT) ||
                libraries.contains(VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT))
            {
                LOG_CMD_WARNING(
                    "Failed to find pipeline layout with handle %" PRIu64 ", setting foreign key to NULL",
                    createInfo.layout
                );
            }
        }
        else
        {
            pipelineLayout = pipelineLayoutIter->second;
        }

        auto deviceId = context.GetDeviceId(device);

        std::optional<int64_t> renderPass;
        // NOTE dynamic rendering will not have a renderPass assigned
        if (!deviceId.has_value() || !context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
        {
            if ((graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT) ||
                (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT) ||
                (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT))
            {

                auto renderPassIter = context.renderPassHandleToId.find(ToInt64(createInfo.renderPass));
                if (renderPassIter == context.renderPassHandleToId.end())
                {
                    LOG_CMD_WARNING(
                        "Failed to find render pass with handle %" PRIu64 ", setting foreign key to NULL",
                        createInfo.renderPass
                    );
                }
                else
                {
                    renderPass = renderPassIter->second;
                }
            }
            else
            {
                // There is no combination logic for these; the render pass simply needs to be compatible.
                // Pre-rasterization shader state is always required, so use that one.
                // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#VUID-VkGraphicsPipelineCreateInfo-pLibraries-06628
                if (auto library = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT);
                    library != libraries.end())
                {
                    renderPass = library->second.renderPass;
                }
            }
        }

        std::optional<uint32_t> viewMask = std::nullopt;
        std::optional<VkFormat> depthAttachmentFormat = std::nullopt;
        std::optional<VkFormat> stencilAttachmentFormat = std::nullopt;
        if (pipelineRenderingCreateInfo)
        {
            auto renderingCreateInfo = pipelineRenderingCreateInfo->decoded_value;
            viewMask = renderingCreateInfo->viewMask;
            depthAttachmentFormat = renderingCreateInfo->depthAttachmentFormat;
            stencilAttachmentFormat = renderingCreateInfo->depthAttachmentFormat;
        }

        auto pipeline = pipelines[i];
        auto pipelineHandle = ToInt64(pipeline);
        auto pipelineId = statements.InsertPipelineGraphics(
            pipelineHandle,
            deviceId,
            pipelineFlags,
            basePipelineId,
            pipelineLayout,
            renderPass,
            viewMask.has_value() ? std::make_optional<int64_t>(viewMask.value()) : std::nullopt,
            depthAttachmentFormat.has_value() ? std::make_optional<int64_t>(depthAttachmentFormat.value())
                                              : std::nullopt,
            stencilAttachmentFormat.has_value() ? std::make_optional<int64_t>(stencilAttachmentFormat.value())
                                                : std::nullopt,
            this->block_index_
        );

        if (pipelineRenderingCreateInfo)
        {
            auto renderingCreateInfo = pipelineRenderingCreateInfo->decoded_value;
            for (uint64_t colorIndex = 0; colorIndex < renderingCreateInfo->colorAttachmentCount; ++colorIndex)
            {
                statements.InsertPipelineColorAttachmentFormat(
                    pipelineId, colorIndex, renderingCreateInfo->pColorAttachmentFormats[colorIndex]
                );
            }
        }

        for (uint64_t libraryIndex = 0; libraryIndex < libraryCount; libraryIndex++)
        {
            auto libraryPipelineIter = context.pipelineHandleToId.find(ToInt64(libraryHandles[libraryIndex]));
            if (libraryPipelineIter == context.pipelineHandleToId.end())
            {
                LOG_CMD_WARNING(
                    "Failed to find library pipeline with handle %" PRIu64 "; ignoring", libraryHandles[libraryIndex]
                );
                continue;
            }

            statements.InsertPipelineLibrary(pipelineId, libraryPipelineIter->second);
        }

        GraphicsPipelineVertexInputState vertexInputStateId;
        GraphicsPipelinePreRasterizationShaderState preRasterizationShaderState;
        GraphicsPipelineFragmentShaderState fragmentShaderState;
        GraphicsPipelineFragmentOutputState fragmentOutputState;
        std::optional<int64_t> multisampleStateId;

        if (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT)
        {
            vertexInputStateId = ProcessGraphicsPipelineVertexInputState(returnValue, createInfo, pipelineId);
        }
        else
        {
            if (auto library = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT);
                library != libraries.end())
            {
                vertexInputStateId = CopyGraphicsPipelineVertexInputState(pipelineId, library->second.pipelineId);
            }
            else if (!(pipelineFlags & VK_PIPELINE_CREATE_LIBRARY_BIT_KHR))
            {
                // TODO: This is allowed if the pipeline lacks a vertex shader
                LOG_CMD_WARNING("Pipeline is missing vertex input state, but is not a library");
            }
        }
        if (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT)
        {
            preRasterizationShaderState =
                ProcessGraphicsPipelinePreRasterizationShaderState(deviceId, createInfo, pipelineId, pipelineHandle);
        }
        else
        {
            if (auto library = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT);
                library != libraries.end())
            {
                preRasterizationShaderState =
                    CopyGraphicsPipelinePreRasterizationShaderState(pipelineId, library->second.pipelineId);
            }
            else if (!(pipelineFlags & VK_PIPELINE_CREATE_LIBRARY_BIT_KHR))
            {
                // This is always required.
                LOG_CMD_WARNING("Pipeline is missing pre rasterization shader state, but is not a library");
            }
        }
        if (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT)
        {
            fragmentShaderState = ProcessGraphicsPipelineFragmentShaderState(
                deviceId, createInfo, pipelineId, pipelineHandle, preRasterizationShaderState.numShaderStages
            );
        }
        else
        {
            if (auto library = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT);
                library != libraries.end())
            {
                fragmentShaderState = CopyGraphicsPipelineFragmentShaderState(
                    pipelineId, library->second.pipelineId, preRasterizationShaderState.numShaderStages
                );
            }
            else if (!(pipelineFlags & VK_PIPELINE_CREATE_LIBRARY_BIT_KHR))
            {
                // TODO: This is technically optional (but doing so discards all fragments)
                LOG_CMD_WARNING("Pipeline is missing fragment shader state, but is not a library");
            }
        }
        if (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT)
        {
            fragmentOutputState = ProcessGraphicsPipelineFragmentOutputState(createInfo, pipelineId);
        }
        else
        {
            if (auto library = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT);
                library != libraries.end())
            {
                fragmentOutputState = CopyGraphicsPipelineFragmentOutputState(pipelineId, library->second.pipelineId);
            }
            else if (!(pipelineFlags & VK_PIPELINE_CREATE_LIBRARY_BIT_KHR))
            {
                // TODO: This is technically optional (but doing so discards all fragments)
                LOG_CMD_WARNING("Pipeline is missing fragment output state, but is not a library");
            }
        }
        // Multisample state must be identically defined between fragment shader state and fragment output state; this
        // also implies that if one is null all are null. See VUID-VkGraphicsPipelineCreateInfo-flags-06633,
        // VUID-VkGraphicsPipelineCreateInfo-pLibraries-06635, VUID-VkGraphicsPipelineCreateInfo-pLibraries-06636.
        // We prefer the one directly in the create info for convenience.
        //
        // TODO:
        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkGraphicsPipelineCreateInfo.html#VUID-VkGraphicsPipelineCreateInfo-pRasterizationState-09039
        // claims that multisample state is also queuePresentId in pre-rasterization shader state, but this may be a
        // mistake in the spec: https://github.com/KhronosGroup/Vulkan-Docs/issues/2498
        if ((graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT) ||
            (graphicsLibraryFlags & VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT))
        {
            multisampleStateId = ProcessGraphicsPipelineMultisampleState(createInfo, pipelineId);
        }
        else
        {
            // However, since both Fragment Shader State and Fragment Output State are optional, we need to check both
            // libraries. Not containing that state is different from containing that state but having a null
            // pMultisampleState.
            if (auto shaderLibrary = libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT);
                shaderLibrary != libraries.end())
            {
                multisampleStateId = CopyGraphicsPipelineMultisampleState(pipelineId, shaderLibrary->second.pipelineId);
            }
            else if (auto outputLibrary =
                         libraries.find(VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT);
                     outputLibrary != libraries.end())
            {
                multisampleStateId = CopyGraphicsPipelineMultisampleState(pipelineId, outputLibrary->second.pipelineId);
            }
            else
            {
                // Both are optional, and a warning would have already been logged above regardless
            }
        }

        auto subpassIndex = createInfo.decoded_value->subpass;
        statements.InsertGraphicsPipelineInfo(
            pipelineId,
            graphicsLibraryFlags,
            subpassIndex,
            vertexInputStateId.inputAssemblyStateId,
            vertexInputStateId.vertexInputStateId,
            preRasterizationShaderState.tessellationStateId,
            preRasterizationShaderState.viewportStateId,
            preRasterizationShaderState.rasterizationStateId,
            multisampleStateId,
            fragmentShaderState.depthStencilStateId,
            fragmentOutputState.colorBlendStateId
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateComputePipelines(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId pipelineCache,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkComputePipelineCreateInfo>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>* pPipelines
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateComputePipelines(
        call_info, returnValue, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines
    );

    auto [pipelinesValid, pipelines, pipelineCount] = GetHandleArray(pPipelines);
    if (!pipelinesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create compute pipeline, invalid pPipelines array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create compute pipeline, invalid pCreateInfos struct array");
        }
        return;
    }

    for (size_t i = 0; i < pipelineCount; ++i)
    {
        auto& createInfo = createInfos[i];

        auto pipelineFlags = createInfo.decoded_value->flags;

        std::optional<int64_t> basePipelineId = std::nullopt;
        if (pipelineFlags & VK_PIPELINE_CREATE_DERIVATIVE_BIT)
        {
            auto basePipelineHandle = createInfo.basePipelineHandle;
            if (basePipelineHandle == format::kNullHandleId)
            {
                if (createInfo.decoded_value->basePipelineIndex < 0)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is out of range, "
                            "setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex
                        );
                    }
                }
                else if (static_cast<size_t>(createInfo.decoded_value->basePipelineIndex) >= i)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is for a "
                            "non-created pipeline at index %" PRIu64 ", setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex,
                            i
                        );
                    }
                }
                else
                {
                    basePipelineHandle = pipelines[createInfo.decoded_value->basePipelineIndex];
                }
            }
            else if (returnValue == VK_SUCCESS && createInfo.decoded_value->basePipelineIndex != -1)
            {
                LOG_CMD_WARNING(
                    "Derivative pipeline has both basePipelineHandle and basePipelineIndex "
                    "set; using basePipelineHandle"
                );
            }

            if (basePipelineHandle != format::kNullHandleId)
            {
                auto basePipelineIter = context.pipelineHandleToId.find(ToInt64(basePipelineHandle));
                if (basePipelineIter == context.pipelineHandleToId.end())
                {
                    LOG_CMD_WARNING(
                        "Failed to find base pipeline with handle %" PRIu64 ", setting foreign key to NULL",
                        basePipelineHandle
                    );
                }
                else
                {
                    basePipelineId = basePipelineIter->second;
                }
            }
        }

        std::optional<int64_t> pipelineLayout = std::nullopt;
        auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(createInfo.layout));
        if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
        {
            LOG_CMD_WARNING(
                "Failed to find pipeline layout with handle %" PRIu64 ", setting foreign key to NULL", createInfo.layout
            );
        }
        else
        {
            pipelineLayout = pipelineLayoutIter->second;
        }

        auto pipeline = pipelines[i];
        auto pipelineHandle = ToInt64(pipeline);
        auto deviceId = context.GetDeviceId(device);
        auto pipelineId = statements.InsertPipelineCompute(
            pipelineHandle, deviceId, pipelineFlags, basePipelineId, pipelineLayout, this->block_index_
        );

        statements.InsertComputePipelineInfo(pipelineId);

        // process stage - compute only has one
        auto stageInfo = createInfo.stage;
        if (!stageInfo)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to create compute pipeline stage for pipeline with handle %" PRIu64 ", invalid stage info",
                    pipeline
                );
            }
        }
        else
        {
            ProcessPipelineShaderStageCreateInfo(deviceId, pipelineId, pipelineHandle, *stageInfo, 0);
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateRayTracingPipelinesNV(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId pipelineCache,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoNV>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>* pPipelines
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateRayTracingPipelinesNV(
        call_info, returnValue, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines
    );

    auto [pipelinesValid, pipelines, pipelineCount] = GetHandleArray(pPipelines);
    if (!pipelinesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create raytracing pipeline, invalid pPipelines array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create raytracing pipeline, invalid pCreateInfos struct array");
        }
        return;
    }

    for (size_t i = 0; i < pipelineCount; ++i)
    {
        auto& createInfo = createInfos[i];

        auto pipelineFlags = createInfo.decoded_value->flags;

        std::optional<int64_t> basePipelineId = std::nullopt;
        if (pipelineFlags & VK_PIPELINE_CREATE_DERIVATIVE_BIT)
        {
            auto basePipelineHandle = createInfo.basePipelineHandle;
            if (basePipelineHandle == format::kNullHandleId)
            {
                if (createInfo.decoded_value->basePipelineIndex < 0)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is out of range, "
                            "setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex
                        );
                    }
                }
                else if (static_cast<size_t>(createInfo.decoded_value->basePipelineIndex) >= i)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is for a "
                            "non-created pipeline at index %" PRIu64 ", setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex,
                            i
                        );
                    }
                }
                else
                {
                    basePipelineHandle = pipelines[createInfo.decoded_value->basePipelineIndex];
                }
            }
            else if (returnValue == VK_SUCCESS && createInfo.decoded_value->basePipelineIndex != -1)
            {
                LOG_CMD_WARNING(
                    "Derivative pipeline has both basePipelineHandle and basePipelineIndex "
                    "set; using basePipelineHandle"
                );
            }

            if (basePipelineHandle != format::kNullHandleId)
            {
                auto basePipelineIter = context.pipelineHandleToId.find(ToInt64(basePipelineHandle));
                if (basePipelineIter == context.pipelineHandleToId.end())
                {
                    LOG_CMD_WARNING(
                        "Failed to find base pipeline with handle %" PRIu64 ", setting foreign key to NULL",
                        basePipelineHandle
                    );
                }
                else
                {
                    basePipelineId = basePipelineIter->second;
                }
            }
        }

        std::optional<int64_t> pipelineLayout = std::nullopt;
        auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(createInfo.layout));
        if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
        {
            LOG_CMD_WARNING(
                "Failed to find pipeline layout with handle %" PRIu64 ", setting foreign key to NULL", createInfo.layout
            );
        }
        else
        {
            pipelineLayout = pipelineLayoutIter->second;
        }

        auto pipeline = pipelines[i];
        auto pipelineHandle = ToInt64(pipeline);
        auto deviceId = context.GetDeviceId(device);
        auto pipelineId = statements.InsertPipelineRayTracingNV(
            pipelineHandle, deviceId, pipelineFlags, basePipelineId, pipelineLayout, this->block_index_
        );

        auto maxRecursionDepth = createInfo.decoded_value->maxRecursionDepth;
        statements.InsertRaytracingPipelineInfo(pipelineId, maxRecursionDepth, std::nullopt, std::nullopt);

        auto [stagesValid, stageInfos, stageCount] = GetMetaStructArray(createInfo.pStages);
        if (!stagesValid)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to create raytracing stage for pipeline with handle %" PRIu64 ", invalid pStages array",
                    pipeline
                );
            }
        }
        else
        {
            for (size_t stageIndex = 0; stageIndex < stageCount; ++stageIndex)
            {
                ProcessPipelineShaderStageCreateInfo(
                    deviceId, pipelineId, pipelineHandle, stageInfos[stageIndex], stageIndex
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateRayTracingPipelinesKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    format::HandleId pipelineCache,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkRayTracingPipelineCreateInfoKHR>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>* pPipelines
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateRayTracingPipelinesKHR(
        call_info,
        returnValue,
        device,
        deferredOperation,
        pipelineCache,
        createInfoCount,
        pCreateInfos,
        pAllocator,
        pPipelines
    );

    auto [pipelinesValid, pipelines, pipelineCount] = GetHandleArray(pPipelines);
    if (!pipelinesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create raytracing pipeline, invalid pPipelines array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create raytracing pipeline, invalid pCreateInfos struct array");
        }
        return;
    }

    for (size_t i = 0; i < pipelineCount; ++i)
    {
        auto& createInfo = createInfos[i];

        auto pipelineFlags = createInfo.decoded_value->flags;

        std::optional<int64_t> basePipelineId = std::nullopt;
        if (pipelineFlags & VK_PIPELINE_CREATE_DERIVATIVE_BIT)
        {
            auto basePipelineHandle = createInfo.basePipelineHandle;
            if (basePipelineHandle == format::kNullHandleId)
            {
                if (createInfo.decoded_value->basePipelineIndex < 0)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is out of range, "
                            "setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex
                        );
                    }
                }
                else if (static_cast<size_t>(createInfo.decoded_value->basePipelineIndex) >= i)
                {
                    if (returnValue == VK_SUCCESS)
                    {
                        LOG_CMD_WARNING(
                            "Derivative pipeline has null basePipelineHandle and basePipelineIndex %d is for a "
                            "non-created pipeline at index %" PRIu64 ", setting foreign key to NULL",
                            createInfo.decoded_value->basePipelineIndex,
                            i
                        );
                    }
                }
                else
                {
                    basePipelineHandle = pipelines[createInfo.decoded_value->basePipelineIndex];
                }
            }
            else if (returnValue == VK_SUCCESS && createInfo.decoded_value->basePipelineIndex != -1)
            {
                LOG_CMD_WARNING(
                    "Derivative pipeline has both basePipelineHandle and basePipelineIndex "
                    "set; using basePipelineHandle"
                );
            }

            if (basePipelineHandle != format::kNullHandleId)
            {
                auto basePipelineIter = context.pipelineHandleToId.find(ToInt64(basePipelineHandle));
                if (basePipelineIter == context.pipelineHandleToId.end())
                {
                    LOG_CMD_WARNING(
                        "Failed to find base pipeline with handle %" PRIu64 ", setting foreign key to NULL",
                        basePipelineHandle
                    );
                }
                else
                {
                    basePipelineId = basePipelineIter->second;
                }
            }
        }

        std::optional<int64_t> pipelineLayout = std::nullopt;
        auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(createInfo.layout));
        if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
        {
            LOG_CMD_WARNING(
                "Failed to find pipeline layout with handle %" PRIu64 ", setting foreign key to NULL", createInfo.layout
            );
        }
        else
        {
            pipelineLayout = pipelineLayoutIter->second;
        }

        auto pipeline = pipelines[i];
        auto pipelineHandle = ToInt64(pipeline);
        auto deviceId = context.GetDeviceId(device);
        auto pipelineId = statements.InsertPipelineRayTracing(
            pipelineHandle, deviceId, pipelineFlags, basePipelineId, pipelineLayout, this->block_index_
        );

        auto [stagesValid, stageInfos, stageCount] = GetMetaStructArray(createInfo.pStages);
        if (!stagesValid)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to create raytracing stage for pipeline with handle %" PRIu64 ", invalid pStages array",
                    pipeline
                );
            }
        }
        else
        {
            for (size_t stageIndex = 0; stageIndex < stageCount; ++stageIndex)
            {
                ProcessPipelineShaderStageCreateInfo(
                    deviceId, pipelineId, pipelineHandle, stageInfos[stageIndex], stageIndex
                );
            }
        }

        ProcessPipelineDynamicStateCreateInfo(createInfo.pDynamicState, pipelineId, RAY_TRACING_DYNAMIC_STATES);

        auto maxRecursionDepth = createInfo.decoded_value->maxPipelineRayRecursionDepth;
        auto [libraryInterfaceValid, libraryInterface] = GetMetaStructPointer(createInfo.pLibraryInterface);
        std::optional<int64_t> maxPipelineRayPayloadSize = std::nullopt;
        std::optional<int64_t> maxPipelineRayHitAttributeSize = std::nullopt;
        if (libraryInterfaceValid)
        {
            LogUnsupportedPNext(libraryInterface->pNext);

            maxPipelineRayPayloadSize = libraryInterface->decoded_value->maxPipelineRayPayloadSize;
            maxPipelineRayHitAttributeSize = libraryInterface->decoded_value->maxPipelineRayHitAttributeSize;
        }

        auto raytracingPipelineId = statements.InsertRaytracingPipelineInfo(
            pipelineId, maxRecursionDepth, maxPipelineRayPayloadSize, maxPipelineRayHitAttributeSize
        );

        auto [groupsValid, groups, groupCount] = GetMetaStructArray(createInfo.pGroups);
        if (groupsValid)
        {
            for (size_t groupIndex = 0; groupIndex < groupCount; ++groupIndex)
            {
                auto& group = groups[groupIndex];
                auto groupType = group.decoded_value->type;
                auto generalShaderIndex = group.decoded_value->generalShader;
                auto closestHitShaderIndex = group.decoded_value->closestHitShader;
                auto anyHitShaderIndex = group.decoded_value->anyHitShader;
                auto intersectionShaderIndex = group.decoded_value->intersectionShader;

                statements.InsertRaytracingShaderGroup(
                    raytracingPipelineId,
                    pipelineId,
                    groupType,
                    generalShaderIndex,
                    closestHitShaderIndex,
                    anyHitShaderIndex,
                    intersectionShaderIndex
                );
            }
        }

        auto [libraryInfoValid2, libraryInfo2] = GetMetaStructPointer(createInfo.pLibraryInfo);
        if (libraryInfoValid2)
        {
            LogUnsupportedPNext(libraryInfo2->pNext);

            auto [librariesValid, libraries, libraryCount2] = GetHandleArray(&libraryInfo2->pLibraries);
            if (librariesValid)
            {
                for (size_t libraryIndex = 0; libraryIndex < libraryCount2; ++libraryIndex)
                {
                    auto library = libraries[libraryIndex];
                    auto libraryPipelineIter = context.pipelineHandleToId.find(ToInt64(library));
                    if (libraryPipelineIter == context.pipelineHandleToId.end())
                    {
                        LOG_CMD_WARNING("Failed to find library pipeline with handle %" PRIu64 ", ignoring", library);
                        continue;
                    }
                    statements.InsertPipelineLibrary(pipelineId, libraryPipelineIter->second);
                }
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyPipeline(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId pipeline,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPipeline(call_info, device, pipeline, pAllocator);

    if (auto id = context.ExtractId(pipeline, context.pipelineHandleToId, "pipeline", this->block_index_))
    {
        statements.DestroyObject(statements.destroyPipelineUpdateStatement, this->block_index_, *id);
        // This applies to anonymous shader modules created during vkCreateGraphicsPipelines et al (implemented in
        // ProcessPipelineShaderStageCreateInfo). It doesn't apply to normal shader modules from vkCreateShaderModule.
        statements.DestroyObject(
            statements.destroyPipelineAnonymousShaderModulesUpdateStatement, this->block_index_, *id
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCreatePipelineLayout(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPipelineLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipelineLayout>* pPipelineLayout
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreatePipelineLayout(
        call_info, returnValue, device, pCreateInfo, pAllocator, pPipelineLayout
    );

    auto [pipelineLayoutValid, pipelineLayout] = GetHandle(pPipelineLayout);
    if (!pipelineLayoutValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline layout, invalid pPipelineLayout handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline layout info, invalid pCreateInfo");
        }
    }
    else
    {
        auto flags = createInfo->decoded_value->flags;

        auto pipelineLayoutHandle = ToInt64(pipelineLayout);
        auto deviceId = context.GetDeviceId(device);
        auto pipelineLayoutId =
            statements.InsertPipelineLayout(pipelineLayoutHandle, deviceId, flags, this->block_index_);

        LogUnsupportedPNext(createInfo->pNext);

        auto [setLayoutsValid, setLayouts, setLayoutCount] = GetHandleArray(&createInfo->pSetLayouts);
        if (setLayoutsValid)
        {
            for (size_t setIndex = 0; setIndex < setLayoutCount; ++setIndex)
            {
                auto layout = setLayouts[setIndex];
                std::optional<int64_t> layoutId = std::nullopt;
                if (layout != format::kNullHandleId)
                {
                    layoutId = context.GetDescriptorSetLayoutId(layout);
                }
                else
                {
                    // Null descriptor set layouts are allowed with VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT
                }

                if (layoutId.has_value())
                {
                    context.pipelineLayoutSetIndexToLayoutId[pipelineLayoutId][setIndex] = layoutId.value();
                }

                statements.InsertPipelineDescriptorSetLayout(pipelineLayoutId, setIndex, layoutId);
            }
        }

        auto [pushConstantRangesValid, pushConstantRanges, pushConstantRangesCount] =
            GetMetaStructArray(createInfo->pPushConstantRanges);
        if (pushConstantRangesValid)
        {
            for (size_t i = 0; i < pushConstantRangesCount; ++i)
            {
                auto& pushConstantRange = pushConstantRanges[i];
                auto stageFlags = pushConstantRange.decoded_value->stageFlags;
                auto offset = pushConstantRange.decoded_value->offset;
                auto size = pushConstantRange.decoded_value->size;
                statements.InsertPipelinePushConstantRange(pipelineLayoutId, i, stageFlags, offset, size);
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyPipelineLayout(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId pipelineLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPipelineLayout(call_info, device, pipelineLayout, pAllocator);

    if (auto id =
            context.ExtractId(pipelineLayout, context.pipelineLayoutHandleToId, "pipelineLayout", this->block_index_))
    {
        statements.DestroyObject(statements.destroyPipelineLayoutUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDescriptorSetLayout(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorSetLayoutCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorSetLayout>* pSetLayout
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDescriptorSetLayout(
        call_info, returnValue, device, pCreateInfo, pAllocator, pSetLayout
    );

    auto [setLayoutValid, setLayout] = GetHandle(pSetLayout);
    if (!setLayoutValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create descriptor set layout, invalid pSetLayout handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create descriptor set layout info, invalid pCreateInfo");
        }
        return;
    }

    auto [bindingsValid, bindings, bindingsCount] = GetMetaStructArray(createInfo->pBindings);
    const VkDescriptorBindingFlags* bindingFlagsPointer = nullptr;

    auto pnext = createInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkDescriptorSetLayoutBindingFlagsCreateInfo>())
        {
            auto* flagsCreateInfo =
                reinterpret_cast<const Decoded_VkDescriptorSetLayoutBindingFlagsCreateInfo*>(header);
            auto [flagsValid, flags, flagsCount] = GetPointerArray(&flagsCreateInfo->pBindingFlags);
            if (flagsValid)
            {
                if (flagsCount == bindingsCount)
                {
                    bindingFlagsPointer = flags;
                }
                else if (flagsCount != 0)
                {
                    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkDescriptorSetLayoutBindingFlagsCreateInfo.html#VUID-VkDescriptorSetLayoutBindingFlagsCreateInfo-bindingCount-03002
                    GFXRECON_LOG_WARNING(
                        "Unexpected bindingCount for flags (%" PRIu64 ") vs bindings (%" PRIu64
                        ") when creating descriptor set layout",
                        flagsCount,
                        bindingsCount
                    );
                }
            }
        }
        else
        {
            // VkMutableDescriptorTypeCreateInfoEXT
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    auto flags = createInfo->decoded_value->flags;

    auto descriptorSetLayoutHandle = ToInt64(setLayout);
    auto deviceId = context.GetDeviceId(device);
    auto descriptorSetLayoutId =
        statements.InsertDescriptorSetLayout(descriptorSetLayoutHandle, deviceId, flags, this->block_index_);

    VulkanSqliteConsumerContext::DescriptorSetLayoutInfo info{};
    info.flags = flags;

    for (size_t i = 0; i < bindingsCount; ++i)
    {
        auto& binding = bindings[i];
        auto bindingValue = binding.decoded_value->binding;
        auto descriptorType = binding.decoded_value->descriptorType;
        auto descriptorCount = binding.decoded_value->descriptorCount;
        auto stageFlags = binding.decoded_value->stageFlags;
        auto bindingFlags = (bindingFlagsPointer != nullptr) ? bindingFlagsPointer[i] : 0;
        info.bindings[bindingValue] = { .descriptorType = descriptorType,
                                        .stageFlags = stageFlags,
                                        .descriptorCount = descriptorCount,
                                        .flags = bindingFlags };
        // TODO: handle pImmutableSamplers
        statements.InsertDescriptorSetLayoutBinding(
            descriptorSetLayoutId, bindingValue, descriptorType, descriptorCount, stageFlags, bindingFlags
        );
    }

    context.descriptorSetLayoutToInfo.emplace(descriptorSetLayoutId, std::move(info));
}

void VulkanSqliteConsumerExt::Process_vkDestroyDescriptorSetLayout(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorSetLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDescriptorSetLayout(call_info, device, descriptorSetLayout, pAllocator);

    if (auto id = context.ExtractId(
            descriptorSetLayout, context.descriptorSetLayoutHandleToId, "descriptorSetLayout", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyDescriptorSetLayoutUpdateStatement, this->block_index_, *id);
        context.descriptorSetLayoutToInfo.erase(*id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDescriptorPool(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorPoolCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorPool>* pDescriptorPool
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDescriptorPool(
        call_info, returnValue, device, pCreateInfo, pAllocator, pDescriptorPool
    );

    auto [poolValid, descriptorPool] = GetHandle(pDescriptorPool);
    if (!poolValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create descriptor pool, invalid pDescriptorPool handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to set descriptor pool info, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;
    // TODO: Handle poolSizeCount and pPoolSizes

    statements.InsertDescriptorPool(descriptorPool, device, ci.flags, ci.maxSets, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyDescriptorPool(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorPool,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDescriptorPool(call_info, device, descriptorPool, pAllocator);

    if (auto id =
            context.ExtractId(descriptorPool, context.descriptorPoolHandleToId, "descriptor pool", this->block_index_))
    {
        statements.DestroyObject(statements.destroyDescriptorPoolUpdateStatement, this->block_index_, *id);
        // update all un-freed associated descriptor sets as they are now implicitly freed
        statements.DestroyObject(statements.freePoolDescriptorSetsUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkResetDescriptorPool(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId descriptorPool,
    VkDescriptorPoolResetFlags flags
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkResetDescriptorPool(call_info, returnValue, device, descriptorPool, flags);

    auto descriptorPoolIter = context.descriptorPoolHandleToId.find(ToInt64(descriptorPool));
    if (descriptorPoolIter == context.descriptorPoolHandleToId.end())
    {
        LOG_CMD_WARNING(
            "Failed to reset descriptor pool, no descriptor pool found with handle %" PRIu64, descriptorPool
        );
        return;
    }

    // update all un-freed associated descriptor sets as they are now implicitly freed
    statements.DestroyObject(
        statements.freePoolDescriptorSetsUpdateStatement, this->block_index_, descriptorPoolIter->second
    );
}

void VulkanSqliteConsumerExt::Process_vkAllocateDescriptorSets(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorSetAllocateInfo>* pAllocateInfo,
    HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkAllocateDescriptorSets(
        call_info, returnValue, device, pAllocateInfo, pDescriptorSets
    );

    auto [descriptorSetsValid, descriptorSets, descriptorSetCount] = GetHandleArray(pDescriptorSets);
    if (!descriptorSetsValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to allocate descriptor sets, invalid pDescriptorSets");
        }
        return;
    }

    auto [allocateInfoValid, allocateInfo] = GetMetaStructPointer(pAllocateInfo);
    if (!allocateInfo)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to allocate descriptor sets, invalid pAllocateInfo");
        }
        return;
    }

    LogUnsupportedPNext(allocateInfo->pNext);

    auto [descriptorSetLayoutsValid, descriptorSetLayouts, descriptorSetLayoutCount] =
        GetHandleArray(&allocateInfo->pSetLayouts);
    if (!descriptorSetLayoutsValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to allocate descriptor sets, invalid pSetLayouts");
        }
        return;
    }
    if (descriptorSetCount != descriptorSetLayoutCount)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING(
                "descriptor set count does not match descriptor set layout count, using minimum of "
                "values to create descriptor sets"
            );
        }
    }

    std::optional<int64_t> descriptorPoolId = std::nullopt;
    auto descriptorPoolIter = context.descriptorPoolHandleToId.find(ToInt64(allocateInfo->descriptorPool));
    if (descriptorPoolIter == context.descriptorPoolHandleToId.end())
    {
        LOG_CMD_WARNING(
            "Failed to find descriptor pool for handle %" PRIu64 ", setting foreign key to NULL",
            allocateInfo->descriptorPool
        );
    }
    else
    {
        descriptorPoolId = descriptorPoolIter->second;
    }

    for (size_t i = 0; i < std::min(descriptorSetCount, descriptorSetLayoutCount); ++i)
    {
        auto layout = descriptorSetLayouts[i];
        auto layoutId = context.GetDescriptorSetLayoutId(layout);

        auto descriptorSet = descriptorSets[i];
        auto descriptorSetHandle = ToInt64(descriptorSet);

        statements.InsertDescriptorSet(descriptorSetHandle, descriptorPoolId, layoutId, this->block_index_);
    }
}

void VulkanSqliteConsumerExt::Process_vkFreeDescriptorSets(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId descriptorPool,
    uint32_t descriptorSetCount,
    HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets
)
{

    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkFreeDescriptorSets(
        call_info, returnValue, device, descriptorPool, descriptorSetCount, pDescriptorSets
    );

    auto [descriptorSetsValid, descriptorSets, descriptorSetsCount] = GetHandleArray(pDescriptorSets);
    if (!descriptorSetsValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to free descriptor set, invalid pDescriptorSets");
        }
        return;
    }
    for (size_t i = 0; i < descriptorSetsCount; ++i)
    {
        auto descriptorSet = descriptorSets[i];
        if (descriptorSet == format::kNullHandleId)
        {
            continue;
        }
        auto descriptorSetIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorSet));
        if (descriptorSetIter == context.descriptorSetHandleToInfo.end())
        {
            LOG_CMD_WARNING(
                "Failed to free descriptor set, failed to find descriptor set for handle %" PRIu64, descriptorSet
            );
            continue;
        }
        statements.DestroyObject(
            statements.freeDescriptorSetUpdateStatement, this->block_index_, descriptorSetIter->second.descriptorSetId
        );
        context.descriptorSetHandleToInfo.erase(descriptorSetIter);
    }
}

template <typename T>
    requires std::same_as<T, Decoded_VkRenderPassCreateInfo> || std::same_as<T, Decoded_VkRenderPassCreateInfo2>
void VulkanSqliteConsumerExt::CreateRenderPass(
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<T>* pCreateInfo,
    HandlePointerDecoder<VkRenderPass>* pRenderPass
)
{
    auto [renderPassValid, renderPass] = GetHandle(pRenderPass);
    if (!renderPassValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass, invalid pRenderPass handle");
        }
        return;
    }
    // For IntelliSense, use GetMetaStructPointer((StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>*)pCreateInfo)
    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto deviceId = context.GetDeviceId(device);
    auto renderPassId =
        statements.InsertRenderPass(renderPass, deviceId, createInfo->decoded_value->flags, this->block_index_);

    auto [attachmentsValid, attachments, attachmentsCount] = GetMetaStructArray(createInfo->pAttachments);
    if (attachmentsValid)
    {
        for (size_t i = 0; i < attachmentsCount; ++i)
        {
            auto& attachment = attachments[i];
            statements.InsertRenderPassAttachment(
                renderPassId,
                i,
                attachment.decoded_value->flags,
                attachment.decoded_value->format,
                attachment.decoded_value->samples,
                attachment.decoded_value->loadOp,
                attachment.decoded_value->storeOp,
                attachment.decoded_value->stencilLoadOp,
                attachment.decoded_value->stencilStoreOp,
                attachment.decoded_value->initialLayout,
                attachment.decoded_value->finalLayout
            );
        }
    }

    auto [subpassesValid, subpasses, subpassesCount] = GetMetaStructArray(createInfo->pSubpasses);
    if (subpassesValid)
    {
        for (size_t subpassIndex = 0; subpassIndex < subpassesCount; ++subpassIndex)
        {
            auto& subpass = subpasses[subpassIndex];
            if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
            {
                LogUnsupportedPNext(subpass.pNext);
            }
            auto flags = subpass.decoded_value->flags;
            auto pipelineBindPoint = subpass.decoded_value->pipelineBindPoint;
            statements.InsertRenderSubpass(renderPassId, subpassIndex, flags, pipelineBindPoint);

            for (size_t attachmentIndex = 0; attachmentIndex < attachmentsCount; ++attachmentIndex)
            {
                statements.InsertBlankRenderSubpassAttachmentReference(renderPassId, subpassIndex, attachmentIndex);
            }

            auto [inputAttachmentsValid, inputAttachments, inputAttachmentCount] =
                GetMetaStructArray(subpass.pInputAttachments);
            if (inputAttachmentsValid)
            {
                for (size_t j = 0; j < inputAttachmentCount; ++j)
                {
                    auto& inputAttachment = inputAttachments[j];
                    if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
                    {
                        LogUnsupportedPNext(inputAttachment.pNext);
                    }
                    auto attachment = inputAttachment.decoded_value->attachment;
                    if (attachment != VK_ATTACHMENT_UNUSED)
                    {
                        auto layout = inputAttachment.decoded_value->layout;
                        statements.UpdateSubpassAttachmentReferenceLayout(
                            statements.renderSubpassSetAttachmentReferenceInputLayoutUpdateStatement,
                            renderPassId,
                            subpassIndex,
                            attachment,
                            layout
                        );
                    }
                }
            }
            auto [colorAttachmentsValid, colorAttachments, colorAttachmentCount] =
                GetMetaStructArray(subpass.pColorAttachments);
            auto [resolveAttachmentsValid, resolveAttachments, resolveAttachmentCount] =
                GetMetaStructArray(subpass.pResolveAttachments);
            if (colorAttachmentsValid)
            {
                for (size_t j = 0; j < colorAttachmentCount; ++j)
                {
                    auto& colorAttachment = colorAttachments[j];
                    if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
                    {
                        LogUnsupportedPNext(colorAttachment.pNext);
                    }
                    auto attachment = colorAttachment.decoded_value->attachment;
                    if (attachment != VK_ATTACHMENT_UNUSED)
                    {
                        auto layoutColor = colorAttachment.decoded_value->layout;
                        statements.UpdateSubpassAttachmentReferenceLayout(
                            statements.renderSubpassSetAttachmentReferenceColorLayoutUpdateStatement,
                            renderPassId,
                            subpassIndex,
                            attachment,
                            layoutColor
                        );
                    }

                    if (resolveAttachmentsValid && j < resolveAttachmentCount)
                    {
                        auto& resolveAttachment = resolveAttachments[j];
                        if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
                        {
                            LogUnsupportedPNext(resolveAttachment.pNext);
                        }
                        auto attachmentResolve = resolveAttachment.decoded_value->attachment;
                        if (attachmentResolve != VK_ATTACHMENT_UNUSED)
                        {
                            auto layoutResolve = resolveAttachment.decoded_value->layout;
                            statements.UpdateSubpassAttachmentReferenceLayout(
                                statements.renderSubpassSetAttachmentReferenceResolveLayoutUpdateStatement,
                                renderPassId,
                                subpassIndex,
                                attachmentResolve,
                                layoutResolve
                            );
                        }
                    }
                }
            }
            auto [preserveAttachmentsValid, preserveAttachments, preserveAttachmentCount] =
                GetPointerArray(&subpass.pPreserveAttachments);
            if (preserveAttachmentCount)
            {
                for (size_t j = 0; j < preserveAttachmentCount; ++j)
                {
                    statements.UpdateSubpassAttachmentReferencePreserve(
                        renderPassId, subpassIndex, preserveAttachments[j]
                    );
                }
            }
            auto [depthStencilAttachmentValid, depthStencilAttachment] =
                GetMetaStructPointer(subpass.pDepthStencilAttachment);
            if (depthStencilAttachmentValid)
            {
                if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
                {
                    LogUnsupportedPNext(depthStencilAttachment->pNext);
                }
                auto attachment = depthStencilAttachment->decoded_value->attachment;
                if (attachment != VK_ATTACHMENT_UNUSED)
                {
                    auto layout = depthStencilAttachment->decoded_value->layout;
                    statements.UpdateSubpassAttachmentReferenceLayout(
                        statements.renderSubpassSetAttachmentReferenceDepthStencilLayoutUpdateStatement,
                        renderPassId,
                        subpassIndex,
                        attachment,
                        layout
                    );
                }
            }
        }
    }

    auto [dependenciesValid, dependencies, dependenciesCount] = GetMetaStructArray(createInfo->pDependencies);
    if (dependenciesValid)
    {
        for (size_t i = 0; i < dependenciesCount; ++i)
        {
            auto& dependency = dependencies[i];
            if constexpr (std::is_same_v<T, Decoded_VkRenderPassCreateInfo2>)
            {
                LogUnsupportedPNext(dependency.pNext);
            }
            statements.InsertSubpassDependencies(
                renderPassId,
                dependency.decoded_value->srcSubpass,
                dependency.decoded_value->dstSubpass,
                dependency.decoded_value->srcStageMask,
                dependency.decoded_value->dstStageMask,
                dependency.decoded_value->srcAccessMask,
                dependency.decoded_value->dstAccessMask,
                dependency.decoded_value->dependencyFlags
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateRenderPass(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>* pRenderPass
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateRenderPass(
        call_info, returnValue, device, pCreateInfo, pAllocator, pRenderPass
    );

    CreateRenderPass(returnValue, device, pCreateInfo, pRenderPass);
}

void VulkanSqliteConsumerExt::Process_vkCreateRenderPass2(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>* pRenderPass
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateRenderPass2(
        call_info, returnValue, device, pCreateInfo, pAllocator, pRenderPass
    );

    CreateRenderPass(returnValue, device, pCreateInfo, pRenderPass);
}

void VulkanSqliteConsumerExt::Process_vkCreateRenderPass2KHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkRenderPassCreateInfo2>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkRenderPass>* pRenderPass
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateRenderPass2KHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pRenderPass
    );

    CreateRenderPass(returnValue, device, pCreateInfo, pRenderPass);
}

void VulkanSqliteConsumerExt::Process_vkDestroyRenderPass(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId renderPass,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyRenderPass(call_info, device, renderPass, pAllocator);

    if (auto id = context.ExtractId(renderPass, context.renderPassHandleToId, "renderPass", this->block_index_))
    {
        statements.DestroyObject(statements.destroyRenderPassUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::CreateSamplerYcbcrConversion(
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
)
{
    auto [conversionValid, conversion] = GetHandle(pYcbcrConversion);
    if (!conversionValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to create sampler ycbcr conversion, invalid pSamplerYcbcrConversion handle"
            );
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create sampler ycbcr conversion, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    statements.InsertSamplerYcbcrConversion(
        conversion,
        device,
        createInfo->decoded_value->format,
        createInfo->decoded_value->ycbcrModel,
        createInfo->decoded_value->ycbcrRange,
        createInfo->decoded_value->components,
        createInfo->decoded_value->xChromaOffset,
        createInfo->decoded_value->yChromaOffset,
        createInfo->decoded_value->chromaFilter,
        createInfo->decoded_value->forceExplicitReconstruction,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateSamplerYcbcrConversion(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSamplerYcbcrConversion(
        call_info, returnValue, device, pCreateInfo, pAllocator, pYcbcrConversion
    );

    CreateSamplerYcbcrConversion(returnValue, device, pCreateInfo, pYcbcrConversion);
}

void VulkanSqliteConsumerExt::Process_vkCreateSamplerYcbcrConversionKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSamplerYcbcrConversionCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSamplerYcbcrConversion>* pYcbcrConversion
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSamplerYcbcrConversionKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pYcbcrConversion
    );

    CreateSamplerYcbcrConversion(returnValue, device, pCreateInfo, pYcbcrConversion);
}

void VulkanSqliteConsumerExt::DestroySamplerYcbcrConversion(format::HandleId ycbcrConversion)
{
    if (auto id = context.ExtractId(
            ycbcrConversion, context.samplerYcbcrConversionHandleToId, "ycbcrConversion", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroySamplerYcbcrConversionUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroySamplerYcbcrConversion(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroySamplerYcbcrConversion(call_info, device, ycbcrConversion, pAllocator);

    DestroySamplerYcbcrConversion(ycbcrConversion);
}

void VulkanSqliteConsumerExt::Process_vkDestroySamplerYcbcrConversionKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId ycbcrConversion,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroySamplerYcbcrConversionKHR(call_info, device, ycbcrConversion, pAllocator);

    DestroySamplerYcbcrConversion(ycbcrConversion);
}

void VulkanSqliteConsumerExt::CreatePrivateDataSlot(
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
)
{
    auto [dataSlotValid, dataSlot] = GetHandle(pPrivateDataSlot);
    if (!dataSlotValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create private data slot, invalid pPrivateDataSlot handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create private data slot, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    statements.InsertPrivateDataSlot(dataSlot, device, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkCreatePrivateDataSlot(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreatePrivateDataSlot(
        call_info, returnValue, device, pCreateInfo, pAllocator, pPrivateDataSlot
    );

    CreatePrivateDataSlot(returnValue, device, pCreateInfo, pPrivateDataSlot);
}

void VulkanSqliteConsumerExt::Process_vkCreatePrivateDataSlotEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPrivateDataSlotCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPrivateDataSlot>* pPrivateDataSlot
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreatePrivateDataSlotEXT(
        call_info, returnValue, device, pCreateInfo, pAllocator, pPrivateDataSlot
    );

    CreatePrivateDataSlot(returnValue, device, pCreateInfo, pPrivateDataSlot);
}

void VulkanSqliteConsumerExt::DestroyPrivateDataSlot(format::HandleId privateDataSlot)
{
    if (auto id = context.ExtractId(
            privateDataSlot, context.privateDataSlotHandleToId, "privateDataSlot", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyPrivateDataSlotUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyPrivateDataSlot(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPrivateDataSlot(call_info, device, privateDataSlot, pAllocator);

    DestroyPrivateDataSlot(privateDataSlot);
}

void VulkanSqliteConsumerExt::Process_vkDestroyPrivateDataSlotEXT(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId privateDataSlot,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPrivateDataSlotEXT(call_info, device, privateDataSlot, pAllocator);

    DestroyPrivateDataSlot(privateDataSlot);
}

void VulkanSqliteConsumerExt::Process_vkCmdBindDescriptorSets(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    format::HandleId layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    HandlePointerDecoder<VkDescriptorSet>* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    PointerDecoder<uint32_t>* pDynamicOffsets
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets(
        call_info,
        commandBuffer,
        pipelineBindPoint,
        layout,
        firstSet,
        descriptorSetCount,
        pDescriptorSets,
        dynamicOffsetCount,
        pDynamicOffsets
    );

    auto [descriptorSetsValid, descriptorSets, descriptorSetsCount] = GetHandleArray(pDescriptorSets);
    if (!descriptorSetsValid)
    {
        LOG_CMD_WARNING("Failed to bind descriptor sets, invalid pDescriptorSets");
        return;
    }

    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        LOG_CMD_WARNING(
            "Failed to bind descriptor sets, failed to find command buffer recording for command buffer with handle "
            "%" PRIi64,
            commandBuffer
        );
        return;
    }
    auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(layout));
    if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
    {
        LOG_CMD_WARNING("Failed to bind descriptor sets, failed to find pipeline layout with handle %" PRIi64, layout);
        return;
    }

    auto [dynamicOffsetValid, dynamicOffsets, dynamicOffsetsCount] = GetPointerArray(pDynamicOffsets);
    uint32_t dynamicOffsetIndex = 0;

    for (size_t i = 0; i < descriptorSetsCount; ++i)
    {
        auto descriptorSet = descriptorSets[i];
        auto descriptorSetIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorSet));
        if (descriptorSetIter == context.descriptorSetHandleToInfo.end())
        {
            LOG_CMD_WARNING(
                "Failed to bind descriptor set, failed to find descriptor set with handle %" PRIi64, descriptorSet
            );
            continue;
        }
        auto setIndex = firstSet + static_cast<uint32_t>(i);

        // we need to generate stage flags based on the pipeline bind point since that is used
        // for filtering and vkCmdBindDescriptorSets does not configure at the stage level
        // we simply gather all stages that apply to the given bind point.
        VkShaderStageFlags stageFlags = 0;
        switch (pipelineBindPoint)
        {
            case VK_PIPELINE_BIND_POINT_GRAPHICS:
                stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS | VK_SHADER_STAGE_TASK_BIT_EXT |
                    VK_SHADER_STAGE_MESH_BIT_EXT | VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI;
                break;
            case VK_PIPELINE_BIND_POINT_COMPUTE:
                stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
                break;
            case VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR:
                stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR |
                    VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR |
                    VK_SHADER_STAGE_INTERSECTION_BIT_KHR | VK_SHADER_STAGE_CALLABLE_BIT_KHR;
                break;
            case VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI:
                stageFlags = VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI;
                break;
            default:
                LOG_CMD_WARNING(
                    "Failed to set descriptor set stage flags, unknown pipeline bind point %" PRIi64, pipelineBindPoint
                );
        }

        auto stateId = statements.InsertStateDescriptorSetBinding(
            this->block_index_,
            commandBufferRecordingIter->second,
            setIndex,
            stageFlags,
            pipelineLayoutIter->second,
            descriptorSetIter->second.descriptorSetId
        );

        auto descriptorSetLayoutIter = context.descriptorSetLayoutToInfo.find(descriptorSetIter->second.layoutId);
        if (descriptorSetLayoutIter != context.descriptorSetLayoutToInfo.end())
        {
            for (auto descriptorSetLayoutBindingIter = descriptorSetLayoutIter->second.bindings.begin();
                 descriptorSetLayoutBindingIter != descriptorSetLayoutIter->second.bindings.end();
                 ++descriptorSetLayoutBindingIter)
            {
                if (descriptorSetLayoutBindingIter->second.descriptorType ==
                        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
                    descriptorSetLayoutBindingIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
                {
                    for (uint32_t j = 0; j < descriptorSetLayoutBindingIter->second.descriptorCount;
                         ++j, ++dynamicOffsetIndex)
                    {
                        if (dynamicOffsetIndex < dynamicOffsetsCount)
                        {
                            statements.InsertStateDescriptorSetBindingDynamicOffset(
                                stateId,
                                static_cast<uint32_t>(descriptorSetLayoutBindingIter->first),
                                j,
                                dynamicOffsets[dynamicOffsetIndex]
                            );
                        }
                        else
                        {
                            LOG_CMD_WARNING(
                                "Failed to add descriptor set dynamic offset, invalid number of dynamic offsets"
                            );
                            break;
                        }
                    }
                }
            }
        }
    }
}

void VulkanSqliteConsumerExt::BindDescriptorSets2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
)
{
    auto [descriptorSetsInfoValid, descriptorSetsInfo] = GetMetaStructPointer(pBindDescriptorSetsInfo);
    if (!descriptorSetsInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind descriptor sets, invalid pBindDescriptorSetsInfo");
        return;
    }

    LogUnsupportedPNext(descriptorSetsInfo->pNext);

    auto [descriptorSetsValid, descriptorSets, descriptorSetsCount] =
        GetHandleArray(&descriptorSetsInfo->pDescriptorSets);
    if (!descriptorSetsValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind descriptor sets, invalid pDescriptorSets");
        return;
    }
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind descriptor sets, failed to find command buffer recording for command buffer with handle "
            "%" PRIi64,
            commandBuffer
        );
        return;
    }
    auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(descriptorSetsInfo->layout));
    if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind descriptor sets, failed to find pipeline layout with handle %" PRIi64,
            descriptorSetsInfo->layout
        );
        return;
    }

    auto [dynamicOffsetValid, dynamicOffsets, dynamicOffsetsCount] =
        GetPointerArray(&descriptorSetsInfo->pDynamicOffsets);
    uint32_t dynamicOffsetIndex = 0;

    for (size_t i = 0; i < descriptorSetsCount; ++i)
    {
        auto descriptorSet = descriptorSets[i];
        auto descriptorSetIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorSet));
        if (descriptorSetIter == context.descriptorSetHandleToInfo.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to bind descriptor set, failed to find descriptor set with handle %" PRIi64, descriptorSet
            );
            continue;
        }
        auto binding = descriptorSetsInfo->decoded_value->firstSet + static_cast<uint32_t>(i);

        auto stateId = statements.InsertStateDescriptorSetBinding(
            this->block_index_,
            commandBufferRecordingIter->second,
            binding,
            descriptorSetsInfo->decoded_value->stageFlags,
            pipelineLayoutIter->second,
            descriptorSetIter->second.descriptorSetId
        );

        auto descriptorSetLayoutIter = context.descriptorSetLayoutToInfo.find(descriptorSetIter->second.layoutId);
        if (descriptorSetLayoutIter != context.descriptorSetLayoutToInfo.end())
        {
            for (auto descriptorSetLayoutBindingIter = descriptorSetLayoutIter->second.bindings.begin();
                 descriptorSetLayoutBindingIter != descriptorSetLayoutIter->second.bindings.end();
                 ++descriptorSetLayoutBindingIter)
            {
                if (descriptorSetLayoutBindingIter->second.descriptorType ==
                        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
                    descriptorSetLayoutBindingIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
                {
                    for (uint32_t j = 0; j < descriptorSetLayoutBindingIter->second.descriptorCount;
                         ++j, ++dynamicOffsetIndex)
                    {
                        if (dynamicOffsetIndex < dynamicOffsetsCount)
                        {
                            statements.InsertStateDescriptorSetBindingDynamicOffset(
                                stateId,
                                static_cast<uint32_t>(descriptorSetLayoutBindingIter->first),
                                j,
                                dynamicOffsets[dynamicOffsetIndex]
                            );
                        }
                        else
                        {
                            GFXRECON_SQLITE_LOG_WARNING(
                                "Failed to add descriptor set dynamic offset, invalid number of dynamic offsets"
                            );
                            break;
                        }
                    }
                }
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdBindDescriptorSets2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets2(call_info, commandBuffer, pBindDescriptorSetsInfo);

    BindDescriptorSets2(commandBuffer, pBindDescriptorSetsInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdBindDescriptorSets2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkBindDescriptorSetsInfo>* pBindDescriptorSetsInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets2KHR(call_info, commandBuffer, pBindDescriptorSetsInfo);

    BindDescriptorSets2(commandBuffer, pBindDescriptorSetsInfo);
}

void VulkanSqliteConsumerExt::CreateDescriptorUpdateTemplate(
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
)
{
    auto [updateTemplateValid, updateTemplate] = GetHandle(pDescriptorUpdateTemplate);
    if (!updateTemplateValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to create descriptor update template, invalid pDescriptorUpdateTemplate handle"
            );
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create descriptor update template, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    // Some fields are only valid based on templateType, and are ignored otherwise (and may be garbage data).
    std::optional<int64_t> descriptorSetLayout = std::nullopt;
    std::optional<VkPipelineBindPoint> pipelineBindPoint = std::nullopt;
    std::optional<int64_t> pipelineLayout = std::nullopt;
    std::optional<uint32_t> setIndex = std::nullopt;
    if (createInfo->decoded_value->templateType == VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET)
    {
        descriptorSetLayout = context.GetDescriptorSetLayoutId(createInfo->descriptorSetLayout);
    }
    else if (createInfo->decoded_value->templateType == VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS)
    {
        pipelineBindPoint = createInfo->decoded_value->pipelineBindPoint;
        pipelineLayout = context.GetPipelineLayoutId(createInfo->pipelineLayout);
        setIndex = createInfo->decoded_value->set;
    }

    auto descriptorUpdateTemplateId = statements.InsertDescriptorUpdateTemplate(
        updateTemplate,
        device,
        createInfo->decoded_value->flags,
        createInfo->decoded_value->templateType,
        descriptorSetLayout,
        pipelineBindPoint,
        pipelineLayout,
        setIndex,
        this->block_index_
    );

    auto [entriesValid, entries, entryCount] = GetMetaStructArray(createInfo->pDescriptorUpdateEntries);

    if (entriesValid)
    {
        for (size_t i = 0; i < entryCount; ++i)
        {
            statements.InsertDescriptorUpdateTemplateEntry(descriptorUpdateTemplateId, entries[i].decoded_value);
        }
    }

    size_t numBytes = graphics::vulkan_struct_deep_copy(createInfo->decoded_value, 1, nullptr);
    std::unique_ptr<uint8_t[]> createInfoData = std::make_unique<uint8_t[]>(numBytes);
    graphics::vulkan_struct_deep_copy(createInfo->decoded_value, 1, createInfoData.get());
    const auto* copiedCreateInfo = reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo*>(createInfoData.get());

    context.descriptorUpdateTemplateInfo.emplace(
        descriptorUpdateTemplateId, std::make_pair(copiedCreateInfo, std::move(createInfoData))
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateDescriptorUpdateTemplate(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDescriptorUpdateTemplate(
        call_info, returnValue, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate
    );

    CreateDescriptorUpdateTemplate(returnValue, device, pCreateInfo, pDescriptorUpdateTemplate);
}

void VulkanSqliteConsumerExt::Process_vkCreateDescriptorUpdateTemplateKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDescriptorUpdateTemplateCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDescriptorUpdateTemplate>* pDescriptorUpdateTemplate
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDescriptorUpdateTemplateKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate
    );

    CreateDescriptorUpdateTemplate(returnValue, device, pCreateInfo, pDescriptorUpdateTemplate);
}

void VulkanSqliteConsumerExt::DestroyDescriptorUpdateTemplate(format::HandleId descriptorUpdateTemplate)
{
    if (auto id = context.ExtractId(
            descriptorUpdateTemplate,
            context.descriptorUpdateTemplateHandleToId,
            "descriptorUpdateTemplate",
            this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyDescriptorUpdateTemplateUpdateStatement, this->block_index_, *id);
        context.descriptorUpdateTemplateInfo.erase(*id);
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyDescriptorUpdateTemplate(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDescriptorUpdateTemplate(
        call_info, device, descriptorUpdateTemplate, pAllocator
    );

    DestroyDescriptorUpdateTemplate(descriptorUpdateTemplate);
}

void VulkanSqliteConsumerExt::Process_vkDestroyDescriptorUpdateTemplateKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorUpdateTemplate,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDescriptorUpdateTemplateKHR(
        call_info, device, descriptorUpdateTemplate, pAllocator
    );

    DestroyDescriptorUpdateTemplate(descriptorUpdateTemplate);
}

void VulkanSqliteConsumerExt::WriteDescriptorSet(
    format::HandleId device, const Decoded_VkWriteDescriptorSet& descriptorWrite
)
{
    auto descriptorSetDstIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorWrite.dstSet));
    if (descriptorSetDstIter == context.descriptorSetHandleToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to write descriptor set, failed to find destination descriptor set with handle "
            "%" PRIu64,
            descriptorWrite.dstSet
        );
        return;
    }

    WriteOrPushDescriptorSet(
        device,
        descriptorWrite,
        descriptorSetDstIter->second.descriptorSetId,
        std::nullopt,
        descriptorSetDstIter->second.layoutId,
        false
    );
}

void VulkanSqliteConsumerExt::WriteOrPushDescriptorSet(
    format::HandleId device,
    const Decoded_VkWriteDescriptorSet& descriptorWrite,
    int64_t descriptorSetDst, // descriptor set ID for writes, descriptor set index for pushes
    std::optional<int64_t> commandBufferRecordingId,
    int64_t layoutId,
    bool isPush
)
{
    const auto arrayElement = descriptorWrite.decoded_value->dstArrayElement;
    const auto descriptorType = descriptorWrite.decoded_value->descriptorType;
    const auto descriptorCount = descriptorWrite.decoded_value->descriptorCount;
    const auto dstBinding = descriptorWrite.decoded_value->dstBinding;

    auto descriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(layoutId);
    if (descriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to write descriptor set, failed to find descriptor set layout binding for layout id "
            "%" PRIu64,
            layoutId
        );
        return;
    }

    auto bindingInfoIter = descriptorSetLayoutInfoIter->second.bindings.find(dstBinding);
    if (bindingInfoIter == descriptorSetLayoutInfoIter->second.bindings.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to write descriptor set, failed to find descriptor set layout binding info for layout id "
            "%" PRIu64 " binding %u",
            layoutId,
            dstBinding
        );
        return;
    }
    const auto initialBindingInfoIter = bindingInfoIter;

    auto [imageInfosValid, imageInfos, imageInfoCount] = GetMetaStructArray(descriptorWrite.pImageInfo);
    auto [bufferInfosValid, bufferInfos, bufferInfoCount] = GetMetaStructArray(descriptorWrite.pBufferInfo);
    auto [texelValid, texels, texelCount] = GetHandleArray(&descriptorWrite.pTexelBufferView);

    const Decoded_VkWriteDescriptorSetAccelerationStructureKHR* accelerationStructureInfo = nullptr;
    const Decoded_VkWriteDescriptorSetAccelerationStructureNV* accelerationStructureNvInfo = nullptr;

    auto pnext = descriptorWrite.pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkWriteDescriptorSetAccelerationStructureKHR>())
        {
            accelerationStructureInfo =
                reinterpret_cast<const Decoded_VkWriteDescriptorSetAccelerationStructureKHR*>(header);
        }
        else if (*header->sType == gfxrecon::util::GetSType<VkWriteDescriptorSetAccelerationStructureNV>())
        {
            accelerationStructureNvInfo =
                reinterpret_cast<const Decoded_VkWriteDescriptorSetAccelerationStructureNV*>(header);
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    auto [accelerationStructsValid, accelerationStructs, accelerationStructCount] =
        GetHandleArray(accelerationStructureInfo ? &accelerationStructureInfo->pAccelerationStructures : nullptr);
    auto [accelerationStructsNvValid, accelerationStructsNv, accelerationStructNvCount] =
        GetHandleArray(accelerationStructureNvInfo ? &accelerationStructureNvInfo->pAccelerationStructures : nullptr);

    auto binding = dstBinding;
    auto element = arrayElement;

    auto deviceId = context.GetDeviceId(device);
    bool nullDescriptorEnabled = false;
    if (deviceId.has_value())
    {
        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceId.value(), "nullDescriptor");
    }

    for (size_t i = 0; i < descriptorCount; ++i, ++element)
    {
        // check for rollover and layout binding info match
        // https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptorsets-updates-consecutive
        while (element >= bindingInfoIter->second.descriptorCount ||
               bindingInfoIter->second.descriptorType != initialBindingInfoIter->second.descriptorType ||
               bindingInfoIter->second.stageFlags != initialBindingInfoIter->second.stageFlags)
        {
            bindingInfoIter++;
            binding++;
            element = 0;
            if (bindingInfoIter == descriptorSetLayoutInfoIter->second.bindings.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to fully write descriptor set, failed to find descriptor set layout binding info for "
                    "layout id %" PRIu64 " binding %u",
                    layoutId,
                    binding
                );
                return;
            }
        }

        int64_t writeId;
        if (!isPush)
        {
            writeId = statements.InsertDescriptorSetWrite(
                descriptorSetDst, binding, element, descriptorType, this->block_index_
            );
        }
        else
        {
            writeId = statements.InsertStateDescriptorSetPush(
                this->block_index_,
                *commandBufferRecordingId,
                static_cast<uint32_t>(descriptorSetDst),
                binding,
                element,
                descriptorType
            );
        }

        if (descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
            descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
            descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE || descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
            descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
        {
            if (imageInfosValid && i < imageInfoCount)
            {
                auto& imageInfo = imageInfos[i];
                std::optional<int64_t> samplerId = std::nullopt;
                if (descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
                    descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                {
                    // value is only read if its a sampler type
                    // otherwise values can be invalid and out of range by default
                    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-00325
                    if (imageInfo.sampler != format::kNullHandleId || !nullDescriptorEnabled)
                    {
                        samplerId = context.GetSamplerId(imageInfo.sampler, true);
                    }
                }

                std::optional<int64_t> imageViewId = std::nullopt;
                if (descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
                    descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
                    descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
                    descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
                {
                    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-02996
                    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-07683
                    if (imageInfo.imageView != format::kNullHandleId || !nullDescriptorEnabled)
                    {
                        imageViewId = context.GetImageViewId(imageInfo.imageView, true);
                    }
                }

                statements.InsertDescriptorSetWriteImageInfo(
                    writeId, samplerId, imageViewId, imageInfo.decoded_value->imageLayout, isPush
                );
            }
        }

        if (descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
            descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
            descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
            descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
        {
            if (bufferInfosValid && i < bufferInfoCount)
            {
                auto& bufferInfo = bufferInfos[i];
                std::optional<int64_t> bufferId = std::nullopt;
                if (bufferInfo.buffer != format::kNullHandleId || !nullDescriptorEnabled)
                {
                    bufferId = context.GetBufferId(bufferInfo.buffer, true);
                }

                statements.InsertDescriptorSetWriteBufferInfo(
                    writeId, bufferId, bufferInfo.decoded_value->offset, bufferInfo.decoded_value->range, isPush
                );
            }
        }

        if (descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
            descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)
        {
            if (texelValid && i < texelCount)
            {
                auto texelBuffer = texels[i];
                std::optional<int64_t> bufferViewId = std::nullopt;
                if (texelBuffer != format::kNullHandleId || !nullDescriptorEnabled)
                {
                    bufferViewId = context.GetBufferViewId(texelBuffer, true);
                }

                statements.InsertDescriptorSetWriteTexelInfo(writeId, bufferViewId, isPush);
            }
        }

        if (descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR)
        {
            if (accelerationStructsValid && i < accelerationStructCount)
            {
                auto accelerationStructure = accelerationStructs[i];
                std::optional<int64_t> accelerationStructureId =
                    context.GetAccelerationStructureId(accelerationStructure, true);
                statements.InsertDescriptorSetWriteAccelerationInfo(writeId, accelerationStructureId, isPush);
            }
        }

        if (descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV)
        {
            if (accelerationStructsNvValid && i < accelerationStructNvCount)
            {
                auto accelerationStructureNv = accelerationStructsNv[i];
                std::optional<int64_t> accelerationStructureNvId =
                    context.GetAccelerationStructureNvId(accelerationStructureNv, true);
                statements.InsertDescriptorSetWriteAccelerationNvInfo(writeId, accelerationStructureNvId, isPush);
            }
        }
    }
}

void VulkanSqliteConsumerExt::CopyDescriptorSet(const Decoded_VkCopyDescriptorSet& descriptorCopy)
{
    auto descriptorSetSrcIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorCopy.srcSet));
    if (descriptorSetSrcIter == context.descriptorSetHandleToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find source descriptor set with handle %" PRIu64,
            descriptorCopy.srcSet
        );
        return;
    }
    auto descriptorSetDstIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorCopy.dstSet));
    if (descriptorSetDstIter == context.descriptorSetHandleToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find destination descriptor set with handle %" PRIu64,
            descriptorCopy.dstSet
        );
        return;
    }
    const auto srcBinding = descriptorCopy.decoded_value->srcBinding;
    const auto dstBinding = descriptorCopy.decoded_value->dstBinding;
    const auto arrayElementSrc = descriptorCopy.decoded_value->srcArrayElement;
    const auto arrayElementDst = descriptorCopy.decoded_value->dstArrayElement;
    const auto descriptorCount = descriptorCopy.decoded_value->descriptorCount;

    auto dstDescriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(descriptorSetDstIter->second.layoutId);
    if (dstDescriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find descriptor set layout binding for layout id "
            "%" PRIu64,
            descriptorSetDstIter->second.layoutId
        );
        return;
    }

    auto dstBindingInfoIter = dstDescriptorSetLayoutInfoIter->second.bindings.find(dstBinding);
    if (dstBindingInfoIter == dstDescriptorSetLayoutInfoIter->second.bindings.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find descriptor set layout binding info for layout id "
            "%" PRIu64 " binding %u",
            descriptorSetDstIter->second.layoutId,
            dstBinding
        );
        return;
    }
    auto srcDescriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(descriptorSetSrcIter->second.layoutId);
    if (srcDescriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find descriptor set layout binding for layout id "
            "%" PRIu64,
            descriptorSetSrcIter->second.layoutId
        );
        return;
    }

    auto srcBindingInfoIter = srcDescriptorSetLayoutInfoIter->second.bindings.find(srcBinding);
    if (srcBindingInfoIter == srcDescriptorSetLayoutInfoIter->second.bindings.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to copy descriptor set, failed to find descriptor set layout binding info for layout id "
            "%" PRIu64 " binding %u",
            descriptorSetSrcIter->second.layoutId,
            srcBinding
        );
        return;
    }

    const auto initialDstBindingInfoIter = dstBindingInfoIter;
    const auto initialSrcBindingInfoIter = srcBindingInfoIter;
    auto writeBinding = dstBinding;
    auto readBinding = srcBinding;
    auto dstElement = arrayElementDst;
    auto srcElement = arrayElementSrc;
    for (size_t i = 0; i < descriptorCount; ++i, ++dstElement, ++srcElement)
    {
        // check for rollover and layout binding info match
        // https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptorsets-updates-consecutive
        while (dstElement >= dstBindingInfoIter->second.descriptorCount ||
               dstBindingInfoIter->second.descriptorType != initialDstBindingInfoIter->second.descriptorType ||
               dstBindingInfoIter->second.stageFlags != initialDstBindingInfoIter->second.stageFlags)
        {
            dstBindingInfoIter++;
            writeBinding++;
            dstElement = 0;
            if (dstBindingInfoIter == dstDescriptorSetLayoutInfoIter->second.bindings.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to fully copy descriptor set, failed to find descriptor set layout binding info for "
                    "layout id %" PRIu64 " binding %u",
                    descriptorSetDstIter->second.layoutId,
                    writeBinding
                );
                return;
            }
        }
        while (srcElement >= srcBindingInfoIter->second.descriptorCount ||
               srcBindingInfoIter->second.descriptorType != initialSrcBindingInfoIter->second.descriptorType ||
               srcBindingInfoIter->second.stageFlags != initialSrcBindingInfoIter->second.stageFlags)
        {
            srcBindingInfoIter++;
            readBinding++;
            srcElement = 0;
            if (srcBindingInfoIter == srcDescriptorSetLayoutInfoIter->second.bindings.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to fully copy descriptor set, failed to find descriptor set layout binding info for "
                    "layout id %" PRIu64 " binding %u",
                    descriptorSetSrcIter->second.layoutId,
                    readBinding
                );
                return;
            }
        }

        auto writeId = statements.InsertDescriptorSetWrite(
            descriptorSetDstIter->second.descriptorSetId,
            writeBinding,
            dstElement,
            initialSrcBindingInfoIter->second.descriptorType,
            this->block_index_
        );

        // we don't use the descriptor set copy src information in the
        // frontend UI so we don't need to store it

        if (initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
        {
            statements.CopyDescriptorSetInfo(
                statements.descriptorSetCopyBufferInfoInsertStatement,
                descriptorSetSrcIter->second.descriptorSetId,
                readBinding,
                srcElement,
                writeId
            );
        }

        if (initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
        {
            statements.CopyDescriptorSetInfo(
                statements.descriptorSetCopyImageInfoInsertStatement,
                descriptorSetSrcIter->second.descriptorSetId,
                readBinding,
                srcElement,
                writeId
            );
        }

        if (initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
            initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)
        {
            statements.CopyDescriptorSetInfo(
                statements.descriptorSetCopyTexelInfoInsertStatement,
                descriptorSetSrcIter->second.descriptorSetId,
                readBinding,
                srcElement,
                writeId
            );
        }

        if (initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR)
        {
            statements.CopyDescriptorSetInfo(
                statements.descriptorSetCopyAccelerationInfoInsertStatement,
                descriptorSetSrcIter->second.descriptorSetId,
                readBinding,
                srcElement,
                writeId
            );
        }

        if (initialDstBindingInfoIter->second.descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV)
        {
            statements.CopyDescriptorSetInfo(
                statements.descriptorSetCopyAccelerationNvInfoInsertStatement,
                descriptorSetSrcIter->second.descriptorSetId,
                readBinding,
                srcElement,
                writeId
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkUpdateDescriptorSets(
    const ApiCallInfo& call_info,
    format::HandleId device,
    uint32_t descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    StructPointerDecoder<Decoded_VkCopyDescriptorSet>* pDescriptorCopies
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkUpdateDescriptorSets(
        call_info, device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies
    );

    auto [descriptorWritesValid, descriptorWrites, descriptorWritesCount] = GetMetaStructArray(pDescriptorWrites);
    if (descriptorWritesValid)
    {
        for (size_t i = 0; i < descriptorWritesCount; ++i)
        {
            WriteDescriptorSet(device, descriptorWrites[i]);
        }
    }

    auto [descriptorCopiesValid, descriptorCopies, descriptorCopiesCount] = GetMetaStructArray(pDescriptorCopies);
    if (descriptorCopiesValid)
    {
        for (size_t i = 0; i < descriptorCopiesCount; ++i)
        {
            auto& descriptorCopy = descriptorCopies[i];
            CopyDescriptorSet(descriptorCopy);
        }
    }
}

void VulkanSqliteConsumerExt::WriteOrPushDescriptorSetWithTemplate(
    format::HandleId device,
    int64_t descriptorSetDst, // descriptor set ID for writes, descriptor set index for pushes
    std::optional<int64_t> commandBufferRecordingId,
    int64_t layoutId,
    format::HandleId descriptorUpdateTemplate,
    const DescriptorUpdateTemplateDecoder* pData,
    bool isPush
)
{
    auto descriptorUpdateTemplateIter =
        context.descriptorUpdateTemplateHandleToId.find(ToInt64(descriptorUpdateTemplate));
    if (descriptorUpdateTemplateIter == context.descriptorUpdateTemplateHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to update descriptor set with template; no template found with handle %" PRIu64,
            descriptorUpdateTemplate
        );
        return;
    }
    int64_t descriptorUpdateTemplateId = descriptorUpdateTemplateIter->second;

    auto descriptorUpdateTemplateInfoIter = context.descriptorUpdateTemplateInfo.find(descriptorUpdateTemplateId);
    if (descriptorUpdateTemplateInfoIter == context.descriptorUpdateTemplateInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to update descriptor set with template; no template found with id %" PRIi64,
            descriptorUpdateTemplateId
        );
        return;
    }

    const VkDescriptorUpdateTemplateCreateInfo* descriptorUpdateTemplateInfo =
        descriptorUpdateTemplateInfoIter->second.first;

    size_t imageInfoCount = 0;
    size_t bufferInfoCount = 0;
    size_t texelBufferViewCount = 0;
    size_t accelerationStructCount = 0;

    bool nullDescriptorEnabled = false;
    auto deviceId = context.GetDeviceId(device);
    if (deviceId.has_value())
    {
        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceId.value(), "nullDescriptor");
    }

    for (size_t entryIdx = 0; entryIdx < descriptorUpdateTemplateInfo->descriptorUpdateEntryCount; entryIdx++)
    {
        const auto& entry = descriptorUpdateTemplateInfo->pDescriptorUpdateEntries[entryIdx];

        auto descriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(layoutId);
        if (descriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to write descriptor set, failed to find descriptor set layout binding for layout id "
                "%" PRIu64,
                layoutId
            );
            return;
        }

        auto bindingInfoIter = descriptorSetLayoutInfoIter->second.bindings.find(entry.dstBinding);
        if (bindingInfoIter == descriptorSetLayoutInfoIter->second.bindings.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to write descriptor set, failed to find descriptor set layout binding info for layout id "
                "%" PRIu64 " binding %u",
                layoutId,
                entry.dstBinding
            );
            return;
        }
        const auto initialBindingInfoIter = bindingInfoIter;

        auto binding = entry.dstBinding;
        auto element = entry.dstArrayElement;
        for (size_t i = 0; i < entry.descriptorCount; ++i, ++element)
        {
            // check for rollover and layout binding info match
            // https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptorsets-updates-consecutive
            while (element >= bindingInfoIter->second.descriptorCount ||
                   bindingInfoIter->second.descriptorType != initialBindingInfoIter->second.descriptorType ||
                   bindingInfoIter->second.stageFlags != initialBindingInfoIter->second.stageFlags)
            {
                bindingInfoIter++;
                binding++;
                element = 0;
                if (bindingInfoIter == descriptorSetLayoutInfoIter->second.bindings.end())
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to fully write descriptor set, failed to find descriptor set layout binding info for "
                        "layout id %" PRIu64 " binding %u",
                        layoutId,
                        binding
                    );
                    return;
                }
            }

            int64_t writeId;
            if (!isPush)
            {
                writeId = statements.InsertDescriptorSetWrite(
                    descriptorSetDst, binding, element, entry.descriptorType, this->block_index_
                );
            }
            else
            {
                writeId = statements.InsertStateDescriptorSetPush(
                    this->block_index_,
                    *commandBufferRecordingId,
                    static_cast<uint32_t>(descriptorSetDst),
                    binding,
                    element,
                    entry.descriptorType
                );
            }

            if (entry.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
            {
                if (imageInfoCount < pData->GetImageInfoCount())
                {
                    auto& imageInfo = pData->GetImageInfoMetaStructPointer()[imageInfoCount];
                    std::optional<int64_t> samplerId = std::nullopt;
                    if (entry.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
                        entry.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                    {
                        // value is only read if its a sampler type
                        // otherwise values can be invalid and out of range by default
                        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-00325
                        if (imageInfo.sampler != format::kNullHandleId || !nullDescriptorEnabled)
                        {
                            samplerId = context.GetSamplerId(imageInfo.sampler, true);
                        }
                    }

                    std::optional<int64_t> imageViewId = std::nullopt;
                    if (entry.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
                        entry.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
                        entry.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
                        entry.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
                    {
                        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-02996
                        // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-07683
                        if (imageInfo.imageView != format::kNullHandleId || !nullDescriptorEnabled)
                        {
                            imageViewId = context.GetImageViewId(imageInfo.imageView, true);
                        }
                    }

                    statements.InsertDescriptorSetWriteImageInfo(
                        writeId, samplerId, imageViewId, imageInfo.decoded_value->imageLayout, isPush
                    );
                }
                imageInfoCount++;
            }

            if (entry.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
            {
                if (bufferInfoCount < pData->GetBufferInfoCount())
                {
                    auto& bufferInfo = pData->GetBufferInfoMetaStructPointer()[bufferInfoCount];
                    std::optional<int64_t> bufferId = std::nullopt;
                    if (bufferInfo.buffer != format::kNullHandleId || !nullDescriptorEnabled)
                    {
                        bufferId = context.GetBufferId(bufferInfo.buffer, true);
                    }

                    statements.InsertDescriptorSetWriteBufferInfo(
                        writeId, bufferId, bufferInfo.decoded_value->offset, bufferInfo.decoded_value->range, isPush
                    );
                }
                bufferInfoCount++;
            }

            if (entry.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
                entry.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)
            {
                if (texelBufferViewCount < pData->GetTexelBufferViewCount())
                {
                    auto texelBuffer = pData->GetTexelBufferViewHandleIdsPointer()[texelBufferViewCount];
                    std::optional<int64_t> bufferViewId = std::nullopt;
                    if (texelBuffer != format::kNullHandleId || !nullDescriptorEnabled)
                    {
                        bufferViewId = context.GetBufferViewId(texelBuffer, true);
                    }

                    statements.InsertDescriptorSetWriteTexelInfo(writeId, bufferViewId, isPush);
                }
                texelBufferViewCount++;
            }

            if (entry.descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR)
            {
                if (accelerationStructCount < pData->GetAccelerationStructureKHRCount())
                {
                    auto accelerationStructure =
                        pData->GetAccelerationStructureKHRHandleIdsPointer()[accelerationStructCount];
                    std::optional<int64_t> accelerationStructureId =
                        context.GetAccelerationStructureId(accelerationStructure, true);
                    statements.InsertDescriptorSetWriteAccelerationInfo(writeId, accelerationStructureId, isPush);
                }
                accelerationStructCount++;
            }

            if (entry.descriptorType == VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV)
            {
                // TODO verify this and add reference link
                GFXRECON_LOG_WARNING(
                    "VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV with descriptor update templates is not supported by "
                    "GFXR; ignoring"
                );
            }
        }
    }

    // We should have read everything from the template.
    if (imageInfoCount != pData->GetImageInfoCount())
    {
        GFXRECON_LOG_WARNING(
            "Descriptor update had %" PRIu64 " image infos while template had %" PRIu64,
            imageInfoCount,
            pData->GetImageInfoCount()
        );
    }
    if (bufferInfoCount != pData->GetBufferInfoCount())
    {
        GFXRECON_LOG_WARNING(
            "Descriptor update had %" PRIu64 " buffer infos while template had %" PRIu64,
            bufferInfoCount,
            pData->GetBufferInfoCount()
        );
    }
    if (texelBufferViewCount != pData->GetTexelBufferViewCount())
    {
        GFXRECON_LOG_WARNING(
            "Descriptor update had %" PRIu64 " texel buffer views while template had %" PRIu64,
            texelBufferViewCount,
            pData->GetTexelBufferViewCount()
        );
    }
    if (accelerationStructCount != pData->GetAccelerationStructureKHRCount())
    {
        GFXRECON_LOG_WARNING(
            "Descriptor update had %" PRIu64 " acceleration structures while template had %" PRIu64,
            accelerationStructCount,
            pData->GetAccelerationStructureKHRCount()
        );
    }
}

void VulkanSqliteConsumerExt::WriteDescriptorSetWithTemplate(
    format::HandleId device,
    format::HandleId descriptorSet,
    format::HandleId descriptorUpdateTemplate,
    const DescriptorUpdateTemplateDecoder* pData
)
{
    auto descriptorSetDstIter = context.descriptorSetHandleToInfo.find(ToInt64(descriptorSet));
    if (descriptorSetDstIter == context.descriptorSetHandleToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to update descriptor set with template; no descriptor set found with handle %" PRIu64, descriptorSet
        );
        return;
    }

    WriteOrPushDescriptorSetWithTemplate(
        device,
        descriptorSetDstIter->second.descriptorSetId,
        std::nullopt,
        descriptorSetDstIter->second.layoutId,
        descriptorUpdateTemplate,
        pData,
        false
    );
}

void VulkanSqliteConsumerExt::Process_vkUpdateDescriptorSetWithTemplate(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorSet,
    format::HandleId descriptorUpdateTemplate,
    DescriptorUpdateTemplateDecoder* pData
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkUpdateDescriptorSetWithTemplate(
        call_info, device, descriptorSet, descriptorUpdateTemplate, pData
    );

    WriteDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}

void VulkanSqliteConsumerExt::Process_vkUpdateDescriptorSetWithTemplateKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId descriptorSet,
    format::HandleId descriptorUpdateTemplate,
    DescriptorUpdateTemplateDecoder* pData
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkUpdateDescriptorSetWithTemplateKHR(
        call_info, device, descriptorSet, descriptorUpdateTemplate, pData
    );

    WriteDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}

void VulkanSqliteConsumerExt::PushDescriptorSet(
    format::HandleId commandBuffer,
    std::optional<VkPipelineBindPoint> bindPoint,
    std::optional<VkShaderStageFlags> stageFlags,
    format::HandleId pipelineLayout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
)
{
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find command buffer recording for command buffer with handle "
            "%" PRIi64,
            commandBuffer
        );
        return;
    }
    auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(pipelineLayout));
    if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find pipeline layout with handle %" PRIi64, pipelineLayout
        );
        return;
    }
    auto pipelineLayoutSetsIter = context.pipelineLayoutSetIndexToLayoutId.find(pipelineLayoutIter->second);
    if (pipelineLayoutSetsIter == context.pipelineLayoutSetIndexToLayoutId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find pipeline layout with handle %" PRIi64 " / ID %" PRIi64,
            pipelineLayout,
            pipelineLayoutIter->second
        );
        return;
    }

    auto descriptorSetLayoutIter = pipelineLayoutSetsIter->second.find(set);
    if (descriptorSetLayoutIter == pipelineLayoutSetsIter->second.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, pipeline layout with handle %" PRIi64 " / ID %" PRIi64
            " does not have a set with index %u",
            pipelineLayout,
            pipelineLayoutIter->second,
            set
        );
        return;
    }

    auto descriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(descriptorSetLayoutIter->second);
    if (descriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "While pushing descriptor sets, pipeline layout with handle %" PRIi64 " / ID %" PRIi64 " set index %" PRIi64
            " references descriptor set layout ID %" PRIi64 " which does not exist",
            pipelineLayout,
            pipelineLayoutIter->second,
            set,
            descriptorSetLayoutIter->second
        );
        return;
    }
    if (!(descriptorSetLayoutInfoIter->second.flags & VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT))
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Descriptor push with pipeline layout with handle %" PRIi64 " / ID %" PRIi64
            " and set with index %u refers to pipeline layout %" PRIi64 " which does not have the push descriptor flag",
            pipelineLayout,
            pipelineLayoutIter->second,
            set,
            descriptorSetLayoutIter->second
        );
    }

    auto deviceHandle = context.GetDeviceFromCommandBuffer(commandBuffer);

    auto [descriptorWritesValid, descriptorWrites, descriptorWritesCount] = GetMetaStructArray(pDescriptorWrites);
    if (descriptorWritesValid)
    {
        for (size_t i = 0; i < descriptorWritesCount; ++i)
        {
            WriteOrPushDescriptorSet(
                deviceHandle,
                descriptorWrites[i],
                set,
                commandBufferRecordingIter->second,
                descriptorSetLayoutIter->second,
                true
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSet(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    format::HandleId layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet(
        call_info, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites
    );

    PushDescriptorSet(
        commandBuffer, pipelineBindPoint, std::nullopt, layout, set, descriptorWriteCount, pDescriptorWrites
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSetKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    format::HandleId layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    StructPointerDecoder<Decoded_VkWriteDescriptorSet>* pDescriptorWrites
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetKHR(
        call_info, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites
    );

    PushDescriptorSet(
        commandBuffer, pipelineBindPoint, std::nullopt, layout, set, descriptorWriteCount, pDescriptorWrites
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSet2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet2(call_info, commandBuffer, pPushDescriptorSetInfo);

    auto [pushDescriptorSetInfoValid, pushDescriptorSetInfo] = GetMetaStructPointer(pPushDescriptorSetInfo);
    if (!pushDescriptorSetInfoValid)
    {
        LOG_CMD_WARNING("Failed to push descriptor sets, invalid pPushDescriptorSetInfo struct");
        return;
    }

    // layout can be null with dynamicPipelineLayout, in which case VkPipelineLayoutCreateInfo is chained
    LogUnsupportedPNext(pushDescriptorSetInfo->pNext);

    PushDescriptorSet(
        commandBuffer,
        std::nullopt,
        pushDescriptorSetInfo->decoded_value->stageFlags,
        pushDescriptorSetInfo->layout,
        pushDescriptorSetInfo->decoded_value->set,
        pushDescriptorSetInfo->decoded_value->descriptorWriteCount,
        pushDescriptorSetInfo->pDescriptorWrites
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSet2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetInfo>* pPushDescriptorSetInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet2KHR(call_info, commandBuffer, pPushDescriptorSetInfo);

    auto [pushDescriptorSetInfoValid, pushDescriptorSetInfo] = GetMetaStructPointer(pPushDescriptorSetInfo);
    if (!pushDescriptorSetInfoValid)
    {
        LOG_CMD_WARNING("Failed to push descriptor sets, invalid pPushDescriptorSetInfo struct");
        return;
    }

    // layout can be null with dynamicPipelineLayout, in which case VkPipelineLayoutCreateInfo is chained
    LogUnsupportedPNext(pushDescriptorSetInfo->pNext);

    PushDescriptorSet(
        commandBuffer,
        std::nullopt,
        pushDescriptorSetInfo->decoded_value->stageFlags,
        pushDescriptorSetInfo->layout,
        pushDescriptorSetInfo->decoded_value->set,
        pushDescriptorSetInfo->decoded_value->descriptorWriteCount,
        pushDescriptorSetInfo->pDescriptorWrites
    );
}

void VulkanSqliteConsumerExt::PushDescriptorSetWithTemplate(
    format::HandleId commandBuffer,
    format::HandleId descriptorUpdateTemplate,
    format::HandleId pipelineLayout,
    uint32_t set,
    const DescriptorUpdateTemplateDecoder* pData
)
{
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find command buffer recording for command buffer with handle "
            "%" PRIi64,
            commandBuffer
        );
        return;
    }
    auto pipelineLayoutIter = context.pipelineLayoutHandleToId.find(ToInt64(pipelineLayout));
    if (pipelineLayoutIter == context.pipelineLayoutHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find pipeline layout with handle %" PRIi64, pipelineLayout
        );
        return;
    }
    auto pipelineLayoutSetsIter = context.pipelineLayoutSetIndexToLayoutId.find(pipelineLayoutIter->second);
    if (pipelineLayoutSetsIter == context.pipelineLayoutSetIndexToLayoutId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, failed to find pipeline layout with handle %" PRIi64 " / ID %" PRIi64,
            pipelineLayout,
            pipelineLayoutIter->second
        );
        return;
    }

    auto descriptorSetLayoutIter = pipelineLayoutSetsIter->second.find(set);
    if (descriptorSetLayoutIter == pipelineLayoutSetsIter->second.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, pipeline layout with handle %" PRIi64 " / ID %" PRIi64
            " does not have a set with index %u",
            pipelineLayout,
            pipelineLayoutIter->second,
            set
        );
        return;
    }

    auto descriptorSetLayoutInfoIter = context.descriptorSetLayoutToInfo.find(descriptorSetLayoutIter->second);
    if (descriptorSetLayoutInfoIter == context.descriptorSetLayoutToInfo.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "While pushing descriptor sets, pipeline layout with handle %" PRIi64 " / ID %" PRIi64 " set index %" PRIi64
            " references descriptor set layout ID %" PRIi64 " which does not exist",
            pipelineLayout,
            pipelineLayoutIter->second,
            set,
            descriptorSetLayoutIter->second
        );
        return;
    }
    if (!(descriptorSetLayoutInfoIter->second.flags & VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT))
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Descriptor push with pipeline layout with handle %" PRIi64 " / ID %" PRIi64
            " and set with index %u refers to pipeline layout %" PRIi64 " which does not have the push descriptor flag",
            pipelineLayout,
            pipelineLayoutIter->second,
            set,
            descriptorSetLayoutIter->second
        );
    }

    auto deviceHandle = context.GetDeviceFromCommandBuffer(commandBuffer);

    WriteOrPushDescriptorSetWithTemplate(
        set,
        deviceHandle,
        commandBufferRecordingIter->second,
        descriptorSetLayoutIter->second,
        descriptorUpdateTemplate,
        pData,
        true
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSetWithTemplate(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId descriptorUpdateTemplate,
    format::HandleId layout,
    uint32_t set,
    DescriptorUpdateTemplateDecoder* pData
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplate(
        call_info, commandBuffer, descriptorUpdateTemplate, layout, set, pData
    );

    PushDescriptorSetWithTemplate(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSetWithTemplateKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId descriptorUpdateTemplate,
    format::HandleId layout,
    uint32_t set,
    DescriptorUpdateTemplateDecoder* pData
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplateKHR(
        call_info, commandBuffer, descriptorUpdateTemplate, layout, set, pData
    );

    PushDescriptorSetWithTemplate(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

void VulkanSqliteConsumerExt::PushDescriptorSetWithTemplate2(
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
)
{
    auto [pushDescriptorSetWithTemplateInfoValid, pushDescriptorSetWithTemplateInfo] =
        GetMetaStructPointer(pPushDescriptorSetWithTemplateInfo);
    if (!pushDescriptorSetWithTemplateInfo)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to push descriptor sets, invalid pPushDescriptorSetWithTemplateInfo struct"
        );
        return;
    }

    // layout can be null with dynamicPipelineLayout, in which case VkPipelineLayoutCreateInfo is chained
    LogUnsupportedPNext(pushDescriptorSetWithTemplateInfo->pNext);

    PushDescriptorSetWithTemplate(
        commandBuffer,
        pushDescriptorSetWithTemplateInfo->descriptorUpdateTemplate,
        pushDescriptorSetWithTemplateInfo->layout,
        pushDescriptorSetWithTemplateInfo->decoded_value->set,
        &pushDescriptorSetWithTemplateInfo->pData
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSetWithTemplate2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplate2(
        call_info, commandBuffer, pPushDescriptorSetWithTemplateInfo
    );

    PushDescriptorSetWithTemplate2(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdPushDescriptorSetWithTemplate2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo>* pPushDescriptorSetWithTemplateInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplate2KHR(
        call_info, commandBuffer, pPushDescriptorSetWithTemplateInfo
    );

    PushDescriptorSetWithTemplate2(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

void VulkanSqliteConsumerExt::Process_vkCreateBuffer(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkBufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBuffer>* pBuffer
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateBuffer(call_info, returnValue, device, pCreateInfo, pAllocator, pBuffer);

    auto [bufferValid, buffer] = GetHandle(pBuffer);
    if (!bufferValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create buffer, invalid pBuffer handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create buffer, invalid pCreateInfo struct");
        }
        return;
    }

    auto& ci = *createInfo->decoded_value;

    std::optional<int64_t> usage2 = std::nullopt;

    auto pnext = createInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkBufferUsageFlags2CreateInfoKHR>())
        {
            const auto* pBufferUsageFlags2CreateInfo =
                reinterpret_cast<const Decoded_VkBufferUsageFlags2CreateInfoKHR*>(header);
            usage2 = pBufferUsageFlags2CreateInfo->decoded_value->usage;
        }
        else
        {
            auto [warningIter, inserted] = context.pNextWarnings.insert(*header->sType);
            if (inserted)
            {
                LOG_CMD_WARNING(
                    "Unsupported pNext structure VkStructureType %d (%s)",
                    *header->sType,
                    gfxrecon::util::ToString(*header->sType, gfxrecon::util::kToString_Unformatted, 0, 0).c_str()
                );
            }
        }

        pnext = header->pNext;
    }

    statements.InsertBuffer(buffer, device, ci.flags, ci.size, ci.usage, usage2, ci.sharingMode, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyBuffer(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId buffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyBuffer(call_info, device, buffer, pAllocator);

    if (auto id = context.ExtractId(buffer, context.bufferHandleToId, "buffer", this->block_index_))
    {
        statements.DestroyObject(statements.destroyBufferUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateBufferView(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkBufferViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkBufferView>* pView
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateBufferView(call_info, returnValue, device, pCreateInfo, pAllocator, pView);

    auto [viewValid, view] = GetHandle(pView);
    if (!viewValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create buffer view, invalid pView handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create buffer view, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto buffer = createInfo->buffer;
    auto bufferId = context.GetBufferId(buffer);
    auto& ci = *createInfo->decoded_value;

    statements.InsertBufferView(
        view, device, bufferId, ci.format, ci.offset, static_cast<int64_t>(ci.range), this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyBufferView(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId bufferView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyBufferView(call_info, device, bufferView, pAllocator);

    if (auto id = context.ExtractId(bufferView, context.bufferViewHandleToId, "bufferView", this->block_index_))
    {
        statements.DestroyObject(statements.destroyBufferViewUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateImage(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkImageCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImage>* pImage
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateImage(call_info, returnValue, device, pCreateInfo, pAllocator, pImage);

    auto [imageValid, image] = GetHandle(pImage);
    if (!imageValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create image, invalid pImage handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create image, invalid pCreateInfo");
        }
        return;
    }

    std::optional<int64_t> externalFormat = std::nullopt;
    std::optional<int64_t> externalMemoryHandleTypes = std::nullopt;

    bool viewFormatsValid = false;
    const VkFormat* viewFormats = nullptr;
    uint64_t viewFormatsCount = 0;

    auto pnext = createInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkExternalFormatANDROID>())
        {
            const auto* pExternalFormat = reinterpret_cast<const Decoded_VkExternalFormatANDROID*>(header);
            if (pExternalFormat->decoded_value->externalFormat != 0)
            {
                externalFormat = static_cast<int64_t>(pExternalFormat->decoded_value->externalFormat);
            }
        }
        else if (*header->sType == gfxrecon::util::GetSType<VkImageFormatListCreateInfo>())
        {
            const auto* pImageFormatList = reinterpret_cast<const Decoded_VkImageFormatListCreateInfo*>(header);
            std::tie(viewFormatsValid, viewFormats, viewFormatsCount) =
                GetPointerArray(&pImageFormatList->pViewFormats);
        }
        else if (*header->sType == gfxrecon::util::GetSType<VkExternalMemoryImageCreateInfo>())
        {
            const auto* pExternalMemory = reinterpret_cast<const Decoded_VkExternalMemoryImageCreateInfo*>(header);
            externalMemoryHandleTypes =
                static_cast<int64_t>(pExternalMemory->decoded_value->handleTypes);
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    auto& ci = *createInfo->decoded_value;
    statements.InsertImage(
        image,
        device,
        ci.flags,
        ci.imageType,
        ci.format,
        ci.extent,
        ci.mipLevels,
        ci.arrayLayers,
        ci.samples,
        ci.tiling,
        ci.usage,
        ci.sharingMode,
        ci.initialLayout,
        externalFormat,
        externalMemoryHandleTypes,
        this->block_index_
    );

    if (viewFormatsValid)
    {
        if (auto imageId = context.GetImageId(image))
        {
            for (size_t i = 0; i < viewFormatsCount; ++i)
            {
                statements.InsertImageViewFormat(*imageId, static_cast<int64_t>(viewFormats[i]));
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyImage(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId image,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyImage(call_info, device, image, pAllocator);

    if (auto id = context.ExtractId(image, context.imageHandleToId, "image", this->block_index_))
    {
        statements.DestroyObject(statements.destroyImageUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateImageView(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkImageViewCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkImageView>* pView
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateImageView(call_info, returnValue, device, pCreateInfo, pAllocator, pView);

    auto [viewValid, view] = GetHandle(pView);
    if (!viewValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create image view, invalid pView handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create image view, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;
    auto imageId = context.GetImageId(createInfo->image);

    statements.InsertImageView(
        view, device, ci.flags, imageId, ci.viewType, ci.format, ci.components, ci.subresourceRange, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyImageView(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId imageView,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyImageView(call_info, device, imageView, pAllocator);

    if (auto id = context.ExtractId(imageView, context.imageViewHandleToId, "imageView", this->block_index_))
    {
        statements.DestroyObject(statements.destroyImageViewUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateSampler(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSamplerCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSampler>* pSampler
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSampler(call_info, returnValue, device, pCreateInfo, pAllocator, pSampler);

    auto [samplerValid, sampler] = GetHandle(pSampler);
    if (!samplerValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create sampler, invalid pSampler handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create sampler, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    // Allowed to be garbage when compareEnable is false:
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkSamplerCreateInfo.html#VUID-VkSamplerCreateInfo-compareEnable-01080
    auto compareOp = ci.compareEnable ? std::make_optional<int64_t>(ci.compareOp) : std::nullopt;
    // Allowed to be garbage if VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER not used:
    // https://registry.khronos.org/vulkan/specs/latest/man/html/VkSamplerCreateInfo.html#VUID-VkSamplerCreateInfo-addressModeU-01078
    auto borderColor = (ci.addressModeU == VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER ||
                        ci.addressModeV == VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER ||
                        ci.addressModeW == VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER)
        ? std::make_optional<int64_t>(ci.borderColor)
        : std::nullopt;

    statements.InsertSampler(
        sampler,
        device,
        ci.flags,
        ci.magFilter,
        ci.minFilter,
        ci.mipmapMode,
        ci.addressModeU,
        ci.addressModeV,
        ci.addressModeW,
        ci.mipLodBias,
        ci.anisotropyEnable,
        ci.maxAnisotropy,
        ci.compareEnable,
        compareOp,
        ci.minLod,
        ci.maxLod,
        borderColor,
        ci.unnormalizedCoordinates,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroySampler(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId sampler,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroySampler(call_info, device, sampler, pAllocator);

    if (auto id = context.ExtractId(sampler, context.samplerHandleToId, "sampler", this->block_index_))
    {
        statements.DestroyObject(statements.destroySamplerUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::GetDisplay(
    VkResult returnValue, format::HandleId physicalDevice, HandlePointerDecoder<VkDisplayKHR>* pDisplay
)
{
    auto [displayValid, display] = GetHandle(pDisplay);
    if (!display)
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create display, invalid pDisplay handle");
        }
        return;
    }

    auto physicalDeviceIter = context.physicalDeviceHandleToId.find(ToInt64(physicalDevice));
    if (physicalDeviceIter == context.physicalDeviceHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to create display, failed to find physical device with handle %" PRIu64, physicalDevice
            );
        }
        return;
    }

    auto displayHandle = ToInt64(display);
    statements.InsertDisplay(displayHandle, physicalDeviceIter->second, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkGetRandROutputDisplayEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId physicalDevice,
    uint64_t dpy,
    size_t rrOutput,
    HandlePointerDecoder<VkDisplayKHR>* pDisplay
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetRandROutputDisplayEXT(
        call_info, returnValue, physicalDevice, dpy, rrOutput, pDisplay
    );

    GetDisplay(returnValue, physicalDevice, pDisplay);
}

void VulkanSqliteConsumerExt::Process_vkGetDrmDisplayEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId physicalDevice,
    int32_t drmFd,
    uint32_t connectorId,
    HandlePointerDecoder<VkDisplayKHR>* display
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetDrmDisplayEXT(
        call_info, returnValue, physicalDevice, drmFd, connectorId, display
    );

    GetDisplay(returnValue, physicalDevice, display);
}

void VulkanSqliteConsumerExt::Process_vkGetWinrtDisplayNV(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId physicalDevice,
    uint32_t deviceRelativeId,
    HandlePointerDecoder<VkDisplayKHR>* pDisplay
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetWinrtDisplayNV(
        call_info, returnValue, physicalDevice, deviceRelativeId, pDisplay
    );

    GetDisplay(returnValue, physicalDevice, pDisplay);
}

void VulkanSqliteConsumerExt::Process_vkCreateDisplayModeKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId physicalDevice,
    format::HandleId display,
    StructPointerDecoder<Decoded_VkDisplayModeCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDisplayModeKHR>* pMode
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDisplayModeKHR(
        call_info, returnValue, physicalDevice, display, pCreateInfo, pAllocator, pMode
    );

    auto [modeValid, mode] = GetHandle(pMode);
    if (!modeValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create display mode, invalid pMode handle");
        }
        return;
    }

    auto physicalDeviceIter = context.physicalDeviceHandleToId.find(ToInt64(physicalDevice));
    if (physicalDeviceIter == context.physicalDeviceHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING(
                "Failed to create display mode, failed to find physical device with handle %" PRIu64, physicalDevice
            );
        }
        return;
    }

    auto displayIter = context.displayHandleToId.find(ToInt64(display));
    if (displayIter == context.displayHandleToId.end())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create display mode,failed to find display with handle %" PRIu64, display);
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create display mode, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertDisplayMode(
        mode,
        physicalDeviceIter->second,
        displayIter->second,
        ci.parameters.visibleRegion.width,
        ci.parameters.visibleRegion.height,
        ci.parameters.refreshRate,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateSwapchainKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSwapchainKHR>* pSwapchain
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSwapchainKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pSwapchain
    );

    auto [swapchainValid, swapchain] = GetHandle(pSwapchain);
    if (!swapchainValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create swapchain, invalid pSwapchain handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create swapchain, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    std::optional<int64_t> oldSwapchainId = std::nullopt;
    if (createInfo->oldSwapchain)
    {
        // This legitimately can be not found if the swapchain is recreated at runtime; see
        // https://github.com/android-graphics/sokatoa/issues/2316 and
        // https://github.com/LunarG/gfxreconstruct/issues/1900
        oldSwapchainId = context.GetSwapchainId(createInfo->oldSwapchain, true);
    }

    statements.InsertSwapchain(
        swapchain,
        device,
        ci.flags,
        ci.minImageCount,
        ci.imageFormat,
        ci.imageColorSpace,
        ci.imageExtent,
        ci.imageArrayLayers,
        ci.imageUsage,
        ci.imageSharingMode,
        ci.preTransform,
        ci.compositeAlpha,
        ci.presentMode,
        ci.clipped,
        oldSwapchainId,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateSharedSwapchainsKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    uint32_t swapchainCount,
    StructPointerDecoder<Decoded_VkSwapchainCreateInfoKHR>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkSwapchainKHR>* pSwapchains
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateSharedSwapchainsKHR(
        call_info, returnValue, device, swapchainCount, pCreateInfos, pAllocator, pSwapchains
    );

    auto [swapchainsValid, swapchains, chainsCount] = GetHandleArray(pSwapchains);
    if (!swapchainsValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create swapchain, invalid pSwapchains handle array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create swapchain, invalid pCreateInfos");
        }
        return;
    }

    for (size_t i = 0; i < createInfosCount; ++i)
    {
        if (chainsCount <= i)
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING("Failed to create swapchain, invalid pSwapchains count");
            }
            return;
        }

        auto& createInfo = createInfos[i];

        LogUnsupportedPNext(createInfo.pNext);

        auto flags = createInfo.decoded_value->flags;
        auto minImageCount = createInfo.decoded_value->minImageCount;
        auto imageFormat = createInfo.decoded_value->imageFormat;
        auto imageColorSpace = createInfo.decoded_value->imageColorSpace;
        auto& imageExtent = createInfo.decoded_value->imageExtent;
        auto imageLayers = createInfo.decoded_value->imageArrayLayers;
        auto imageUsage = createInfo.decoded_value->imageUsage;
        auto imageSharingMode = createInfo.decoded_value->imageSharingMode;
        auto preTransform = createInfo.decoded_value->preTransform;
        auto compositeAlpha = createInfo.decoded_value->compositeAlpha;
        auto presentMode = createInfo.decoded_value->presentMode;
        auto clipped = createInfo.decoded_value->clipped;
        std::optional<int64_t> oldSwapchainId = std::nullopt;
        if (createInfo.oldSwapchain)
        {
            // This legitimately can be not found if the swapchain is recreated at runtime; see
            // https://github.com/android-graphics/sokatoa/issues/2316 and
            // https://github.com/LunarG/gfxreconstruct/issues/1900
            oldSwapchainId = context.GetSwapchainId(createInfo.oldSwapchain, true);
        }

        auto swapchain = swapchains[i];

        statements.InsertSwapchain(
            swapchain,
            device,
            flags,
            minImageCount,
            imageFormat,
            imageColorSpace,
            imageExtent,
            imageLayers,
            imageUsage,
            imageSharingMode,
            preTransform,
            compositeAlpha,
            presentMode,
            clipped,
            oldSwapchainId,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroySwapchainKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId swapchain,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroySwapchainKHR(call_info, device, swapchain, pAllocator);

    if (auto id = context.ExtractId(swapchain, context.swapchainHandleToId, "swapchain", this->block_index_))
    {
        statements.DestroyObject(statements.destroySwapchainUpdateStatement, this->block_index_, *id);
        // destroying the swapchain destroys all swapchain images
        statements.DestroyObject(statements.destroySwapchainImagesUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkGetSwapchainImagesKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId swapchain,
    PointerDecoder<uint32_t>* pSwapchainImageCount,
    HandlePointerDecoder<VkImage>* pSwapchainImages
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetSwapchainImagesKHR(
        call_info, returnValue, device, swapchain, pSwapchainImageCount, pSwapchainImages
    );

    // we don't know how many swapchain images will be generated until the vkGetSwapchainImagesKHR call
    // so we insert them into the image table here and use the associated swapchain's create api event as
    // the create api event for the image
    auto swapchainId = context.GetSwapchainId(swapchain);
    if (!swapchainId)
    {
        return;
    }

    // pSwapchainImages can be null for the initial query for how many images are supported by the swapchain
    // ignore any where this is the case
    auto [swapchainImagesValid, swapchainImages, swapchainImageCount] = GetHandleArray(pSwapchainImages);
    if (swapchainImagesValid)
    {
        for (size_t i = 0; i < swapchainImageCount; ++i)
        {
            // check to see if we have already retrieved this image prior
            auto swapchainImage = swapchainImages[i];
            if (context.imageHandleToId.find(ToInt64(swapchainImage)) == context.imageHandleToId.end())
            {
                statements.InsertSwapchainImage(swapchainImage, device, *swapchainId);
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkAcquireNextImageKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId swapchain,
    uint64_t timeout,
    format::HandleId semaphore,
    format::HandleId fence,
    PointerDecoder<uint32_t>* pImageIndex
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkAcquireNextImageKHR(
        call_info, returnValue, device, swapchain, timeout, semaphore, fence, pImageIndex
    );

    auto swapchainId = context.GetSwapchainId(swapchain, true);

    std::optional<int64_t> fenceSyncScopeId = std::nullopt;
    if (fence != format::kNullHandleId)
    {
        auto fenceSyncScopeIter = context.fenceHandleToSyncScopeId.find(ToInt64(fence));
        if (fenceSyncScopeIter == context.fenceHandleToSyncScopeId.end())
        {
            if (returnValue == VK_SUCCESS)
            {
                LOG_CMD_WARNING(
                    "Failed to find fence instance for handle %" PRIu64 " setting foreign key to NULL", fence
                );
            }
        }
        else
        {
            fenceSyncScopeId = fenceSyncScopeIter->second;
        }
    }

    auto semaphoreId = context.GetSemaphoreId(semaphore);

    statements.InsertAcquireNextImage(
        swapchainId, fenceSyncScopeId, semaphoreId, context.currentFrame, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkAcquireNextImage2KHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkAcquireNextImageInfoKHR>* pAcquireInfo,
    PointerDecoder<uint32_t>* pImageIndex
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkAcquireNextImage2KHR(call_info, returnValue, device, pAcquireInfo, pImageIndex);

    std::optional<int64_t> swapchainId = std::nullopt;
    std::optional<int64_t> fenceSyncScopeId = std::nullopt;
    auto [acquireInfoValid, acquireInfo] = GetMetaStructPointer(pAcquireInfo);
    if (!acquireInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Invalid pAcquireInfo for acquire next image, setting foreign keys to NULL");
        }
    }
    else
    {
        LogUnsupportedPNext(acquireInfo->pNext);

        swapchainId = context.GetSwapchainId(acquireInfo->swapchain, true);

        if (acquireInfo->fence != format::kNullHandleId)
        {
            auto fenceSyncScopeIter = context.fenceHandleToSyncScopeId.find(ToInt64(acquireInfo->fence));
            if (fenceSyncScopeIter == context.fenceHandleToSyncScopeId.end())
            {
                if (returnValue == VK_SUCCESS)
                {
                    LOG_CMD_WARNING(
                        "Failed to find fence instance for handle %" PRIu64 " setting foreign key to NULL",
                        acquireInfo->fence
                    );
                }
            }
            else
            {
                fenceSyncScopeId = fenceSyncScopeIter->second;
            }
        }
    }

    statements.InsertAcquireNextImage(
        swapchainId, fenceSyncScopeId, std::nullopt, context.currentFrame, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateFramebuffer(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkFramebufferCreateInfo>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkFramebuffer>* pFramebuffer
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateFramebuffer(
        call_info, returnValue, device, pCreateInfo, pAllocator, pFramebuffer
    );

    auto [framebufferValid, framebuffer] = GetHandle(pFramebuffer);
    if (!framebufferValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create framebuffer, invalid pFramebuffer handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create framebuffer, invalid pCreateInfo");
        }
        return;
    }

    auto& ci = *createInfo->decoded_value;
    auto framebufferFlags = ci.flags;
    std::optional<int64_t> renderPassId = std::nullopt;
    if (createInfo->renderPass)
    {
        auto renderPassIter = context.renderPassHandleToId.find(ToInt64(createInfo->renderPass));
        if (renderPassIter == context.renderPassHandleToId.end())
        {
            LOG_CMD_WARNING(
                "Failed to find render pass for handle %" PRIu64 ", setting foreign key to NULL", createInfo->renderPass
            );
        }
        else
        {
            renderPassId = renderPassIter->second;
        }
    }

    auto framebufferId = statements.InsertFramebuffer(
        framebuffer, device, framebufferFlags, renderPassId, ci.width, ci.height, ci.layers, this->block_index_
    );

    if (ci.flags & VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT)
    {
        // framebuffer is in imageless mode, pAttachments are not provided
        // and pNext should contain additional attachment info

        // framebuffer only has 1 pNext type it supports so use utility function to query directly
        const auto* pAttachmentsCreateInfo =
            GetPNextMetaStruct<Decoded_VkFramebufferAttachmentsCreateInfo>(createInfo->pNext);

        if (pAttachmentsCreateInfo)
        {
            auto [attachmentsImageInfoValid, attachmentsImageInfos, attachmentsImageInfoCount] =
                GetMetaStructArray(pAttachmentsCreateInfo->pAttachmentImageInfos);

            if (attachmentsImageInfoValid)
            {
                for (size_t i = 0; i < attachmentsImageInfoCount; ++i)
                {
                    auto& info = *attachmentsImageInfos[i].decoded_value;

                    auto attachmentInfoId = statements.InsertFramebufferAttachmentInfo(
                        info.flags, info.width, info.height, info.layerCount, info.usage
                    );
                    statements.InsertFramebufferAttachmentWithInfo(framebufferId, i, attachmentInfoId);
                }
            }
        }
    }
    else
    {
        auto [attachmentsValid, attachments, attachmentsCount] = GetHandleArray(&createInfo->pAttachments);
        if (attachmentsValid)
        {
            for (size_t i = 0; i < attachmentsCount; ++i)
            {
                auto attachment = attachments[i];
                std::optional<int64_t> imageViewId = std::nullopt;
                auto imageViewIter = context.imageViewHandleToId.find(ToInt64(attachment));
                if (imageViewIter == context.imageViewHandleToId.end())
                {
                    LOG_CMD_WARNING(
                        "Failed to find image view for handle %" PRIu64 ", setting foreign key to NULL", attachment
                    );
                }
                else
                {
                    imageViewId = imageViewIter->second;
                }

                statements.InsertFramebufferAttachmentWithImageView(framebufferId, i, imageViewId);
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyFramebuffer(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId framebuffer,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyFramebuffer(call_info, device, framebuffer, pAllocator);

    if (auto id = context.ExtractId(framebuffer, context.framebufferHandleToId, "framebuffer", this->block_index_))
    {
        statements.DestroyObject(statements.destroyFramebufferUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetVertexInputEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputBindingDescription2EXT>* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    StructPointerDecoder<Decoded_VkVertexInputAttributeDescription2EXT>* pVertexAttributeDescriptions
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetVertexInputEXT(
        call_info,
        commandBuffer,
        vertexBindingDescriptionCount,
        pVertexBindingDescriptions,
        vertexAttributeDescriptionCount,
        pVertexAttributeDescriptions
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // we need to clear the existing state before insertion, the vulkan spec indicates that if this command does not
    // include the description for a binding, then it is set to undefined
    context.commandBufferRecordingVertexInputBindingDescriptions[commandBufferRecordingId].clear();
    auto [vertexBindingsValid, vertexBindings, vertexBindingsCount] = GetMetaStructArray(pVertexBindingDescriptions);
    if (vertexBindingsValid)
    {
        for (size_t i = 0; i < vertexBindingsCount; ++i)
        {
            auto vertexBinding = vertexBindings[i].decoded_value;
            statements.InsertStateVertexInputBindingDescription(
                this->block_index_,
                commandBufferRecordingId,
                vertexBinding->binding,
                vertexBinding->stride,
                vertexBinding->inputRate
            );
        }
    }

    context.commandBufferRecordingVertexInputAttributeDescriptions[commandBufferRecordingId].clear();
    auto [vertexAttrsValid, vertexAttrs, vertexAttrsCount] = GetMetaStructArray(pVertexAttributeDescriptions);
    if (vertexAttrsValid)
    {
        for (size_t i = 0; i < vertexAttrsCount; ++i)
        {
            auto vertexAttr = vertexAttrs[i].decoded_value;
            statements.InsertStateVertexInputAttributeDescription(
                this->block_index_,
                commandBufferRecordingId,
                vertexAttr->location,
                vertexAttr->binding,
                vertexAttr->format,
                vertexAttr->offset
            );
        }
    }

    // make sure we reset the state since we are modifying the state collection outside of the insert functions
    context.commandBufferRecordingWithDirtyState.insert(commandBufferRecordingId);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRenderingAttachmentLocations(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfo>* pLocationInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRenderingAttachmentLocations(call_info, commandBuffer, pLocationInfo);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    auto [locationInfoValid, locationInfo] = GetMetaStructPointer(pLocationInfo);
    if (!locationInfoValid)
    {
        LOG_CMD_WARNING("Failed to insert dynamic rendering attachment locations, invalid pLocationInfo");
        return;
    }

    LogUnsupportedPNext(locationInfo->pNext);

    auto colorAttachmentLocations = locationInfo->pColorAttachmentLocations.GetPointer();
    if (colorAttachmentLocations)
    {
        auto locationCount = locationInfo->pColorAttachmentLocations.GetLength();

        for (size_t i = 0; i < locationCount; ++i)
        {
            statements.InsertStateDynamicRenderingColorAttachmentLocation(
                this->block_index_, commandBufferRecordingId, static_cast<uint32_t>(i), colorAttachmentLocations[i]
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRenderingAttachmentLocationsKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingAttachmentLocationInfoKHR>* pLocationInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRenderingAttachmentLocationsKHR(call_info, commandBuffer, pLocationInfo);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    auto [locationInfoValid, locationInfo] = GetMetaStructPointer(pLocationInfo);
    if (!locationInfoValid)
    {
        LOG_CMD_WARNING("Failed to insert dynamic rendering attachment locations, invalid pLocationInfo");
        return;
    }

    LogUnsupportedPNext(locationInfo->pNext);

    auto colorAttachmentLocations = locationInfo->pColorAttachmentLocations.GetPointer();
    if (colorAttachmentLocations)
    {
        auto locationCount = locationInfo->pColorAttachmentLocations.GetLength();

        for (size_t i = 0; i < locationCount; ++i)
        {
            statements.InsertStateDynamicRenderingColorAttachmentLocation(
                this->block_index_, commandBufferRecordingId, static_cast<uint32_t>(i), colorAttachmentLocations[i]
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRenderingInputAttachmentIndices(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfo>* pInputAttachmentIndexInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRenderingInputAttachmentIndices(
        call_info, commandBuffer, pInputAttachmentIndexInfo
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    auto [inputAttachmentIndexInfoValid, inputAttachmentIndexInfo] = GetMetaStructPointer(pInputAttachmentIndexInfo);
    if (!inputAttachmentIndexInfoValid)
    {
        LOG_CMD_WARNING(
            "Failed to insert dynamic rendering input attachment indices, invalid pInputAttachmentIndexInfo"
        );
        return;
    }

    LogUnsupportedPNext(inputAttachmentIndexInfo->pNext);

    auto colorAttachmentIndices = inputAttachmentIndexInfo->pColorAttachmentInputIndices.GetPointer();
    if (colorAttachmentIndices)
    {
        auto indexCount = inputAttachmentIndexInfo->pColorAttachmentInputIndices.GetLength();

        for (size_t i = 0; i < indexCount; ++i)
        {
            statements.InsertStateDynamicRenderingInputColorAttachmentIndex(
                this->block_index_, commandBufferRecordingId, static_cast<uint32_t>(i), colorAttachmentIndices[i]
            );
        }
    }

    auto depthAttachmentIndex = inputAttachmentIndexInfo->pDepthInputAttachmentIndex.GetPointer();
    if (depthAttachmentIndex)
    {
        statements.InsertStateDynamicRenderingInputDepthAttachmentIndex(
            this->block_index_, commandBufferRecordingId, *depthAttachmentIndex
        );
    }

    auto stencilAttachmentIndex = inputAttachmentIndexInfo->pStencilInputAttachmentIndex.GetPointer();
    if (stencilAttachmentIndex)
    {
        statements.InsertStateDynamicRenderingInputStencilAttachmentIndex(
            this->block_index_, commandBufferRecordingId, *stencilAttachmentIndex
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkRenderingInputAttachmentIndexInfoKHR>* pInputAttachmentIndexInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
        call_info, commandBuffer, pInputAttachmentIndexInfo
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    auto [inputAttachmentIndexInfoValid, inputAttachmentIndexInfo] = GetMetaStructPointer(pInputAttachmentIndexInfo);
    if (!inputAttachmentIndexInfoValid)
    {
        LOG_CMD_WARNING(
            "Failed to insert dynamic rendering input attachment indices, invalid pInputAttachmentIndexInfo"
        );
        return;
    }

    LogUnsupportedPNext(inputAttachmentIndexInfo->pNext);

    auto colorAttachmentIndices = inputAttachmentIndexInfo->pColorAttachmentInputIndices.GetPointer();
    if (colorAttachmentIndices)
    {
        auto indexCount = inputAttachmentIndexInfo->pColorAttachmentInputIndices.GetLength();

        for (size_t i = 0; i < indexCount; ++i)
        {
            statements.InsertStateDynamicRenderingInputColorAttachmentIndex(
                this->block_index_, commandBufferRecordingId, static_cast<uint32_t>(i), colorAttachmentIndices[i]
            );
        }
    }

    auto depthAttachmentIndex = inputAttachmentIndexInfo->pDepthInputAttachmentIndex.GetPointer();
    if (depthAttachmentIndex)
    {
        statements.InsertStateDynamicRenderingInputDepthAttachmentIndex(
            this->block_index_, commandBufferRecordingId, *depthAttachmentIndex
        );
    }

    auto stencilAttachmentIndex = inputAttachmentIndexInfo->pStencilInputAttachmentIndex.GetPointer();
    if (stencilAttachmentIndex)
    {
        statements.InsertStateDynamicRenderingInputStencilAttachmentIndex(
            this->block_index_, commandBufferRecordingId, *stencilAttachmentIndex
        );
    }
}

#define InsertDynamicViewport(firstViewport)                                           \
    auto [viewportsValid, viewports, viewportsCount] = GetMetaStructArray(pViewports); \
    if (!viewportsValid)                                                               \
    {                                                                                  \
        LOG_CMD_WARNING("Failed to insert dynamic viewport, invalid pViewports");      \
        return;                                                                        \
    }                                                                                  \
                                                                                       \
    for (uint32_t i = 0; i < viewportsCount; ++i)                                      \
    {                                                                                  \
        auto viewportIndex = i + firstViewport;                                        \
        auto viewport = viewports[i].decoded_value;                                    \
        statements.InsertStateDynamicViewport(                                         \
            this->block_index_,                                                        \
            commandBufferRecordingId,                                                  \
            viewportIndex,                                                             \
            viewport->x,                                                               \
            viewport->y,                                                               \
            viewport->width,                                                           \
            viewport->height,                                                          \
            viewport->minDepth,                                                        \
            viewport->maxDepth                                                         \
        );                                                                             \
    }

void VulkanSqliteConsumerExt::Process_vkCmdSetViewport(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    StructPointerDecoder<Decoded_VkViewport>* pViewports
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetViewport(call_info, commandBuffer, firstViewport, viewportCount, pViewports);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    InsertDynamicViewport(firstViewport);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetViewportWithCount(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t viewportCount,
    StructPointerDecoder<Decoded_VkViewport>* pViewports
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetViewportWithCount(call_info, commandBuffer, viewportCount, pViewports);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // clear previous settings as WithCount explicitly sets the whole viewport state
    context.commandBufferRecordingDynamicViewports.erase(commandBufferRecordingId);

    InsertDynamicViewport(0);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetViewportWithCountEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t viewportCount,
    StructPointerDecoder<Decoded_VkViewport>* pViewports
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetViewportWithCountEXT(call_info, commandBuffer, viewportCount, pViewports);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // clear previous settings as WithCount explicitly sets the whole viewport state
    context.commandBufferRecordingDynamicViewports.erase(commandBufferRecordingId);

    InsertDynamicViewport(0);
}

#define InsertDynamicScissor(firstScissor)                                                               \
    auto [scissorsValid, scissors, scissorsCount] = GetMetaStructArray(pScissors);                       \
    if (!scissorsValid)                                                                                  \
    {                                                                                                    \
        LOG_CMD_WARNING("Failed to insert dynamic scissors, invalid pScissors");                         \
        return;                                                                                          \
    }                                                                                                    \
                                                                                                         \
    for (uint32_t i = 0; i < scissorsCount; ++i)                                                         \
    {                                                                                                    \
        auto scissorIndex = i + firstScissor;                                                            \
        auto scissor = scissors[i].decoded_value;                                                        \
        statements.InsertStateDynamicScissor(                                                            \
            this->block_index_, commandBufferRecordingId, scissorIndex, scissor->offset, scissor->extent \
        );                                                                                               \
    }

void VulkanSqliteConsumerExt::Process_vkCmdSetScissor(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>* pScissors
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetScissor(call_info, commandBuffer, firstScissor, scissorCount, pScissors);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    InsertDynamicScissor(firstScissor);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetScissorWithCount(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>* pScissors
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetScissorWithCount(call_info, commandBuffer, scissorCount, pScissors);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // clear previous settings as WithCount explicitly sets the whole scissor state
    context.commandBufferRecordingDynamicScissors.erase(commandBufferRecordingId);

    InsertDynamicScissor(0);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetScissorWithCountEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t scissorCount,
    StructPointerDecoder<Decoded_VkRect2D>* pScissors
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetScissorWithCountEXT(call_info, commandBuffer, scissorCount, pScissors);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // clear previous settings as WithCount explicitly sets the whole scissor state
    context.commandBufferRecordingDynamicScissors.erase(commandBufferRecordingId);

    InsertDynamicScissor(0);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetLineWidth(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, float lineWidth
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetLineWidth(call_info, commandBuffer, lineWidth);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicLineWidth(this->block_index_, commandBufferRecordingId, lineWidth);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBias(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBias(
        call_info, commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdSetDepthBias.html#_description
    // https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDepthBiasInfoEXT.html#_description
    const VkDepthBiasRepresentationEXT depthBiasRepresentation =
        VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT;
    const VkBool32 depthBiasExact = VK_FALSE;

    statements.InsertStateDynamicDepthBias(
        this->block_index_,
        commandBufferRecordingId,
        depthBiasConstantFactor,
        depthBiasClamp,
        depthBiasSlopeFactor,
        depthBiasRepresentation,
        depthBiasExact
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBias2EXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkDepthBiasInfoEXT>* pDepthBiasInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBias2EXT(call_info, commandBuffer, pDepthBiasInfo);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    // https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDepthBiasInfoEXT.html#_description
    VkDepthBiasRepresentationEXT depthBiasRepresentation =
        VK_DEPTH_BIAS_REPRESENTATION_LEAST_REPRESENTABLE_VALUE_FORMAT_EXT;
    VkBool32 depthBiasExact = VK_FALSE;

    auto [depthBiasInfoValid, depthBiasInfo] = GetMetaStructPointer(pDepthBiasInfo);
    if (depthBiasInfoValid && depthBiasInfo->pNext)
    {
        auto pnext = depthBiasInfo->pNext;
        while (pnext != nullptr)
        {
            auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
            if (*header->sType == gfxrecon::util::GetSType<VkDepthBiasRepresentationInfoEXT>())
            {
                const auto* pRepresentationInfo =
                    reinterpret_cast<const Decoded_VkDepthBiasRepresentationInfoEXT*>(header);
                depthBiasRepresentation = pRepresentationInfo->decoded_value->depthBiasRepresentation;
                depthBiasExact = pRepresentationInfo->decoded_value->depthBiasExact;
            }
            else
            {
                LogUnsupportedPNext(*header->sType);
            }

            pnext = header->pNext;
        }

        statements.InsertStateDynamicDepthBias(
            this->block_index_,
            commandBufferRecordingId,
            pDepthBiasInfo->GetPointer()->depthBiasConstantFactor,
            pDepthBiasInfo->GetPointer()->depthBiasClamp,
            pDepthBiasInfo->GetPointer()->depthBiasSlopeFactor,
            depthBiasRepresentation,
            depthBiasExact
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetBlendConstants(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, PointerDecoder<float>* blendConstants
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetBlendConstants(call_info, commandBuffer, blendConstants);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    GFXRECON_ASSERT(blendConstants->GetLength() == 4);
    statements.InsertStateDynamicBlendConstants(
        this->block_index_, commandBufferRecordingId, std::span<const float, 4>(blendConstants->GetPointer(), 4)
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBounds(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, float minDepthBounds, float maxDepthBounds
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBounds(call_info, commandBuffer, minDepthBounds, maxDepthBounds);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthBounds(
        this->block_index_, commandBufferRecordingId, minDepthBounds, maxDepthBounds
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilCompareMask(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilCompareMask(call_info, commandBuffer, faceMask, compareMask);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    if (faceMask & VK_STENCIL_FACE_FRONT_BIT)
    {
        statements.InsertStateDynamicStencilCompareMaskFront(this->block_index_, commandBufferRecordingId, compareMask);
    }
    if (faceMask & VK_STENCIL_FACE_BACK_BIT)
    {
        statements.InsertStateDynamicStencilCompareMaskBack(this->block_index_, commandBufferRecordingId, compareMask);
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilWriteMask(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilWriteMask(call_info, commandBuffer, faceMask, writeMask);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    if (faceMask & VK_STENCIL_FACE_FRONT_BIT)
    {
        statements.InsertStateDynamicStencilWriteMaskFront(this->block_index_, commandBufferRecordingId, writeMask);
    }
    if (faceMask & VK_STENCIL_FACE_BACK_BIT)
    {
        statements.InsertStateDynamicStencilWriteMaskBack(this->block_index_, commandBufferRecordingId, writeMask);
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilReference(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilReference(call_info, commandBuffer, faceMask, reference);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    if (faceMask & VK_STENCIL_FACE_FRONT_BIT)
    {
        statements.InsertStateDynamicStencilReferenceFront(this->block_index_, commandBufferRecordingId, reference);
    }
    if (faceMask & VK_STENCIL_FACE_BACK_BIT)
    {
        statements.InsertStateDynamicStencilReferenceBack(this->block_index_, commandBufferRecordingId, reference);
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetCullMode(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCullModeFlags cullMode
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetCullMode(call_info, commandBuffer, cullMode);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicCullMode(this->block_index_, commandBufferRecordingId, cullMode);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetCullModeEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCullModeFlags cullMode
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetCullModeEXT(call_info, commandBuffer, cullMode);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicCullMode(this->block_index_, commandBufferRecordingId, cullMode);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetFrontFace(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkFrontFace frontFace
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetFrontFace(call_info, commandBuffer, frontFace);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicFrontFace(this->block_index_, commandBufferRecordingId, frontFace);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetFrontFaceEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkFrontFace frontFace
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetFrontFaceEXT(call_info, commandBuffer, frontFace);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicFrontFace(this->block_index_, commandBufferRecordingId, frontFace);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetPrimitiveTopology(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkPrimitiveTopology primitiveTopology
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetPrimitiveTopology(call_info, commandBuffer, primitiveTopology);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicPrimitiveTopology(this->block_index_, commandBufferRecordingId, primitiveTopology);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetPrimitiveTopologyEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkPrimitiveTopology primitiveTopology
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetPrimitiveTopologyEXT(call_info, commandBuffer, primitiveTopology);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicPrimitiveTopology(this->block_index_, commandBufferRecordingId, primitiveTopology);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthTestEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthTestEnable(call_info, commandBuffer, depthTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthTestEnable(this->block_index_, commandBufferRecordingId, depthTestEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthTestEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthTestEnableEXT(call_info, commandBuffer, depthTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthTestEnable(this->block_index_, commandBufferRecordingId, depthTestEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthWriteEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthWriteEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthWriteEnable(call_info, commandBuffer, depthWriteEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthWriteEnable(this->block_index_, commandBufferRecordingId, depthWriteEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthWriteEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthWriteEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthWriteEnableEXT(call_info, commandBuffer, depthWriteEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthWriteEnable(this->block_index_, commandBufferRecordingId, depthWriteEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthCompareOp(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCompareOp depthCompareOp
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthCompareOp(call_info, commandBuffer, depthCompareOp);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthCompareOp(this->block_index_, commandBufferRecordingId, depthCompareOp);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthCompareOpEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkCompareOp depthCompareOp
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthCompareOpEXT(call_info, commandBuffer, depthCompareOp);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthCompareOp(this->block_index_, commandBufferRecordingId, depthCompareOp);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBoundsTestEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBoundsTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBoundsTestEnable(call_info, commandBuffer, depthBoundsTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthBoundsTestEnable(
        this->block_index_, commandBufferRecordingId, depthBoundsTestEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBoundsTestEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBoundsTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBoundsTestEnableEXT(call_info, commandBuffer, depthBoundsTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthBoundsTestEnable(
        this->block_index_, commandBufferRecordingId, depthBoundsTestEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilTestEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 stencilTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilTestEnable(call_info, commandBuffer, stencilTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicStencilTestEnable(this->block_index_, commandBufferRecordingId, stencilTestEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilTestEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 stencilTestEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilTestEnableEXT(call_info, commandBuffer, stencilTestEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicStencilTestEnable(this->block_index_, commandBufferRecordingId, stencilTestEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilOp(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilOp(
        call_info, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    if (faceMask & VK_STENCIL_FACE_FRONT_BIT)
    {
        statements.InsertStateDynamicStencilOpsFront(
            this->block_index_, commandBufferRecordingId, failOp, passOp, depthFailOp, compareOp
        );
    }
    if (faceMask & VK_STENCIL_FACE_BACK_BIT)
    {
        statements.InsertStateDynamicStencilOpsBack(
            this->block_index_, commandBufferRecordingId, failOp, passOp, depthFailOp, compareOp
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetStencilOpEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetStencilOpEXT(
        call_info, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    if (faceMask & VK_STENCIL_FACE_FRONT_BIT)
    {
        statements.InsertStateDynamicStencilOpsFront(
            this->block_index_, commandBufferRecordingId, failOp, passOp, depthFailOp, compareOp
        );
    }
    if (faceMask & VK_STENCIL_FACE_BACK_BIT)
    {
        statements.InsertStateDynamicStencilOpsBack(
            this->block_index_, commandBufferRecordingId, failOp, passOp, depthFailOp, compareOp
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRasterizerDiscardEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 rasterizerDiscardEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRasterizerDiscardEnable(call_info, commandBuffer, rasterizerDiscardEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicRasterizerDiscardEnable(
        this->block_index_, commandBufferRecordingId, rasterizerDiscardEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetRasterizerDiscardEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 rasterizerDiscardEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetRasterizerDiscardEnableEXT(call_info, commandBuffer, rasterizerDiscardEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicRasterizerDiscardEnable(
        this->block_index_, commandBufferRecordingId, rasterizerDiscardEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBiasEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBiasEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBiasEnable(call_info, commandBuffer, depthBiasEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthBiasEnable(this->block_index_, commandBufferRecordingId, depthBiasEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetDepthBiasEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 depthBiasEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetDepthBiasEnableEXT(call_info, commandBuffer, depthBiasEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicDepthBiasEnable(this->block_index_, commandBufferRecordingId, depthBiasEnable);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetPrimitiveRestartEnable(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 primitiveRestartEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetPrimitiveRestartEnable(call_info, commandBuffer, primitiveRestartEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicPrimitiveRestartEnable(
        this->block_index_, commandBufferRecordingId, primitiveRestartEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetPrimitiveRestartEnableEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 primitiveRestartEnable
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetPrimitiveRestartEnableEXT(call_info, commandBuffer, primitiveRestartEnable);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicPrimitiveRestartEnable(
        this->block_index_, commandBufferRecordingId, primitiveRestartEnable
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdSetPatchControlPointsEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkBool32 patchControlPoints
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetPatchControlPointsEXT(call_info, commandBuffer, patchControlPoints);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicPatchControlPoints(this->block_index_, commandBufferRecordingId, patchControlPoints);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetLogicOpEXT(
    const ApiCallInfo& call_info, format::HandleId commandBuffer, VkLogicOp logicOp
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetLogicOpEXT(call_info, commandBuffer, logicOp);

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    statements.InsertStateDynamicLogicOp(this->block_index_, commandBufferRecordingId, logicOp);
}

void VulkanSqliteConsumerExt::Process_vkCmdSetColorWriteEnableEXT(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t attachmentCount,
    PointerDecoder<VkBool32>* pColorWriteEnables
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdSetColorWriteEnableEXT(
        call_info, commandBuffer, attachmentCount, pColorWriteEnables
    );

    CREATE_COMMAND_BUFFER_INSTANCE_ID();

    auto [enablesValid, enables, enablesCount] = GetPointerArray(pColorWriteEnables);
    if (!enablesValid)
    {
        LOG_CMD_WARNING("Failed to insert dynamic color write enables, invalid pColorWriteEnables");
        return;
    }

    for (uint32_t i = 0; i < enablesCount; ++i)
    {
        const VkBool32 enable = enables[i];
        statements.InsertStateDynamicColorWriteEnable(this->block_index_, commandBufferRecordingId, i, enable);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureKHR>* pAccelerationStructure
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateAccelerationStructureKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pAccelerationStructure
    );

    auto [accelStrucValid, accelStruct] = GetHandle(pAccelerationStructure);
    if (!accelStrucValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create acceleration structure, invalid pAccelerationStructure handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create acceleration structure, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertAccelerationStructure(
        accelStruct,
        device,
        ci.createFlags,
        ci.type,
        createInfo->buffer,
        ci.offset,
        ci.size,
        ci.deviceAddress,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkCreateAccelerationStructureNV(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkAccelerationStructureCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkAccelerationStructureNV>* pAccelerationStructure
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateAccelerationStructureNV(
        call_info, returnValue, device, pCreateInfo, pAllocator, pAccelerationStructure
    );

    auto [accelStrucValid, accelStruct] = GetHandle(pAccelerationStructure);
    if (!accelStrucValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create acceleration structure, invalid pAccelerationStructure handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create acceleration structure, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertAccelerationStructureNv(
        accelStruct, device, ci.info.flags, ci.info.type, ci.compactedSize, ci.info.instanceCount, this->block_index_
    );

    // TODO parse geometries
}

void VulkanSqliteConsumerExt::Process_vkDestroyAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyAccelerationStructureKHR(
        call_info, device, accelerationStructure, pAllocator
    );

    if (auto id = context.ExtractId(
            accelerationStructure, context.accelerationStructureHandleToId, "accelerationStructure", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyAccelerationStructureUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyAccelerationStructureNV(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId accelerationStructure,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyAccelerationStructureNV(
        call_info, device, accelerationStructure, pAllocator
    );

    if (auto id = context.ExtractId(
            accelerationStructure,
            context.accelerationStructureNvHandleToId,
            "accelerationStructure",
            this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyAccelerationStructureNvUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::ProcessVkAccelerationStructureBuildGeometryInfo(
    const int64_t buildId,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
)
{
    auto [infosValid, infos, infosCount] = GetMetaStructArray(pInfos);
    if (infosValid)
    {
        for (size_t i = 0; i < infosCount; ++i)
        {
            auto& info = infos[i];
            auto type = info.decoded_value->type;
            auto flags = info.decoded_value->flags;
            auto mode = info.decoded_value->mode;
            auto srcAccelStruct = info.srcAccelerationStructure;
            auto dstAccelStruct = info.dstAccelerationStructure;
            auto scratchData = info.decoded_value->scratchData;
            auto infoId = statements.InsertAccelerationStructureBuildGeometryInfo(
                buildId, i, type, flags, mode, srcAccelStruct, dstAccelStruct, scratchData
            );

            auto [geometriesValid, geometries, geometriesCount] = GetMetaStructArray(info.pGeometries);
            if (geometriesValid)
            {
                for (size_t j = 0; j < geometriesCount; ++j)
                {
                    auto& geometry = geometries[j];
                    std::optional<int64_t> triangleDataId = std::nullopt;
                    std::optional<int64_t> aabbDataId = std::nullopt;
                    std::optional<int64_t> instanceDataId = std::nullopt;

                    auto geometryType = geometry.decoded_value->geometryType;
                    switch (geometryType)
                    {
                        case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
                        {
                            triangleDataId = statements.InsertAccelerationStructureBuildTriangleData(
                                geometry.decoded_value->geometry.triangles
                            );
                            break;
                        }
                        case VK_GEOMETRY_TYPE_AABBS_KHR:
                        {
                            aabbDataId = statements.InsertAccelerationStructureBuildAABBData(
                                geometry.decoded_value->geometry.aabbs
                            );
                            break;
                        }
                        case VK_GEOMETRY_TYPE_INSTANCES_KHR:
                        {
                            instanceDataId = statements.InsertAccelerationStructureBuildInstanceData(
                                geometry.decoded_value->geometry.instances
                            );
                            break;
                        }
                        default:
                            // do nothing
                            break;
                    }

                    auto geometryFlags = geometry.decoded_value->flags;
                    statements.InsertAccelerationStructureBuildGeometry(
                        infoId, j, geometryType, geometryFlags, triangleDataId, aabbDataId, instanceDataId
                    );
                }
            }
            auto [geometriesPValid, geometriesP, geometriesPCount] = GetMetaStructArray2D(info.ppGeometries, i);
            if (geometriesPValid)
            {
                for (size_t j = 0; j < geometriesPCount; ++j)
                {
                    auto& geometry = geometriesP[j];
                    std::optional<int64_t> triangleDataId = std::nullopt;
                    std::optional<int64_t> aabbDataId = std::nullopt;
                    std::optional<int64_t> instanceDataId = std::nullopt;
                    // insert the triangle etc...

                    auto geometryType = geometry.decoded_value->geometryType;
                    switch (geometryType)
                    {
                        case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
                        {
                            triangleDataId = statements.InsertAccelerationStructureBuildTriangleData(
                                geometry.decoded_value->geometry.triangles
                            );
                            break;
                        }
                        case VK_GEOMETRY_TYPE_AABBS_KHR:
                        {
                            aabbDataId = statements.InsertAccelerationStructureBuildAABBData(
                                geometry.decoded_value->geometry.aabbs
                            );
                            break;
                        }
                        case VK_GEOMETRY_TYPE_INSTANCES_KHR:
                        {
                            instanceDataId = statements.InsertAccelerationStructureBuildInstanceData(
                                geometry.decoded_value->geometry.instances
                            );
                            break;
                        }
                        default:
                            // do nothing
                            break;
                    }

                    auto geometryFlags = geometry.decoded_value->flags;
                    statements.InsertAccelerationStructureBuildGeometry(
                        infoId, j, geometryType, geometryFlags, triangleDataId, aabbDataId, instanceDataId
                    );
                }
            }
            ProcessVkAccelerationStructureBuildRangeInfo(infoId, ppBuildRangeInfos, i);
        }
    }
}

void VulkanSqliteConsumerExt::ProcessVkAccelerationStructureBuildRangeInfo(
    const int64_t infoId,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos,
    size_t infoIndex
)
{
    auto [infoEntriesValid, infoEntries, infoEntriesCount] = GetMetaStructArray2D(ppRangeInfos, infoIndex);
    if (infoEntriesValid)
    {
        for (size_t i = 0; i < infoEntriesCount; ++i)
        {
            auto& infoEntry = infoEntries[i];
            auto primCount = infoEntry.decoded_value->primitiveCount;
            auto primOffset = infoEntry.decoded_value->primitiveOffset;
            auto firstVert = infoEntry.decoded_value->firstVertex;
            auto transOffset = infoEntry.decoded_value->transformOffset;
            statements.InsertAccelerationStructureBuildRangeInfo(
                infoId, i, primCount, primOffset, firstVert, transOffset
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkBuildAccelerationStructuresKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    uint32_t infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkBuildAccelerationStructuresKHR(
        call_info, returnValue, device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos
    );

    auto buildId =
        statements.InsertAccelerationStructureBuild(device, deferredOperation, std::nullopt, this->block_index_);

    ProcessVkAccelerationStructureBuildGeometryInfo(buildId, pInfos, ppBuildRangeInfos);
}

void VulkanSqliteConsumerExt::Process_vkCmdBuildAccelerationStructuresKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppBuildRangeInfos
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBuildAccelerationStructuresKHR(
        call_info, commandBuffer, infoCount, pInfos, ppBuildRangeInfos
    );

    auto buildId =
        statements.InsertAccelerationStructureBuild(std::nullopt, std::nullopt, commandBuffer, this->block_index_);

    ProcessVkAccelerationStructureBuildGeometryInfo(buildId, pInfos, ppBuildRangeInfos);
}

void VulkanSqliteConsumerExt::ProcessVulkanBuildAccelerationStructuresCommand(
    format::HandleId device,
    uint32_t infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*>* ppRangeInfos
)
{
    // The base class has no implementation for this meta command — insert the apiEventId ourselves
    const auto functionId = statements.InsertFunctionName("BuildAccelerationStructures");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    auto buildId = statements.InsertAccelerationStructureBuild(device, std::nullopt, std::nullopt, this->block_index_);

    ProcessVkAccelerationStructureBuildGeometryInfo(buildId, pInfos, ppRangeInfos);
}

void VulkanSqliteConsumerExt::Process_vkCopyAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCopyAccelerationStructureKHR(
        call_info, returnValue, device, deferredOperation, pInfo
    );

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            device,
            deferredOperation,
            std::nullopt,
            info->src,
            info->dst,
            std::nullopt,
            std::nullopt,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCopyAccelerationStructureToMemoryKHR(
        call_info, returnValue, device, deferredOperation, pInfo
    );

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            device,
            deferredOperation,
            std::nullopt,
            info->src,
            std::nullopt,
            std::nullopt,
            info->decoded_value->dst,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCopyMemoryToAccelerationStructureKHR(
        call_info, returnValue, device, deferredOperation, pInfo
    );

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            device,
            deferredOperation,
            std::nullopt,
            std::nullopt,
            info->dst,
            info->decoded_value->src,
            std::nullopt,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdCopyAccelerationStructureKHR(call_info, commandBuffer, pInfo);

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            std::nullopt,
            std::nullopt,
            commandBuffer,
            info->src,
            info->dst,
            std::nullopt,
            std::nullopt,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureToMemoryInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdCopyAccelerationStructureToMemoryKHR(call_info, commandBuffer, pInfo);

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            std::nullopt,
            std::nullopt,
            commandBuffer,
            info->src,
            std::nullopt,
            std::nullopt,
            info->decoded_value->dst,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyMemoryToAccelerationStructureInfoKHR>* pInfo
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdCopyMemoryToAccelerationStructureKHR(call_info, commandBuffer, pInfo);

    auto [infoValid, info] = GetMetaStructPointer(pInfo);
    if (infoValid)
    {
        statements.InsertAccelerationStructureCopy(
            std::nullopt,
            std::nullopt,
            commandBuffer,
            std::nullopt,
            info->dst,
            info->decoded_value->src,
            std::nullopt,
            info->decoded_value->mode,
            this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::ProcessVulkanCopyAccelerationStructuresCommand(
    format::HandleId device, StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR>* copyInfos
)
{
    // The base class has no implementation for this meta command — insert the apiEventId ourselves
    const auto functionId = statements.InsertFunctionName("CopyAccelerationStructures");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    auto [infosValid, infos, infosCount] = GetMetaStructArray(copyInfos);
    if (infosValid)
    {
        for (size_t i = 0; i < infosCount; ++i)
        {
            auto& info = infos[i];
            statements.InsertAccelerationStructureCopy(
                device,
                std::nullopt,
                std::nullopt,
                info.src,
                info.dst,
                std::nullopt,
                std::nullopt,
                info.decoded_value->mode,
                this->block_index_
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDeferredOperationKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDeferredOperationKHR>* pDeferredOperation
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreateDeferredOperationKHR(
        call_info, returnValue, device, pAllocator, pDeferredOperation
    );

    auto [operationValid, operation] = GetHandle(pDeferredOperation);
    if (!operationValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create deferred operation, invalid pDeferredOperation handle");
        }
        return;
    }

    statements.InsertDeferredOperation(operation, device, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyDeferredOperationKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId operation,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyDeferredOperationKHR(call_info, device, operation, pAllocator);

    if (auto id = context.ExtractId(operation, context.deferredOperationHandleToId, "operation", this->block_index_))
    {
        statements.DestroyObject(statements.destroyDeferredOperationUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreatePipelineBinariesKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkPipelineBinaryCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    StructPointerDecoder<Decoded_VkPipelineBinaryHandlesInfoKHR>* pBinaries
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCreatePipelineBinariesKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pBinaries
    );

    auto [binariesValid, binaries] = GetMetaStructPointer(pBinaries);
    if (!binariesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline binaries, invalid pBinaries structure");
        }
        return;
    }

    LogUnsupportedPNext(binaries->pNext);

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create pipeline binaries, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    // keys and data structure can be NULL
    uint64_t keysCount = 0;
    uint64_t datasCount = 0;
    const gfxrecon::decode::Decoded_VkPipelineBinaryKeyKHR* keysArray = nullptr;
    const gfxrecon::decode::Decoded_VkPipelineBinaryDataKHR* datasArray = nullptr;
    auto [keysAndDataValid, keysAndData] = GetMetaStructPointer(createInfo->pKeysAndDataInfo);
    if (keysAndDataValid)
    {
        auto [keysValid, keys, keyCount] = GetMetaStructArray(keysAndData->pPipelineBinaryKeys);
        if (keysValid)
        {
            keysArray = keys;
            keysCount = keyCount;
        }
        auto [datasValid, datas, dataCount] = GetMetaStructArray(keysAndData->pPipelineBinaryData);
        if (datasValid)
        {
            datasArray = datas;
            datasCount = dataCount;
        }
    }

    // pipeline can be NULL
    std::optional<int64_t> sourcePipelineId = std::nullopt;
    auto pipelineIter = context.pipelineHandleToId.find(ToInt64(device));
    if (pipelineIter != context.pipelineHandleToId.end())
    {
        sourcePipelineId = pipelineIter->second;
    }

    auto [pipelineBinariesValid, pipelineBinaries, pipelineBinaryCount] = GetHandleArray(&binaries->pPipelineBinaries);

    for (size_t i = 0; i < pipelineBinaryCount; ++i)
    {
        auto pipelineBinary = pipelineBinaries[i];
        uint32_t keySize = 0;
        size_t dataSize = 0;
        if (keysAndDataValid)
        {
            if (keysCount <= i)
            {
                keySize = keysArray[i].decoded_value->keySize;
                // TODO handle key (byte array)
            }
            if (datasCount <= i)
            {
                dataSize = datasArray[i].decoded_value->dataSize;
                // TODO handle data (void* to binary data)
            }
        }

        statements.InsertPipelineBinary(
            pipelineBinary, device, keySize, dataSize, sourcePipelineId, this->block_index_
        );
    }
}

void VulkanSqliteConsumerExt::Process_vkDestroyPipelineBinaryKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId pipelineBinary,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkDestroyPipelineBinaryKHR(call_info, device, pipelineBinary, pAllocator);

    if (auto id =
            context.ExtractId(pipelineBinary, context.pipelineBinaryHandleToId, "pipelineBinary", this->block_index_))
    {
        statements.DestroyObject(statements.destroyPipelineBinaryUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateVideoSessionKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkVideoSessionCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionKHR>* pVideoSession
)
{
    VulkanSqliteConsumer::Process_vkCreateVideoSessionKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pVideoSession
    );

    auto [videoSessionValid, videoSession] = GetHandle(pVideoSession);
    if (!videoSessionValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session, invalid pVideoSession handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    auto [profileValid, profile] = GetMetaStructPointer(createInfo->pVideoProfile);
    if (!profileValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session, invalid pVideoProfile");
        }
        return;
    }

    auto [stdHeaderValid, stdHeader] = GetMetaStructPointer(createInfo->pStdHeaderVersion);
    if (!stdHeaderValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session, invalid pStdHeaderVersion");
        }
        return;
    }

    auto& profileCi = *profile->decoded_value;
    auto& stdHeaderCi = *stdHeader->decoded_value;

    statements.InsertVideoSession(
        videoSession,
        device,
        ci.queueFamilyIndex,
        ci.flags,
        profileCi.videoCodecOperation,
        profileCi.chromaSubsampling,
        profileCi.lumaBitDepth,
        profileCi.chromaBitDepth,
        ci.pictureFormat,
        createInfo->maxCodedExtent->decoded_value->width,
        createInfo->maxCodedExtent->decoded_value->height,
        ci.referencePictureFormat,
        ci.maxDpbSlots,
        ci.maxActiveReferencePictures,
        stdHeaderCi.extensionName,
        stdHeaderCi.specVersion,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyVideoSessionKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId videoSession,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyVideoSessionKHR(call_info, device, videoSession, pAllocator);

    if (auto id = context.ExtractId(videoSession, context.videoSessionHandleToId, "videoSession", this->block_index_))
    {
        statements.DestroyObject(statements.destroyVideoSessionUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateVideoSessionParametersKHR(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkVideoSessionParametersCreateInfoKHR>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkVideoSessionParametersKHR>* pVideoSessionParameters
)
{
    VulkanSqliteConsumer::Process_vkCreateVideoSessionParametersKHR(
        call_info, returnValue, device, pCreateInfo, pAllocator, pVideoSessionParameters
    );

    auto [paramsValid, params] = GetHandle(pVideoSessionParameters);
    if (!paramsValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session parameters, invalid pVideoSessionParameters handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create video session parameters, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    auto videoSessionId = context.GetVideoSessionId(createInfo->videoSession);
    if (!videoSessionId.has_value())
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING(
                "Failed to create video session parameters, failed to find video session with handle %" PRIu64,
                createInfo->videoSession
            );
        }
        return;
    }

    auto templateId = context.GetVideoSessionParametersId(createInfo->videoSessionParametersTemplate, true);

    statements.InsertVideoSessionParameters(params, device, ci.flags, templateId, *videoSessionId, this->block_index_);
}

void VulkanSqliteConsumerExt::Process_vkDestroyVideoSessionParametersKHR(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId videoSessionParameters,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyVideoSessionParametersKHR(
        call_info, device, videoSessionParameters, pAllocator
    );

    if (auto id = context.ExtractId(
            videoSessionParameters,
            context.videoSessionParametersHandleToId,
            "videoSessionParameters",
            this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyVideoSessionParametersUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateIndirectCommandsLayoutEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkIndirectCommandsLayoutCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkIndirectCommandsLayoutEXT>* pIndirectCommandsLayout
)
{
    VulkanSqliteConsumer::Process_vkCreateIndirectCommandsLayoutEXT(
        call_info, returnValue, device, pCreateInfo, pAllocator, pIndirectCommandsLayout
    );

    auto [layoutValid, layout] = GetHandle(pIndirectCommandsLayout);
    if (!layoutValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create indirect commands layout, invalid pIndirectCommandsLayout handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create indirect commands layout, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    // TODO: Support pTokens members (union-typed binary data, see Process_vkCreatePipelineBinariesKHR for reference)

    auto pipelineLayoutId = context.GetPipelineLayoutId(createInfo->pipelineLayout, true);

    statements.InsertIndirectCommandsLayout(
        layout,
        device,
        ci.flags,
        ci.shaderStages,
        ci.indirectStride,
        pipelineLayoutId,
        ci.tokenCount,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyIndirectCommandsLayoutEXT(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId indirectCommandsLayout,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyIndirectCommandsLayoutEXT(
        call_info, device, indirectCommandsLayout, pAllocator
    );

    if (auto id = context.ExtractId(
            indirectCommandsLayout,
            context.indirectCommandsLayoutHandleToId,
            "indirectCommandsLayout",
            this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyIndirectCommandsLayoutUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateMicromapEXT(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkMicromapCreateInfoEXT>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkMicromapEXT>* pMicromap
)
{
    VulkanSqliteConsumer::Process_vkCreateMicromapEXT(
        call_info, returnValue, device, pCreateInfo, pAllocator, pMicromap
    );

    auto [micromapValid, micromap] = GetHandle(pMicromap);
    if (!micromapValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create micromap, invalid pMicromap handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create micromap, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    auto bufferId = context.GetBufferId(createInfo->buffer, true);

    statements.InsertMicromap(
        micromap, device, ci.createFlags, bufferId, ci.offset, ci.size, ci.type, ci.deviceAddress, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyMicromapEXT(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId micromap,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyMicromapEXT(call_info, device, micromap, pAllocator);

    if (auto id = context.ExtractId(micromap, context.micromapHandleToId, "micromap", this->block_index_))
    {
        statements.DestroyObject(statements.destroyMicromapUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateOpticalFlowSessionNV(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkOpticalFlowSessionCreateInfoNV>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkOpticalFlowSessionNV>* pSession
)
{
    VulkanSqliteConsumer::Process_vkCreateOpticalFlowSessionNV(
        call_info, returnValue, device, pCreateInfo, pAllocator, pSession
    );

    auto [sessionValid, session] = GetHandle(pSession);
    if (!sessionValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create optical flow session, invalid pSession handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create optical flow session, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;

    statements.InsertOpticalFlowSession(
        session,
        device,
        ci.width,
        ci.height,
        ci.imageFormat,
        ci.flowVectorFormat,
        ci.costFormat,
        ci.outputGridSize,
        ci.hintGridSize,
        ci.performanceLevel,
        ci.flags,
        this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyOpticalFlowSessionNV(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId session,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyOpticalFlowSessionNV(call_info, device, session, pAllocator);

    if (auto id =
            context.ExtractId(session, context.opticalFlowSessionHandleToId, "opticalFlowSession", this->block_index_))
    {
        statements.DestroyObject(statements.destroyOpticalFlowSessionUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDataGraphPipelinesARM(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId deferredOperation,
    format::HandleId pipelineCache,
    uint32_t createInfoCount,
    StructPointerDecoder<Decoded_VkDataGraphPipelineCreateInfoARM>* pCreateInfos,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkPipeline>* pPipelines
)
{
    VulkanSqliteConsumer::Process_vkCreateDataGraphPipelinesARM(
        call_info,
        returnValue,
        device,
        deferredOperation,
        pipelineCache,
        createInfoCount,
        pCreateInfos,
        pAllocator,
        pPipelines
    );

    auto [pipelinesValid, pipelines, pipelineCount] = GetHandleArray(pPipelines);
    if (!pipelinesValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create data graph pipeline, invalid pPipelines array");
        }
        return;
    }

    auto [createInfosValid, createInfos, createInfosCount] = GetMetaStructArray(pCreateInfos);
    if (!createInfosValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create data graph pipeline, invalid pCreateInfos struct array");
        }
        return;
    }

    auto deviceId = context.GetDeviceId(device);

    for (size_t i = 0; i < pipelineCount; ++i)
    {
        auto& createInfo = createInfos[i];

        auto pipelineFlags = createInfo.decoded_value->flags;

        // DataGraph pipelines do not support pipeline derivatives
        const std::optional<int64_t> basePipeline = std::nullopt;

        auto pipelineLayout = context.GetPipelineLayoutId(createInfo.layout, /*allowNull=*/true);

        auto pipeline = pipelines[i];
        auto pipelineHandle = ToInt64(pipeline);
        auto pipelineId = statements.InsertPipelineDataGraph(
            pipelineHandle, deviceId, pipelineFlags, basePipeline, pipelineLayout, this->block_index_
        );

        auto infoId = statements.InsertDataGraphPipelineInfo(pipelineId);

        auto [resourceInfosValid, resourceInfos, resourceInfosCount] = GetMetaStructArray(createInfo.pResourceInfos);
        if (resourceInfosValid)
        {
            for (uint32_t j = 0; j < resourceInfosCount; ++j)
            {
                auto& ri = *resourceInfos[j].decoded_value;
                statements.InsertDataGraphPipelineResourceInfo(
                    infoId, j, ri.descriptorSet, ri.binding, ri.arrayElement
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCreateDataGraphPipelineSessionARM(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    StructPointerDecoder<Decoded_VkDataGraphPipelineSessionCreateInfoARM>* pCreateInfo,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator,
    HandlePointerDecoder<VkDataGraphPipelineSessionARM>* pSession
)
{
    VulkanSqliteConsumer::Process_vkCreateDataGraphPipelineSessionARM(
        call_info, returnValue, device, pCreateInfo, pAllocator, pSession
    );

    if (returnValue != VK_SUCCESS)
    {
        return;
    }

    auto [sessionValid, session] = GetHandle(pSession);
    if (!sessionValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create data graph pipeline session, invalid session handle");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(pCreateInfo);
    if (!createInfoValid)
    {
        if (returnValue == VK_SUCCESS)
        {
            LOG_CMD_WARNING("Failed to create data graph pipeline session, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto& ci = *createInfo->decoded_value;
    auto deviceId = context.GetDeviceId(device);

    auto pipelineIter = context.pipelineHandleToId.find(ToInt64(createInfo->dataGraphPipeline));
    if (pipelineIter == context.pipelineHandleToId.end())
    {
        LOG_CMD_WARNING(
            "Failed to find data graph pipeline for session with handle %" PRIu64, createInfo->dataGraphPipeline
        );
        return;
    }

    statements.InsertDataGraphPipelineSession(
        ToInt64(session), deviceId, ci.flags, pipelineIter->second, this->block_index_
    );
}

void VulkanSqliteConsumerExt::Process_vkDestroyDataGraphPipelineSessionARM(
    const ApiCallInfo& call_info,
    format::HandleId device,
    format::HandleId session,
    StructPointerDecoder<Decoded_VkAllocationCallbacks>* pAllocator
)
{
    VulkanSqliteConsumer::Process_vkDestroyDataGraphPipelineSessionARM(call_info, device, session, pAllocator);

    if (auto id = context.ExtractId(
            session, context.dataGraphPipelineSessionHandleToId, "dataGraphPipelineSession", this->block_index_
        ))
    {
        statements.DestroyObject(statements.destroyDataGraphPipelineSessionUpdateStatement, this->block_index_, *id);
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdDispatchDataGraphARM(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId session,
    StructPointerDecoder<Decoded_VkDataGraphPipelineDispatchInfoARM>* pDispatchInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdDispatchDataGraphARM(call_info, commandBuffer, session, pDispatchInfo);

    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert data graph dispatch recording, failed to find command buffer recording for handle "
            "%" PRIi64,
            commandBuffer
        );
        return;
    }

    auto sessionId = context.GetDataGraphPipelineSessionId(session, /*allowNull=*/true);
    auto cmdDataGraphDispatchRecordingId = statements.InsertCmdDataGraphDispatchRecording(
        this->block_index_, sessionId, commandBufferRecordingIter->second
    );

    // TODO: Expose dispatch info flags in dispatch recording info
    auto [dispatchInfoValid, dispatchInfo] = GetMetaStructPointer(pDispatchInfo);
    if (dispatchInfoValid && dispatchInfo)
    {
        statements.InsertCmdDataGraphDispatchRecordingInfo(
            cmdDataGraphDispatchRecordingId, dispatchInfo->decoded_value->flags
        );
    }

    context.InvalidateDynamicStates(commandBufferRecordingIter->second, VK_PIPELINE_BIND_POINT_DATA_GRAPH_ARM, {});
}

//////// TODO These were added as custom handled functions by the export JSON consumer
//////// Determine if we still need to perform custom implementation when handling
//////// these calls
void VulkanSqliteConsumerExt::Process_vkCmdBuildAccelerationStructuresIndirectKHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    uint32_t infoCount,
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR>* pInfos,
    PointerDecoder<VkDeviceAddress>* pIndirectDeviceAddresses,
    PointerDecoder<uint32_t>* pIndirectStrides,
    PointerDecoder<uint32_t*>* ppMaxPrimitiveCounts
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdBuildAccelerationStructuresIndirectKHR(
        call_info, commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts
    );

    /*
    // TODO need to figure out how to pack the custom structs into the db
    // needs acceleration structure table?
    WriteApiCallToFile(call_info, "vkCmdBuildAccelerationStructuresIndirectKHR", [&](nlohmann::ordered_json
    &function)
                        {
        auto& args = function[NameArgs()];
        HandleToJson(args["commandBuffer"], commandBuffer, json_options_);
        FieldToJson(args["infoCount"], infoCount, json_options_);
        FieldToJson(args["pInfos"], pInfos, json_options_);
        FieldToJson(args["pIndirectDeviceAddresses"], pIndirectDeviceAddresses, json_options_);
        FieldToJson(args["pIndirectStrides"], pIndirectStrides, json_options_);

        auto infos                     = pInfos ? pInfos->GetPointer() : nullptr;
        auto max_primitive_counts      = ppMaxPrimitiveCounts ? ppMaxPrimitiveCounts->GetPointer() : nullptr;
        auto max_primitive_counts_json = args["ppMaxPrimitiveCounts"];

        for (uint32_t i = 0; i < infoCount; ++i)
        {
            auto element = max_primitive_counts_json[i];
            FieldToJson(max_primitive_counts_json[i], max_primitive_counts[i], infos[i].geometryCount,
    json_options_); } });
    */
}

void VulkanSqliteConsumerExt::Process_vkGetPipelineCacheData(
    const ApiCallInfo& call_info,
    VkResult returnValue,
    format::HandleId device,
    format::HandleId pipelineCache,
    PointerDecoder<size_t>* pDataSize,
    PointerDecoder<uint8_t>* pData
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkGetPipelineCacheData(
        call_info, returnValue, device, pipelineCache, pDataSize, pData
    );

    /*
    // TODO need to figure out what to do with this
    WriteApiCallToFile(call_info, "vkGetPipelineCacheData", [&](nlohmann::ordered_json &function)
                        {
        FieldToJson(function[NameReturn()], returnValue, json_options_);
        auto& args = function[NameArgs()];
        HandleToJson(args["device"], device, json_options_);
        HandleToJson(args["pipelineCache"], pipelineCache, json_options_);
        FieldToJson(args["pDataSize"], pDataSize, json_options_);
        if (pData->IsNull())
        {
            args["pData"] = nullptr;
        }
        else if (json_options_.dump_binaries)
        {
            auto        decodedData = pData->GetPointer();
            auto        dataSize    = pData->GetLength();
            std::string filename     = GenerateFilename("pipeline_cache_data.bin");
            std::string basename     = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
            std::string filepath     = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
            if (WriteBinaryFile(filepath, dataSize, decodedData))
            {
                FieldToJson(args["pData"], basename, json_options_);
            }
            else
            {
                FieldToJson(args["pData"], "Unable to write file", json_options_);
            }
        }
        else
        {
            FieldToJson(args["pData"], "[Binary data]", json_options_);
        } });
    */
}

void VulkanSqliteConsumerExt::Process_vkCmdPushConstants(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    PointerDecoder<uint8_t>* pValues
)
{
    // generate the base apiEvents database entries
    VulkanSqliteConsumer::Process_vkCmdPushConstants(
        call_info, commandBuffer, layout, stageFlags, offset, size, pValues
    );

    // TODO need to figure out how to pack the custom structs into the db
    // May want to update existing push constants values or have table of
    // push constant changes
    /*
    WriteApiCallToFile(call_info, "vkCmdPushConstants", [&](nlohmann::ordered_json &function)
                        {
        auto& args = function[NameArgs()];
        HandleToJson(args["commandBuffer"], commandBuffer, json_options_);
        HandleToJson(args["layout"], layout, json_options_);
        FieldToJson(VkShaderStageFlags_t(), args["stageFlags"], stageFlags, json_options_);
        FieldToJson(args["offset"], offset, json_options_);
        FieldToJson(args["size"], size, json_options_);
        FieldToJson(args["pValues"], pValues, json_options_);
        if (pValues->IsNull())
        {
            args["pValues"] = nullptr;
        }
        else if (json_options_.dump_binaries)
        {
            auto        decodedData = pValues->GetPointer();
            auto        dataSize    = pValues->GetLength();
            std::string filename     = GenerateFilename("pushconstants.bin");
            std::string basename     = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
            std::string filepath     = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
            if (WriteBinaryFile(filepath, dataSize, decodedData))
            {
                FieldToJson(args["pValues"], basename, json_options_);
            }
            else
            {
                FieldToJson(args["pValues"], "Unable to write file", json_options_);
            }
        }
        else
        {
            FieldToJson(args["pValues"], "[Binary data]", json_options_);
        } });
    */
}

// Transfer command utility functions
void VulkanSqliteConsumerExt::ProcessTransferCommandBufferCopy(
    format::HandleId commandBuffer,
    format::HandleId srcBuffer,
    format::HandleId dstBuffer,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferCopy>* pRegions
)
{
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandBufferCopy(
        instanceId, context.GetBufferId(srcBuffer), context.GetBufferId(dstBuffer)
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcBufferId = context.GetBufferId(srcBuffer);
        auto dstBufferId = context.GetBufferId(dstBuffer);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];
            statements.InsertTransferCommandRegionBufferCopy(
                instanceId,
                i, // regionIndex
                srcBufferId.value(),
                dstBufferId.value(),
                region
            );
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandBufferCopy2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pCopyBufferInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandBufferCopy(
            instanceId, context.GetBufferId(info->srcBuffer), context.GetBufferId(info->dstBuffer)
        );

        // Insert region data from pRegions in VkCopyBufferInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcBufferId = context.GetBufferId(info->srcBuffer);
            auto dstBufferId = context.GetBufferId(info->dstBuffer);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];
                statements.InsertTransferCommandRegionBufferCopy(
                    instanceId,
                    i, // regionIndex
                    srcBufferId.value(),
                    dstBufferId.value(),
                    VkBufferCopy{ region.srcOffset, region.dstOffset, region.size }
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandImageCopy(
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkImageCopy>* pRegions
)
{
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandImageCopy(
        instanceId, context.GetImageId(srcImage), context.GetImageId(dstImage), srcImageLayout, dstImageLayout
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcImageId = context.GetImageId(srcImage);
        auto dstImageId = context.GetImageId(dstImage);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];
            statements.InsertTransferCommandRegionImageCopy(
                instanceId,
                i, // regionIndex
                srcImageId.value(),
                dstImageId.value(),
                region.srcSubresource.baseArrayLayer,
                region.srcSubresource.layerCount,
                region.srcSubresource.mipLevel,
                region.dstSubresource.baseArrayLayer,
                region.dstSubresource.layerCount,
                region.dstSubresource.mipLevel,
                region.srcOffset.x,   // srcOffsetX
                region.srcOffset.y,   // srcOffsetY
                region.srcOffset.z,   // srcOffsetZ
                region.dstOffset.x,   // dstOffsetX
                region.dstOffset.y,   // dstOffsetY
                region.dstOffset.z,   // dstOffsetZ
                region.extent.width,  // srcExtentWidth
                region.extent.height, // srcExtentHeight
                region.extent.depth,  // srcExtentDepth
                region.extent.width,  // dstExtentWidth
                region.extent.height, // dstExtentHeight
                region.extent.depth   // dstExtentDepth
            );
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandImageCopy2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pCopyImageInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandImageCopy(
            instanceId,
            context.GetImageId(info->srcImage),
            context.GetImageId(info->dstImage),
            info->decoded_value->srcImageLayout,
            info->decoded_value->dstImageLayout
        );

        // Insert region data from pRegions in VkCopyImageInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcImageId = context.GetImageId(info->srcImage);
            auto dstImageId = context.GetImageId(info->dstImage);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];
                statements.InsertTransferCommandRegionImageCopy(
                    instanceId,
                    i, // regionIndex
                    srcImageId.value(),
                    dstImageId.value(),
                    region.srcSubresource.baseArrayLayer,
                    region.srcSubresource.layerCount,
                    region.srcSubresource.mipLevel,
                    region.dstSubresource.baseArrayLayer,
                    region.dstSubresource.layerCount,
                    region.dstSubresource.mipLevel,
                    region.srcOffset.x,   // srcOffsetX
                    region.srcOffset.y,   // srcOffsetY
                    region.srcOffset.z,   // srcOffsetZ
                    region.dstOffset.x,   // dstOffsetX
                    region.dstOffset.y,   // dstOffsetY
                    region.dstOffset.z,   // dstOffsetZ
                    region.extent.width,  // srcExtentWidth
                    region.extent.height, // srcExtentHeight
                    region.extent.depth,  // srcExtentDepth
                    region.extent.width,  // dstExtentWidth
                    region.extent.height, // dstExtentHeight
                    region.extent.depth   // dstExtentDepth
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandBufferToImage(
    format::HandleId commandBuffer,
    format::HandleId srcBuffer,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
)
{
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandBufferToImage(
        instanceId, context.GetBufferId(srcBuffer), context.GetImageId(dstImage), dstImageLayout
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcBufferId = context.GetBufferId(srcBuffer);
        auto dstImageId = context.GetImageId(dstImage);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];
            statements.InsertTransferCommandRegionBufferImageCopy(
                instanceId,
                i, // regionIndex
                srcBufferId.value(),
                dstImageId.value(),
                1, // isBufferSource (buffer→image)
                region.bufferOffset,
                region.imageSubresource.baseArrayLayer,
                region.imageSubresource.layerCount,
                region.imageSubresource.mipLevel,
                region.imageOffset.x,
                region.imageOffset.y,
                region.imageOffset.z,
                region.imageExtent.width,
                region.imageExtent.height,
                region.imageExtent.depth
            );
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandBufferToImage2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pCopyBufferToImageInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandBufferToImage(
            instanceId,
            context.GetBufferId(info->srcBuffer),
            context.GetImageId(info->dstImage),
            info->decoded_value->dstImageLayout
        );

        // Insert region data from pRegions in VkCopyBufferToImageInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcBufferId = context.GetBufferId(info->srcBuffer);
            auto dstImageId = context.GetImageId(info->dstImage);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];
                statements.InsertTransferCommandRegionBufferImageCopy(
                    instanceId,
                    i, // regionIndex
                    srcBufferId.value(),
                    dstImageId.value(),
                    1, // isBufferSource (buffer→image)
                    region.bufferOffset,
                    region.imageSubresource.baseArrayLayer,
                    region.imageSubresource.layerCount,
                    region.imageSubresource.mipLevel,
                    region.imageOffset.x,
                    region.imageOffset.y,
                    region.imageOffset.z,
                    region.imageExtent.width,
                    region.imageExtent.height,
                    region.imageExtent.depth
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandImageToBuffer(
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstBuffer,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
)
{
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandImageToBuffer(
        instanceId, context.GetImageId(srcImage), context.GetBufferId(dstBuffer), srcImageLayout
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcImageId = context.GetImageId(srcImage);
        auto dstBufferId = context.GetBufferId(dstBuffer);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];
            statements.InsertTransferCommandRegionBufferImageCopy(
                instanceId,
                i, // regionIndex
                dstBufferId.value(),
                srcImageId.value(),
                0, // isBufferSource (image→buffer)
                region.bufferOffset,
                region.imageSubresource.baseArrayLayer,
                region.imageSubresource.layerCount,
                region.imageSubresource.mipLevel,
                region.imageOffset.x,
                region.imageOffset.y,
                region.imageOffset.z,
                region.imageExtent.width,
                region.imageExtent.height,
                region.imageExtent.depth
            );
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandImageToBuffer2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pCopyImageToBufferInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandImageToBuffer(
            instanceId,
            context.GetImageId(info->srcImage),
            context.GetBufferId(info->dstBuffer),
            info->decoded_value->srcImageLayout
        );

        // Insert region data from pRegions in VkCopyImageToBufferInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcImageId = context.GetImageId(info->srcImage);
            auto dstBufferId = context.GetBufferId(info->dstBuffer);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];
                statements.InsertTransferCommandRegionBufferImageCopy(
                    instanceId,
                    i, // regionIndex
                    dstBufferId.value(),
                    srcImageId.value(),
                    0, // isBufferSource (image→buffer)
                    region.bufferOffset,
                    region.imageSubresource.baseArrayLayer,
                    region.imageSubresource.layerCount,
                    region.imageSubresource.mipLevel,
                    region.imageOffset.x,
                    region.imageOffset.y,
                    region.imageOffset.z,
                    region.imageExtent.width,
                    region.imageExtent.height,
                    region.imageExtent.depth
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandBlit(
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    VkFilter filter,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkImageBlit>* pRegions
)
{
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandBlit(
        instanceId, context.GetImageId(srcImage), context.GetImageId(dstImage), srcImageLayout, dstImageLayout, filter
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcImageId = context.GetImageId(srcImage);
        auto dstImageId = context.GetImageId(dstImage);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];

            // Calculate true min/max for source (handles flips)
            int32_t srcMinX = std::min(region.srcOffsets[0].x, region.srcOffsets[1].x);
            int32_t srcMinY = std::min(region.srcOffsets[0].y, region.srcOffsets[1].y);
            int32_t srcMinZ = std::min(region.srcOffsets[0].z, region.srcOffsets[1].z);
            int32_t srcMaxX = std::max(region.srcOffsets[0].x, region.srcOffsets[1].x);
            int32_t srcMaxY = std::max(region.srcOffsets[0].y, region.srcOffsets[1].y);
            int32_t srcMaxZ = std::max(region.srcOffsets[0].z, region.srcOffsets[1].z);

            // Calculate true min/max for destination (handles flips)
            int32_t dstMinX = std::min(region.dstOffsets[0].x, region.dstOffsets[1].x);
            int32_t dstMinY = std::min(region.dstOffsets[0].y, region.dstOffsets[1].y);
            int32_t dstMinZ = std::min(region.dstOffsets[0].z, region.dstOffsets[1].z);
            int32_t dstMaxX = std::max(region.dstOffsets[0].x, region.dstOffsets[1].x);
            int32_t dstMaxY = std::max(region.dstOffsets[0].y, region.dstOffsets[1].y);
            int32_t dstMaxZ = std::max(region.dstOffsets[0].z, region.dstOffsets[1].z);

            statements.InsertTransferCommandRegionImageCopy(
                instanceId,
                i, // regionIndex
                srcImageId.value(),
                dstImageId.value(),
                region.srcSubresource.baseArrayLayer,
                region.srcSubresource.layerCount,
                region.srcSubresource.mipLevel,
                region.dstSubresource.baseArrayLayer,
                region.dstSubresource.layerCount,
                region.dstSubresource.mipLevel,
                srcMinX,           // srcOffsetX
                srcMinY,           // srcOffsetY
                srcMinZ,           // srcOffsetZ
                dstMinX,           // dstOffsetX
                dstMinY,           // dstOffsetY
                dstMinZ,           // dstOffsetZ
                srcMaxX - srcMinX, // srcExtentWidth
                srcMaxY - srcMinY, // srcExtentHeight
                srcMaxZ - srcMinZ, // srcExtentDepth
                dstMaxX - dstMinX, // dstExtentWidth
                dstMaxY - dstMinY, // dstExtentHeight
                dstMaxZ - dstMinZ  // dstExtentDepth
            );
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandBlit2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pBlitImageInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandBlit(
            instanceId,
            context.GetImageId(info->srcImage),
            context.GetImageId(info->dstImage),
            info->decoded_value->srcImageLayout,
            info->decoded_value->dstImageLayout,
            info->decoded_value->filter
        );

        // Insert region data from pRegions in VkBlitImageInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcImageId = context.GetImageId(info->srcImage);
            auto dstImageId = context.GetImageId(info->dstImage);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];

                // Calculate true min/max for source (handles flips)
                int32_t srcMinX = std::min(region.srcOffsets[0].x, region.srcOffsets[1].x);
                int32_t srcMinY = std::min(region.srcOffsets[0].y, region.srcOffsets[1].y);
                int32_t srcMinZ = std::min(region.srcOffsets[0].z, region.srcOffsets[1].z);
                int32_t srcMaxX = std::max(region.srcOffsets[0].x, region.srcOffsets[1].x);
                int32_t srcMaxY = std::max(region.srcOffsets[0].y, region.srcOffsets[1].y);
                int32_t srcMaxZ = std::max(region.srcOffsets[0].z, region.srcOffsets[1].z);

                // Calculate true min/max for destination (handles flips)
                int32_t dstMinX = std::min(region.dstOffsets[0].x, region.dstOffsets[1].x);
                int32_t dstMinY = std::min(region.dstOffsets[0].y, region.dstOffsets[1].y);
                int32_t dstMinZ = std::min(region.dstOffsets[0].z, region.dstOffsets[1].z);
                int32_t dstMaxX = std::max(region.dstOffsets[0].x, region.dstOffsets[1].x);
                int32_t dstMaxY = std::max(region.dstOffsets[0].y, region.dstOffsets[1].y);
                int32_t dstMaxZ = std::max(region.dstOffsets[0].z, region.dstOffsets[1].z);

                statements.InsertTransferCommandRegionImageCopy(
                    instanceId,
                    i, // regionIndex
                    srcImageId.value(),
                    dstImageId.value(),
                    region.srcSubresource.baseArrayLayer,
                    region.srcSubresource.layerCount,
                    region.srcSubresource.mipLevel,
                    region.dstSubresource.baseArrayLayer,
                    region.dstSubresource.layerCount,
                    region.dstSubresource.mipLevel,
                    srcMinX,           // srcOffsetX
                    srcMinY,           // srcOffsetY
                    srcMinZ,           // srcOffsetZ
                    dstMinX,           // dstOffsetX
                    dstMinY,           // dstOffsetY
                    dstMinZ,           // dstOffsetZ
                    srcMaxX - srcMinX, // srcExtentWidth
                    srcMaxY - srcMinY, // srcExtentHeight
                    srcMaxZ - srcMinZ, // srcExtentDepth
                    dstMaxX - dstMinX, // dstExtentWidth
                    dstMaxY - dstMinY, // dstExtentHeight
                    dstMaxZ - dstMinZ  // dstExtentDepth
                );
            }
        }
    }
}

void VulkanSqliteConsumerExt::ProcessTransferCommandResolve2(
    format::HandleId commandBuffer, StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
)
{
    auto [infoValid, info] = GetMetaStructPointer(pResolveImageInfo);
    if (infoValid)
    {
        auto instanceId =
            statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

        statements.UpdateTransferCommandImageCopy(
            instanceId,
            context.GetImageId(info->srcImage),
            context.GetImageId(info->dstImage),
            info->decoded_value->srcImageLayout,
            info->decoded_value->dstImageLayout
        );

        // Insert region data from pRegions in VkResolveImageInfo2
        if (info->pRegions != nullptr && info->pRegions->GetPointer() != nullptr && info->decoded_value != nullptr)
        {
            auto srcImageId = context.GetImageId(info->srcImage);
            auto dstImageId = context.GetImageId(info->dstImage);
            uint32_t regionCount = info->decoded_value->regionCount;

            for (uint32_t i = 0; i < regionCount; ++i)
            {
                const auto& region = info->pRegions->GetPointer()[i];
                statements.InsertTransferCommandRegionImageCopy(
                    instanceId,
                    i, // regionIndex
                    srcImageId.value(),
                    dstImageId.value(),
                    region.srcSubresource.baseArrayLayer,
                    region.srcSubresource.layerCount,
                    region.srcSubresource.mipLevel,
                    region.dstSubresource.baseArrayLayer,
                    region.dstSubresource.layerCount,
                    region.dstSubresource.mipLevel,
                    region.srcOffset.x,   // srcOffsetX
                    region.srcOffset.y,   // srcOffsetY
                    region.srcOffset.z,   // srcOffsetZ
                    region.dstOffset.x,   // dstOffsetX
                    region.dstOffset.y,   // dstOffsetY
                    region.dstOffset.z,   // dstOffsetZ
                    region.extent.width,  // srcExtentWidth
                    region.extent.height, // srcExtentHeight
                    region.extent.depth,  // srcExtentDepth
                    region.extent.width,  // dstExtentWidth
                    region.extent.height, // dstExtentHeight
                    region.extent.depth   // dstExtentDepth
                );
            }
        }
    }
}

// Transfer command implementations
void VulkanSqliteConsumerExt::Process_vkCmdCopyBuffer(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcBuffer,
    format::HandleId dstBuffer,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferCopy>* pRegions
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBuffer(
        call_info, commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions
    );
    ProcessTransferCommandBufferCopy(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyBuffer2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBuffer2(call_info, commandBuffer, pCopyBufferInfo);
    ProcessTransferCommandBufferCopy2(commandBuffer, pCopyBufferInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyBuffer2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferInfo2>* pCopyBufferInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBuffer2KHR(call_info, commandBuffer, pCopyBufferInfo);
    ProcessTransferCommandBufferCopy2(commandBuffer, pCopyBufferInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImage(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkImageCopy>* pRegions
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImage(
        call_info, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions
    );
    ProcessTransferCommandImageCopy(
        commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImage2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImage2(call_info, commandBuffer, pCopyImageInfo);
    ProcessTransferCommandImageCopy2(commandBuffer, pCopyImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImage2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageInfo2>* pCopyImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImage2KHR(call_info, commandBuffer, pCopyImageInfo);
    ProcessTransferCommandImageCopy2(commandBuffer, pCopyImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyBufferToImage(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcBuffer,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage(
        call_info, commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions
    );
    ProcessTransferCommandBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyBufferToImage2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage2(call_info, commandBuffer, pCopyBufferToImageInfo);
    ProcessTransferCommandBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyBufferToImage2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyBufferToImageInfo2>* pCopyBufferToImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage2KHR(call_info, commandBuffer, pCopyBufferToImageInfo);
    ProcessTransferCommandBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImageToBuffer(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstBuffer,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkBufferImageCopy>* pRegions
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer(
        call_info, commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions
    );
    ProcessTransferCommandImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImageToBuffer2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer2(call_info, commandBuffer, pCopyImageToBufferInfo);
    ProcessTransferCommandImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdCopyImageToBuffer2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkCopyImageToBufferInfo2>* pCopyImageToBufferInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer2KHR(call_info, commandBuffer, pCopyImageToBufferInfo);
    ProcessTransferCommandImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdBlitImage(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkImageBlit>* pRegions,
    VkFilter filter
)
{
    VulkanSqliteConsumer::Process_vkCmdBlitImage(
        call_info, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter
    );
    ProcessTransferCommandBlit(
        commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, filter, regionCount, pRegions
    );
}

void VulkanSqliteConsumerExt::Process_vkCmdBlitImage2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdBlitImage2(call_info, commandBuffer, pBlitImageInfo);
    ProcessTransferCommandBlit2(commandBuffer, pBlitImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdBlitImage2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkBlitImageInfo2>* pBlitImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdBlitImage2KHR(call_info, commandBuffer, pBlitImageInfo);
    ProcessTransferCommandBlit2(commandBuffer, pBlitImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdResolveImage(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId srcImage,
    VkImageLayout srcImageLayout,
    format::HandleId dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    StructPointerDecoder<Decoded_VkImageResolve>* pRegions
)
{
    VulkanSqliteConsumer::Process_vkCmdResolveImage(
        call_info, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions
    );

    // Process as transfer command with regions
    auto instanceId =
        statements.InsertTransferCommand(this->block_index_, context.GetCommandBufferRecordingId(commandBuffer));

    statements.UpdateTransferCommandImageCopy(
        instanceId, context.GetImageId(srcImage), context.GetImageId(dstImage), srcImageLayout, dstImageLayout
    );

    // Insert region data
    if (pRegions != nullptr && pRegions->GetPointer() != nullptr)
    {
        auto srcImageId = context.GetImageId(srcImage);
        auto dstImageId = context.GetImageId(dstImage);

        for (uint32_t i = 0; i < regionCount; ++i)
        {
            const auto& region = pRegions->GetPointer()[i];
            statements.InsertTransferCommandRegionImageCopy(
                instanceId,
                i, // regionIndex
                srcImageId.value(),
                dstImageId.value(),
                region.srcSubresource.baseArrayLayer,
                region.srcSubresource.layerCount,
                region.srcSubresource.mipLevel,
                region.dstSubresource.baseArrayLayer,
                region.dstSubresource.layerCount,
                region.dstSubresource.mipLevel,
                region.srcOffset.x,   // srcOffsetX
                region.srcOffset.y,   // srcOffsetY
                region.srcOffset.z,   // srcOffsetZ
                region.dstOffset.x,   // dstOffsetX
                region.dstOffset.y,   // dstOffsetY
                region.dstOffset.z,   // dstOffsetZ
                region.extent.width,  // srcExtentWidth
                region.extent.height, // srcExtentHeight
                region.extent.depth,  // srcExtentDepth
                region.extent.width,  // dstExtentWidth
                region.extent.height, // dstExtentHeight
                region.extent.depth   // dstExtentDepth
            );
        }
    }
}

void VulkanSqliteConsumerExt::Process_vkCmdResolveImage2(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdResolveImage2(call_info, commandBuffer, pResolveImageInfo);
    ProcessTransferCommandResolve2(commandBuffer, pResolveImageInfo);
}

void VulkanSqliteConsumerExt::Process_vkCmdResolveImage2KHR(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    StructPointerDecoder<Decoded_VkResolveImageInfo2>* pResolveImageInfo
)
{
    VulkanSqliteConsumer::Process_vkCmdResolveImage2KHR(call_info, commandBuffer, pResolveImageInfo);
    ProcessTransferCommandResolve2(commandBuffer, pResolveImageInfo);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)