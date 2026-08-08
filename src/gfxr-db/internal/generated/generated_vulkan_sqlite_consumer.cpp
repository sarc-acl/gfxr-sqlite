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

#include "util/defines.h"
#include "generated/generated_vulkan_sqlite_consumer.h"
#include "generated/generated_vulkan_struct_to_sqlite.h"
#include "decode/consumer_utils.h"
#include "decode/custom_vulkan_struct_to_sqlite.h"
#include "decode/api_event_types.h"

#include "sqlite_utils.h"

#include <cstdint>
#include <sstream>
#include <optional>
#include <unordered_set>
GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)
namespace
{
void RecordTrackedCmdCommand(
    VulkanSqliteConsumerContext&    context,
    VulkanSqlitePreparedStatements& statements,
    uint64_t                        block_index,
    format::HandleId                commandBuffer)
{
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert tracked command, failed to find command buffer recording for command buffer with handle %" PRIi64,
            commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
            }
        }
    }
    statements.InsertTrackedCmdCommand(block_index, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
}
} // namespace
namespace
{
void RecordTrackedDeviceCommand(
    VulkanSqliteConsumerContext&    context,
    VulkanSqlitePreparedStatements& statements,
    uint64_t                        block_index,
    format::HandleId                device)
{
    auto deviceId = context.GetDeviceId(device);
    if (!deviceId.has_value())
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to insert device command, unknown device handle");
    }
    else
    {
        statements.InsertTrackedDeviceCommand(*deviceId, block_index);
    }
}
} // namespace
void VulkanSqliteConsumer::Process_vkCreateInstance(
    const ApiCallInfo&                          call_info,
    args::CreateInstance&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateInstance");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    FieldToSqlite(statements, fieldInfo, 1, "pCreateInfo", &args.pCreateInfo, "const VkInstanceCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 2, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 3, "pInstance", &args.pInstance, "VkInstance*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyInstance(
    const ApiCallInfo&                          call_info,
    args::DestroyInstance&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyInstance");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkEnumeratePhysicalDevices(
    const ApiCallInfo&                          call_info,
    args::EnumeratePhysicalDevices&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEnumeratePhysicalDevices");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pPhysicalDeviceCount", args.pPhysicalDeviceCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pPhysicalDevices", &args.pPhysicalDevices, "VkPhysicalDevice*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFeatures(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFeatures&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFeatures");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFeatures", &args.pFeatures, "VkPhysicalDeviceFeatures*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFormatProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFormatProperties&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFormatProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    FieldToSqlite(statements, fieldInfo, 3, "pFormatProperties", &args.pFormatProperties, "VkFormatProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceImageFormatProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceImageFormatProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceImageFormatProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    RecordField(
        statements, fieldInfo, 3, "type", "VkImageType", args.type);
    RecordField(
        statements, fieldInfo, 4, "tiling", "VkImageTiling", args.tiling);
    RecordField(
        statements, fieldInfo, 5, "usage", "VkImageUsageFlags", args.usage);
    RecordField(
        statements, fieldInfo, 6, "flags", "VkImageCreateFlags", args.flags);
    FieldToSqlite(statements, fieldInfo, 7, "pImageFormatProperties", &args.pImageFormatProperties, "VkImageFormatProperties*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceProperties&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pProperties", &args.pProperties, "VkPhysicalDeviceProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueFamilyPropertyCount", args.pQueueFamilyPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyProperties", &args.pQueueFamilyProperties, "VkQueueFamilyProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceMemoryProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceMemoryProperties&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceMemoryProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryProperties", &args.pMemoryProperties, "VkPhysicalDeviceMemoryProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateDevice(
    const ApiCallInfo&                          call_info,
    args::CreateDevice&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDevice");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDeviceCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pDevice", &args.pDevice, "VkDevice*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDevice(
    const ApiCallInfo&                          call_info,
    args::DestroyDevice&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDevice");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceQueue(
    const ApiCallInfo&                          call_info,
    args::GetDeviceQueue&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceQueue");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    RecordField(
        statements, fieldInfo, 3, "queueIndex", "uint32_t", args.queueIndex);
    FieldToSqlite(statements, fieldInfo, 4, "pQueue", &args.pQueue, "VkQueue*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkQueueSubmit(
    const ApiCallInfo&                          call_info,
    args::QueueSubmit&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueSubmit");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    RecordField(
        statements, fieldInfo, 2, "submitCount", "uint32_t", args.submitCount);
    FieldToSqlite(statements, fieldInfo, 3, "pSubmits", &args.pSubmits, "const VkSubmitInfo*");
    RecordField(
        statements, fieldInfo, 4, "fence", "VkFence", args.fence);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkQueueWaitIdle(
    const ApiCallInfo&                          call_info,
    args::QueueWaitIdle&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueWaitIdle");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDeviceWaitIdle(
    const ApiCallInfo&                          call_info,
    args::DeviceWaitIdle&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDeviceWaitIdle");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkAllocateMemory(
    const ApiCallInfo&                          call_info,
    args::AllocateMemory&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAllocateMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocateInfo", &args.pAllocateInfo, "const VkMemoryAllocateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pMemory", &args.pMemory, "VkDeviceMemory*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkFreeMemory(
    const ApiCallInfo&                          call_info,
    args::FreeMemory&                           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkFreeMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkMapMemory(
    const ApiCallInfo&                          call_info,
    args::MapMemory&                            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkMapMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "size", "VkDeviceSize", args.size);
    RecordField(
        statements, fieldInfo, 5, "flags", "VkMemoryMapFlags", args.flags);
    FieldToSqlite(statements, fieldInfo, 6, "ppData", args.ppData, "void**");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkUnmapMemory(
    const ApiCallInfo&                          call_info,
    args::UnmapMemory&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUnmapMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkFlushMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    args::FlushMappedMemoryRanges&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkFlushMappedMemoryRanges");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memoryRangeCount", "uint32_t", args.memoryRangeCount);
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRanges", &args.pMemoryRanges, "const VkMappedMemoryRange*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkInvalidateMappedMemoryRanges(
    const ApiCallInfo&                          call_info,
    args::InvalidateMappedMemoryRanges&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkInvalidateMappedMemoryRanges");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memoryRangeCount", "uint32_t", args.memoryRangeCount);
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRanges", &args.pMemoryRanges, "const VkMappedMemoryRange*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetDeviceMemoryCommitment(
    const ApiCallInfo&                          call_info,
    args::GetDeviceMemoryCommitment&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceMemoryCommitment");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);
    FieldToSqlite(statements, fieldInfo, 3, "pCommittedMemoryInBytes", args.pCommittedMemoryInBytes, "VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkBindBufferMemory(
    const ApiCallInfo&                          call_info,
    args::BindBufferMemory&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindBufferMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "memory", "VkDeviceMemory", args.memory);
    RecordField(
        statements, fieldInfo, 4, "memoryOffset", "VkDeviceSize", args.memoryOffset);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkBindImageMemory(
    const ApiCallInfo&                          call_info,
    args::BindImageMemory&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindImageMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    RecordField(
        statements, fieldInfo, 3, "memory", "VkDeviceMemory", args.memory);
    RecordField(
        statements, fieldInfo, 4, "memoryOffset", "VkDeviceSize", args.memoryOffset);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetBufferMemoryRequirements&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetImageMemoryRequirements&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetImageSparseMemoryRequirements&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSparseMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pSparseMemoryRequirementCount", args.pSparseMemoryRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSparseMemoryRequirements", &args.pSparseMemoryRequirements, "VkSparseImageMemoryRequirements*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSparseImageFormatProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSparseImageFormatProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    RecordField(
        statements, fieldInfo, 3, "type", "VkImageType", args.type);
    RecordField(
        statements, fieldInfo, 4, "samples", "VkSampleCountFlagBits", args.samples);
    RecordField(
        statements, fieldInfo, 5, "usage", "VkImageUsageFlags", args.usage);
    RecordField(
        statements, fieldInfo, 6, "tiling", "VkImageTiling", args.tiling);
    FieldToSqlite(statements, fieldInfo, 7, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 8, "pProperties", &args.pProperties, "VkSparseImageFormatProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkQueueBindSparse(
    const ApiCallInfo&                          call_info,
    args::QueueBindSparse&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueBindSparse");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfo", &args.pBindInfo, "const VkBindSparseInfo*");
    RecordField(
        statements, fieldInfo, 4, "fence", "VkFence", args.fence);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateFence(
    const ApiCallInfo&                          call_info,
    args::CreateFence&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateFence");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkFenceCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pFence", &args.pFence, "VkFence*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyFence(
    const ApiCallInfo&                          call_info,
    args::DestroyFence&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyFence");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "fence", "VkFence", args.fence);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkResetFences(
    const ApiCallInfo&                          call_info,
    args::ResetFences&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetFences");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "fenceCount", "uint32_t", args.fenceCount);
    FieldToSqlite(statements, fieldInfo, 3, "pFences", &args.pFences, "const VkFence*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetFenceStatus(
    const ApiCallInfo&                          call_info,
    args::GetFenceStatus&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetFenceStatus");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "fence", "VkFence", args.fence);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkWaitForFences(
    const ApiCallInfo&                          call_info,
    args::WaitForFences&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWaitForFences");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "fenceCount", "uint32_t", args.fenceCount);
    FieldToSqlite(statements, fieldInfo, 3, "pFences", &args.pFences, "const VkFence*");
    RecordField(
        statements, fieldInfo, 4, "waitAll", "VkBool32", args.waitAll);
    RecordField(
        statements, fieldInfo, 5, "timeout", "uint64_t", args.timeout);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkCreateSemaphore(
    const ApiCallInfo&                          call_info,
    args::CreateSemaphore&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSemaphore");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkSemaphoreCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSemaphore", &args.pSemaphore, "VkSemaphore*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroySemaphore(
    const ApiCallInfo&                          call_info,
    args::DestroySemaphore&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySemaphore");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "semaphore", "VkSemaphore", args.semaphore);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateQueryPool(
    const ApiCallInfo&                          call_info,
    args::CreateQueryPool&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateQueryPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkQueryPoolCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pQueryPool", &args.pQueryPool, "VkQueryPool*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyQueryPool(
    const ApiCallInfo&                          call_info,
    args::DestroyQueryPool&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyQueryPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetQueryPoolResults(
    const ApiCallInfo&                          call_info,
    args::GetQueryPoolResults&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetQueryPoolResults");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");
    RecordField(
        statements, fieldInfo, 7, "stride", "VkDeviceSize", args.stride);
    RecordField(
        statements, fieldInfo, 8, "flags", "VkQueryResultFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateBuffer(
    const ApiCallInfo&                          call_info,
    args::CreateBuffer&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkBufferCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pBuffer", &args.pBuffer, "VkBuffer*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyBuffer(
    const ApiCallInfo&                          call_info,
    args::DestroyBuffer&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateImage(
    const ApiCallInfo&                          call_info,
    args::CreateImage&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkImageCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pImage", &args.pImage, "VkImage*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyImage(
    const ApiCallInfo&                          call_info,
    args::DestroyImage&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    args::GetImageSubresourceLayout&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSubresourceLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pSubresource", &args.pSubresource, "const VkImageSubresource*");
    FieldToSqlite(statements, fieldInfo, 4, "pLayout", &args.pLayout, "VkSubresourceLayout*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateImageView(
    const ApiCallInfo&                          call_info,
    args::CreateImageView&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateImageView");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkImageViewCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pView", &args.pView, "VkImageView*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyImageView(
    const ApiCallInfo&                          call_info,
    args::DestroyImageView&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyImageView");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "imageView", "VkImageView", args.imageView);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateCommandPool(
    const ApiCallInfo&                          call_info,
    args::CreateCommandPool&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateCommandPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkCommandPoolCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pCommandPool", &args.pCommandPool, "VkCommandPool*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    auto [commandPoolValid, commandPool] = GetHandle(&args.pCommandPool);
    if (!commandPoolValid)
    {
        if (args.result == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create command pool, invalid pCommandPool");
        }
        return;
    }

    auto [createInfoValid, createInfo] = GetMetaStructPointer(&args.pCreateInfo);
    if (!createInfoValid)
    {
        if (args.result == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to create command pool, invalid pCreateInfo");
        }
        return;
    }

    LogUnsupportedPNext(createInfo->pNext);

    auto flags = createInfo->decoded_value->flags;
    auto queueFamilyIndex = createInfo->decoded_value->queueFamilyIndex;
    statements.InsertCommandPool(this->block_index_, commandPool, args.device, flags, queueFamilyIndex);
}

void VulkanSqliteConsumer::Process_vkDestroyCommandPool(
    const ApiCallInfo&                          call_info,
    args::DestroyCommandPool&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyCommandPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "commandPool", "VkCommandPool", args.commandPool);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    auto commandPoolIter = context.commandPoolHandleToId.find(ToInt64(args.commandPool));
    if (commandPoolIter == context.commandPoolHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to destroy command pool, failed to find command pool for handle %" PRIi64, args.commandPool);
        return;
    }
    auto commandPoolCommandBufferHandlesIter = context.commandPoolHandleToCommandBufferHandles.find(ToInt64(args.commandPool));
    if (commandPoolCommandBufferHandlesIter != context.commandPoolHandleToCommandBufferHandles.end())
    {
        for (auto commandBufferHandle : commandPoolCommandBufferHandlesIter->second)
        {
            auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
            if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end())
            {
                statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
            }
            auto commandBufferId = context.GetCommandBufferId(commandBufferHandle);
            if (commandBufferId.has_value())
            {
                statements.DestroyObject(statements.freeCommandBufferUpdateStatement, this->block_index_, commandBufferId.value());
            }
            context.commandBufferHandleToId.erase(commandBufferHandle);
            context.commandBufferHandleToLevel.erase(commandBufferHandle);
            context.commandBufferHandleToDeviceId.erase(commandBufferHandle);
        }
    }
    statements.DestroyObject(statements.destroyCommandPoolUpdateStatement, this->block_index_, commandPoolIter->second);
    context.commandPoolHandleToId.erase(commandPoolIter);
}

void VulkanSqliteConsumer::Process_vkResetCommandPool(
    const ApiCallInfo&                          call_info,
    args::ResetCommandPool&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetCommandPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "commandPool", "VkCommandPool", args.commandPool);
    RecordField(
        statements, fieldInfo, 3, "flags", "VkCommandPoolResetFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    auto commandPoolIter = context.commandPoolHandleToId.find(ToInt64(args.commandPool));
    if (commandPoolIter == context.commandPoolHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to reset command buffers associated with command pool, failed to find command pool for handle %" PRIi64, args.commandPool);
        return;
    }
    auto commandPoolCommandBufferHandlesIter = context.commandPoolHandleToCommandBufferHandles.find(ToInt64(args.commandPool));
    if (commandPoolCommandBufferHandlesIter != context.commandPoolHandleToCommandBufferHandles.end())
    {
        for (auto commandBufferHandle : commandPoolCommandBufferHandlesIter->second)
        {
            auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
            if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end())
            {
                statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
                context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
            }
        }
    }
}

void VulkanSqliteConsumer::Process_vkAllocateCommandBuffers(
    const ApiCallInfo&                          call_info,
    args::AllocateCommandBuffers&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAllocateCommandBuffers");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocateInfo", &args.pAllocateInfo, "const VkCommandBufferAllocateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pCommandBuffers", &args.pCommandBuffers, "VkCommandBuffer*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
    if (!commandBuffersValid)
    {
        if (args.result == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to allocate command buffers, invalid pCommandBuffers");
        }
        return;
    }

    auto [allocateInfoValid, allocateInfo] = GetMetaStructPointer(&args.pAllocateInfo);
    if (!allocateInfoValid)
    {
        if (args.result == VK_SUCCESS)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to allocate command buffers, invalid pAllocateInfo");
        }
        return;
    }

    LogUnsupportedPNext(allocateInfo->pNext);

    auto commandPool = allocateInfo->commandPool;
    auto level = allocateInfo->decoded_value->level;

    for (size_t i = 0; i < commandBuffersCount; ++i)
    {
        statements.InsertCommandBuffer(this->block_index_, commandBuffers[i], args.device, commandPool, level);
    }
}

void VulkanSqliteConsumer::Process_vkFreeCommandBuffers(
    const ApiCallInfo&                          call_info,
    args::FreeCommandBuffers&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkFreeCommandBuffers");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "commandPool", "VkCommandPool", args.commandPool);
    RecordField(
        statements, fieldInfo, 3, "commandBufferCount", "uint32_t", args.commandBufferCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCommandBuffers", &args.pCommandBuffers, "const VkCommandBuffer*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
    if (!commandBuffersValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to free command buffers, invalid pCommandBuffers");
        return;
    }

    auto commandPoolCommandBuffersIter = context.commandPoolHandleToCommandBufferHandles.find(ToInt64(args.commandPool));

    for (size_t i = 0; i < commandBuffersCount; ++i)
    {
        auto commandBuffer = commandBuffers[i];
        auto commandBufferHandle = ToInt64(commandBuffer);
        // ensure we "reset" the command buffer if it was not reset automatically
        // don't report an error if the recording is not found as it may have been previously reset
        auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
        if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end()) {
            statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
            context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
        }

        auto commandBufferIter = context.commandBufferHandleToId.find(commandBufferHandle);
        if (commandBufferIter == context.commandBufferHandleToId.end()) {
            if (commandBuffer != format::kNullHandleId)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to free command buffer, no active command buffer found for handle %" PRIi64,
                    commandBuffer
                );
            }
            continue;
        }

        statements.DestroyObject(statements.freeCommandBufferUpdateStatement, this->block_index_, commandBufferIter->second);

        // cleanup context tracking
        if (commandPoolCommandBuffersIter != context.commandPoolHandleToCommandBufferHandles.end())
        {
            auto& commandPoolCommandBuffers = commandPoolCommandBuffersIter->second;
            std::erase(commandPoolCommandBuffers, commandBufferHandle);
        }
        context.commandBufferHandleToId.erase(commandBufferIter);
        context.commandBufferHandleToLevel.erase(commandBufferHandle);
        context.commandBufferHandleToDeviceId.erase(commandBufferHandle);
    }
}

void VulkanSqliteConsumer::Process_vkBeginCommandBuffer(
    const ApiCallInfo&                          call_info,
    args::BeginCommandBuffer&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBeginCommandBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBeginInfo", &args.pBeginInfo, "const VkCommandBufferBeginInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pBeginInfo);
    if (!beginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create command buffer recording, invalid pBeginInfo");
        return;
    }

    LogUnsupportedPNext(beginInfo->pNext);

    std::optional<int64_t> inheritanceId = std::nullopt;
    auto [inheritanceInfoValid, inheritanceInfo] = GetMetaStructPointer(beginInfo->pInheritanceInfo);
    if (inheritanceInfoValid)
    {
        LogUnsupportedPNext(inheritanceInfo->pNext);

        auto renderPassId = context.GetRenderPassId(inheritanceInfo->renderPass, true);
        auto framebufferId = context.GetFramebufferId(inheritanceInfo->framebuffer, true);
        auto queryFlags = inheritanceInfo->decoded_value->queryFlags;
        auto pipelineStats = inheritanceInfo->decoded_value->pipelineStatistics;
        auto occlusionQueryEnable = inheritanceInfo->decoded_value->occlusionQueryEnable;
        auto subpass = inheritanceInfo->decoded_value->subpass;
        inheritanceId = statements.InsertCommandBufferInheritanceInfo(renderPassId, subpass, framebufferId, occlusionQueryEnable, queryFlags, pipelineStats);
    }

    auto commandBufferHandle = ToInt64(args.commandBuffer);
    auto commandBufferIter = context.commandBufferHandleToId.find(commandBufferHandle);
    if (commandBufferIter == context.commandBufferHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer for handle %" PRIi64 ", setting foreign key to NULL", args.commandBuffer
        );
        return;
    }

    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(commandBufferHandle);
    if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end())
    {
        statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
        context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
    }
    auto commandBufferRecordingId = statements.InsertCommandBufferRecording(this->block_index_, commandBufferIter->second, beginInfo->decoded_value->flags, inheritanceId);

    context.commandBufferHandleToRecordingId[commandBufferHandle] = commandBufferRecordingId;
    context.commandBufferHandleToRenderPassRecordingIdStack[commandBufferHandle] = {};
    context.commandBufferHandleToDynamicRenderPassRecordingIdStack[commandBufferHandle] = {};


    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkEndCommandBuffer(
    const ApiCallInfo&                          call_info,
    args::EndCommandBuffer&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEndCommandBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end command buffer recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.EndCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);

    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto pipelineBindingIter = context.commandBufferRecordingPipelineBindings.find(commandBufferRecordingIter->second);
    if (pipelineBindingIter != context.commandBufferRecordingPipelineBindings.end()) {
        pipelineBindingIter->second.clear();
        context.commandBufferRecordingPipelineBindings.erase(pipelineBindingIter);
    }
    auto vertexBindingIter = context.commandBufferRecordingVertexBindings.find(commandBufferRecordingIter->second);
    if (vertexBindingIter != context.commandBufferRecordingVertexBindings.end()) {
        vertexBindingIter->second.clear();
        context.commandBufferRecordingVertexBindings.erase(vertexBindingIter);
    }
    context.commandBufferRecordingIndexBindings.erase(commandBufferRecordingIter->second);
}

void VulkanSqliteConsumer::Process_vkResetCommandBuffer(
    const ApiCallInfo&                          call_info,
    args::ResetCommandBuffer&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetCommandBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "flags", "VkCommandBufferResetFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    // don't report an error if the recording is not found as it may have been previously reset
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter != context.commandBufferHandleToRecordingId.end()) {
        statements.ResetCommandBufferRecording(this->block_index_, commandBufferRecordingIter->second);
        context.commandBufferHandleToRecordingId.erase(commandBufferRecordingIter);
    }
}

void VulkanSqliteConsumer::Process_vkCmdCopyBuffer(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBuffer&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcBuffer", "VkBuffer", args.srcBuffer);
    RecordField(
        statements, fieldInfo, 3, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 4, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 5, "pRegions", &args.pRegions, "const VkBufferCopy*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImage(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImage&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcImage", "VkImage", args.srcImage);
    RecordField(
        statements, fieldInfo, 3, "srcImageLayout", "VkImageLayout", args.srcImageLayout);
    RecordField(
        statements, fieldInfo, 4, "dstImage", "VkImage", args.dstImage);
    RecordField(
        statements, fieldInfo, 5, "dstImageLayout", "VkImageLayout", args.dstImageLayout);
    RecordField(
        statements, fieldInfo, 6, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 7, "pRegions", &args.pRegions, "const VkImageCopy*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBufferToImage&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBufferToImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcBuffer", "VkBuffer", args.srcBuffer);
    RecordField(
        statements, fieldInfo, 3, "dstImage", "VkImage", args.dstImage);
    RecordField(
        statements, fieldInfo, 4, "dstImageLayout", "VkImageLayout", args.dstImageLayout);
    RecordField(
        statements, fieldInfo, 5, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 6, "pRegions", &args.pRegions, "const VkBufferImageCopy*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImageToBuffer&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImageToBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcImage", "VkImage", args.srcImage);
    RecordField(
        statements, fieldInfo, 3, "srcImageLayout", "VkImageLayout", args.srcImageLayout);
    RecordField(
        statements, fieldInfo, 4, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 5, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 6, "pRegions", &args.pRegions, "const VkBufferImageCopy*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdUpdateBuffer(
    const ApiCallInfo&                          call_info,
    args::CmdUpdateBuffer&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdUpdateBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 3, "dstOffset", "VkDeviceSize", args.dstOffset);
    RecordField(
        statements, fieldInfo, 4, "dataSize", "VkDeviceSize", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdFillBuffer(
    const ApiCallInfo&                          call_info,
    args::CmdFillBuffer&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdFillBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 3, "dstOffset", "VkDeviceSize", args.dstOffset);
    RecordField(
        statements, fieldInfo, 4, "size", "VkDeviceSize", args.size);
    RecordField(
        statements, fieldInfo, 5, "data", "uint32_t", args.data);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPipelineBarrier(
    const ApiCallInfo&                          call_info,
    args::CmdPipelineBarrier&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPipelineBarrier");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcStageMask", "VkPipelineStageFlags", args.srcStageMask);
    RecordField(
        statements, fieldInfo, 3, "dstStageMask", "VkPipelineStageFlags", args.dstStageMask);
    RecordField(
        statements, fieldInfo, 4, "dependencyFlags", "VkDependencyFlags", args.dependencyFlags);
    RecordField(
        statements, fieldInfo, 5, "memoryBarrierCount", "uint32_t", args.memoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 6, "pMemoryBarriers", &args.pMemoryBarriers, "const VkMemoryBarrier*");
    RecordField(
        statements, fieldInfo, 7, "bufferMemoryBarrierCount", "uint32_t", args.bufferMemoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 8, "pBufferMemoryBarriers", &args.pBufferMemoryBarriers, "const VkBufferMemoryBarrier*");
    RecordField(
        statements, fieldInfo, 9, "imageMemoryBarrierCount", "uint32_t", args.imageMemoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 10, "pImageMemoryBarriers", &args.pImageMemoryBarriers, "const VkImageMemoryBarrier*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginQuery(
    const ApiCallInfo&                          call_info,
    args::CmdBeginQuery&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginQuery");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "query", "uint32_t", args.query);
    RecordField(
        statements, fieldInfo, 4, "flags", "VkQueryControlFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndQuery(
    const ApiCallInfo&                          call_info,
    args::CmdEndQuery&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndQuery");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "query", "uint32_t", args.query);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResetQueryPool(
    const ApiCallInfo&                          call_info,
    args::CmdResetQueryPool&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResetQueryPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWriteTimestamp(
    const ApiCallInfo&                          call_info,
    args::CmdWriteTimestamp&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteTimestamp");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineStage", "VkPipelineStageFlagBits", args.pipelineStage);
    RecordField(
        statements, fieldInfo, 3, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 4, "query", "uint32_t", args.query);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyQueryPoolResults(
    const ApiCallInfo&                          call_info,
    args::CmdCopyQueryPoolResults&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyQueryPoolResults");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);
    RecordField(
        statements, fieldInfo, 5, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 6, "dstOffset", "VkDeviceSize", args.dstOffset);
    RecordField(
        statements, fieldInfo, 7, "stride", "VkDeviceSize", args.stride);
    RecordField(
        statements, fieldInfo, 8, "flags", "VkQueryResultFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdExecuteCommands(
    const ApiCallInfo&                          call_info,
    args::CmdExecuteCommands&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdExecuteCommands");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "commandBufferCount", "uint32_t", args.commandBufferCount);
    FieldToSqlite(statements, fieldInfo, 3, "pCommandBuffers", &args.pCommandBuffers, "const VkCommandBuffer*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [commandBuffersValid, commandBuffers, commandBuffersCount] = GetHandleArray(&args.pCommandBuffers);
    if (!commandBuffersValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to insert secondary command buffer execution, invalid pCommandBuffers");
        return;
    }

    auto parentCommandBufferHandle = ToInt64(args.commandBuffer);
    auto parentCommandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(parentCommandBufferHandle);
    if (parentCommandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert secondary command buffer, failed to find command buffer recording for parent command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }

    std::optional<uint64_t> renderPassRecordingId = std::nullopt;
    std::optional<uint64_t> renderSubpassRecordingId = std::nullopt;

    auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(parentCommandBufferHandle);
    if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end() &&
        !commandBufferRenderPassStackIter->second.empty())
    {
        renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
        auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
        if (renderSubpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                "setting foreign key to NULL",
                renderPassRecordingId.value()
            );
        }
        else
        {
            renderSubpassRecordingId = renderSubpassRecordingIter->second;
        }
    }

    std::optional<uint64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(parentCommandBufferHandle);
    if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end() &&
        !commandBufferDynamicRenderPassStackIter->second.empty())
    {
        dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
    }

    for (size_t i = 0; i < commandBuffersCount; ++i)
    {
        auto secondaryCommandBuffer = commandBuffers[i];
        std::string secondaryCommandBufferRecordingIdStr = "NULL";
        auto secondaryCommandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(secondaryCommandBuffer));
        if (secondaryCommandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to insert secondary command buffer execution, failed to find secondary command buffer recording for command buffer with handle %" PRIi64,
                secondaryCommandBuffer
            );
            continue;
        }

        statements.InsertSecondaryCommandBufferExecutionRecording(
            this->block_index_,
            parentCommandBufferRecordingIter->second,
            secondaryCommandBufferRecordingIter->second,
            renderPassRecordingId,
            renderSubpassRecordingId,
            dynamicRenderPassRecordingId,
            i
        );
    }
}

void VulkanSqliteConsumer::Process_vkCreateEvent(
    const ApiCallInfo&                          call_info,
    args::CreateEvent&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkEventCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pEvent", &args.pEvent, "VkEvent*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyEvent(
    const ApiCallInfo&                          call_info,
    args::DestroyEvent&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetEventStatus(
    const ApiCallInfo&                          call_info,
    args::GetEventStatus&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetEventStatus");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkSetEvent(
    const ApiCallInfo&                          call_info,
    args::SetEvent&                             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkResetEvent(
    const ApiCallInfo&                          call_info,
    args::ResetEvent&                           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateBufferView(
    const ApiCallInfo&                          call_info,
    args::CreateBufferView&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateBufferView");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkBufferViewCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pView", &args.pView, "VkBufferView*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyBufferView(
    const ApiCallInfo&                          call_info,
    args::DestroyBufferView&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyBufferView");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bufferView", "VkBufferView", args.bufferView);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateShaderModule(
    const ApiCallInfo&                          call_info,
    args::CreateShaderModule&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateShaderModule");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkShaderModuleCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pShaderModule", &args.pShaderModule, "VkShaderModule*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyShaderModule(
    const ApiCallInfo&                          call_info,
    args::DestroyShaderModule&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyShaderModule");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "shaderModule", "VkShaderModule", args.shaderModule);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreatePipelineCache(
    const ApiCallInfo&                          call_info,
    args::CreatePipelineCache&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreatePipelineCache");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkPipelineCacheCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pPipelineCache", &args.pPipelineCache, "VkPipelineCache*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPipelineCache(
    const ApiCallInfo&                          call_info,
    args::DestroyPipelineCache&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPipelineCache");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPipelineCacheData(
    const ApiCallInfo&                          call_info,
    args::GetPipelineCacheData&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineCacheData");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    FieldToSqlite(statements, fieldInfo, 3, "pDataSize", args.pDataSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkMergePipelineCaches(
    const ApiCallInfo&                          call_info,
    args::MergePipelineCaches&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkMergePipelineCaches");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "dstCache", "VkPipelineCache", args.dstCache);
    RecordField(
        statements, fieldInfo, 3, "srcCacheCount", "uint32_t", args.srcCacheCount);
    FieldToSqlite(statements, fieldInfo, 4, "pSrcCaches", &args.pSrcCaches, "const VkPipelineCache*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateComputePipelines(
    const ApiCallInfo&                          call_info,
    args::CreateComputePipelines&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateComputePipelines");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    RecordField(
        statements, fieldInfo, 3, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCreateInfos", &args.pCreateInfos, "const VkComputePipelineCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 5, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 6, "pPipelines", &args.pPipelines, "VkPipeline*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPipeline(
    const ApiCallInfo&                          call_info,
    args::DestroyPipeline&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPipeline");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreatePipelineLayout(
    const ApiCallInfo&                          call_info,
    args::CreatePipelineLayout&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreatePipelineLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkPipelineLayoutCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pPipelineLayout", &args.pPipelineLayout, "VkPipelineLayout*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPipelineLayout(
    const ApiCallInfo&                          call_info,
    args::DestroyPipelineLayout&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPipelineLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineLayout", "VkPipelineLayout", args.pipelineLayout);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateSampler(
    const ApiCallInfo&                          call_info,
    args::CreateSampler&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSampler");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkSamplerCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSampler", &args.pSampler, "VkSampler*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroySampler(
    const ApiCallInfo&                          call_info,
    args::DestroySampler&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySampler");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "sampler", "VkSampler", args.sampler);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    args::CreateDescriptorSetLayout&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDescriptorSetLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorSetLayoutCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSetLayout", &args.pSetLayout, "VkDescriptorSetLayout*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDescriptorSetLayout(
    const ApiCallInfo&                          call_info,
    args::DestroyDescriptorSetLayout&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDescriptorSetLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorSetLayout", "VkDescriptorSetLayout", args.descriptorSetLayout);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateDescriptorPool(
    const ApiCallInfo&                          call_info,
    args::CreateDescriptorPool&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDescriptorPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorPoolCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pDescriptorPool", &args.pDescriptorPool, "VkDescriptorPool*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDescriptorPool(
    const ApiCallInfo&                          call_info,
    args::DestroyDescriptorPool&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDescriptorPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorPool", "VkDescriptorPool", args.descriptorPool);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkResetDescriptorPool(
    const ApiCallInfo&                          call_info,
    args::ResetDescriptorPool&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetDescriptorPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorPool", "VkDescriptorPool", args.descriptorPool);
    RecordField(
        statements, fieldInfo, 3, "flags", "VkDescriptorPoolResetFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkAllocateDescriptorSets(
    const ApiCallInfo&                          call_info,
    args::AllocateDescriptorSets&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAllocateDescriptorSets");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocateInfo", &args.pAllocateInfo, "const VkDescriptorSetAllocateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pDescriptorSets", &args.pDescriptorSets, "VkDescriptorSet*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkFreeDescriptorSets(
    const ApiCallInfo&                          call_info,
    args::FreeDescriptorSets&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkFreeDescriptorSets");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorPool", "VkDescriptorPool", args.descriptorPool);
    RecordField(
        statements, fieldInfo, 3, "descriptorSetCount", "uint32_t", args.descriptorSetCount);
    FieldToSqlite(statements, fieldInfo, 4, "pDescriptorSets", &args.pDescriptorSets, "const VkDescriptorSet*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkUpdateDescriptorSets(
    const ApiCallInfo&                          call_info,
    args::UpdateDescriptorSets&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUpdateDescriptorSets");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorWriteCount", "uint32_t", args.descriptorWriteCount);
    FieldToSqlite(statements, fieldInfo, 3, "pDescriptorWrites", &args.pDescriptorWrites, "const VkWriteDescriptorSet*");
    RecordField(
        statements, fieldInfo, 4, "descriptorCopyCount", "uint32_t", args.descriptorCopyCount);
    FieldToSqlite(statements, fieldInfo, 5, "pDescriptorCopies", &args.pDescriptorCopies, "const VkCopyDescriptorSet*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBindPipeline(
    const ApiCallInfo&                          call_info,
    args::CmdBindPipeline&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindPipeline");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "pipeline", "VkPipeline", args.pipeline);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind pipeline, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    auto pipelineIter = context.pipelineHandleToId.find(ToInt64(args.pipeline));
    if (pipelineIter == context.pipelineHandleToId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind pipeline, failed to find pipeline for handle %" PRIi64,
            args.pipeline
        );
        return;
    }

    std::unordered_set<VkShaderStageFlagBits> stagesToClear;
    switch(args.pipelineBindPoint)
    {
        case VK_PIPELINE_BIND_POINT_GRAPHICS:
            {
                stagesToClear.insert(VK_SHADER_STAGE_VERTEX_BIT);
                stagesToClear.insert(VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT);
                stagesToClear.insert(VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT);
                stagesToClear.insert(VK_SHADER_STAGE_GEOMETRY_BIT);
                stagesToClear.insert(VK_SHADER_STAGE_FRAGMENT_BIT);
                stagesToClear.insert(VK_SHADER_STAGE_TASK_BIT_EXT);
                stagesToClear.insert(VK_SHADER_STAGE_MESH_BIT_EXT);
                stagesToClear.insert(VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI);
                break;
            }
        case VK_PIPELINE_BIND_POINT_COMPUTE:
        case VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX:
            {
                stagesToClear.insert(VK_SHADER_STAGE_COMPUTE_BIT);
                break;
            }
        case VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR:
            {
                stagesToClear.insert(VK_SHADER_STAGE_ANY_HIT_BIT_KHR);
                stagesToClear.insert(VK_SHADER_STAGE_CALLABLE_BIT_KHR);
                stagesToClear.insert(VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR);
                stagesToClear.insert(VK_SHADER_STAGE_INTERSECTION_BIT_KHR);
                stagesToClear.insert(VK_SHADER_STAGE_MISS_BIT_KHR);
                stagesToClear.insert(VK_SHADER_STAGE_RAYGEN_BIT_KHR);
                break;
            }
        case VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI:
            {
                stagesToClear.insert(VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI);
                break;
            }
        case VK_PIPELINE_BIND_POINT_MAX_ENUM:
            // do nothing
        default:
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to clear shader stages on pipeline binding, unsupported bind point %" PRIu64,
                args.pipelineBindPoint
            );
    }

    // binding pipelines will reset any previous shader object binding so clear that now
    auto shaderBindingsIter = context.commandBufferRecordingShaderObjectBindings.find(commandBufferRecordingIter->second);
    if (shaderBindingsIter != context.commandBufferRecordingShaderObjectBindings.end())
    {
        for (auto stage : stagesToClear)
        {
            shaderBindingsIter->second.erase(stage);
        }
        if (shaderBindingsIter->second.empty())
        {
            context.commandBufferRecordingShaderObjectBindings.erase(shaderBindingsIter);
        }
    }

    statements.InsertStatePipelineBinding(this->block_index_, commandBufferRecordingIter->second, pipelineIter->second, args.pipelineBindPoint);
}

void VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets(
    const ApiCallInfo&                          call_info,
    args::CmdBindDescriptorSets&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindDescriptorSets");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "layout", "VkPipelineLayout", args.layout);
    RecordField(
        statements, fieldInfo, 4, "firstSet", "uint32_t", args.firstSet);
    RecordField(
        statements, fieldInfo, 5, "descriptorSetCount", "uint32_t", args.descriptorSetCount);
    FieldToSqlite(statements, fieldInfo, 6, "pDescriptorSets", &args.pDescriptorSets, "const VkDescriptorSet*");
    RecordField(
        statements, fieldInfo, 7, "dynamicOffsetCount", "uint32_t", args.dynamicOffsetCount);
    FieldToSqlite(statements, fieldInfo, 8, "pDynamicOffsets", args.pDynamicOffsets, "const uint32_t*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdClearColorImage(
    const ApiCallInfo&                          call_info,
    args::CmdClearColorImage&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdClearColorImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    RecordField(
        statements, fieldInfo, 3, "imageLayout", "VkImageLayout", args.imageLayout);
    FieldToSqlite(statements, fieldInfo, 4, "pColor", &args.pColor, "const VkClearColorValue*");
    RecordField(
        statements, fieldInfo, 5, "rangeCount", "uint32_t", args.rangeCount);
    FieldToSqlite(statements, fieldInfo, 6, "pRanges", &args.pRanges, "const VkImageSubresourceRange*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDispatch(
    const ApiCallInfo&                          call_info,
    args::CmdDispatch&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatch");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "groupCountX", "uint32_t", args.groupCountX);
    RecordField(
        statements, fieldInfo, 3, "groupCountY", "uint32_t", args.groupCountY);
    RecordField(
        statements, fieldInfo, 4, "groupCountZ", "uint32_t", args.groupCountZ);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd dispatch recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    auto cmdDispatchRecordingId = statements.InsertCmdDispatchRecording(this->block_index_, commandBufferRecordingIter->second);
    statements.InsertCmdDispatchRecordingInfo(cmdDispatchRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
}

void VulkanSqliteConsumer::Process_vkCmdDispatchIndirect(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchIndirect&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchIndirect");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd dispatch recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    auto cmdDispatchRecordingId = statements.InsertCmdDispatchRecording(this->block_index_, commandBufferRecordingIter->second);
    statements.InsertCmdDispatchRecordingIndirectInfo(cmdDispatchRecordingId, context.GetBufferId(args.buffer), args.offset);
}

void VulkanSqliteConsumer::Process_vkCmdSetEvent(
    const ApiCallInfo&                          call_info,
    args::CmdSetEvent&                          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    RecordField(
        statements, fieldInfo, 3, "stageMask", "VkPipelineStageFlags", args.stageMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResetEvent(
    const ApiCallInfo&                          call_info,
    args::CmdResetEvent&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResetEvent");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    RecordField(
        statements, fieldInfo, 3, "stageMask", "VkPipelineStageFlags", args.stageMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWaitEvents(
    const ApiCallInfo&                          call_info,
    args::CmdWaitEvents&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWaitEvents");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "eventCount", "uint32_t", args.eventCount);
    FieldToSqlite(statements, fieldInfo, 3, "pEvents", &args.pEvents, "const VkEvent*");
    RecordField(
        statements, fieldInfo, 4, "srcStageMask", "VkPipelineStageFlags", args.srcStageMask);
    RecordField(
        statements, fieldInfo, 5, "dstStageMask", "VkPipelineStageFlags", args.dstStageMask);
    RecordField(
        statements, fieldInfo, 6, "memoryBarrierCount", "uint32_t", args.memoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 7, "pMemoryBarriers", &args.pMemoryBarriers, "const VkMemoryBarrier*");
    RecordField(
        statements, fieldInfo, 8, "bufferMemoryBarrierCount", "uint32_t", args.bufferMemoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 9, "pBufferMemoryBarriers", &args.pBufferMemoryBarriers, "const VkBufferMemoryBarrier*");
    RecordField(
        statements, fieldInfo, 10, "imageMemoryBarrierCount", "uint32_t", args.imageMemoryBarrierCount);
    FieldToSqlite(statements, fieldInfo, 11, "pImageMemoryBarriers", &args.pImageMemoryBarriers, "const VkImageMemoryBarrier*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushConstants(
    const ApiCallInfo&                          call_info,
    args::CmdPushConstants&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushConstants");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "layout", "VkPipelineLayout", args.layout);
    RecordField(
        statements, fieldInfo, 3, "stageFlags", "VkShaderStageFlags", args.stageFlags);
    RecordField(
        statements, fieldInfo, 4, "offset", "uint32_t", args.offset);
    RecordField(
        statements, fieldInfo, 5, "size", "uint32_t", args.size);
    FieldToSqlite(statements, fieldInfo, 6, "pValues", args.pValues, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCreateGraphicsPipelines(
    const ApiCallInfo&                          call_info,
    args::CreateGraphicsPipelines&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateGraphicsPipelines");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    RecordField(
        statements, fieldInfo, 3, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCreateInfos", &args.pCreateInfos, "const VkGraphicsPipelineCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 5, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 6, "pPipelines", &args.pPipelines, "VkPipeline*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateFramebuffer(
    const ApiCallInfo&                          call_info,
    args::CreateFramebuffer&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateFramebuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkFramebufferCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pFramebuffer", &args.pFramebuffer, "VkFramebuffer*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyFramebuffer(
    const ApiCallInfo&                          call_info,
    args::DestroyFramebuffer&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyFramebuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "framebuffer", "VkFramebuffer", args.framebuffer);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateRenderPass(
    const ApiCallInfo&                          call_info,
    args::CreateRenderPass&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateRenderPass");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkRenderPassCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pRenderPass", &args.pRenderPass, "VkRenderPass*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyRenderPass(
    const ApiCallInfo&                          call_info,
    args::DestroyRenderPass&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyRenderPass");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "renderPass", "VkRenderPass", args.renderPass);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetRenderAreaGranularity(
    const ApiCallInfo&                          call_info,
    args::GetRenderAreaGranularity&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRenderAreaGranularity");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "renderPass", "VkRenderPass", args.renderPass);
    FieldToSqlite(statements, fieldInfo, 3, "pGranularity", &args.pGranularity, "VkExtent2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetViewport(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewport&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewport");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstViewport", "uint32_t", args.firstViewport);
    RecordField(
        statements, fieldInfo, 3, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 4, "pViewports", &args.pViewports, "const VkViewport*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetScissor(
    const ApiCallInfo&                          call_info,
    args::CmdSetScissor&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetScissor");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstScissor", "uint32_t", args.firstScissor);
    RecordField(
        statements, fieldInfo, 3, "scissorCount", "uint32_t", args.scissorCount);
    FieldToSqlite(statements, fieldInfo, 4, "pScissors", &args.pScissors, "const VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLineWidth(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineWidth&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineWidth");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "lineWidth", "float", args.lineWidth);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBias(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBias&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBias");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthBiasConstantFactor", "float", args.depthBiasConstantFactor);
    RecordField(
        statements, fieldInfo, 3, "depthBiasClamp", "float", args.depthBiasClamp);
    RecordField(
        statements, fieldInfo, 4, "depthBiasSlopeFactor", "float", args.depthBiasSlopeFactor);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetBlendConstants(
    const ApiCallInfo&                          call_info,
    args::CmdSetBlendConstants&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetBlendConstants");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "blendConstants", args.blendConstants, "const float");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBounds(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBounds&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBounds");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "minDepthBounds", "float", args.minDepthBounds);
    RecordField(
        statements, fieldInfo, 3, "maxDepthBounds", "float", args.maxDepthBounds);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilCompareMask(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilCompareMask&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilCompareMask");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "faceMask", "VkStencilFaceFlags", args.faceMask);
    RecordField(
        statements, fieldInfo, 3, "compareMask", "uint32_t", args.compareMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilWriteMask(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilWriteMask&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilWriteMask");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "faceMask", "VkStencilFaceFlags", args.faceMask);
    RecordField(
        statements, fieldInfo, 3, "writeMask", "uint32_t", args.writeMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilReference(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilReference&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilReference");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "faceMask", "VkStencilFaceFlags", args.faceMask);
    RecordField(
        statements, fieldInfo, 3, "reference", "uint32_t", args.reference);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindIndexBuffer(
    const ApiCallInfo&                          call_info,
    args::CmdBindIndexBuffer&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindIndexBuffer");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "indexType", "VkIndexType", args.indexType);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    bool nullDescriptorEnabled = false;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
    }

    std::optional<int64_t> bufferId = std::nullopt;
    if (args.buffer != format::kNullHandleId || !nullDescriptorEnabled)
    {
        auto bufferIter = context.bufferHandleToId.find(ToInt64(args.buffer));
        if (bufferIter == context.bufferHandleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to bind index buffer, failed to find buffer with handle %" PRIi64,
                args.commandBuffer
            );
            return;
        }
        else
        {
            bufferId = bufferIter->second;
        }
    }
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind index buffer, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<uint64_t> size = std::nullopt;
    statements.InsertStateIndexBufferBinding(this->block_index_, commandBufferRecordingIter->second, bufferId, args.offset, args.indexType, size);
}

void VulkanSqliteConsumer::Process_vkCmdBindVertexBuffers(
    const ApiCallInfo&                          call_info,
    args::CmdBindVertexBuffers&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindVertexBuffers");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBuffers", &args.pBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pOffsets", args.pOffsets, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [buffersValid, buffers, buffersCount] = GetHandleArray(&args.pBuffers);
    if (!buffersValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pBuffers");
        return;
    }

    auto [offsetsValid, offsets, offsetsCount] = GetPointerArray(&args.pOffsets);
    if (!offsetsValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pOffsets");
        return;
    }
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind vertex buffers, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (buffersCount != offsetsCount) {
        GFXRECON_SQLITE_LOG_WARNING("pBuffer and pOffset counts do not match, using min");
    }
    for (size_t i = 0; i < std::min(buffersCount, offsetsCount); ++i)
    {
        std::optional<uint64_t> size = std::nullopt;
        std::optional<uint64_t> stride = std::nullopt;
        bool nullDescriptorEnabled = false;
        auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
        if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
        {
            nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
        }

        auto buffer = buffers[i];
        std::optional<int64_t> bufferId = std::nullopt;
        if (buffer != format::kNullHandleId || !nullDescriptorEnabled)
        {
            auto bufferIter = context.bufferHandleToId.find(ToInt64(buffer));
            if (bufferIter == context.bufferHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to bind vertex buffer, failed to find buffer with handle %" PRIi64,
                    buffer
                );
                continue;
            }
            else
            {
                bufferId = bufferIter->second;
            }
        }
        auto offset = offsets[i];
        auto binding = args.firstBinding + static_cast<uint32_t>(i);

        statements.InsertStateVertexBufferBinding(this->block_index_, commandBufferRecordingIter->second, binding, bufferId, offset, size, stride);
    }
}

void VulkanSqliteConsumer::Process_vkCmdDraw(
    const ApiCallInfo&                          call_info,
    args::CmdDraw&                              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDraw");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "vertexCount", "uint32_t", args.vertexCount);
    RecordField(
        statements, fieldInfo, 3, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 4, "firstVertex", "uint32_t", args.firstVertex);
    RecordField(
        statements, fieldInfo, 5, "firstInstance", "uint32_t", args.firstInstance);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    statements.InsertCmdDrawRecordingInfo(cmdDrawRecordingId, args.vertexCount, args.firstVertex, std::nullopt, std::nullopt, std::nullopt, args.instanceCount, args.firstInstance);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexed(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexed&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexed");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "indexCount", "uint32_t", args.indexCount);
    RecordField(
        statements, fieldInfo, 3, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 4, "firstIndex", "uint32_t", args.firstIndex);
    RecordField(
        statements, fieldInfo, 5, "vertexOffset", "int32_t", args.vertexOffset);
    RecordField(
        statements, fieldInfo, 6, "firstInstance", "uint32_t", args.firstInstance);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
    statements.InsertCmdDrawRecordingInfo(cmdDrawRecordingId, std::nullopt, std::nullopt, args.vertexOffset, args.indexCount, args.firstIndex, args.instanceCount, args.firstInstance);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirect(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirect&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirect");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "drawCount", "uint32_t", args.drawCount);
    RecordField(
        statements, fieldInfo, 5, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectDrawCount = args.drawCount;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirect(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirect&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirect");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "drawCount", "uint32_t", args.drawCount);
    RecordField(
        statements, fieldInfo, 5, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectDrawCount = args.drawCount;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCmdBlitImage(
    const ApiCallInfo&                          call_info,
    args::CmdBlitImage&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBlitImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcImage", "VkImage", args.srcImage);
    RecordField(
        statements, fieldInfo, 3, "srcImageLayout", "VkImageLayout", args.srcImageLayout);
    RecordField(
        statements, fieldInfo, 4, "dstImage", "VkImage", args.dstImage);
    RecordField(
        statements, fieldInfo, 5, "dstImageLayout", "VkImageLayout", args.dstImageLayout);
    RecordField(
        statements, fieldInfo, 6, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 7, "pRegions", &args.pRegions, "const VkImageBlit*");
    RecordField(
        statements, fieldInfo, 8, "filter", "VkFilter", args.filter);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdClearDepthStencilImage(
    const ApiCallInfo&                          call_info,
    args::CmdClearDepthStencilImage&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdClearDepthStencilImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    RecordField(
        statements, fieldInfo, 3, "imageLayout", "VkImageLayout", args.imageLayout);
    FieldToSqlite(statements, fieldInfo, 4, "pDepthStencil", &args.pDepthStencil, "const VkClearDepthStencilValue*");
    RecordField(
        statements, fieldInfo, 5, "rangeCount", "uint32_t", args.rangeCount);
    FieldToSqlite(statements, fieldInfo, 6, "pRanges", &args.pRanges, "const VkImageSubresourceRange*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdClearAttachments(
    const ApiCallInfo&                          call_info,
    args::CmdClearAttachments&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdClearAttachments");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 3, "pAttachments", &args.pAttachments, "const VkClearAttachment*");
    RecordField(
        statements, fieldInfo, 4, "rectCount", "uint32_t", args.rectCount);
    FieldToSqlite(statements, fieldInfo, 5, "pRects", &args.pRects, "const VkClearRect*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResolveImage(
    const ApiCallInfo&                          call_info,
    args::CmdResolveImage&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResolveImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "srcImage", "VkImage", args.srcImage);
    RecordField(
        statements, fieldInfo, 3, "srcImageLayout", "VkImageLayout", args.srcImageLayout);
    RecordField(
        statements, fieldInfo, 4, "dstImage", "VkImage", args.dstImage);
    RecordField(
        statements, fieldInfo, 5, "dstImageLayout", "VkImageLayout", args.dstImageLayout);
    RecordField(
        statements, fieldInfo, 6, "regionCount", "uint32_t", args.regionCount);
    FieldToSqlite(statements, fieldInfo, 7, "pRegions", &args.pRegions, "const VkImageResolve*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginRenderPass(
    const ApiCallInfo&                          call_info,
    args::CmdBeginRenderPass&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginRenderPass");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderPassBegin", &args.pRenderPassBegin, "const VkRenderPassBeginInfo*");
    RecordField(
        statements, fieldInfo, 3, "contents", "VkSubpassContents", args.contents);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pRenderPassBegin);
    if (!beginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass recording, invalid pBeginInfo");
        return;
    }

    const Decoded_VkRenderPassAttachmentBeginInfo* attachmentBeginInfo = nullptr;

    auto pnext = beginInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkRenderPassAttachmentBeginInfo>())
        {
            attachmentBeginInfo = reinterpret_cast<const Decoded_VkRenderPassAttachmentBeginInfo*>(header);
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    std::optional<int64_t> renderPassId = context.GetRenderPassId(beginInfo->renderPass, true);
    std::optional<int64_t> framebufferId = context.GetFramebufferId(beginInfo->framebuffer);
    auto renderOffset = beginInfo->renderArea->offset->decoded_value;
    auto renderExtent = beginInfo->renderArea->extent->decoded_value;
    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

    uint64_t passIndex = 0;
    if (commandBufferRecordingId.has_value())
    {
        auto passIndexIter = context.commandBufferRecordingIdToRenderPassIndex.find(commandBufferRecordingId.value());
        if (passIndexIter == context.commandBufferRecordingIdToRenderPassIndex.end())
        {
            context.commandBufferRecordingIdToRenderPassIndex[commandBufferRecordingId.value()] = 0;
        }
        else
        {
            passIndexIter->second++;
            passIndex = passIndexIter->second;
        }
    }

    auto renderPassRecordingId = statements.InsertRenderPassRecording(this->block_index_, renderPassId, passIndex,
                                                         commandBufferRecordingId, framebufferId,
                                                         renderOffset->x, renderOffset->y, renderExtent->width,
                                                         renderExtent->height );

    context.commandBufferHandleToRenderPassRecordingIdStack[args.commandBuffer].push(renderPassRecordingId);

    auto [clearValuesValid, clearValues, clearValuesCount] = GetMetaStructArray(beginInfo->pClearValues);
    if (clearValuesValid)
    {
        for (size_t i = 0; i < clearValuesCount; ++i) {
            const auto& clearValue = clearValues[i];
            const auto& clearDS = clearValue.decoded_value->depthStencil;

            auto clearColorId = statements.InsertUnionColor(clearValue.decoded_value->color);

            statements.InsertRenderPassRecordingClearValues(renderPassRecordingId, i, clearColorId, clearDS.depth, clearDS.stencil);

        }
    }

    if (attachmentBeginInfo != nullptr)
    {
        auto [attachmentsValid, attachments, attachmentsCount] = GetHandleArray(&attachmentBeginInfo->pAttachments);
        if (attachmentsValid)
        {
            for (size_t i = 0; i < attachmentsCount; ++i) {
                auto imageViewId = context.GetImageViewId(attachments[i]);
                if (imageViewId.has_value())
                {
                    statements.InsertRenderPassRecordingAttachment(renderPassRecordingId, i, imageViewId.value());
                }
            }
        }
    }

    // insert implicit first subpass
    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, args.contents);
}

void VulkanSqliteConsumer::Process_vkCmdNextSubpass(
    const ApiCallInfo&                          call_info,
    args::CmdNextSubpass&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdNextSubpass");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "contents", "VkSubpassContents", args.contents);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            "failed to find render pass recording stack for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            " render subpass recording stack for command buffer with handle %" PRIi64 " is empty, "
            "expecting a render pass recording for next render pass event",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingStackIter->second.top();
    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass, failed to find subpass pass recording for render pass recording %" PRIu64,
            renderPassRecordingStackIter->second.top()
        );
        // this is an error for the previous subpass, but we want to continue so we can add the next subpass
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);
    }

    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, args.contents);
}

void VulkanSqliteConsumer::Process_vkCmdEndRenderPass(
    const ApiCallInfo&                          call_info,
    args::CmdEndRenderPass&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRenderPass");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingIdStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingIdStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, failed to find render pass recording stack for command buffer %" PRIu64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, render pass recording stack for command buffer %" PRIu64 " is empty, "
            "expected prior render pass begin",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingIdStackIter->second.top();
    statements.EndRenderPassRecording(this->block_index_, renderPassRecordingId);

    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render subpass recording, render pass recording stack for render pass %" PRIu64 " is empty, "
            "expected implicit first subpass",
            renderPassRecordingId
        );
        // This is an error for the subpass but not for render pass, we need to continue to finish ending the render pass recording
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);

        context.renderPassRecordingIdToRenderSubpassRecordingId.erase(subpassRecordingIter);
    }

    auto subpassIndexRemoved = context.renderPassRecordingIdToSubpassIndex.erase(renderPassRecordingId);
    if (!subpassIndexRemoved)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render subpass index for render pass recording %" PRIu64 ", expected implicit first subpass",
            renderPassRecordingId
        );
    }

    renderPassRecordingIdStackIter->second.pop();
    if (!renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end render pass api event",
            args.commandBuffer
        );
    }
    else
    {
        context.commandBufferHandleToRenderPassRecordingIdStack.erase(renderPassRecordingIdStackIter);
    }
}
void VulkanSqliteConsumer::Process_vkBindBufferMemory2(
    const ApiCallInfo&                          call_info,
    args::BindBufferMemory2&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindBufferMemory2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindBufferMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkBindImageMemory2(
    const ApiCallInfo&                          call_info,
    args::BindImageMemory2&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindImageMemory2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindImageMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetDeviceGroupPeerMemoryFeatures(
    const ApiCallInfo&                          call_info,
    args::GetDeviceGroupPeerMemoryFeatures&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceGroupPeerMemoryFeatures");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "heapIndex", "uint32_t", args.heapIndex);
    RecordField(
        statements, fieldInfo, 3, "localDeviceIndex", "uint32_t", args.localDeviceIndex);
    RecordField(
        statements, fieldInfo, 4, "remoteDeviceIndex", "uint32_t", args.remoteDeviceIndex);
    FieldToSqlite(statements, fieldInfo, 5, "pPeerMemoryFeatures", args.pPeerMemoryFeatures, "VkPeerMemoryFeatureFlags*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetDeviceMask(
    const ApiCallInfo&                          call_info,
    args::CmdSetDeviceMask&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDeviceMask");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "deviceMask", "uint32_t", args.deviceMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkEnumeratePhysicalDeviceGroups(
    const ApiCallInfo&                          call_info,
    args::EnumeratePhysicalDeviceGroups&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEnumeratePhysicalDeviceGroups");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pPhysicalDeviceGroupCount", args.pPhysicalDeviceGroupCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pPhysicalDeviceGroupProperties", &args.pPhysicalDeviceGroupProperties, "VkPhysicalDeviceGroupProperties*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetImageMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    args::GetImageMemoryRequirements2&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageMemoryRequirements2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetBufferMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    args::GetBufferMemoryRequirements2&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferMemoryRequirements2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSparseMemoryRequirements2(
    const ApiCallInfo&                          call_info,
    args::GetImageSparseMemoryRequirements2&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSparseMemoryRequirements2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageSparseMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pSparseMemoryRequirementCount", args.pSparseMemoryRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSparseMemoryRequirements", &args.pSparseMemoryRequirements, "VkSparseImageMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFeatures2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFeatures2&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFeatures2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFeatures", &args.pFeatures, "VkPhysicalDeviceFeatures2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceProperties2&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pProperties", &args.pProperties, "VkPhysicalDeviceProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFormatProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFormatProperties2&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFormatProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    FieldToSqlite(statements, fieldInfo, 3, "pFormatProperties", &args.pFormatProperties, "VkFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceImageFormatProperties2& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceImageFormatProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pImageFormatInfo", &args.pImageFormatInfo, "const VkPhysicalDeviceImageFormatInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pImageFormatProperties", &args.pImageFormatProperties, "VkImageFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyProperties2& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueFamilyPropertyCount", args.pQueueFamilyPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyProperties", &args.pQueueFamilyProperties, "VkQueueFamilyProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceMemoryProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceMemoryProperties2&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceMemoryProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryProperties", &args.pMemoryProperties, "VkPhysicalDeviceMemoryProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSparseImageFormatProperties2& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSparseImageFormatProperties2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFormatInfo", &args.pFormatInfo, "const VkPhysicalDeviceSparseImageFormatInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkSparseImageFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkTrimCommandPool(
    const ApiCallInfo&                          call_info,
    args::TrimCommandPool&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkTrimCommandPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "commandPool", "VkCommandPool", args.commandPool);
    RecordField(
        statements, fieldInfo, 3, "flags", "VkCommandPoolTrimFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceQueue2(
    const ApiCallInfo&                          call_info,
    args::GetDeviceQueue2&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceQueue2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueInfo", &args.pQueueInfo, "const VkDeviceQueueInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pQueue", &args.pQueue, "VkQueue*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalBufferProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalBufferProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalBufferProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalBufferInfo", &args.pExternalBufferInfo, "const VkPhysicalDeviceExternalBufferInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalBufferProperties", &args.pExternalBufferProperties, "VkExternalBufferProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalFenceProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalFenceProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalFenceProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalFenceInfo", &args.pExternalFenceInfo, "const VkPhysicalDeviceExternalFenceInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalFenceProperties", &args.pExternalFenceProperties, "VkExternalFenceProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalSemaphoreProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalSemaphoreProperties& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalSemaphoreProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalSemaphoreInfo", &args.pExternalSemaphoreInfo, "const VkPhysicalDeviceExternalSemaphoreInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalSemaphoreProperties", &args.pExternalSemaphoreProperties, "VkExternalSemaphoreProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdDispatchBase(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchBase&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchBase");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "baseGroupX", "uint32_t", args.baseGroupX);
    RecordField(
        statements, fieldInfo, 3, "baseGroupY", "uint32_t", args.baseGroupY);
    RecordField(
        statements, fieldInfo, 4, "baseGroupZ", "uint32_t", args.baseGroupZ);
    RecordField(
        statements, fieldInfo, 5, "groupCountX", "uint32_t", args.groupCountX);
    RecordField(
        statements, fieldInfo, 6, "groupCountY", "uint32_t", args.groupCountY);
    RecordField(
        statements, fieldInfo, 7, "groupCountZ", "uint32_t", args.groupCountZ);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd dispatch recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    auto cmdDispatchRecordingId = statements.InsertCmdDispatchRecording(this->block_index_, commandBufferRecordingIter->second);
    statements.InsertCmdDispatchRecordingBaseInfo(cmdDispatchRecordingId, args.baseGroupX, args.baseGroupY, args.baseGroupZ);
    statements.InsertCmdDispatchRecordingInfo(cmdDispatchRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
}

void VulkanSqliteConsumer::Process_vkCreateDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    args::CreateDescriptorUpdateTemplate&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDescriptorUpdateTemplate");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorUpdateTemplateCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pDescriptorUpdateTemplate", &args.pDescriptorUpdateTemplate, "VkDescriptorUpdateTemplate*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDescriptorUpdateTemplate(
    const ApiCallInfo&                          call_info,
    args::DestroyDescriptorUpdateTemplate&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDescriptorUpdateTemplate");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", args.descriptorUpdateTemplate);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDescriptorSetLayoutSupport(
    const ApiCallInfo&                          call_info,
    args::GetDescriptorSetLayoutSupport&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDescriptorSetLayoutSupport");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorSetLayoutCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSupport", &args.pSupport, "VkDescriptorSetLayoutSupport*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateSamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    args::CreateSamplerYcbcrConversion&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSamplerYcbcrConversion");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkSamplerYcbcrConversionCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pYcbcrConversion", &args.pYcbcrConversion, "VkSamplerYcbcrConversion*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroySamplerYcbcrConversion(
    const ApiCallInfo&                          call_info,
    args::DestroySamplerYcbcrConversion&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySamplerYcbcrConversion");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "ycbcrConversion", "VkSamplerYcbcrConversion", args.ycbcrConversion);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkResetQueryPool(
    const ApiCallInfo&                          call_info,
    args::ResetQueryPool&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetQueryPool");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetSemaphoreCounterValue(
    const ApiCallInfo&                          call_info,
    args::GetSemaphoreCounterValue&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSemaphoreCounterValue");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "semaphore", "VkSemaphore", args.semaphore);
    FieldToSqlite(statements, fieldInfo, 3, "pValue", args.pValue, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkWaitSemaphores(
    const ApiCallInfo&                          call_info,
    args::WaitSemaphores&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWaitSemaphores");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pWaitInfo", &args.pWaitInfo, "const VkSemaphoreWaitInfo*");
    RecordField(
        statements, fieldInfo, 3, "timeout", "uint64_t", args.timeout);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkSignalSemaphore(
    const ApiCallInfo&                          call_info,
    args::SignalSemaphore&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSignalSemaphore");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pSignalInfo", &args.pSignalInfo, "const VkSemaphoreSignalInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetBufferDeviceAddress(
    const ApiCallInfo&                          call_info,
    args::GetBufferDeviceAddress&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferDeviceAddress");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferDeviceAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceAddress", args.result);
}

void VulkanSqliteConsumer::Process_vkGetBufferOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    args::GetBufferOpaqueCaptureAddress&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferOpaqueCaptureAddress");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferDeviceAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddress(
    const ApiCallInfo&                          call_info,
    args::GetDeviceMemoryOpaqueCaptureAddress&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceMemoryOpaqueCaptureAddress");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceMemoryOpaqueCaptureAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirectCount(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectCount&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectCount");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirectCount(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirectCount&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirectCount");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCreateRenderPass2(
    const ApiCallInfo&                          call_info,
    args::CreateRenderPass2&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateRenderPass2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkRenderPassCreateInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pRenderPass", &args.pRenderPass, "VkRenderPass*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdBeginRenderPass2(
    const ApiCallInfo&                          call_info,
    args::CmdBeginRenderPass2&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginRenderPass2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderPassBegin", &args.pRenderPassBegin, "const VkRenderPassBeginInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSubpassBeginInfo", &args.pSubpassBeginInfo, "const VkSubpassBeginInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pRenderPassBegin);
    if (!beginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass recording, invalid pBeginInfo");
        return;
    }

    const Decoded_VkRenderPassAttachmentBeginInfo* attachmentBeginInfo = nullptr;

    auto pnext = beginInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkRenderPassAttachmentBeginInfo>())
        {
            attachmentBeginInfo = reinterpret_cast<const Decoded_VkRenderPassAttachmentBeginInfo*>(header);
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    std::optional<int64_t> renderPassId = context.GetRenderPassId(beginInfo->renderPass, true);
    std::optional<int64_t> framebufferId = context.GetFramebufferId(beginInfo->framebuffer);
    auto renderOffset = beginInfo->renderArea->offset->decoded_value;
    auto renderExtent = beginInfo->renderArea->extent->decoded_value;
    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

    uint64_t passIndex = 0;
    if (commandBufferRecordingId.has_value())
    {
        auto passIndexIter = context.commandBufferRecordingIdToRenderPassIndex.find(commandBufferRecordingId.value());
        if (passIndexIter == context.commandBufferRecordingIdToRenderPassIndex.end())
        {
            context.commandBufferRecordingIdToRenderPassIndex[commandBufferRecordingId.value()] = 0;
        }
        else
        {
            passIndexIter->second++;
            passIndex = passIndexIter->second;
        }
    }

    auto renderPassRecordingId = statements.InsertRenderPassRecording(this->block_index_, renderPassId, passIndex,
                                                         commandBufferRecordingId, framebufferId,
                                                         renderOffset->x, renderOffset->y, renderExtent->width,
                                                         renderExtent->height );

    context.commandBufferHandleToRenderPassRecordingIdStack[args.commandBuffer].push(renderPassRecordingId);

    auto [clearValuesValid, clearValues, clearValuesCount] = GetMetaStructArray(beginInfo->pClearValues);
    if (clearValuesValid)
    {
        for (size_t i = 0; i < clearValuesCount; ++i) {
            const auto& clearValue = clearValues[i];
            const auto& clearDS = clearValue.decoded_value->depthStencil;

            auto clearColorId = statements.InsertUnionColor(clearValue.decoded_value->color);

            statements.InsertRenderPassRecordingClearValues(renderPassRecordingId, i, clearColorId, clearDS.depth, clearDS.stencil);

        }
    }

    if (attachmentBeginInfo != nullptr)
    {
        auto [attachmentsValid, attachments, attachmentsCount] = GetHandleArray(&attachmentBeginInfo->pAttachments);
        if (attachmentsValid)
        {
            for (size_t i = 0; i < attachmentsCount; ++i) {
                auto imageViewId = context.GetImageViewId(attachments[i]);
                if (imageViewId.has_value())
                {
                    statements.InsertRenderPassRecordingAttachment(renderPassRecordingId, i, imageViewId.value());
                }
            }
        }
    }

    auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
    if (!subpassBeginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create render subpass recording, invalid pSubpassBeginInfo");
        return;
    }

    LogUnsupportedPNext(subpassBeginInfo->pNext);

    const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;

    // insert implicit first subpass
    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, contents);
}

void VulkanSqliteConsumer::Process_vkCmdNextSubpass2(
    const ApiCallInfo&                          call_info,
    args::CmdNextSubpass2&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdNextSubpass2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pSubpassBeginInfo", &args.pSubpassBeginInfo, "const VkSubpassBeginInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSubpassEndInfo", &args.pSubpassEndInfo, "const VkSubpassEndInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            "failed to find render pass recording stack for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            " render subpass recording stack for command buffer with handle %" PRIi64 " is empty, "
            "expecting a render pass recording for next render pass event",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingStackIter->second.top();
    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass, failed to find subpass pass recording for render pass recording %" PRIu64,
            renderPassRecordingStackIter->second.top()
        );
        // this is an error for the previous subpass, but we want to continue so we can add the next subpass
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);
    }

    auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
    if (!subpassBeginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create next subpass, invalid pSubpassBeginInfo");
        return;
    }

    LogUnsupportedPNext(subpassBeginInfo->pNext);

    auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
    if (!subpassEndInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create create next subpass, invalid pSubpassEndInfo");
        return;
    }

    LogUnsupportedPNext(subpassEndInfo->pNext);

    const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;

    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, contents);
}

void VulkanSqliteConsumer::Process_vkCmdEndRenderPass2(
    const ApiCallInfo&                          call_info,
    args::CmdEndRenderPass2&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRenderPass2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pSubpassEndInfo", &args.pSubpassEndInfo, "const VkSubpassEndInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingIdStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingIdStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, failed to find render pass recording stack for command buffer %" PRIu64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, render pass recording stack for command buffer %" PRIu64 " is empty, "
            "expected prior render pass begin",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingIdStackIter->second.top();
    statements.EndRenderPassRecording(this->block_index_, renderPassRecordingId);

    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render subpass recording, render pass recording stack for render pass %" PRIu64 " is empty, "
            "expected implicit first subpass",
            renderPassRecordingId
        );
        // This is an error for the subpass but not for render pass, we need to continue to finish ending the render pass recording
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);

        context.renderPassRecordingIdToRenderSubpassRecordingId.erase(subpassRecordingIter);
    }

    auto subpassIndexRemoved = context.renderPassRecordingIdToSubpassIndex.erase(renderPassRecordingId);
    if (!subpassIndexRemoved)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render subpass index for render pass recording %" PRIu64 ", expected implicit first subpass",
            renderPassRecordingId
        );
    }

    renderPassRecordingIdStackIter->second.pop();
    if (!renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end render pass api event",
            args.commandBuffer
        );
    }
    else
    {
        context.commandBufferHandleToRenderPassRecordingIdStack.erase(renderPassRecordingIdStackIter);
    }

    auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
    if (!subpassEndInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to process end subpass, invalid pSubpassEndInfo");
        return;
    }

    LogUnsupportedPNext(subpassEndInfo->pNext);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceToolProperties(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceToolProperties&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceToolProperties");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pToolCount", args.pToolCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pToolProperties", &args.pToolProperties, "VkPhysicalDeviceToolProperties*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreatePrivateDataSlot(
    const ApiCallInfo&                          call_info,
    args::CreatePrivateDataSlot&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreatePrivateDataSlot");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkPrivateDataSlotCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pPrivateDataSlot", &args.pPrivateDataSlot, "VkPrivateDataSlot*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPrivateDataSlot(
    const ApiCallInfo&                          call_info,
    args::DestroyPrivateDataSlot&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPrivateDataSlot");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkSetPrivateData(
    const ApiCallInfo&                          call_info,
    args::SetPrivateData&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetPrivateData");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "objectType", "VkObjectType", args.objectType);
    RecordField(
        statements, fieldInfo, 3, "objectHandle", "uint64_t", args.objectHandle);
    RecordField(
        statements, fieldInfo, 4, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    RecordField(
        statements, fieldInfo, 5, "data", "uint64_t", args.data);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPrivateData(
    const ApiCallInfo&                          call_info,
    args::GetPrivateData&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPrivateData");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "objectType", "VkObjectType", args.objectType);
    RecordField(
        statements, fieldInfo, 3, "objectHandle", "uint64_t", args.objectHandle);
    RecordField(
        statements, fieldInfo, 4, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdPipelineBarrier2(
    const ApiCallInfo&                          call_info,
    args::CmdPipelineBarrier2&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPipelineBarrier2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDependencyInfo", &args.pDependencyInfo, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWriteTimestamp2(
    const ApiCallInfo&                          call_info,
    args::CmdWriteTimestamp2&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteTimestamp2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stage", "VkPipelineStageFlags2", args.stage);
    RecordField(
        statements, fieldInfo, 3, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 4, "query", "uint32_t", args.query);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkQueueSubmit2(
    const ApiCallInfo&                          call_info,
    args::QueueSubmit2&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueSubmit2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    RecordField(
        statements, fieldInfo, 2, "submitCount", "uint32_t", args.submitCount);
    FieldToSqlite(statements, fieldInfo, 3, "pSubmits", &args.pSubmits, "const VkSubmitInfo2*");
    RecordField(
        statements, fieldInfo, 4, "fence", "VkFence", args.fence);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdCopyBuffer2(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBuffer2&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBuffer2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyBufferInfo", &args.pCopyBufferInfo, "const VkCopyBufferInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImage2(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImage2&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImage2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageInfo", &args.pCopyImageInfo, "const VkCopyImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage2(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBufferToImage2&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBufferToImage2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyBufferToImageInfo", &args.pCopyBufferToImageInfo, "const VkCopyBufferToImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer2(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImageToBuffer2&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImageToBuffer2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToBufferInfo", &args.pCopyImageToBufferInfo, "const VkCopyImageToBufferInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetDeviceBufferMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetDeviceBufferMemoryRequirements&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceBufferMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceBufferMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageMemoryRequirements&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageSparseMemoryRequirements(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageSparseMemoryRequirements& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageSparseMemoryRequirements");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pSparseMemoryRequirementCount", args.pSparseMemoryRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSparseMemoryRequirements", &args.pSparseMemoryRequirements, "VkSparseImageMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetEvent2(
    const ApiCallInfo&                          call_info,
    args::CmdSetEvent2&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetEvent2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    FieldToSqlite(statements, fieldInfo, 3, "pDependencyInfo", &args.pDependencyInfo, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResetEvent2(
    const ApiCallInfo&                          call_info,
    args::CmdResetEvent2&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResetEvent2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    RecordField(
        statements, fieldInfo, 3, "stageMask", "VkPipelineStageFlags2", args.stageMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWaitEvents2(
    const ApiCallInfo&                          call_info,
    args::CmdWaitEvents2&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWaitEvents2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "eventCount", "uint32_t", args.eventCount);
    FieldToSqlite(statements, fieldInfo, 3, "pEvents", &args.pEvents, "const VkEvent*");
    FieldToSqlite(statements, fieldInfo, 4, "pDependencyInfos", &args.pDependencyInfos, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBlitImage2(
    const ApiCallInfo&                          call_info,
    args::CmdBlitImage2&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBlitImage2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBlitImageInfo", &args.pBlitImageInfo, "const VkBlitImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResolveImage2(
    const ApiCallInfo&                          call_info,
    args::CmdResolveImage2&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResolveImage2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pResolveImageInfo", &args.pResolveImageInfo, "const VkResolveImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginRendering(
    const ApiCallInfo&                          call_info,
    args::CmdBeginRendering&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginRendering");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingInfo", &args.pRenderingInfo, "const VkRenderingInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [renderingInfoValid, renderingInfo] = GetMetaStructPointer(&args.pRenderingInfo);
    if (!renderingInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create dynamic render pass recording, invalid pRenderingInfo");
        return;
    }

    LogUnsupportedPNext(renderingInfo->pNext);

    auto flags = renderingInfo->decoded_value->flags;
    auto renderOffset = renderingInfo->renderArea->offset->decoded_value;
    auto renderExtent = renderingInfo->renderArea->extent->decoded_value;
    auto layerCount = renderingInfo->decoded_value->layerCount;
    auto viewMask = renderingInfo->decoded_value->viewMask;


    // create rendering attachments
    std::optional<int64_t> depthAttachmentId = std::nullopt;
    auto [depthAttachmentValid, depthAttachment] = GetMetaStructPointer(renderingInfo->pDepthAttachment);
    if (depthAttachmentValid)
    {
        auto imageView = context.GetImageViewId(depthAttachment->imageView, true);
        auto imageLayout = depthAttachment->decoded_value->imageLayout;
        auto resolveMode = depthAttachment->decoded_value->resolveMode;
        auto resolveImageViewId = context.GetImageViewId(depthAttachment->resolveImageView, true);
        auto resolveImageLayout = depthAttachment->decoded_value->resolveImageLayout;
        auto loadOp = depthAttachment->decoded_value->loadOp;
        auto storeOp = depthAttachment->decoded_value->storeOp;
        auto clearValue = depthAttachment->clearValue;
        auto vkClearColor = clearValue->color->decoded_value;
        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
        auto clearDepth = clearDepthStencil.depth;
        auto clearStencil = clearDepthStencil.stencil;

        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

        depthAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                      resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                      clearStencil);
    }

    std::optional<int64_t> stencilAttachmentId = std::nullopt;
    auto [stencilAttachmentValid, stencilAttachment] = GetMetaStructPointer(renderingInfo->pStencilAttachment);
    if (stencilAttachmentValid)
    {
        auto imageView = context.GetImageViewId(stencilAttachment->imageView, true);
        auto imageLayout = stencilAttachment->decoded_value->imageLayout;
        auto resolveMode = stencilAttachment->decoded_value->resolveMode;
        auto resolveImageViewId = context.GetImageViewId(stencilAttachment->resolveImageView, true);
        auto resolveImageLayout = stencilAttachment->decoded_value->resolveImageLayout;
        auto loadOp = stencilAttachment->decoded_value->loadOp;
        auto storeOp = stencilAttachment->decoded_value->storeOp;
        auto clearValue = stencilAttachment->clearValue;
        auto vkClearColor = clearValue->color->decoded_value;
        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
        auto clearDepth = clearDepthStencil.depth;
        auto clearStencil = clearDepthStencil.stencil;

        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

        stencilAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                        resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                        clearStencil);
    }

    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

    uint64_t passIndex = 0;
    if (commandBufferRecordingId.has_value())
    {
        auto passIndexIter = context.commandBufferRecordingIdToDynamicRenderPassIndex.find(commandBufferRecordingId.value());
        if (passIndexIter == context.commandBufferRecordingIdToDynamicRenderPassIndex.end())
        {
            context.commandBufferRecordingIdToDynamicRenderPassIndex[commandBufferRecordingId.value()] = 0;
        }
        else
        {
            passIndexIter->second++;
            passIndex = passIndexIter->second;
        }
    }

    auto dynamicRenderPassRecordingId = statements.InsertDynamicRenderPassRecording(this->block_index_, passIndex, commandBufferRecordingId, flags,
                                                                       renderOffset->x, renderOffset->y,
                                                                       renderExtent->width, renderExtent->height,
                                                                       layerCount, viewMask,
                                                                       depthAttachmentId, stencilAttachmentId);

    context.commandBufferHandleToDynamicRenderPassRecordingIdStack[ToInt64(args.commandBuffer)].push(dynamicRenderPassRecordingId);

    // create color rendering attachments - needs dynamicRenderPassRecordingId so must be done after
    auto [colorAttachmentsValid, colorAttachments, colorAttachmentsCount] = GetMetaStructArray(renderingInfo->pColorAttachments);
    if (colorAttachmentsValid)
    {
        for (size_t i = 0; i < colorAttachmentsCount; ++i)
        {
            auto& colorAttachment = colorAttachments[i];
            auto imageView = context.GetImageViewId(colorAttachment.imageView, true);
            auto imageLayout = colorAttachment.decoded_value->imageLayout;
            auto resolveMode = colorAttachment.decoded_value->resolveMode;
            auto resolveImageViewId = context.GetImageViewId(colorAttachment.resolveImageView, true);
            auto resolveImageLayout = colorAttachment.decoded_value->resolveImageLayout;
            auto loadOp = colorAttachment.decoded_value->loadOp;
            auto storeOp = colorAttachment.decoded_value->storeOp;
            auto clearValue = colorAttachment.clearValue;
            auto vkClearColor = clearValue->color->decoded_value;
            auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
            auto clearDepth = clearDepthStencil.depth;
            auto clearStencil = clearDepthStencil.stencil;

            auto clearColorId = statements.InsertUnionColor(*vkClearColor);

            auto colorAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                               resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                               clearStencil);

            statements.InsertDynamicColorAttachment(dynamicRenderPassRecordingId, i, colorAttachmentId);
        }
    }
}

void VulkanSqliteConsumer::Process_vkCmdEndRendering(
    const ApiCallInfo&                          call_info,
    args::CmdEndRendering&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRendering");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto dynamicRenderPassRecordingIdStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (dynamicRenderPassRecordingIdStackIter == context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, failed to find dynamic render pass recording stack for command buffer %" PRIu64,
            args.commandBuffer
        );
        return;
    }
    if (dynamicRenderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end dynamic render pass recording, dynamic render pass recording stack for command buffer %" PRIu64 " is empty, "
            "expected prior dynamic render pass begin",
            args.commandBuffer
        );
        return;
    }

    auto dynamicRenderPassRecordingId = dynamicRenderPassRecordingIdStackIter->second.top();
    statements.EndDynamicRenderPassRecording(this->block_index_, dynamicRenderPassRecordingId);

    dynamicRenderPassRecordingIdStackIter->second.pop();
    if (!dynamicRenderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup dynamic render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end dynamic render pass api event",
            args.commandBuffer
        );
    }
    else
    {
        context.commandBufferHandleToDynamicRenderPassRecordingIdStack.erase(dynamicRenderPassRecordingIdStackIter);
    }
}

void VulkanSqliteConsumer::Process_vkCmdSetCullMode(
    const ApiCallInfo&                          call_info,
    args::CmdSetCullMode&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCullMode");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "cullMode", "VkCullModeFlags", args.cullMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetFrontFace(
    const ApiCallInfo&                          call_info,
    args::CmdSetFrontFace&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetFrontFace");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "frontFace", "VkFrontFace", args.frontFace);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPrimitiveTopology(
    const ApiCallInfo&                          call_info,
    args::CmdSetPrimitiveTopology&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPrimitiveTopology");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "primitiveTopology", "VkPrimitiveTopology", args.primitiveTopology);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetViewportWithCount(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportWithCount&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportWithCount");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 3, "pViewports", &args.pViewports, "const VkViewport*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetScissorWithCount(
    const ApiCallInfo&                          call_info,
    args::CmdSetScissorWithCount&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetScissorWithCount");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "scissorCount", "uint32_t", args.scissorCount);
    FieldToSqlite(statements, fieldInfo, 3, "pScissors", &args.pScissors, "const VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindVertexBuffers2(
    const ApiCallInfo&                          call_info,
    args::CmdBindVertexBuffers2&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindVertexBuffers2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBuffers", &args.pBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pOffsets", args.pOffsets, "const VkDeviceSize*");
    FieldToSqlite(statements, fieldInfo, 6, "pSizes", args.pSizes, "const VkDeviceSize*");
    FieldToSqlite(statements, fieldInfo, 7, "pStrides", args.pStrides, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [buffersValid, buffers, buffersCount] = GetHandleArray(&args.pBuffers);
    if (!buffersValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pBuffers");
        return;
    }

    auto [offsetsValid, offsets, offsetsCount] = GetPointerArray(&args.pOffsets);
    if (!offsetsValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pOffsets");
        return;
    }
    auto [sizesValid, sizes, sizesCount] = GetPointerArray(&args.pSizes);
    auto [stridesValid, strides, stridesCount] = GetPointerArray(&args.pStrides);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind vertex buffers, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (buffersCount != offsetsCount) {
        GFXRECON_SQLITE_LOG_WARNING("pBuffer and pOffset counts do not match, using min");
    }
    for (size_t i = 0; i < std::min(buffersCount, offsetsCount); ++i)
    {
        std::optional<uint64_t> size = std::nullopt;
        std::optional<uint64_t> stride = std::nullopt;
        if (sizesValid)
        {
            size = sizes[i];
        }
        if (stridesValid)
        {
            stride = strides[i];
        }
        bool nullDescriptorEnabled = false;
        auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
        if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
        {
            nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
        }

        auto buffer = buffers[i];
        std::optional<int64_t> bufferId = std::nullopt;
        if (buffer != format::kNullHandleId || !nullDescriptorEnabled)
        {
            auto bufferIter = context.bufferHandleToId.find(ToInt64(buffer));
            if (bufferIter == context.bufferHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to bind vertex buffer, failed to find buffer with handle %" PRIi64,
                    buffer
                );
                continue;
            }
            else
            {
                bufferId = bufferIter->second;
            }
        }
        auto offset = offsets[i];
        auto binding = args.firstBinding + static_cast<uint32_t>(i);

        statements.InsertStateVertexBufferBinding(this->block_index_, commandBufferRecordingIter->second, binding, bufferId, offset, size, stride);
    }
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthTestEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthTestEnable&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthTestEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthTestEnable", "VkBool32", args.depthTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthWriteEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthWriteEnable&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthWriteEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthWriteEnable", "VkBool32", args.depthWriteEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthCompareOp(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthCompareOp&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthCompareOp");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthCompareOp", "VkCompareOp", args.depthCompareOp);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBoundsTestEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBoundsTestEnable&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBoundsTestEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthBoundsTestEnable", "VkBool32", args.depthBoundsTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilTestEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilTestEnable&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilTestEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stencilTestEnable", "VkBool32", args.stencilTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilOp(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilOp&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilOp");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "faceMask", "VkStencilFaceFlags", args.faceMask);
    RecordField(
        statements, fieldInfo, 3, "failOp", "VkStencilOp", args.failOp);
    RecordField(
        statements, fieldInfo, 4, "passOp", "VkStencilOp", args.passOp);
    RecordField(
        statements, fieldInfo, 5, "depthFailOp", "VkStencilOp", args.depthFailOp);
    RecordField(
        statements, fieldInfo, 6, "compareOp", "VkCompareOp", args.compareOp);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRasterizerDiscardEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetRasterizerDiscardEnable&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRasterizerDiscardEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "rasterizerDiscardEnable", "VkBool32", args.rasterizerDiscardEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBiasEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBiasEnable&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBiasEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthBiasEnable", "VkBool32", args.depthBiasEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPrimitiveRestartEnable(
    const ApiCallInfo&                          call_info,
    args::CmdSetPrimitiveRestartEnable&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPrimitiveRestartEnable");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "primitiveRestartEnable", "VkBool32", args.primitiveRestartEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkMapMemory2(
    const ApiCallInfo&                          call_info,
    args::MapMemory2&                           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkMapMemory2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryMapInfo", &args.pMemoryMapInfo, "const VkMemoryMapInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "ppData", args.ppData, "void**");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkUnmapMemory2(
    const ApiCallInfo&                          call_info,
    args::UnmapMemory2&                         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUnmapMemory2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryUnmapInfo", &args.pMemoryUnmapInfo, "const VkMemoryUnmapInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageSubresourceLayout(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageSubresourceLayout&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageSubresourceLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageSubresourceInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pLayout", &args.pLayout, "VkSubresourceLayout2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSubresourceLayout2(
    const ApiCallInfo&                          call_info,
    args::GetImageSubresourceLayout2&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSubresourceLayout2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pSubresource", &args.pSubresource, "const VkImageSubresource2*");
    FieldToSqlite(statements, fieldInfo, 4, "pLayout", &args.pLayout, "VkSubresourceLayout2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCopyMemoryToImage(
    const ApiCallInfo&                          call_info,
    args::CopyMemoryToImage&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMemoryToImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryToImageInfo", &args.pCopyMemoryToImageInfo, "const VkCopyMemoryToImageInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyImageToMemory(
    const ApiCallInfo&                          call_info,
    args::CopyImageToMemory&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyImageToMemory");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToMemoryInfo", &args.pCopyImageToMemoryInfo, "const VkCopyImageToMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyImageToImage(
    const ApiCallInfo&                          call_info,
    args::CopyImageToImage&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyImageToImage");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToImageInfo", &args.pCopyImageToImageInfo, "const VkCopyImageToImageInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkTransitionImageLayout(
    const ApiCallInfo&                          call_info,
    args::TransitionImageLayout&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkTransitionImageLayout");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "transitionCount", "uint32_t", args.transitionCount);
    FieldToSqlite(statements, fieldInfo, 3, "pTransitions", &args.pTransitions, "const VkHostImageLayoutTransitionInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSet&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSet");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "layout", "VkPipelineLayout", args.layout);
    RecordField(
        statements, fieldInfo, 4, "set", "uint32_t", args.set);
    RecordField(
        statements, fieldInfo, 5, "descriptorWriteCount", "uint32_t", args.descriptorWriteCount);
    FieldToSqlite(statements, fieldInfo, 6, "pDescriptorWrites", &args.pDescriptorWrites, "const VkWriteDescriptorSet*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets2(
    const ApiCallInfo&                          call_info,
    args::CmdBindDescriptorSets2&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindDescriptorSets2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBindDescriptorSetsInfo", &args.pBindDescriptorSetsInfo, "const VkBindDescriptorSetsInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushConstants2(
    const ApiCallInfo&                          call_info,
    args::CmdPushConstants2&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushConstants2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushConstantsInfo", &args.pPushConstantsInfo, "const VkPushConstantsInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet2(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSet2&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSet2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushDescriptorSetInfo", &args.pPushDescriptorSetInfo, "const VkPushDescriptorSetInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplate2(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSetWithTemplate2&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSetWithTemplate2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushDescriptorSetWithTemplateInfo", &args.pPushDescriptorSetWithTemplateInfo, "const VkPushDescriptorSetWithTemplateInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLineStipple(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineStipple&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineStipple");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "lineStippleFactor", "uint32_t", args.lineStippleFactor);
    RecordField(
        statements, fieldInfo, 3, "lineStipplePattern", "uint16_t", args.lineStipplePattern);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindIndexBuffer2(
    const ApiCallInfo&                          call_info,
    args::CmdBindIndexBuffer2&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindIndexBuffer2");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "size", "VkDeviceSize", args.size);
    RecordField(
        statements, fieldInfo, 5, "indexType", "VkIndexType", args.indexType);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    bool nullDescriptorEnabled = false;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
    }

    std::optional<int64_t> bufferId = std::nullopt;
    if (args.buffer != format::kNullHandleId || !nullDescriptorEnabled)
    {
        auto bufferIter = context.bufferHandleToId.find(ToInt64(args.buffer));
        if (bufferIter == context.bufferHandleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to bind index buffer, failed to find buffer with handle %" PRIi64,
                args.commandBuffer
            );
            return;
        }
        else
        {
            bufferId = bufferIter->second;
        }
    }
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind index buffer, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertStateIndexBufferBinding(this->block_index_, commandBufferRecordingIter->second, bufferId, args.offset, args.indexType, args.size);
}

void VulkanSqliteConsumer::Process_vkGetRenderingAreaGranularity(
    const ApiCallInfo&                          call_info,
    args::GetRenderingAreaGranularity&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRenderingAreaGranularity");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingAreaInfo", &args.pRenderingAreaInfo, "const VkRenderingAreaInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pGranularity", &args.pGranularity, "VkExtent2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetRenderingAttachmentLocations(
    const ApiCallInfo&                          call_info,
    args::CmdSetRenderingAttachmentLocations&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRenderingAttachmentLocations");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pLocationInfo", &args.pLocationInfo, "const VkRenderingAttachmentLocationInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRenderingInputAttachmentIndices(
    const ApiCallInfo&                          call_info,
    args::CmdSetRenderingInputAttachmentIndices& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRenderingInputAttachmentIndices");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInputAttachmentIndexInfo", &args.pInputAttachmentIndexInfo, "const VkRenderingInputAttachmentIndexInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkDestroySurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::DestroySurfaceKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    auto surfaceIter = context.surfaceHandleToId.find(ToInt64(args.surface));
    if (surfaceIter == context.surfaceHandleToId.end())
    {
        if (args.surface != format::kNullHandleId)
        {
            GFXRECON_SQLITE_LOG_WARNING("Failed to destroy surface, no surface found with handle %" PRIi64, args.surface);
        }
        return;
    }

    statements.DestroyObject(statements.destroySurfaceUpdateStatement, this->block_index_, surfaceIter->second);

    context.surfaceHandleToId.erase(surfaceIter);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceSupportKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    RecordField(
        statements, fieldInfo, 3, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 4, "pSupported", args.pSupported, "VkBool32*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceCapabilitiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pSurfaceCapabilities", &args.pSurfaceCapabilities, "VkSurfaceCapabilitiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceFormatsKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceFormatsKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceFormatsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pSurfaceFormatCount", args.pSurfaceFormatCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurfaceFormats", &args.pSurfaceFormats, "VkSurfaceFormatKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfacePresentModesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfacePresentModesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pPresentModeCount", args.pPresentModeCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pPresentModes", args.pPresentModes, "VkPresentModeKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateSwapchainKHR(
    const ApiCallInfo&                          call_info,
    args::CreateSwapchainKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSwapchainKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkSwapchainCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSwapchain", &args.pSwapchain, "VkSwapchainKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroySwapchainKHR(
    const ApiCallInfo&                          call_info,
    args::DestroySwapchainKHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySwapchainKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetSwapchainImagesKHR(
    const ApiCallInfo&                          call_info,
    args::GetSwapchainImagesKHR&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSwapchainImagesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pSwapchainImageCount", args.pSwapchainImageCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSwapchainImages", &args.pSwapchainImages, "VkImage*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkAcquireNextImageKHR(
    const ApiCallInfo&                          call_info,
    args::AcquireNextImageKHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireNextImageKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    RecordField(
        statements, fieldInfo, 3, "timeout", "uint64_t", args.timeout);
    RecordField(
        statements, fieldInfo, 4, "semaphore", "VkSemaphore", args.semaphore);
    RecordField(
        statements, fieldInfo, 5, "fence", "VkFence", args.fence);
    FieldToSqlite(statements, fieldInfo, 6, "pImageIndex", args.pImageIndex, "uint32_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkQueuePresentKHR(
    const ApiCallInfo&                          call_info,
    args::QueuePresentKHR&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueuePresentKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pPresentInfo", &args.pPresentInfo, "const VkPresentInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceGroupPresentCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceGroupPresentCapabilitiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceGroupPresentCapabilitiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pDeviceGroupPresentCapabilities", &args.pDeviceGroupPresentCapabilities, "VkDeviceGroupPresentCapabilitiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceGroupSurfacePresentModesKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceGroupSurfacePresentModesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceGroupSurfacePresentModesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pModes", args.pModes, "VkDeviceGroupPresentModeFlagsKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDevicePresentRectanglesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDevicePresentRectanglesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDevicePresentRectanglesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pRectCount", args.pRectCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pRects", &args.pRects, "VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkAcquireNextImage2KHR(
    const ApiCallInfo&                          call_info,
    args::AcquireNextImage2KHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireNextImage2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAcquireInfo", &args.pAcquireInfo, "const VkAcquireNextImageInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pImageIndex", args.pImageIndex, "uint32_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceDisplayPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceDisplayPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceDisplayPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkDisplayPropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceDisplayPlanePropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkDisplayPlanePropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDisplayPlaneSupportedDisplaysKHR(
    const ApiCallInfo&                          call_info,
    args::GetDisplayPlaneSupportedDisplaysKHR&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDisplayPlaneSupportedDisplaysKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "planeIndex", "uint32_t", args.planeIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pDisplayCount", args.pDisplayCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pDisplays", &args.pDisplays, "VkDisplayKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDisplayModePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetDisplayModePropertiesKHR&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDisplayModePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);
    FieldToSqlite(statements, fieldInfo, 3, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkDisplayModePropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateDisplayModeKHR(
    const ApiCallInfo&                          call_info,
    args::CreateDisplayModeKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDisplayModeKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);
    FieldToSqlite(statements, fieldInfo, 3, "pCreateInfo", &args.pCreateInfo, "const VkDisplayModeCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 5, "pMode", &args.pMode, "VkDisplayModeKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDisplayPlaneCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetDisplayPlaneCapabilitiesKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDisplayPlaneCapabilitiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "mode", "VkDisplayModeKHR", args.mode);
    RecordField(
        statements, fieldInfo, 3, "planeIndex", "uint32_t", args.planeIndex);
    FieldToSqlite(statements, fieldInfo, 4, "pCapabilities", &args.pCapabilities, "VkDisplayPlaneCapabilitiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateDisplayPlaneSurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateDisplayPlaneSurfaceKHR&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDisplayPlaneSurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDisplaySurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCreateSharedSwapchainsKHR(
    const ApiCallInfo&                          call_info,
    args::CreateSharedSwapchainsKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSharedSwapchainsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchainCount", "uint32_t", args.swapchainCount);
    FieldToSqlite(statements, fieldInfo, 3, "pCreateInfos", &args.pCreateInfos, "const VkSwapchainCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 5, "pSwapchains", &args.pSwapchains, "VkSwapchainKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateXlibSurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateXlibSurfaceKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateXlibSurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkXlibSurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceXlibPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceXlibPresentationSupportKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceXlibPresentationSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "dpy", args.dpy, "Display*");
    RecordField(
        statements, fieldInfo, 4, "visualID", "VisualID", args.visualID);

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateXcbSurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateXcbSurfaceKHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateXcbSurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkXcbSurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceXcbPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceXcbPresentationSupportKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceXcbPresentationSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "connection", args.connection, "xcb_connection_t*");
    RecordField(
        statements, fieldInfo, 4, "visual_id", "xcb_visualid_t", args.visual_id);

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateWaylandSurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateWaylandSurfaceKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateWaylandSurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkWaylandSurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceWaylandPresentationSupportKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceWaylandPresentationSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "display", args.display, "struct wl_display*");

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateAndroidSurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateAndroidSurfaceKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateAndroidSurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkAndroidSurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCreateWin32SurfaceKHR(
    const ApiCallInfo&                          call_info,
    args::CreateWin32SurfaceKHR&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateWin32SurfaceKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkWin32SurfaceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceWin32PresentationSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceWin32PresentationSupportKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceWin32PresentationSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceVideoCapabilitiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceVideoCapabilitiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceVideoCapabilitiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pVideoProfile", &args.pVideoProfile, "const VkVideoProfileInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pCapabilities", &args.pCapabilities, "VkVideoCapabilitiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceVideoFormatPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceVideoFormatPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceVideoFormatPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pVideoFormatInfo", &args.pVideoFormatInfo, "const VkPhysicalDeviceVideoFormatInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pVideoFormatPropertyCount", args.pVideoFormatPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pVideoFormatProperties", &args.pVideoFormatProperties, "VkVideoFormatPropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    args::CreateVideoSessionKHR&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateVideoSessionKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkVideoSessionCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pVideoSession", &args.pVideoSession, "VkVideoSessionKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyVideoSessionKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyVideoSessionKHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyVideoSessionKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "videoSession", "VkVideoSessionKHR", args.videoSession);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetVideoSessionMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    args::GetVideoSessionMemoryRequirementsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetVideoSessionMemoryRequirementsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "videoSession", "VkVideoSessionKHR", args.videoSession);
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirementsCount", args.pMemoryRequirementsCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryRequirements", &args.pMemoryRequirements, "VkVideoSessionMemoryRequirementsKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkBindVideoSessionMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::BindVideoSessionMemoryKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindVideoSessionMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "videoSession", "VkVideoSessionKHR", args.videoSession);
    RecordField(
        statements, fieldInfo, 3, "bindSessionMemoryInfoCount", "uint32_t", args.bindSessionMemoryInfoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBindSessionMemoryInfos", &args.pBindSessionMemoryInfos, "const VkBindVideoSessionMemoryInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    args::CreateVideoSessionParametersKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateVideoSessionParametersKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkVideoSessionParametersCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pVideoSessionParameters", &args.pVideoSessionParameters, "VkVideoSessionParametersKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkUpdateVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    args::UpdateVideoSessionParametersKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUpdateVideoSessionParametersKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "videoSessionParameters", "VkVideoSessionParametersKHR", args.videoSessionParameters);
    FieldToSqlite(statements, fieldInfo, 3, "pUpdateInfo", &args.pUpdateInfo, "const VkVideoSessionParametersUpdateInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyVideoSessionParametersKHR&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyVideoSessionParametersKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "videoSessionParameters", "VkVideoSessionParametersKHR", args.videoSessionParameters);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBeginVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    args::CmdBeginVideoCodingKHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginVideoCodingKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBeginInfo", &args.pBeginInfo, "const VkVideoBeginCodingInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    args::CmdEndVideoCodingKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndVideoCodingKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pEndCodingInfo", &args.pEndCodingInfo, "const VkVideoEndCodingInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdControlVideoCodingKHR(
    const ApiCallInfo&                          call_info,
    args::CmdControlVideoCodingKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdControlVideoCodingKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCodingControlInfo", &args.pCodingControlInfo, "const VkVideoCodingControlInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdDecodeVideoKHR(
    const ApiCallInfo&                          call_info,
    args::CmdDecodeVideoKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDecodeVideoKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDecodeInfo", &args.pDecodeInfo, "const VkVideoDecodeInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdBeginRenderingKHR(
    const ApiCallInfo&                          call_info,
    args::CmdBeginRenderingKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginRenderingKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingInfo", &args.pRenderingInfo, "const VkRenderingInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [renderingInfoValid, renderingInfo] = GetMetaStructPointer(&args.pRenderingInfo);
    if (!renderingInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create dynamic render pass recording, invalid pRenderingInfo");
        return;
    }

    LogUnsupportedPNext(renderingInfo->pNext);

    auto flags = renderingInfo->decoded_value->flags;
    auto renderOffset = renderingInfo->renderArea->offset->decoded_value;
    auto renderExtent = renderingInfo->renderArea->extent->decoded_value;
    auto layerCount = renderingInfo->decoded_value->layerCount;
    auto viewMask = renderingInfo->decoded_value->viewMask;


    // create rendering attachments
    std::optional<int64_t> depthAttachmentId = std::nullopt;
    auto [depthAttachmentValid, depthAttachment] = GetMetaStructPointer(renderingInfo->pDepthAttachment);
    if (depthAttachmentValid)
    {
        auto imageView = context.GetImageViewId(depthAttachment->imageView, true);
        auto imageLayout = depthAttachment->decoded_value->imageLayout;
        auto resolveMode = depthAttachment->decoded_value->resolveMode;
        auto resolveImageViewId = context.GetImageViewId(depthAttachment->resolveImageView, true);
        auto resolveImageLayout = depthAttachment->decoded_value->resolveImageLayout;
        auto loadOp = depthAttachment->decoded_value->loadOp;
        auto storeOp = depthAttachment->decoded_value->storeOp;
        auto clearValue = depthAttachment->clearValue;
        auto vkClearColor = clearValue->color->decoded_value;
        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
        auto clearDepth = clearDepthStencil.depth;
        auto clearStencil = clearDepthStencil.stencil;

        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

        depthAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                      resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                      clearStencil);
    }

    std::optional<int64_t> stencilAttachmentId = std::nullopt;
    auto [stencilAttachmentValid, stencilAttachment] = GetMetaStructPointer(renderingInfo->pStencilAttachment);
    if (stencilAttachmentValid)
    {
        auto imageView = context.GetImageViewId(stencilAttachment->imageView, true);
        auto imageLayout = stencilAttachment->decoded_value->imageLayout;
        auto resolveMode = stencilAttachment->decoded_value->resolveMode;
        auto resolveImageViewId = context.GetImageViewId(stencilAttachment->resolveImageView, true);
        auto resolveImageLayout = stencilAttachment->decoded_value->resolveImageLayout;
        auto loadOp = stencilAttachment->decoded_value->loadOp;
        auto storeOp = stencilAttachment->decoded_value->storeOp;
        auto clearValue = stencilAttachment->clearValue;
        auto vkClearColor = clearValue->color->decoded_value;
        auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
        auto clearDepth = clearDepthStencil.depth;
        auto clearStencil = clearDepthStencil.stencil;

        auto clearColorId = statements.InsertUnionColor(*vkClearColor);

        stencilAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                        resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                        clearStencil);
    }

    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

    uint64_t passIndex = 0;
    if (commandBufferRecordingId.has_value())
    {
        auto passIndexIter = context.commandBufferRecordingIdToDynamicRenderPassIndex.find(commandBufferRecordingId.value());
        if (passIndexIter == context.commandBufferRecordingIdToDynamicRenderPassIndex.end())
        {
            context.commandBufferRecordingIdToDynamicRenderPassIndex[commandBufferRecordingId.value()] = 0;
        }
        else
        {
            passIndexIter->second++;
            passIndex = passIndexIter->second;
        }
    }

    auto dynamicRenderPassRecordingId = statements.InsertDynamicRenderPassRecording(this->block_index_, passIndex, commandBufferRecordingId, flags,
                                                                       renderOffset->x, renderOffset->y,
                                                                       renderExtent->width, renderExtent->height,
                                                                       layerCount, viewMask,
                                                                       depthAttachmentId, stencilAttachmentId);

    context.commandBufferHandleToDynamicRenderPassRecordingIdStack[ToInt64(args.commandBuffer)].push(dynamicRenderPassRecordingId);

    // create color rendering attachments - needs dynamicRenderPassRecordingId so must be done after
    auto [colorAttachmentsValid, colorAttachments, colorAttachmentsCount] = GetMetaStructArray(renderingInfo->pColorAttachments);
    if (colorAttachmentsValid)
    {
        for (size_t i = 0; i < colorAttachmentsCount; ++i)
        {
            auto& colorAttachment = colorAttachments[i];
            auto imageView = context.GetImageViewId(colorAttachment.imageView, true);
            auto imageLayout = colorAttachment.decoded_value->imageLayout;
            auto resolveMode = colorAttachment.decoded_value->resolveMode;
            auto resolveImageViewId = context.GetImageViewId(colorAttachment.resolveImageView, true);
            auto resolveImageLayout = colorAttachment.decoded_value->resolveImageLayout;
            auto loadOp = colorAttachment.decoded_value->loadOp;
            auto storeOp = colorAttachment.decoded_value->storeOp;
            auto clearValue = colorAttachment.clearValue;
            auto vkClearColor = clearValue->color->decoded_value;
            auto& clearDepthStencil = clearValue->decoded_value->depthStencil;
            auto clearDepth = clearDepthStencil.depth;
            auto clearStencil = clearDepthStencil.stencil;

            auto clearColorId = statements.InsertUnionColor(*vkClearColor);

            auto colorAttachmentId = statements.InsertRenderingAttachment(imageView, imageLayout, resolveMode, resolveImageViewId,
                                                               resolveImageLayout, loadOp, storeOp, clearColorId, clearDepth,
                                                               clearStencil);

            statements.InsertDynamicColorAttachment(dynamicRenderPassRecordingId, i, colorAttachmentId);
        }
    }
}

void VulkanSqliteConsumer::Process_vkCmdEndRenderingKHR(
    const ApiCallInfo&                          call_info,
    args::CmdEndRenderingKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRenderingKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto dynamicRenderPassRecordingIdStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (dynamicRenderPassRecordingIdStackIter == context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, failed to find dynamic render pass recording stack for command buffer %" PRIu64,
            args.commandBuffer
        );
        return;
    }
    if (dynamicRenderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end dynamic render pass recording, dynamic render pass recording stack for command buffer %" PRIu64 " is empty, "
            "expected prior dynamic render pass begin",
            args.commandBuffer
        );
        return;
    }

    auto dynamicRenderPassRecordingId = dynamicRenderPassRecordingIdStackIter->second.top();
    statements.EndDynamicRenderPassRecording(this->block_index_, dynamicRenderPassRecordingId);

    dynamicRenderPassRecordingIdStackIter->second.pop();
    if (!dynamicRenderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup dynamic render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end dynamic render pass api event",
            args.commandBuffer
        );
    }
    else
    {
        context.commandBufferHandleToDynamicRenderPassRecordingIdStack.erase(dynamicRenderPassRecordingIdStackIter);
    }
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFeatures2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFeatures2KHR&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFeatures2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFeatures", &args.pFeatures, "VkPhysicalDeviceFeatures2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceProperties2KHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pProperties", &args.pProperties, "VkPhysicalDeviceProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFormatProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFormatProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    FieldToSqlite(statements, fieldInfo, 3, "pFormatProperties", &args.pFormatProperties, "VkFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceImageFormatProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceImageFormatProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pImageFormatInfo", &args.pImageFormatInfo, "const VkPhysicalDeviceImageFormatInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pImageFormatProperties", &args.pImageFormatProperties, "VkImageFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueFamilyPropertyCount", args.pQueueFamilyPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyProperties", &args.pQueueFamilyProperties, "VkQueueFamilyProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceMemoryProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceMemoryProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceMemoryProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryProperties", &args.pMemoryProperties, "VkPhysicalDeviceMemoryProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSparseImageFormatProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFormatInfo", &args.pFormatInfo, "const VkPhysicalDeviceSparseImageFormatInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkSparseImageFormatProperties2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetDeviceGroupPeerMemoryFeaturesKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceGroupPeerMemoryFeaturesKHR&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceGroupPeerMemoryFeaturesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "heapIndex", "uint32_t", args.heapIndex);
    RecordField(
        statements, fieldInfo, 3, "localDeviceIndex", "uint32_t", args.localDeviceIndex);
    RecordField(
        statements, fieldInfo, 4, "remoteDeviceIndex", "uint32_t", args.remoteDeviceIndex);
    FieldToSqlite(statements, fieldInfo, 5, "pPeerMemoryFeatures", args.pPeerMemoryFeatures, "VkPeerMemoryFeatureFlags*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetDeviceMaskKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetDeviceMaskKHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDeviceMaskKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "deviceMask", "uint32_t", args.deviceMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDispatchBaseKHR(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchBaseKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchBaseKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "baseGroupX", "uint32_t", args.baseGroupX);
    RecordField(
        statements, fieldInfo, 3, "baseGroupY", "uint32_t", args.baseGroupY);
    RecordField(
        statements, fieldInfo, 4, "baseGroupZ", "uint32_t", args.baseGroupZ);
    RecordField(
        statements, fieldInfo, 5, "groupCountX", "uint32_t", args.groupCountX);
    RecordField(
        statements, fieldInfo, 6, "groupCountY", "uint32_t", args.groupCountY);
    RecordField(
        statements, fieldInfo, 7, "groupCountZ", "uint32_t", args.groupCountZ);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd dispatch recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    auto cmdDispatchRecordingId = statements.InsertCmdDispatchRecording(this->block_index_, commandBufferRecordingIter->second);
    statements.InsertCmdDispatchRecordingBaseInfo(cmdDispatchRecordingId, args.baseGroupX, args.baseGroupY, args.baseGroupZ);
    statements.InsertCmdDispatchRecordingInfo(cmdDispatchRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
}
void VulkanSqliteConsumer::Process_vkTrimCommandPoolKHR(
    const ApiCallInfo&                          call_info,
    args::TrimCommandPoolKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkTrimCommandPoolKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "commandPool", "VkCommandPool", args.commandPool);
    RecordField(
        statements, fieldInfo, 3, "flags", "VkCommandPoolTrimFlags", args.flags);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkEnumeratePhysicalDeviceGroupsKHR(
    const ApiCallInfo&                          call_info,
    args::EnumeratePhysicalDeviceGroupsKHR&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEnumeratePhysicalDeviceGroupsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pPhysicalDeviceGroupCount", args.pPhysicalDeviceGroupCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pPhysicalDeviceGroupProperties", &args.pPhysicalDeviceGroupProperties, "VkPhysicalDeviceGroupProperties*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalBufferPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalBufferPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalBufferInfo", &args.pExternalBufferInfo, "const VkPhysicalDeviceExternalBufferInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalBufferProperties", &args.pExternalBufferProperties, "VkExternalBufferProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetMemoryWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    args::GetMemoryWin32HandleKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryWin32HandleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetWin32HandleInfo", &args.pGetWin32HandleInfo, "const VkMemoryGetWin32HandleInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pHandle", args.pHandle, "HANDLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetMemoryWin32HandlePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetMemoryWin32HandlePropertiesKHR&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryWin32HandlePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "handleType", "VkExternalMemoryHandleTypeFlagBits", args.handleType);
    FieldToSqlite(statements, fieldInfo, 3, "handle", args.handle, "HANDLE");
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryWin32HandleProperties", &args.pMemoryWin32HandleProperties, "VkMemoryWin32HandlePropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetMemoryFdKHR(
    const ApiCallInfo&                          call_info,
    args::GetMemoryFdKHR&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryFdKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetFdInfo", &args.pGetFdInfo, "const VkMemoryGetFdInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pFd", args.pFd, "int*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetMemoryFdPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetMemoryFdPropertiesKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryFdPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "handleType", "VkExternalMemoryHandleTypeFlagBits", args.handleType);
    RecordField(
        statements, fieldInfo, 3, "fd", "int", args.fd);
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryFdProperties", &args.pMemoryFdProperties, "VkMemoryFdPropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalSemaphorePropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalSemaphoreInfo", &args.pExternalSemaphoreInfo, "const VkPhysicalDeviceExternalSemaphoreInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalSemaphoreProperties", &args.pExternalSemaphoreProperties, "VkExternalSemaphoreProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkImportSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    args::ImportSemaphoreWin32HandleKHR&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkImportSemaphoreWin32HandleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pImportSemaphoreWin32HandleInfo", &args.pImportSemaphoreWin32HandleInfo, "const VkImportSemaphoreWin32HandleInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSemaphoreWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    args::GetSemaphoreWin32HandleKHR&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSemaphoreWin32HandleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetWin32HandleInfo", &args.pGetWin32HandleInfo, "const VkSemaphoreGetWin32HandleInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pHandle", args.pHandle, "HANDLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkImportSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    args::ImportSemaphoreFdKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkImportSemaphoreFdKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pImportSemaphoreFdInfo", &args.pImportSemaphoreFdInfo, "const VkImportSemaphoreFdInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSemaphoreFdKHR(
    const ApiCallInfo&                          call_info,
    args::GetSemaphoreFdKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSemaphoreFdKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetFdInfo", &args.pGetFdInfo, "const VkSemaphoreGetFdInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pFd", args.pFd, "int*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetKHR(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSetKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSetKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "layout", "VkPipelineLayout", args.layout);
    RecordField(
        statements, fieldInfo, 4, "set", "uint32_t", args.set);
    RecordField(
        statements, fieldInfo, 5, "descriptorWriteCount", "uint32_t", args.descriptorWriteCount);
    FieldToSqlite(statements, fieldInfo, 6, "pDescriptorWrites", &args.pDescriptorWrites, "const VkWriteDescriptorSet*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    args::CreateDescriptorUpdateTemplateKHR&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDescriptorUpdateTemplateKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorUpdateTemplateCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pDescriptorUpdateTemplate", &args.pDescriptorUpdateTemplate, "VkDescriptorUpdateTemplate*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDescriptorUpdateTemplateKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyDescriptorUpdateTemplateKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDescriptorUpdateTemplateKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", args.descriptorUpdateTemplate);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    args::CreateRenderPass2KHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateRenderPass2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkRenderPassCreateInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pRenderPass", &args.pRenderPass, "VkRenderPass*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdBeginRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBeginRenderPass2KHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginRenderPass2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderPassBegin", &args.pRenderPassBegin, "const VkRenderPassBeginInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSubpassBeginInfo", &args.pSubpassBeginInfo, "const VkSubpassBeginInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [beginInfoValid, beginInfo] = GetMetaStructPointer(&args.pRenderPassBegin);
    if (!beginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create render pass recording, invalid pBeginInfo");
        return;
    }

    const Decoded_VkRenderPassAttachmentBeginInfo* attachmentBeginInfo = nullptr;

    auto pnext = beginInfo->pNext;
    while (pnext != nullptr)
    {
        auto header = reinterpret_cast<const VulkanMetaStructHeader*>(pnext->GetMetaStructPointer());
        if (*header->sType == gfxrecon::util::GetSType<VkRenderPassAttachmentBeginInfo>())
        {
            attachmentBeginInfo = reinterpret_cast<const Decoded_VkRenderPassAttachmentBeginInfo*>(header);
        }
        else
        {
            LogUnsupportedPNext(*header->sType);
        }

        pnext = header->pNext;
    }

    std::optional<int64_t> renderPassId = context.GetRenderPassId(beginInfo->renderPass, true);
    std::optional<int64_t> framebufferId = context.GetFramebufferId(beginInfo->framebuffer);
    auto renderOffset = beginInfo->renderArea->offset->decoded_value;
    auto renderExtent = beginInfo->renderArea->extent->decoded_value;
    std::optional<int64_t> commandBufferRecordingId = context.GetCommandBufferRecordingId(args.commandBuffer);

    uint64_t passIndex = 0;
    if (commandBufferRecordingId.has_value())
    {
        auto passIndexIter = context.commandBufferRecordingIdToRenderPassIndex.find(commandBufferRecordingId.value());
        if (passIndexIter == context.commandBufferRecordingIdToRenderPassIndex.end())
        {
            context.commandBufferRecordingIdToRenderPassIndex[commandBufferRecordingId.value()] = 0;
        }
        else
        {
            passIndexIter->second++;
            passIndex = passIndexIter->second;
        }
    }

    auto renderPassRecordingId = statements.InsertRenderPassRecording(this->block_index_, renderPassId, passIndex,
                                                         commandBufferRecordingId, framebufferId,
                                                         renderOffset->x, renderOffset->y, renderExtent->width,
                                                         renderExtent->height );

    context.commandBufferHandleToRenderPassRecordingIdStack[args.commandBuffer].push(renderPassRecordingId);

    auto [clearValuesValid, clearValues, clearValuesCount] = GetMetaStructArray(beginInfo->pClearValues);
    if (clearValuesValid)
    {
        for (size_t i = 0; i < clearValuesCount; ++i) {
            const auto& clearValue = clearValues[i];
            const auto& clearDS = clearValue.decoded_value->depthStencil;

            auto clearColorId = statements.InsertUnionColor(clearValue.decoded_value->color);

            statements.InsertRenderPassRecordingClearValues(renderPassRecordingId, i, clearColorId, clearDS.depth, clearDS.stencil);

        }
    }

    if (attachmentBeginInfo != nullptr)
    {
        auto [attachmentsValid, attachments, attachmentsCount] = GetHandleArray(&attachmentBeginInfo->pAttachments);
        if (attachmentsValid)
        {
            for (size_t i = 0; i < attachmentsCount; ++i) {
                auto imageViewId = context.GetImageViewId(attachments[i]);
                if (imageViewId.has_value())
                {
                    statements.InsertRenderPassRecordingAttachment(renderPassRecordingId, i, imageViewId.value());
                }
            }
        }
    }

    auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
    if (!subpassBeginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create render subpass recording, invalid pSubpassBeginInfo");
        return;
    }

    LogUnsupportedPNext(subpassBeginInfo->pNext);

    const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;

    // insert implicit first subpass
    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, contents);
}

void VulkanSqliteConsumer::Process_vkCmdNextSubpass2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdNextSubpass2KHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdNextSubpass2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pSubpassBeginInfo", &args.pSubpassBeginInfo, "const VkSubpassBeginInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSubpassEndInfo", &args.pSubpassEndInfo, "const VkSubpassEndInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            "failed to find render pass recording stack for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass and create next subpass, "
            " render subpass recording stack for command buffer with handle %" PRIi64 " is empty, "
            "expecting a render pass recording for next render pass event",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingStackIter->second.top();
    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end previous subpass, failed to find subpass pass recording for render pass recording %" PRIu64,
            renderPassRecordingStackIter->second.top()
        );
        // this is an error for the previous subpass, but we want to continue so we can add the next subpass
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);
    }

    auto [subpassBeginInfoValid, subpassBeginInfo] = GetMetaStructPointer(&args.pSubpassBeginInfo);
    if (!subpassBeginInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create next subpass, invalid pSubpassBeginInfo");
        return;
    }

    LogUnsupportedPNext(subpassBeginInfo->pNext);

    auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
    if (!subpassEndInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to create create next subpass, invalid pSubpassEndInfo");
        return;
    }

    LogUnsupportedPNext(subpassEndInfo->pNext);

    const VkSubpassContents contents = subpassBeginInfo->decoded_value->contents;

    statements.InsertRenderSubpassRecording(this->block_index_, renderPassRecordingId, contents);
}

void VulkanSqliteConsumer::Process_vkCmdEndRenderPass2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdEndRenderPass2KHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRenderPass2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pSubpassEndInfo", &args.pSubpassEndInfo, "const VkSubpassEndInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto renderPassRecordingIdStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
    if (renderPassRecordingIdStackIter == context.commandBufferHandleToRenderPassRecordingIdStack.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, failed to find render pass recording stack for command buffer %" PRIu64,
            args.commandBuffer
        );
        return;
    }
    if (renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render pass recording, render pass recording stack for command buffer %" PRIu64 " is empty, "
            "expected prior render pass begin",
            args.commandBuffer
        );
        return;
    }

    auto renderPassRecordingId = renderPassRecordingIdStackIter->second.top();
    statements.EndRenderPassRecording(this->block_index_, renderPassRecordingId);

    auto subpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId);
    if (subpassRecordingIter == context.renderPassRecordingIdToRenderSubpassRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to end render subpass recording, render pass recording stack for render pass %" PRIu64 " is empty, "
            "expected implicit first subpass",
            renderPassRecordingId
        );
        // This is an error for the subpass but not for render pass, we need to continue to finish ending the render pass recording
    }
    else
    {
        statements.EndRenderSubpassRecording(this->block_index_, subpassRecordingIter->second);

        context.renderPassRecordingIdToRenderSubpassRecordingId.erase(subpassRecordingIter);
    }

    auto subpassIndexRemoved = context.renderPassRecordingIdToSubpassIndex.erase(renderPassRecordingId);
    if (!subpassIndexRemoved)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render subpass index for render pass recording %" PRIu64 ", expected implicit first subpass",
            renderPassRecordingId
        );
    }

    renderPassRecordingIdStackIter->second.pop();
    if (!renderPassRecordingIdStackIter->second.empty())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to cleanup render pass recording stack for command buffer %" PRIu64 ", expected stack to be empty after end render pass api event",
            args.commandBuffer
        );
    }
    else
    {
        context.commandBufferHandleToRenderPassRecordingIdStack.erase(renderPassRecordingIdStackIter);
    }

    auto [subpassEndInfoValid, subpassEndInfo] = GetMetaStructPointer(&args.pSubpassEndInfo);
    if (!subpassEndInfoValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to process end subpass, invalid pSubpassEndInfo");
        return;
    }

    LogUnsupportedPNext(subpassEndInfo->pNext);
}
void VulkanSqliteConsumer::Process_vkGetSwapchainStatusKHR(
    const ApiCallInfo&                          call_info,
    args::GetSwapchainStatusKHR&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSwapchainStatusKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalFencePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalFencePropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalFencePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalFenceInfo", &args.pExternalFenceInfo, "const VkPhysicalDeviceExternalFenceInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalFenceProperties", &args.pExternalFenceProperties, "VkExternalFenceProperties*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkImportFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    args::ImportFenceWin32HandleKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkImportFenceWin32HandleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pImportFenceWin32HandleInfo", &args.pImportFenceWin32HandleInfo, "const VkImportFenceWin32HandleInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetFenceWin32HandleKHR(
    const ApiCallInfo&                          call_info,
    args::GetFenceWin32HandleKHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetFenceWin32HandleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetWin32HandleInfo", &args.pGetWin32HandleInfo, "const VkFenceGetWin32HandleInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pHandle", args.pHandle, "HANDLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkImportFenceFdKHR(
    const ApiCallInfo&                          call_info,
    args::ImportFenceFdKHR&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkImportFenceFdKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pImportFenceFdInfo", &args.pImportFenceFdInfo, "const VkImportFenceFdInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetFenceFdKHR(
    const ApiCallInfo&                          call_info,
    args::GetFenceFdKHR&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetFenceFdKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetFdInfo", &args.pGetFdInfo, "const VkFenceGetFdInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pFd", args.pFd, "int*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    const ApiCallInfo&                          call_info,
    args::EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pCounterCount", args.pCounterCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pCounters", &args.pCounters, "VkPerformanceCounterKHR*");
    FieldToSqlite(statements, fieldInfo, 5, "pCounterDescriptions", &args.pCounterDescriptions, "VkPerformanceCounterDescriptionKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPerformanceQueryCreateInfo", &args.pPerformanceQueryCreateInfo, "const VkQueryPoolPerformanceCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pNumPasses", args.pNumPasses, "uint32_t*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkAcquireProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    args::AcquireProfilingLockKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireProfilingLockKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkAcquireProfilingLockInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkReleaseProfilingLockKHR(
    const ApiCallInfo&                          call_info,
    args::ReleaseProfilingLockKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseProfilingLockKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceCapabilities2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pSurfaceInfo", &args.pSurfaceInfo, "const VkPhysicalDeviceSurfaceInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pSurfaceCapabilities", &args.pSurfaceCapabilities, "VkSurfaceCapabilities2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceFormats2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceFormats2KHR&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceFormats2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pSurfaceInfo", &args.pSurfaceInfo, "const VkPhysicalDeviceSurfaceInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pSurfaceFormatCount", args.pSurfaceFormatCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurfaceFormats", &args.pSurfaceFormats, "VkSurfaceFormat2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceDisplayProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceDisplayProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceDisplayProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkDisplayProperties2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceDisplayPlaneProperties2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkDisplayPlaneProperties2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDisplayModeProperties2KHR(
    const ApiCallInfo&                          call_info,
    args::GetDisplayModeProperties2KHR&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDisplayModeProperties2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);
    FieldToSqlite(statements, fieldInfo, 3, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkDisplayModeProperties2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDisplayPlaneCapabilities2KHR(
    const ApiCallInfo&                          call_info,
    args::GetDisplayPlaneCapabilities2KHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDisplayPlaneCapabilities2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pDisplayPlaneInfo", &args.pDisplayPlaneInfo, "const VkDisplayPlaneInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pCapabilities", &args.pCapabilities, "VkDisplayPlaneCapabilities2KHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetImageMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    args::GetImageMemoryRequirements2KHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageMemoryRequirements2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetBufferMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    args::GetBufferMemoryRequirements2KHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferMemoryRequirements2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSparseMemoryRequirements2KHR(
    const ApiCallInfo&                          call_info,
    args::GetImageSparseMemoryRequirements2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSparseMemoryRequirements2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageSparseMemoryRequirementsInfo2*");
    FieldToSqlite(statements, fieldInfo, 3, "pSparseMemoryRequirementCount", args.pSparseMemoryRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSparseMemoryRequirements", &args.pSparseMemoryRequirements, "VkSparseImageMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateSamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    args::CreateSamplerYcbcrConversionKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateSamplerYcbcrConversionKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkSamplerYcbcrConversionCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pYcbcrConversion", &args.pYcbcrConversion, "VkSamplerYcbcrConversion*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroySamplerYcbcrConversionKHR(
    const ApiCallInfo&                          call_info,
    args::DestroySamplerYcbcrConversionKHR&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroySamplerYcbcrConversionKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "ycbcrConversion", "VkSamplerYcbcrConversion", args.ycbcrConversion);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkBindBufferMemory2KHR(
    const ApiCallInfo&                          call_info,
    args::BindBufferMemory2KHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindBufferMemory2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindBufferMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkBindImageMemory2KHR(
    const ApiCallInfo&                          call_info,
    args::BindImageMemory2KHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindImageMemory2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindImageMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}
void VulkanSqliteConsumer::Process_vkGetDescriptorSetLayoutSupportKHR(
    const ApiCallInfo&                          call_info,
    args::GetDescriptorSetLayoutSupportKHR&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDescriptorSetLayoutSupportKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDescriptorSetLayoutCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pSupport", &args.pSupport, "VkDescriptorSetLayoutSupport*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdDrawIndirectCountKHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectCountKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectCountKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirectCountKHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirectCountKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirectCountKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}
void VulkanSqliteConsumer::Process_vkGetSemaphoreCounterValueKHR(
    const ApiCallInfo&                          call_info,
    args::GetSemaphoreCounterValueKHR&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSemaphoreCounterValueKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "semaphore", "VkSemaphore", args.semaphore);
    FieldToSqlite(statements, fieldInfo, 3, "pValue", args.pValue, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkWaitSemaphoresKHR(
    const ApiCallInfo&                          call_info,
    args::WaitSemaphoresKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWaitSemaphoresKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pWaitInfo", &args.pWaitInfo, "const VkSemaphoreWaitInfo*");
    RecordField(
        statements, fieldInfo, 3, "timeout", "uint64_t", args.timeout);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkSignalSemaphoreKHR(
    const ApiCallInfo&                          call_info,
    args::SignalSemaphoreKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSignalSemaphoreKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pSignalInfo", &args.pSignalInfo, "const VkSemaphoreSignalInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceFragmentShadingRatesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceFragmentShadingRatesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceFragmentShadingRatesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pFragmentShadingRateCount", args.pFragmentShadingRateCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pFragmentShadingRates", &args.pFragmentShadingRates, "VkPhysicalDeviceFragmentShadingRateKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdSetFragmentShadingRateKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetFragmentShadingRateKHR&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetFragmentShadingRateKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pFragmentSize", &args.pFragmentSize, "const VkExtent2D*");
    FieldToSqlite(statements, fieldInfo, 3, "combinerOps", args.combinerOps, "const VkFragmentShadingRateCombinerOpKHR");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetRenderingAttachmentLocationsKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetRenderingAttachmentLocationsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRenderingAttachmentLocationsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pLocationInfo", &args.pLocationInfo, "const VkRenderingAttachmentLocationInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRenderingInputAttachmentIndicesKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetRenderingInputAttachmentIndicesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRenderingInputAttachmentIndicesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInputAttachmentIndexInfo", &args.pInputAttachmentIndexInfo, "const VkRenderingInputAttachmentIndexInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkWaitForPresentKHR(
    const ApiCallInfo&                          call_info,
    args::WaitForPresentKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWaitForPresentKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    RecordField(
        statements, fieldInfo, 3, "presentId", "uint64_t", args.presentId);
    RecordField(
        statements, fieldInfo, 4, "timeout", "uint64_t", args.timeout);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}
void VulkanSqliteConsumer::Process_vkGetBufferDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    args::GetBufferDeviceAddressKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferDeviceAddressKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferDeviceAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceAddress", args.result);
}

void VulkanSqliteConsumer::Process_vkGetBufferOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    args::GetBufferOpaqueCaptureAddressKHR&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferOpaqueCaptureAddressKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferDeviceAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceMemoryOpaqueCaptureAddressKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceMemoryOpaqueCaptureAddressKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceMemoryOpaqueCaptureAddressKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceMemoryOpaqueCaptureAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    args::CreateDeferredOperationKHR&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDeferredOperationKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 3, "pDeferredOperation", &args.pDeferredOperation, "VkDeferredOperationKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDeferredOperationKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyDeferredOperationKHR&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDeferredOperationKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "operation", "VkDeferredOperationKHR", args.operation);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeferredOperationMaxConcurrencyKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeferredOperationMaxConcurrencyKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeferredOperationMaxConcurrencyKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "operation", "VkDeferredOperationKHR", args.operation);

    statements.InsertApiEventReturns(this->block_index_, "uint32_t", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeferredOperationResultKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeferredOperationResultKHR&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeferredOperationResultKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "operation", "VkDeferredOperationKHR", args.operation);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDeferredOperationJoinKHR(
    const ApiCallInfo&                          call_info,
    args::DeferredOperationJoinKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDeferredOperationJoinKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "operation", "VkDeferredOperationKHR", args.operation);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPipelineExecutablePropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPipelineExecutablePropertiesKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineExecutablePropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pPipelineInfo", &args.pPipelineInfo, "const VkPipelineInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pExecutableCount", args.pExecutableCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkPipelineExecutablePropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPipelineExecutableStatisticsKHR(
    const ApiCallInfo&                          call_info,
    args::GetPipelineExecutableStatisticsKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineExecutableStatisticsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pExecutableInfo", &args.pExecutableInfo, "const VkPipelineExecutableInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pStatisticCount", args.pStatisticCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pStatistics", &args.pStatistics, "VkPipelineExecutableStatisticKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPipelineExecutableInternalRepresentationsKHR(
    const ApiCallInfo&                          call_info,
    args::GetPipelineExecutableInternalRepresentationsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineExecutableInternalRepresentationsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pExecutableInfo", &args.pExecutableInfo, "const VkPipelineExecutableInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pInternalRepresentationCount", args.pInternalRepresentationCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pInternalRepresentations", &args.pInternalRepresentations, "VkPipelineExecutableInternalRepresentationKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkMapMemory2KHR(
    const ApiCallInfo&                          call_info,
    args::MapMemory2KHR&                        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkMapMemory2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryMapInfo", &args.pMemoryMapInfo, "const VkMemoryMapInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "ppData", args.ppData, "void**");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}

void VulkanSqliteConsumer::Process_vkUnmapMemory2KHR(
    const ApiCallInfo&                          call_info,
    args::UnmapMemory2KHR&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUnmapMemory2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryUnmapInfo", &args.pMemoryUnmapInfo, "const VkMemoryUnmapInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pQualityLevelInfo", &args.pQualityLevelInfo, "const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pQualityLevelProperties", &args.pQualityLevelProperties, "VkVideoEncodeQualityLevelPropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetEncodedVideoSessionParametersKHR(
    const ApiCallInfo&                          call_info,
    args::GetEncodedVideoSessionParametersKHR&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetEncodedVideoSessionParametersKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pVideoSessionParametersInfo", &args.pVideoSessionParametersInfo, "const VkVideoEncodeSessionParametersGetInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pFeedbackInfo", &args.pFeedbackInfo, "VkVideoEncodeSessionParametersFeedbackInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pDataSize", args.pDataSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdEncodeVideoKHR(
    const ApiCallInfo&                          call_info,
    args::CmdEncodeVideoKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEncodeVideoKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pEncodeInfo", &args.pEncodeInfo, "const VkVideoEncodeInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetEvent2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetEvent2KHR&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetEvent2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    FieldToSqlite(statements, fieldInfo, 3, "pDependencyInfo", &args.pDependencyInfo, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResetEvent2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdResetEvent2KHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResetEvent2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "event", "VkEvent", args.event);
    RecordField(
        statements, fieldInfo, 3, "stageMask", "VkPipelineStageFlags2", args.stageMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWaitEvents2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdWaitEvents2KHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWaitEvents2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "eventCount", "uint32_t", args.eventCount);
    FieldToSqlite(statements, fieldInfo, 3, "pEvents", &args.pEvents, "const VkEvent*");
    FieldToSqlite(statements, fieldInfo, 4, "pDependencyInfos", &args.pDependencyInfos, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPipelineBarrier2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdPipelineBarrier2KHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPipelineBarrier2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDependencyInfo", &args.pDependencyInfo, "const VkDependencyInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWriteTimestamp2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdWriteTimestamp2KHR&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteTimestamp2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stage", "VkPipelineStageFlags2", args.stage);
    RecordField(
        statements, fieldInfo, 3, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 4, "query", "uint32_t", args.query);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkQueueSubmit2KHR(
    const ApiCallInfo&                          call_info,
    args::QueueSubmit2KHR&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueSubmit2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    RecordField(
        statements, fieldInfo, 2, "submitCount", "uint32_t", args.submitCount);
    FieldToSqlite(statements, fieldInfo, 3, "pSubmits", &args.pSubmits, "const VkSubmitInfo2*");
    RecordField(
        statements, fieldInfo, 4, "fence", "VkFence", args.fence);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdBindIndexBuffer3KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBindIndexBuffer3KHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindIndexBuffer3KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBindIndexBuffer3InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdBindVertexBuffers3KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBindVertexBuffers3KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindVertexBuffers3KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBindingInfos", &args.pBindingInfos, "const VkBindVertexBuffer3InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirect2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirect2KHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirect2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirect2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirect2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirect2KHR&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirect2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirect2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDispatchIndirect2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchIndirect2KHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchIndirect2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDispatchIndirect2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdCopyMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryKHR&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryInfo", &args.pCopyMemoryInfo, "const VkCopyDeviceMemoryInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMemoryToImageKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryToImageKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryToImageKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryInfo", &args.pCopyMemoryInfo, "const VkCopyDeviceMemoryImageInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImageToMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImageToMemoryKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImageToMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryInfo", &args.pCopyMemoryInfo, "const VkCopyDeviceMemoryImageInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdUpdateMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdUpdateMemoryKHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdUpdateMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDstRange", &args.pDstRange, "const VkDeviceAddressRangeKHR*");
    RecordField(
        statements, fieldInfo, 3, "dstFlags", "VkAddressCommandFlagsKHR", args.dstFlags);
    RecordField(
        statements, fieldInfo, 4, "dataSize", "VkDeviceSize", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdFillMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdFillMemoryKHR&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdFillMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDstRange", &args.pDstRange, "const VkDeviceAddressRangeKHR*");
    RecordField(
        statements, fieldInfo, 3, "dstFlags", "VkAddressCommandFlagsKHR", args.dstFlags);
    RecordField(
        statements, fieldInfo, 4, "data", "uint32_t", args.data);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyQueryPoolResultsToMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyQueryPoolResultsToMemoryKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyQueryPoolResultsToMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);
    FieldToSqlite(statements, fieldInfo, 5, "pDstRange", &args.pDstRange, "const VkStridedDeviceAddressRangeKHR*");
    RecordField(
        statements, fieldInfo, 6, "dstFlags", "VkAddressCommandFlagsKHR", args.dstFlags);
    RecordField(
        statements, fieldInfo, 7, "queryResultFlags", "VkQueryResultFlags", args.queryResultFlags);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirectCount2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectCount2KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectCount2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirectCount2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirectCount2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirectCount2KHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirectCount2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirectCount2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdBeginConditionalRendering2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginConditionalRendering2EXT&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginConditionalRendering2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pConditionalRenderingBegin", &args.pConditionalRenderingBegin, "const VkConditionalRenderingBeginInfo2EXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindTransformFeedbackBuffers2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdBindTransformFeedbackBuffers2EXT&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindTransformFeedbackBuffers2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBindingInfos", &args.pBindingInfos, "const VkBindTransformFeedbackBuffer2InfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdBeginTransformFeedback2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginTransformFeedback2EXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginTransformFeedback2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstCounterRange", "uint32_t", args.firstCounterRange);
    RecordField(
        statements, fieldInfo, 3, "counterRangeCount", "uint32_t", args.counterRangeCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterInfos", &args.pCounterInfos, "const VkBindTransformFeedbackBuffer2InfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndTransformFeedback2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndTransformFeedback2EXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndTransformFeedback2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstCounterRange", "uint32_t", args.firstCounterRange);
    RecordField(
        statements, fieldInfo, 3, "counterRangeCount", "uint32_t", args.counterRangeCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterInfos", &args.pCounterInfos, "const VkBindTransformFeedbackBuffer2InfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirectByteCount2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectByteCount2EXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectByteCount2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 3, "firstInstance", "uint32_t", args.firstInstance);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterInfo", &args.pCounterInfo, "const VkBindTransformFeedbackBuffer2InfoEXT*");
    RecordField(
        statements, fieldInfo, 5, "counterOffset", "uint32_t", args.counterOffset);
    RecordField(
        statements, fieldInfo, 6, "vertexStride", "uint32_t", args.vertexStride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirect2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirect2EXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirect2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirect2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirectCount2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirectCount2EXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirectCount2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDrawIndirectCount2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    // TODO: No draw recording or state binding tracking for device-address-based commands.
    // This command uses VkDeviceAddress / pInfo structs instead of VkBuffer handles and
    // cannot be resolved to database buffer IDs with the current tracking system.
}

void VulkanSqliteConsumer::Process_vkCmdWriteMarkerToMemoryAMD(
    const ApiCallInfo&                          call_info,
    args::CmdWriteMarkerToMemoryAMD&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteMarkerToMemoryAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkMemoryMarkerInfoAMD*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCreateAccelerationStructure2KHR(
    const ApiCallInfo&                          call_info,
    args::CreateAccelerationStructure2KHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateAccelerationStructure2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkAccelerationStructureCreateInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pAccelerationStructure", &args.pAccelerationStructure, "VkAccelerationStructureKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdCopyBuffer2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBuffer2KHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBuffer2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyBufferInfo", &args.pCopyBufferInfo, "const VkCopyBufferInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImage2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImage2KHR&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImage2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageInfo", &args.pCopyImageInfo, "const VkCopyImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyBufferToImage2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyBufferToImage2KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyBufferToImage2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyBufferToImageInfo", &args.pCopyBufferToImageInfo, "const VkCopyBufferToImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyImageToBuffer2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyImageToBuffer2KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyImageToBuffer2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToBufferInfo", &args.pCopyImageToBufferInfo, "const VkCopyImageToBufferInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBlitImage2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBlitImage2KHR&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBlitImage2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBlitImageInfo", &args.pBlitImageInfo, "const VkBlitImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdResolveImage2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdResolveImage2KHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdResolveImage2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pResolveImageInfo", &args.pResolveImageInfo, "const VkResolveImageInfo2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdTraceRaysIndirect2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdTraceRaysIndirect2KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdTraceRaysIndirect2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "indirectDeviceAddress", "VkDeviceAddress", args.indirectDeviceAddress);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd raytracing recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertCmdRaytracingRecording(this->block_index_, commandBufferRecordingIter->second);
}
void VulkanSqliteConsumer::Process_vkGetDeviceBufferMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceBufferMemoryRequirementsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceBufferMemoryRequirementsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceBufferMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageMemoryRequirementsKHR&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageMemoryRequirementsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageSparseMemoryRequirementsKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageSparseMemoryRequirementsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageSparseMemoryRequirementsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageMemoryRequirements*");
    FieldToSqlite(statements, fieldInfo, 3, "pSparseMemoryRequirementCount", args.pSparseMemoryRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pSparseMemoryRequirements", &args.pSparseMemoryRequirements, "VkSparseImageMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdBindIndexBuffer2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBindIndexBuffer2KHR&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindIndexBuffer2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "size", "VkDeviceSize", args.size);
    RecordField(
        statements, fieldInfo, 5, "indexType", "VkIndexType", args.indexType);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    bool nullDescriptorEnabled = false;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
    }

    std::optional<int64_t> bufferId = std::nullopt;
    if (args.buffer != format::kNullHandleId || !nullDescriptorEnabled)
    {
        auto bufferIter = context.bufferHandleToId.find(ToInt64(args.buffer));
        if (bufferIter == context.bufferHandleToId.end())
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "Failed to bind index buffer, failed to find buffer with handle %" PRIi64,
                args.commandBuffer
            );
            return;
        }
        else
        {
            bufferId = bufferIter->second;
        }
    }
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind index buffer, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertStateIndexBufferBinding(this->block_index_, commandBufferRecordingIter->second, bufferId, args.offset, args.indexType, args.size);
}

void VulkanSqliteConsumer::Process_vkGetRenderingAreaGranularityKHR(
    const ApiCallInfo&                          call_info,
    args::GetRenderingAreaGranularityKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRenderingAreaGranularityKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingAreaInfo", &args.pRenderingAreaInfo, "const VkRenderingAreaInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pGranularity", &args.pGranularity, "VkExtent2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDeviceImageSubresourceLayoutKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceImageSubresourceLayoutKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceImageSubresourceLayoutKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceImageSubresourceInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pLayout", &args.pLayout, "VkSubresourceLayout2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetImageSubresourceLayout2KHR(
    const ApiCallInfo&                          call_info,
    args::GetImageSubresourceLayout2KHR&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSubresourceLayout2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pSubresource", &args.pSubresource, "const VkImageSubresource2*");
    FieldToSqlite(statements, fieldInfo, 4, "pLayout", &args.pLayout, "VkSubresourceLayout2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkWaitForPresent2KHR(
    const ApiCallInfo&                          call_info,
    args::WaitForPresent2KHR&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWaitForPresent2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pPresentWait2Info", &args.pPresentWait2Info, "const VkPresentWait2InfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordTrackedDeviceCommand(context, statements, this->block_index_, args.device);
}
void VulkanSqliteConsumer::Process_vkCreatePipelineBinariesKHR(
    const ApiCallInfo&                          call_info,
    args::CreatePipelineBinariesKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreatePipelineBinariesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkPipelineBinaryCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pBinaries", &args.pBinaries, "VkPipelineBinaryHandlesInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPipelineBinaryKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyPipelineBinaryKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPipelineBinaryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineBinary", "VkPipelineBinaryKHR", args.pipelineBinary);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetPipelineKeyKHR(
    const ApiCallInfo&                          call_info,
    args::GetPipelineKeyKHR&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineKeyKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pPipelineCreateInfo", &args.pPipelineCreateInfo, "const VkPipelineCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pPipelineKey", &args.pPipelineKey, "VkPipelineBinaryKeyKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPipelineBinaryDataKHR(
    const ApiCallInfo&                          call_info,
    args::GetPipelineBinaryDataKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineBinaryDataKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkPipelineBinaryDataInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pPipelineBinaryKey", &args.pPipelineBinaryKey, "VkPipelineBinaryKeyKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pPipelineBinaryDataSize", args.pPipelineBinaryDataSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pPipelineBinaryData", args.pPipelineBinaryData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkReleaseCapturedPipelineDataKHR(
    const ApiCallInfo&                          call_info,
    args::ReleaseCapturedPipelineDataKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseCapturedPipelineDataKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkReleaseCapturedPipelineDataInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkReleaseSwapchainImagesKHR(
    const ApiCallInfo&                          call_info,
    args::ReleaseSwapchainImagesKHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseSwapchainImagesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pReleaseInfo", &args.pReleaseInfo, "const VkReleaseSwapchainImagesInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCooperativeMatrixPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkCooperativeMatrixPropertiesKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetLineStippleKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineStippleKHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineStippleKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "lineStippleFactor", "uint32_t", args.lineStippleFactor);
    RecordField(
        statements, fieldInfo, 3, "lineStipplePattern", "uint16_t", args.lineStipplePattern);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCalibrateableTimeDomainsKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pTimeDomainCount", args.pTimeDomainCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pTimeDomains", args.pTimeDomains, "VkTimeDomainKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetCalibratedTimestampsKHR(
    const ApiCallInfo&                          call_info,
    args::GetCalibratedTimestampsKHR&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetCalibratedTimestampsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "timestampCount", "uint32_t", args.timestampCount);
    FieldToSqlite(statements, fieldInfo, 3, "pTimestampInfos", &args.pTimestampInfos, "const VkCalibratedTimestampInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pTimestamps", args.pTimestamps, "uint64_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pMaxDeviation", args.pMaxDeviation, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdBindDescriptorSets2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdBindDescriptorSets2KHR&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindDescriptorSets2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBindDescriptorSetsInfo", &args.pBindDescriptorSetsInfo, "const VkBindDescriptorSetsInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushConstants2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdPushConstants2KHR&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushConstants2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushConstantsInfo", &args.pPushConstantsInfo, "const VkPushConstantsInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSet2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSet2KHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSet2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushDescriptorSetInfo", &args.pPushDescriptorSetInfo, "const VkPushDescriptorSetInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdPushDescriptorSetWithTemplate2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdPushDescriptorSetWithTemplate2KHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSetWithTemplate2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPushDescriptorSetWithTemplateInfo", &args.pPushDescriptorSetWithTemplateInfo, "const VkPushDescriptorSetWithTemplateInfo*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdCopyMemoryIndirectKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryIndirectKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryIndirectKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryIndirectInfo", &args.pCopyMemoryIndirectInfo, "const VkCopyMemoryIndirectInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMemoryToImageIndirectKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryToImageIndirectKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryToImageIndirectKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryToImageIndirectInfo", &args.pCopyMemoryToImageIndirectInfo, "const VkCopyMemoryToImageIndirectInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetDeviceFaultReportsKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceFaultReportsKHR&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceFaultReportsKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "timeout", "uint64_t", args.timeout);
    FieldToSqlite(statements, fieldInfo, 3, "pFaultCounts", args.pFaultCounts, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pFaultInfo", &args.pFaultInfo, "VkDeviceFaultInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceFaultDebugInfoKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceFaultDebugInfoKHR&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceFaultDebugInfoKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pDebugInfo", &args.pDebugInfo, "VkDeviceFaultDebugInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdEndRendering2KHR(
    const ApiCallInfo&                          call_info,
    args::CmdEndRendering2KHR&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRendering2KHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingEndInfo", &args.pRenderingEndInfo, "const VkRenderingEndInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkFrameBoundaryANDROID(
    const ApiCallInfo&                          call_info,
    args::FrameBoundaryANDROID&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkFrameBoundaryANDROID");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "semaphore", "VkSemaphore", args.semaphore);
    RecordField(
        statements, fieldInfo, 3, "image", "VkImage", args.image);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    args::CreateDebugReportCallbackEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDebugReportCallbackEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDebugReportCallbackCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pCallback", &args.pCallback, "VkDebugReportCallbackEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDebugReportCallbackEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyDebugReportCallbackEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDebugReportCallbackEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    RecordField(
        statements, fieldInfo, 2, "callback", "VkDebugReportCallbackEXT", args.callback);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkDebugReportMessageEXT(
    const ApiCallInfo&                          call_info,
    args::DebugReportMessageEXT&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDebugReportMessageEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    RecordField(
        statements, fieldInfo, 2, "flags", "VkDebugReportFlagsEXT", args.flags);
    RecordField(
        statements, fieldInfo, 3, "objectType", "VkDebugReportObjectTypeEXT", args.objectType);
    RecordField(
        statements, fieldInfo, 4, "object", "uint64_t", args.object);
    RecordField(
        statements, fieldInfo, 5, "location", "size_t", args.location);
    RecordField(
        statements, fieldInfo, 6, "messageCode", "int32_t", args.messageCode);
    FieldToSqlite(statements, fieldInfo, 7, "pLayerPrefix", &args.pLayerPrefix, "const char*");
    FieldToSqlite(statements, fieldInfo, 8, "pMessage", &args.pMessage, "const char*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkDebugMarkerSetObjectTagEXT(
    const ApiCallInfo&                          call_info,
    args::DebugMarkerSetObjectTagEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDebugMarkerSetObjectTagEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pTagInfo", &args.pTagInfo, "const VkDebugMarkerObjectTagInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDebugMarkerSetObjectNameEXT(
    const ApiCallInfo&                          call_info,
    args::DebugMarkerSetObjectNameEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDebugMarkerSetObjectNameEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pNameInfo", &args.pNameInfo, "const VkDebugMarkerObjectNameInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdDebugMarkerBeginEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDebugMarkerBeginEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDebugMarkerBeginEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pMarkerInfo", &args.pMarkerInfo, "const VkDebugMarkerMarkerInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDebugMarkerEndEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDebugMarkerEndEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDebugMarkerEndEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDebugMarkerInsertEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDebugMarkerInsertEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDebugMarkerInsertEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pMarkerInfo", &args.pMarkerInfo, "const VkDebugMarkerMarkerInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdBindTransformFeedbackBuffersEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBindTransformFeedbackBuffersEXT&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindTransformFeedbackBuffersEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBuffers", &args.pBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pOffsets", args.pOffsets, "const VkDeviceSize*");
    FieldToSqlite(statements, fieldInfo, 6, "pSizes", args.pSizes, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginTransformFeedbackEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginTransformFeedbackEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstCounterBuffer", "uint32_t", args.firstCounterBuffer);
    RecordField(
        statements, fieldInfo, 3, "counterBufferCount", "uint32_t", args.counterBufferCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterBuffers", &args.pCounterBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pCounterBufferOffsets", args.pCounterBufferOffsets, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndTransformFeedbackEXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndTransformFeedbackEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndTransformFeedbackEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstCounterBuffer", "uint32_t", args.firstCounterBuffer);
    RecordField(
        statements, fieldInfo, 3, "counterBufferCount", "uint32_t", args.counterBufferCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterBuffers", &args.pCounterBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pCounterBufferOffsets", args.pCounterBufferOffsets, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginQueryIndexedEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginQueryIndexedEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "query", "uint32_t", args.query);
    RecordField(
        statements, fieldInfo, 4, "flags", "VkQueryControlFlags", args.flags);
    RecordField(
        statements, fieldInfo, 5, "index", "uint32_t", args.index);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndQueryIndexedEXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndQueryIndexedEXT&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndQueryIndexedEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "query", "uint32_t", args.query);
    RecordField(
        statements, fieldInfo, 4, "index", "uint32_t", args.index);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndirectByteCountEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectByteCountEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectByteCountEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 3, "firstInstance", "uint32_t", args.firstInstance);
    RecordField(
        statements, fieldInfo, 4, "counterBuffer", "VkBuffer", args.counterBuffer);
    RecordField(
        statements, fieldInfo, 5, "counterBufferOffset", "VkDeviceSize", args.counterBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "counterOffset", "uint32_t", args.counterOffset);
    RecordField(
        statements, fieldInfo, 7, "vertexStride", "uint32_t", args.vertexStride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectCountBuffer = context.GetBufferId(args.counterBuffer);
    indirectCountBufferOffset = args.counterBufferOffset;
    indirectCountOffset = args.counterOffset;
    indirectVertexStride = args.vertexStride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}
void VulkanSqliteConsumer::Process_vkGetImageViewHandleNVX(
    const ApiCallInfo&                          call_info,
    args::GetImageViewHandleNVX&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageViewHandleNVX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageViewHandleInfoNVX*");

    statements.InsertApiEventReturns(this->block_index_, "uint32_t", args.result);
}

void VulkanSqliteConsumer::Process_vkGetImageViewHandle64NVX(
    const ApiCallInfo&                          call_info,
    args::GetImageViewHandle64NVX&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageViewHandle64NVX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkImageViewHandleInfoNVX*");

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}

void VulkanSqliteConsumer::Process_vkGetImageViewAddressNVX(
    const ApiCallInfo&                          call_info,
    args::GetImageViewAddressNVX&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageViewAddressNVX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "imageView", "VkImageView", args.imageView);
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkImageViewAddressPropertiesNVX*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceCombinedImageSamplerIndexNVX(
    const ApiCallInfo&                          call_info,
    args::GetDeviceCombinedImageSamplerIndexNVX& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceCombinedImageSamplerIndexNVX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "imageViewIndex", "uint64_t", args.imageViewIndex);
    RecordField(
        statements, fieldInfo, 3, "samplerIndex", "uint64_t", args.samplerIndex);

    statements.InsertApiEventReturns(this->block_index_, "uint64_t", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdDrawIndirectCountAMD(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndirectCountAMD&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndirectCountAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, false);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawIndexedIndirectCountAMD(
    const ApiCallInfo&                          call_info,
    args::CmdDrawIndexedIndirectCountAMD&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawIndexedIndirectCountAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd draw recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdDrawRecordingId = statements.InsertCmdDrawRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId, true);
    std::optional<int64_t> indirectBuffer = std::nullopt;
    std::optional<uint64_t> indirectBufferOffset = std::nullopt;
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectCountOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    std::optional<uint32_t> indirectStride = std::nullopt;
    std::optional<uint32_t> indirectVertexStride = std::nullopt;
    indirectBuffer = context.GetBufferId(args.buffer);
    indirectBufferOffset = args.offset;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    indirectStride = args.stride;
    statements.InsertCmdDrawRecordingIndirectInfo(cmdDrawRecordingId, indirectBuffer, indirectBufferOffset, indirectCountBuffer, indirectCountBufferOffset, indirectCountOffset, indirectDrawCount, indirectMaxDrawCount, indirectStride, indirectVertexStride);
}
void VulkanSqliteConsumer::Process_vkGetShaderInfoAMD(
    const ApiCallInfo&                          call_info,
    args::GetShaderInfoAMD&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetShaderInfoAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "shaderStage", "VkShaderStageFlagBits", args.shaderStage);
    RecordField(
        statements, fieldInfo, 4, "infoType", "VkShaderInfoTypeAMD", args.infoType);
    FieldToSqlite(statements, fieldInfo, 5, "pInfoSize", args.pInfoSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 6, "pInfo", args.pInfo, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateStreamDescriptorSurfaceGGP(
    const ApiCallInfo&                          call_info,
    args::CreateStreamDescriptorSurfaceGGP&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateStreamDescriptorSurfaceGGP");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkStreamDescriptorSurfaceCreateInfoGGP*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalImageFormatPropertiesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalImageFormatPropertiesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "format", "VkFormat", args.format);
    RecordField(
        statements, fieldInfo, 3, "type", "VkImageType", args.type);
    RecordField(
        statements, fieldInfo, 4, "tiling", "VkImageTiling", args.tiling);
    RecordField(
        statements, fieldInfo, 5, "usage", "VkImageUsageFlags", args.usage);
    RecordField(
        statements, fieldInfo, 6, "flags", "VkImageCreateFlags", args.flags);
    RecordField(
        statements, fieldInfo, 7, "externalHandleType", "VkExternalMemoryHandleTypeFlagsNV", args.externalHandleType);
    FieldToSqlite(statements, fieldInfo, 8, "pExternalImageFormatProperties", &args.pExternalImageFormatProperties, "VkExternalImageFormatPropertiesNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetMemoryWin32HandleNV(
    const ApiCallInfo&                          call_info,
    args::GetMemoryWin32HandleNV&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryWin32HandleNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);
    RecordField(
        statements, fieldInfo, 3, "handleType", "VkExternalMemoryHandleTypeFlagsNV", args.handleType);
    FieldToSqlite(statements, fieldInfo, 4, "pHandle", args.pHandle, "HANDLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateViSurfaceNN(
    const ApiCallInfo&                          call_info,
    args::CreateViSurfaceNN&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateViSurfaceNN");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkViSurfaceCreateInfoNN*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCmdBeginConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginConditionalRenderingEXT&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginConditionalRenderingEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pConditionalRenderingBegin", &args.pConditionalRenderingBegin, "const VkConditionalRenderingBeginInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndConditionalRenderingEXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndConditionalRenderingEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndConditionalRenderingEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetViewportWScalingNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportWScalingNV&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportWScalingNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstViewport", "uint32_t", args.firstViewport);
    RecordField(
        statements, fieldInfo, 3, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 4, "pViewportWScalings", &args.pViewportWScalings, "const VkViewportWScalingNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkReleaseDisplayEXT(
    const ApiCallInfo&                          call_info,
    args::ReleaseDisplayEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseDisplayEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkAcquireXlibDisplayEXT(
    const ApiCallInfo&                          call_info,
    args::AcquireXlibDisplayEXT&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireXlibDisplayEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "dpy", args.dpy, "Display*");
    RecordField(
        statements, fieldInfo, 3, "display", "VkDisplayKHR", args.display);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetRandROutputDisplayEXT(
    const ApiCallInfo&                          call_info,
    args::GetRandROutputDisplayEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRandROutputDisplayEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "dpy", args.dpy, "Display*");
    RecordField(
        statements, fieldInfo, 3, "rrOutput", "RROutput", args.rrOutput);
    FieldToSqlite(statements, fieldInfo, 4, "pDisplay", &args.pDisplay, "VkDisplayKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfaceCapabilities2EXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfaceCapabilities2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "surface", "VkSurfaceKHR", args.surface);
    FieldToSqlite(statements, fieldInfo, 3, "pSurfaceCapabilities", &args.pSurfaceCapabilities, "VkSurfaceCapabilities2EXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkDisplayPowerControlEXT(
    const ApiCallInfo&                          call_info,
    args::DisplayPowerControlEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDisplayPowerControlEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);
    FieldToSqlite(statements, fieldInfo, 3, "pDisplayPowerInfo", &args.pDisplayPowerInfo, "const VkDisplayPowerInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkRegisterDeviceEventEXT(
    const ApiCallInfo&                          call_info,
    args::RegisterDeviceEventEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkRegisterDeviceEventEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pDeviceEventInfo", &args.pDeviceEventInfo, "const VkDeviceEventInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pFence", &args.pFence, "VkFence*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkRegisterDisplayEventEXT(
    const ApiCallInfo&                          call_info,
    args::RegisterDisplayEventEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkRegisterDisplayEventEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);
    FieldToSqlite(statements, fieldInfo, 3, "pDisplayEventInfo", &args.pDisplayEventInfo, "const VkDisplayEventInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 4, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 5, "pFence", &args.pFence, "VkFence*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSwapchainCounterEXT(
    const ApiCallInfo&                          call_info,
    args::GetSwapchainCounterEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSwapchainCounterEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    RecordField(
        statements, fieldInfo, 3, "counter", "VkSurfaceCounterFlagBitsEXT", args.counter);
    FieldToSqlite(statements, fieldInfo, 4, "pCounterValue", args.pCounterValue, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetRefreshCycleDurationGOOGLE(
    const ApiCallInfo&                          call_info,
    args::GetRefreshCycleDurationGOOGLE&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRefreshCycleDurationGOOGLE");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pDisplayTimingProperties", &args.pDisplayTimingProperties, "VkRefreshCycleDurationGOOGLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPastPresentationTimingGOOGLE(
    const ApiCallInfo&                          call_info,
    args::GetPastPresentationTimingGOOGLE&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPastPresentationTimingGOOGLE");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pPresentationTimingCount", args.pPresentationTimingCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pPresentationTimings", &args.pPresentationTimings, "VkPastPresentationTimingGOOGLE*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetDiscardRectangleEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDiscardRectangleEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDiscardRectangleEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstDiscardRectangle", "uint32_t", args.firstDiscardRectangle);
    RecordField(
        statements, fieldInfo, 3, "discardRectangleCount", "uint32_t", args.discardRectangleCount);
    FieldToSqlite(statements, fieldInfo, 4, "pDiscardRectangles", &args.pDiscardRectangles, "const VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDiscardRectangleEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDiscardRectangleEnableEXT&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDiscardRectangleEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "discardRectangleEnable", "VkBool32", args.discardRectangleEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDiscardRectangleModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDiscardRectangleModeEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDiscardRectangleModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "discardRectangleMode", "VkDiscardRectangleModeEXT", args.discardRectangleMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkSetHdrMetadataEXT(
    const ApiCallInfo&                          call_info,
    args::SetHdrMetadataEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetHdrMetadataEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchainCount", "uint32_t", args.swapchainCount);
    FieldToSqlite(statements, fieldInfo, 3, "pSwapchains", &args.pSwapchains, "const VkSwapchainKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pMetadata", &args.pMetadata, "const VkHdrMetadataEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateIOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    args::CreateIOSSurfaceMVK&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateIOSSurfaceMVK");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkIOSSurfaceCreateInfoMVK*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCreateMacOSSurfaceMVK(
    const ApiCallInfo&                          call_info,
    args::CreateMacOSSurfaceMVK&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateMacOSSurfaceMVK");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkMacOSSurfaceCreateInfoMVK*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkSetDebugUtilsObjectNameEXT(
    const ApiCallInfo&                          call_info,
    args::SetDebugUtilsObjectNameEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetDebugUtilsObjectNameEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pNameInfo", &args.pNameInfo, "const VkDebugUtilsObjectNameInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkSetDebugUtilsObjectTagEXT(
    const ApiCallInfo&                          call_info,
    args::SetDebugUtilsObjectTagEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetDebugUtilsObjectTagEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pTagInfo", &args.pTagInfo, "const VkDebugUtilsObjectTagInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkQueueBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::QueueBeginDebugUtilsLabelEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueBeginDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pLabelInfo", &args.pLabelInfo, "const VkDebugUtilsLabelEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkQueueEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::QueueEndDebugUtilsLabelEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueEndDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkQueueInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::QueueInsertDebugUtilsLabelEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueInsertDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pLabelInfo", &args.pLabelInfo, "const VkDebugUtilsLabelEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBeginDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginDebugUtilsLabelEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pLabelInfo", &args.pLabelInfo, "const VkDebugUtilsLabelEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndDebugUtilsLabelEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdInsertDebugUtilsLabelEXT(
    const ApiCallInfo&                          call_info,
    args::CmdInsertDebugUtilsLabelEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdInsertDebugUtilsLabelEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pLabelInfo", &args.pLabelInfo, "const VkDebugUtilsLabelEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCreateDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    args::CreateDebugUtilsMessengerEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDebugUtilsMessengerEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDebugUtilsMessengerCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pMessenger", &args.pMessenger, "VkDebugUtilsMessengerEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDebugUtilsMessengerEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyDebugUtilsMessengerEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDebugUtilsMessengerEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    RecordField(
        statements, fieldInfo, 2, "messenger", "VkDebugUtilsMessengerEXT", args.messenger);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkSubmitDebugUtilsMessageEXT(
    const ApiCallInfo&                          call_info,
    args::SubmitDebugUtilsMessageEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSubmitDebugUtilsMessageEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    RecordField(
        statements, fieldInfo, 2, "messageSeverity", "VkDebugUtilsMessageSeverityFlagBitsEXT", args.messageSeverity);
    RecordField(
        statements, fieldInfo, 3, "messageTypes", "VkDebugUtilsMessageTypeFlagsEXT", args.messageTypes);
    FieldToSqlite(statements, fieldInfo, 4, "pCallbackData", &args.pCallbackData, "const VkDebugUtilsMessengerCallbackDataEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetAndroidHardwareBufferPropertiesANDROID(
    const ApiCallInfo&                          call_info,
    args::GetAndroidHardwareBufferPropertiesANDROID& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetAndroidHardwareBufferPropertiesANDROID");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "buffer", args.buffer, "const struct AHardwareBuffer*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkAndroidHardwareBufferPropertiesANDROID*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetMemoryAndroidHardwareBufferANDROID(
    const ApiCallInfo&                          call_info,
    args::GetMemoryAndroidHardwareBufferANDROID& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryAndroidHardwareBufferANDROID");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkMemoryGetAndroidHardwareBufferInfoANDROID*");
    FieldToSqlite(statements, fieldInfo, 3, "pBuffer", args.pBuffer, "struct AHardwareBuffer**");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateGpaSessionAMD(
    const ApiCallInfo&                          call_info,
    args::CreateGpaSessionAMD&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateGpaSessionAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkGpaSessionCreateInfoAMD*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pGpaSession", &args.pGpaSession, "VkGpaSessionAMD*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyGpaSessionAMD(
    const ApiCallInfo&                          call_info,
    args::DestroyGpaSessionAMD&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyGpaSessionAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkSetGpaDeviceClockModeAMD(
    const ApiCallInfo&                          call_info,
    args::SetGpaDeviceClockModeAMD&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetGpaDeviceClockModeAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "VkGpaDeviceClockModeInfoAMD*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetGpaDeviceClockInfoAMD(
    const ApiCallInfo&                          call_info,
    args::GetGpaDeviceClockInfoAMD&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetGpaDeviceClockInfoAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "VkGpaDeviceGetClockInfoAMD*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdBeginGpaSessionAMD(
    const ApiCallInfo&                          call_info,
    args::CmdBeginGpaSessionAMD&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginGpaSessionAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndGpaSessionAMD(
    const ApiCallInfo&                          call_info,
    args::CmdEndGpaSessionAMD&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndGpaSessionAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginGpaSampleAMD(
    const ApiCallInfo&                          call_info,
    args::CmdBeginGpaSampleAMD&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginGpaSampleAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);
    FieldToSqlite(statements, fieldInfo, 3, "pGpaSampleBeginInfo", &args.pGpaSampleBeginInfo, "const VkGpaSampleBeginInfoAMD*");
    FieldToSqlite(statements, fieldInfo, 4, "pSampleID", args.pSampleID, "uint32_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndGpaSampleAMD(
    const ApiCallInfo&                          call_info,
    args::CmdEndGpaSampleAMD&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndGpaSampleAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);
    RecordField(
        statements, fieldInfo, 3, "sampleID", "uint32_t", args.sampleID);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetGpaSessionStatusAMD(
    const ApiCallInfo&                          call_info,
    args::GetGpaSessionStatusAMD&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetGpaSessionStatusAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetGpaSessionResultsAMD(
    const ApiCallInfo&                          call_info,
    args::GetGpaSessionResultsAMD&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetGpaSessionResultsAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);
    RecordField(
        statements, fieldInfo, 3, "sampleID", "uint32_t", args.sampleID);
    FieldToSqlite(statements, fieldInfo, 4, "pSizeInBytes", args.pSizeInBytes, "size_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkResetGpaSessionAMD(
    const ApiCallInfo&                          call_info,
    args::ResetGpaSessionAMD&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetGpaSessionAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdCopyGpaSessionResultsAMD(
    const ApiCallInfo&                          call_info,
    args::CmdCopyGpaSessionResultsAMD&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyGpaSessionResultsAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "gpaSession", "VkGpaSessionAMD", args.gpaSession);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetSampleLocationsEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetSampleLocationsEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetSampleLocationsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pSampleLocationsInfo", &args.pSampleLocationsInfo, "const VkSampleLocationsInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceMultisamplePropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceMultisamplePropertiesEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceMultisamplePropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "samples", "VkSampleCountFlagBits", args.samples);
    FieldToSqlite(statements, fieldInfo, 3, "pMultisampleProperties", &args.pMultisampleProperties, "VkMultisamplePropertiesEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetImageDrmFormatModifierPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetImageDrmFormatModifierPropertiesEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageDrmFormatModifierPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkImageDrmFormatModifierPropertiesEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    args::CreateValidationCacheEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateValidationCacheEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkValidationCacheCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pValidationCache", &args.pValidationCache, "VkValidationCacheEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyValidationCacheEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyValidationCacheEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyValidationCacheEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "validationCache", "VkValidationCacheEXT", args.validationCache);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkMergeValidationCachesEXT(
    const ApiCallInfo&                          call_info,
    args::MergeValidationCachesEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkMergeValidationCachesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "dstCache", "VkValidationCacheEXT", args.dstCache);
    RecordField(
        statements, fieldInfo, 3, "srcCacheCount", "uint32_t", args.srcCacheCount);
    FieldToSqlite(statements, fieldInfo, 4, "pSrcCaches", &args.pSrcCaches, "const VkValidationCacheEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetValidationCacheDataEXT(
    const ApiCallInfo&                          call_info,
    args::GetValidationCacheDataEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetValidationCacheDataEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "validationCache", "VkValidationCacheEXT", args.validationCache);
    FieldToSqlite(statements, fieldInfo, 3, "pDataSize", args.pDataSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdBindShadingRateImageNV(
    const ApiCallInfo&                          call_info,
    args::CmdBindShadingRateImageNV&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindShadingRateImageNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "imageView", "VkImageView", args.imageView);
    RecordField(
        statements, fieldInfo, 3, "imageLayout", "VkImageLayout", args.imageLayout);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetViewportShadingRatePaletteNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportShadingRatePaletteNV&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportShadingRatePaletteNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstViewport", "uint32_t", args.firstViewport);
    RecordField(
        statements, fieldInfo, 3, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 4, "pShadingRatePalettes", &args.pShadingRatePalettes, "const VkShadingRatePaletteNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoarseSampleOrderNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoarseSampleOrderNV&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoarseSampleOrderNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "sampleOrderType", "VkCoarseSampleOrderTypeNV", args.sampleOrderType);
    RecordField(
        statements, fieldInfo, 3, "customSampleOrderCount", "uint32_t", args.customSampleOrderCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCustomSampleOrders", &args.pCustomSampleOrders, "const VkCoarseSampleOrderCustomNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    args::CreateAccelerationStructureNV&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateAccelerationStructureNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkAccelerationStructureCreateInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pAccelerationStructure", &args.pAccelerationStructure, "VkAccelerationStructureNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    args::DestroyAccelerationStructureNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyAccelerationStructureNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructure", "VkAccelerationStructureNV", args.accelerationStructure);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetAccelerationStructureMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    args::GetAccelerationStructureMemoryRequirementsNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetAccelerationStructureMemoryRequirementsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkAccelerationStructureMemoryRequirementsInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkBindAccelerationStructureMemoryNV(
    const ApiCallInfo&                          call_info,
    args::BindAccelerationStructureMemoryNV&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindAccelerationStructureMemoryNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindAccelerationStructureMemoryInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdBuildAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    args::CmdBuildAccelerationStructureNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBuildAccelerationStructureNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkAccelerationStructureInfoNV*");
    RecordField(
        statements, fieldInfo, 3, "instanceData", "VkBuffer", args.instanceData);
    RecordField(
        statements, fieldInfo, 4, "instanceOffset", "VkDeviceSize", args.instanceOffset);
    RecordField(
        statements, fieldInfo, 5, "update", "VkBool32", args.update);
    RecordField(
        statements, fieldInfo, 6, "dst", "VkAccelerationStructureNV", args.dst);
    RecordField(
        statements, fieldInfo, 7, "src", "VkAccelerationStructureNV", args.src);
    RecordField(
        statements, fieldInfo, 8, "scratch", "VkBuffer", args.scratch);
    RecordField(
        statements, fieldInfo, 9, "scratchOffset", "VkDeviceSize", args.scratchOffset);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyAccelerationStructureNV(
    const ApiCallInfo&                          call_info,
    args::CmdCopyAccelerationStructureNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyAccelerationStructureNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "dst", "VkAccelerationStructureNV", args.dst);
    RecordField(
        statements, fieldInfo, 3, "src", "VkAccelerationStructureNV", args.src);
    RecordField(
        statements, fieldInfo, 4, "mode", "VkCopyAccelerationStructureModeKHR", args.mode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdTraceRaysNV(
    const ApiCallInfo&                          call_info,
    args::CmdTraceRaysNV&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdTraceRaysNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "raygenShaderBindingTableBuffer", "VkBuffer", args.raygenShaderBindingTableBuffer);
    RecordField(
        statements, fieldInfo, 3, "raygenShaderBindingOffset", "VkDeviceSize", args.raygenShaderBindingOffset);
    RecordField(
        statements, fieldInfo, 4, "missShaderBindingTableBuffer", "VkBuffer", args.missShaderBindingTableBuffer);
    RecordField(
        statements, fieldInfo, 5, "missShaderBindingOffset", "VkDeviceSize", args.missShaderBindingOffset);
    RecordField(
        statements, fieldInfo, 6, "missShaderBindingStride", "VkDeviceSize", args.missShaderBindingStride);
    RecordField(
        statements, fieldInfo, 7, "hitShaderBindingTableBuffer", "VkBuffer", args.hitShaderBindingTableBuffer);
    RecordField(
        statements, fieldInfo, 8, "hitShaderBindingOffset", "VkDeviceSize", args.hitShaderBindingOffset);
    RecordField(
        statements, fieldInfo, 9, "hitShaderBindingStride", "VkDeviceSize", args.hitShaderBindingStride);
    RecordField(
        statements, fieldInfo, 10, "callableShaderBindingTableBuffer", "VkBuffer", args.callableShaderBindingTableBuffer);
    RecordField(
        statements, fieldInfo, 11, "callableShaderBindingOffset", "VkDeviceSize", args.callableShaderBindingOffset);
    RecordField(
        statements, fieldInfo, 12, "callableShaderBindingStride", "VkDeviceSize", args.callableShaderBindingStride);
    RecordField(
        statements, fieldInfo, 13, "width", "uint32_t", args.width);
    RecordField(
        statements, fieldInfo, 14, "height", "uint32_t", args.height);
    RecordField(
        statements, fieldInfo, 15, "depth", "uint32_t", args.depth);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd raytracing recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertCmdRaytracingRecording(this->block_index_, commandBufferRecordingIter->second);
}

void VulkanSqliteConsumer::Process_vkCreateRayTracingPipelinesNV(
    const ApiCallInfo&                          call_info,
    args::CreateRayTracingPipelinesNV&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateRayTracingPipelinesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    RecordField(
        statements, fieldInfo, 3, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pCreateInfos", &args.pCreateInfos, "const VkRayTracingPipelineCreateInfoNV*");
    FieldToSqlite(statements, fieldInfo, 5, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 6, "pPipelines", &args.pPipelines, "VkPipeline*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetRayTracingShaderGroupHandlesKHR(
    const ApiCallInfo&                          call_info,
    args::GetRayTracingShaderGroupHandlesKHR&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRayTracingShaderGroupHandlesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "firstGroup", "uint32_t", args.firstGroup);
    RecordField(
        statements, fieldInfo, 4, "groupCount", "uint32_t", args.groupCount);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetRayTracingShaderGroupHandlesNV(
    const ApiCallInfo&                          call_info,
    args::GetRayTracingShaderGroupHandlesNV&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRayTracingShaderGroupHandlesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "firstGroup", "uint32_t", args.firstGroup);
    RecordField(
        statements, fieldInfo, 4, "groupCount", "uint32_t", args.groupCount);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetAccelerationStructureHandleNV(
    const ApiCallInfo&                          call_info,
    args::GetAccelerationStructureHandleNV&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetAccelerationStructureHandleNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructure", "VkAccelerationStructureNV", args.accelerationStructure);
    RecordField(
        statements, fieldInfo, 3, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 4, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdWriteAccelerationStructuresPropertiesNV(
    const ApiCallInfo&                          call_info,
    args::CmdWriteAccelerationStructuresPropertiesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteAccelerationStructuresPropertiesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructureCount", "uint32_t", args.accelerationStructureCount);
    FieldToSqlite(statements, fieldInfo, 3, "pAccelerationStructures", &args.pAccelerationStructures, "const VkAccelerationStructureNV*");
    RecordField(
        statements, fieldInfo, 4, "queryType", "VkQueryType", args.queryType);
    RecordField(
        statements, fieldInfo, 5, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 6, "firstQuery", "uint32_t", args.firstQuery);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCompileDeferredNV(
    const ApiCallInfo&                          call_info,
    args::CompileDeferredNV&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCompileDeferredNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "shader", "uint32_t", args.shader);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetMemoryHostPointerPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetMemoryHostPointerPropertiesEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryHostPointerPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "handleType", "VkExternalMemoryHandleTypeFlagBits", args.handleType);
    FieldToSqlite(statements, fieldInfo, 3, "pHostPointer", args.pHostPointer, "const void*");
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryHostPointerProperties", &args.pMemoryHostPointerProperties, "VkMemoryHostPointerPropertiesEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdWriteBufferMarkerAMD(
    const ApiCallInfo&                          call_info,
    args::CmdWriteBufferMarkerAMD&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteBufferMarkerAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineStage", "VkPipelineStageFlagBits", args.pipelineStage);
    RecordField(
        statements, fieldInfo, 3, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 4, "dstOffset", "VkDeviceSize", args.dstOffset);
    RecordField(
        statements, fieldInfo, 5, "marker", "uint32_t", args.marker);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWriteBufferMarker2AMD(
    const ApiCallInfo&                          call_info,
    args::CmdWriteBufferMarker2AMD&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteBufferMarker2AMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stage", "VkPipelineStageFlags2", args.stage);
    RecordField(
        statements, fieldInfo, 3, "dstBuffer", "VkBuffer", args.dstBuffer);
    RecordField(
        statements, fieldInfo, 4, "dstOffset", "VkDeviceSize", args.dstOffset);
    RecordField(
        statements, fieldInfo, 5, "marker", "uint32_t", args.marker);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCalibrateableTimeDomainsEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pTimeDomainCount", args.pTimeDomainCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pTimeDomains", args.pTimeDomains, "VkTimeDomainKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetCalibratedTimestampsEXT(
    const ApiCallInfo&                          call_info,
    args::GetCalibratedTimestampsEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetCalibratedTimestampsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "timestampCount", "uint32_t", args.timestampCount);
    FieldToSqlite(statements, fieldInfo, 3, "pTimestampInfos", &args.pTimestampInfos, "const VkCalibratedTimestampInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pTimestamps", args.pTimestamps, "uint64_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pMaxDeviation", args.pMaxDeviation, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksNV(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksNV&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "taskCount", "uint32_t", args.taskCount);
    RecordField(
        statements, fieldInfo, 3, "firstTask", "uint32_t", args.firstTask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    // TODO handle firstTask value which represents the x component of the first workgroup ID
    // per: https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawMeshTasksNV.html
    statements.InsertCmdMeshTaskRecordingInfo(cmdMeshTaskRecordingId, args.taskCount, 1, 1);
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirectNV(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirectNV&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirectNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "drawCount", "uint32_t", args.drawCount);
    RecordField(
        statements, fieldInfo, 5, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    std::optional<int64_t> indirectBuffer = context.GetBufferId(args.buffer);
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    indirectDrawCount = args.drawCount;
    statements.InsertCmdMeshTaskRecordingIndirectInfo(cmdMeshTaskRecordingId, indirectBuffer, args.offset, indirectCountBuffer, indirectCountBufferOffset, indirectDrawCount, indirectMaxDrawCount, args.stride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirectCountNV(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirectCountNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirectCountNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    std::optional<int64_t> indirectBuffer = context.GetBufferId(args.buffer);
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    statements.InsertCmdMeshTaskRecordingIndirectInfo(cmdMeshTaskRecordingId, indirectBuffer, args.offset, indirectCountBuffer, indirectCountBufferOffset, indirectDrawCount, indirectMaxDrawCount, args.stride);
}
void VulkanSqliteConsumer::Process_vkCmdSetExclusiveScissorEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetExclusiveScissorEnableNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetExclusiveScissorEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstExclusiveScissor", "uint32_t", args.firstExclusiveScissor);
    RecordField(
        statements, fieldInfo, 3, "exclusiveScissorCount", "uint32_t", args.exclusiveScissorCount);
    FieldToSqlite(statements, fieldInfo, 4, "pExclusiveScissorEnables", args.pExclusiveScissorEnables, "const VkBool32*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetExclusiveScissorNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetExclusiveScissorNV&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetExclusiveScissorNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstExclusiveScissor", "uint32_t", args.firstExclusiveScissor);
    RecordField(
        statements, fieldInfo, 3, "exclusiveScissorCount", "uint32_t", args.exclusiveScissorCount);
    FieldToSqlite(statements, fieldInfo, 4, "pExclusiveScissors", &args.pExclusiveScissors, "const VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetCheckpointNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCheckpointNV&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCheckpointNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCheckpointMarker", args.pCheckpointMarker, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetQueueCheckpointDataNV(
    const ApiCallInfo&                          call_info,
    args::GetQueueCheckpointDataNV&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetQueueCheckpointDataNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pCheckpointDataCount", args.pCheckpointDataCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pCheckpointData", &args.pCheckpointData, "VkCheckpointDataNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetQueueCheckpointData2NV(
    const ApiCallInfo&                          call_info,
    args::GetQueueCheckpointData2NV&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetQueueCheckpointData2NV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pCheckpointDataCount", args.pCheckpointDataCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pCheckpointData", &args.pCheckpointData, "VkCheckpointData2NV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkSetSwapchainPresentTimingQueueSizeEXT(
    const ApiCallInfo&                          call_info,
    args::SetSwapchainPresentTimingQueueSizeEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetSwapchainPresentTimingQueueSizeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    RecordField(
        statements, fieldInfo, 3, "size", "uint32_t", args.size);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSwapchainTimingPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetSwapchainTimingPropertiesEXT&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSwapchainTimingPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pSwapchainTimingProperties", &args.pSwapchainTimingProperties, "VkSwapchainTimingPropertiesEXT*");
    FieldToSqlite(statements, fieldInfo, 4, "pSwapchainTimingPropertiesCounter", args.pSwapchainTimingPropertiesCounter, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSwapchainTimeDomainPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetSwapchainTimeDomainPropertiesEXT&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSwapchainTimeDomainPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pSwapchainTimeDomainProperties", &args.pSwapchainTimeDomainProperties, "VkSwapchainTimeDomainPropertiesEXT*");
    FieldToSqlite(statements, fieldInfo, 4, "pTimeDomainsCounter", args.pTimeDomainsCounter, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPastPresentationTimingEXT(
    const ApiCallInfo&                          call_info,
    args::GetPastPresentationTimingEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPastPresentationTimingEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pPastPresentationTimingInfo", &args.pPastPresentationTimingInfo, "const VkPastPresentationTimingInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pPastPresentationTimingProperties", &args.pPastPresentationTimingProperties, "VkPastPresentationTimingPropertiesEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkInitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    args::InitializePerformanceApiINTEL&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkInitializePerformanceApiINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInitializeInfo", &args.pInitializeInfo, "const VkInitializePerformanceApiInfoINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkUninitializePerformanceApiINTEL(
    const ApiCallInfo&                          call_info,
    args::UninitializePerformanceApiINTEL&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUninitializePerformanceApiINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdSetPerformanceMarkerINTEL(
    const ApiCallInfo&                          call_info,
    args::CmdSetPerformanceMarkerINTEL&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPerformanceMarkerINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pMarkerInfo", &args.pMarkerInfo, "const VkPerformanceMarkerInfoINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPerformanceStreamMarkerINTEL(
    const ApiCallInfo&                          call_info,
    args::CmdSetPerformanceStreamMarkerINTEL&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPerformanceStreamMarkerINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pMarkerInfo", &args.pMarkerInfo, "const VkPerformanceStreamMarkerInfoINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPerformanceOverrideINTEL(
    const ApiCallInfo&                          call_info,
    args::CmdSetPerformanceOverrideINTEL&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPerformanceOverrideINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pOverrideInfo", &args.pOverrideInfo, "const VkPerformanceOverrideInfoINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkAcquirePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    args::AcquirePerformanceConfigurationINTEL& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquirePerformanceConfigurationINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pAcquireInfo", &args.pAcquireInfo, "const VkPerformanceConfigurationAcquireInfoINTEL*");
    FieldToSqlite(statements, fieldInfo, 3, "pConfiguration", &args.pConfiguration, "VkPerformanceConfigurationINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkReleasePerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    args::ReleasePerformanceConfigurationINTEL& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleasePerformanceConfigurationINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "configuration", "VkPerformanceConfigurationINTEL", args.configuration);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkQueueSetPerformanceConfigurationINTEL(
    const ApiCallInfo&                          call_info,
    args::QueueSetPerformanceConfigurationINTEL& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueSetPerformanceConfigurationINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    RecordField(
        statements, fieldInfo, 2, "configuration", "VkPerformanceConfigurationINTEL", args.configuration);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPerformanceParameterINTEL(
    const ApiCallInfo&                          call_info,
    args::GetPerformanceParameterINTEL&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPerformanceParameterINTEL");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "parameter", "VkPerformanceParameterTypeINTEL", args.parameter);
    FieldToSqlite(statements, fieldInfo, 3, "pValue", &args.pValue, "VkPerformanceValueINTEL*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkSetLocalDimmingAMD(
    const ApiCallInfo&                          call_info,
    args::SetLocalDimmingAMD&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetLocalDimmingAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapChain", "VkSwapchainKHR", args.swapChain);
    RecordField(
        statements, fieldInfo, 3, "localDimmingEnable", "VkBool32", args.localDimmingEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateImagePipeSurfaceFUCHSIA(
    const ApiCallInfo&                          call_info,
    args::CreateImagePipeSurfaceFUCHSIA&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateImagePipeSurfaceFUCHSIA");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkImagePipeSurfaceCreateInfoFUCHSIA*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCreateMetalSurfaceEXT(
    const ApiCallInfo&                          call_info,
    args::CreateMetalSurfaceEXT&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateMetalSurfaceEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkMetalSurfaceCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkGetBufferDeviceAddressEXT(
    const ApiCallInfo&                          call_info,
    args::GetBufferDeviceAddressEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetBufferDeviceAddressEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkBufferDeviceAddressInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceAddress", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceToolPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceToolPropertiesEXT&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceToolPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pToolCount", args.pToolCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pToolProperties", &args.pToolProperties, "VkPhysicalDeviceToolProperties*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCooperativeMatrixPropertiesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCooperativeMatrixPropertiesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkCooperativeMatrixPropertiesNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pCombinationCount", args.pCombinationCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pCombinations", &args.pCombinations, "VkFramebufferMixedSamplesCombinationNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceSurfacePresentModes2EXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceSurfacePresentModes2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pSurfaceInfo", &args.pSurfaceInfo, "const VkPhysicalDeviceSurfaceInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pPresentModeCount", args.pPresentModeCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pPresentModes", args.pPresentModes, "VkPresentModeKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkAcquireFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    args::AcquireFullScreenExclusiveModeEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireFullScreenExclusiveModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkReleaseFullScreenExclusiveModeEXT(
    const ApiCallInfo&                          call_info,
    args::ReleaseFullScreenExclusiveModeEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseFullScreenExclusiveModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceGroupSurfacePresentModes2EXT(
    const ApiCallInfo&                          call_info,
    args::GetDeviceGroupSurfacePresentModes2EXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceGroupSurfacePresentModes2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pSurfaceInfo", &args.pSurfaceInfo, "const VkPhysicalDeviceSurfaceInfo2KHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pModes", args.pModes, "VkDeviceGroupPresentModeFlagsKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateHeadlessSurfaceEXT(
    const ApiCallInfo&                          call_info,
    args::CreateHeadlessSurfaceEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateHeadlessSurfaceEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkHeadlessSurfaceCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetLineStippleEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineStippleEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineStippleEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "lineStippleFactor", "uint32_t", args.lineStippleFactor);
    RecordField(
        statements, fieldInfo, 3, "lineStipplePattern", "uint16_t", args.lineStipplePattern);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkResetQueryPoolEXT(
    const ApiCallInfo&                          call_info,
    args::ResetQueryPoolEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkResetQueryPoolEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 3, "firstQuery", "uint32_t", args.firstQuery);
    RecordField(
        statements, fieldInfo, 4, "queryCount", "uint32_t", args.queryCount);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdSetCullModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetCullModeEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCullModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "cullMode", "VkCullModeFlags", args.cullMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetFrontFaceEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetFrontFaceEXT&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetFrontFaceEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "frontFace", "VkFrontFace", args.frontFace);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPrimitiveTopologyEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetPrimitiveTopologyEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPrimitiveTopologyEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "primitiveTopology", "VkPrimitiveTopology", args.primitiveTopology);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetViewportWithCountEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportWithCountEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportWithCountEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 3, "pViewports", &args.pViewports, "const VkViewport*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetScissorWithCountEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetScissorWithCountEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetScissorWithCountEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "scissorCount", "uint32_t", args.scissorCount);
    FieldToSqlite(statements, fieldInfo, 3, "pScissors", &args.pScissors, "const VkRect2D*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindVertexBuffers2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdBindVertexBuffers2EXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindVertexBuffers2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstBinding", "uint32_t", args.firstBinding);
    RecordField(
        statements, fieldInfo, 3, "bindingCount", "uint32_t", args.bindingCount);
    FieldToSqlite(statements, fieldInfo, 4, "pBuffers", &args.pBuffers, "const VkBuffer*");
    FieldToSqlite(statements, fieldInfo, 5, "pOffsets", args.pOffsets, "const VkDeviceSize*");
    FieldToSqlite(statements, fieldInfo, 6, "pSizes", args.pSizes, "const VkDeviceSize*");
    FieldToSqlite(statements, fieldInfo, 7, "pStrides", args.pStrides, "const VkDeviceSize*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [buffersValid, buffers, buffersCount] = GetHandleArray(&args.pBuffers);
    if (!buffersValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pBuffers");
        return;
    }

    auto [offsetsValid, offsets, offsetsCount] = GetPointerArray(&args.pOffsets);
    if (!offsetsValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind vertex buffers, invalid pOffsets");
        return;
    }
    auto [sizesValid, sizes, sizesCount] = GetPointerArray(&args.pSizes);
    auto [stridesValid, strides, stridesCount] = GetPointerArray(&args.pStrides);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind vertex buffers, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (buffersCount != offsetsCount) {
        GFXRECON_SQLITE_LOG_WARNING("pBuffer and pOffset counts do not match, using min");
    }
    for (size_t i = 0; i < std::min(buffersCount, offsetsCount); ++i)
    {
        std::optional<uint64_t> size = std::nullopt;
        std::optional<uint64_t> stride = std::nullopt;
        if (sizesValid)
        {
            size = sizes[i];
        }
        if (stridesValid)
        {
            stride = strides[i];
        }
        bool nullDescriptorEnabled = false;
        auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
        if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
        {
            nullDescriptorEnabled = context.IsDeviceFeatureEnabled(deviceIdIter->second, "nullDescriptor");
        }

        auto buffer = buffers[i];
        std::optional<int64_t> bufferId = std::nullopt;
        if (buffer != format::kNullHandleId || !nullDescriptorEnabled)
        {
            auto bufferIter = context.bufferHandleToId.find(ToInt64(buffer));
            if (bufferIter == context.bufferHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to bind vertex buffer, failed to find buffer with handle %" PRIi64,
                    buffer
                );
                continue;
            }
            else
            {
                bufferId = bufferIter->second;
            }
        }
        auto offset = offsets[i];
        auto binding = args.firstBinding + static_cast<uint32_t>(i);

        statements.InsertStateVertexBufferBinding(this->block_index_, commandBufferRecordingIter->second, binding, bufferId, offset, size, stride);
    }
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthTestEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthTestEnableEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthTestEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthTestEnable", "VkBool32", args.depthTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthWriteEnableEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthWriteEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthWriteEnable", "VkBool32", args.depthWriteEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthCompareOpEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthCompareOpEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthCompareOpEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthCompareOp", "VkCompareOp", args.depthCompareOp);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBoundsTestEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBoundsTestEnableEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBoundsTestEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthBoundsTestEnable", "VkBool32", args.depthBoundsTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilTestEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilTestEnableEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilTestEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stencilTestEnable", "VkBool32", args.stencilTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetStencilOpEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetStencilOpEXT&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetStencilOpEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "faceMask", "VkStencilFaceFlags", args.faceMask);
    RecordField(
        statements, fieldInfo, 3, "failOp", "VkStencilOp", args.failOp);
    RecordField(
        statements, fieldInfo, 4, "passOp", "VkStencilOp", args.passOp);
    RecordField(
        statements, fieldInfo, 5, "depthFailOp", "VkStencilOp", args.depthFailOp);
    RecordField(
        statements, fieldInfo, 6, "compareOp", "VkCompareOp", args.compareOp);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCopyMemoryToImageEXT(
    const ApiCallInfo&                          call_info,
    args::CopyMemoryToImageEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMemoryToImageEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyMemoryToImageInfo", &args.pCopyMemoryToImageInfo, "const VkCopyMemoryToImageInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyImageToMemoryEXT(
    const ApiCallInfo&                          call_info,
    args::CopyImageToMemoryEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyImageToMemoryEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToMemoryInfo", &args.pCopyImageToMemoryInfo, "const VkCopyImageToMemoryInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyImageToImageEXT(
    const ApiCallInfo&                          call_info,
    args::CopyImageToImageEXT&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyImageToImageEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyImageToImageInfo", &args.pCopyImageToImageInfo, "const VkCopyImageToImageInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkTransitionImageLayoutEXT(
    const ApiCallInfo&                          call_info,
    args::TransitionImageLayoutEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkTransitionImageLayoutEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "transitionCount", "uint32_t", args.transitionCount);
    FieldToSqlite(statements, fieldInfo, 3, "pTransitions", &args.pTransitions, "const VkHostImageLayoutTransitionInfo*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetImageSubresourceLayout2EXT(
    const ApiCallInfo&                          call_info,
    args::GetImageSubresourceLayout2EXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetImageSubresourceLayout2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "image", "VkImage", args.image);
    FieldToSqlite(statements, fieldInfo, 3, "pSubresource", &args.pSubresource, "const VkImageSubresource2*");
    FieldToSqlite(statements, fieldInfo, 4, "pLayout", &args.pLayout, "VkSubresourceLayout2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkReleaseSwapchainImagesEXT(
    const ApiCallInfo&                          call_info,
    args::ReleaseSwapchainImagesEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkReleaseSwapchainImagesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pReleaseInfo", &args.pReleaseInfo, "const VkReleaseSwapchainImagesInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    args::GetGeneratedCommandsMemoryRequirementsNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetGeneratedCommandsMemoryRequirementsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkGeneratedCommandsMemoryRequirementsInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdPreprocessGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    args::CmdPreprocessGeneratedCommandsNV&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPreprocessGeneratedCommandsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pGeneratedCommandsInfo", &args.pGeneratedCommandsInfo, "const VkGeneratedCommandsInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdExecuteGeneratedCommandsNV(
    const ApiCallInfo&                          call_info,
    args::CmdExecuteGeneratedCommandsNV&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdExecuteGeneratedCommandsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "isPreprocessed", "VkBool32", args.isPreprocessed);
    FieldToSqlite(statements, fieldInfo, 3, "pGeneratedCommandsInfo", &args.pGeneratedCommandsInfo, "const VkGeneratedCommandsInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBindPipelineShaderGroupNV(
    const ApiCallInfo&                          call_info,
    args::CmdBindPipelineShaderGroupNV&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindPipelineShaderGroupNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 4, "groupIndex", "uint32_t", args.groupIndex);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCreateIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    args::CreateIndirectCommandsLayoutNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateIndirectCommandsLayoutNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkIndirectCommandsLayoutCreateInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pIndirectCommandsLayout", &args.pIndirectCommandsLayout, "VkIndirectCommandsLayoutNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyIndirectCommandsLayoutNV(
    const ApiCallInfo&                          call_info,
    args::DestroyIndirectCommandsLayoutNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyIndirectCommandsLayoutNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "indirectCommandsLayout", "VkIndirectCommandsLayoutNV", args.indirectCommandsLayout);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdSetDepthBias2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBias2EXT&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBias2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDepthBiasInfo", &args.pDepthBiasInfo, "const VkDepthBiasInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkAcquireDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    args::AcquireDrmDisplayEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireDrmDisplayEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "drmFd", "int32_t", args.drmFd);
    RecordField(
        statements, fieldInfo, 3, "display", "VkDisplayKHR", args.display);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDrmDisplayEXT(
    const ApiCallInfo&                          call_info,
    args::GetDrmDisplayEXT&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDrmDisplayEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "drmFd", "int32_t", args.drmFd);
    RecordField(
        statements, fieldInfo, 3, "connectorId", "uint32_t", args.connectorId);
    FieldToSqlite(statements, fieldInfo, 4, "display", &args.display, "VkDisplayKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreatePrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    args::CreatePrivateDataSlotEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreatePrivateDataSlotEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkPrivateDataSlotCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pPrivateDataSlot", &args.pPrivateDataSlot, "VkPrivateDataSlot*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyPrivateDataSlotEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyPrivateDataSlotEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyPrivateDataSlotEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkSetPrivateDataEXT(
    const ApiCallInfo&                          call_info,
    args::SetPrivateDataEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetPrivateDataEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "objectType", "VkObjectType", args.objectType);
    RecordField(
        statements, fieldInfo, 3, "objectHandle", "uint64_t", args.objectHandle);
    RecordField(
        statements, fieldInfo, 4, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    RecordField(
        statements, fieldInfo, 5, "data", "uint64_t", args.data);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPrivateDataEXT(
    const ApiCallInfo&                          call_info,
    args::GetPrivateDataEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPrivateDataEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "objectType", "VkObjectType", args.objectType);
    RecordField(
        statements, fieldInfo, 3, "objectHandle", "uint64_t", args.objectHandle);
    RecordField(
        statements, fieldInfo, 4, "privateDataSlot", "VkPrivateDataSlot", args.privateDataSlot);
    FieldToSqlite(statements, fieldInfo, 5, "pData", args.pData, "uint64_t*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkQueueSetPerfHintQCOM(
    const ApiCallInfo&                          call_info,
    args::QueueSetPerfHintQCOM&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueSetPerfHintQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pPerfHintInfo", &args.pPerfHintInfo, "const VkPerfHintInfoQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdDispatchTileQCOM(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchTileQCOM&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchTileQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDispatchTileInfo", &args.pDispatchTileInfo, "const VkDispatchTileInfoQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdBeginPerTileExecutionQCOM(
    const ApiCallInfo&                          call_info,
    args::CmdBeginPerTileExecutionQCOM&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginPerTileExecutionQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPerTileBeginInfo", &args.pPerTileBeginInfo, "const VkPerTileBeginInfoQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdEndPerTileExecutionQCOM(
    const ApiCallInfo&                          call_info,
    args::CmdEndPerTileExecutionQCOM&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndPerTileExecutionQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pPerTileEndInfo", &args.pPerTileEndInfo, "const VkPerTileEndInfoQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetFragmentShadingRateEnumNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetFragmentShadingRateEnumNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetFragmentShadingRateEnumNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "shadingRate", "VkFragmentShadingRateNV", args.shadingRate);
    FieldToSqlite(statements, fieldInfo, 3, "combinerOps", args.combinerOps, "const VkFragmentShadingRateCombinerOpKHR");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetDeviceFaultInfoEXT(
    const ApiCallInfo&                          call_info,
    args::GetDeviceFaultInfoEXT&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceFaultInfoEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pFaultCounts", &args.pFaultCounts, "VkDeviceFaultCountsEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pFaultInfo", &args.pFaultInfo, "VkDeviceFaultInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkAcquireWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    args::AcquireWinrtDisplayNV&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAcquireWinrtDisplayNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "display", "VkDisplayKHR", args.display);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetWinrtDisplayNV(
    const ApiCallInfo&                          call_info,
    args::GetWinrtDisplayNV&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetWinrtDisplayNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "deviceRelativeId", "uint32_t", args.deviceRelativeId);
    FieldToSqlite(statements, fieldInfo, 3, "pDisplay", &args.pDisplay, "VkDisplayKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCreateDirectFBSurfaceEXT(
    const ApiCallInfo&                          call_info,
    args::CreateDirectFBSurfaceEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDirectFBSurfaceEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDirectFBSurfaceCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceDirectFBPresentationSupportEXT(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceDirectFBPresentationSupportEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceDirectFBPresentationSupportEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "dfb", args.dfb, "IDirectFB*");

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetVertexInputEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetVertexInputEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetVertexInputEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "vertexBindingDescriptionCount", "uint32_t", args.vertexBindingDescriptionCount);
    FieldToSqlite(statements, fieldInfo, 3, "pVertexBindingDescriptions", &args.pVertexBindingDescriptions, "const VkVertexInputBindingDescription2EXT*");
    RecordField(
        statements, fieldInfo, 4, "vertexAttributeDescriptionCount", "uint32_t", args.vertexAttributeDescriptionCount);
    FieldToSqlite(statements, fieldInfo, 5, "pVertexAttributeDescriptions", &args.pVertexAttributeDescriptions, "const VkVertexInputAttributeDescription2EXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetMemoryZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    args::GetMemoryZirconHandleFUCHSIA&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryZirconHandleFUCHSIA");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetZirconHandleInfo", &args.pGetZirconHandleInfo, "const VkMemoryGetZirconHandleInfoFUCHSIA*");
    FieldToSqlite(statements, fieldInfo, 3, "pZirconHandle", args.pZirconHandle, "zx_handle_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetMemoryZirconHandlePropertiesFUCHSIA(
    const ApiCallInfo&                          call_info,
    args::GetMemoryZirconHandlePropertiesFUCHSIA& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryZirconHandlePropertiesFUCHSIA");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "handleType", "VkExternalMemoryHandleTypeFlagBits", args.handleType);
    RecordField(
        statements, fieldInfo, 3, "zirconHandle", "zx_handle_t", args.zirconHandle);
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryZirconHandleProperties", &args.pMemoryZirconHandleProperties, "VkMemoryZirconHandlePropertiesFUCHSIA*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkImportSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    args::ImportSemaphoreZirconHandleFUCHSIA&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkImportSemaphoreZirconHandleFUCHSIA");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pImportSemaphoreZirconHandleInfo", &args.pImportSemaphoreZirconHandleInfo, "const VkImportSemaphoreZirconHandleInfoFUCHSIA*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetSemaphoreZirconHandleFUCHSIA(
    const ApiCallInfo&                          call_info,
    args::GetSemaphoreZirconHandleFUCHSIA&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetSemaphoreZirconHandleFUCHSIA");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetZirconHandleInfo", &args.pGetZirconHandleInfo, "const VkSemaphoreGetZirconHandleInfoFUCHSIA*");
    FieldToSqlite(statements, fieldInfo, 3, "pZirconHandle", args.pZirconHandle, "zx_handle_t*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdBindInvocationMaskHUAWEI(
    const ApiCallInfo&                          call_info,
    args::CmdBindInvocationMaskHUAWEI&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindInvocationMaskHUAWEI");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "imageView", "VkImageView", args.imageView);
    RecordField(
        statements, fieldInfo, 3, "imageLayout", "VkImageLayout", args.imageLayout);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetMemoryRemoteAddressNV(
    const ApiCallInfo&                          call_info,
    args::GetMemoryRemoteAddressNV&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryRemoteAddressNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pMemoryGetRemoteAddressInfo", &args.pMemoryGetRemoteAddressInfo, "const VkMemoryGetRemoteAddressInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pAddress", args.pAddress, "VkRemoteAddressNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetPatchControlPointsEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetPatchControlPointsEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPatchControlPointsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "patchControlPoints", "uint32_t", args.patchControlPoints);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRasterizerDiscardEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetRasterizerDiscardEnableEXT&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRasterizerDiscardEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "rasterizerDiscardEnable", "VkBool32", args.rasterizerDiscardEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthBiasEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthBiasEnableEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthBiasEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthBiasEnable", "VkBool32", args.depthBiasEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLogicOpEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetLogicOpEXT&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLogicOpEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "logicOp", "VkLogicOp", args.logicOp);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPrimitiveRestartEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetPrimitiveRestartEnableEXT&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPrimitiveRestartEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "primitiveRestartEnable", "VkBool32", args.primitiveRestartEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateScreenSurfaceQNX(
    const ApiCallInfo&                          call_info,
    args::CreateScreenSurfaceQNX&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateScreenSurfaceQNX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "instance", "VkInstance", args.instance);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkScreenSurfaceCreateInfoQNX*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSurface", &args.pSurface, "VkSurfaceKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
    RecordCreateSurface(&args.pSurface, &args.pCreateInfo, args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceScreenPresentationSupportQNX(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceScreenPresentationSupportQNX& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceScreenPresentationSupportQNX");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "window", args.window, "struct _screen_window*");

    statements.InsertApiEventReturns(this->block_index_, "VkBool32", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetColorWriteEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetColorWriteEnableEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetColorWriteEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 3, "pColorWriteEnables", args.pColorWriteEnables, "const VkBool32*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdDrawMultiEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMultiEXT&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMultiEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "drawCount", "uint32_t", args.drawCount);
    FieldToSqlite(statements, fieldInfo, 3, "pVertexInfo", &args.pVertexInfo, "const VkMultiDrawInfoEXT*");
    RecordField(
        statements, fieldInfo, 4, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 5, "firstInstance", "uint32_t", args.firstInstance);
    RecordField(
        statements, fieldInfo, 6, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDrawMultiIndexedEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMultiIndexedEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMultiIndexedEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "drawCount", "uint32_t", args.drawCount);
    FieldToSqlite(statements, fieldInfo, 3, "pIndexInfo", &args.pIndexInfo, "const VkMultiDrawIndexedInfoEXT*");
    RecordField(
        statements, fieldInfo, 4, "instanceCount", "uint32_t", args.instanceCount);
    RecordField(
        statements, fieldInfo, 5, "firstInstance", "uint32_t", args.firstInstance);
    RecordField(
        statements, fieldInfo, 6, "stride", "uint32_t", args.stride);
    FieldToSqlite(statements, fieldInfo, 7, "pVertexOffset", args.pVertexOffset, "const int32_t*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::CreateMicromapEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkMicromapCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pMicromap", &args.pMicromap, "VkMicromapEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyMicromapEXT&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "micromap", "VkMicromapEXT", args.micromap);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBuildMicromapsEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBuildMicromapsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pInfos", &args.pInfos, "const VkMicromapBuildInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkBuildMicromapsEXT(
    const ApiCallInfo&                          call_info,
    args::BuildMicromapsEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBuildMicromapsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    RecordField(
        statements, fieldInfo, 3, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pInfos", &args.pInfos, "const VkMicromapBuildInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::CopyMicromapEXT&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyMicromapInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    args::CopyMicromapToMemoryEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMicromapToMemoryEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyMicromapToMemoryInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::CopyMemoryToMicromapEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMemoryToMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyMemoryToMicromapInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkWriteMicromapsPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::WriteMicromapsPropertiesEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWriteMicromapsPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "micromapCount", "uint32_t", args.micromapCount);
    FieldToSqlite(statements, fieldInfo, 3, "pMicromaps", &args.pMicromaps, "const VkMicromapEXT*");
    RecordField(
        statements, fieldInfo, 4, "queryType", "VkQueryType", args.queryType);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");
    RecordField(
        statements, fieldInfo, 7, "stride", "size_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMicromapEXT&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyMicromapInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMicromapToMemoryEXT(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMicromapToMemoryEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMicromapToMemoryEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyMicromapToMemoryInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMemoryToMicromapEXT(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryToMicromapEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryToMicromapEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyMemoryToMicromapInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdWriteMicromapsPropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::CmdWriteMicromapsPropertiesEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteMicromapsPropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "micromapCount", "uint32_t", args.micromapCount);
    FieldToSqlite(statements, fieldInfo, 3, "pMicromaps", &args.pMicromaps, "const VkMicromapEXT*");
    RecordField(
        statements, fieldInfo, 4, "queryType", "VkQueryType", args.queryType);
    RecordField(
        statements, fieldInfo, 5, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 6, "firstQuery", "uint32_t", args.firstQuery);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetDeviceMicromapCompatibilityEXT(
    const ApiCallInfo&                          call_info,
    args::GetDeviceMicromapCompatibilityEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceMicromapCompatibilityEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pVersionInfo", &args.pVersionInfo, "const VkMicromapVersionInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pCompatibility", args.pCompatibility, "VkAccelerationStructureCompatibilityKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetMicromapBuildSizesEXT(
    const ApiCallInfo&                          call_info,
    args::GetMicromapBuildSizesEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMicromapBuildSizesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "buildType", "VkAccelerationStructureBuildTypeKHR", args.buildType);
    FieldToSqlite(statements, fieldInfo, 3, "pBuildInfo", &args.pBuildInfo, "const VkMicromapBuildInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 4, "pSizeInfo", &args.pSizeInfo, "VkMicromapBuildSizesInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdDrawClusterHUAWEI(
    const ApiCallInfo&                          call_info,
    args::CmdDrawClusterHUAWEI&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawClusterHUAWEI");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "groupCountX", "uint32_t", args.groupCountX);
    RecordField(
        statements, fieldInfo, 3, "groupCountY", "uint32_t", args.groupCountY);
    RecordField(
        statements, fieldInfo, 4, "groupCountZ", "uint32_t", args.groupCountZ);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd cluster recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdClusterRecordingId = statements.InsertCmdClusterRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    statements.InsertCmdClusterRecordingInfo(cmdClusterRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
}

void VulkanSqliteConsumer::Process_vkCmdDrawClusterIndirectHUAWEI(
    const ApiCallInfo&                          call_info,
    args::CmdDrawClusterIndirectHUAWEI&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawClusterIndirectHUAWEI");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd cluster recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdClusterRecordingId = statements.InsertCmdClusterRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    statements.InsertCmdClusterRecordingIndirectInfo(cmdClusterRecordingId, context.GetBufferId(args.buffer), args.offset);
}
void VulkanSqliteConsumer::Process_vkSetDeviceMemoryPriorityEXT(
    const ApiCallInfo&                          call_info,
    args::SetDeviceMemoryPriorityEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetDeviceMemoryPriorityEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "memory", "VkDeviceMemory", args.memory);
    RecordField(
        statements, fieldInfo, 3, "priority", "float", args.priority);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdSetDispatchParametersARM(
    const ApiCallInfo&                          call_info,
    args::CmdSetDispatchParametersARM&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDispatchParametersARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDispatchParameters", &args.pDispatchParameters, "const VkDispatchParametersARM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetDescriptorSetLayoutHostMappingInfoVALVE(
    const ApiCallInfo&                          call_info,
    args::GetDescriptorSetLayoutHostMappingInfoVALVE& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDescriptorSetLayoutHostMappingInfoVALVE");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pBindingReference", &args.pBindingReference, "const VkDescriptorSetBindingReferenceVALVE*");
    FieldToSqlite(statements, fieldInfo, 3, "pHostMapping", &args.pHostMapping, "VkDescriptorSetLayoutHostMappingInfoVALVE*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetDescriptorSetHostMappingVALVE(
    const ApiCallInfo&                          call_info,
    args::GetDescriptorSetHostMappingVALVE&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDescriptorSetHostMappingVALVE");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "descriptorSet", "VkDescriptorSet", args.descriptorSet);
    FieldToSqlite(statements, fieldInfo, 3, "ppData", args.ppData, "void**");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetPipelineIndirectMemoryRequirementsNV(
    const ApiCallInfo&                          call_info,
    args::GetPipelineIndirectMemoryRequirementsNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineIndirectMemoryRequirementsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkComputePipelineCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdUpdatePipelineIndirectBufferNV(
    const ApiCallInfo&                          call_info,
    args::CmdUpdatePipelineIndirectBufferNV&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdUpdatePipelineIndirectBufferNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineBindPoint", "VkPipelineBindPoint", args.pipelineBindPoint);
    RecordField(
        statements, fieldInfo, 3, "pipeline", "VkPipeline", args.pipeline);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetPipelineIndirectDeviceAddressNV(
    const ApiCallInfo&                          call_info,
    args::GetPipelineIndirectDeviceAddressNV&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPipelineIndirectDeviceAddressNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkPipelineIndirectDeviceAddressInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceAddress", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetDepthClampEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthClampEnableEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthClampEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthClampEnable", "VkBool32", args.depthClampEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetPolygonModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetPolygonModeEXT&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPolygonModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "polygonMode", "VkPolygonMode", args.polygonMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRasterizationSamplesEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetRasterizationSamplesEXT&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRasterizationSamplesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "rasterizationSamples", "VkSampleCountFlagBits", args.rasterizationSamples);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetSampleMaskEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetSampleMaskEXT&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetSampleMaskEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "samples", "VkSampleCountFlagBits", args.samples);
    FieldToSqlite(statements, fieldInfo, 3, "pSampleMask", args.pSampleMask, "const VkSampleMask*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetAlphaToCoverageEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetAlphaToCoverageEnableEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetAlphaToCoverageEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "alphaToCoverageEnable", "VkBool32", args.alphaToCoverageEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetAlphaToOneEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetAlphaToOneEnableEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetAlphaToOneEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "alphaToOneEnable", "VkBool32", args.alphaToOneEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLogicOpEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetLogicOpEnableEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLogicOpEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "logicOpEnable", "VkBool32", args.logicOpEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetColorBlendEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetColorBlendEnableEXT&            args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetColorBlendEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstAttachment", "uint32_t", args.firstAttachment);
    RecordField(
        statements, fieldInfo, 3, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 4, "pColorBlendEnables", args.pColorBlendEnables, "const VkBool32*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetColorBlendEquationEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetColorBlendEquationEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetColorBlendEquationEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstAttachment", "uint32_t", args.firstAttachment);
    RecordField(
        statements, fieldInfo, 3, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 4, "pColorBlendEquations", &args.pColorBlendEquations, "const VkColorBlendEquationEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetColorWriteMaskEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetColorWriteMaskEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetColorWriteMaskEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstAttachment", "uint32_t", args.firstAttachment);
    RecordField(
        statements, fieldInfo, 3, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 4, "pColorWriteMasks", args.pColorWriteMasks, "const VkColorComponentFlags*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetTessellationDomainOriginEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetTessellationDomainOriginEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetTessellationDomainOriginEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "domainOrigin", "VkTessellationDomainOrigin", args.domainOrigin);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRasterizationStreamEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetRasterizationStreamEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRasterizationStreamEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "rasterizationStream", "uint32_t", args.rasterizationStream);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetConservativeRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetConservativeRasterizationModeEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetConservativeRasterizationModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "conservativeRasterizationMode", "VkConservativeRasterizationModeEXT", args.conservativeRasterizationMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetExtraPrimitiveOverestimationSizeEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetExtraPrimitiveOverestimationSizeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "extraPrimitiveOverestimationSize", "float", args.extraPrimitiveOverestimationSize);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthClipEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthClipEnableEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthClipEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthClipEnable", "VkBool32", args.depthClipEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetSampleLocationsEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetSampleLocationsEnableEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetSampleLocationsEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "sampleLocationsEnable", "VkBool32", args.sampleLocationsEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetColorBlendAdvancedEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetColorBlendAdvancedEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetColorBlendAdvancedEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstAttachment", "uint32_t", args.firstAttachment);
    RecordField(
        statements, fieldInfo, 3, "attachmentCount", "uint32_t", args.attachmentCount);
    FieldToSqlite(statements, fieldInfo, 4, "pColorBlendAdvanced", &args.pColorBlendAdvanced, "const VkColorBlendAdvancedEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetProvokingVertexModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetProvokingVertexModeEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetProvokingVertexModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "provokingVertexMode", "VkProvokingVertexModeEXT", args.provokingVertexMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLineRasterizationModeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineRasterizationModeEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineRasterizationModeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "lineRasterizationMode", "VkLineRasterizationModeEXT", args.lineRasterizationMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetLineStippleEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetLineStippleEnableEXT&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetLineStippleEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stippledLineEnable", "VkBool32", args.stippledLineEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthClipNegativeOneToOneEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthClipNegativeOneToOneEXT&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthClipNegativeOneToOneEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "negativeOneToOne", "VkBool32", args.negativeOneToOne);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetViewportWScalingEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportWScalingEnableNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportWScalingEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "viewportWScalingEnable", "VkBool32", args.viewportWScalingEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetViewportSwizzleNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetViewportSwizzleNV&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetViewportSwizzleNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "firstViewport", "uint32_t", args.firstViewport);
    RecordField(
        statements, fieldInfo, 3, "viewportCount", "uint32_t", args.viewportCount);
    FieldToSqlite(statements, fieldInfo, 4, "pViewportSwizzles", &args.pViewportSwizzles, "const VkViewportSwizzleNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageToColorEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageToColorEnableNV&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageToColorEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageToColorEnable", "VkBool32", args.coverageToColorEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageToColorLocationNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageToColorLocationNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageToColorLocationNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageToColorLocation", "uint32_t", args.coverageToColorLocation);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageModulationModeNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageModulationModeNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageModulationModeNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageModulationMode", "VkCoverageModulationModeNV", args.coverageModulationMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageModulationTableEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageModulationTableEnableNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageModulationTableEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageModulationTableEnable", "VkBool32", args.coverageModulationTableEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageModulationTableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageModulationTableNV&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageModulationTableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageModulationTableCount", "uint32_t", args.coverageModulationTableCount);
    FieldToSqlite(statements, fieldInfo, 3, "pCoverageModulationTable", args.pCoverageModulationTable, "const float*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetShadingRateImageEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetShadingRateImageEnableNV&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetShadingRateImageEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "shadingRateImageEnable", "VkBool32", args.shadingRateImageEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetRepresentativeFragmentTestEnableNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetRepresentativeFragmentTestEnableNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRepresentativeFragmentTestEnableNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "representativeFragmentTestEnable", "VkBool32", args.representativeFragmentTestEnable);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdSetCoverageReductionModeNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetCoverageReductionModeNV&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetCoverageReductionModeNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "coverageReductionMode", "VkCoverageReductionModeNV", args.coverageReductionMode);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateTensorARM(
    const ApiCallInfo&                          call_info,
    args::CreateTensorARM&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateTensorARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkTensorCreateInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pTensor", &args.pTensor, "VkTensorARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyTensorARM(
    const ApiCallInfo&                          call_info,
    args::DestroyTensorARM&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyTensorARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "tensor", "VkTensorARM", args.tensor);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCreateTensorViewARM(
    const ApiCallInfo&                          call_info,
    args::CreateTensorViewARM&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateTensorViewARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkTensorViewCreateInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pView", &args.pView, "VkTensorViewARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyTensorViewARM(
    const ApiCallInfo&                          call_info,
    args::DestroyTensorViewARM&                 args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyTensorViewARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "tensorView", "VkTensorViewARM", args.tensorView);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetTensorMemoryRequirementsARM(
    const ApiCallInfo&                          call_info,
    args::GetTensorMemoryRequirementsARM&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetTensorMemoryRequirementsARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkTensorMemoryRequirementsInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkBindTensorMemoryARM(
    const ApiCallInfo&                          call_info,
    args::BindTensorMemoryARM&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindTensorMemoryARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindTensorMemoryInfoARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDeviceTensorMemoryRequirementsARM(
    const ApiCallInfo&                          call_info,
    args::GetDeviceTensorMemoryRequirementsARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceTensorMemoryRequirementsARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDeviceTensorMemoryRequirementsARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdCopyTensorARM(
    const ApiCallInfo&                          call_info,
    args::CmdCopyTensorARM&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyTensorARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pCopyTensorInfo", &args.pCopyTensorInfo, "const VkCopyTensorInfoARM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceExternalTensorPropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceExternalTensorPropertiesARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceExternalTensorPropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pExternalTensorInfo", &args.pExternalTensorInfo, "const VkPhysicalDeviceExternalTensorInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pExternalTensorProperties", &args.pExternalTensorProperties, "VkExternalTensorPropertiesARM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetShaderModuleIdentifierEXT(
    const ApiCallInfo&                          call_info,
    args::GetShaderModuleIdentifierEXT&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetShaderModuleIdentifierEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "shaderModule", "VkShaderModule", args.shaderModule);
    FieldToSqlite(statements, fieldInfo, 3, "pIdentifier", &args.pIdentifier, "VkShaderModuleIdentifierEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetShaderModuleCreateInfoIdentifierEXT(
    const ApiCallInfo&                          call_info,
    args::GetShaderModuleCreateInfoIdentifierEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetShaderModuleCreateInfoIdentifierEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkShaderModuleCreateInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pIdentifier", &args.pIdentifier, "VkShaderModuleIdentifierEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceOpticalFlowImageFormatsNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceOpticalFlowImageFormatsNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceOpticalFlowImageFormatsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pOpticalFlowImageFormatInfo", &args.pOpticalFlowImageFormatInfo, "const VkOpticalFlowImageFormatInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pFormatCount", args.pFormatCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pImageFormatProperties", &args.pImageFormatProperties, "VkOpticalFlowImageFormatPropertiesNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    args::CreateOpticalFlowSessionNV&           args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateOpticalFlowSessionNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkOpticalFlowSessionCreateInfoNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSession", &args.pSession, "VkOpticalFlowSessionNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyOpticalFlowSessionNV(
    const ApiCallInfo&                          call_info,
    args::DestroyOpticalFlowSessionNV&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyOpticalFlowSessionNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "session", "VkOpticalFlowSessionNV", args.session);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkBindOpticalFlowSessionImageNV(
    const ApiCallInfo&                          call_info,
    args::BindOpticalFlowSessionImageNV&        args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindOpticalFlowSessionImageNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "session", "VkOpticalFlowSessionNV", args.session);
    RecordField(
        statements, fieldInfo, 3, "bindingPoint", "VkOpticalFlowSessionBindingPointNV", args.bindingPoint);
    RecordField(
        statements, fieldInfo, 4, "view", "VkImageView", args.view);
    RecordField(
        statements, fieldInfo, 5, "layout", "VkImageLayout", args.layout);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdOpticalFlowExecuteNV(
    const ApiCallInfo&                          call_info,
    args::CmdOpticalFlowExecuteNV&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdOpticalFlowExecuteNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "session", "VkOpticalFlowSessionNV", args.session);
    FieldToSqlite(statements, fieldInfo, 3, "pExecuteInfo", &args.pExecuteInfo, "const VkOpticalFlowExecuteInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkAntiLagUpdateAMD(
    const ApiCallInfo&                          call_info,
    args::AntiLagUpdateAMD&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkAntiLagUpdateAMD");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pData", &args.pData, "const VkAntiLagDataAMD*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateShadersEXT(
    const ApiCallInfo&                          call_info,
    args::CreateShadersEXT&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateShadersEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pCreateInfos", &args.pCreateInfos, "const VkShaderCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 4, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 5, "pShaders", &args.pShaders, "VkShaderEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyShaderEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyShaderEXT&                     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyShaderEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "shader", "VkShaderEXT", args.shader);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetShaderBinaryDataEXT(
    const ApiCallInfo&                          call_info,
    args::GetShaderBinaryDataEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetShaderBinaryDataEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "shader", "VkShaderEXT", args.shader);
    FieldToSqlite(statements, fieldInfo, 3, "pDataSize", args.pDataSize, "size_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdBindShadersEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBindShadersEXT&                    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindShadersEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "stageCount", "uint32_t", args.stageCount);
    FieldToSqlite(statements, fieldInfo, 3, "pStages", args.pStages, "const VkShaderStageFlagBits*");
    FieldToSqlite(statements, fieldInfo, 4, "pShaders", &args.pShaders, "const VkShaderEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto [shadersValid, shaders, shadersCount] = GetHandleArray(&args.pShaders);
    auto [stagesValid, stages, stagesCount] = GetPointerArray(&args.pStages);
    if (!stagesValid)
    {
        GFXRECON_SQLITE_LOG_WARNING("Failed to bind shader objects, invalid pStages");
        return;
    }    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to bind shader object, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    if (shadersValid && shadersCount != stagesCount) {
        GFXRECON_SQLITE_LOG_WARNING("pShaders and pStages counts do not match, using min");
    }
    std::unordered_set<VkPipelineBindPoint> bindPointsToClear;
    for (size_t i = 0; i < (shadersValid ? std::min(shadersCount, stagesCount) : stagesCount); ++i)
    {
        auto shader = shadersValid ? shaders[i] : format::kNullHandleId;
        auto stage = stages[i];
        switch(stage)
        {
            case VK_SHADER_STAGE_ALL:
                {
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_GRAPHICS);
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_COMPUTE);
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX);
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
                    break;
                }
            case VK_SHADER_STAGE_VERTEX_BIT:
            case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            case VK_SHADER_STAGE_GEOMETRY_BIT:
            case VK_SHADER_STAGE_FRAGMENT_BIT:
            case VK_SHADER_STAGE_TASK_BIT_EXT:
            case VK_SHADER_STAGE_MESH_BIT_EXT:
            case VK_SHADER_STAGE_CLUSTER_CULLING_BIT_HUAWEI:
            case VK_SHADER_STAGE_ALL_GRAPHICS:
                {
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_GRAPHICS);
                    break;
                }
            case VK_SHADER_STAGE_COMPUTE_BIT:
                {
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_COMPUTE);
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_EXECUTION_GRAPH_AMDX);
                    break;
                }
            case VK_SHADER_STAGE_ANY_HIT_BIT_KHR:
            case VK_SHADER_STAGE_CALLABLE_BIT_KHR:
            case VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR:
            case VK_SHADER_STAGE_INTERSECTION_BIT_KHR:
            case VK_SHADER_STAGE_MISS_BIT_KHR:
            case VK_SHADER_STAGE_RAYGEN_BIT_KHR:
                {
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR);
                    break;
                }
            case VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI:
                {
                    bindPointsToClear.insert(VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI);
                    break;
                }
            default:
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to clear bind points, unsupported shader stage %" PRIu64,
                    stage
                );
        }
        if (shader)
        {
            auto shaderIter = context.shaderObjectHandleToId.find(ToInt64(shader));
            if (shaderIter == context.shaderObjectHandleToId.end())
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to bind shader, failed to find shader with handle %" PRIi64,
                    shader
                );
                continue;
            }

            statements.InsertStateShaderObjectBinding(this->block_index_, commandBufferRecordingIter->second, shaderIter->second, stage);
        }
        else
        {
            // clear any existing shader binding for the stage since the shader was a VK_NULL_HANDLE
            auto shaderBindingsIter = context.commandBufferRecordingShaderObjectBindings.find(commandBufferRecordingIter->second);
            if (shaderBindingsIter != context.commandBufferRecordingShaderObjectBindings.end())
            {
                shaderBindingsIter->second.erase(stage);
                if (shaderBindingsIter->second.empty())
                {
                    context.commandBufferRecordingShaderObjectBindings.erase(shaderBindingsIter);
                    context.commandBufferRecordingWithDirtyState.insert(commandBufferRecordingIter->second);
                }
            }
        }
    }

    // binding shader objects will reset any previous pipeline binding so clear that now
    auto pipelineBindingsIter = context.commandBufferRecordingPipelineBindings.find(commandBufferRecordingIter->second);
    if (pipelineBindingsIter != context.commandBufferRecordingPipelineBindings.end())
    {
        for (auto bindPoint : bindPointsToClear)
        {
            pipelineBindingsIter->second.erase(bindPoint);
        }
        if (pipelineBindingsIter->second.empty())
        {
            context.commandBufferRecordingPipelineBindings.erase(pipelineBindingsIter);
        }
        context.commandBufferRecordingWithDirtyState.insert(commandBufferRecordingIter->second);
    }
}

void VulkanSqliteConsumer::Process_vkCmdSetDepthClampRangeEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetDepthClampRangeEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetDepthClampRangeEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "depthClampMode", "VkDepthClampModeEXT", args.depthClampMode);
    FieldToSqlite(statements, fieldInfo, 3, "pDepthClampRange", &args.pDepthClampRange, "const VkDepthClampRangeEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetFramebufferTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    args::GetFramebufferTilePropertiesQCOM&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetFramebufferTilePropertiesQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "framebuffer", "VkFramebuffer", args.framebuffer);
    FieldToSqlite(statements, fieldInfo, 3, "pPropertiesCount", args.pPropertiesCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkTilePropertiesQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDynamicRenderingTilePropertiesQCOM(
    const ApiCallInfo&                          call_info,
    args::GetDynamicRenderingTilePropertiesQCOM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDynamicRenderingTilePropertiesQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingInfo", &args.pRenderingInfo, "const VkRenderingInfo*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkTilePropertiesQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCooperativeVectorPropertiesNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCooperativeVectorPropertiesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCooperativeVectorPropertiesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkCooperativeVectorPropertiesNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    args::ConvertCooperativeVectorMatrixNV&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkConvertCooperativeVectorMatrixNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkConvertCooperativeVectorMatrixInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdConvertCooperativeVectorMatrixNV(
    const ApiCallInfo&                          call_info,
    args::CmdConvertCooperativeVectorMatrixNV&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdConvertCooperativeVectorMatrixNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pInfos", &args.pInfos, "const VkConvertCooperativeVectorMatrixInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkSetLatencySleepModeNV(
    const ApiCallInfo&                          call_info,
    args::SetLatencySleepModeNV&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetLatencySleepModeNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pSleepModeInfo", &args.pSleepModeInfo, "const VkLatencySleepModeInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkLatencySleepNV(
    const ApiCallInfo&                          call_info,
    args::LatencySleepNV&                       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkLatencySleepNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pSleepInfo", &args.pSleepInfo, "const VkLatencySleepInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkSetLatencyMarkerNV(
    const ApiCallInfo&                          call_info,
    args::SetLatencyMarkerNV&                   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkSetLatencyMarkerNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pLatencyMarkerInfo", &args.pLatencyMarkerInfo, "const VkSetLatencyMarkerInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetLatencyTimingsNV(
    const ApiCallInfo&                          call_info,
    args::GetLatencyTimingsNV&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetLatencyTimingsNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "swapchain", "VkSwapchainKHR", args.swapchain);
    FieldToSqlite(statements, fieldInfo, 3, "pLatencyMarkerInfo", &args.pLatencyMarkerInfo, "VkGetLatencyMarkerInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkQueueNotifyOutOfBandNV(
    const ApiCallInfo&                          call_info,
    args::QueueNotifyOutOfBandNV&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkQueueNotifyOutOfBandNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "queue", "VkQueue", args.queue);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueTypeInfo", &args.pQueueTypeInfo, "const VkOutOfBandQueueTypeInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCreateDataGraphPipelinesARM(
    const ApiCallInfo&                          call_info,
    args::CreateDataGraphPipelinesARM&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDataGraphPipelinesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    RecordField(
        statements, fieldInfo, 3, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    RecordField(
        statements, fieldInfo, 4, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 5, "pCreateInfos", &args.pCreateInfos, "const VkDataGraphPipelineCreateInfoARM*");
    FieldToSqlite(statements, fieldInfo, 6, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 7, "pPipelines", &args.pPipelines, "VkPipeline*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCreateDataGraphPipelineSessionARM(
    const ApiCallInfo&                          call_info,
    args::CreateDataGraphPipelineSessionARM&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateDataGraphPipelineSessionARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkDataGraphPipelineSessionCreateInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pSession", &args.pSession, "VkDataGraphPipelineSessionARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDataGraphPipelineSessionBindPointRequirementsARM(
    const ApiCallInfo&                          call_info,
    args::GetDataGraphPipelineSessionBindPointRequirementsARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDataGraphPipelineSessionBindPointRequirementsARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDataGraphPipelineSessionBindPointRequirementsInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pBindPointRequirementCount", args.pBindPointRequirementCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pBindPointRequirements", &args.pBindPointRequirements, "VkDataGraphPipelineSessionBindPointRequirementARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDataGraphPipelineSessionMemoryRequirementsARM(
    const ApiCallInfo&                          call_info,
    args::GetDataGraphPipelineSessionMemoryRequirementsARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDataGraphPipelineSessionMemoryRequirementsARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkDataGraphPipelineSessionMemoryRequirementsInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkBindDataGraphPipelineSessionMemoryARM(
    const ApiCallInfo&                          call_info,
    args::BindDataGraphPipelineSessionMemoryARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBindDataGraphPipelineSessionMemoryARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "bindInfoCount", "uint32_t", args.bindInfoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pBindInfos", &args.pBindInfos, "const VkBindDataGraphPipelineSessionMemoryInfoARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyDataGraphPipelineSessionARM(
    const ApiCallInfo&                          call_info,
    args::DestroyDataGraphPipelineSessionARM&   args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyDataGraphPipelineSessionARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "session", "VkDataGraphPipelineSessionARM", args.session);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdDispatchDataGraphARM(
    const ApiCallInfo&                          call_info,
    args::CmdDispatchDataGraphARM&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDispatchDataGraphARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "session", "VkDataGraphPipelineSessionARM", args.session);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkDataGraphPipelineDispatchInfoARM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetDataGraphPipelineAvailablePropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetDataGraphPipelineAvailablePropertiesARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDataGraphPipelineAvailablePropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pPipelineInfo", &args.pPipelineInfo, "const VkDataGraphPipelineInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pPropertiesCount", args.pPropertiesCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", args.pProperties, "VkDataGraphPipelinePropertyARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetDataGraphPipelinePropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetDataGraphPipelinePropertiesARM&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDataGraphPipelinePropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pPipelineInfo", &args.pPipelineInfo, "const VkDataGraphPipelineInfoARM*");
    RecordField(
        statements, fieldInfo, 3, "propertiesCount", "uint32_t", args.propertiesCount);
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkDataGraphPipelinePropertyQueryResultARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyDataGraphPropertyCount", args.pQueueFamilyDataGraphPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pQueueFamilyDataGraphProperties", &args.pQueueFamilyDataGraphProperties, "VkQueueFamilyDataGraphPropertiesARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pQueueFamilyDataGraphProcessingEngineInfo", &args.pQueueFamilyDataGraphProcessingEngineInfo, "const VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM*");
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyDataGraphProcessingEngineProperties", &args.pQueueFamilyDataGraphProcessingEngineProperties, "VkQueueFamilyDataGraphProcessingEnginePropertiesARM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdSetAttachmentFeedbackLoopEnableEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetAttachmentFeedbackLoopEnableEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetAttachmentFeedbackLoopEnableEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "aspectMask", "VkImageAspectFlags", args.aspectMask);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdBindTileMemoryQCOM(
    const ApiCallInfo&                          call_info,
    args::CmdBindTileMemoryQCOM&                args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBindTileMemoryQCOM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pTileMemoryBindInfo", &args.pTileMemoryBindInfo, "const VkTileMemoryBindInfoQCOM*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdDecompressMemoryEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDecompressMemoryEXT&               args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDecompressMemoryEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pDecompressMemoryInfoEXT", &args.pDecompressMemoryInfoEXT, "const VkDecompressMemoryInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdDecompressMemoryIndirectCountEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDecompressMemoryIndirectCountEXT&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDecompressMemoryIndirectCountEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "decompressionMethod", "VkMemoryDecompressionMethodFlagsEXT", args.decompressionMethod);
    RecordField(
        statements, fieldInfo, 3, "indirectCommandsAddress", "VkDeviceAddress", args.indirectCommandsAddress);
    RecordField(
        statements, fieldInfo, 4, "indirectCommandsCountAddress", "VkDeviceAddress", args.indirectCommandsCountAddress);
    RecordField(
        statements, fieldInfo, 5, "maxDecompressionCount", "uint32_t", args.maxDecompressionCount);
    RecordField(
        statements, fieldInfo, 6, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetPartitionedAccelerationStructuresBuildSizesNV(
    const ApiCallInfo&                          call_info,
    args::GetPartitionedAccelerationStructuresBuildSizesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPartitionedAccelerationStructuresBuildSizesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkPartitionedAccelerationStructureInstancesInputNV*");
    FieldToSqlite(statements, fieldInfo, 3, "pSizeInfo", &args.pSizeInfo, "VkAccelerationStructureBuildSizesInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBuildPartitionedAccelerationStructuresNV(
    const ApiCallInfo&                          call_info,
    args::CmdBuildPartitionedAccelerationStructuresNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBuildPartitionedAccelerationStructuresNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBuildInfo", &args.pBuildInfo, "const VkBuildPartitionedAccelerationStructureInfoNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetGeneratedCommandsMemoryRequirementsEXT(
    const ApiCallInfo&                          call_info,
    args::GetGeneratedCommandsMemoryRequirementsEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetGeneratedCommandsMemoryRequirementsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkGeneratedCommandsMemoryRequirementsInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pMemoryRequirements", &args.pMemoryRequirements, "VkMemoryRequirements2*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdPreprocessGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    args::CmdPreprocessGeneratedCommandsEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdPreprocessGeneratedCommandsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pGeneratedCommandsInfo", &args.pGeneratedCommandsInfo, "const VkGeneratedCommandsInfoEXT*");
    RecordField(
        statements, fieldInfo, 3, "stateCommandBuffer", "VkCommandBuffer", args.stateCommandBuffer);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdExecuteGeneratedCommandsEXT(
    const ApiCallInfo&                          call_info,
    args::CmdExecuteGeneratedCommandsEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdExecuteGeneratedCommandsEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "isPreprocessed", "VkBool32", args.isPreprocessed);
    FieldToSqlite(statements, fieldInfo, 3, "pGeneratedCommandsInfo", &args.pGeneratedCommandsInfo, "const VkGeneratedCommandsInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCreateIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    args::CreateIndirectCommandsLayoutEXT&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateIndirectCommandsLayoutEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkIndirectCommandsLayoutCreateInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pIndirectCommandsLayout", &args.pIndirectCommandsLayout, "VkIndirectCommandsLayoutEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyIndirectCommandsLayoutEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyIndirectCommandsLayoutEXT&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyIndirectCommandsLayoutEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "indirectCommandsLayout", "VkIndirectCommandsLayoutEXT", args.indirectCommandsLayout);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkDestroyIndirectExecutionSetEXT(
    const ApiCallInfo&                          call_info,
    args::DestroyIndirectExecutionSetEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyIndirectExecutionSetEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "indirectExecutionSet", "VkIndirectExecutionSetEXT", args.indirectExecutionSet);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkUpdateIndirectExecutionSetPipelineEXT(
    const ApiCallInfo&                          call_info,
    args::UpdateIndirectExecutionSetPipelineEXT& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUpdateIndirectExecutionSetPipelineEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "indirectExecutionSet", "VkIndirectExecutionSetEXT", args.indirectExecutionSet);
    RecordField(
        statements, fieldInfo, 3, "executionSetWriteCount", "uint32_t", args.executionSetWriteCount);
    FieldToSqlite(statements, fieldInfo, 4, "pExecutionSetWrites", &args.pExecutionSetWrites, "const VkWriteIndirectExecutionSetPipelineEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkUpdateIndirectExecutionSetShaderEXT(
    const ApiCallInfo&                          call_info,
    args::UpdateIndirectExecutionSetShaderEXT&  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkUpdateIndirectExecutionSetShaderEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "indirectExecutionSet", "VkIndirectExecutionSetEXT", args.indirectExecutionSet);
    RecordField(
        statements, fieldInfo, 3, "executionSetWriteCount", "uint32_t", args.executionSetWriteCount);
    FieldToSqlite(statements, fieldInfo, 4, "pExecutionSetWrites", &args.pExecutionSetWrites, "const VkWriteIndirectExecutionSetShaderEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    FieldToSqlite(statements, fieldInfo, 2, "pPropertyCount", args.pPropertyCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 3, "pProperties", &args.pProperties, "VkCooperativeMatrixFlexibleDimensionsPropertiesNV*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkGetMemoryMetalHandleEXT(
    const ApiCallInfo&                          call_info,
    args::GetMemoryMetalHandleEXT&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryMetalHandleEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pGetMetalHandleInfo", &args.pGetMetalHandleInfo, "const VkMemoryGetMetalHandleInfoEXT*");
    FieldToSqlite(statements, fieldInfo, 3, "pHandle", args.pHandle, "void**");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetMemoryMetalHandlePropertiesEXT(
    const ApiCallInfo&                          call_info,
    args::GetMemoryMetalHandlePropertiesEXT&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetMemoryMetalHandlePropertiesEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "handleType", "VkExternalMemoryHandleTypeFlagBits", args.handleType);
    FieldToSqlite(statements, fieldInfo, 3, "pHandle", args.pHandle, "const void*");
    FieldToSqlite(statements, fieldInfo, 4, "pMemoryMetalHandleProperties", &args.pMemoryMetalHandleProperties, "VkMemoryMetalHandlePropertiesEXT*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(
    const ApiCallInfo&                          call_info,
    args::EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pCounterCount", args.pCounterCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 4, "pCounters", &args.pCounters, "VkPerformanceCounterARM*");
    FieldToSqlite(statements, fieldInfo, 5, "pCounterDescriptions", &args.pCounterDescriptions, "VkPerformanceCounterDescriptionARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdEndRendering2EXT(
    const ApiCallInfo&                          call_info,
    args::CmdEndRendering2EXT&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdEndRendering2EXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRenderingEndInfo", &args.pRenderingEndInfo, "const VkRenderingEndInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdBeginCustomResolveEXT(
    const ApiCallInfo&                          call_info,
    args::CmdBeginCustomResolveEXT&             args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBeginCustomResolveEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pBeginCustomResolveInfo", &args.pBeginCustomResolveInfo, "const VkBeginCustomResolveInfoEXT*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyDataGraphProperties", &args.pQueueFamilyDataGraphProperties, "const VkQueueFamilyDataGraphPropertiesARM*");
    FieldToSqlite(statements, fieldInfo, 4, "pOpticalFlowImageFormatInfo", &args.pOpticalFlowImageFormatInfo, "const VkDataGraphOpticalFlowImageFormatInfoARM*");
    FieldToSqlite(statements, fieldInfo, 5, "pFormatCount", args.pFormatCount, "uint32_t*");
    FieldToSqlite(statements, fieldInfo, 6, "pImageFormatProperties", &args.pImageFormatProperties, "VkDataGraphOpticalFlowImageFormatPropertiesARM*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(
    const ApiCallInfo&                          call_info,
    args::GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "physicalDevice", "VkPhysicalDevice", args.physicalDevice);
    RecordField(
        statements, fieldInfo, 2, "queueFamilyIndex", "uint32_t", args.queueFamilyIndex);
    FieldToSqlite(statements, fieldInfo, 3, "pQueueFamilyDataGraphProperties", &args.pQueueFamilyDataGraphProperties, "const VkQueueFamilyDataGraphPropertiesARM*");
    FieldToSqlite(statements, fieldInfo, 4, "pProperties", &args.pProperties, "VkBaseOutStructure*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}
void VulkanSqliteConsumer::Process_vkCmdSetComputeOccupancyPriorityNV(
    const ApiCallInfo&                          call_info,
    args::CmdSetComputeOccupancyPriorityNV&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetComputeOccupancyPriorityNV");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pParameters", &args.pParameters, "const VkComputeOccupancyPriorityParametersNV*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdSetPrimitiveRestartIndexEXT(
    const ApiCallInfo&                          call_info,
    args::CmdSetPrimitiveRestartIndexEXT&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetPrimitiveRestartIndexEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "primitiveRestartIndex", "uint32_t", args.primitiveRestartIndex);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCreateAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::CreateAccelerationStructureKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pCreateInfo", &args.pCreateInfo, "const VkAccelerationStructureCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 4, "pAccelerationStructure", &args.pAccelerationStructure, "VkAccelerationStructureKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkDestroyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::DestroyAccelerationStructureKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkDestroyAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructure", "VkAccelerationStructureKHR", args.accelerationStructure);
    FieldToSqlite(statements, fieldInfo, 3, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkCmdBuildAccelerationStructuresKHR(
    const ApiCallInfo&                          call_info,
    args::CmdBuildAccelerationStructuresKHR&    args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdBuildAccelerationStructuresKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pInfos", &args.pInfos, "const VkAccelerationStructureBuildGeometryInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "ppBuildRangeInfos", &args.ppBuildRangeInfos, "const VkAccelerationStructureBuildRangeInfoKHR* const*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkBuildAccelerationStructuresKHR(
    const ApiCallInfo&                          call_info,
    args::BuildAccelerationStructuresKHR&       args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkBuildAccelerationStructuresKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    RecordField(
        statements, fieldInfo, 3, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 4, "pInfos", &args.pInfos, "const VkAccelerationStructureBuildGeometryInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 5, "ppBuildRangeInfos", &args.ppBuildRangeInfos, "const VkAccelerationStructureBuildRangeInfoKHR* const*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::CopyAccelerationStructureKHR&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyAccelerationStructureInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CopyAccelerationStructureToMemoryKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyAccelerationStructureToMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyAccelerationStructureToMemoryInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::CopyMemoryToAccelerationStructureKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCopyMemoryToAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    FieldToSqlite(statements, fieldInfo, 3, "pInfo", &args.pInfo, "const VkCopyMemoryToAccelerationStructureInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkWriteAccelerationStructuresPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::WriteAccelerationStructuresPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkWriteAccelerationStructuresPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructureCount", "uint32_t", args.accelerationStructureCount);
    FieldToSqlite(statements, fieldInfo, 3, "pAccelerationStructures", &args.pAccelerationStructures, "const VkAccelerationStructureKHR*");
    RecordField(
        statements, fieldInfo, 4, "queryType", "VkQueryType", args.queryType);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");
    RecordField(
        statements, fieldInfo, 7, "stride", "size_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdCopyAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyAccelerationStructureKHR&      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyAccelerationStructureInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyAccelerationStructureToMemoryKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyAccelerationStructureToMemoryKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyAccelerationStructureToMemoryKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyAccelerationStructureToMemoryInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkCmdCopyMemoryToAccelerationStructureKHR(
    const ApiCallInfo&                          call_info,
    args::CmdCopyMemoryToAccelerationStructureKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdCopyMemoryToAccelerationStructureKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkCopyMemoryToAccelerationStructureInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetAccelerationStructureDeviceAddressKHR(
    const ApiCallInfo&                          call_info,
    args::GetAccelerationStructureDeviceAddressKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetAccelerationStructureDeviceAddressKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pInfo", &args.pInfo, "const VkAccelerationStructureDeviceAddressInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceAddress", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdWriteAccelerationStructuresPropertiesKHR(
    const ApiCallInfo&                          call_info,
    args::CmdWriteAccelerationStructuresPropertiesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdWriteAccelerationStructuresPropertiesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "accelerationStructureCount", "uint32_t", args.accelerationStructureCount);
    FieldToSqlite(statements, fieldInfo, 3, "pAccelerationStructures", &args.pAccelerationStructures, "const VkAccelerationStructureKHR*");
    RecordField(
        statements, fieldInfo, 4, "queryType", "VkQueryType", args.queryType);
    RecordField(
        statements, fieldInfo, 5, "queryPool", "VkQueryPool", args.queryPool);
    RecordField(
        statements, fieldInfo, 6, "firstQuery", "uint32_t", args.firstQuery);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    RecordTrackedCmdCommand(context, statements, this->block_index_, args.commandBuffer);
}

void VulkanSqliteConsumer::Process_vkGetDeviceAccelerationStructureCompatibilityKHR(
    const ApiCallInfo&                          call_info,
    args::GetDeviceAccelerationStructureCompatibilityKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetDeviceAccelerationStructureCompatibilityKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    FieldToSqlite(statements, fieldInfo, 2, "pVersionInfo", &args.pVersionInfo, "const VkAccelerationStructureVersionInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pCompatibility", args.pCompatibility, "VkAccelerationStructureCompatibilityKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumer::Process_vkGetAccelerationStructureBuildSizesKHR(
    const ApiCallInfo&                          call_info,
    args::GetAccelerationStructureBuildSizesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetAccelerationStructureBuildSizesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "buildType", "VkAccelerationStructureBuildTypeKHR", args.buildType);
    FieldToSqlite(statements, fieldInfo, 3, "pBuildInfo", &args.pBuildInfo, "const VkAccelerationStructureBuildGeometryInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pMaxPrimitiveCounts", args.pMaxPrimitiveCounts, "const uint32_t*");
    FieldToSqlite(statements, fieldInfo, 5, "pSizeInfo", &args.pSizeInfo, "VkAccelerationStructureBuildSizesInfoKHR*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}
void VulkanSqliteConsumer::Process_vkCmdTraceRaysKHR(
    const ApiCallInfo&                          call_info,
    args::CmdTraceRaysKHR&                      args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdTraceRaysKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRaygenShaderBindingTable", &args.pRaygenShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pMissShaderBindingTable", &args.pMissShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pHitShaderBindingTable", &args.pHitShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 5, "pCallableShaderBindingTable", &args.pCallableShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    RecordField(
        statements, fieldInfo, 6, "width", "uint32_t", args.width);
    RecordField(
        statements, fieldInfo, 7, "height", "uint32_t", args.height);
    RecordField(
        statements, fieldInfo, 8, "depth", "uint32_t", args.depth);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd raytracing recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertCmdRaytracingRecording(this->block_index_, commandBufferRecordingIter->second);
}

void VulkanSqliteConsumer::Process_vkCreateRayTracingPipelinesKHR(
    const ApiCallInfo&                          call_info,
    args::CreateRayTracingPipelinesKHR&         args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCreateRayTracingPipelinesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "deferredOperation", "VkDeferredOperationKHR", args.deferredOperation);
    RecordField(
        statements, fieldInfo, 3, "pipelineCache", "VkPipelineCache", args.pipelineCache);
    RecordField(
        statements, fieldInfo, 4, "createInfoCount", "uint32_t", args.createInfoCount);
    FieldToSqlite(statements, fieldInfo, 5, "pCreateInfos", &args.pCreateInfos, "const VkRayTracingPipelineCreateInfoKHR*");
    FieldToSqlite(statements, fieldInfo, 6, "pAllocator", &args.pAllocator, "const VkAllocationCallbacks*");
    FieldToSqlite(statements, fieldInfo, 7, "pPipelines", &args.pPipelines, "VkPipeline*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(
    const ApiCallInfo&                          call_info,
    args::GetRayTracingCaptureReplayShaderGroupHandlesKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRayTracingCaptureReplayShaderGroupHandlesKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "firstGroup", "uint32_t", args.firstGroup);
    RecordField(
        statements, fieldInfo, 4, "groupCount", "uint32_t", args.groupCount);
    RecordField(
        statements, fieldInfo, 5, "dataSize", "size_t", args.dataSize);
    FieldToSqlite(statements, fieldInfo, 6, "pData", args.pData, "void*");

    statements.InsertApiEventReturns(this->block_index_, "VkResult", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdTraceRaysIndirectKHR(
    const ApiCallInfo&                          call_info,
    args::CmdTraceRaysIndirectKHR&              args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdTraceRaysIndirectKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    FieldToSqlite(statements, fieldInfo, 2, "pRaygenShaderBindingTable", &args.pRaygenShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 3, "pMissShaderBindingTable", &args.pMissShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 4, "pHitShaderBindingTable", &args.pHitShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    FieldToSqlite(statements, fieldInfo, 5, "pCallableShaderBindingTable", &args.pCallableShaderBindingTable, "const VkStridedDeviceAddressRegionKHR*");
    RecordField(
        statements, fieldInfo, 6, "indirectDeviceAddress", "VkDeviceAddress", args.indirectDeviceAddress);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd raytracing recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    statements.InsertCmdRaytracingRecording(this->block_index_, commandBufferRecordingIter->second);
}

void VulkanSqliteConsumer::Process_vkGetRayTracingShaderGroupStackSizeKHR(
    const ApiCallInfo&                          call_info,
    args::GetRayTracingShaderGroupStackSizeKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkGetRayTracingShaderGroupStackSizeKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(
        statements, fieldInfo, 2, "pipeline", "VkPipeline", args.pipeline);
    RecordField(
        statements, fieldInfo, 3, "group", "uint32_t", args.group);
    RecordField(
        statements, fieldInfo, 4, "groupShader", "VkShaderGroupShaderKHR", args.groupShader);

    statements.InsertApiEventReturns(this->block_index_, "VkDeviceSize", args.result);
}

void VulkanSqliteConsumer::Process_vkCmdSetRayTracingPipelineStackSizeKHR(
    const ApiCallInfo&                          call_info,
    args::CmdSetRayTracingPipelineStackSizeKHR& args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdSetRayTracingPipelineStackSizeKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "pipelineStackSize", "uint32_t", args.pipelineStackSize);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}
void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksEXT&                  args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "groupCountX", "uint32_t", args.groupCountX);
    RecordField(
        statements, fieldInfo, 3, "groupCountY", "uint32_t", args.groupCountY);
    RecordField(
        statements, fieldInfo, 4, "groupCountZ", "uint32_t", args.groupCountZ);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    statements.InsertCmdMeshTaskRecordingInfo(cmdMeshTaskRecordingId, args.groupCountX, args.groupCountY, args.groupCountZ);
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirectEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirectEXT&          args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirectEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "drawCount", "uint32_t", args.drawCount);
    RecordField(
        statements, fieldInfo, 5, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    std::optional<int64_t> indirectBuffer = context.GetBufferId(args.buffer);
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    indirectDrawCount = args.drawCount;
    statements.InsertCmdMeshTaskRecordingIndirectInfo(cmdMeshTaskRecordingId, indirectBuffer, args.offset, indirectCountBuffer, indirectCountBufferOffset, indirectDrawCount, indirectMaxDrawCount, args.stride);
}

void VulkanSqliteConsumer::Process_vkCmdDrawMeshTasksIndirectCountEXT(
    const ApiCallInfo&                          call_info,
    args::CmdDrawMeshTasksIndirectCountEXT&     args)
{
    FieldInfo fieldInfo = {this->block_index_, 0, 0, 0};
    const auto functionId = statements.InsertFunctionName("vkCmdDrawMeshTasksIndirectCountEXT");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(
        statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "buffer", "VkBuffer", args.buffer);
    RecordField(
        statements, fieldInfo, 3, "offset", "VkDeviceSize", args.offset);
    RecordField(
        statements, fieldInfo, 4, "countBuffer", "VkBuffer", args.countBuffer);
    RecordField(
        statements, fieldInfo, 5, "countBufferOffset", "VkDeviceSize", args.countBufferOffset);
    RecordField(
        statements, fieldInfo, 6, "maxDrawCount", "uint32_t", args.maxDrawCount);
    RecordField(
        statements, fieldInfo, 7, "stride", "uint32_t", args.stride);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, args.commandBuffer);
    auto commandBufferRecordingIter = context.commandBufferHandleToRecordingId.find(ToInt64(args.commandBuffer));
    if (commandBufferRecordingIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to insert cmd mesh task recording, failed to find command buffer recording for command buffer with handle %" PRIi64,
            args.commandBuffer
        );
        return;
    }
    std::optional<int64_t> renderPassRecordingId = std::nullopt;
    std::optional<int64_t> renderSubpassRecordingId = std::nullopt;
    std::optional<int64_t> dynamicRenderPassRecordingId = std::nullopt;

    auto commandBufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    auto commandBufferLevelIter = context.commandBufferHandleToLevel.find(ToInt64(args.commandBuffer));
    if (commandBufferLevelIter == context.commandBufferHandleToLevel.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to find command buffer level for command buffer with handle %" PRIi64 ", assuming Primary",
            args.commandBuffer
        );
    } else {
        commandBufferLevel = commandBufferLevelIter->second;
    }

    std::optional<int64_t> deviceId = std::nullopt;
    auto deviceIdIter = context.commandBufferHandleToDeviceId.find(ToInt64(args.commandBuffer));
    if (deviceIdIter != context.commandBufferHandleToDeviceId.end())
    {
        deviceId = deviceIdIter->second;
    }
    if (deviceId.has_value() && context.IsDeviceFeatureEnabled(deviceId.value(), "dynamicRendering"))
    {
        auto commandBufferDynamicRenderPassStackIter = context.commandBufferHandleToDynamicRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferDynamicRenderPassStackIter != context.commandBufferHandleToDynamicRenderPassRecordingIdStack.end())
        {
            if (!commandBufferDynamicRenderPassStackIter->second.empty())
            {
                dynamicRenderPassRecordingId = commandBufferDynamicRenderPassStackIter->second.top();
            }
        }
    }

    if (!dynamicRenderPassRecordingId.has_value())
    {
        auto commandBufferRenderPassStackIter = context.commandBufferHandleToRenderPassRecordingIdStack.find(ToInt64(args.commandBuffer));
        if (commandBufferRenderPassStackIter != context.commandBufferHandleToRenderPassRecordingIdStack.end())
        {
            if (!commandBufferRenderPassStackIter->second.empty())
            {
                renderPassRecordingId = commandBufferRenderPassStackIter->second.top();
                auto renderSubpassRecordingIter = context.renderPassRecordingIdToRenderSubpassRecordingId.find(renderPassRecordingId.value());
                if (renderSubpassRecordingIter != context.renderPassRecordingIdToRenderSubpassRecordingId.end())
                {
                    renderSubpassRecordingId = renderSubpassRecordingIter->second;
                }
                else
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render subpass recording from render pass recording %" PRIu64 ", expected at least one implicit subpass, "
                        "setting foreign key to NULL",
                        renderPassRecordingId.value()
                    );
                }
            }
            else
            {
                if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
                {
                    GFXRECON_SQLITE_LOG_WARNING(
                        "Failed to find render pass recording for command buffer with handle %" PRIi64 " stack is empty, expected at least one render pass, "
                        "setting foreign keys to NULL",
                        args.commandBuffer
                    );
                }
            }
        }
        else
        {
            if (commandBufferLevel == VK_COMMAND_BUFFER_LEVEL_PRIMARY)
            {
                GFXRECON_SQLITE_LOG_WARNING(
                    "Failed to find render pass recording stack for command buffer with handle %" PRIi64 ", setting foreign keys to NULL",
                    args.commandBuffer
                );
            }
        }
    }
    auto cmdMeshTaskRecordingId = statements.InsertCmdMeshTaskRecording(this->block_index_, commandBufferRecordingIter->second, renderPassRecordingId, renderSubpassRecordingId, dynamicRenderPassRecordingId);
    std::optional<int64_t> indirectBuffer = context.GetBufferId(args.buffer);
    std::optional<int64_t> indirectCountBuffer = std::nullopt;
    std::optional<uint64_t> indirectCountBufferOffset = std::nullopt;
    std::optional<uint32_t> indirectDrawCount = std::nullopt;
    std::optional<uint32_t> indirectMaxDrawCount = std::nullopt;
    indirectCountBuffer = context.GetBufferId(args.countBuffer);
    indirectCountBufferOffset = args.countBufferOffset;
    indirectMaxDrawCount = args.maxDrawCount;
    statements.InsertCmdMeshTaskRecordingIndirectInfo(cmdMeshTaskRecordingId, indirectBuffer, args.offset, indirectCountBuffer, indirectCountBufferOffset, indirectDrawCount, indirectMaxDrawCount, args.stride);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
