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

#include "generated_vulkan_apidump_dispatch.h"

#include "apidump_struct_encode.h"
#include "generated_vulkan_enum_from_string.h"
#include "generated_vulkan_struct_from_apidump.h"

#include "format/api_call_id.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace
{

void ApiDump_vkCreateInstance(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    StructPtrFromApiDump<VkInstanceCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pInstance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyInstance(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
}

void ApiDump_vkEnumeratePhysicalDevices(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.UInt32Ptr(call.Arg("pPhysicalDeviceCount"));
    ctx.VulkanHandleArray(call.Arg("pPhysicalDevices"), VK_OBJECT_TYPE_PHYSICAL_DEVICE, ctx.Length(call.Arg("pPhysicalDeviceCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceFeatures(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceFeatures>(ctx, call.Arg("pFeatures"));
}

void ApiDump_vkGetPhysicalDeviceFormatProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    StructPtrFromApiDump<VkFormatProperties>(ctx, call.Arg("pFormatProperties"));
}

void ApiDump_vkGetPhysicalDeviceImageFormatProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    ctx.EnumValue(call.Arg("type"), EnumFromString_VkImageType);
    ctx.EnumValue(call.Arg("tiling"), EnumFromString_VkImageTiling);
    ctx.FlagsValue(call.Arg("usage"), EnumFromString_VkImageUsageFlagBits);
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkImageCreateFlagBits);
    StructPtrFromApiDump<VkImageFormatProperties>(ctx, call.Arg("pImageFormatProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceProperties>(ctx, call.Arg("pProperties"));
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pQueueFamilyPropertyCount"));
    StructArrayFromApiDump<VkQueueFamilyProperties>(ctx, call.Arg("pQueueFamilyProperties"), ctx.Length(call.Arg("pQueueFamilyPropertyCount")));
}

void ApiDump_vkGetPhysicalDeviceMemoryProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceMemoryProperties>(ctx, call.Arg("pMemoryProperties"));
}

void ApiDump_vkCreateDevice(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkDeviceCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pDevice"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDevice(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
}

void ApiDump_vkGetDeviceQueue(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.UInt32Value(call.Arg("queueIndex"));
    ctx.VulkanHandlePtr(call.Arg("pQueue"), VK_OBJECT_TYPE_QUEUE);
}

void ApiDump_vkQueueSubmit(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Value(call.Arg("submitCount"));
    StructArrayFromApiDump<VkSubmitInfo>(ctx, call.Arg("pSubmits"), ctx.Length(call.Arg("submitCount")));
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkQueueWaitIdle(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDeviceWaitIdle(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAllocateMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryAllocateInfo>(ctx, call.Arg("pAllocateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pMemory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkFreeMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
}

void ApiDump_vkMapMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt64Value(call.Arg("size"));
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkMemoryMapFlagBits);
    ctx.VoidPtrValue(call.Arg("ppData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkUnmapMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
}

void ApiDump_vkFlushMappedMemoryRanges(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("memoryRangeCount"));
    StructArrayFromApiDump<VkMappedMemoryRange>(ctx, call.Arg("pMemoryRanges"), ctx.Length(call.Arg("memoryRangeCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkInvalidateMappedMemoryRanges(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("memoryRangeCount"));
    StructArrayFromApiDump<VkMappedMemoryRange>(ctx, call.Arg("pMemoryRanges"), ctx.Length(call.Arg("memoryRangeCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceMemoryCommitment(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Ptr(call.Arg("pCommittedMemoryInBytes"));
}

void ApiDump_vkBindBufferMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(call.Arg("memoryOffset"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkBindImageMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.UInt64Value(call.Arg("memoryOffset"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetBufferMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    StructPtrFromApiDump<VkMemoryRequirements>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetImageMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkMemoryRequirements>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetImageSparseMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    ctx.UInt32Ptr(call.Arg("pSparseMemoryRequirementCount"));
    StructArrayFromApiDump<VkSparseImageMemoryRequirements>(ctx, call.Arg("pSparseMemoryRequirements"), ctx.Length(call.Arg("pSparseMemoryRequirementCount")));
}

void ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    ctx.EnumValue(call.Arg("type"), EnumFromString_VkImageType);
    ctx.EnumValue(call.Arg("samples"), EnumFromString_VkSampleCountFlagBits);
    ctx.FlagsValue(call.Arg("usage"), EnumFromString_VkImageUsageFlagBits);
    ctx.EnumValue(call.Arg("tiling"), EnumFromString_VkImageTiling);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkSparseImageFormatProperties>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
}

void ApiDump_vkQueueBindSparse(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindSparseInfo>(ctx, call.Arg("pBindInfo"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateFence(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkFenceCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pFence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyFence(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
}

void ApiDump_vkResetFences(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("fenceCount"));
    ctx.VulkanHandleArray(call.Arg("pFences"), VK_OBJECT_TYPE_FENCE, ctx.Length(call.Arg("fenceCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetFenceStatus(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkWaitForFences(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("fenceCount"));
    ctx.VulkanHandleArray(call.Arg("pFences"), VK_OBJECT_TYPE_FENCE, ctx.Length(call.Arg("fenceCount")));
    ctx.UInt32Value(call.Arg("waitAll"));
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateSemaphore(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSemaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroySemaphore(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
}

void ApiDump_vkCreateQueryPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkQueryPoolCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pQueryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyQueryPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
}

void ApiDump_vkGetQueryPoolResults(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.UInt64Value(call.Arg("stride"));
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkQueryResultFlagBits);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
}

void ApiDump_vkCreateImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
}

void ApiDump_vkGetImageSubresourceLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkImageSubresource>(ctx, call.Arg("pSubresource"));
    StructPtrFromApiDump<VkSubresourceLayout>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkCreateImageView(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageViewCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pView"), VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyImageView(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("imageView"), VK_OBJECT_TYPE_IMAGE_VIEW);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("imageView"), VK_OBJECT_TYPE_IMAGE_VIEW);
}

void ApiDump_vkCreateCommandPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCommandPoolCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pCommandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyCommandPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
}

void ApiDump_vkResetCommandPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkCommandPoolResetFlagBits);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAllocateCommandBuffers(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCommandBufferAllocateInfo>(ctx, call.Arg("pAllocateInfo"));
    ctx.VulkanHandleCreatedArray(call.Arg("pCommandBuffers"), VK_OBJECT_TYPE_COMMAND_BUFFER, ctx.Length(call.Arg("pAllocateInfo")["commandBufferCount"]));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkFreeCommandBuffers(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.UInt32Value(call.Arg("commandBufferCount"));
    ctx.VulkanHandleArray(call.Arg("pCommandBuffers"), VK_OBJECT_TYPE_COMMAND_BUFFER, ctx.Length(call.Arg("commandBufferCount")));
    ctx.ReleaseHandleArray(call.Arg("pCommandBuffers"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkBeginCommandBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCommandBufferBeginInfo>(ctx, call.Arg("pBeginInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkEndCommandBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkResetCommandBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkCommandBufferResetFlagBits);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkBufferCopy>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
}

void ApiDump_vkCmdCopyImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("srcImageLayout"), EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(call.Arg("dstImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("dstImageLayout"), EnumFromString_VkImageLayout);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkImageCopy>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
}

void ApiDump_vkCmdCopyBufferToImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.VulkanHandleValue(call.Arg("dstImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("dstImageLayout"), EnumFromString_VkImageLayout);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkBufferImageCopy>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
}

void ApiDump_vkCmdCopyImageToBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("srcImageLayout"), EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkBufferImageCopy>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
}

void ApiDump_vkCmdUpdateBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("dstOffset"));
    ctx.UInt64Value(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
}

void ApiDump_vkCmdFillBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("dstOffset"));
    ctx.UInt64Value(call.Arg("size"));
    ctx.UInt32Value(call.Arg("data"));
}

void ApiDump_vkCmdPipelineBarrier(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("srcStageMask"), EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(call.Arg("dstStageMask"), EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(call.Arg("dependencyFlags"), EnumFromString_VkDependencyFlagBits);
    ctx.UInt32Value(call.Arg("memoryBarrierCount"));
    StructArrayFromApiDump<VkMemoryBarrier>(ctx, call.Arg("pMemoryBarriers"), ctx.Length(call.Arg("memoryBarrierCount")));
    ctx.UInt32Value(call.Arg("bufferMemoryBarrierCount"));
    StructArrayFromApiDump<VkBufferMemoryBarrier>(ctx, call.Arg("pBufferMemoryBarriers"), ctx.Length(call.Arg("bufferMemoryBarrierCount")));
    ctx.UInt32Value(call.Arg("imageMemoryBarrierCount"));
    StructArrayFromApiDump<VkImageMemoryBarrier>(ctx, call.Arg("pImageMemoryBarriers"), ctx.Length(call.Arg("imageMemoryBarrierCount")));
}

void ApiDump_vkCmdBeginQuery(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkQueryControlFlagBits);
}

void ApiDump_vkCmdEndQuery(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
}

void ApiDump_vkCmdResetQueryPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
}

void ApiDump_vkCmdWriteTimestamp(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineStage"), EnumFromString_VkPipelineStageFlagBits);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
}

void ApiDump_vkCmdCopyQueryPoolResults(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("dstOffset"));
    ctx.UInt64Value(call.Arg("stride"));
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkQueryResultFlagBits);
}

void ApiDump_vkCmdExecuteCommands(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("commandBufferCount"));
    ctx.VulkanHandleArray(call.Arg("pCommandBuffers"), VK_OBJECT_TYPE_COMMAND_BUFFER, ctx.Length(call.Arg("commandBufferCount")));
}

void ApiDump_vkCreateEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkEventCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pEvent"), VK_OBJECT_TYPE_EVENT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
}

void ApiDump_vkGetEventStatus(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSetEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkResetEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateBufferView(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferViewCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pView"), VK_OBJECT_TYPE_BUFFER_VIEW);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyBufferView(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("bufferView"), VK_OBJECT_TYPE_BUFFER_VIEW);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("bufferView"), VK_OBJECT_TYPE_BUFFER_VIEW);
}

void ApiDump_vkCreateShaderModule(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkShaderModuleCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pShaderModule"), VK_OBJECT_TYPE_SHADER_MODULE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyShaderModule(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("shaderModule"), VK_OBJECT_TYPE_SHADER_MODULE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("shaderModule"), VK_OBJECT_TYPE_SHADER_MODULE);
}

void ApiDump_vkCreatePipelineCache(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineCacheCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pPipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPipelineCache(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
}

void ApiDump_vkGetPipelineCacheData(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.SizeTPtr(call.Arg("pDataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkMergePipelineCaches(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("dstCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.UInt32Value(call.Arg("srcCacheCount"));
    ctx.VulkanHandleArray(call.Arg("pSrcCaches"), VK_OBJECT_TYPE_PIPELINE_CACHE, ctx.Length(call.Arg("srcCacheCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateComputePipelines(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.UInt32Value(call.Arg("createInfoCount"));
    StructArrayFromApiDump<VkComputePipelineCreateInfo>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("createInfoCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pPipelines"), VK_OBJECT_TYPE_PIPELINE, ctx.Length(call.Arg("createInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPipeline(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
}

void ApiDump_vkCreatePipelineLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineLayoutCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pPipelineLayout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPipelineLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineLayout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("pipelineLayout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
}

void ApiDump_vkCreateSampler(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSamplerCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSampler"), VK_OBJECT_TYPE_SAMPLER);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroySampler(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("sampler"), VK_OBJECT_TYPE_SAMPLER);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("sampler"), VK_OBJECT_TYPE_SAMPLER);
}

void ApiDump_vkCreateDescriptorSetLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorSetLayoutCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSetLayout"), VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDescriptorSetLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorSetLayout"), VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("descriptorSetLayout"), VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
}

void ApiDump_vkCreateDescriptorPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorPoolCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pDescriptorPool"), VK_OBJECT_TYPE_DESCRIPTOR_POOL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDescriptorPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorPool"), VK_OBJECT_TYPE_DESCRIPTOR_POOL);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("descriptorPool"), VK_OBJECT_TYPE_DESCRIPTOR_POOL);
}

void ApiDump_vkResetDescriptorPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorPool"), VK_OBJECT_TYPE_DESCRIPTOR_POOL);
    ctx.FlagsValue(call.Arg("flags"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAllocateDescriptorSets(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorSetAllocateInfo>(ctx, call.Arg("pAllocateInfo"));
    ctx.VulkanHandleCreatedArray(call.Arg("pDescriptorSets"), VK_OBJECT_TYPE_DESCRIPTOR_SET, ctx.Length(call.Arg("pAllocateInfo")["descriptorSetCount"]));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkFreeDescriptorSets(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorPool"), VK_OBJECT_TYPE_DESCRIPTOR_POOL);
    ctx.UInt32Value(call.Arg("descriptorSetCount"));
    ctx.VulkanHandleArray(call.Arg("pDescriptorSets"), VK_OBJECT_TYPE_DESCRIPTOR_SET, ctx.Length(call.Arg("descriptorSetCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
    ctx.ReleaseHandleArray(call.Arg("pDescriptorSets"), VK_OBJECT_TYPE_DESCRIPTOR_SET);
}

void ApiDump_vkUpdateDescriptorSets(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("descriptorWriteCount"));
    StructArrayFromApiDump<VkWriteDescriptorSet>(ctx, call.Arg("pDescriptorWrites"), ctx.Length(call.Arg("descriptorWriteCount")));
    ctx.UInt32Value(call.Arg("descriptorCopyCount"));
    StructArrayFromApiDump<VkCopyDescriptorSet>(ctx, call.Arg("pDescriptorCopies"), ctx.Length(call.Arg("descriptorCopyCount")));
}

void ApiDump_vkCmdBindPipeline(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
}

void ApiDump_vkCmdBindDescriptorSets(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(call.Arg("firstSet"));
    ctx.UInt32Value(call.Arg("descriptorSetCount"));
    ctx.VulkanHandleArray(call.Arg("pDescriptorSets"), VK_OBJECT_TYPE_DESCRIPTOR_SET, ctx.Length(call.Arg("descriptorSetCount")));
    ctx.UInt32Value(call.Arg("dynamicOffsetCount"));
    ctx.UInt32Array(call.Arg("pDynamicOffsets"), ctx.Length(call.Arg("dynamicOffsetCount")));
}

void ApiDump_vkCmdClearColorImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("imageLayout"), EnumFromString_VkImageLayout);
    StructPtrFromApiDump<VkClearColorValue>(ctx, call.Arg("pColor"));
    ctx.UInt32Value(call.Arg("rangeCount"));
    StructArrayFromApiDump<VkImageSubresourceRange>(ctx, call.Arg("pRanges"), ctx.Length(call.Arg("rangeCount")));
}

void ApiDump_vkCmdDispatch(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("groupCountX"));
    ctx.UInt32Value(call.Arg("groupCountY"));
    ctx.UInt32Value(call.Arg("groupCountZ"));
}

void ApiDump_vkCmdDispatchIndirect(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
}

void ApiDump_vkCmdSetEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.FlagsValue(call.Arg("stageMask"), EnumFromString_VkPipelineStageFlagBits);
}

void ApiDump_vkCmdResetEvent(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.FlagsValue(call.Arg("stageMask"), EnumFromString_VkPipelineStageFlagBits);
}

void ApiDump_vkCmdWaitEvents(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("eventCount"));
    ctx.VulkanHandleArray(call.Arg("pEvents"), VK_OBJECT_TYPE_EVENT, ctx.Length(call.Arg("eventCount")));
    ctx.FlagsValue(call.Arg("srcStageMask"), EnumFromString_VkPipelineStageFlagBits);
    ctx.FlagsValue(call.Arg("dstStageMask"), EnumFromString_VkPipelineStageFlagBits);
    ctx.UInt32Value(call.Arg("memoryBarrierCount"));
    StructArrayFromApiDump<VkMemoryBarrier>(ctx, call.Arg("pMemoryBarriers"), ctx.Length(call.Arg("memoryBarrierCount")));
    ctx.UInt32Value(call.Arg("bufferMemoryBarrierCount"));
    StructArrayFromApiDump<VkBufferMemoryBarrier>(ctx, call.Arg("pBufferMemoryBarriers"), ctx.Length(call.Arg("bufferMemoryBarrierCount")));
    ctx.UInt32Value(call.Arg("imageMemoryBarrierCount"));
    StructArrayFromApiDump<VkImageMemoryBarrier>(ctx, call.Arg("pImageMemoryBarriers"), ctx.Length(call.Arg("imageMemoryBarrierCount")));
}

void ApiDump_vkCmdPushConstants(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.FlagsValue(call.Arg("stageFlags"), EnumFromString_VkShaderStageFlagBits);
    ctx.UInt32Value(call.Arg("offset"));
    ctx.UInt32Value(call.Arg("size"));
    ctx.VoidPtrValue(call.Arg("pValues"));
}

void ApiDump_vkCreateGraphicsPipelines(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.UInt32Value(call.Arg("createInfoCount"));
    StructArrayFromApiDump<VkGraphicsPipelineCreateInfo>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("createInfoCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pPipelines"), VK_OBJECT_TYPE_PIPELINE, ctx.Length(call.Arg("createInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateFramebuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkFramebufferCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pFramebuffer"), VK_OBJECT_TYPE_FRAMEBUFFER);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyFramebuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("framebuffer"), VK_OBJECT_TYPE_FRAMEBUFFER);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("framebuffer"), VK_OBJECT_TYPE_FRAMEBUFFER);
}

void ApiDump_vkCreateRenderPass(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderPassCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pRenderPass"), VK_OBJECT_TYPE_RENDER_PASS);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyRenderPass(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("renderPass"), VK_OBJECT_TYPE_RENDER_PASS);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("renderPass"), VK_OBJECT_TYPE_RENDER_PASS);
}

void ApiDump_vkGetRenderAreaGranularity(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("renderPass"), VK_OBJECT_TYPE_RENDER_PASS);
    StructPtrFromApiDump<VkExtent2D>(ctx, call.Arg("pGranularity"));
}

void ApiDump_vkCmdSetViewport(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstViewport"));
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkViewport>(ctx, call.Arg("pViewports"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkCmdSetScissor(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstScissor"));
    ctx.UInt32Value(call.Arg("scissorCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pScissors"), ctx.Length(call.Arg("scissorCount")));
}

void ApiDump_vkCmdSetLineWidth(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FloatValue(call.Arg("lineWidth"));
}

void ApiDump_vkCmdSetDepthBias(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FloatValue(call.Arg("depthBiasConstantFactor"));
    ctx.FloatValue(call.Arg("depthBiasClamp"));
    ctx.FloatValue(call.Arg("depthBiasSlopeFactor"));
}

void ApiDump_vkCmdSetBlendConstants(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FloatArray(call.Arg("blendConstants"), 4);
}

void ApiDump_vkCmdSetDepthBounds(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FloatValue(call.Arg("minDepthBounds"));
    ctx.FloatValue(call.Arg("maxDepthBounds"));
}

void ApiDump_vkCmdSetStencilCompareMask(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("faceMask"), EnumFromString_VkStencilFaceFlagBits);
    ctx.UInt32Value(call.Arg("compareMask"));
}

void ApiDump_vkCmdSetStencilWriteMask(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("faceMask"), EnumFromString_VkStencilFaceFlagBits);
    ctx.UInt32Value(call.Arg("writeMask"));
}

void ApiDump_vkCmdSetStencilReference(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("faceMask"), EnumFromString_VkStencilFaceFlagBits);
    ctx.UInt32Value(call.Arg("reference"));
}

void ApiDump_vkCmdBindIndexBuffer(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.EnumValue(call.Arg("indexType"), EnumFromString_VkIndexType);
}

void ApiDump_vkCmdBindVertexBuffers(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    ctx.VulkanHandleArray(call.Arg("pBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pOffsets"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdDraw(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("vertexCount"));
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstVertex"));
    ctx.UInt32Value(call.Arg("firstInstance"));
}

void ApiDump_vkCmdDrawIndexed(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("indexCount"));
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstIndex"));
    ctx.Int32Value(call.Arg("vertexOffset"));
    ctx.UInt32Value(call.Arg("firstInstance"));
}

void ApiDump_vkCmdDrawIndirect(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt32Value(call.Arg("drawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawIndexedIndirect(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt32Value(call.Arg("drawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdBlitImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("srcImageLayout"), EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(call.Arg("dstImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("dstImageLayout"), EnumFromString_VkImageLayout);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkImageBlit>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
    ctx.EnumValue(call.Arg("filter"), EnumFromString_VkFilter);
}

void ApiDump_vkCmdClearDepthStencilImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("imageLayout"), EnumFromString_VkImageLayout);
    StructPtrFromApiDump<VkClearDepthStencilValue>(ctx, call.Arg("pDepthStencil"));
    ctx.UInt32Value(call.Arg("rangeCount"));
    StructArrayFromApiDump<VkImageSubresourceRange>(ctx, call.Arg("pRanges"), ctx.Length(call.Arg("rangeCount")));
}

void ApiDump_vkCmdClearAttachments(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("attachmentCount"));
    StructArrayFromApiDump<VkClearAttachment>(ctx, call.Arg("pAttachments"), ctx.Length(call.Arg("attachmentCount")));
    ctx.UInt32Value(call.Arg("rectCount"));
    StructArrayFromApiDump<VkClearRect>(ctx, call.Arg("pRects"), ctx.Length(call.Arg("rectCount")));
}

void ApiDump_vkCmdResolveImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("srcImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("srcImageLayout"), EnumFromString_VkImageLayout);
    ctx.VulkanHandleValue(call.Arg("dstImage"), VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(call.Arg("dstImageLayout"), EnumFromString_VkImageLayout);
    ctx.UInt32Value(call.Arg("regionCount"));
    StructArrayFromApiDump<VkImageResolve>(ctx, call.Arg("pRegions"), ctx.Length(call.Arg("regionCount")));
}

void ApiDump_vkCmdBeginRenderPass(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderPassBeginInfo>(ctx, call.Arg("pRenderPassBegin"));
    ctx.EnumValue(call.Arg("contents"), EnumFromString_VkSubpassContents);
}

void ApiDump_vkCmdNextSubpass(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("contents"), EnumFromString_VkSubpassContents);
}

void ApiDump_vkCmdEndRenderPass(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkBindBufferMemory2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindBufferMemoryInfo>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkBindImageMemory2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindImageMemoryInfo>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceGroupPeerMemoryFeatures(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("heapIndex"));
    ctx.UInt32Value(call.Arg("localDeviceIndex"));
    ctx.UInt32Value(call.Arg("remoteDeviceIndex"));
    ctx.FlagsValue(call.Arg("pPeerMemoryFeatures"), EnumFromString_VkPeerMemoryFeatureFlagBits);
}

void ApiDump_vkCmdSetDeviceMask(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("deviceMask"));
}

void ApiDump_vkEnumeratePhysicalDeviceGroups(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.UInt32Ptr(call.Arg("pPhysicalDeviceGroupCount"));
    StructArrayFromApiDump<VkPhysicalDeviceGroupProperties>(ctx, call.Arg("pPhysicalDeviceGroupProperties"), ctx.Length(call.Arg("pPhysicalDeviceGroupCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetImageMemoryRequirements2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetBufferMemoryRequirements2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetImageSparseMemoryRequirements2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageSparseMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    ctx.UInt32Ptr(call.Arg("pSparseMemoryRequirementCount"));
    StructArrayFromApiDump<VkSparseImageMemoryRequirements2>(ctx, call.Arg("pSparseMemoryRequirements"), ctx.Length(call.Arg("pSparseMemoryRequirementCount")));
}

void ApiDump_vkGetPhysicalDeviceFeatures2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceFeatures2>(ctx, call.Arg("pFeatures"));
}

void ApiDump_vkGetPhysicalDeviceProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceProperties2>(ctx, call.Arg("pProperties"));
}

void ApiDump_vkGetPhysicalDeviceFormatProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    StructPtrFromApiDump<VkFormatProperties2>(ctx, call.Arg("pFormatProperties"));
}

void ApiDump_vkGetPhysicalDeviceImageFormatProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceImageFormatInfo2>(ctx, call.Arg("pImageFormatInfo"));
    StructPtrFromApiDump<VkImageFormatProperties2>(ctx, call.Arg("pImageFormatProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pQueueFamilyPropertyCount"));
    StructArrayFromApiDump<VkQueueFamilyProperties2>(ctx, call.Arg("pQueueFamilyProperties"), ctx.Length(call.Arg("pQueueFamilyPropertyCount")));
}

void ApiDump_vkGetPhysicalDeviceMemoryProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceMemoryProperties2>(ctx, call.Arg("pMemoryProperties"));
}

void ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSparseImageFormatInfo2>(ctx, call.Arg("pFormatInfo"));
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkSparseImageFormatProperties2>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
}

void ApiDump_vkTrimCommandPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.FlagsValue(call.Arg("flags"));
}

void ApiDump_vkGetDeviceQueue2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceQueueInfo2>(ctx, call.Arg("pQueueInfo"));
    ctx.VulkanHandlePtr(call.Arg("pQueue"), VK_OBJECT_TYPE_QUEUE);
}

void ApiDump_vkGetPhysicalDeviceExternalBufferProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalBufferInfo>(ctx, call.Arg("pExternalBufferInfo"));
    StructPtrFromApiDump<VkExternalBufferProperties>(ctx, call.Arg("pExternalBufferProperties"));
}

void ApiDump_vkGetPhysicalDeviceExternalFenceProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalFenceInfo>(ctx, call.Arg("pExternalFenceInfo"));
    StructPtrFromApiDump<VkExternalFenceProperties>(ctx, call.Arg("pExternalFenceProperties"));
}

void ApiDump_vkGetPhysicalDeviceExternalSemaphoreProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalSemaphoreInfo>(ctx, call.Arg("pExternalSemaphoreInfo"));
    StructPtrFromApiDump<VkExternalSemaphoreProperties>(ctx, call.Arg("pExternalSemaphoreProperties"));
}

void ApiDump_vkCmdDispatchBase(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("baseGroupX"));
    ctx.UInt32Value(call.Arg("baseGroupY"));
    ctx.UInt32Value(call.Arg("baseGroupZ"));
    ctx.UInt32Value(call.Arg("groupCountX"));
    ctx.UInt32Value(call.Arg("groupCountY"));
    ctx.UInt32Value(call.Arg("groupCountZ"));
}

void ApiDump_vkCreateDescriptorUpdateTemplate(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorUpdateTemplateCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pDescriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDescriptorUpdateTemplate(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("descriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
}

void ApiDump_vkGetDescriptorSetLayoutSupport(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorSetLayoutCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkDescriptorSetLayoutSupport>(ctx, call.Arg("pSupport"));
}

void ApiDump_vkCreateSamplerYcbcrConversion(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSamplerYcbcrConversionCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pYcbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroySamplerYcbcrConversion(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("ycbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("ycbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
}

void ApiDump_vkResetQueryPool(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
}

void ApiDump_vkGetSemaphoreCounterValue(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    ctx.UInt64Ptr(call.Arg("pValue"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkWaitSemaphores(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreWaitInfo>(ctx, call.Arg("pWaitInfo"));
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSignalSemaphore(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreSignalInfo>(ctx, call.Arg("pSignalInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetBufferDeviceAddress(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetBufferOpaqueCaptureAddress(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetDeviceMemoryOpaqueCaptureAddress(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceMemoryOpaqueCaptureAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCmdDrawIndirectCount(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawIndexedIndirectCount(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCreateRenderPass2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderPassCreateInfo2>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pRenderPass"), VK_OBJECT_TYPE_RENDER_PASS);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBeginRenderPass2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderPassBeginInfo>(ctx, call.Arg("pRenderPassBegin"));
    StructPtrFromApiDump<VkSubpassBeginInfo>(ctx, call.Arg("pSubpassBeginInfo"));
}

void ApiDump_vkCmdNextSubpass2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSubpassBeginInfo>(ctx, call.Arg("pSubpassBeginInfo"));
    StructPtrFromApiDump<VkSubpassEndInfo>(ctx, call.Arg("pSubpassEndInfo"));
}

void ApiDump_vkCmdEndRenderPass2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSubpassEndInfo>(ctx, call.Arg("pSubpassEndInfo"));
}

void ApiDump_vkGetPhysicalDeviceToolProperties(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pToolCount"));
    StructArrayFromApiDump<VkPhysicalDeviceToolProperties>(ctx, call.Arg("pToolProperties"), ctx.Length(call.Arg("pToolCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreatePrivateDataSlot(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPrivateDataSlotCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pPrivateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPrivateDataSlot(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
}

void ApiDump_vkSetPrivateData(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("objectType"), EnumFromString_VkObjectType);
    ctx.UInt64Value(call.Arg("objectHandle"));
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.UInt64Value(call.Arg("data"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPrivateData(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("objectType"), EnumFromString_VkObjectType);
    ctx.UInt64Value(call.Arg("objectHandle"));
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.UInt64Ptr(call.Arg("pData"));
}

void ApiDump_vkCmdPipelineBarrier2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfo"));
}

void ApiDump_vkCmdWriteTimestamp2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.Flags64Value(call.Arg("stage"), EnumFromString_VkPipelineStageFlagBits2);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
}

void ApiDump_vkQueueSubmit2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Value(call.Arg("submitCount"));
    StructArrayFromApiDump<VkSubmitInfo2>(ctx, call.Arg("pSubmits"), ctx.Length(call.Arg("submitCount")));
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyBuffer2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyBufferInfo2>(ctx, call.Arg("pCopyBufferInfo"));
}

void ApiDump_vkCmdCopyImage2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyImageInfo2>(ctx, call.Arg("pCopyImageInfo"));
}

void ApiDump_vkCmdCopyBufferToImage2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyBufferToImageInfo2>(ctx, call.Arg("pCopyBufferToImageInfo"));
}

void ApiDump_vkCmdCopyImageToBuffer2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyImageToBufferInfo2>(ctx, call.Arg("pCopyImageToBufferInfo"));
}

void ApiDump_vkGetDeviceBufferMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceBufferMemoryRequirements>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetDeviceImageMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageMemoryRequirements>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetDeviceImageSparseMemoryRequirements(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageMemoryRequirements>(ctx, call.Arg("pInfo"));
    ctx.UInt32Ptr(call.Arg("pSparseMemoryRequirementCount"));
    StructArrayFromApiDump<VkSparseImageMemoryRequirements2>(ctx, call.Arg("pSparseMemoryRequirements"), ctx.Length(call.Arg("pSparseMemoryRequirementCount")));
}

void ApiDump_vkCmdSetEvent2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    StructPtrFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfo"));
}

void ApiDump_vkCmdResetEvent2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.Flags64Value(call.Arg("stageMask"), EnumFromString_VkPipelineStageFlagBits2);
}

void ApiDump_vkCmdWaitEvents2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("eventCount"));
    ctx.VulkanHandleArray(call.Arg("pEvents"), VK_OBJECT_TYPE_EVENT, ctx.Length(call.Arg("eventCount")));
    StructArrayFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfos"), ctx.Length(call.Arg("eventCount")));
}

void ApiDump_vkCmdBlitImage2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBlitImageInfo2>(ctx, call.Arg("pBlitImageInfo"));
}

void ApiDump_vkCmdResolveImage2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkResolveImageInfo2>(ctx, call.Arg("pResolveImageInfo"));
}

void ApiDump_vkCmdBeginRendering(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingInfo>(ctx, call.Arg("pRenderingInfo"));
}

void ApiDump_vkCmdEndRendering(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkCmdSetCullMode(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("cullMode"), EnumFromString_VkCullModeFlagBits);
}

void ApiDump_vkCmdSetFrontFace(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("frontFace"), EnumFromString_VkFrontFace);
}

void ApiDump_vkCmdSetPrimitiveTopology(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("primitiveTopology"), EnumFromString_VkPrimitiveTopology);
}

void ApiDump_vkCmdSetViewportWithCount(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkViewport>(ctx, call.Arg("pViewports"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkCmdSetScissorWithCount(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("scissorCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pScissors"), ctx.Length(call.Arg("scissorCount")));
}

void ApiDump_vkCmdBindVertexBuffers2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    ctx.VulkanHandleArray(call.Arg("pBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pOffsets"), ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pSizes"), ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pStrides"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdSetDepthTestEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthTestEnable"));
}

void ApiDump_vkCmdSetDepthWriteEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthWriteEnable"));
}

void ApiDump_vkCmdSetDepthCompareOp(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("depthCompareOp"), EnumFromString_VkCompareOp);
}

void ApiDump_vkCmdSetDepthBoundsTestEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthBoundsTestEnable"));
}

void ApiDump_vkCmdSetStencilTestEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("stencilTestEnable"));
}

void ApiDump_vkCmdSetStencilOp(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("faceMask"), EnumFromString_VkStencilFaceFlagBits);
    ctx.EnumValue(call.Arg("failOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("passOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("depthFailOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("compareOp"), EnumFromString_VkCompareOp);
}

void ApiDump_vkCmdSetRasterizerDiscardEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("rasterizerDiscardEnable"));
}

void ApiDump_vkCmdSetDepthBiasEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthBiasEnable"));
}

void ApiDump_vkCmdSetPrimitiveRestartEnable(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("primitiveRestartEnable"));
}

void ApiDump_vkMapMemory2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryMapInfo>(ctx, call.Arg("pMemoryMapInfo"));
    ctx.VoidPtrValue(call.Arg("ppData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkUnmapMemory2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryUnmapInfo>(ctx, call.Arg("pMemoryUnmapInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceImageSubresourceLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageSubresourceInfo>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkSubresourceLayout2>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkGetImageSubresourceLayout2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkImageSubresource2>(ctx, call.Arg("pSubresource"));
    StructPtrFromApiDump<VkSubresourceLayout2>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkCopyMemoryToImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyMemoryToImageInfo>(ctx, call.Arg("pCopyMemoryToImageInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyImageToMemory(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyImageToMemoryInfo>(ctx, call.Arg("pCopyImageToMemoryInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyImageToImage(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyImageToImageInfo>(ctx, call.Arg("pCopyImageToImageInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkTransitionImageLayout(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("transitionCount"));
    StructArrayFromApiDump<VkHostImageLayoutTransitionInfo>(ctx, call.Arg("pTransitions"), ctx.Length(call.Arg("transitionCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdPushDescriptorSet(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(call.Arg("set"));
    ctx.UInt32Value(call.Arg("descriptorWriteCount"));
    StructArrayFromApiDump<VkWriteDescriptorSet>(ctx, call.Arg("pDescriptorWrites"), ctx.Length(call.Arg("descriptorWriteCount")));
}

void ApiDump_vkCmdBindDescriptorSets2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBindDescriptorSetsInfo>(ctx, call.Arg("pBindDescriptorSetsInfo"));
}

void ApiDump_vkCmdPushConstants2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPushConstantsInfo>(ctx, call.Arg("pPushConstantsInfo"));
}

void ApiDump_vkCmdPushDescriptorSet2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPushDescriptorSetInfo>(ctx, call.Arg("pPushDescriptorSetInfo"));
}

void ApiDump_vkCmdSetLineStipple(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("lineStippleFactor"));
    ctx.UInt16Value(call.Arg("lineStipplePattern"));
}

void ApiDump_vkCmdBindIndexBuffer2(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt64Value(call.Arg("size"));
    ctx.EnumValue(call.Arg("indexType"), EnumFromString_VkIndexType);
}

void ApiDump_vkGetRenderingAreaGranularity(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderingAreaInfo>(ctx, call.Arg("pRenderingAreaInfo"));
    StructPtrFromApiDump<VkExtent2D>(ctx, call.Arg("pGranularity"));
}

void ApiDump_vkCmdSetRenderingAttachmentLocations(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingAttachmentLocationInfo>(ctx, call.Arg("pLocationInfo"));
}

void ApiDump_vkCmdSetRenderingInputAttachmentIndices(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingInputAttachmentIndexInfo>(ctx, call.Arg("pInputAttachmentIndexInfo"));
}

void ApiDump_vkDestroySurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
}

void ApiDump_vkGetPhysicalDeviceSurfaceSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.UInt32Ptr(call.Arg("pSupported"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    StructPtrFromApiDump<VkSurfaceCapabilitiesKHR>(ctx, call.Arg("pSurfaceCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfaceFormatsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.UInt32Ptr(call.Arg("pSurfaceFormatCount"));
    StructArrayFromApiDump<VkSurfaceFormatKHR>(ctx, call.Arg("pSurfaceFormats"), ctx.Length(call.Arg("pSurfaceFormatCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfacePresentModesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.UInt32Ptr(call.Arg("pPresentModeCount"));
    ctx.EnumArray(call.Arg("pPresentModes"), EnumFromString_VkPresentModeKHR, ctx.Length(call.Arg("pPresentModeCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateSwapchainKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSwapchainCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSwapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroySwapchainKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
}

void ApiDump_vkGetSwapchainImagesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Ptr(call.Arg("pSwapchainImageCount"));
    ctx.VulkanHandleArray(call.Arg("pSwapchainImages"), VK_OBJECT_TYPE_IMAGE, ctx.Length(call.Arg("pSwapchainImageCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquireNextImageKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.VulkanHandleValue(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.UInt32Ptr(call.Arg("pImageIndex"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkQueuePresentKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    StructPtrFromApiDump<VkPresentInfoKHR>(ctx, call.Arg("pPresentInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceGroupPresentCapabilitiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceGroupPresentCapabilitiesKHR>(ctx, call.Arg("pDeviceGroupPresentCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceGroupSurfacePresentModesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.FlagsValue(call.Arg("pModes"), EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDevicePresentRectanglesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.UInt32Ptr(call.Arg("pRectCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pRects"), ctx.Length(call.Arg("pRectCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquireNextImage2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAcquireNextImageInfoKHR>(ctx, call.Arg("pAcquireInfo"));
    ctx.UInt32Ptr(call.Arg("pImageIndex"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceDisplayPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayPropertiesKHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayPlanePropertiesKHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDisplayPlaneSupportedDisplaysKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("planeIndex"));
    ctx.UInt32Ptr(call.Arg("pDisplayCount"));
    ctx.VulkanHandleArray(call.Arg("pDisplays"), VK_OBJECT_TYPE_DISPLAY_KHR, ctx.Length(call.Arg("pDisplayCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDisplayModePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayModePropertiesKHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateDisplayModeKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    StructPtrFromApiDump<VkDisplayModeCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pMode"), VK_OBJECT_TYPE_DISPLAY_MODE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDisplayPlaneCapabilitiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("mode"), VK_OBJECT_TYPE_DISPLAY_MODE_KHR);
    ctx.UInt32Value(call.Arg("planeIndex"));
    StructPtrFromApiDump<VkDisplayPlaneCapabilitiesKHR>(ctx, call.Arg("pCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateDisplayPlaneSurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkDisplaySurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateSharedSwapchainsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("swapchainCount"));
    StructArrayFromApiDump<VkSwapchainCreateInfoKHR>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("swapchainCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pSwapchains"), VK_OBJECT_TYPE_SWAPCHAIN_KHR, ctx.Length(call.Arg("swapchainCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateXlibSurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkXlibSurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceXlibPresentationSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VoidPtrValue(call.Arg("dpy"));
    ctx.SizeTValue(call.Arg("visualID"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkCreateXcbSurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkXcbSurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceXcbPresentationSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VoidPtrValue(call.Arg("connection"));
    ctx.UInt32Value(call.Arg("visual_id"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkCreateWaylandSurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkWaylandSurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceWaylandPresentationSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VoidPtrValue(call.Arg("display"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkCreateAndroidSurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkAndroidSurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateWin32SurfaceKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkWin32SurfaceCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceWin32PresentationSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkGetPhysicalDeviceVideoCapabilitiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkVideoProfileInfoKHR>(ctx, call.Arg("pVideoProfile"));
    StructPtrFromApiDump<VkVideoCapabilitiesKHR>(ctx, call.Arg("pCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceVideoFormatPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceVideoFormatInfoKHR>(ctx, call.Arg("pVideoFormatInfo"));
    ctx.UInt32Ptr(call.Arg("pVideoFormatPropertyCount"));
    StructArrayFromApiDump<VkVideoFormatPropertiesKHR>(ctx, call.Arg("pVideoFormatProperties"), ctx.Length(call.Arg("pVideoFormatPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateVideoSessionKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkVideoSessionCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pVideoSession"), VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyVideoSessionKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("videoSession"), VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("videoSession"), VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
}

void ApiDump_vkGetVideoSessionMemoryRequirementsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("videoSession"), VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
    ctx.UInt32Ptr(call.Arg("pMemoryRequirementsCount"));
    StructArrayFromApiDump<VkVideoSessionMemoryRequirementsKHR>(ctx, call.Arg("pMemoryRequirements"), ctx.Length(call.Arg("pMemoryRequirementsCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkBindVideoSessionMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("videoSession"), VK_OBJECT_TYPE_VIDEO_SESSION_KHR);
    ctx.UInt32Value(call.Arg("bindSessionMemoryInfoCount"));
    StructArrayFromApiDump<VkBindVideoSessionMemoryInfoKHR>(ctx, call.Arg("pBindSessionMemoryInfos"), ctx.Length(call.Arg("bindSessionMemoryInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateVideoSessionParametersKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkVideoSessionParametersCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pVideoSessionParameters"), VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkUpdateVideoSessionParametersKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("videoSessionParameters"), VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
    StructPtrFromApiDump<VkVideoSessionParametersUpdateInfoKHR>(ctx, call.Arg("pUpdateInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyVideoSessionParametersKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("videoSessionParameters"), VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("videoSessionParameters"), VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR);
}

void ApiDump_vkCmdBeginVideoCodingKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkVideoBeginCodingInfoKHR>(ctx, call.Arg("pBeginInfo"));
}

void ApiDump_vkCmdEndVideoCodingKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkVideoEndCodingInfoKHR>(ctx, call.Arg("pEndCodingInfo"));
}

void ApiDump_vkCmdControlVideoCodingKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkVideoCodingControlInfoKHR>(ctx, call.Arg("pCodingControlInfo"));
}

void ApiDump_vkCmdDecodeVideoKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkVideoDecodeInfoKHR>(ctx, call.Arg("pDecodeInfo"));
}

void ApiDump_vkCmdBeginRenderingKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingInfo>(ctx, call.Arg("pRenderingInfo"));
}

void ApiDump_vkCmdEndRenderingKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkGetPhysicalDeviceFeatures2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceFeatures2>(ctx, call.Arg("pFeatures"));
}

void ApiDump_vkGetPhysicalDeviceProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceProperties2>(ctx, call.Arg("pProperties"));
}

void ApiDump_vkGetPhysicalDeviceFormatProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    StructPtrFromApiDump<VkFormatProperties2>(ctx, call.Arg("pFormatProperties"));
}

void ApiDump_vkGetPhysicalDeviceImageFormatProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceImageFormatInfo2>(ctx, call.Arg("pImageFormatInfo"));
    StructPtrFromApiDump<VkImageFormatProperties2>(ctx, call.Arg("pImageFormatProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pQueueFamilyPropertyCount"));
    StructArrayFromApiDump<VkQueueFamilyProperties2>(ctx, call.Arg("pQueueFamilyProperties"), ctx.Length(call.Arg("pQueueFamilyPropertyCount")));
}

void ApiDump_vkGetPhysicalDeviceMemoryProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceMemoryProperties2>(ctx, call.Arg("pMemoryProperties"));
}

void ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSparseImageFormatInfo2>(ctx, call.Arg("pFormatInfo"));
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkSparseImageFormatProperties2>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
}

void ApiDump_vkGetDeviceGroupPeerMemoryFeaturesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("heapIndex"));
    ctx.UInt32Value(call.Arg("localDeviceIndex"));
    ctx.UInt32Value(call.Arg("remoteDeviceIndex"));
    ctx.FlagsValue(call.Arg("pPeerMemoryFeatures"), EnumFromString_VkPeerMemoryFeatureFlagBits);
}

void ApiDump_vkCmdSetDeviceMaskKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("deviceMask"));
}

void ApiDump_vkCmdDispatchBaseKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("baseGroupX"));
    ctx.UInt32Value(call.Arg("baseGroupY"));
    ctx.UInt32Value(call.Arg("baseGroupZ"));
    ctx.UInt32Value(call.Arg("groupCountX"));
    ctx.UInt32Value(call.Arg("groupCountY"));
    ctx.UInt32Value(call.Arg("groupCountZ"));
}

void ApiDump_vkTrimCommandPoolKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("commandPool"), VK_OBJECT_TYPE_COMMAND_POOL);
    ctx.FlagsValue(call.Arg("flags"));
}

void ApiDump_vkEnumeratePhysicalDeviceGroupsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.UInt32Ptr(call.Arg("pPhysicalDeviceGroupCount"));
    StructArrayFromApiDump<VkPhysicalDeviceGroupProperties>(ctx, call.Arg("pPhysicalDeviceGroupProperties"), ctx.Length(call.Arg("pPhysicalDeviceGroupCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceExternalBufferPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalBufferInfo>(ctx, call.Arg("pExternalBufferInfo"));
    StructPtrFromApiDump<VkExternalBufferProperties>(ctx, call.Arg("pExternalBufferProperties"));
}

void ApiDump_vkGetMemoryWin32HandleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetWin32HandleInfoKHR>(ctx, call.Arg("pGetWin32HandleInfo"));
    ctx.VoidPtrValue(call.Arg("pHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryWin32HandlePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(call.Arg("handle"));
    StructPtrFromApiDump<VkMemoryWin32HandlePropertiesKHR>(ctx, call.Arg("pMemoryWin32HandleProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryFdKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetFdInfoKHR>(ctx, call.Arg("pGetFdInfo"));
    ctx.Int32Ptr(call.Arg("pFd"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryFdPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.Int32Value(call.Arg("fd"));
    StructPtrFromApiDump<VkMemoryFdPropertiesKHR>(ctx, call.Arg("pMemoryFdProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalSemaphoreInfo>(ctx, call.Arg("pExternalSemaphoreInfo"));
    StructPtrFromApiDump<VkExternalSemaphoreProperties>(ctx, call.Arg("pExternalSemaphoreProperties"));
}

void ApiDump_vkImportSemaphoreWin32HandleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImportSemaphoreWin32HandleInfoKHR>(ctx, call.Arg("pImportSemaphoreWin32HandleInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSemaphoreWin32HandleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreGetWin32HandleInfoKHR>(ctx, call.Arg("pGetWin32HandleInfo"));
    ctx.VoidPtrValue(call.Arg("pHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkImportSemaphoreFdKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImportSemaphoreFdInfoKHR>(ctx, call.Arg("pImportSemaphoreFdInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSemaphoreFdKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreGetFdInfoKHR>(ctx, call.Arg("pGetFdInfo"));
    ctx.Int32Ptr(call.Arg("pFd"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdPushDescriptorSetKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(call.Arg("set"));
    ctx.UInt32Value(call.Arg("descriptorWriteCount"));
    StructArrayFromApiDump<VkWriteDescriptorSet>(ctx, call.Arg("pDescriptorWrites"), ctx.Length(call.Arg("descriptorWriteCount")));
}

void ApiDump_vkCreateDescriptorUpdateTemplateKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorUpdateTemplateCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pDescriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDescriptorUpdateTemplateKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("descriptorUpdateTemplate"), VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
}

void ApiDump_vkCreateRenderPass2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderPassCreateInfo2>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pRenderPass"), VK_OBJECT_TYPE_RENDER_PASS);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBeginRenderPass2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderPassBeginInfo>(ctx, call.Arg("pRenderPassBegin"));
    StructPtrFromApiDump<VkSubpassBeginInfo>(ctx, call.Arg("pSubpassBeginInfo"));
}

void ApiDump_vkCmdNextSubpass2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSubpassBeginInfo>(ctx, call.Arg("pSubpassBeginInfo"));
    StructPtrFromApiDump<VkSubpassEndInfo>(ctx, call.Arg("pSubpassEndInfo"));
}

void ApiDump_vkCmdEndRenderPass2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSubpassEndInfo>(ctx, call.Arg("pSubpassEndInfo"));
}

void ApiDump_vkGetSwapchainStatusKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceExternalFencePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalFenceInfo>(ctx, call.Arg("pExternalFenceInfo"));
    StructPtrFromApiDump<VkExternalFenceProperties>(ctx, call.Arg("pExternalFenceProperties"));
}

void ApiDump_vkImportFenceWin32HandleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImportFenceWin32HandleInfoKHR>(ctx, call.Arg("pImportFenceWin32HandleInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetFenceWin32HandleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkFenceGetWin32HandleInfoKHR>(ctx, call.Arg("pGetWin32HandleInfo"));
    ctx.VoidPtrValue(call.Arg("pHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkImportFenceFdKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImportFenceFdInfoKHR>(ctx, call.Arg("pImportFenceFdInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetFenceFdKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkFenceGetFdInfoKHR>(ctx, call.Arg("pGetFdInfo"));
    ctx.Int32Ptr(call.Arg("pFd"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.UInt32Ptr(call.Arg("pCounterCount"));
    StructArrayFromApiDump<VkPerformanceCounterKHR>(ctx, call.Arg("pCounters"), ctx.Length(call.Arg("pCounterCount")));
    StructArrayFromApiDump<VkPerformanceCounterDescriptionKHR>(ctx, call.Arg("pCounterDescriptions"), ctx.Length(call.Arg("pCounterCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkQueryPoolPerformanceCreateInfoKHR>(ctx, call.Arg("pPerformanceQueryCreateInfo"));
    ctx.UInt32Ptr(call.Arg("pNumPasses"));
}

void ApiDump_vkAcquireProfilingLockKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAcquireProfilingLockInfoKHR>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkReleaseProfilingLockKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
}

void ApiDump_vkGetPhysicalDeviceSurfaceCapabilities2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ctx, call.Arg("pSurfaceInfo"));
    StructPtrFromApiDump<VkSurfaceCapabilities2KHR>(ctx, call.Arg("pSurfaceCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfaceFormats2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ctx, call.Arg("pSurfaceInfo"));
    ctx.UInt32Ptr(call.Arg("pSurfaceFormatCount"));
    StructArrayFromApiDump<VkSurfaceFormat2KHR>(ctx, call.Arg("pSurfaceFormats"), ctx.Length(call.Arg("pSurfaceFormatCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceDisplayProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayProperties2KHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayPlaneProperties2KHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDisplayModeProperties2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkDisplayModeProperties2KHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDisplayPlaneCapabilities2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkDisplayPlaneInfo2KHR>(ctx, call.Arg("pDisplayPlaneInfo"));
    StructPtrFromApiDump<VkDisplayPlaneCapabilities2KHR>(ctx, call.Arg("pCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetImageMemoryRequirements2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetBufferMemoryRequirements2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetImageSparseMemoryRequirements2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageSparseMemoryRequirementsInfo2>(ctx, call.Arg("pInfo"));
    ctx.UInt32Ptr(call.Arg("pSparseMemoryRequirementCount"));
    StructArrayFromApiDump<VkSparseImageMemoryRequirements2>(ctx, call.Arg("pSparseMemoryRequirements"), ctx.Length(call.Arg("pSparseMemoryRequirementCount")));
}

void ApiDump_vkCreateSamplerYcbcrConversionKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSamplerYcbcrConversionCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pYcbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroySamplerYcbcrConversionKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("ycbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("ycbcrConversion"), VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION);
}

void ApiDump_vkBindBufferMemory2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindBufferMemoryInfo>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkBindImageMemory2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindImageMemoryInfo>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDescriptorSetLayoutSupportKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorSetLayoutCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkDescriptorSetLayoutSupport>(ctx, call.Arg("pSupport"));
}

void ApiDump_vkCmdDrawIndirectCountKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawIndexedIndirectCountKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkGetSemaphoreCounterValueKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    ctx.UInt64Ptr(call.Arg("pValue"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkWaitSemaphoresKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreWaitInfo>(ctx, call.Arg("pWaitInfo"));
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSignalSemaphoreKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreSignalInfo>(ctx, call.Arg("pSignalInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceFragmentShadingRatesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pFragmentShadingRateCount"));
    StructArrayFromApiDump<VkPhysicalDeviceFragmentShadingRateKHR>(ctx, call.Arg("pFragmentShadingRates"), ctx.Length(call.Arg("pFragmentShadingRateCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetFragmentShadingRateKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkExtent2D>(ctx, call.Arg("pFragmentSize"));
    ctx.EnumArray(call.Arg("combinerOps"), EnumFromString_VkFragmentShadingRateCombinerOpKHR, 2);
}

void ApiDump_vkCmdSetRenderingAttachmentLocationsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingAttachmentLocationInfo>(ctx, call.Arg("pLocationInfo"));
}

void ApiDump_vkCmdSetRenderingInputAttachmentIndicesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingInputAttachmentIndexInfo>(ctx, call.Arg("pInputAttachmentIndexInfo"));
}

void ApiDump_vkWaitForPresentKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt64Value(call.Arg("presentId"));
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetBufferDeviceAddressKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetBufferOpaqueCaptureAddressKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetDeviceMemoryOpaqueCaptureAddressKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceMemoryOpaqueCaptureAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCreateDeferredOperationKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pDeferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDeferredOperationKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("operation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("operation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
}

void ApiDump_vkGetDeferredOperationMaxConcurrencyKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("operation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkGetDeferredOperationResultKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("operation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPipelineExecutablePropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineInfoKHR>(ctx, call.Arg("pPipelineInfo"));
    ctx.UInt32Ptr(call.Arg("pExecutableCount"));
    StructArrayFromApiDump<VkPipelineExecutablePropertiesKHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pExecutableCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPipelineExecutableStatisticsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineExecutableInfoKHR>(ctx, call.Arg("pExecutableInfo"));
    ctx.UInt32Ptr(call.Arg("pStatisticCount"));
    StructArrayFromApiDump<VkPipelineExecutableStatisticKHR>(ctx, call.Arg("pStatistics"), ctx.Length(call.Arg("pStatisticCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPipelineExecutableInternalRepresentationsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineExecutableInfoKHR>(ctx, call.Arg("pExecutableInfo"));
    ctx.UInt32Ptr(call.Arg("pInternalRepresentationCount"));
    StructArrayFromApiDump<VkPipelineExecutableInternalRepresentationKHR>(ctx, call.Arg("pInternalRepresentations"), ctx.Length(call.Arg("pInternalRepresentationCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkMapMemory2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryMapInfo>(ctx, call.Arg("pMemoryMapInfo"));
    ctx.VoidPtrValue(call.Arg("ppData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkUnmapMemory2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryUnmapInfo>(ctx, call.Arg("pMemoryUnmapInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR>(ctx, call.Arg("pQualityLevelInfo"));
    StructPtrFromApiDump<VkVideoEncodeQualityLevelPropertiesKHR>(ctx, call.Arg("pQualityLevelProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetEncodedVideoSessionParametersKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkVideoEncodeSessionParametersGetInfoKHR>(ctx, call.Arg("pVideoSessionParametersInfo"));
    StructPtrFromApiDump<VkVideoEncodeSessionParametersFeedbackInfoKHR>(ctx, call.Arg("pFeedbackInfo"));
    ctx.SizeTPtr(call.Arg("pDataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdEncodeVideoKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkVideoEncodeInfoKHR>(ctx, call.Arg("pEncodeInfo"));
}

void ApiDump_vkCmdSetEvent2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    StructPtrFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfo"));
}

void ApiDump_vkCmdResetEvent2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("event"), VK_OBJECT_TYPE_EVENT);
    ctx.Flags64Value(call.Arg("stageMask"), EnumFromString_VkPipelineStageFlagBits2);
}

void ApiDump_vkCmdWaitEvents2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("eventCount"));
    ctx.VulkanHandleArray(call.Arg("pEvents"), VK_OBJECT_TYPE_EVENT, ctx.Length(call.Arg("eventCount")));
    StructArrayFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfos"), ctx.Length(call.Arg("eventCount")));
}

void ApiDump_vkCmdPipelineBarrier2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDependencyInfo>(ctx, call.Arg("pDependencyInfo"));
}

void ApiDump_vkCmdWriteTimestamp2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.Flags64Value(call.Arg("stage"), EnumFromString_VkPipelineStageFlagBits2);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
}

void ApiDump_vkQueueSubmit2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Value(call.Arg("submitCount"));
    StructArrayFromApiDump<VkSubmitInfo2>(ctx, call.Arg("pSubmits"), ctx.Length(call.Arg("submitCount")));
    ctx.VulkanHandleValue(call.Arg("fence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBindIndexBuffer3KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBindIndexBuffer3InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdBindVertexBuffers3KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    StructArrayFromApiDump<VkBindVertexBuffer3InfoKHR>(ctx, call.Arg("pBindingInfos"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdDrawIndirect2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirect2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdDrawIndexedIndirect2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirect2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdDispatchIndirect2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDispatchIndirect2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdCopyMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyDeviceMemoryInfoKHR>(ctx, call.Arg("pCopyMemoryInfo"));
}

void ApiDump_vkCmdCopyMemoryToImageKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyDeviceMemoryImageInfoKHR>(ctx, call.Arg("pCopyMemoryInfo"));
}

void ApiDump_vkCmdCopyImageToMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyDeviceMemoryImageInfoKHR>(ctx, call.Arg("pCopyMemoryInfo"));
}

void ApiDump_vkCmdUpdateMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDeviceAddressRangeKHR>(ctx, call.Arg("pDstRange"));
    ctx.FlagsValue(call.Arg("dstFlags"), EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt64Value(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
}

void ApiDump_vkCmdFillMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDeviceAddressRangeKHR>(ctx, call.Arg("pDstRange"));
    ctx.FlagsValue(call.Arg("dstFlags"), EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.UInt32Value(call.Arg("data"));
}

void ApiDump_vkCmdCopyQueryPoolResultsToMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
    StructPtrFromApiDump<VkStridedDeviceAddressRangeKHR>(ctx, call.Arg("pDstRange"));
    ctx.FlagsValue(call.Arg("dstFlags"), EnumFromString_VkAddressCommandFlagBitsKHR);
    ctx.FlagsValue(call.Arg("queryResultFlags"), EnumFromString_VkQueryResultFlagBits);
}

void ApiDump_vkCmdDrawIndirectCount2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirectCount2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdDrawIndexedIndirectCount2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirectCount2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdBeginConditionalRendering2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkConditionalRenderingBeginInfo2EXT>(ctx, call.Arg("pConditionalRenderingBegin"));
}

void ApiDump_vkCmdBindTransformFeedbackBuffers2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    StructArrayFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ctx, call.Arg("pBindingInfos"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdBeginTransformFeedback2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstCounterRange"));
    ctx.UInt32Value(call.Arg("counterRangeCount"));
    StructArrayFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ctx, call.Arg("pCounterInfos"), ctx.Length(call.Arg("counterRangeCount")));
}

void ApiDump_vkCmdEndTransformFeedback2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstCounterRange"));
    ctx.UInt32Value(call.Arg("counterRangeCount"));
    StructArrayFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ctx, call.Arg("pCounterInfos"), ctx.Length(call.Arg("counterRangeCount")));
}

void ApiDump_vkCmdDrawIndirectByteCount2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstInstance"));
    StructPtrFromApiDump<VkBindTransformFeedbackBuffer2InfoEXT>(ctx, call.Arg("pCounterInfo"));
    ctx.UInt32Value(call.Arg("counterOffset"));
    ctx.UInt32Value(call.Arg("vertexStride"));
}

void ApiDump_vkCmdDrawMeshTasksIndirect2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirect2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdDrawMeshTasksIndirectCount2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDrawIndirectCount2InfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdWriteMarkerToMemoryAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkMemoryMarkerInfoAMD>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCreateAccelerationStructure2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureCreateInfo2KHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pAccelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyBuffer2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyBufferInfo2>(ctx, call.Arg("pCopyBufferInfo"));
}

void ApiDump_vkCmdCopyImage2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyImageInfo2>(ctx, call.Arg("pCopyImageInfo"));
}

void ApiDump_vkCmdCopyBufferToImage2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyBufferToImageInfo2>(ctx, call.Arg("pCopyBufferToImageInfo"));
}

void ApiDump_vkCmdCopyImageToBuffer2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyImageToBufferInfo2>(ctx, call.Arg("pCopyImageToBufferInfo"));
}

void ApiDump_vkCmdBlitImage2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBlitImageInfo2>(ctx, call.Arg("pBlitImageInfo"));
}

void ApiDump_vkCmdResolveImage2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkResolveImageInfo2>(ctx, call.Arg("pResolveImageInfo"));
}

void ApiDump_vkCmdTraceRaysIndirect2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt64Value(call.Arg("indirectDeviceAddress"));
}

void ApiDump_vkGetDeviceBufferMemoryRequirementsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceBufferMemoryRequirements>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetDeviceImageMemoryRequirementsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageMemoryRequirements>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkGetDeviceImageSparseMemoryRequirementsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageMemoryRequirements>(ctx, call.Arg("pInfo"));
    ctx.UInt32Ptr(call.Arg("pSparseMemoryRequirementCount"));
    StructArrayFromApiDump<VkSparseImageMemoryRequirements2>(ctx, call.Arg("pSparseMemoryRequirements"), ctx.Length(call.Arg("pSparseMemoryRequirementCount")));
}

void ApiDump_vkCmdBindIndexBuffer2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt64Value(call.Arg("size"));
    ctx.EnumValue(call.Arg("indexType"), EnumFromString_VkIndexType);
}

void ApiDump_vkGetRenderingAreaGranularityKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderingAreaInfo>(ctx, call.Arg("pRenderingAreaInfo"));
    StructPtrFromApiDump<VkExtent2D>(ctx, call.Arg("pGranularity"));
}

void ApiDump_vkGetDeviceImageSubresourceLayoutKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceImageSubresourceInfo>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkSubresourceLayout2>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkGetImageSubresourceLayout2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkImageSubresource2>(ctx, call.Arg("pSubresource"));
    StructPtrFromApiDump<VkSubresourceLayout2>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkWaitForPresent2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkPresentWait2InfoKHR>(ctx, call.Arg("pPresentWait2Info"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreatePipelineBinariesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineBinaryCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    StructPtrFromApiDump<VkPipelineBinaryHandlesInfoKHR>(ctx, call.Arg("pBinaries"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPipelineBinaryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineBinary"), VK_OBJECT_TYPE_PIPELINE_BINARY_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("pipelineBinary"), VK_OBJECT_TYPE_PIPELINE_BINARY_KHR);
}

void ApiDump_vkGetPipelineKeyKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineCreateInfoKHR>(ctx, call.Arg("pPipelineCreateInfo"));
    StructPtrFromApiDump<VkPipelineBinaryKeyKHR>(ctx, call.Arg("pPipelineKey"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPipelineBinaryDataKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineBinaryDataInfoKHR>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkPipelineBinaryKeyKHR>(ctx, call.Arg("pPipelineBinaryKey"));
    ctx.SizeTPtr(call.Arg("pPipelineBinaryDataSize"));
    ctx.VoidPtrValue(call.Arg("pPipelineBinaryData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkReleaseCapturedPipelineDataKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkReleaseCapturedPipelineDataInfoKHR>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkReleaseSwapchainImagesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkReleaseSwapchainImagesInfoKHR>(ctx, call.Arg("pReleaseInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkCooperativeMatrixPropertiesKHR>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetLineStippleKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("lineStippleFactor"));
    ctx.UInt16Value(call.Arg("lineStipplePattern"));
}

void ApiDump_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pTimeDomainCount"));
    ctx.EnumArray(call.Arg("pTimeDomains"), EnumFromString_VkTimeDomainKHR, ctx.Length(call.Arg("pTimeDomainCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetCalibratedTimestampsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("timestampCount"));
    StructArrayFromApiDump<VkCalibratedTimestampInfoKHR>(ctx, call.Arg("pTimestampInfos"), ctx.Length(call.Arg("timestampCount")));
    ctx.UInt64Array(call.Arg("pTimestamps"), ctx.Length(call.Arg("timestampCount")));
    ctx.UInt64Ptr(call.Arg("pMaxDeviation"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBindDescriptorSets2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBindDescriptorSetsInfo>(ctx, call.Arg("pBindDescriptorSetsInfo"));
}

void ApiDump_vkCmdPushConstants2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPushConstantsInfo>(ctx, call.Arg("pPushConstantsInfo"));
}

void ApiDump_vkCmdPushDescriptorSet2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPushDescriptorSetInfo>(ctx, call.Arg("pPushDescriptorSetInfo"));
}

void ApiDump_vkCmdSetDescriptorBufferOffsets2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSetDescriptorBufferOffsetsInfoEXT>(ctx, call.Arg("pSetDescriptorBufferOffsetsInfo"));
}

void ApiDump_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBindDescriptorBufferEmbeddedSamplersInfoEXT>(ctx, call.Arg("pBindDescriptorBufferEmbeddedSamplersInfo"));
}

void ApiDump_vkCmdCopyMemoryIndirectKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMemoryIndirectInfoKHR>(ctx, call.Arg("pCopyMemoryIndirectInfo"));
}

void ApiDump_vkCmdCopyMemoryToImageIndirectKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMemoryToImageIndirectInfoKHR>(ctx, call.Arg("pCopyMemoryToImageIndirectInfo"));
}

void ApiDump_vkGetDeviceFaultReportsKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt64Value(call.Arg("timeout"));
    ctx.UInt32Ptr(call.Arg("pFaultCounts"));
    StructArrayFromApiDump<VkDeviceFaultInfoKHR>(ctx, call.Arg("pFaultInfo"), ctx.Length(call.Arg("pFaultCounts")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceFaultDebugInfoKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceFaultDebugInfoKHR>(ctx, call.Arg("pDebugInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdEndRendering2KHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingEndInfoKHR>(ctx, call.Arg("pRenderingEndInfo"));
}

void ApiDump_vkFrameBoundaryANDROID(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("semaphore"), VK_OBJECT_TYPE_SEMAPHORE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
}

void ApiDump_vkCreateDebugReportCallbackEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkDebugReportCallbackCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pCallback"), VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDebugReportCallbackEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.VulkanHandleValue(call.Arg("callback"), VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("callback"), VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT);
}

void ApiDump_vkDebugReportMessageEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkDebugReportFlagBitsEXT);
    ctx.EnumValue(call.Arg("objectType"), EnumFromString_VkDebugReportObjectTypeEXT);
    ctx.UInt64Value(call.Arg("object"));
    ctx.SizeTValue(call.Arg("location"));
    ctx.Int32Value(call.Arg("messageCode"));
    ctx.StringValue(call.Arg("pLayerPrefix"));
    ctx.StringValue(call.Arg("pMessage"));
}

void ApiDump_vkDebugMarkerSetObjectTagEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDebugMarkerObjectTagInfoEXT>(ctx, call.Arg("pTagInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDebugMarkerSetObjectNameEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDebugMarkerObjectNameInfoEXT>(ctx, call.Arg("pNameInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdDebugMarkerBeginEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDebugMarkerMarkerInfoEXT>(ctx, call.Arg("pMarkerInfo"));
}

void ApiDump_vkCmdDebugMarkerEndEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkCmdDebugMarkerInsertEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDebugMarkerMarkerInfoEXT>(ctx, call.Arg("pMarkerInfo"));
}

void ApiDump_vkCmdBindTransformFeedbackBuffersEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    ctx.VulkanHandleArray(call.Arg("pBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pOffsets"), ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pSizes"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdBeginTransformFeedbackEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstCounterBuffer"));
    ctx.UInt32Value(call.Arg("counterBufferCount"));
    ctx.VulkanHandleArray(call.Arg("pCounterBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("counterBufferCount")));
    ctx.UInt64Array(call.Arg("pCounterBufferOffsets"), ctx.Length(call.Arg("counterBufferCount")));
}

void ApiDump_vkCmdEndTransformFeedbackEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstCounterBuffer"));
    ctx.UInt32Value(call.Arg("counterBufferCount"));
    ctx.VulkanHandleArray(call.Arg("pCounterBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("counterBufferCount")));
    ctx.UInt64Array(call.Arg("pCounterBufferOffsets"), ctx.Length(call.Arg("counterBufferCount")));
}

void ApiDump_vkCmdBeginQueryIndexedEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkQueryControlFlagBits);
    ctx.UInt32Value(call.Arg("index"));
}

void ApiDump_vkCmdEndQueryIndexedEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("query"));
    ctx.UInt32Value(call.Arg("index"));
}

void ApiDump_vkCmdDrawIndirectByteCountEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstInstance"));
    ctx.VulkanHandleValue(call.Arg("counterBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("counterBufferOffset"));
    ctx.UInt32Value(call.Arg("counterOffset"));
    ctx.UInt32Value(call.Arg("vertexStride"));
}

void ApiDump_vkGetImageViewHandleNVX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageViewHandleInfoNVX>(ctx, call.Arg("pInfo"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkGetImageViewHandle64NVX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImageViewHandleInfoNVX>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetImageViewAddressNVX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("imageView"), VK_OBJECT_TYPE_IMAGE_VIEW);
    StructPtrFromApiDump<VkImageViewAddressPropertiesNVX>(ctx, call.Arg("pProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceCombinedImageSamplerIndexNVX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt64Value(call.Arg("imageViewIndex"));
    ctx.UInt64Value(call.Arg("samplerIndex"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCmdDrawIndirectCountAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawIndexedIndirectCountAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkGetShaderInfoAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.EnumValue(call.Arg("shaderStage"), EnumFromString_VkShaderStageFlagBits);
    ctx.EnumValue(call.Arg("infoType"), EnumFromString_VkShaderInfoTypeAMD);
    ctx.SizeTPtr(call.Arg("pInfoSize"));
    ctx.VoidPtrValue(call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateStreamDescriptorSurfaceGGP(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkStreamDescriptorSurfaceCreateInfoGGP>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("format"), EnumFromString_VkFormat);
    ctx.EnumValue(call.Arg("type"), EnumFromString_VkImageType);
    ctx.EnumValue(call.Arg("tiling"), EnumFromString_VkImageTiling);
    ctx.FlagsValue(call.Arg("usage"), EnumFromString_VkImageUsageFlagBits);
    ctx.FlagsValue(call.Arg("flags"), EnumFromString_VkImageCreateFlagBits);
    ctx.FlagsValue(call.Arg("externalHandleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
    StructPtrFromApiDump<VkExternalImageFormatPropertiesNV>(ctx, call.Arg("pExternalImageFormatProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryWin32HandleNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.FlagsValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBitsNV);
    ctx.VoidPtrValue(call.Arg("pHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateViSurfaceNN(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkViSurfaceCreateInfoNN>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBeginConditionalRenderingEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkConditionalRenderingBeginInfoEXT>(ctx, call.Arg("pConditionalRenderingBegin"));
}

void ApiDump_vkCmdEndConditionalRenderingEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkCmdSetViewportWScalingNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstViewport"));
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkViewportWScalingNV>(ctx, call.Arg("pViewportWScalings"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkReleaseDisplayEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquireXlibDisplayEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VoidPtrValue(call.Arg("dpy"));
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetRandROutputDisplayEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VoidPtrValue(call.Arg("dpy"));
    ctx.SizeTValue(call.Arg("rrOutput"));
    ctx.VulkanHandlePtr(call.Arg("pDisplay"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfaceCapabilities2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("surface"), VK_OBJECT_TYPE_SURFACE_KHR);
    StructPtrFromApiDump<VkSurfaceCapabilities2EXT>(ctx, call.Arg("pSurfaceCapabilities"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDisplayPowerControlEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    StructPtrFromApiDump<VkDisplayPowerInfoEXT>(ctx, call.Arg("pDisplayPowerInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkRegisterDeviceEventEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceEventInfoEXT>(ctx, call.Arg("pDeviceEventInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandlePtr(call.Arg("pFence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkRegisterDisplayEventEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    StructPtrFromApiDump<VkDisplayEventInfoEXT>(ctx, call.Arg("pDisplayEventInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandlePtr(call.Arg("pFence"), VK_OBJECT_TYPE_FENCE);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSwapchainCounterEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.EnumValue(call.Arg("counter"), EnumFromString_VkSurfaceCounterFlagBitsEXT);
    ctx.UInt64Ptr(call.Arg("pCounterValue"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetRefreshCycleDurationGOOGLE(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkRefreshCycleDurationGOOGLE>(ctx, call.Arg("pDisplayTimingProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPastPresentationTimingGOOGLE(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Ptr(call.Arg("pPresentationTimingCount"));
    StructArrayFromApiDump<VkPastPresentationTimingGOOGLE>(ctx, call.Arg("pPresentationTimings"), ctx.Length(call.Arg("pPresentationTimingCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetDiscardRectangleEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstDiscardRectangle"));
    ctx.UInt32Value(call.Arg("discardRectangleCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pDiscardRectangles"), ctx.Length(call.Arg("discardRectangleCount")));
}

void ApiDump_vkCmdSetDiscardRectangleEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("discardRectangleEnable"));
}

void ApiDump_vkCmdSetDiscardRectangleModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("discardRectangleMode"), EnumFromString_VkDiscardRectangleModeEXT);
}

void ApiDump_vkSetHdrMetadataEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("swapchainCount"));
    ctx.VulkanHandleArray(call.Arg("pSwapchains"), VK_OBJECT_TYPE_SWAPCHAIN_KHR, ctx.Length(call.Arg("swapchainCount")));
    StructArrayFromApiDump<VkHdrMetadataEXT>(ctx, call.Arg("pMetadata"), ctx.Length(call.Arg("swapchainCount")));
}

void ApiDump_vkCreateIOSSurfaceMVK(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkIOSSurfaceCreateInfoMVK>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateMacOSSurfaceMVK(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkMacOSSurfaceCreateInfoMVK>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSetDebugUtilsObjectNameEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDebugUtilsObjectNameInfoEXT>(ctx, call.Arg("pNameInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSetDebugUtilsObjectTagEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDebugUtilsObjectTagInfoEXT>(ctx, call.Arg("pTagInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkQueueBeginDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    StructPtrFromApiDump<VkDebugUtilsLabelEXT>(ctx, call.Arg("pLabelInfo"));
}

void ApiDump_vkQueueEndDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
}

void ApiDump_vkQueueInsertDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    StructPtrFromApiDump<VkDebugUtilsLabelEXT>(ctx, call.Arg("pLabelInfo"));
}

void ApiDump_vkCmdBeginDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDebugUtilsLabelEXT>(ctx, call.Arg("pLabelInfo"));
}

void ApiDump_vkCmdEndDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkCmdInsertDebugUtilsLabelEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDebugUtilsLabelEXT>(ctx, call.Arg("pLabelInfo"));
}

void ApiDump_vkCreateDebugUtilsMessengerEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkDebugUtilsMessengerCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pMessenger"), VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDebugUtilsMessengerEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.VulkanHandleValue(call.Arg("messenger"), VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("messenger"), VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT);
}

void ApiDump_vkSubmitDebugUtilsMessageEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    ctx.EnumValue(call.Arg("messageSeverity"), EnumFromString_VkDebugUtilsMessageSeverityFlagBitsEXT);
    ctx.FlagsValue(call.Arg("messageTypes"), EnumFromString_VkDebugUtilsMessageTypeFlagBitsEXT);
    StructPtrFromApiDump<VkDebugUtilsMessengerCallbackDataEXT>(ctx, call.Arg("pCallbackData"));
}

void ApiDump_vkGetAndroidHardwareBufferPropertiesANDROID(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VoidPtrValue(call.Arg("buffer"));
    StructPtrFromApiDump<VkAndroidHardwareBufferPropertiesANDROID>(ctx, call.Arg("pProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryAndroidHardwareBufferANDROID(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetAndroidHardwareBufferInfoANDROID>(ctx, call.Arg("pInfo"));
    ctx.VoidPtrValue(call.Arg("pBuffer"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateGpaSessionAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkGpaSessionCreateInfoAMD>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pGpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyGpaSessionAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
}

void ApiDump_vkSetGpaDeviceClockModeAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkGpaDeviceClockModeInfoAMD>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetGpaDeviceClockInfoAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkGpaDeviceGetClockInfoAMD>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBeginGpaSessionAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdEndGpaSessionAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBeginGpaSampleAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    StructPtrFromApiDump<VkGpaSampleBeginInfoAMD>(ctx, call.Arg("pGpaSampleBeginInfo"));
    ctx.UInt32Ptr(call.Arg("pSampleID"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdEndGpaSampleAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.UInt32Value(call.Arg("sampleID"));
}

void ApiDump_vkGetGpaSessionStatusAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetGpaSessionResultsAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.UInt32Value(call.Arg("sampleID"));
    ctx.SizeTPtr(call.Arg("pSizeInBytes"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkResetGpaSessionAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyGpaSessionResultsAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("gpaSession"), VK_OBJECT_TYPE_GPA_SESSION_AMD);
}

void ApiDump_vkCmdSetSampleLocationsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkSampleLocationsInfoEXT>(ctx, call.Arg("pSampleLocationsInfo"));
}

void ApiDump_vkGetPhysicalDeviceMultisamplePropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.EnumValue(call.Arg("samples"), EnumFromString_VkSampleCountFlagBits);
    StructPtrFromApiDump<VkMultisamplePropertiesEXT>(ctx, call.Arg("pMultisampleProperties"));
}

void ApiDump_vkGetImageDrmFormatModifierPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkImageDrmFormatModifierPropertiesEXT>(ctx, call.Arg("pProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateValidationCacheEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkValidationCacheCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pValidationCache"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyValidationCacheEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("validationCache"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("validationCache"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
}

void ApiDump_vkMergeValidationCachesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("dstCache"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
    ctx.UInt32Value(call.Arg("srcCacheCount"));
    ctx.VulkanHandleArray(call.Arg("pSrcCaches"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT, ctx.Length(call.Arg("srcCacheCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetValidationCacheDataEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("validationCache"), VK_OBJECT_TYPE_VALIDATION_CACHE_EXT);
    ctx.SizeTPtr(call.Arg("pDataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBindShadingRateImageNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("imageView"), VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(call.Arg("imageLayout"), EnumFromString_VkImageLayout);
}

void ApiDump_vkCmdSetViewportShadingRatePaletteNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstViewport"));
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkShadingRatePaletteNV>(ctx, call.Arg("pShadingRatePalettes"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkCmdSetCoarseSampleOrderNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("sampleOrderType"), EnumFromString_VkCoarseSampleOrderTypeNV);
    ctx.UInt32Value(call.Arg("customSampleOrderCount"));
    StructArrayFromApiDump<VkCoarseSampleOrderCustomNV>(ctx, call.Arg("pCustomSampleOrders"), ctx.Length(call.Arg("customSampleOrderCount")));
}

void ApiDump_vkCreateAccelerationStructureNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureCreateInfoNV>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pAccelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyAccelerationStructureNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("accelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("accelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
}

void ApiDump_vkGetAccelerationStructureMemoryRequirementsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureMemoryRequirementsInfoNV>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkBindAccelerationStructureMemoryNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindAccelerationStructureMemoryInfoNV>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBuildAccelerationStructureNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkAccelerationStructureInfoNV>(ctx, call.Arg("pInfo"));
    ctx.VulkanHandleValue(call.Arg("instanceData"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("instanceOffset"));
    ctx.UInt32Value(call.Arg("update"));
    ctx.VulkanHandleValue(call.Arg("dst"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.VulkanHandleValue(call.Arg("src"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.VulkanHandleValue(call.Arg("scratch"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("scratchOffset"));
}

void ApiDump_vkCmdCopyAccelerationStructureNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("dst"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.VulkanHandleValue(call.Arg("src"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.EnumValue(call.Arg("mode"), EnumFromString_VkCopyAccelerationStructureModeKHR);
}

void ApiDump_vkCmdTraceRaysNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("raygenShaderBindingTableBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("raygenShaderBindingOffset"));
    ctx.VulkanHandleValue(call.Arg("missShaderBindingTableBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("missShaderBindingOffset"));
    ctx.UInt64Value(call.Arg("missShaderBindingStride"));
    ctx.VulkanHandleValue(call.Arg("hitShaderBindingTableBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("hitShaderBindingOffset"));
    ctx.UInt64Value(call.Arg("hitShaderBindingStride"));
    ctx.VulkanHandleValue(call.Arg("callableShaderBindingTableBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("callableShaderBindingOffset"));
    ctx.UInt64Value(call.Arg("callableShaderBindingStride"));
    ctx.UInt32Value(call.Arg("width"));
    ctx.UInt32Value(call.Arg("height"));
    ctx.UInt32Value(call.Arg("depth"));
}

void ApiDump_vkCreateRayTracingPipelinesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.UInt32Value(call.Arg("createInfoCount"));
    StructArrayFromApiDump<VkRayTracingPipelineCreateInfoNV>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("createInfoCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pPipelines"), VK_OBJECT_TYPE_PIPELINE, ctx.Length(call.Arg("createInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetRayTracingShaderGroupHandlesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("firstGroup"));
    ctx.UInt32Value(call.Arg("groupCount"));
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetRayTracingShaderGroupHandlesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("firstGroup"));
    ctx.UInt32Value(call.Arg("groupCount"));
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetAccelerationStructureHandleNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("accelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV);
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdWriteAccelerationStructuresPropertiesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("accelerationStructureCount"));
    ctx.VulkanHandleArray(call.Arg("pAccelerationStructures"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV, ctx.Length(call.Arg("accelerationStructureCount")));
    ctx.EnumValue(call.Arg("queryType"), EnumFromString_VkQueryType);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
}

void ApiDump_vkCompileDeferredNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("shader"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryHostPointerPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(call.Arg("pHostPointer"));
    StructPtrFromApiDump<VkMemoryHostPointerPropertiesEXT>(ctx, call.Arg("pMemoryHostPointerProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdWriteBufferMarkerAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineStage"), EnumFromString_VkPipelineStageFlagBits);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("dstOffset"));
    ctx.UInt32Value(call.Arg("marker"));
}

void ApiDump_vkCmdWriteBufferMarker2AMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.Flags64Value(call.Arg("stage"), EnumFromString_VkPipelineStageFlagBits2);
    ctx.VulkanHandleValue(call.Arg("dstBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("dstOffset"));
    ctx.UInt32Value(call.Arg("marker"));
}

void ApiDump_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pTimeDomainCount"));
    ctx.EnumArray(call.Arg("pTimeDomains"), EnumFromString_VkTimeDomainKHR, ctx.Length(call.Arg("pTimeDomainCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetCalibratedTimestampsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("timestampCount"));
    StructArrayFromApiDump<VkCalibratedTimestampInfoKHR>(ctx, call.Arg("pTimestampInfos"), ctx.Length(call.Arg("timestampCount")));
    ctx.UInt64Array(call.Arg("pTimestamps"), ctx.Length(call.Arg("timestampCount")));
    ctx.UInt64Ptr(call.Arg("pMaxDeviation"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdDrawMeshTasksNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("taskCount"));
    ctx.UInt32Value(call.Arg("firstTask"));
}

void ApiDump_vkCmdDrawMeshTasksIndirectNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt32Value(call.Arg("drawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawMeshTasksIndirectCountNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdSetExclusiveScissorEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstExclusiveScissor"));
    ctx.UInt32Value(call.Arg("exclusiveScissorCount"));
    ctx.UInt32Array(call.Arg("pExclusiveScissorEnables"), ctx.Length(call.Arg("exclusiveScissorCount")));
}

void ApiDump_vkCmdSetExclusiveScissorNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstExclusiveScissor"));
    ctx.UInt32Value(call.Arg("exclusiveScissorCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pExclusiveScissors"), ctx.Length(call.Arg("exclusiveScissorCount")));
}

void ApiDump_vkCmdSetCheckpointNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VoidPtrValue(call.Arg("pCheckpointMarker"));
}

void ApiDump_vkGetQueueCheckpointDataNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Ptr(call.Arg("pCheckpointDataCount"));
    StructArrayFromApiDump<VkCheckpointDataNV>(ctx, call.Arg("pCheckpointData"), ctx.Length(call.Arg("pCheckpointDataCount")));
}

void ApiDump_vkGetQueueCheckpointData2NV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.UInt32Ptr(call.Arg("pCheckpointDataCount"));
    StructArrayFromApiDump<VkCheckpointData2NV>(ctx, call.Arg("pCheckpointData"), ctx.Length(call.Arg("pCheckpointDataCount")));
}

void ApiDump_vkSetSwapchainPresentTimingQueueSizeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Value(call.Arg("size"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSwapchainTimingPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkSwapchainTimingPropertiesEXT>(ctx, call.Arg("pSwapchainTimingProperties"));
    ctx.UInt64Ptr(call.Arg("pSwapchainTimingPropertiesCounter"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSwapchainTimeDomainPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkSwapchainTimeDomainPropertiesEXT>(ctx, call.Arg("pSwapchainTimeDomainProperties"));
    ctx.UInt64Ptr(call.Arg("pTimeDomainsCounter"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPastPresentationTimingEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPastPresentationTimingInfoEXT>(ctx, call.Arg("pPastPresentationTimingInfo"));
    StructPtrFromApiDump<VkPastPresentationTimingPropertiesEXT>(ctx, call.Arg("pPastPresentationTimingProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkInitializePerformanceApiINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkInitializePerformanceApiInfoINTEL>(ctx, call.Arg("pInitializeInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkUninitializePerformanceApiINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
}

void ApiDump_vkCmdSetPerformanceMarkerINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPerformanceMarkerInfoINTEL>(ctx, call.Arg("pMarkerInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetPerformanceStreamMarkerINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPerformanceStreamMarkerInfoINTEL>(ctx, call.Arg("pMarkerInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetPerformanceOverrideINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPerformanceOverrideInfoINTEL>(ctx, call.Arg("pOverrideInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquirePerformanceConfigurationINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPerformanceConfigurationAcquireInfoINTEL>(ctx, call.Arg("pAcquireInfo"));
    ctx.VulkanHandlePtr(call.Arg("pConfiguration"), VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkReleasePerformanceConfigurationINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("configuration"), VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkQueueSetPerformanceConfigurationINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    ctx.VulkanHandleValue(call.Arg("configuration"), VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPerformanceParameterINTEL(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("parameter"), EnumFromString_VkPerformanceParameterTypeINTEL);
    StructPtrFromApiDump<VkPerformanceValueINTEL>(ctx, call.Arg("pValue"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSetLocalDimmingAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapChain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.UInt32Value(call.Arg("localDimmingEnable"));
}

void ApiDump_vkCreateImagePipeSurfaceFUCHSIA(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkImagePipeSurfaceCreateInfoFUCHSIA>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateMetalSurfaceEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkMetalSurfaceCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetBufferDeviceAddressEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkBufferDeviceAddressInfo>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkGetPhysicalDeviceToolPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pToolCount"));
    StructArrayFromApiDump<VkPhysicalDeviceToolProperties>(ctx, call.Arg("pToolProperties"), ctx.Length(call.Arg("pToolCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkCooperativeMatrixPropertiesNV>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pCombinationCount"));
    StructArrayFromApiDump<VkFramebufferMixedSamplesCombinationNV>(ctx, call.Arg("pCombinations"), ctx.Length(call.Arg("pCombinationCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceSurfacePresentModes2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ctx, call.Arg("pSurfaceInfo"));
    ctx.UInt32Ptr(call.Arg("pPresentModeCount"));
    ctx.EnumArray(call.Arg("pPresentModes"), EnumFromString_VkPresentModeKHR, ctx.Length(call.Arg("pPresentModeCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquireFullScreenExclusiveModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkReleaseFullScreenExclusiveModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceGroupSurfacePresentModes2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceSurfaceInfo2KHR>(ctx, call.Arg("pSurfaceInfo"));
    ctx.FlagsValue(call.Arg("pModes"), EnumFromString_VkDeviceGroupPresentModeFlagBitsKHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateHeadlessSurfaceEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkHeadlessSurfaceCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetLineStippleEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("lineStippleFactor"));
    ctx.UInt16Value(call.Arg("lineStipplePattern"));
}

void ApiDump_vkResetQueryPoolEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
    ctx.UInt32Value(call.Arg("queryCount"));
}

void ApiDump_vkCmdSetCullModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("cullMode"), EnumFromString_VkCullModeFlagBits);
}

void ApiDump_vkCmdSetFrontFaceEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("frontFace"), EnumFromString_VkFrontFace);
}

void ApiDump_vkCmdSetPrimitiveTopologyEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("primitiveTopology"), EnumFromString_VkPrimitiveTopology);
}

void ApiDump_vkCmdSetViewportWithCountEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkViewport>(ctx, call.Arg("pViewports"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkCmdSetScissorWithCountEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("scissorCount"));
    StructArrayFromApiDump<VkRect2D>(ctx, call.Arg("pScissors"), ctx.Length(call.Arg("scissorCount")));
}

void ApiDump_vkCmdBindVertexBuffers2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstBinding"));
    ctx.UInt32Value(call.Arg("bindingCount"));
    ctx.VulkanHandleArray(call.Arg("pBuffers"), VK_OBJECT_TYPE_BUFFER, ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pOffsets"), ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pSizes"), ctx.Length(call.Arg("bindingCount")));
    ctx.UInt64Array(call.Arg("pStrides"), ctx.Length(call.Arg("bindingCount")));
}

void ApiDump_vkCmdSetDepthTestEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthTestEnable"));
}

void ApiDump_vkCmdSetDepthWriteEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthWriteEnable"));
}

void ApiDump_vkCmdSetDepthCompareOpEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("depthCompareOp"), EnumFromString_VkCompareOp);
}

void ApiDump_vkCmdSetDepthBoundsTestEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthBoundsTestEnable"));
}

void ApiDump_vkCmdSetStencilTestEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("stencilTestEnable"));
}

void ApiDump_vkCmdSetStencilOpEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("faceMask"), EnumFromString_VkStencilFaceFlagBits);
    ctx.EnumValue(call.Arg("failOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("passOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("depthFailOp"), EnumFromString_VkStencilOp);
    ctx.EnumValue(call.Arg("compareOp"), EnumFromString_VkCompareOp);
}

void ApiDump_vkCopyMemoryToImageEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyMemoryToImageInfo>(ctx, call.Arg("pCopyMemoryToImageInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyImageToMemoryEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyImageToMemoryInfo>(ctx, call.Arg("pCopyImageToMemoryInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyImageToImageEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkCopyImageToImageInfo>(ctx, call.Arg("pCopyImageToImageInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkTransitionImageLayoutEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("transitionCount"));
    StructArrayFromApiDump<VkHostImageLayoutTransitionInfo>(ctx, call.Arg("pTransitions"), ctx.Length(call.Arg("transitionCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetImageSubresourceLayout2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("image"), VK_OBJECT_TYPE_IMAGE);
    StructPtrFromApiDump<VkImageSubresource2>(ctx, call.Arg("pSubresource"));
    StructPtrFromApiDump<VkSubresourceLayout2>(ctx, call.Arg("pLayout"));
}

void ApiDump_vkReleaseSwapchainImagesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkReleaseSwapchainImagesInfoKHR>(ctx, call.Arg("pReleaseInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetGeneratedCommandsMemoryRequirementsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoNV>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkCmdPreprocessGeneratedCommandsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkGeneratedCommandsInfoNV>(ctx, call.Arg("pGeneratedCommandsInfo"));
}

void ApiDump_vkCmdExecuteGeneratedCommandsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("isPreprocessed"));
    StructPtrFromApiDump<VkGeneratedCommandsInfoNV>(ctx, call.Arg("pGeneratedCommandsInfo"));
}

void ApiDump_vkCmdBindPipelineShaderGroupNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("groupIndex"));
}

void ApiDump_vkCreateIndirectCommandsLayoutNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkIndirectCommandsLayoutCreateInfoNV>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pIndirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyIndirectCommandsLayoutNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("indirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("indirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV);
}

void ApiDump_vkCmdSetDepthBias2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDepthBiasInfoEXT>(ctx, call.Arg("pDepthBiasInfo"));
}

void ApiDump_vkAcquireDrmDisplayEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.Int32Value(call.Arg("drmFd"));
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDrmDisplayEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.Int32Value(call.Arg("drmFd"));
    ctx.UInt32Value(call.Arg("connectorId"));
    ctx.VulkanHandlePtr(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreatePrivateDataSlotEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPrivateDataSlotCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pPrivateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyPrivateDataSlotEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
}

void ApiDump_vkSetPrivateDataEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("objectType"), EnumFromString_VkObjectType);
    ctx.UInt64Value(call.Arg("objectHandle"));
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.UInt64Value(call.Arg("data"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPrivateDataEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("objectType"), EnumFromString_VkObjectType);
    ctx.UInt64Value(call.Arg("objectHandle"));
    ctx.VulkanHandleValue(call.Arg("privateDataSlot"), VK_OBJECT_TYPE_PRIVATE_DATA_SLOT);
    ctx.UInt64Ptr(call.Arg("pData"));
}

void ApiDump_vkQueueSetPerfHintQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    StructPtrFromApiDump<VkPerfHintInfoQCOM>(ctx, call.Arg("pPerfHintInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdDispatchTileQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDispatchTileInfoQCOM>(ctx, call.Arg("pDispatchTileInfo"));
}

void ApiDump_vkCmdBeginPerTileExecutionQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPerTileBeginInfoQCOM>(ctx, call.Arg("pPerTileBeginInfo"));
}

void ApiDump_vkCmdEndPerTileExecutionQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkPerTileEndInfoQCOM>(ctx, call.Arg("pPerTileEndInfo"));
}

void ApiDump_vkGetDescriptorSetLayoutSizeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    ctx.UInt64Ptr(call.Arg("pLayoutSizeInBytes"));
}

void ApiDump_vkGetDescriptorSetLayoutBindingOffsetEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT);
    ctx.UInt32Value(call.Arg("binding"));
    ctx.UInt64Ptr(call.Arg("pOffset"));
}

void ApiDump_vkGetDescriptorEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorGetInfoEXT>(ctx, call.Arg("pDescriptorInfo"));
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pDescriptor"));
}

void ApiDump_vkCmdBindDescriptorBuffersEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("bufferCount"));
    StructArrayFromApiDump<VkDescriptorBufferBindingInfoEXT>(ctx, call.Arg("pBindingInfos"), ctx.Length(call.Arg("bufferCount")));
}

void ApiDump_vkCmdSetDescriptorBufferOffsetsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(call.Arg("firstSet"));
    ctx.UInt32Value(call.Arg("setCount"));
    ctx.UInt32Array(call.Arg("pBufferIndices"), ctx.Length(call.Arg("setCount")));
    ctx.UInt64Array(call.Arg("pOffsets"), ctx.Length(call.Arg("setCount")));
}

void ApiDump_vkCmdBindDescriptorBufferEmbeddedSamplersEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("layout"), VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(call.Arg("set"));
}

void ApiDump_vkCmdSetFragmentShadingRateEnumNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("shadingRate"), EnumFromString_VkFragmentShadingRateNV);
    ctx.EnumArray(call.Arg("combinerOps"), EnumFromString_VkFragmentShadingRateCombinerOpKHR, 2);
}

void ApiDump_vkGetDeviceFaultInfoEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceFaultCountsEXT>(ctx, call.Arg("pFaultCounts"));
    StructPtrFromApiDump<VkDeviceFaultInfoEXT>(ctx, call.Arg("pFaultInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkAcquireWinrtDisplayNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.VulkanHandleValue(call.Arg("display"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetWinrtDisplayNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("deviceRelativeId"));
    ctx.VulkanHandlePtr(call.Arg("pDisplay"), VK_OBJECT_TYPE_DISPLAY_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateDirectFBSurfaceEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkDirectFBSurfaceCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceDirectFBPresentationSupportEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VoidPtrValue(call.Arg("dfb"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkCmdSetVertexInputEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("vertexBindingDescriptionCount"));
    StructArrayFromApiDump<VkVertexInputBindingDescription2EXT>(ctx, call.Arg("pVertexBindingDescriptions"), ctx.Length(call.Arg("vertexBindingDescriptionCount")));
    ctx.UInt32Value(call.Arg("vertexAttributeDescriptionCount"));
    StructArrayFromApiDump<VkVertexInputAttributeDescription2EXT>(ctx, call.Arg("pVertexAttributeDescriptions"), ctx.Length(call.Arg("vertexAttributeDescriptionCount")));
}

void ApiDump_vkGetMemoryZirconHandleFUCHSIA(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetZirconHandleInfoFUCHSIA>(ctx, call.Arg("pGetZirconHandleInfo"));
    ctx.UInt32Ptr(call.Arg("pZirconHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryZirconHandlePropertiesFUCHSIA(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.UInt32Value(call.Arg("zirconHandle"));
    StructPtrFromApiDump<VkMemoryZirconHandlePropertiesFUCHSIA>(ctx, call.Arg("pMemoryZirconHandleProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkImportSemaphoreZirconHandleFUCHSIA(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkImportSemaphoreZirconHandleInfoFUCHSIA>(ctx, call.Arg("pImportSemaphoreZirconHandleInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetSemaphoreZirconHandleFUCHSIA(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkSemaphoreGetZirconHandleInfoFUCHSIA>(ctx, call.Arg("pGetZirconHandleInfo"));
    ctx.UInt32Ptr(call.Arg("pZirconHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBindInvocationMaskHUAWEI(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("imageView"), VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(call.Arg("imageLayout"), EnumFromString_VkImageLayout);
}

void ApiDump_vkGetMemoryRemoteAddressNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetRemoteAddressInfoNV>(ctx, call.Arg("pMemoryGetRemoteAddressInfo"));
    ctx.VoidPtrValue(call.Arg("pAddress"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetPatchControlPointsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("patchControlPoints"));
}

void ApiDump_vkCmdSetRasterizerDiscardEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("rasterizerDiscardEnable"));
}

void ApiDump_vkCmdSetDepthBiasEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthBiasEnable"));
}

void ApiDump_vkCmdSetLogicOpEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("logicOp"), EnumFromString_VkLogicOp);
}

void ApiDump_vkCmdSetPrimitiveRestartEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("primitiveRestartEnable"));
}

void ApiDump_vkCreateScreenSurfaceQNX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("instance"), VK_OBJECT_TYPE_INSTANCE);
    StructPtrFromApiDump<VkScreenSurfaceCreateInfoQNX>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSurface"), VK_OBJECT_TYPE_SURFACE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceScreenPresentationSupportQNX(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.VoidPtrValue(call.Arg("window"));
    ctx.UInt32Value(call.ReturnValue());
}

void ApiDump_vkCmdSetColorWriteEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("attachmentCount"));
    ctx.UInt32Array(call.Arg("pColorWriteEnables"), ctx.Length(call.Arg("attachmentCount")));
}

void ApiDump_vkCmdDrawMultiEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("drawCount"));
    StructArrayFromApiDump<VkMultiDrawInfoEXT>(ctx, call.Arg("pVertexInfo"), ctx.Length(call.Arg("drawCount")));
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstInstance"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawMultiIndexedEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("drawCount"));
    StructArrayFromApiDump<VkMultiDrawIndexedInfoEXT>(ctx, call.Arg("pIndexInfo"), ctx.Length(call.Arg("drawCount")));
    ctx.UInt32Value(call.Arg("instanceCount"));
    ctx.UInt32Value(call.Arg("firstInstance"));
    ctx.UInt32Value(call.Arg("stride"));
    ctx.Int32Ptr(call.Arg("pVertexOffset"));
}

void ApiDump_vkCreateMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMicromapCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pMicromap"), VK_OBJECT_TYPE_MICROMAP_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("micromap"), VK_OBJECT_TYPE_MICROMAP_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("micromap"), VK_OBJECT_TYPE_MICROMAP_EXT);
}

void ApiDump_vkCmdBuildMicromapsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("infoCount"));
    StructArrayFromApiDump<VkMicromapBuildInfoEXT>(ctx, call.Arg("pInfos"), ctx.Length(call.Arg("infoCount")));
}

void ApiDump_vkBuildMicromapsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    ctx.UInt32Value(call.Arg("infoCount"));
    StructArrayFromApiDump<VkMicromapBuildInfoEXT>(ctx, call.Arg("pInfos"), ctx.Length(call.Arg("infoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkCopyMicromapInfoEXT>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyMicromapToMemoryEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkCopyMicromapToMemoryInfoEXT>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyMemoryToMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkCopyMemoryToMicromapInfoEXT>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkWriteMicromapsPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("micromapCount"));
    ctx.VulkanHandleArray(call.Arg("pMicromaps"), VK_OBJECT_TYPE_MICROMAP_EXT, ctx.Length(call.Arg("micromapCount")));
    ctx.EnumValue(call.Arg("queryType"), EnumFromString_VkQueryType);
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.SizeTValue(call.Arg("stride"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMicromapInfoEXT>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdCopyMicromapToMemoryEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMicromapToMemoryInfoEXT>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdCopyMemoryToMicromapEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMemoryToMicromapInfoEXT>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdWriteMicromapsPropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("micromapCount"));
    ctx.VulkanHandleArray(call.Arg("pMicromaps"), VK_OBJECT_TYPE_MICROMAP_EXT, ctx.Length(call.Arg("micromapCount")));
    ctx.EnumValue(call.Arg("queryType"), EnumFromString_VkQueryType);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
}

void ApiDump_vkGetDeviceMicromapCompatibilityEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMicromapVersionInfoEXT>(ctx, call.Arg("pVersionInfo"));
    ctx.EnumPtr(call.Arg("pCompatibility"), EnumFromString_VkAccelerationStructureCompatibilityKHR);
}

void ApiDump_vkGetMicromapBuildSizesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("buildType"), EnumFromString_VkAccelerationStructureBuildTypeKHR);
    StructPtrFromApiDump<VkMicromapBuildInfoEXT>(ctx, call.Arg("pBuildInfo"));
    StructPtrFromApiDump<VkMicromapBuildSizesInfoEXT>(ctx, call.Arg("pSizeInfo"));
}

void ApiDump_vkCmdDrawClusterHUAWEI(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("groupCountX"));
    ctx.UInt32Value(call.Arg("groupCountY"));
    ctx.UInt32Value(call.Arg("groupCountZ"));
}

void ApiDump_vkCmdDrawClusterIndirectHUAWEI(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
}

void ApiDump_vkSetDeviceMemoryPriorityEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("memory"), VK_OBJECT_TYPE_DEVICE_MEMORY);
    ctx.FloatValue(call.Arg("priority"));
}

void ApiDump_vkCmdSetDispatchParametersARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDispatchParametersARM>(ctx, call.Arg("pDispatchParameters"));
}

void ApiDump_vkGetDescriptorSetLayoutHostMappingInfoVALVE(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDescriptorSetBindingReferenceVALVE>(ctx, call.Arg("pBindingReference"));
    StructPtrFromApiDump<VkDescriptorSetLayoutHostMappingInfoVALVE>(ctx, call.Arg("pHostMapping"));
}

void ApiDump_vkGetDescriptorSetHostMappingVALVE(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("descriptorSet"), VK_OBJECT_TYPE_DESCRIPTOR_SET);
    ctx.VoidPtrValue(call.Arg("ppData"));
}

void ApiDump_vkGetPipelineIndirectMemoryRequirementsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkComputePipelineCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkCmdUpdatePipelineIndirectBufferNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("pipelineBindPoint"), EnumFromString_VkPipelineBindPoint);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
}

void ApiDump_vkGetPipelineIndirectDeviceAddressNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPipelineIndirectDeviceAddressInfoNV>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCmdSetDepthClampEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthClampEnable"));
}

void ApiDump_vkCmdSetPolygonModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("polygonMode"), EnumFromString_VkPolygonMode);
}

void ApiDump_vkCmdSetRasterizationSamplesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("rasterizationSamples"), EnumFromString_VkSampleCountFlagBits);
}

void ApiDump_vkCmdSetSampleMaskEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("samples"), EnumFromString_VkSampleCountFlagBits);
    ctx.UInt32Array(call.Arg("pSampleMask"));
}

void ApiDump_vkCmdSetAlphaToCoverageEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("alphaToCoverageEnable"));
}

void ApiDump_vkCmdSetAlphaToOneEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("alphaToOneEnable"));
}

void ApiDump_vkCmdSetLogicOpEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("logicOpEnable"));
}

void ApiDump_vkCmdSetColorBlendEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstAttachment"));
    ctx.UInt32Value(call.Arg("attachmentCount"));
    ctx.UInt32Array(call.Arg("pColorBlendEnables"), ctx.Length(call.Arg("attachmentCount")));
}

void ApiDump_vkCmdSetColorBlendEquationEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstAttachment"));
    ctx.UInt32Value(call.Arg("attachmentCount"));
    StructArrayFromApiDump<VkColorBlendEquationEXT>(ctx, call.Arg("pColorBlendEquations"), ctx.Length(call.Arg("attachmentCount")));
}

void ApiDump_vkCmdSetColorWriteMaskEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstAttachment"));
    ctx.UInt32Value(call.Arg("attachmentCount"));
    ctx.FlagsArray(call.Arg("pColorWriteMasks"), EnumFromString_VkColorComponentFlagBits, ctx.Length(call.Arg("attachmentCount")));
}

void ApiDump_vkCmdSetTessellationDomainOriginEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("domainOrigin"), EnumFromString_VkTessellationDomainOrigin);
}

void ApiDump_vkCmdSetRasterizationStreamEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("rasterizationStream"));
}

void ApiDump_vkCmdSetConservativeRasterizationModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("conservativeRasterizationMode"), EnumFromString_VkConservativeRasterizationModeEXT);
}

void ApiDump_vkCmdSetExtraPrimitiveOverestimationSizeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FloatValue(call.Arg("extraPrimitiveOverestimationSize"));
}

void ApiDump_vkCmdSetDepthClipEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("depthClipEnable"));
}

void ApiDump_vkCmdSetSampleLocationsEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("sampleLocationsEnable"));
}

void ApiDump_vkCmdSetColorBlendAdvancedEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstAttachment"));
    ctx.UInt32Value(call.Arg("attachmentCount"));
    StructArrayFromApiDump<VkColorBlendAdvancedEXT>(ctx, call.Arg("pColorBlendAdvanced"), ctx.Length(call.Arg("attachmentCount")));
}

void ApiDump_vkCmdSetProvokingVertexModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("provokingVertexMode"), EnumFromString_VkProvokingVertexModeEXT);
}

void ApiDump_vkCmdSetLineRasterizationModeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("lineRasterizationMode"), EnumFromString_VkLineRasterizationMode);
}

void ApiDump_vkCmdSetLineStippleEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("stippledLineEnable"));
}

void ApiDump_vkCmdSetDepthClipNegativeOneToOneEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("negativeOneToOne"));
}

void ApiDump_vkCmdSetViewportWScalingEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("viewportWScalingEnable"));
}

void ApiDump_vkCmdSetViewportSwizzleNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("firstViewport"));
    ctx.UInt32Value(call.Arg("viewportCount"));
    StructArrayFromApiDump<VkViewportSwizzleNV>(ctx, call.Arg("pViewportSwizzles"), ctx.Length(call.Arg("viewportCount")));
}

void ApiDump_vkCmdSetCoverageToColorEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("coverageToColorEnable"));
}

void ApiDump_vkCmdSetCoverageToColorLocationNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("coverageToColorLocation"));
}

void ApiDump_vkCmdSetCoverageModulationModeNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("coverageModulationMode"), EnumFromString_VkCoverageModulationModeNV);
}

void ApiDump_vkCmdSetCoverageModulationTableEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("coverageModulationTableEnable"));
}

void ApiDump_vkCmdSetCoverageModulationTableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("coverageModulationTableCount"));
    ctx.FloatArray(call.Arg("pCoverageModulationTable"), ctx.Length(call.Arg("coverageModulationTableCount")));
}

void ApiDump_vkCmdSetShadingRateImageEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("shadingRateImageEnable"));
}

void ApiDump_vkCmdSetRepresentativeFragmentTestEnableNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("representativeFragmentTestEnable"));
}

void ApiDump_vkCmdSetCoverageReductionModeNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("coverageReductionMode"), EnumFromString_VkCoverageReductionModeNV);
}

void ApiDump_vkCreateTensorARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkTensorCreateInfoARM>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pTensor"), VK_OBJECT_TYPE_TENSOR_ARM);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyTensorARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("tensor"), VK_OBJECT_TYPE_TENSOR_ARM);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("tensor"), VK_OBJECT_TYPE_TENSOR_ARM);
}

void ApiDump_vkCreateTensorViewARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkTensorViewCreateInfoARM>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pView"), VK_OBJECT_TYPE_TENSOR_VIEW_ARM);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyTensorViewARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("tensorView"), VK_OBJECT_TYPE_TENSOR_VIEW_ARM);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("tensorView"), VK_OBJECT_TYPE_TENSOR_VIEW_ARM);
}

void ApiDump_vkGetTensorMemoryRequirementsARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkTensorMemoryRequirementsInfoARM>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkBindTensorMemoryARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindTensorMemoryInfoARM>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDeviceTensorMemoryRequirementsARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDeviceTensorMemoryRequirementsARM>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkCmdCopyTensorARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyTensorInfoARM>(ctx, call.Arg("pCopyTensorInfo"));
}

void ApiDump_vkGetPhysicalDeviceExternalTensorPropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceExternalTensorInfoARM>(ctx, call.Arg("pExternalTensorInfo"));
    StructPtrFromApiDump<VkExternalTensorPropertiesARM>(ctx, call.Arg("pExternalTensorProperties"));
}

void ApiDump_vkGetShaderModuleIdentifierEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("shaderModule"), VK_OBJECT_TYPE_SHADER_MODULE);
    StructPtrFromApiDump<VkShaderModuleIdentifierEXT>(ctx, call.Arg("pIdentifier"));
}

void ApiDump_vkGetShaderModuleCreateInfoIdentifierEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkShaderModuleCreateInfo>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkShaderModuleIdentifierEXT>(ctx, call.Arg("pIdentifier"));
}

void ApiDump_vkGetPhysicalDeviceOpticalFlowImageFormatsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkOpticalFlowImageFormatInfoNV>(ctx, call.Arg("pOpticalFlowImageFormatInfo"));
    ctx.UInt32Ptr(call.Arg("pFormatCount"));
    StructArrayFromApiDump<VkOpticalFlowImageFormatPropertiesNV>(ctx, call.Arg("pImageFormatProperties"), ctx.Length(call.Arg("pFormatCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateOpticalFlowSessionNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkOpticalFlowSessionCreateInfoNV>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSession"), VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyOpticalFlowSessionNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("session"), VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("session"), VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV);
}

void ApiDump_vkBindOpticalFlowSessionImageNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("session"), VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV);
    ctx.EnumValue(call.Arg("bindingPoint"), EnumFromString_VkOpticalFlowSessionBindingPointNV);
    ctx.VulkanHandleValue(call.Arg("view"), VK_OBJECT_TYPE_IMAGE_VIEW);
    ctx.EnumValue(call.Arg("layout"), EnumFromString_VkImageLayout);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdOpticalFlowExecuteNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("session"), VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV);
    StructPtrFromApiDump<VkOpticalFlowExecuteInfoNV>(ctx, call.Arg("pExecuteInfo"));
}

void ApiDump_vkAntiLagUpdateAMD(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAntiLagDataAMD>(ctx, call.Arg("pData"));
}

void ApiDump_vkCreateShadersEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("createInfoCount"));
    StructArrayFromApiDump<VkShaderCreateInfoEXT>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("createInfoCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pShaders"), VK_OBJECT_TYPE_SHADER_EXT, ctx.Length(call.Arg("createInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyShaderEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("shader"), VK_OBJECT_TYPE_SHADER_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("shader"), VK_OBJECT_TYPE_SHADER_EXT);
}

void ApiDump_vkGetShaderBinaryDataEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("shader"), VK_OBJECT_TYPE_SHADER_EXT);
    ctx.SizeTPtr(call.Arg("pDataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdBindShadersEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("stageCount"));
    ctx.EnumArray(call.Arg("pStages"), EnumFromString_VkShaderStageFlagBits, ctx.Length(call.Arg("stageCount")));
    ctx.VulkanHandleArray(call.Arg("pShaders"), VK_OBJECT_TYPE_SHADER_EXT, ctx.Length(call.Arg("stageCount")));
}

void ApiDump_vkCmdSetDepthClampRangeEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.EnumValue(call.Arg("depthClampMode"), EnumFromString_VkDepthClampModeEXT);
    StructPtrFromApiDump<VkDepthClampRangeEXT>(ctx, call.Arg("pDepthClampRange"));
}

void ApiDump_vkGetFramebufferTilePropertiesQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("framebuffer"), VK_OBJECT_TYPE_FRAMEBUFFER);
    ctx.UInt32Ptr(call.Arg("pPropertiesCount"));
    StructArrayFromApiDump<VkTilePropertiesQCOM>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertiesCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDynamicRenderingTilePropertiesQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkRenderingInfo>(ctx, call.Arg("pRenderingInfo"));
    StructPtrFromApiDump<VkTilePropertiesQCOM>(ctx, call.Arg("pProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceCooperativeVectorPropertiesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkCooperativeVectorPropertiesNV>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkConvertCooperativeVectorMatrixNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkConvertCooperativeVectorMatrixInfoNV>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdConvertCooperativeVectorMatrixNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("infoCount"));
    StructArrayFromApiDump<VkConvertCooperativeVectorMatrixInfoNV>(ctx, call.Arg("pInfos"), ctx.Length(call.Arg("infoCount")));
}

void ApiDump_vkSetLatencySleepModeNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkLatencySleepModeInfoNV>(ctx, call.Arg("pSleepModeInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkLatencySleepNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkLatencySleepInfoNV>(ctx, call.Arg("pSleepInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkSetLatencyMarkerNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkSetLatencyMarkerInfoNV>(ctx, call.Arg("pLatencyMarkerInfo"));
}

void ApiDump_vkGetLatencyTimingsNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("swapchain"), VK_OBJECT_TYPE_SWAPCHAIN_KHR);
    StructPtrFromApiDump<VkGetLatencyMarkerInfoNV>(ctx, call.Arg("pLatencyMarkerInfo"));
}

void ApiDump_vkQueueNotifyOutOfBandNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("queue"), VK_OBJECT_TYPE_QUEUE);
    StructPtrFromApiDump<VkOutOfBandQueueTypeInfoNV>(ctx, call.Arg("pQueueTypeInfo"));
}

void ApiDump_vkCreateDataGraphPipelinesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    ctx.VulkanHandleValue(call.Arg("pipelineCache"), VK_OBJECT_TYPE_PIPELINE_CACHE);
    ctx.UInt32Value(call.Arg("createInfoCount"));
    StructArrayFromApiDump<VkDataGraphPipelineCreateInfoARM>(ctx, call.Arg("pCreateInfos"), ctx.Length(call.Arg("createInfoCount")));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedArray(call.Arg("pPipelines"), VK_OBJECT_TYPE_PIPELINE, ctx.Length(call.Arg("createInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCreateDataGraphPipelineSessionARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDataGraphPipelineSessionCreateInfoARM>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pSession"), VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDataGraphPipelineSessionBindPointRequirementsARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDataGraphPipelineSessionBindPointRequirementsInfoARM>(ctx, call.Arg("pInfo"));
    ctx.UInt32Ptr(call.Arg("pBindPointRequirementCount"));
    StructArrayFromApiDump<VkDataGraphPipelineSessionBindPointRequirementARM>(ctx, call.Arg("pBindPointRequirements"), ctx.Length(call.Arg("pBindPointRequirementCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDataGraphPipelineSessionMemoryRequirementsARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDataGraphPipelineSessionMemoryRequirementsInfoARM>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkBindDataGraphPipelineSessionMemoryARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("bindInfoCount"));
    StructArrayFromApiDump<VkBindDataGraphPipelineSessionMemoryInfoARM>(ctx, call.Arg("pBindInfos"), ctx.Length(call.Arg("bindInfoCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyDataGraphPipelineSessionARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("session"), VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("session"), VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
}

void ApiDump_vkCmdDispatchDataGraphARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("session"), VK_OBJECT_TYPE_DATA_GRAPH_PIPELINE_SESSION_ARM);
    StructPtrFromApiDump<VkDataGraphPipelineDispatchInfoARM>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkGetDataGraphPipelineAvailablePropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDataGraphPipelineInfoARM>(ctx, call.Arg("pPipelineInfo"));
    ctx.UInt32Ptr(call.Arg("pPropertiesCount"));
    ctx.EnumArray(call.Arg("pProperties"), EnumFromString_VkDataGraphPipelinePropertyARM, ctx.Length(call.Arg("pPropertiesCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetDataGraphPipelinePropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkDataGraphPipelineInfoARM>(ctx, call.Arg("pPipelineInfo"));
    ctx.UInt32Value(call.Arg("propertiesCount"));
    StructArrayFromApiDump<VkDataGraphPipelinePropertyQueryResultARM>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("propertiesCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.UInt32Ptr(call.Arg("pQueueFamilyDataGraphPropertyCount"));
    StructArrayFromApiDump<VkQueueFamilyDataGraphPropertiesARM>(ctx, call.Arg("pQueueFamilyDataGraphProperties"), ctx.Length(call.Arg("pQueueFamilyDataGraphPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM>(ctx, call.Arg("pQueueFamilyDataGraphProcessingEngineInfo"));
    StructPtrFromApiDump<VkQueueFamilyDataGraphProcessingEnginePropertiesARM>(ctx, call.Arg("pQueueFamilyDataGraphProcessingEngineProperties"));
}

void ApiDump_vkCmdSetAttachmentFeedbackLoopEnableEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.FlagsValue(call.Arg("aspectMask"), EnumFromString_VkImageAspectFlagBits);
}

void ApiDump_vkCmdBindTileMemoryQCOM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkTileMemoryBindInfoQCOM>(ctx, call.Arg("pTileMemoryBindInfo"));
}

void ApiDump_vkCmdDecompressMemoryEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkDecompressMemoryInfoEXT>(ctx, call.Arg("pDecompressMemoryInfoEXT"));
}

void ApiDump_vkCmdDecompressMemoryIndirectCountEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.Flags64Value(call.Arg("decompressionMethod"), EnumFromString_VkMemoryDecompressionMethodFlagBitsEXT);
    ctx.UInt64Value(call.Arg("indirectCommandsAddress"));
    ctx.UInt64Value(call.Arg("indirectCommandsCountAddress"));
    ctx.UInt32Value(call.Arg("maxDecompressionCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkGetPartitionedAccelerationStructuresBuildSizesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkPartitionedAccelerationStructureInstancesInputNV>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkAccelerationStructureBuildSizesInfoKHR>(ctx, call.Arg("pSizeInfo"));
}

void ApiDump_vkCmdBuildPartitionedAccelerationStructuresNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBuildPartitionedAccelerationStructureInfoNV>(ctx, call.Arg("pBuildInfo"));
}

void ApiDump_vkGetGeneratedCommandsMemoryRequirementsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkGeneratedCommandsMemoryRequirementsInfoEXT>(ctx, call.Arg("pInfo"));
    StructPtrFromApiDump<VkMemoryRequirements2>(ctx, call.Arg("pMemoryRequirements"));
}

void ApiDump_vkCmdPreprocessGeneratedCommandsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkGeneratedCommandsInfoEXT>(ctx, call.Arg("pGeneratedCommandsInfo"));
    ctx.VulkanHandleValue(call.Arg("stateCommandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
}

void ApiDump_vkCmdExecuteGeneratedCommandsEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("isPreprocessed"));
    StructPtrFromApiDump<VkGeneratedCommandsInfoEXT>(ctx, call.Arg("pGeneratedCommandsInfo"));
}

void ApiDump_vkCreateIndirectCommandsLayoutEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkIndirectCommandsLayoutCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pIndirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyIndirectCommandsLayoutEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("indirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("indirectCommandsLayout"), VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT);
}

void ApiDump_vkCreateIndirectExecutionSetEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkIndirectExecutionSetCreateInfoEXT>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pIndirectExecutionSet"), VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyIndirectExecutionSetEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("indirectExecutionSet"), VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("indirectExecutionSet"), VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
}

void ApiDump_vkUpdateIndirectExecutionSetPipelineEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("indirectExecutionSet"), VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    ctx.UInt32Value(call.Arg("executionSetWriteCount"));
    StructArrayFromApiDump<VkWriteIndirectExecutionSetPipelineEXT>(ctx, call.Arg("pExecutionSetWrites"), ctx.Length(call.Arg("executionSetWriteCount")));
}

void ApiDump_vkUpdateIndirectExecutionSetShaderEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("indirectExecutionSet"), VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT);
    ctx.UInt32Value(call.Arg("executionSetWriteCount"));
    StructArrayFromApiDump<VkWriteIndirectExecutionSetShaderEXT>(ctx, call.Arg("pExecutionSetWrites"), ctx.Length(call.Arg("executionSetWriteCount")));
}

void ApiDump_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkCooperativeMatrixFlexibleDimensionsPropertiesNV>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryMetalHandleEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkMemoryGetMetalHandleInfoEXT>(ctx, call.Arg("pGetMetalHandleInfo"));
    ctx.VoidPtrValue(call.Arg("pHandle"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetMemoryMetalHandlePropertiesEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("handleType"), EnumFromString_VkExternalMemoryHandleTypeFlagBits);
    ctx.VoidPtrValue(call.Arg("pHandle"));
    StructPtrFromApiDump<VkMemoryMetalHandlePropertiesEXT>(ctx, call.Arg("pMemoryMetalHandleProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    ctx.UInt32Ptr(call.Arg("pCounterCount"));
    StructArrayFromApiDump<VkPerformanceCounterARM>(ctx, call.Arg("pCounters"), ctx.Length(call.Arg("pCounterCount")));
    StructArrayFromApiDump<VkPerformanceCounterDescriptionARM>(ctx, call.Arg("pCounterDescriptions"), ctx.Length(call.Arg("pCounterCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdEndRendering2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkRenderingEndInfoKHR>(ctx, call.Arg("pRenderingEndInfo"));
}

void ApiDump_vkCmdBeginCustomResolveEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkBeginCustomResolveInfoEXT>(ctx, call.Arg("pBeginCustomResolveInfo"));
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    StructPtrFromApiDump<VkQueueFamilyDataGraphPropertiesARM>(ctx, call.Arg("pQueueFamilyDataGraphProperties"));
    StructPtrFromApiDump<VkDataGraphOpticalFlowImageFormatInfoARM>(ctx, call.Arg("pOpticalFlowImageFormatInfo"));
    ctx.UInt32Ptr(call.Arg("pFormatCount"));
    StructArrayFromApiDump<VkDataGraphOpticalFlowImageFormatPropertiesARM>(ctx, call.Arg("pImageFormatProperties"), ctx.Length(call.Arg("pFormatCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    ctx.UInt32Value(call.Arg("queueFamilyIndex"));
    StructPtrFromApiDump<VkQueueFamilyDataGraphPropertiesARM>(ctx, call.Arg("pQueueFamilyDataGraphProperties"));
    StructPtrFromApiDump<VkBaseOutStructure>(ctx, call.Arg("pProperties"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetComputeOccupancyPriorityNV(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkComputeOccupancyPriorityParametersNV>(ctx, call.Arg("pParameters"));
}

void ApiDump_vkGetPhysicalDeviceCooperativeMatrixProperties2EXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("physicalDevice"), VK_OBJECT_TYPE_PHYSICAL_DEVICE);
    StructPtrFromApiDump<VkPhysicalDeviceCooperativeMatrixInfo2EXT>(ctx, call.Arg("pCooperativeMatrixInfo"));
    ctx.UInt32Ptr(call.Arg("pPropertyCount"));
    StructArrayFromApiDump<VkCooperativeMatrixProperties2EXT>(ctx, call.Arg("pProperties"), ctx.Length(call.Arg("pPropertyCount")));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdSetPrimitiveRestartIndexEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("primitiveRestartIndex"));
}

void ApiDump_vkCreateAccelerationStructureKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureCreateInfoKHR>(ctx, call.Arg("pCreateInfo"));
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.VulkanHandleCreatedPtr(call.Arg("pAccelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkDestroyAccelerationStructureKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("accelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
    StructPtrFromApiDump<VkAllocationCallbacks>(ctx, call.Arg("pAllocator"));
    ctx.ReleaseHandle(call.Arg("accelerationStructure"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR);
}

void ApiDump_vkCmdBuildAccelerationStructuresKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("infoCount"));
    StructArrayFromApiDump<VkAccelerationStructureBuildGeometryInfoKHR>(ctx, call.Arg("pInfos"), ctx.Length(call.Arg("infoCount")));
    StructArrayFromApiDump<VkAccelerationStructureBuildRangeInfoKHR>(ctx, call.Arg("ppBuildRangeInfos"), ctx.Length(call.Arg("infoCount")));
}

void ApiDump_vkCmdBuildAccelerationStructuresIndirectKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("infoCount"));
    StructArrayFromApiDump<VkAccelerationStructureBuildGeometryInfoKHR>(ctx, call.Arg("pInfos"), ctx.Length(call.Arg("infoCount")));
    ctx.UInt64Array(call.Arg("pIndirectDeviceAddresses"), ctx.Length(call.Arg("infoCount")));
    ctx.UInt32Array(call.Arg("pIndirectStrides"), ctx.Length(call.Arg("infoCount")));
    ctx.UInt32Array(call.Arg("ppMaxPrimitiveCounts"), ctx.Length(call.Arg("infoCount")));
}

void ApiDump_vkCopyAccelerationStructureToMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkCopyAccelerationStructureToMemoryInfoKHR>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCopyMemoryToAccelerationStructureKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("deferredOperation"), VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR);
    StructPtrFromApiDump<VkCopyMemoryToAccelerationStructureInfoKHR>(ctx, call.Arg("pInfo"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkWriteAccelerationStructuresPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.UInt32Value(call.Arg("accelerationStructureCount"));
    ctx.VulkanHandleArray(call.Arg("pAccelerationStructures"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, ctx.Length(call.Arg("accelerationStructureCount")));
    ctx.EnumValue(call.Arg("queryType"), EnumFromString_VkQueryType);
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.SizeTValue(call.Arg("stride"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdCopyAccelerationStructureKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyAccelerationStructureInfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdCopyAccelerationStructureToMemoryKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyAccelerationStructureToMemoryInfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkCmdCopyMemoryToAccelerationStructureKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkCopyMemoryToAccelerationStructureInfoKHR>(ctx, call.Arg("pInfo"));
}

void ApiDump_vkGetAccelerationStructureDeviceAddressKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureDeviceAddressInfoKHR>(ctx, call.Arg("pInfo"));
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCmdWriteAccelerationStructuresPropertiesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("accelerationStructureCount"));
    ctx.VulkanHandleArray(call.Arg("pAccelerationStructures"), VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR, ctx.Length(call.Arg("accelerationStructureCount")));
    ctx.EnumValue(call.Arg("queryType"), EnumFromString_VkQueryType);
    ctx.VulkanHandleValue(call.Arg("queryPool"), VK_OBJECT_TYPE_QUERY_POOL);
    ctx.UInt32Value(call.Arg("firstQuery"));
}

void ApiDump_vkGetDeviceAccelerationStructureCompatibilityKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    StructPtrFromApiDump<VkAccelerationStructureVersionInfoKHR>(ctx, call.Arg("pVersionInfo"));
    ctx.EnumPtr(call.Arg("pCompatibility"), EnumFromString_VkAccelerationStructureCompatibilityKHR);
}

void ApiDump_vkGetAccelerationStructureBuildSizesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.EnumValue(call.Arg("buildType"), EnumFromString_VkAccelerationStructureBuildTypeKHR);
    StructPtrFromApiDump<VkAccelerationStructureBuildGeometryInfoKHR>(ctx, call.Arg("pBuildInfo"));
    ctx.UInt32Array(call.Arg("pMaxPrimitiveCounts"), ctx.Length(call.Arg("pBuildInfo")["geometryCount"]));
    StructPtrFromApiDump<VkAccelerationStructureBuildSizesInfoKHR>(ctx, call.Arg("pSizeInfo"));
}

void ApiDump_vkCmdTraceRaysKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pRaygenShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pMissShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pHitShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pCallableShaderBindingTable"));
    ctx.UInt32Value(call.Arg("width"));
    ctx.UInt32Value(call.Arg("height"));
    ctx.UInt32Value(call.Arg("depth"));
}

void ApiDump_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("firstGroup"));
    ctx.UInt32Value(call.Arg("groupCount"));
    ctx.SizeTValue(call.Arg("dataSize"));
    ctx.VoidPtrValue(call.Arg("pData"));
    ctx.EnumValue(call.ReturnValue(), EnumFromString_VkResult);
}

void ApiDump_vkCmdTraceRaysIndirectKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pRaygenShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pMissShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pHitShaderBindingTable"));
    StructPtrFromApiDump<VkStridedDeviceAddressRegionKHR>(ctx, call.Arg("pCallableShaderBindingTable"));
    ctx.UInt64Value(call.Arg("indirectDeviceAddress"));
}

void ApiDump_vkGetRayTracingShaderGroupStackSizeKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("device"), VK_OBJECT_TYPE_DEVICE);
    ctx.VulkanHandleValue(call.Arg("pipeline"), VK_OBJECT_TYPE_PIPELINE);
    ctx.UInt32Value(call.Arg("group"));
    ctx.EnumValue(call.Arg("groupShader"), EnumFromString_VkShaderGroupShaderKHR);
    ctx.UInt64Value(call.ReturnValue());
}

void ApiDump_vkCmdSetRayTracingPipelineStackSizeKHR(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("pipelineStackSize"));
}

void ApiDump_vkCmdDrawMeshTasksEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.UInt32Value(call.Arg("groupCountX"));
    ctx.UInt32Value(call.Arg("groupCountY"));
    ctx.UInt32Value(call.Arg("groupCountZ"));
}

void ApiDump_vkCmdDrawMeshTasksIndirectEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.UInt32Value(call.Arg("drawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

void ApiDump_vkCmdDrawMeshTasksIndirectCountEXT(ApiDumpContext& ctx, const ApiDumpCall& call)
{
    ctx.VulkanHandleValue(call.Arg("commandBuffer"), VK_OBJECT_TYPE_COMMAND_BUFFER);
    ctx.VulkanHandleValue(call.Arg("buffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("offset"));
    ctx.VulkanHandleValue(call.Arg("countBuffer"), VK_OBJECT_TYPE_BUFFER);
    ctx.UInt64Value(call.Arg("countBufferOffset"));
    ctx.UInt32Value(call.Arg("maxDrawCount"));
    ctx.UInt32Value(call.Arg("stride"));
}

} // namespace

const ApiDumpCommandTable& GetApiDumpCommandTable()
{
    static const ApiDumpCommandTable table = {
        { "vkCreateInstance", { format::ApiCallId::ApiCall_vkCreateInstance, ApiDump_vkCreateInstance } },
        { "vkDestroyInstance", { format::ApiCallId::ApiCall_vkDestroyInstance, ApiDump_vkDestroyInstance } },
        { "vkEnumeratePhysicalDevices", { format::ApiCallId::ApiCall_vkEnumeratePhysicalDevices, ApiDump_vkEnumeratePhysicalDevices } },
        { "vkGetPhysicalDeviceFeatures", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFeatures, ApiDump_vkGetPhysicalDeviceFeatures } },
        { "vkGetPhysicalDeviceFormatProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFormatProperties, ApiDump_vkGetPhysicalDeviceFormatProperties } },
        { "vkGetPhysicalDeviceImageFormatProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceImageFormatProperties, ApiDump_vkGetPhysicalDeviceImageFormatProperties } },
        { "vkGetPhysicalDeviceProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceProperties, ApiDump_vkGetPhysicalDeviceProperties } },
        { "vkGetPhysicalDeviceQueueFamilyProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyProperties, ApiDump_vkGetPhysicalDeviceQueueFamilyProperties } },
        { "vkGetPhysicalDeviceMemoryProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceMemoryProperties, ApiDump_vkGetPhysicalDeviceMemoryProperties } },
        { "vkCreateDevice", { format::ApiCallId::ApiCall_vkCreateDevice, ApiDump_vkCreateDevice } },
        { "vkDestroyDevice", { format::ApiCallId::ApiCall_vkDestroyDevice, ApiDump_vkDestroyDevice } },
        { "vkGetDeviceQueue", { format::ApiCallId::ApiCall_vkGetDeviceQueue, ApiDump_vkGetDeviceQueue } },
        { "vkQueueSubmit", { format::ApiCallId::ApiCall_vkQueueSubmit, ApiDump_vkQueueSubmit } },
        { "vkQueueWaitIdle", { format::ApiCallId::ApiCall_vkQueueWaitIdle, ApiDump_vkQueueWaitIdle } },
        { "vkDeviceWaitIdle", { format::ApiCallId::ApiCall_vkDeviceWaitIdle, ApiDump_vkDeviceWaitIdle } },
        { "vkAllocateMemory", { format::ApiCallId::ApiCall_vkAllocateMemory, ApiDump_vkAllocateMemory } },
        { "vkFreeMemory", { format::ApiCallId::ApiCall_vkFreeMemory, ApiDump_vkFreeMemory } },
        { "vkMapMemory", { format::ApiCallId::ApiCall_vkMapMemory, ApiDump_vkMapMemory } },
        { "vkUnmapMemory", { format::ApiCallId::ApiCall_vkUnmapMemory, ApiDump_vkUnmapMemory } },
        { "vkFlushMappedMemoryRanges", { format::ApiCallId::ApiCall_vkFlushMappedMemoryRanges, ApiDump_vkFlushMappedMemoryRanges } },
        { "vkInvalidateMappedMemoryRanges", { format::ApiCallId::ApiCall_vkInvalidateMappedMemoryRanges, ApiDump_vkInvalidateMappedMemoryRanges } },
        { "vkGetDeviceMemoryCommitment", { format::ApiCallId::ApiCall_vkGetDeviceMemoryCommitment, ApiDump_vkGetDeviceMemoryCommitment } },
        { "vkBindBufferMemory", { format::ApiCallId::ApiCall_vkBindBufferMemory, ApiDump_vkBindBufferMemory } },
        { "vkBindImageMemory", { format::ApiCallId::ApiCall_vkBindImageMemory, ApiDump_vkBindImageMemory } },
        { "vkGetBufferMemoryRequirements", { format::ApiCallId::ApiCall_vkGetBufferMemoryRequirements, ApiDump_vkGetBufferMemoryRequirements } },
        { "vkGetImageMemoryRequirements", { format::ApiCallId::ApiCall_vkGetImageMemoryRequirements, ApiDump_vkGetImageMemoryRequirements } },
        { "vkGetImageSparseMemoryRequirements", { format::ApiCallId::ApiCall_vkGetImageSparseMemoryRequirements, ApiDump_vkGetImageSparseMemoryRequirements } },
        { "vkGetPhysicalDeviceSparseImageFormatProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSparseImageFormatProperties, ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties } },
        { "vkQueueBindSparse", { format::ApiCallId::ApiCall_vkQueueBindSparse, ApiDump_vkQueueBindSparse } },
        { "vkCreateFence", { format::ApiCallId::ApiCall_vkCreateFence, ApiDump_vkCreateFence } },
        { "vkDestroyFence", { format::ApiCallId::ApiCall_vkDestroyFence, ApiDump_vkDestroyFence } },
        { "vkResetFences", { format::ApiCallId::ApiCall_vkResetFences, ApiDump_vkResetFences } },
        { "vkGetFenceStatus", { format::ApiCallId::ApiCall_vkGetFenceStatus, ApiDump_vkGetFenceStatus } },
        { "vkWaitForFences", { format::ApiCallId::ApiCall_vkWaitForFences, ApiDump_vkWaitForFences } },
        { "vkCreateSemaphore", { format::ApiCallId::ApiCall_vkCreateSemaphore, ApiDump_vkCreateSemaphore } },
        { "vkDestroySemaphore", { format::ApiCallId::ApiCall_vkDestroySemaphore, ApiDump_vkDestroySemaphore } },
        { "vkCreateQueryPool", { format::ApiCallId::ApiCall_vkCreateQueryPool, ApiDump_vkCreateQueryPool } },
        { "vkDestroyQueryPool", { format::ApiCallId::ApiCall_vkDestroyQueryPool, ApiDump_vkDestroyQueryPool } },
        { "vkGetQueryPoolResults", { format::ApiCallId::ApiCall_vkGetQueryPoolResults, ApiDump_vkGetQueryPoolResults } },
        { "vkCreateBuffer", { format::ApiCallId::ApiCall_vkCreateBuffer, ApiDump_vkCreateBuffer } },
        { "vkDestroyBuffer", { format::ApiCallId::ApiCall_vkDestroyBuffer, ApiDump_vkDestroyBuffer } },
        { "vkCreateImage", { format::ApiCallId::ApiCall_vkCreateImage, ApiDump_vkCreateImage } },
        { "vkDestroyImage", { format::ApiCallId::ApiCall_vkDestroyImage, ApiDump_vkDestroyImage } },
        { "vkGetImageSubresourceLayout", { format::ApiCallId::ApiCall_vkGetImageSubresourceLayout, ApiDump_vkGetImageSubresourceLayout } },
        { "vkCreateImageView", { format::ApiCallId::ApiCall_vkCreateImageView, ApiDump_vkCreateImageView } },
        { "vkDestroyImageView", { format::ApiCallId::ApiCall_vkDestroyImageView, ApiDump_vkDestroyImageView } },
        { "vkCreateCommandPool", { format::ApiCallId::ApiCall_vkCreateCommandPool, ApiDump_vkCreateCommandPool } },
        { "vkDestroyCommandPool", { format::ApiCallId::ApiCall_vkDestroyCommandPool, ApiDump_vkDestroyCommandPool } },
        { "vkResetCommandPool", { format::ApiCallId::ApiCall_vkResetCommandPool, ApiDump_vkResetCommandPool } },
        { "vkAllocateCommandBuffers", { format::ApiCallId::ApiCall_vkAllocateCommandBuffers, ApiDump_vkAllocateCommandBuffers } },
        { "vkFreeCommandBuffers", { format::ApiCallId::ApiCall_vkFreeCommandBuffers, ApiDump_vkFreeCommandBuffers } },
        { "vkBeginCommandBuffer", { format::ApiCallId::ApiCall_vkBeginCommandBuffer, ApiDump_vkBeginCommandBuffer } },
        { "vkEndCommandBuffer", { format::ApiCallId::ApiCall_vkEndCommandBuffer, ApiDump_vkEndCommandBuffer } },
        { "vkResetCommandBuffer", { format::ApiCallId::ApiCall_vkResetCommandBuffer, ApiDump_vkResetCommandBuffer } },
        { "vkCmdCopyBuffer", { format::ApiCallId::ApiCall_vkCmdCopyBuffer, ApiDump_vkCmdCopyBuffer } },
        { "vkCmdCopyImage", { format::ApiCallId::ApiCall_vkCmdCopyImage, ApiDump_vkCmdCopyImage } },
        { "vkCmdCopyBufferToImage", { format::ApiCallId::ApiCall_vkCmdCopyBufferToImage, ApiDump_vkCmdCopyBufferToImage } },
        { "vkCmdCopyImageToBuffer", { format::ApiCallId::ApiCall_vkCmdCopyImageToBuffer, ApiDump_vkCmdCopyImageToBuffer } },
        { "vkCmdUpdateBuffer", { format::ApiCallId::ApiCall_vkCmdUpdateBuffer, ApiDump_vkCmdUpdateBuffer } },
        { "vkCmdFillBuffer", { format::ApiCallId::ApiCall_vkCmdFillBuffer, ApiDump_vkCmdFillBuffer } },
        { "vkCmdPipelineBarrier", { format::ApiCallId::ApiCall_vkCmdPipelineBarrier, ApiDump_vkCmdPipelineBarrier } },
        { "vkCmdBeginQuery", { format::ApiCallId::ApiCall_vkCmdBeginQuery, ApiDump_vkCmdBeginQuery } },
        { "vkCmdEndQuery", { format::ApiCallId::ApiCall_vkCmdEndQuery, ApiDump_vkCmdEndQuery } },
        { "vkCmdResetQueryPool", { format::ApiCallId::ApiCall_vkCmdResetQueryPool, ApiDump_vkCmdResetQueryPool } },
        { "vkCmdWriteTimestamp", { format::ApiCallId::ApiCall_vkCmdWriteTimestamp, ApiDump_vkCmdWriteTimestamp } },
        { "vkCmdCopyQueryPoolResults", { format::ApiCallId::ApiCall_vkCmdCopyQueryPoolResults, ApiDump_vkCmdCopyQueryPoolResults } },
        { "vkCmdExecuteCommands", { format::ApiCallId::ApiCall_vkCmdExecuteCommands, ApiDump_vkCmdExecuteCommands } },
        { "vkCreateEvent", { format::ApiCallId::ApiCall_vkCreateEvent, ApiDump_vkCreateEvent } },
        { "vkDestroyEvent", { format::ApiCallId::ApiCall_vkDestroyEvent, ApiDump_vkDestroyEvent } },
        { "vkGetEventStatus", { format::ApiCallId::ApiCall_vkGetEventStatus, ApiDump_vkGetEventStatus } },
        { "vkSetEvent", { format::ApiCallId::ApiCall_vkSetEvent, ApiDump_vkSetEvent } },
        { "vkResetEvent", { format::ApiCallId::ApiCall_vkResetEvent, ApiDump_vkResetEvent } },
        { "vkCreateBufferView", { format::ApiCallId::ApiCall_vkCreateBufferView, ApiDump_vkCreateBufferView } },
        { "vkDestroyBufferView", { format::ApiCallId::ApiCall_vkDestroyBufferView, ApiDump_vkDestroyBufferView } },
        { "vkCreateShaderModule", { format::ApiCallId::ApiCall_vkCreateShaderModule, ApiDump_vkCreateShaderModule } },
        { "vkDestroyShaderModule", { format::ApiCallId::ApiCall_vkDestroyShaderModule, ApiDump_vkDestroyShaderModule } },
        { "vkCreatePipelineCache", { format::ApiCallId::ApiCall_vkCreatePipelineCache, ApiDump_vkCreatePipelineCache } },
        { "vkDestroyPipelineCache", { format::ApiCallId::ApiCall_vkDestroyPipelineCache, ApiDump_vkDestroyPipelineCache } },
        { "vkGetPipelineCacheData", { format::ApiCallId::ApiCall_vkGetPipelineCacheData, ApiDump_vkGetPipelineCacheData } },
        { "vkMergePipelineCaches", { format::ApiCallId::ApiCall_vkMergePipelineCaches, ApiDump_vkMergePipelineCaches } },
        { "vkCreateComputePipelines", { format::ApiCallId::ApiCall_vkCreateComputePipelines, ApiDump_vkCreateComputePipelines } },
        { "vkDestroyPipeline", { format::ApiCallId::ApiCall_vkDestroyPipeline, ApiDump_vkDestroyPipeline } },
        { "vkCreatePipelineLayout", { format::ApiCallId::ApiCall_vkCreatePipelineLayout, ApiDump_vkCreatePipelineLayout } },
        { "vkDestroyPipelineLayout", { format::ApiCallId::ApiCall_vkDestroyPipelineLayout, ApiDump_vkDestroyPipelineLayout } },
        { "vkCreateSampler", { format::ApiCallId::ApiCall_vkCreateSampler, ApiDump_vkCreateSampler } },
        { "vkDestroySampler", { format::ApiCallId::ApiCall_vkDestroySampler, ApiDump_vkDestroySampler } },
        { "vkCreateDescriptorSetLayout", { format::ApiCallId::ApiCall_vkCreateDescriptorSetLayout, ApiDump_vkCreateDescriptorSetLayout } },
        { "vkDestroyDescriptorSetLayout", { format::ApiCallId::ApiCall_vkDestroyDescriptorSetLayout, ApiDump_vkDestroyDescriptorSetLayout } },
        { "vkCreateDescriptorPool", { format::ApiCallId::ApiCall_vkCreateDescriptorPool, ApiDump_vkCreateDescriptorPool } },
        { "vkDestroyDescriptorPool", { format::ApiCallId::ApiCall_vkDestroyDescriptorPool, ApiDump_vkDestroyDescriptorPool } },
        { "vkResetDescriptorPool", { format::ApiCallId::ApiCall_vkResetDescriptorPool, ApiDump_vkResetDescriptorPool } },
        { "vkAllocateDescriptorSets", { format::ApiCallId::ApiCall_vkAllocateDescriptorSets, ApiDump_vkAllocateDescriptorSets } },
        { "vkFreeDescriptorSets", { format::ApiCallId::ApiCall_vkFreeDescriptorSets, ApiDump_vkFreeDescriptorSets } },
        { "vkUpdateDescriptorSets", { format::ApiCallId::ApiCall_vkUpdateDescriptorSets, ApiDump_vkUpdateDescriptorSets } },
        { "vkCmdBindPipeline", { format::ApiCallId::ApiCall_vkCmdBindPipeline, ApiDump_vkCmdBindPipeline } },
        { "vkCmdBindDescriptorSets", { format::ApiCallId::ApiCall_vkCmdBindDescriptorSets, ApiDump_vkCmdBindDescriptorSets } },
        { "vkCmdClearColorImage", { format::ApiCallId::ApiCall_vkCmdClearColorImage, ApiDump_vkCmdClearColorImage } },
        { "vkCmdDispatch", { format::ApiCallId::ApiCall_vkCmdDispatch, ApiDump_vkCmdDispatch } },
        { "vkCmdDispatchIndirect", { format::ApiCallId::ApiCall_vkCmdDispatchIndirect, ApiDump_vkCmdDispatchIndirect } },
        { "vkCmdSetEvent", { format::ApiCallId::ApiCall_vkCmdSetEvent, ApiDump_vkCmdSetEvent } },
        { "vkCmdResetEvent", { format::ApiCallId::ApiCall_vkCmdResetEvent, ApiDump_vkCmdResetEvent } },
        { "vkCmdWaitEvents", { format::ApiCallId::ApiCall_vkCmdWaitEvents, ApiDump_vkCmdWaitEvents } },
        { "vkCmdPushConstants", { format::ApiCallId::ApiCall_vkCmdPushConstants, ApiDump_vkCmdPushConstants } },
        { "vkCreateGraphicsPipelines", { format::ApiCallId::ApiCall_vkCreateGraphicsPipelines, ApiDump_vkCreateGraphicsPipelines } },
        { "vkCreateFramebuffer", { format::ApiCallId::ApiCall_vkCreateFramebuffer, ApiDump_vkCreateFramebuffer } },
        { "vkDestroyFramebuffer", { format::ApiCallId::ApiCall_vkDestroyFramebuffer, ApiDump_vkDestroyFramebuffer } },
        { "vkCreateRenderPass", { format::ApiCallId::ApiCall_vkCreateRenderPass, ApiDump_vkCreateRenderPass } },
        { "vkDestroyRenderPass", { format::ApiCallId::ApiCall_vkDestroyRenderPass, ApiDump_vkDestroyRenderPass } },
        { "vkGetRenderAreaGranularity", { format::ApiCallId::ApiCall_vkGetRenderAreaGranularity, ApiDump_vkGetRenderAreaGranularity } },
        { "vkCmdSetViewport", { format::ApiCallId::ApiCall_vkCmdSetViewport, ApiDump_vkCmdSetViewport } },
        { "vkCmdSetScissor", { format::ApiCallId::ApiCall_vkCmdSetScissor, ApiDump_vkCmdSetScissor } },
        { "vkCmdSetLineWidth", { format::ApiCallId::ApiCall_vkCmdSetLineWidth, ApiDump_vkCmdSetLineWidth } },
        { "vkCmdSetDepthBias", { format::ApiCallId::ApiCall_vkCmdSetDepthBias, ApiDump_vkCmdSetDepthBias } },
        { "vkCmdSetBlendConstants", { format::ApiCallId::ApiCall_vkCmdSetBlendConstants, ApiDump_vkCmdSetBlendConstants } },
        { "vkCmdSetDepthBounds", { format::ApiCallId::ApiCall_vkCmdSetDepthBounds, ApiDump_vkCmdSetDepthBounds } },
        { "vkCmdSetStencilCompareMask", { format::ApiCallId::ApiCall_vkCmdSetStencilCompareMask, ApiDump_vkCmdSetStencilCompareMask } },
        { "vkCmdSetStencilWriteMask", { format::ApiCallId::ApiCall_vkCmdSetStencilWriteMask, ApiDump_vkCmdSetStencilWriteMask } },
        { "vkCmdSetStencilReference", { format::ApiCallId::ApiCall_vkCmdSetStencilReference, ApiDump_vkCmdSetStencilReference } },
        { "vkCmdBindIndexBuffer", { format::ApiCallId::ApiCall_vkCmdBindIndexBuffer, ApiDump_vkCmdBindIndexBuffer } },
        { "vkCmdBindVertexBuffers", { format::ApiCallId::ApiCall_vkCmdBindVertexBuffers, ApiDump_vkCmdBindVertexBuffers } },
        { "vkCmdDraw", { format::ApiCallId::ApiCall_vkCmdDraw, ApiDump_vkCmdDraw } },
        { "vkCmdDrawIndexed", { format::ApiCallId::ApiCall_vkCmdDrawIndexed, ApiDump_vkCmdDrawIndexed } },
        { "vkCmdDrawIndirect", { format::ApiCallId::ApiCall_vkCmdDrawIndirect, ApiDump_vkCmdDrawIndirect } },
        { "vkCmdDrawIndexedIndirect", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirect, ApiDump_vkCmdDrawIndexedIndirect } },
        { "vkCmdBlitImage", { format::ApiCallId::ApiCall_vkCmdBlitImage, ApiDump_vkCmdBlitImage } },
        { "vkCmdClearDepthStencilImage", { format::ApiCallId::ApiCall_vkCmdClearDepthStencilImage, ApiDump_vkCmdClearDepthStencilImage } },
        { "vkCmdClearAttachments", { format::ApiCallId::ApiCall_vkCmdClearAttachments, ApiDump_vkCmdClearAttachments } },
        { "vkCmdResolveImage", { format::ApiCallId::ApiCall_vkCmdResolveImage, ApiDump_vkCmdResolveImage } },
        { "vkCmdBeginRenderPass", { format::ApiCallId::ApiCall_vkCmdBeginRenderPass, ApiDump_vkCmdBeginRenderPass } },
        { "vkCmdNextSubpass", { format::ApiCallId::ApiCall_vkCmdNextSubpass, ApiDump_vkCmdNextSubpass } },
        { "vkCmdEndRenderPass", { format::ApiCallId::ApiCall_vkCmdEndRenderPass, ApiDump_vkCmdEndRenderPass } },
        { "vkBindBufferMemory2", { format::ApiCallId::ApiCall_vkBindBufferMemory2, ApiDump_vkBindBufferMemory2 } },
        { "vkBindImageMemory2", { format::ApiCallId::ApiCall_vkBindImageMemory2, ApiDump_vkBindImageMemory2 } },
        { "vkGetDeviceGroupPeerMemoryFeatures", { format::ApiCallId::ApiCall_vkGetDeviceGroupPeerMemoryFeatures, ApiDump_vkGetDeviceGroupPeerMemoryFeatures } },
        { "vkCmdSetDeviceMask", { format::ApiCallId::ApiCall_vkCmdSetDeviceMask, ApiDump_vkCmdSetDeviceMask } },
        { "vkEnumeratePhysicalDeviceGroups", { format::ApiCallId::ApiCall_vkEnumeratePhysicalDeviceGroups, ApiDump_vkEnumeratePhysicalDeviceGroups } },
        { "vkGetImageMemoryRequirements2", { format::ApiCallId::ApiCall_vkGetImageMemoryRequirements2, ApiDump_vkGetImageMemoryRequirements2 } },
        { "vkGetBufferMemoryRequirements2", { format::ApiCallId::ApiCall_vkGetBufferMemoryRequirements2, ApiDump_vkGetBufferMemoryRequirements2 } },
        { "vkGetImageSparseMemoryRequirements2", { format::ApiCallId::ApiCall_vkGetImageSparseMemoryRequirements2, ApiDump_vkGetImageSparseMemoryRequirements2 } },
        { "vkGetPhysicalDeviceFeatures2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFeatures2, ApiDump_vkGetPhysicalDeviceFeatures2 } },
        { "vkGetPhysicalDeviceProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceProperties2, ApiDump_vkGetPhysicalDeviceProperties2 } },
        { "vkGetPhysicalDeviceFormatProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFormatProperties2, ApiDump_vkGetPhysicalDeviceFormatProperties2 } },
        { "vkGetPhysicalDeviceImageFormatProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceImageFormatProperties2, ApiDump_vkGetPhysicalDeviceImageFormatProperties2 } },
        { "vkGetPhysicalDeviceQueueFamilyProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyProperties2, ApiDump_vkGetPhysicalDeviceQueueFamilyProperties2 } },
        { "vkGetPhysicalDeviceMemoryProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceMemoryProperties2, ApiDump_vkGetPhysicalDeviceMemoryProperties2 } },
        { "vkGetPhysicalDeviceSparseImageFormatProperties2", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSparseImageFormatProperties2, ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties2 } },
        { "vkTrimCommandPool", { format::ApiCallId::ApiCall_vkTrimCommandPool, ApiDump_vkTrimCommandPool } },
        { "vkGetDeviceQueue2", { format::ApiCallId::ApiCall_vkGetDeviceQueue2, ApiDump_vkGetDeviceQueue2 } },
        { "vkGetPhysicalDeviceExternalBufferProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalBufferProperties, ApiDump_vkGetPhysicalDeviceExternalBufferProperties } },
        { "vkGetPhysicalDeviceExternalFenceProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalFenceProperties, ApiDump_vkGetPhysicalDeviceExternalFenceProperties } },
        { "vkGetPhysicalDeviceExternalSemaphoreProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalSemaphoreProperties, ApiDump_vkGetPhysicalDeviceExternalSemaphoreProperties } },
        { "vkCmdDispatchBase", { format::ApiCallId::ApiCall_vkCmdDispatchBase, ApiDump_vkCmdDispatchBase } },
        { "vkCreateDescriptorUpdateTemplate", { format::ApiCallId::ApiCall_vkCreateDescriptorUpdateTemplate, ApiDump_vkCreateDescriptorUpdateTemplate } },
        { "vkDestroyDescriptorUpdateTemplate", { format::ApiCallId::ApiCall_vkDestroyDescriptorUpdateTemplate, ApiDump_vkDestroyDescriptorUpdateTemplate } },
        { "vkGetDescriptorSetLayoutSupport", { format::ApiCallId::ApiCall_vkGetDescriptorSetLayoutSupport, ApiDump_vkGetDescriptorSetLayoutSupport } },
        { "vkCreateSamplerYcbcrConversion", { format::ApiCallId::ApiCall_vkCreateSamplerYcbcrConversion, ApiDump_vkCreateSamplerYcbcrConversion } },
        { "vkDestroySamplerYcbcrConversion", { format::ApiCallId::ApiCall_vkDestroySamplerYcbcrConversion, ApiDump_vkDestroySamplerYcbcrConversion } },
        { "vkResetQueryPool", { format::ApiCallId::ApiCall_vkResetQueryPool, ApiDump_vkResetQueryPool } },
        { "vkGetSemaphoreCounterValue", { format::ApiCallId::ApiCall_vkGetSemaphoreCounterValue, ApiDump_vkGetSemaphoreCounterValue } },
        { "vkWaitSemaphores", { format::ApiCallId::ApiCall_vkWaitSemaphores, ApiDump_vkWaitSemaphores } },
        { "vkSignalSemaphore", { format::ApiCallId::ApiCall_vkSignalSemaphore, ApiDump_vkSignalSemaphore } },
        { "vkGetBufferDeviceAddress", { format::ApiCallId::ApiCall_vkGetBufferDeviceAddress, ApiDump_vkGetBufferDeviceAddress } },
        { "vkGetBufferOpaqueCaptureAddress", { format::ApiCallId::ApiCall_vkGetBufferOpaqueCaptureAddress, ApiDump_vkGetBufferOpaqueCaptureAddress } },
        { "vkGetDeviceMemoryOpaqueCaptureAddress", { format::ApiCallId::ApiCall_vkGetDeviceMemoryOpaqueCaptureAddress, ApiDump_vkGetDeviceMemoryOpaqueCaptureAddress } },
        { "vkCmdDrawIndirectCount", { format::ApiCallId::ApiCall_vkCmdDrawIndirectCount, ApiDump_vkCmdDrawIndirectCount } },
        { "vkCmdDrawIndexedIndirectCount", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirectCount, ApiDump_vkCmdDrawIndexedIndirectCount } },
        { "vkCreateRenderPass2", { format::ApiCallId::ApiCall_vkCreateRenderPass2, ApiDump_vkCreateRenderPass2 } },
        { "vkCmdBeginRenderPass2", { format::ApiCallId::ApiCall_vkCmdBeginRenderPass2, ApiDump_vkCmdBeginRenderPass2 } },
        { "vkCmdNextSubpass2", { format::ApiCallId::ApiCall_vkCmdNextSubpass2, ApiDump_vkCmdNextSubpass2 } },
        { "vkCmdEndRenderPass2", { format::ApiCallId::ApiCall_vkCmdEndRenderPass2, ApiDump_vkCmdEndRenderPass2 } },
        { "vkGetPhysicalDeviceToolProperties", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceToolProperties, ApiDump_vkGetPhysicalDeviceToolProperties } },
        { "vkCreatePrivateDataSlot", { format::ApiCallId::ApiCall_vkCreatePrivateDataSlot, ApiDump_vkCreatePrivateDataSlot } },
        { "vkDestroyPrivateDataSlot", { format::ApiCallId::ApiCall_vkDestroyPrivateDataSlot, ApiDump_vkDestroyPrivateDataSlot } },
        { "vkSetPrivateData", { format::ApiCallId::ApiCall_vkSetPrivateData, ApiDump_vkSetPrivateData } },
        { "vkGetPrivateData", { format::ApiCallId::ApiCall_vkGetPrivateData, ApiDump_vkGetPrivateData } },
        { "vkCmdPipelineBarrier2", { format::ApiCallId::ApiCall_vkCmdPipelineBarrier2, ApiDump_vkCmdPipelineBarrier2 } },
        { "vkCmdWriteTimestamp2", { format::ApiCallId::ApiCall_vkCmdWriteTimestamp2, ApiDump_vkCmdWriteTimestamp2 } },
        { "vkQueueSubmit2", { format::ApiCallId::ApiCall_vkQueueSubmit2, ApiDump_vkQueueSubmit2 } },
        { "vkCmdCopyBuffer2", { format::ApiCallId::ApiCall_vkCmdCopyBuffer2, ApiDump_vkCmdCopyBuffer2 } },
        { "vkCmdCopyImage2", { format::ApiCallId::ApiCall_vkCmdCopyImage2, ApiDump_vkCmdCopyImage2 } },
        { "vkCmdCopyBufferToImage2", { format::ApiCallId::ApiCall_vkCmdCopyBufferToImage2, ApiDump_vkCmdCopyBufferToImage2 } },
        { "vkCmdCopyImageToBuffer2", { format::ApiCallId::ApiCall_vkCmdCopyImageToBuffer2, ApiDump_vkCmdCopyImageToBuffer2 } },
        { "vkGetDeviceBufferMemoryRequirements", { format::ApiCallId::ApiCall_vkGetDeviceBufferMemoryRequirements, ApiDump_vkGetDeviceBufferMemoryRequirements } },
        { "vkGetDeviceImageMemoryRequirements", { format::ApiCallId::ApiCall_vkGetDeviceImageMemoryRequirements, ApiDump_vkGetDeviceImageMemoryRequirements } },
        { "vkGetDeviceImageSparseMemoryRequirements", { format::ApiCallId::ApiCall_vkGetDeviceImageSparseMemoryRequirements, ApiDump_vkGetDeviceImageSparseMemoryRequirements } },
        { "vkCmdSetEvent2", { format::ApiCallId::ApiCall_vkCmdSetEvent2, ApiDump_vkCmdSetEvent2 } },
        { "vkCmdResetEvent2", { format::ApiCallId::ApiCall_vkCmdResetEvent2, ApiDump_vkCmdResetEvent2 } },
        { "vkCmdWaitEvents2", { format::ApiCallId::ApiCall_vkCmdWaitEvents2, ApiDump_vkCmdWaitEvents2 } },
        { "vkCmdBlitImage2", { format::ApiCallId::ApiCall_vkCmdBlitImage2, ApiDump_vkCmdBlitImage2 } },
        { "vkCmdResolveImage2", { format::ApiCallId::ApiCall_vkCmdResolveImage2, ApiDump_vkCmdResolveImage2 } },
        { "vkCmdBeginRendering", { format::ApiCallId::ApiCall_vkCmdBeginRendering, ApiDump_vkCmdBeginRendering } },
        { "vkCmdEndRendering", { format::ApiCallId::ApiCall_vkCmdEndRendering, ApiDump_vkCmdEndRendering } },
        { "vkCmdSetCullMode", { format::ApiCallId::ApiCall_vkCmdSetCullMode, ApiDump_vkCmdSetCullMode } },
        { "vkCmdSetFrontFace", { format::ApiCallId::ApiCall_vkCmdSetFrontFace, ApiDump_vkCmdSetFrontFace } },
        { "vkCmdSetPrimitiveTopology", { format::ApiCallId::ApiCall_vkCmdSetPrimitiveTopology, ApiDump_vkCmdSetPrimitiveTopology } },
        { "vkCmdSetViewportWithCount", { format::ApiCallId::ApiCall_vkCmdSetViewportWithCount, ApiDump_vkCmdSetViewportWithCount } },
        { "vkCmdSetScissorWithCount", { format::ApiCallId::ApiCall_vkCmdSetScissorWithCount, ApiDump_vkCmdSetScissorWithCount } },
        { "vkCmdBindVertexBuffers2", { format::ApiCallId::ApiCall_vkCmdBindVertexBuffers2, ApiDump_vkCmdBindVertexBuffers2 } },
        { "vkCmdSetDepthTestEnable", { format::ApiCallId::ApiCall_vkCmdSetDepthTestEnable, ApiDump_vkCmdSetDepthTestEnable } },
        { "vkCmdSetDepthWriteEnable", { format::ApiCallId::ApiCall_vkCmdSetDepthWriteEnable, ApiDump_vkCmdSetDepthWriteEnable } },
        { "vkCmdSetDepthCompareOp", { format::ApiCallId::ApiCall_vkCmdSetDepthCompareOp, ApiDump_vkCmdSetDepthCompareOp } },
        { "vkCmdSetDepthBoundsTestEnable", { format::ApiCallId::ApiCall_vkCmdSetDepthBoundsTestEnable, ApiDump_vkCmdSetDepthBoundsTestEnable } },
        { "vkCmdSetStencilTestEnable", { format::ApiCallId::ApiCall_vkCmdSetStencilTestEnable, ApiDump_vkCmdSetStencilTestEnable } },
        { "vkCmdSetStencilOp", { format::ApiCallId::ApiCall_vkCmdSetStencilOp, ApiDump_vkCmdSetStencilOp } },
        { "vkCmdSetRasterizerDiscardEnable", { format::ApiCallId::ApiCall_vkCmdSetRasterizerDiscardEnable, ApiDump_vkCmdSetRasterizerDiscardEnable } },
        { "vkCmdSetDepthBiasEnable", { format::ApiCallId::ApiCall_vkCmdSetDepthBiasEnable, ApiDump_vkCmdSetDepthBiasEnable } },
        { "vkCmdSetPrimitiveRestartEnable", { format::ApiCallId::ApiCall_vkCmdSetPrimitiveRestartEnable, ApiDump_vkCmdSetPrimitiveRestartEnable } },
        { "vkMapMemory2", { format::ApiCallId::ApiCall_vkMapMemory2, ApiDump_vkMapMemory2 } },
        { "vkUnmapMemory2", { format::ApiCallId::ApiCall_vkUnmapMemory2, ApiDump_vkUnmapMemory2 } },
        { "vkGetDeviceImageSubresourceLayout", { format::ApiCallId::ApiCall_vkGetDeviceImageSubresourceLayout, ApiDump_vkGetDeviceImageSubresourceLayout } },
        { "vkGetImageSubresourceLayout2", { format::ApiCallId::ApiCall_vkGetImageSubresourceLayout2, ApiDump_vkGetImageSubresourceLayout2 } },
        { "vkCopyMemoryToImage", { format::ApiCallId::ApiCall_vkCopyMemoryToImage, ApiDump_vkCopyMemoryToImage } },
        { "vkCopyImageToMemory", { format::ApiCallId::ApiCall_vkCopyImageToMemory, ApiDump_vkCopyImageToMemory } },
        { "vkCopyImageToImage", { format::ApiCallId::ApiCall_vkCopyImageToImage, ApiDump_vkCopyImageToImage } },
        { "vkTransitionImageLayout", { format::ApiCallId::ApiCall_vkTransitionImageLayout, ApiDump_vkTransitionImageLayout } },
        { "vkCmdPushDescriptorSet", { format::ApiCallId::ApiCall_vkCmdPushDescriptorSet, ApiDump_vkCmdPushDescriptorSet } },
        { "vkCmdBindDescriptorSets2", { format::ApiCallId::ApiCall_vkCmdBindDescriptorSets2, ApiDump_vkCmdBindDescriptorSets2 } },
        { "vkCmdPushConstants2", { format::ApiCallId::ApiCall_vkCmdPushConstants2, ApiDump_vkCmdPushConstants2 } },
        { "vkCmdPushDescriptorSet2", { format::ApiCallId::ApiCall_vkCmdPushDescriptorSet2, ApiDump_vkCmdPushDescriptorSet2 } },
        { "vkCmdSetLineStipple", { format::ApiCallId::ApiCall_vkCmdSetLineStipple, ApiDump_vkCmdSetLineStipple } },
        { "vkCmdBindIndexBuffer2", { format::ApiCallId::ApiCall_vkCmdBindIndexBuffer2, ApiDump_vkCmdBindIndexBuffer2 } },
        { "vkGetRenderingAreaGranularity", { format::ApiCallId::ApiCall_vkGetRenderingAreaGranularity, ApiDump_vkGetRenderingAreaGranularity } },
        { "vkCmdSetRenderingAttachmentLocations", { format::ApiCallId::ApiCall_vkCmdSetRenderingAttachmentLocations, ApiDump_vkCmdSetRenderingAttachmentLocations } },
        { "vkCmdSetRenderingInputAttachmentIndices", { format::ApiCallId::ApiCall_vkCmdSetRenderingInputAttachmentIndices, ApiDump_vkCmdSetRenderingInputAttachmentIndices } },
        { "vkDestroySurfaceKHR", { format::ApiCallId::ApiCall_vkDestroySurfaceKHR, ApiDump_vkDestroySurfaceKHR } },
        { "vkGetPhysicalDeviceSurfaceSupportKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceSupportKHR, ApiDump_vkGetPhysicalDeviceSurfaceSupportKHR } },
        { "vkGetPhysicalDeviceSurfaceCapabilitiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceCapabilitiesKHR, ApiDump_vkGetPhysicalDeviceSurfaceCapabilitiesKHR } },
        { "vkGetPhysicalDeviceSurfaceFormatsKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceFormatsKHR, ApiDump_vkGetPhysicalDeviceSurfaceFormatsKHR } },
        { "vkGetPhysicalDeviceSurfacePresentModesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfacePresentModesKHR, ApiDump_vkGetPhysicalDeviceSurfacePresentModesKHR } },
        { "vkCreateSwapchainKHR", { format::ApiCallId::ApiCall_vkCreateSwapchainKHR, ApiDump_vkCreateSwapchainKHR } },
        { "vkDestroySwapchainKHR", { format::ApiCallId::ApiCall_vkDestroySwapchainKHR, ApiDump_vkDestroySwapchainKHR } },
        { "vkGetSwapchainImagesKHR", { format::ApiCallId::ApiCall_vkGetSwapchainImagesKHR, ApiDump_vkGetSwapchainImagesKHR } },
        { "vkAcquireNextImageKHR", { format::ApiCallId::ApiCall_vkAcquireNextImageKHR, ApiDump_vkAcquireNextImageKHR } },
        { "vkQueuePresentKHR", { format::ApiCallId::ApiCall_vkQueuePresentKHR, ApiDump_vkQueuePresentKHR } },
        { "vkGetDeviceGroupPresentCapabilitiesKHR", { format::ApiCallId::ApiCall_vkGetDeviceGroupPresentCapabilitiesKHR, ApiDump_vkGetDeviceGroupPresentCapabilitiesKHR } },
        { "vkGetDeviceGroupSurfacePresentModesKHR", { format::ApiCallId::ApiCall_vkGetDeviceGroupSurfacePresentModesKHR, ApiDump_vkGetDeviceGroupSurfacePresentModesKHR } },
        { "vkGetPhysicalDevicePresentRectanglesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDevicePresentRectanglesKHR, ApiDump_vkGetPhysicalDevicePresentRectanglesKHR } },
        { "vkAcquireNextImage2KHR", { format::ApiCallId::ApiCall_vkAcquireNextImage2KHR, ApiDump_vkAcquireNextImage2KHR } },
        { "vkGetPhysicalDeviceDisplayPropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceDisplayPropertiesKHR, ApiDump_vkGetPhysicalDeviceDisplayPropertiesKHR } },
        { "vkGetPhysicalDeviceDisplayPlanePropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceDisplayPlanePropertiesKHR, ApiDump_vkGetPhysicalDeviceDisplayPlanePropertiesKHR } },
        { "vkGetDisplayPlaneSupportedDisplaysKHR", { format::ApiCallId::ApiCall_vkGetDisplayPlaneSupportedDisplaysKHR, ApiDump_vkGetDisplayPlaneSupportedDisplaysKHR } },
        { "vkGetDisplayModePropertiesKHR", { format::ApiCallId::ApiCall_vkGetDisplayModePropertiesKHR, ApiDump_vkGetDisplayModePropertiesKHR } },
        { "vkCreateDisplayModeKHR", { format::ApiCallId::ApiCall_vkCreateDisplayModeKHR, ApiDump_vkCreateDisplayModeKHR } },
        { "vkGetDisplayPlaneCapabilitiesKHR", { format::ApiCallId::ApiCall_vkGetDisplayPlaneCapabilitiesKHR, ApiDump_vkGetDisplayPlaneCapabilitiesKHR } },
        { "vkCreateDisplayPlaneSurfaceKHR", { format::ApiCallId::ApiCall_vkCreateDisplayPlaneSurfaceKHR, ApiDump_vkCreateDisplayPlaneSurfaceKHR } },
        { "vkCreateSharedSwapchainsKHR", { format::ApiCallId::ApiCall_vkCreateSharedSwapchainsKHR, ApiDump_vkCreateSharedSwapchainsKHR } },
        { "vkCreateXlibSurfaceKHR", { format::ApiCallId::ApiCall_vkCreateXlibSurfaceKHR, ApiDump_vkCreateXlibSurfaceKHR } },
        { "vkGetPhysicalDeviceXlibPresentationSupportKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceXlibPresentationSupportKHR, ApiDump_vkGetPhysicalDeviceXlibPresentationSupportKHR } },
        { "vkCreateXcbSurfaceKHR", { format::ApiCallId::ApiCall_vkCreateXcbSurfaceKHR, ApiDump_vkCreateXcbSurfaceKHR } },
        { "vkGetPhysicalDeviceXcbPresentationSupportKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceXcbPresentationSupportKHR, ApiDump_vkGetPhysicalDeviceXcbPresentationSupportKHR } },
        { "vkCreateWaylandSurfaceKHR", { format::ApiCallId::ApiCall_vkCreateWaylandSurfaceKHR, ApiDump_vkCreateWaylandSurfaceKHR } },
        { "vkGetPhysicalDeviceWaylandPresentationSupportKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceWaylandPresentationSupportKHR, ApiDump_vkGetPhysicalDeviceWaylandPresentationSupportKHR } },
        { "vkCreateAndroidSurfaceKHR", { format::ApiCallId::ApiCall_vkCreateAndroidSurfaceKHR, ApiDump_vkCreateAndroidSurfaceKHR } },
        { "vkCreateWin32SurfaceKHR", { format::ApiCallId::ApiCall_vkCreateWin32SurfaceKHR, ApiDump_vkCreateWin32SurfaceKHR } },
        { "vkGetPhysicalDeviceWin32PresentationSupportKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceWin32PresentationSupportKHR, ApiDump_vkGetPhysicalDeviceWin32PresentationSupportKHR } },
        { "vkGetPhysicalDeviceVideoCapabilitiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceVideoCapabilitiesKHR, ApiDump_vkGetPhysicalDeviceVideoCapabilitiesKHR } },
        { "vkGetPhysicalDeviceVideoFormatPropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceVideoFormatPropertiesKHR, ApiDump_vkGetPhysicalDeviceVideoFormatPropertiesKHR } },
        { "vkCreateVideoSessionKHR", { format::ApiCallId::ApiCall_vkCreateVideoSessionKHR, ApiDump_vkCreateVideoSessionKHR } },
        { "vkDestroyVideoSessionKHR", { format::ApiCallId::ApiCall_vkDestroyVideoSessionKHR, ApiDump_vkDestroyVideoSessionKHR } },
        { "vkGetVideoSessionMemoryRequirementsKHR", { format::ApiCallId::ApiCall_vkGetVideoSessionMemoryRequirementsKHR, ApiDump_vkGetVideoSessionMemoryRequirementsKHR } },
        { "vkBindVideoSessionMemoryKHR", { format::ApiCallId::ApiCall_vkBindVideoSessionMemoryKHR, ApiDump_vkBindVideoSessionMemoryKHR } },
        { "vkCreateVideoSessionParametersKHR", { format::ApiCallId::ApiCall_vkCreateVideoSessionParametersKHR, ApiDump_vkCreateVideoSessionParametersKHR } },
        { "vkUpdateVideoSessionParametersKHR", { format::ApiCallId::ApiCall_vkUpdateVideoSessionParametersKHR, ApiDump_vkUpdateVideoSessionParametersKHR } },
        { "vkDestroyVideoSessionParametersKHR", { format::ApiCallId::ApiCall_vkDestroyVideoSessionParametersKHR, ApiDump_vkDestroyVideoSessionParametersKHR } },
        { "vkCmdBeginVideoCodingKHR", { format::ApiCallId::ApiCall_vkCmdBeginVideoCodingKHR, ApiDump_vkCmdBeginVideoCodingKHR } },
        { "vkCmdEndVideoCodingKHR", { format::ApiCallId::ApiCall_vkCmdEndVideoCodingKHR, ApiDump_vkCmdEndVideoCodingKHR } },
        { "vkCmdControlVideoCodingKHR", { format::ApiCallId::ApiCall_vkCmdControlVideoCodingKHR, ApiDump_vkCmdControlVideoCodingKHR } },
        { "vkCmdDecodeVideoKHR", { format::ApiCallId::ApiCall_vkCmdDecodeVideoKHR, ApiDump_vkCmdDecodeVideoKHR } },
        { "vkCmdBeginRenderingKHR", { format::ApiCallId::ApiCall_vkCmdBeginRenderingKHR, ApiDump_vkCmdBeginRenderingKHR } },
        { "vkCmdEndRenderingKHR", { format::ApiCallId::ApiCall_vkCmdEndRenderingKHR, ApiDump_vkCmdEndRenderingKHR } },
        { "vkGetPhysicalDeviceFeatures2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFeatures2KHR, ApiDump_vkGetPhysicalDeviceFeatures2KHR } },
        { "vkGetPhysicalDeviceProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceProperties2KHR, ApiDump_vkGetPhysicalDeviceProperties2KHR } },
        { "vkGetPhysicalDeviceFormatProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFormatProperties2KHR, ApiDump_vkGetPhysicalDeviceFormatProperties2KHR } },
        { "vkGetPhysicalDeviceImageFormatProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceImageFormatProperties2KHR, ApiDump_vkGetPhysicalDeviceImageFormatProperties2KHR } },
        { "vkGetPhysicalDeviceQueueFamilyProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyProperties2KHR, ApiDump_vkGetPhysicalDeviceQueueFamilyProperties2KHR } },
        { "vkGetPhysicalDeviceMemoryProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceMemoryProperties2KHR, ApiDump_vkGetPhysicalDeviceMemoryProperties2KHR } },
        { "vkGetPhysicalDeviceSparseImageFormatProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSparseImageFormatProperties2KHR, ApiDump_vkGetPhysicalDeviceSparseImageFormatProperties2KHR } },
        { "vkGetDeviceGroupPeerMemoryFeaturesKHR", { format::ApiCallId::ApiCall_vkGetDeviceGroupPeerMemoryFeaturesKHR, ApiDump_vkGetDeviceGroupPeerMemoryFeaturesKHR } },
        { "vkCmdSetDeviceMaskKHR", { format::ApiCallId::ApiCall_vkCmdSetDeviceMaskKHR, ApiDump_vkCmdSetDeviceMaskKHR } },
        { "vkCmdDispatchBaseKHR", { format::ApiCallId::ApiCall_vkCmdDispatchBaseKHR, ApiDump_vkCmdDispatchBaseKHR } },
        { "vkTrimCommandPoolKHR", { format::ApiCallId::ApiCall_vkTrimCommandPoolKHR, ApiDump_vkTrimCommandPoolKHR } },
        { "vkEnumeratePhysicalDeviceGroupsKHR", { format::ApiCallId::ApiCall_vkEnumeratePhysicalDeviceGroupsKHR, ApiDump_vkEnumeratePhysicalDeviceGroupsKHR } },
        { "vkGetPhysicalDeviceExternalBufferPropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalBufferPropertiesKHR, ApiDump_vkGetPhysicalDeviceExternalBufferPropertiesKHR } },
        { "vkGetMemoryWin32HandleKHR", { format::ApiCallId::ApiCall_vkGetMemoryWin32HandleKHR, ApiDump_vkGetMemoryWin32HandleKHR } },
        { "vkGetMemoryWin32HandlePropertiesKHR", { format::ApiCallId::ApiCall_vkGetMemoryWin32HandlePropertiesKHR, ApiDump_vkGetMemoryWin32HandlePropertiesKHR } },
        { "vkGetMemoryFdKHR", { format::ApiCallId::ApiCall_vkGetMemoryFdKHR, ApiDump_vkGetMemoryFdKHR } },
        { "vkGetMemoryFdPropertiesKHR", { format::ApiCallId::ApiCall_vkGetMemoryFdPropertiesKHR, ApiDump_vkGetMemoryFdPropertiesKHR } },
        { "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR, ApiDump_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR } },
        { "vkImportSemaphoreWin32HandleKHR", { format::ApiCallId::ApiCall_vkImportSemaphoreWin32HandleKHR, ApiDump_vkImportSemaphoreWin32HandleKHR } },
        { "vkGetSemaphoreWin32HandleKHR", { format::ApiCallId::ApiCall_vkGetSemaphoreWin32HandleKHR, ApiDump_vkGetSemaphoreWin32HandleKHR } },
        { "vkImportSemaphoreFdKHR", { format::ApiCallId::ApiCall_vkImportSemaphoreFdKHR, ApiDump_vkImportSemaphoreFdKHR } },
        { "vkGetSemaphoreFdKHR", { format::ApiCallId::ApiCall_vkGetSemaphoreFdKHR, ApiDump_vkGetSemaphoreFdKHR } },
        { "vkCmdPushDescriptorSetKHR", { format::ApiCallId::ApiCall_vkCmdPushDescriptorSetKHR, ApiDump_vkCmdPushDescriptorSetKHR } },
        { "vkCreateDescriptorUpdateTemplateKHR", { format::ApiCallId::ApiCall_vkCreateDescriptorUpdateTemplateKHR, ApiDump_vkCreateDescriptorUpdateTemplateKHR } },
        { "vkDestroyDescriptorUpdateTemplateKHR", { format::ApiCallId::ApiCall_vkDestroyDescriptorUpdateTemplateKHR, ApiDump_vkDestroyDescriptorUpdateTemplateKHR } },
        { "vkCreateRenderPass2KHR", { format::ApiCallId::ApiCall_vkCreateRenderPass2KHR, ApiDump_vkCreateRenderPass2KHR } },
        { "vkCmdBeginRenderPass2KHR", { format::ApiCallId::ApiCall_vkCmdBeginRenderPass2KHR, ApiDump_vkCmdBeginRenderPass2KHR } },
        { "vkCmdNextSubpass2KHR", { format::ApiCallId::ApiCall_vkCmdNextSubpass2KHR, ApiDump_vkCmdNextSubpass2KHR } },
        { "vkCmdEndRenderPass2KHR", { format::ApiCallId::ApiCall_vkCmdEndRenderPass2KHR, ApiDump_vkCmdEndRenderPass2KHR } },
        { "vkGetSwapchainStatusKHR", { format::ApiCallId::ApiCall_vkGetSwapchainStatusKHR, ApiDump_vkGetSwapchainStatusKHR } },
        { "vkGetPhysicalDeviceExternalFencePropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalFencePropertiesKHR, ApiDump_vkGetPhysicalDeviceExternalFencePropertiesKHR } },
        { "vkImportFenceWin32HandleKHR", { format::ApiCallId::ApiCall_vkImportFenceWin32HandleKHR, ApiDump_vkImportFenceWin32HandleKHR } },
        { "vkGetFenceWin32HandleKHR", { format::ApiCallId::ApiCall_vkGetFenceWin32HandleKHR, ApiDump_vkGetFenceWin32HandleKHR } },
        { "vkImportFenceFdKHR", { format::ApiCallId::ApiCall_vkImportFenceFdKHR, ApiDump_vkImportFenceFdKHR } },
        { "vkGetFenceFdKHR", { format::ApiCallId::ApiCall_vkGetFenceFdKHR, ApiDump_vkGetFenceFdKHR } },
        { "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", { format::ApiCallId::ApiCall_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR, ApiDump_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR } },
        { "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR, ApiDump_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR } },
        { "vkAcquireProfilingLockKHR", { format::ApiCallId::ApiCall_vkAcquireProfilingLockKHR, ApiDump_vkAcquireProfilingLockKHR } },
        { "vkReleaseProfilingLockKHR", { format::ApiCallId::ApiCall_vkReleaseProfilingLockKHR, ApiDump_vkReleaseProfilingLockKHR } },
        { "vkGetPhysicalDeviceSurfaceCapabilities2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceCapabilities2KHR, ApiDump_vkGetPhysicalDeviceSurfaceCapabilities2KHR } },
        { "vkGetPhysicalDeviceSurfaceFormats2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceFormats2KHR, ApiDump_vkGetPhysicalDeviceSurfaceFormats2KHR } },
        { "vkGetPhysicalDeviceDisplayProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceDisplayProperties2KHR, ApiDump_vkGetPhysicalDeviceDisplayProperties2KHR } },
        { "vkGetPhysicalDeviceDisplayPlaneProperties2KHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceDisplayPlaneProperties2KHR, ApiDump_vkGetPhysicalDeviceDisplayPlaneProperties2KHR } },
        { "vkGetDisplayModeProperties2KHR", { format::ApiCallId::ApiCall_vkGetDisplayModeProperties2KHR, ApiDump_vkGetDisplayModeProperties2KHR } },
        { "vkGetDisplayPlaneCapabilities2KHR", { format::ApiCallId::ApiCall_vkGetDisplayPlaneCapabilities2KHR, ApiDump_vkGetDisplayPlaneCapabilities2KHR } },
        { "vkGetImageMemoryRequirements2KHR", { format::ApiCallId::ApiCall_vkGetImageMemoryRequirements2KHR, ApiDump_vkGetImageMemoryRequirements2KHR } },
        { "vkGetBufferMemoryRequirements2KHR", { format::ApiCallId::ApiCall_vkGetBufferMemoryRequirements2KHR, ApiDump_vkGetBufferMemoryRequirements2KHR } },
        { "vkGetImageSparseMemoryRequirements2KHR", { format::ApiCallId::ApiCall_vkGetImageSparseMemoryRequirements2KHR, ApiDump_vkGetImageSparseMemoryRequirements2KHR } },
        { "vkCreateSamplerYcbcrConversionKHR", { format::ApiCallId::ApiCall_vkCreateSamplerYcbcrConversionKHR, ApiDump_vkCreateSamplerYcbcrConversionKHR } },
        { "vkDestroySamplerYcbcrConversionKHR", { format::ApiCallId::ApiCall_vkDestroySamplerYcbcrConversionKHR, ApiDump_vkDestroySamplerYcbcrConversionKHR } },
        { "vkBindBufferMemory2KHR", { format::ApiCallId::ApiCall_vkBindBufferMemory2KHR, ApiDump_vkBindBufferMemory2KHR } },
        { "vkBindImageMemory2KHR", { format::ApiCallId::ApiCall_vkBindImageMemory2KHR, ApiDump_vkBindImageMemory2KHR } },
        { "vkGetDescriptorSetLayoutSupportKHR", { format::ApiCallId::ApiCall_vkGetDescriptorSetLayoutSupportKHR, ApiDump_vkGetDescriptorSetLayoutSupportKHR } },
        { "vkCmdDrawIndirectCountKHR", { format::ApiCallId::ApiCall_vkCmdDrawIndirectCountKHR, ApiDump_vkCmdDrawIndirectCountKHR } },
        { "vkCmdDrawIndexedIndirectCountKHR", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirectCountKHR, ApiDump_vkCmdDrawIndexedIndirectCountKHR } },
        { "vkGetSemaphoreCounterValueKHR", { format::ApiCallId::ApiCall_vkGetSemaphoreCounterValueKHR, ApiDump_vkGetSemaphoreCounterValueKHR } },
        { "vkWaitSemaphoresKHR", { format::ApiCallId::ApiCall_vkWaitSemaphoresKHR, ApiDump_vkWaitSemaphoresKHR } },
        { "vkSignalSemaphoreKHR", { format::ApiCallId::ApiCall_vkSignalSemaphoreKHR, ApiDump_vkSignalSemaphoreKHR } },
        { "vkGetPhysicalDeviceFragmentShadingRatesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceFragmentShadingRatesKHR, ApiDump_vkGetPhysicalDeviceFragmentShadingRatesKHR } },
        { "vkCmdSetFragmentShadingRateKHR", { format::ApiCallId::ApiCall_vkCmdSetFragmentShadingRateKHR, ApiDump_vkCmdSetFragmentShadingRateKHR } },
        { "vkCmdSetRenderingAttachmentLocationsKHR", { format::ApiCallId::ApiCall_vkCmdSetRenderingAttachmentLocationsKHR, ApiDump_vkCmdSetRenderingAttachmentLocationsKHR } },
        { "vkCmdSetRenderingInputAttachmentIndicesKHR", { format::ApiCallId::ApiCall_vkCmdSetRenderingInputAttachmentIndicesKHR, ApiDump_vkCmdSetRenderingInputAttachmentIndicesKHR } },
        { "vkWaitForPresentKHR", { format::ApiCallId::ApiCall_vkWaitForPresentKHR, ApiDump_vkWaitForPresentKHR } },
        { "vkGetBufferDeviceAddressKHR", { format::ApiCallId::ApiCall_vkGetBufferDeviceAddressKHR, ApiDump_vkGetBufferDeviceAddressKHR } },
        { "vkGetBufferOpaqueCaptureAddressKHR", { format::ApiCallId::ApiCall_vkGetBufferOpaqueCaptureAddressKHR, ApiDump_vkGetBufferOpaqueCaptureAddressKHR } },
        { "vkGetDeviceMemoryOpaqueCaptureAddressKHR", { format::ApiCallId::ApiCall_vkGetDeviceMemoryOpaqueCaptureAddressKHR, ApiDump_vkGetDeviceMemoryOpaqueCaptureAddressKHR } },
        { "vkCreateDeferredOperationKHR", { format::ApiCallId::ApiCall_vkCreateDeferredOperationKHR, ApiDump_vkCreateDeferredOperationKHR } },
        { "vkDestroyDeferredOperationKHR", { format::ApiCallId::ApiCall_vkDestroyDeferredOperationKHR, ApiDump_vkDestroyDeferredOperationKHR } },
        { "vkGetDeferredOperationMaxConcurrencyKHR", { format::ApiCallId::ApiCall_vkGetDeferredOperationMaxConcurrencyKHR, ApiDump_vkGetDeferredOperationMaxConcurrencyKHR } },
        { "vkGetDeferredOperationResultKHR", { format::ApiCallId::ApiCall_vkGetDeferredOperationResultKHR, ApiDump_vkGetDeferredOperationResultKHR } },
        { "vkGetPipelineExecutablePropertiesKHR", { format::ApiCallId::ApiCall_vkGetPipelineExecutablePropertiesKHR, ApiDump_vkGetPipelineExecutablePropertiesKHR } },
        { "vkGetPipelineExecutableStatisticsKHR", { format::ApiCallId::ApiCall_vkGetPipelineExecutableStatisticsKHR, ApiDump_vkGetPipelineExecutableStatisticsKHR } },
        { "vkGetPipelineExecutableInternalRepresentationsKHR", { format::ApiCallId::ApiCall_vkGetPipelineExecutableInternalRepresentationsKHR, ApiDump_vkGetPipelineExecutableInternalRepresentationsKHR } },
        { "vkMapMemory2KHR", { format::ApiCallId::ApiCall_vkMapMemory2KHR, ApiDump_vkMapMemory2KHR } },
        { "vkUnmapMemory2KHR", { format::ApiCallId::ApiCall_vkUnmapMemory2KHR, ApiDump_vkUnmapMemory2KHR } },
        { "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR, ApiDump_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR } },
        { "vkGetEncodedVideoSessionParametersKHR", { format::ApiCallId::ApiCall_vkGetEncodedVideoSessionParametersKHR, ApiDump_vkGetEncodedVideoSessionParametersKHR } },
        { "vkCmdEncodeVideoKHR", { format::ApiCallId::ApiCall_vkCmdEncodeVideoKHR, ApiDump_vkCmdEncodeVideoKHR } },
        { "vkCmdSetEvent2KHR", { format::ApiCallId::ApiCall_vkCmdSetEvent2KHR, ApiDump_vkCmdSetEvent2KHR } },
        { "vkCmdResetEvent2KHR", { format::ApiCallId::ApiCall_vkCmdResetEvent2KHR, ApiDump_vkCmdResetEvent2KHR } },
        { "vkCmdWaitEvents2KHR", { format::ApiCallId::ApiCall_vkCmdWaitEvents2KHR, ApiDump_vkCmdWaitEvents2KHR } },
        { "vkCmdPipelineBarrier2KHR", { format::ApiCallId::ApiCall_vkCmdPipelineBarrier2KHR, ApiDump_vkCmdPipelineBarrier2KHR } },
        { "vkCmdWriteTimestamp2KHR", { format::ApiCallId::ApiCall_vkCmdWriteTimestamp2KHR, ApiDump_vkCmdWriteTimestamp2KHR } },
        { "vkQueueSubmit2KHR", { format::ApiCallId::ApiCall_vkQueueSubmit2KHR, ApiDump_vkQueueSubmit2KHR } },
        { "vkCmdBindIndexBuffer3KHR", { format::ApiCallId::ApiCall_vkCmdBindIndexBuffer3KHR, ApiDump_vkCmdBindIndexBuffer3KHR } },
        { "vkCmdBindVertexBuffers3KHR", { format::ApiCallId::ApiCall_vkCmdBindVertexBuffers3KHR, ApiDump_vkCmdBindVertexBuffers3KHR } },
        { "vkCmdDrawIndirect2KHR", { format::ApiCallId::ApiCall_vkCmdDrawIndirect2KHR, ApiDump_vkCmdDrawIndirect2KHR } },
        { "vkCmdDrawIndexedIndirect2KHR", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirect2KHR, ApiDump_vkCmdDrawIndexedIndirect2KHR } },
        { "vkCmdDispatchIndirect2KHR", { format::ApiCallId::ApiCall_vkCmdDispatchIndirect2KHR, ApiDump_vkCmdDispatchIndirect2KHR } },
        { "vkCmdCopyMemoryKHR", { format::ApiCallId::ApiCall_vkCmdCopyMemoryKHR, ApiDump_vkCmdCopyMemoryKHR } },
        { "vkCmdCopyMemoryToImageKHR", { format::ApiCallId::ApiCall_vkCmdCopyMemoryToImageKHR, ApiDump_vkCmdCopyMemoryToImageKHR } },
        { "vkCmdCopyImageToMemoryKHR", { format::ApiCallId::ApiCall_vkCmdCopyImageToMemoryKHR, ApiDump_vkCmdCopyImageToMemoryKHR } },
        { "vkCmdUpdateMemoryKHR", { format::ApiCallId::ApiCall_vkCmdUpdateMemoryKHR, ApiDump_vkCmdUpdateMemoryKHR } },
        { "vkCmdFillMemoryKHR", { format::ApiCallId::ApiCall_vkCmdFillMemoryKHR, ApiDump_vkCmdFillMemoryKHR } },
        { "vkCmdCopyQueryPoolResultsToMemoryKHR", { format::ApiCallId::ApiCall_vkCmdCopyQueryPoolResultsToMemoryKHR, ApiDump_vkCmdCopyQueryPoolResultsToMemoryKHR } },
        { "vkCmdDrawIndirectCount2KHR", { format::ApiCallId::ApiCall_vkCmdDrawIndirectCount2KHR, ApiDump_vkCmdDrawIndirectCount2KHR } },
        { "vkCmdDrawIndexedIndirectCount2KHR", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirectCount2KHR, ApiDump_vkCmdDrawIndexedIndirectCount2KHR } },
        { "vkCmdBeginConditionalRendering2EXT", { format::ApiCallId::ApiCall_vkCmdBeginConditionalRendering2EXT, ApiDump_vkCmdBeginConditionalRendering2EXT } },
        { "vkCmdBindTransformFeedbackBuffers2EXT", { format::ApiCallId::ApiCall_vkCmdBindTransformFeedbackBuffers2EXT, ApiDump_vkCmdBindTransformFeedbackBuffers2EXT } },
        { "vkCmdBeginTransformFeedback2EXT", { format::ApiCallId::ApiCall_vkCmdBeginTransformFeedback2EXT, ApiDump_vkCmdBeginTransformFeedback2EXT } },
        { "vkCmdEndTransformFeedback2EXT", { format::ApiCallId::ApiCall_vkCmdEndTransformFeedback2EXT, ApiDump_vkCmdEndTransformFeedback2EXT } },
        { "vkCmdDrawIndirectByteCount2EXT", { format::ApiCallId::ApiCall_vkCmdDrawIndirectByteCount2EXT, ApiDump_vkCmdDrawIndirectByteCount2EXT } },
        { "vkCmdDrawMeshTasksIndirect2EXT", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirect2EXT, ApiDump_vkCmdDrawMeshTasksIndirect2EXT } },
        { "vkCmdDrawMeshTasksIndirectCount2EXT", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirectCount2EXT, ApiDump_vkCmdDrawMeshTasksIndirectCount2EXT } },
        { "vkCmdWriteMarkerToMemoryAMD", { format::ApiCallId::ApiCall_vkCmdWriteMarkerToMemoryAMD, ApiDump_vkCmdWriteMarkerToMemoryAMD } },
        { "vkCreateAccelerationStructure2KHR", { format::ApiCallId::ApiCall_vkCreateAccelerationStructure2KHR, ApiDump_vkCreateAccelerationStructure2KHR } },
        { "vkCmdCopyBuffer2KHR", { format::ApiCallId::ApiCall_vkCmdCopyBuffer2KHR, ApiDump_vkCmdCopyBuffer2KHR } },
        { "vkCmdCopyImage2KHR", { format::ApiCallId::ApiCall_vkCmdCopyImage2KHR, ApiDump_vkCmdCopyImage2KHR } },
        { "vkCmdCopyBufferToImage2KHR", { format::ApiCallId::ApiCall_vkCmdCopyBufferToImage2KHR, ApiDump_vkCmdCopyBufferToImage2KHR } },
        { "vkCmdCopyImageToBuffer2KHR", { format::ApiCallId::ApiCall_vkCmdCopyImageToBuffer2KHR, ApiDump_vkCmdCopyImageToBuffer2KHR } },
        { "vkCmdBlitImage2KHR", { format::ApiCallId::ApiCall_vkCmdBlitImage2KHR, ApiDump_vkCmdBlitImage2KHR } },
        { "vkCmdResolveImage2KHR", { format::ApiCallId::ApiCall_vkCmdResolveImage2KHR, ApiDump_vkCmdResolveImage2KHR } },
        { "vkCmdTraceRaysIndirect2KHR", { format::ApiCallId::ApiCall_vkCmdTraceRaysIndirect2KHR, ApiDump_vkCmdTraceRaysIndirect2KHR } },
        { "vkGetDeviceBufferMemoryRequirementsKHR", { format::ApiCallId::ApiCall_vkGetDeviceBufferMemoryRequirementsKHR, ApiDump_vkGetDeviceBufferMemoryRequirementsKHR } },
        { "vkGetDeviceImageMemoryRequirementsKHR", { format::ApiCallId::ApiCall_vkGetDeviceImageMemoryRequirementsKHR, ApiDump_vkGetDeviceImageMemoryRequirementsKHR } },
        { "vkGetDeviceImageSparseMemoryRequirementsKHR", { format::ApiCallId::ApiCall_vkGetDeviceImageSparseMemoryRequirementsKHR, ApiDump_vkGetDeviceImageSparseMemoryRequirementsKHR } },
        { "vkCmdBindIndexBuffer2KHR", { format::ApiCallId::ApiCall_vkCmdBindIndexBuffer2KHR, ApiDump_vkCmdBindIndexBuffer2KHR } },
        { "vkGetRenderingAreaGranularityKHR", { format::ApiCallId::ApiCall_vkGetRenderingAreaGranularityKHR, ApiDump_vkGetRenderingAreaGranularityKHR } },
        { "vkGetDeviceImageSubresourceLayoutKHR", { format::ApiCallId::ApiCall_vkGetDeviceImageSubresourceLayoutKHR, ApiDump_vkGetDeviceImageSubresourceLayoutKHR } },
        { "vkGetImageSubresourceLayout2KHR", { format::ApiCallId::ApiCall_vkGetImageSubresourceLayout2KHR, ApiDump_vkGetImageSubresourceLayout2KHR } },
        { "vkWaitForPresent2KHR", { format::ApiCallId::ApiCall_vkWaitForPresent2KHR, ApiDump_vkWaitForPresent2KHR } },
        { "vkCreatePipelineBinariesKHR", { format::ApiCallId::ApiCall_vkCreatePipelineBinariesKHR, ApiDump_vkCreatePipelineBinariesKHR } },
        { "vkDestroyPipelineBinaryKHR", { format::ApiCallId::ApiCall_vkDestroyPipelineBinaryKHR, ApiDump_vkDestroyPipelineBinaryKHR } },
        { "vkGetPipelineKeyKHR", { format::ApiCallId::ApiCall_vkGetPipelineKeyKHR, ApiDump_vkGetPipelineKeyKHR } },
        { "vkGetPipelineBinaryDataKHR", { format::ApiCallId::ApiCall_vkGetPipelineBinaryDataKHR, ApiDump_vkGetPipelineBinaryDataKHR } },
        { "vkReleaseCapturedPipelineDataKHR", { format::ApiCallId::ApiCall_vkReleaseCapturedPipelineDataKHR, ApiDump_vkReleaseCapturedPipelineDataKHR } },
        { "vkReleaseSwapchainImagesKHR", { format::ApiCallId::ApiCall_vkReleaseSwapchainImagesKHR, ApiDump_vkReleaseSwapchainImagesKHR } },
        { "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR, ApiDump_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR } },
        { "vkCmdSetLineStippleKHR", { format::ApiCallId::ApiCall_vkCmdSetLineStippleKHR, ApiDump_vkCmdSetLineStippleKHR } },
        { "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR, ApiDump_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR } },
        { "vkGetCalibratedTimestampsKHR", { format::ApiCallId::ApiCall_vkGetCalibratedTimestampsKHR, ApiDump_vkGetCalibratedTimestampsKHR } },
        { "vkCmdBindDescriptorSets2KHR", { format::ApiCallId::ApiCall_vkCmdBindDescriptorSets2KHR, ApiDump_vkCmdBindDescriptorSets2KHR } },
        { "vkCmdPushConstants2KHR", { format::ApiCallId::ApiCall_vkCmdPushConstants2KHR, ApiDump_vkCmdPushConstants2KHR } },
        { "vkCmdPushDescriptorSet2KHR", { format::ApiCallId::ApiCall_vkCmdPushDescriptorSet2KHR, ApiDump_vkCmdPushDescriptorSet2KHR } },
        { "vkCmdSetDescriptorBufferOffsets2EXT", { format::ApiCallId::ApiCall_vkCmdSetDescriptorBufferOffsets2EXT, ApiDump_vkCmdSetDescriptorBufferOffsets2EXT } },
        { "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT", { format::ApiCallId::ApiCall_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT, ApiDump_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT } },
        { "vkCmdCopyMemoryIndirectKHR", { format::ApiCallId::ApiCall_vkCmdCopyMemoryIndirectKHR, ApiDump_vkCmdCopyMemoryIndirectKHR } },
        { "vkCmdCopyMemoryToImageIndirectKHR", { format::ApiCallId::ApiCall_vkCmdCopyMemoryToImageIndirectKHR, ApiDump_vkCmdCopyMemoryToImageIndirectKHR } },
        { "vkGetDeviceFaultReportsKHR", { format::ApiCallId::ApiCall_vkGetDeviceFaultReportsKHR, ApiDump_vkGetDeviceFaultReportsKHR } },
        { "vkGetDeviceFaultDebugInfoKHR", { format::ApiCallId::ApiCall_vkGetDeviceFaultDebugInfoKHR, ApiDump_vkGetDeviceFaultDebugInfoKHR } },
        { "vkCmdEndRendering2KHR", { format::ApiCallId::ApiCall_vkCmdEndRendering2KHR, ApiDump_vkCmdEndRendering2KHR } },
        { "vkFrameBoundaryANDROID", { format::ApiCallId::ApiCall_vkFrameBoundaryANDROID, ApiDump_vkFrameBoundaryANDROID } },
        { "vkCreateDebugReportCallbackEXT", { format::ApiCallId::ApiCall_vkCreateDebugReportCallbackEXT, ApiDump_vkCreateDebugReportCallbackEXT } },
        { "vkDestroyDebugReportCallbackEXT", { format::ApiCallId::ApiCall_vkDestroyDebugReportCallbackEXT, ApiDump_vkDestroyDebugReportCallbackEXT } },
        { "vkDebugReportMessageEXT", { format::ApiCallId::ApiCall_vkDebugReportMessageEXT, ApiDump_vkDebugReportMessageEXT } },
        { "vkDebugMarkerSetObjectTagEXT", { format::ApiCallId::ApiCall_vkDebugMarkerSetObjectTagEXT, ApiDump_vkDebugMarkerSetObjectTagEXT } },
        { "vkDebugMarkerSetObjectNameEXT", { format::ApiCallId::ApiCall_vkDebugMarkerSetObjectNameEXT, ApiDump_vkDebugMarkerSetObjectNameEXT } },
        { "vkCmdDebugMarkerBeginEXT", { format::ApiCallId::ApiCall_vkCmdDebugMarkerBeginEXT, ApiDump_vkCmdDebugMarkerBeginEXT } },
        { "vkCmdDebugMarkerEndEXT", { format::ApiCallId::ApiCall_vkCmdDebugMarkerEndEXT, ApiDump_vkCmdDebugMarkerEndEXT } },
        { "vkCmdDebugMarkerInsertEXT", { format::ApiCallId::ApiCall_vkCmdDebugMarkerInsertEXT, ApiDump_vkCmdDebugMarkerInsertEXT } },
        { "vkCmdBindTransformFeedbackBuffersEXT", { format::ApiCallId::ApiCall_vkCmdBindTransformFeedbackBuffersEXT, ApiDump_vkCmdBindTransformFeedbackBuffersEXT } },
        { "vkCmdBeginTransformFeedbackEXT", { format::ApiCallId::ApiCall_vkCmdBeginTransformFeedbackEXT, ApiDump_vkCmdBeginTransformFeedbackEXT } },
        { "vkCmdEndTransformFeedbackEXT", { format::ApiCallId::ApiCall_vkCmdEndTransformFeedbackEXT, ApiDump_vkCmdEndTransformFeedbackEXT } },
        { "vkCmdBeginQueryIndexedEXT", { format::ApiCallId::ApiCall_vkCmdBeginQueryIndexedEXT, ApiDump_vkCmdBeginQueryIndexedEXT } },
        { "vkCmdEndQueryIndexedEXT", { format::ApiCallId::ApiCall_vkCmdEndQueryIndexedEXT, ApiDump_vkCmdEndQueryIndexedEXT } },
        { "vkCmdDrawIndirectByteCountEXT", { format::ApiCallId::ApiCall_vkCmdDrawIndirectByteCountEXT, ApiDump_vkCmdDrawIndirectByteCountEXT } },
        { "vkGetImageViewHandleNVX", { format::ApiCallId::ApiCall_vkGetImageViewHandleNVX, ApiDump_vkGetImageViewHandleNVX } },
        { "vkGetImageViewHandle64NVX", { format::ApiCallId::ApiCall_vkGetImageViewHandle64NVX, ApiDump_vkGetImageViewHandle64NVX } },
        { "vkGetImageViewAddressNVX", { format::ApiCallId::ApiCall_vkGetImageViewAddressNVX, ApiDump_vkGetImageViewAddressNVX } },
        { "vkGetDeviceCombinedImageSamplerIndexNVX", { format::ApiCallId::ApiCall_vkGetDeviceCombinedImageSamplerIndexNVX, ApiDump_vkGetDeviceCombinedImageSamplerIndexNVX } },
        { "vkCmdDrawIndirectCountAMD", { format::ApiCallId::ApiCall_vkCmdDrawIndirectCountAMD, ApiDump_vkCmdDrawIndirectCountAMD } },
        { "vkCmdDrawIndexedIndirectCountAMD", { format::ApiCallId::ApiCall_vkCmdDrawIndexedIndirectCountAMD, ApiDump_vkCmdDrawIndexedIndirectCountAMD } },
        { "vkGetShaderInfoAMD", { format::ApiCallId::ApiCall_vkGetShaderInfoAMD, ApiDump_vkGetShaderInfoAMD } },
        { "vkCreateStreamDescriptorSurfaceGGP", { format::ApiCallId::ApiCall_vkCreateStreamDescriptorSurfaceGGP, ApiDump_vkCreateStreamDescriptorSurfaceGGP } },
        { "vkGetPhysicalDeviceExternalImageFormatPropertiesNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalImageFormatPropertiesNV, ApiDump_vkGetPhysicalDeviceExternalImageFormatPropertiesNV } },
        { "vkGetMemoryWin32HandleNV", { format::ApiCallId::ApiCall_vkGetMemoryWin32HandleNV, ApiDump_vkGetMemoryWin32HandleNV } },
        { "vkCreateViSurfaceNN", { format::ApiCallId::ApiCall_vkCreateViSurfaceNN, ApiDump_vkCreateViSurfaceNN } },
        { "vkCmdBeginConditionalRenderingEXT", { format::ApiCallId::ApiCall_vkCmdBeginConditionalRenderingEXT, ApiDump_vkCmdBeginConditionalRenderingEXT } },
        { "vkCmdEndConditionalRenderingEXT", { format::ApiCallId::ApiCall_vkCmdEndConditionalRenderingEXT, ApiDump_vkCmdEndConditionalRenderingEXT } },
        { "vkCmdSetViewportWScalingNV", { format::ApiCallId::ApiCall_vkCmdSetViewportWScalingNV, ApiDump_vkCmdSetViewportWScalingNV } },
        { "vkReleaseDisplayEXT", { format::ApiCallId::ApiCall_vkReleaseDisplayEXT, ApiDump_vkReleaseDisplayEXT } },
        { "vkAcquireXlibDisplayEXT", { format::ApiCallId::ApiCall_vkAcquireXlibDisplayEXT, ApiDump_vkAcquireXlibDisplayEXT } },
        { "vkGetRandROutputDisplayEXT", { format::ApiCallId::ApiCall_vkGetRandROutputDisplayEXT, ApiDump_vkGetRandROutputDisplayEXT } },
        { "vkGetPhysicalDeviceSurfaceCapabilities2EXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfaceCapabilities2EXT, ApiDump_vkGetPhysicalDeviceSurfaceCapabilities2EXT } },
        { "vkDisplayPowerControlEXT", { format::ApiCallId::ApiCall_vkDisplayPowerControlEXT, ApiDump_vkDisplayPowerControlEXT } },
        { "vkRegisterDeviceEventEXT", { format::ApiCallId::ApiCall_vkRegisterDeviceEventEXT, ApiDump_vkRegisterDeviceEventEXT } },
        { "vkRegisterDisplayEventEXT", { format::ApiCallId::ApiCall_vkRegisterDisplayEventEXT, ApiDump_vkRegisterDisplayEventEXT } },
        { "vkGetSwapchainCounterEXT", { format::ApiCallId::ApiCall_vkGetSwapchainCounterEXT, ApiDump_vkGetSwapchainCounterEXT } },
        { "vkGetRefreshCycleDurationGOOGLE", { format::ApiCallId::ApiCall_vkGetRefreshCycleDurationGOOGLE, ApiDump_vkGetRefreshCycleDurationGOOGLE } },
        { "vkGetPastPresentationTimingGOOGLE", { format::ApiCallId::ApiCall_vkGetPastPresentationTimingGOOGLE, ApiDump_vkGetPastPresentationTimingGOOGLE } },
        { "vkCmdSetDiscardRectangleEXT", { format::ApiCallId::ApiCall_vkCmdSetDiscardRectangleEXT, ApiDump_vkCmdSetDiscardRectangleEXT } },
        { "vkCmdSetDiscardRectangleEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDiscardRectangleEnableEXT, ApiDump_vkCmdSetDiscardRectangleEnableEXT } },
        { "vkCmdSetDiscardRectangleModeEXT", { format::ApiCallId::ApiCall_vkCmdSetDiscardRectangleModeEXT, ApiDump_vkCmdSetDiscardRectangleModeEXT } },
        { "vkSetHdrMetadataEXT", { format::ApiCallId::ApiCall_vkSetHdrMetadataEXT, ApiDump_vkSetHdrMetadataEXT } },
        { "vkCreateIOSSurfaceMVK", { format::ApiCallId::ApiCall_vkCreateIOSSurfaceMVK, ApiDump_vkCreateIOSSurfaceMVK } },
        { "vkCreateMacOSSurfaceMVK", { format::ApiCallId::ApiCall_vkCreateMacOSSurfaceMVK, ApiDump_vkCreateMacOSSurfaceMVK } },
        { "vkSetDebugUtilsObjectNameEXT", { format::ApiCallId::ApiCall_vkSetDebugUtilsObjectNameEXT, ApiDump_vkSetDebugUtilsObjectNameEXT } },
        { "vkSetDebugUtilsObjectTagEXT", { format::ApiCallId::ApiCall_vkSetDebugUtilsObjectTagEXT, ApiDump_vkSetDebugUtilsObjectTagEXT } },
        { "vkQueueBeginDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkQueueBeginDebugUtilsLabelEXT, ApiDump_vkQueueBeginDebugUtilsLabelEXT } },
        { "vkQueueEndDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkQueueEndDebugUtilsLabelEXT, ApiDump_vkQueueEndDebugUtilsLabelEXT } },
        { "vkQueueInsertDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkQueueInsertDebugUtilsLabelEXT, ApiDump_vkQueueInsertDebugUtilsLabelEXT } },
        { "vkCmdBeginDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkCmdBeginDebugUtilsLabelEXT, ApiDump_vkCmdBeginDebugUtilsLabelEXT } },
        { "vkCmdEndDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkCmdEndDebugUtilsLabelEXT, ApiDump_vkCmdEndDebugUtilsLabelEXT } },
        { "vkCmdInsertDebugUtilsLabelEXT", { format::ApiCallId::ApiCall_vkCmdInsertDebugUtilsLabelEXT, ApiDump_vkCmdInsertDebugUtilsLabelEXT } },
        { "vkCreateDebugUtilsMessengerEXT", { format::ApiCallId::ApiCall_vkCreateDebugUtilsMessengerEXT, ApiDump_vkCreateDebugUtilsMessengerEXT } },
        { "vkDestroyDebugUtilsMessengerEXT", { format::ApiCallId::ApiCall_vkDestroyDebugUtilsMessengerEXT, ApiDump_vkDestroyDebugUtilsMessengerEXT } },
        { "vkSubmitDebugUtilsMessageEXT", { format::ApiCallId::ApiCall_vkSubmitDebugUtilsMessageEXT, ApiDump_vkSubmitDebugUtilsMessageEXT } },
        { "vkGetAndroidHardwareBufferPropertiesANDROID", { format::ApiCallId::ApiCall_vkGetAndroidHardwareBufferPropertiesANDROID, ApiDump_vkGetAndroidHardwareBufferPropertiesANDROID } },
        { "vkGetMemoryAndroidHardwareBufferANDROID", { format::ApiCallId::ApiCall_vkGetMemoryAndroidHardwareBufferANDROID, ApiDump_vkGetMemoryAndroidHardwareBufferANDROID } },
        { "vkCreateGpaSessionAMD", { format::ApiCallId::ApiCall_vkCreateGpaSessionAMD, ApiDump_vkCreateGpaSessionAMD } },
        { "vkDestroyGpaSessionAMD", { format::ApiCallId::ApiCall_vkDestroyGpaSessionAMD, ApiDump_vkDestroyGpaSessionAMD } },
        { "vkSetGpaDeviceClockModeAMD", { format::ApiCallId::ApiCall_vkSetGpaDeviceClockModeAMD, ApiDump_vkSetGpaDeviceClockModeAMD } },
        { "vkGetGpaDeviceClockInfoAMD", { format::ApiCallId::ApiCall_vkGetGpaDeviceClockInfoAMD, ApiDump_vkGetGpaDeviceClockInfoAMD } },
        { "vkCmdBeginGpaSessionAMD", { format::ApiCallId::ApiCall_vkCmdBeginGpaSessionAMD, ApiDump_vkCmdBeginGpaSessionAMD } },
        { "vkCmdEndGpaSessionAMD", { format::ApiCallId::ApiCall_vkCmdEndGpaSessionAMD, ApiDump_vkCmdEndGpaSessionAMD } },
        { "vkCmdBeginGpaSampleAMD", { format::ApiCallId::ApiCall_vkCmdBeginGpaSampleAMD, ApiDump_vkCmdBeginGpaSampleAMD } },
        { "vkCmdEndGpaSampleAMD", { format::ApiCallId::ApiCall_vkCmdEndGpaSampleAMD, ApiDump_vkCmdEndGpaSampleAMD } },
        { "vkGetGpaSessionStatusAMD", { format::ApiCallId::ApiCall_vkGetGpaSessionStatusAMD, ApiDump_vkGetGpaSessionStatusAMD } },
        { "vkGetGpaSessionResultsAMD", { format::ApiCallId::ApiCall_vkGetGpaSessionResultsAMD, ApiDump_vkGetGpaSessionResultsAMD } },
        { "vkResetGpaSessionAMD", { format::ApiCallId::ApiCall_vkResetGpaSessionAMD, ApiDump_vkResetGpaSessionAMD } },
        { "vkCmdCopyGpaSessionResultsAMD", { format::ApiCallId::ApiCall_vkCmdCopyGpaSessionResultsAMD, ApiDump_vkCmdCopyGpaSessionResultsAMD } },
        { "vkCmdSetSampleLocationsEXT", { format::ApiCallId::ApiCall_vkCmdSetSampleLocationsEXT, ApiDump_vkCmdSetSampleLocationsEXT } },
        { "vkGetPhysicalDeviceMultisamplePropertiesEXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceMultisamplePropertiesEXT, ApiDump_vkGetPhysicalDeviceMultisamplePropertiesEXT } },
        { "vkGetImageDrmFormatModifierPropertiesEXT", { format::ApiCallId::ApiCall_vkGetImageDrmFormatModifierPropertiesEXT, ApiDump_vkGetImageDrmFormatModifierPropertiesEXT } },
        { "vkCreateValidationCacheEXT", { format::ApiCallId::ApiCall_vkCreateValidationCacheEXT, ApiDump_vkCreateValidationCacheEXT } },
        { "vkDestroyValidationCacheEXT", { format::ApiCallId::ApiCall_vkDestroyValidationCacheEXT, ApiDump_vkDestroyValidationCacheEXT } },
        { "vkMergeValidationCachesEXT", { format::ApiCallId::ApiCall_vkMergeValidationCachesEXT, ApiDump_vkMergeValidationCachesEXT } },
        { "vkGetValidationCacheDataEXT", { format::ApiCallId::ApiCall_vkGetValidationCacheDataEXT, ApiDump_vkGetValidationCacheDataEXT } },
        { "vkCmdBindShadingRateImageNV", { format::ApiCallId::ApiCall_vkCmdBindShadingRateImageNV, ApiDump_vkCmdBindShadingRateImageNV } },
        { "vkCmdSetViewportShadingRatePaletteNV", { format::ApiCallId::ApiCall_vkCmdSetViewportShadingRatePaletteNV, ApiDump_vkCmdSetViewportShadingRatePaletteNV } },
        { "vkCmdSetCoarseSampleOrderNV", { format::ApiCallId::ApiCall_vkCmdSetCoarseSampleOrderNV, ApiDump_vkCmdSetCoarseSampleOrderNV } },
        { "vkCreateAccelerationStructureNV", { format::ApiCallId::ApiCall_vkCreateAccelerationStructureNV, ApiDump_vkCreateAccelerationStructureNV } },
        { "vkDestroyAccelerationStructureNV", { format::ApiCallId::ApiCall_vkDestroyAccelerationStructureNV, ApiDump_vkDestroyAccelerationStructureNV } },
        { "vkGetAccelerationStructureMemoryRequirementsNV", { format::ApiCallId::ApiCall_vkGetAccelerationStructureMemoryRequirementsNV, ApiDump_vkGetAccelerationStructureMemoryRequirementsNV } },
        { "vkBindAccelerationStructureMemoryNV", { format::ApiCallId::ApiCall_vkBindAccelerationStructureMemoryNV, ApiDump_vkBindAccelerationStructureMemoryNV } },
        { "vkCmdBuildAccelerationStructureNV", { format::ApiCallId::ApiCall_vkCmdBuildAccelerationStructureNV, ApiDump_vkCmdBuildAccelerationStructureNV } },
        { "vkCmdCopyAccelerationStructureNV", { format::ApiCallId::ApiCall_vkCmdCopyAccelerationStructureNV, ApiDump_vkCmdCopyAccelerationStructureNV } },
        { "vkCmdTraceRaysNV", { format::ApiCallId::ApiCall_vkCmdTraceRaysNV, ApiDump_vkCmdTraceRaysNV } },
        { "vkCreateRayTracingPipelinesNV", { format::ApiCallId::ApiCall_vkCreateRayTracingPipelinesNV, ApiDump_vkCreateRayTracingPipelinesNV } },
        { "vkGetRayTracingShaderGroupHandlesKHR", { format::ApiCallId::ApiCall_vkGetRayTracingShaderGroupHandlesKHR, ApiDump_vkGetRayTracingShaderGroupHandlesKHR } },
        { "vkGetRayTracingShaderGroupHandlesNV", { format::ApiCallId::ApiCall_vkGetRayTracingShaderGroupHandlesNV, ApiDump_vkGetRayTracingShaderGroupHandlesNV } },
        { "vkGetAccelerationStructureHandleNV", { format::ApiCallId::ApiCall_vkGetAccelerationStructureHandleNV, ApiDump_vkGetAccelerationStructureHandleNV } },
        { "vkCmdWriteAccelerationStructuresPropertiesNV", { format::ApiCallId::ApiCall_vkCmdWriteAccelerationStructuresPropertiesNV, ApiDump_vkCmdWriteAccelerationStructuresPropertiesNV } },
        { "vkCompileDeferredNV", { format::ApiCallId::ApiCall_vkCompileDeferredNV, ApiDump_vkCompileDeferredNV } },
        { "vkGetMemoryHostPointerPropertiesEXT", { format::ApiCallId::ApiCall_vkGetMemoryHostPointerPropertiesEXT, ApiDump_vkGetMemoryHostPointerPropertiesEXT } },
        { "vkCmdWriteBufferMarkerAMD", { format::ApiCallId::ApiCall_vkCmdWriteBufferMarkerAMD, ApiDump_vkCmdWriteBufferMarkerAMD } },
        { "vkCmdWriteBufferMarker2AMD", { format::ApiCallId::ApiCall_vkCmdWriteBufferMarker2AMD, ApiDump_vkCmdWriteBufferMarker2AMD } },
        { "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT, ApiDump_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT } },
        { "vkGetCalibratedTimestampsEXT", { format::ApiCallId::ApiCall_vkGetCalibratedTimestampsEXT, ApiDump_vkGetCalibratedTimestampsEXT } },
        { "vkCmdDrawMeshTasksNV", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksNV, ApiDump_vkCmdDrawMeshTasksNV } },
        { "vkCmdDrawMeshTasksIndirectNV", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirectNV, ApiDump_vkCmdDrawMeshTasksIndirectNV } },
        { "vkCmdDrawMeshTasksIndirectCountNV", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirectCountNV, ApiDump_vkCmdDrawMeshTasksIndirectCountNV } },
        { "vkCmdSetExclusiveScissorEnableNV", { format::ApiCallId::ApiCall_vkCmdSetExclusiveScissorEnableNV, ApiDump_vkCmdSetExclusiveScissorEnableNV } },
        { "vkCmdSetExclusiveScissorNV", { format::ApiCallId::ApiCall_vkCmdSetExclusiveScissorNV, ApiDump_vkCmdSetExclusiveScissorNV } },
        { "vkCmdSetCheckpointNV", { format::ApiCallId::ApiCall_vkCmdSetCheckpointNV, ApiDump_vkCmdSetCheckpointNV } },
        { "vkGetQueueCheckpointDataNV", { format::ApiCallId::ApiCall_vkGetQueueCheckpointDataNV, ApiDump_vkGetQueueCheckpointDataNV } },
        { "vkGetQueueCheckpointData2NV", { format::ApiCallId::ApiCall_vkGetQueueCheckpointData2NV, ApiDump_vkGetQueueCheckpointData2NV } },
        { "vkSetSwapchainPresentTimingQueueSizeEXT", { format::ApiCallId::ApiCall_vkSetSwapchainPresentTimingQueueSizeEXT, ApiDump_vkSetSwapchainPresentTimingQueueSizeEXT } },
        { "vkGetSwapchainTimingPropertiesEXT", { format::ApiCallId::ApiCall_vkGetSwapchainTimingPropertiesEXT, ApiDump_vkGetSwapchainTimingPropertiesEXT } },
        { "vkGetSwapchainTimeDomainPropertiesEXT", { format::ApiCallId::ApiCall_vkGetSwapchainTimeDomainPropertiesEXT, ApiDump_vkGetSwapchainTimeDomainPropertiesEXT } },
        { "vkGetPastPresentationTimingEXT", { format::ApiCallId::ApiCall_vkGetPastPresentationTimingEXT, ApiDump_vkGetPastPresentationTimingEXT } },
        { "vkInitializePerformanceApiINTEL", { format::ApiCallId::ApiCall_vkInitializePerformanceApiINTEL, ApiDump_vkInitializePerformanceApiINTEL } },
        { "vkUninitializePerformanceApiINTEL", { format::ApiCallId::ApiCall_vkUninitializePerformanceApiINTEL, ApiDump_vkUninitializePerformanceApiINTEL } },
        { "vkCmdSetPerformanceMarkerINTEL", { format::ApiCallId::ApiCall_vkCmdSetPerformanceMarkerINTEL, ApiDump_vkCmdSetPerformanceMarkerINTEL } },
        { "vkCmdSetPerformanceStreamMarkerINTEL", { format::ApiCallId::ApiCall_vkCmdSetPerformanceStreamMarkerINTEL, ApiDump_vkCmdSetPerformanceStreamMarkerINTEL } },
        { "vkCmdSetPerformanceOverrideINTEL", { format::ApiCallId::ApiCall_vkCmdSetPerformanceOverrideINTEL, ApiDump_vkCmdSetPerformanceOverrideINTEL } },
        { "vkAcquirePerformanceConfigurationINTEL", { format::ApiCallId::ApiCall_vkAcquirePerformanceConfigurationINTEL, ApiDump_vkAcquirePerformanceConfigurationINTEL } },
        { "vkReleasePerformanceConfigurationINTEL", { format::ApiCallId::ApiCall_vkReleasePerformanceConfigurationINTEL, ApiDump_vkReleasePerformanceConfigurationINTEL } },
        { "vkQueueSetPerformanceConfigurationINTEL", { format::ApiCallId::ApiCall_vkQueueSetPerformanceConfigurationINTEL, ApiDump_vkQueueSetPerformanceConfigurationINTEL } },
        { "vkGetPerformanceParameterINTEL", { format::ApiCallId::ApiCall_vkGetPerformanceParameterINTEL, ApiDump_vkGetPerformanceParameterINTEL } },
        { "vkSetLocalDimmingAMD", { format::ApiCallId::ApiCall_vkSetLocalDimmingAMD, ApiDump_vkSetLocalDimmingAMD } },
        { "vkCreateImagePipeSurfaceFUCHSIA", { format::ApiCallId::ApiCall_vkCreateImagePipeSurfaceFUCHSIA, ApiDump_vkCreateImagePipeSurfaceFUCHSIA } },
        { "vkCreateMetalSurfaceEXT", { format::ApiCallId::ApiCall_vkCreateMetalSurfaceEXT, ApiDump_vkCreateMetalSurfaceEXT } },
        { "vkGetBufferDeviceAddressEXT", { format::ApiCallId::ApiCall_vkGetBufferDeviceAddressEXT, ApiDump_vkGetBufferDeviceAddressEXT } },
        { "vkGetPhysicalDeviceToolPropertiesEXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceToolPropertiesEXT, ApiDump_vkGetPhysicalDeviceToolPropertiesEXT } },
        { "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV, ApiDump_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV } },
        { "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV, ApiDump_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV } },
        { "vkGetPhysicalDeviceSurfacePresentModes2EXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceSurfacePresentModes2EXT, ApiDump_vkGetPhysicalDeviceSurfacePresentModes2EXT } },
        { "vkAcquireFullScreenExclusiveModeEXT", { format::ApiCallId::ApiCall_vkAcquireFullScreenExclusiveModeEXT, ApiDump_vkAcquireFullScreenExclusiveModeEXT } },
        { "vkReleaseFullScreenExclusiveModeEXT", { format::ApiCallId::ApiCall_vkReleaseFullScreenExclusiveModeEXT, ApiDump_vkReleaseFullScreenExclusiveModeEXT } },
        { "vkGetDeviceGroupSurfacePresentModes2EXT", { format::ApiCallId::ApiCall_vkGetDeviceGroupSurfacePresentModes2EXT, ApiDump_vkGetDeviceGroupSurfacePresentModes2EXT } },
        { "vkCreateHeadlessSurfaceEXT", { format::ApiCallId::ApiCall_vkCreateHeadlessSurfaceEXT, ApiDump_vkCreateHeadlessSurfaceEXT } },
        { "vkCmdSetLineStippleEXT", { format::ApiCallId::ApiCall_vkCmdSetLineStippleEXT, ApiDump_vkCmdSetLineStippleEXT } },
        { "vkResetQueryPoolEXT", { format::ApiCallId::ApiCall_vkResetQueryPoolEXT, ApiDump_vkResetQueryPoolEXT } },
        { "vkCmdSetCullModeEXT", { format::ApiCallId::ApiCall_vkCmdSetCullModeEXT, ApiDump_vkCmdSetCullModeEXT } },
        { "vkCmdSetFrontFaceEXT", { format::ApiCallId::ApiCall_vkCmdSetFrontFaceEXT, ApiDump_vkCmdSetFrontFaceEXT } },
        { "vkCmdSetPrimitiveTopologyEXT", { format::ApiCallId::ApiCall_vkCmdSetPrimitiveTopologyEXT, ApiDump_vkCmdSetPrimitiveTopologyEXT } },
        { "vkCmdSetViewportWithCountEXT", { format::ApiCallId::ApiCall_vkCmdSetViewportWithCountEXT, ApiDump_vkCmdSetViewportWithCountEXT } },
        { "vkCmdSetScissorWithCountEXT", { format::ApiCallId::ApiCall_vkCmdSetScissorWithCountEXT, ApiDump_vkCmdSetScissorWithCountEXT } },
        { "vkCmdBindVertexBuffers2EXT", { format::ApiCallId::ApiCall_vkCmdBindVertexBuffers2EXT, ApiDump_vkCmdBindVertexBuffers2EXT } },
        { "vkCmdSetDepthTestEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthTestEnableEXT, ApiDump_vkCmdSetDepthTestEnableEXT } },
        { "vkCmdSetDepthWriteEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthWriteEnableEXT, ApiDump_vkCmdSetDepthWriteEnableEXT } },
        { "vkCmdSetDepthCompareOpEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthCompareOpEXT, ApiDump_vkCmdSetDepthCompareOpEXT } },
        { "vkCmdSetDepthBoundsTestEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthBoundsTestEnableEXT, ApiDump_vkCmdSetDepthBoundsTestEnableEXT } },
        { "vkCmdSetStencilTestEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetStencilTestEnableEXT, ApiDump_vkCmdSetStencilTestEnableEXT } },
        { "vkCmdSetStencilOpEXT", { format::ApiCallId::ApiCall_vkCmdSetStencilOpEXT, ApiDump_vkCmdSetStencilOpEXT } },
        { "vkCopyMemoryToImageEXT", { format::ApiCallId::ApiCall_vkCopyMemoryToImageEXT, ApiDump_vkCopyMemoryToImageEXT } },
        { "vkCopyImageToMemoryEXT", { format::ApiCallId::ApiCall_vkCopyImageToMemoryEXT, ApiDump_vkCopyImageToMemoryEXT } },
        { "vkCopyImageToImageEXT", { format::ApiCallId::ApiCall_vkCopyImageToImageEXT, ApiDump_vkCopyImageToImageEXT } },
        { "vkTransitionImageLayoutEXT", { format::ApiCallId::ApiCall_vkTransitionImageLayoutEXT, ApiDump_vkTransitionImageLayoutEXT } },
        { "vkGetImageSubresourceLayout2EXT", { format::ApiCallId::ApiCall_vkGetImageSubresourceLayout2EXT, ApiDump_vkGetImageSubresourceLayout2EXT } },
        { "vkReleaseSwapchainImagesEXT", { format::ApiCallId::ApiCall_vkReleaseSwapchainImagesEXT, ApiDump_vkReleaseSwapchainImagesEXT } },
        { "vkGetGeneratedCommandsMemoryRequirementsNV", { format::ApiCallId::ApiCall_vkGetGeneratedCommandsMemoryRequirementsNV, ApiDump_vkGetGeneratedCommandsMemoryRequirementsNV } },
        { "vkCmdPreprocessGeneratedCommandsNV", { format::ApiCallId::ApiCall_vkCmdPreprocessGeneratedCommandsNV, ApiDump_vkCmdPreprocessGeneratedCommandsNV } },
        { "vkCmdExecuteGeneratedCommandsNV", { format::ApiCallId::ApiCall_vkCmdExecuteGeneratedCommandsNV, ApiDump_vkCmdExecuteGeneratedCommandsNV } },
        { "vkCmdBindPipelineShaderGroupNV", { format::ApiCallId::ApiCall_vkCmdBindPipelineShaderGroupNV, ApiDump_vkCmdBindPipelineShaderGroupNV } },
        { "vkCreateIndirectCommandsLayoutNV", { format::ApiCallId::ApiCall_vkCreateIndirectCommandsLayoutNV, ApiDump_vkCreateIndirectCommandsLayoutNV } },
        { "vkDestroyIndirectCommandsLayoutNV", { format::ApiCallId::ApiCall_vkDestroyIndirectCommandsLayoutNV, ApiDump_vkDestroyIndirectCommandsLayoutNV } },
        { "vkCmdSetDepthBias2EXT", { format::ApiCallId::ApiCall_vkCmdSetDepthBias2EXT, ApiDump_vkCmdSetDepthBias2EXT } },
        { "vkAcquireDrmDisplayEXT", { format::ApiCallId::ApiCall_vkAcquireDrmDisplayEXT, ApiDump_vkAcquireDrmDisplayEXT } },
        { "vkGetDrmDisplayEXT", { format::ApiCallId::ApiCall_vkGetDrmDisplayEXT, ApiDump_vkGetDrmDisplayEXT } },
        { "vkCreatePrivateDataSlotEXT", { format::ApiCallId::ApiCall_vkCreatePrivateDataSlotEXT, ApiDump_vkCreatePrivateDataSlotEXT } },
        { "vkDestroyPrivateDataSlotEXT", { format::ApiCallId::ApiCall_vkDestroyPrivateDataSlotEXT, ApiDump_vkDestroyPrivateDataSlotEXT } },
        { "vkSetPrivateDataEXT", { format::ApiCallId::ApiCall_vkSetPrivateDataEXT, ApiDump_vkSetPrivateDataEXT } },
        { "vkGetPrivateDataEXT", { format::ApiCallId::ApiCall_vkGetPrivateDataEXT, ApiDump_vkGetPrivateDataEXT } },
        { "vkQueueSetPerfHintQCOM", { format::ApiCallId::ApiCall_vkQueueSetPerfHintQCOM, ApiDump_vkQueueSetPerfHintQCOM } },
        { "vkCmdDispatchTileQCOM", { format::ApiCallId::ApiCall_vkCmdDispatchTileQCOM, ApiDump_vkCmdDispatchTileQCOM } },
        { "vkCmdBeginPerTileExecutionQCOM", { format::ApiCallId::ApiCall_vkCmdBeginPerTileExecutionQCOM, ApiDump_vkCmdBeginPerTileExecutionQCOM } },
        { "vkCmdEndPerTileExecutionQCOM", { format::ApiCallId::ApiCall_vkCmdEndPerTileExecutionQCOM, ApiDump_vkCmdEndPerTileExecutionQCOM } },
        { "vkGetDescriptorSetLayoutSizeEXT", { format::ApiCallId::ApiCall_vkGetDescriptorSetLayoutSizeEXT, ApiDump_vkGetDescriptorSetLayoutSizeEXT } },
        { "vkGetDescriptorSetLayoutBindingOffsetEXT", { format::ApiCallId::ApiCall_vkGetDescriptorSetLayoutBindingOffsetEXT, ApiDump_vkGetDescriptorSetLayoutBindingOffsetEXT } },
        { "vkGetDescriptorEXT", { format::ApiCallId::ApiCall_vkGetDescriptorEXT, ApiDump_vkGetDescriptorEXT } },
        { "vkCmdBindDescriptorBuffersEXT", { format::ApiCallId::ApiCall_vkCmdBindDescriptorBuffersEXT, ApiDump_vkCmdBindDescriptorBuffersEXT } },
        { "vkCmdSetDescriptorBufferOffsetsEXT", { format::ApiCallId::ApiCall_vkCmdSetDescriptorBufferOffsetsEXT, ApiDump_vkCmdSetDescriptorBufferOffsetsEXT } },
        { "vkCmdBindDescriptorBufferEmbeddedSamplersEXT", { format::ApiCallId::ApiCall_vkCmdBindDescriptorBufferEmbeddedSamplersEXT, ApiDump_vkCmdBindDescriptorBufferEmbeddedSamplersEXT } },
        { "vkCmdSetFragmentShadingRateEnumNV", { format::ApiCallId::ApiCall_vkCmdSetFragmentShadingRateEnumNV, ApiDump_vkCmdSetFragmentShadingRateEnumNV } },
        { "vkGetDeviceFaultInfoEXT", { format::ApiCallId::ApiCall_vkGetDeviceFaultInfoEXT, ApiDump_vkGetDeviceFaultInfoEXT } },
        { "vkAcquireWinrtDisplayNV", { format::ApiCallId::ApiCall_vkAcquireWinrtDisplayNV, ApiDump_vkAcquireWinrtDisplayNV } },
        { "vkGetWinrtDisplayNV", { format::ApiCallId::ApiCall_vkGetWinrtDisplayNV, ApiDump_vkGetWinrtDisplayNV } },
        { "vkCreateDirectFBSurfaceEXT", { format::ApiCallId::ApiCall_vkCreateDirectFBSurfaceEXT, ApiDump_vkCreateDirectFBSurfaceEXT } },
        { "vkGetPhysicalDeviceDirectFBPresentationSupportEXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceDirectFBPresentationSupportEXT, ApiDump_vkGetPhysicalDeviceDirectFBPresentationSupportEXT } },
        { "vkCmdSetVertexInputEXT", { format::ApiCallId::ApiCall_vkCmdSetVertexInputEXT, ApiDump_vkCmdSetVertexInputEXT } },
        { "vkGetMemoryZirconHandleFUCHSIA", { format::ApiCallId::ApiCall_vkGetMemoryZirconHandleFUCHSIA, ApiDump_vkGetMemoryZirconHandleFUCHSIA } },
        { "vkGetMemoryZirconHandlePropertiesFUCHSIA", { format::ApiCallId::ApiCall_vkGetMemoryZirconHandlePropertiesFUCHSIA, ApiDump_vkGetMemoryZirconHandlePropertiesFUCHSIA } },
        { "vkImportSemaphoreZirconHandleFUCHSIA", { format::ApiCallId::ApiCall_vkImportSemaphoreZirconHandleFUCHSIA, ApiDump_vkImportSemaphoreZirconHandleFUCHSIA } },
        { "vkGetSemaphoreZirconHandleFUCHSIA", { format::ApiCallId::ApiCall_vkGetSemaphoreZirconHandleFUCHSIA, ApiDump_vkGetSemaphoreZirconHandleFUCHSIA } },
        { "vkCmdBindInvocationMaskHUAWEI", { format::ApiCallId::ApiCall_vkCmdBindInvocationMaskHUAWEI, ApiDump_vkCmdBindInvocationMaskHUAWEI } },
        { "vkGetMemoryRemoteAddressNV", { format::ApiCallId::ApiCall_vkGetMemoryRemoteAddressNV, ApiDump_vkGetMemoryRemoteAddressNV } },
        { "vkCmdSetPatchControlPointsEXT", { format::ApiCallId::ApiCall_vkCmdSetPatchControlPointsEXT, ApiDump_vkCmdSetPatchControlPointsEXT } },
        { "vkCmdSetRasterizerDiscardEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetRasterizerDiscardEnableEXT, ApiDump_vkCmdSetRasterizerDiscardEnableEXT } },
        { "vkCmdSetDepthBiasEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthBiasEnableEXT, ApiDump_vkCmdSetDepthBiasEnableEXT } },
        { "vkCmdSetLogicOpEXT", { format::ApiCallId::ApiCall_vkCmdSetLogicOpEXT, ApiDump_vkCmdSetLogicOpEXT } },
        { "vkCmdSetPrimitiveRestartEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetPrimitiveRestartEnableEXT, ApiDump_vkCmdSetPrimitiveRestartEnableEXT } },
        { "vkCreateScreenSurfaceQNX", { format::ApiCallId::ApiCall_vkCreateScreenSurfaceQNX, ApiDump_vkCreateScreenSurfaceQNX } },
        { "vkGetPhysicalDeviceScreenPresentationSupportQNX", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceScreenPresentationSupportQNX, ApiDump_vkGetPhysicalDeviceScreenPresentationSupportQNX } },
        { "vkCmdSetColorWriteEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetColorWriteEnableEXT, ApiDump_vkCmdSetColorWriteEnableEXT } },
        { "vkCmdDrawMultiEXT", { format::ApiCallId::ApiCall_vkCmdDrawMultiEXT, ApiDump_vkCmdDrawMultiEXT } },
        { "vkCmdDrawMultiIndexedEXT", { format::ApiCallId::ApiCall_vkCmdDrawMultiIndexedEXT, ApiDump_vkCmdDrawMultiIndexedEXT } },
        { "vkCreateMicromapEXT", { format::ApiCallId::ApiCall_vkCreateMicromapEXT, ApiDump_vkCreateMicromapEXT } },
        { "vkDestroyMicromapEXT", { format::ApiCallId::ApiCall_vkDestroyMicromapEXT, ApiDump_vkDestroyMicromapEXT } },
        { "vkCmdBuildMicromapsEXT", { format::ApiCallId::ApiCall_vkCmdBuildMicromapsEXT, ApiDump_vkCmdBuildMicromapsEXT } },
        { "vkBuildMicromapsEXT", { format::ApiCallId::ApiCall_vkBuildMicromapsEXT, ApiDump_vkBuildMicromapsEXT } },
        { "vkCopyMicromapEXT", { format::ApiCallId::ApiCall_vkCopyMicromapEXT, ApiDump_vkCopyMicromapEXT } },
        { "vkCopyMicromapToMemoryEXT", { format::ApiCallId::ApiCall_vkCopyMicromapToMemoryEXT, ApiDump_vkCopyMicromapToMemoryEXT } },
        { "vkCopyMemoryToMicromapEXT", { format::ApiCallId::ApiCall_vkCopyMemoryToMicromapEXT, ApiDump_vkCopyMemoryToMicromapEXT } },
        { "vkWriteMicromapsPropertiesEXT", { format::ApiCallId::ApiCall_vkWriteMicromapsPropertiesEXT, ApiDump_vkWriteMicromapsPropertiesEXT } },
        { "vkCmdCopyMicromapEXT", { format::ApiCallId::ApiCall_vkCmdCopyMicromapEXT, ApiDump_vkCmdCopyMicromapEXT } },
        { "vkCmdCopyMicromapToMemoryEXT", { format::ApiCallId::ApiCall_vkCmdCopyMicromapToMemoryEXT, ApiDump_vkCmdCopyMicromapToMemoryEXT } },
        { "vkCmdCopyMemoryToMicromapEXT", { format::ApiCallId::ApiCall_vkCmdCopyMemoryToMicromapEXT, ApiDump_vkCmdCopyMemoryToMicromapEXT } },
        { "vkCmdWriteMicromapsPropertiesEXT", { format::ApiCallId::ApiCall_vkCmdWriteMicromapsPropertiesEXT, ApiDump_vkCmdWriteMicromapsPropertiesEXT } },
        { "vkGetDeviceMicromapCompatibilityEXT", { format::ApiCallId::ApiCall_vkGetDeviceMicromapCompatibilityEXT, ApiDump_vkGetDeviceMicromapCompatibilityEXT } },
        { "vkGetMicromapBuildSizesEXT", { format::ApiCallId::ApiCall_vkGetMicromapBuildSizesEXT, ApiDump_vkGetMicromapBuildSizesEXT } },
        { "vkCmdDrawClusterHUAWEI", { format::ApiCallId::ApiCall_vkCmdDrawClusterHUAWEI, ApiDump_vkCmdDrawClusterHUAWEI } },
        { "vkCmdDrawClusterIndirectHUAWEI", { format::ApiCallId::ApiCall_vkCmdDrawClusterIndirectHUAWEI, ApiDump_vkCmdDrawClusterIndirectHUAWEI } },
        { "vkSetDeviceMemoryPriorityEXT", { format::ApiCallId::ApiCall_vkSetDeviceMemoryPriorityEXT, ApiDump_vkSetDeviceMemoryPriorityEXT } },
        { "vkCmdSetDispatchParametersARM", { format::ApiCallId::ApiCall_vkCmdSetDispatchParametersARM, ApiDump_vkCmdSetDispatchParametersARM } },
        { "vkGetDescriptorSetLayoutHostMappingInfoVALVE", { format::ApiCallId::ApiCall_vkGetDescriptorSetLayoutHostMappingInfoVALVE, ApiDump_vkGetDescriptorSetLayoutHostMappingInfoVALVE } },
        { "vkGetDescriptorSetHostMappingVALVE", { format::ApiCallId::ApiCall_vkGetDescriptorSetHostMappingVALVE, ApiDump_vkGetDescriptorSetHostMappingVALVE } },
        { "vkGetPipelineIndirectMemoryRequirementsNV", { format::ApiCallId::ApiCall_vkGetPipelineIndirectMemoryRequirementsNV, ApiDump_vkGetPipelineIndirectMemoryRequirementsNV } },
        { "vkCmdUpdatePipelineIndirectBufferNV", { format::ApiCallId::ApiCall_vkCmdUpdatePipelineIndirectBufferNV, ApiDump_vkCmdUpdatePipelineIndirectBufferNV } },
        { "vkGetPipelineIndirectDeviceAddressNV", { format::ApiCallId::ApiCall_vkGetPipelineIndirectDeviceAddressNV, ApiDump_vkGetPipelineIndirectDeviceAddressNV } },
        { "vkCmdSetDepthClampEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthClampEnableEXT, ApiDump_vkCmdSetDepthClampEnableEXT } },
        { "vkCmdSetPolygonModeEXT", { format::ApiCallId::ApiCall_vkCmdSetPolygonModeEXT, ApiDump_vkCmdSetPolygonModeEXT } },
        { "vkCmdSetRasterizationSamplesEXT", { format::ApiCallId::ApiCall_vkCmdSetRasterizationSamplesEXT, ApiDump_vkCmdSetRasterizationSamplesEXT } },
        { "vkCmdSetSampleMaskEXT", { format::ApiCallId::ApiCall_vkCmdSetSampleMaskEXT, ApiDump_vkCmdSetSampleMaskEXT } },
        { "vkCmdSetAlphaToCoverageEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetAlphaToCoverageEnableEXT, ApiDump_vkCmdSetAlphaToCoverageEnableEXT } },
        { "vkCmdSetAlphaToOneEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetAlphaToOneEnableEXT, ApiDump_vkCmdSetAlphaToOneEnableEXT } },
        { "vkCmdSetLogicOpEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetLogicOpEnableEXT, ApiDump_vkCmdSetLogicOpEnableEXT } },
        { "vkCmdSetColorBlendEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetColorBlendEnableEXT, ApiDump_vkCmdSetColorBlendEnableEXT } },
        { "vkCmdSetColorBlendEquationEXT", { format::ApiCallId::ApiCall_vkCmdSetColorBlendEquationEXT, ApiDump_vkCmdSetColorBlendEquationEXT } },
        { "vkCmdSetColorWriteMaskEXT", { format::ApiCallId::ApiCall_vkCmdSetColorWriteMaskEXT, ApiDump_vkCmdSetColorWriteMaskEXT } },
        { "vkCmdSetTessellationDomainOriginEXT", { format::ApiCallId::ApiCall_vkCmdSetTessellationDomainOriginEXT, ApiDump_vkCmdSetTessellationDomainOriginEXT } },
        { "vkCmdSetRasterizationStreamEXT", { format::ApiCallId::ApiCall_vkCmdSetRasterizationStreamEXT, ApiDump_vkCmdSetRasterizationStreamEXT } },
        { "vkCmdSetConservativeRasterizationModeEXT", { format::ApiCallId::ApiCall_vkCmdSetConservativeRasterizationModeEXT, ApiDump_vkCmdSetConservativeRasterizationModeEXT } },
        { "vkCmdSetExtraPrimitiveOverestimationSizeEXT", { format::ApiCallId::ApiCall_vkCmdSetExtraPrimitiveOverestimationSizeEXT, ApiDump_vkCmdSetExtraPrimitiveOverestimationSizeEXT } },
        { "vkCmdSetDepthClipEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthClipEnableEXT, ApiDump_vkCmdSetDepthClipEnableEXT } },
        { "vkCmdSetSampleLocationsEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetSampleLocationsEnableEXT, ApiDump_vkCmdSetSampleLocationsEnableEXT } },
        { "vkCmdSetColorBlendAdvancedEXT", { format::ApiCallId::ApiCall_vkCmdSetColorBlendAdvancedEXT, ApiDump_vkCmdSetColorBlendAdvancedEXT } },
        { "vkCmdSetProvokingVertexModeEXT", { format::ApiCallId::ApiCall_vkCmdSetProvokingVertexModeEXT, ApiDump_vkCmdSetProvokingVertexModeEXT } },
        { "vkCmdSetLineRasterizationModeEXT", { format::ApiCallId::ApiCall_vkCmdSetLineRasterizationModeEXT, ApiDump_vkCmdSetLineRasterizationModeEXT } },
        { "vkCmdSetLineStippleEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetLineStippleEnableEXT, ApiDump_vkCmdSetLineStippleEnableEXT } },
        { "vkCmdSetDepthClipNegativeOneToOneEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthClipNegativeOneToOneEXT, ApiDump_vkCmdSetDepthClipNegativeOneToOneEXT } },
        { "vkCmdSetViewportWScalingEnableNV", { format::ApiCallId::ApiCall_vkCmdSetViewportWScalingEnableNV, ApiDump_vkCmdSetViewportWScalingEnableNV } },
        { "vkCmdSetViewportSwizzleNV", { format::ApiCallId::ApiCall_vkCmdSetViewportSwizzleNV, ApiDump_vkCmdSetViewportSwizzleNV } },
        { "vkCmdSetCoverageToColorEnableNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageToColorEnableNV, ApiDump_vkCmdSetCoverageToColorEnableNV } },
        { "vkCmdSetCoverageToColorLocationNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageToColorLocationNV, ApiDump_vkCmdSetCoverageToColorLocationNV } },
        { "vkCmdSetCoverageModulationModeNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageModulationModeNV, ApiDump_vkCmdSetCoverageModulationModeNV } },
        { "vkCmdSetCoverageModulationTableEnableNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageModulationTableEnableNV, ApiDump_vkCmdSetCoverageModulationTableEnableNV } },
        { "vkCmdSetCoverageModulationTableNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageModulationTableNV, ApiDump_vkCmdSetCoverageModulationTableNV } },
        { "vkCmdSetShadingRateImageEnableNV", { format::ApiCallId::ApiCall_vkCmdSetShadingRateImageEnableNV, ApiDump_vkCmdSetShadingRateImageEnableNV } },
        { "vkCmdSetRepresentativeFragmentTestEnableNV", { format::ApiCallId::ApiCall_vkCmdSetRepresentativeFragmentTestEnableNV, ApiDump_vkCmdSetRepresentativeFragmentTestEnableNV } },
        { "vkCmdSetCoverageReductionModeNV", { format::ApiCallId::ApiCall_vkCmdSetCoverageReductionModeNV, ApiDump_vkCmdSetCoverageReductionModeNV } },
        { "vkCreateTensorARM", { format::ApiCallId::ApiCall_vkCreateTensorARM, ApiDump_vkCreateTensorARM } },
        { "vkDestroyTensorARM", { format::ApiCallId::ApiCall_vkDestroyTensorARM, ApiDump_vkDestroyTensorARM } },
        { "vkCreateTensorViewARM", { format::ApiCallId::ApiCall_vkCreateTensorViewARM, ApiDump_vkCreateTensorViewARM } },
        { "vkDestroyTensorViewARM", { format::ApiCallId::ApiCall_vkDestroyTensorViewARM, ApiDump_vkDestroyTensorViewARM } },
        { "vkGetTensorMemoryRequirementsARM", { format::ApiCallId::ApiCall_vkGetTensorMemoryRequirementsARM, ApiDump_vkGetTensorMemoryRequirementsARM } },
        { "vkBindTensorMemoryARM", { format::ApiCallId::ApiCall_vkBindTensorMemoryARM, ApiDump_vkBindTensorMemoryARM } },
        { "vkGetDeviceTensorMemoryRequirementsARM", { format::ApiCallId::ApiCall_vkGetDeviceTensorMemoryRequirementsARM, ApiDump_vkGetDeviceTensorMemoryRequirementsARM } },
        { "vkCmdCopyTensorARM", { format::ApiCallId::ApiCall_vkCmdCopyTensorARM, ApiDump_vkCmdCopyTensorARM } },
        { "vkGetPhysicalDeviceExternalTensorPropertiesARM", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceExternalTensorPropertiesARM, ApiDump_vkGetPhysicalDeviceExternalTensorPropertiesARM } },
        { "vkGetShaderModuleIdentifierEXT", { format::ApiCallId::ApiCall_vkGetShaderModuleIdentifierEXT, ApiDump_vkGetShaderModuleIdentifierEXT } },
        { "vkGetShaderModuleCreateInfoIdentifierEXT", { format::ApiCallId::ApiCall_vkGetShaderModuleCreateInfoIdentifierEXT, ApiDump_vkGetShaderModuleCreateInfoIdentifierEXT } },
        { "vkGetPhysicalDeviceOpticalFlowImageFormatsNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceOpticalFlowImageFormatsNV, ApiDump_vkGetPhysicalDeviceOpticalFlowImageFormatsNV } },
        { "vkCreateOpticalFlowSessionNV", { format::ApiCallId::ApiCall_vkCreateOpticalFlowSessionNV, ApiDump_vkCreateOpticalFlowSessionNV } },
        { "vkDestroyOpticalFlowSessionNV", { format::ApiCallId::ApiCall_vkDestroyOpticalFlowSessionNV, ApiDump_vkDestroyOpticalFlowSessionNV } },
        { "vkBindOpticalFlowSessionImageNV", { format::ApiCallId::ApiCall_vkBindOpticalFlowSessionImageNV, ApiDump_vkBindOpticalFlowSessionImageNV } },
        { "vkCmdOpticalFlowExecuteNV", { format::ApiCallId::ApiCall_vkCmdOpticalFlowExecuteNV, ApiDump_vkCmdOpticalFlowExecuteNV } },
        { "vkAntiLagUpdateAMD", { format::ApiCallId::ApiCall_vkAntiLagUpdateAMD, ApiDump_vkAntiLagUpdateAMD } },
        { "vkCreateShadersEXT", { format::ApiCallId::ApiCall_vkCreateShadersEXT, ApiDump_vkCreateShadersEXT } },
        { "vkDestroyShaderEXT", { format::ApiCallId::ApiCall_vkDestroyShaderEXT, ApiDump_vkDestroyShaderEXT } },
        { "vkGetShaderBinaryDataEXT", { format::ApiCallId::ApiCall_vkGetShaderBinaryDataEXT, ApiDump_vkGetShaderBinaryDataEXT } },
        { "vkCmdBindShadersEXT", { format::ApiCallId::ApiCall_vkCmdBindShadersEXT, ApiDump_vkCmdBindShadersEXT } },
        { "vkCmdSetDepthClampRangeEXT", { format::ApiCallId::ApiCall_vkCmdSetDepthClampRangeEXT, ApiDump_vkCmdSetDepthClampRangeEXT } },
        { "vkGetFramebufferTilePropertiesQCOM", { format::ApiCallId::ApiCall_vkGetFramebufferTilePropertiesQCOM, ApiDump_vkGetFramebufferTilePropertiesQCOM } },
        { "vkGetDynamicRenderingTilePropertiesQCOM", { format::ApiCallId::ApiCall_vkGetDynamicRenderingTilePropertiesQCOM, ApiDump_vkGetDynamicRenderingTilePropertiesQCOM } },
        { "vkGetPhysicalDeviceCooperativeVectorPropertiesNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCooperativeVectorPropertiesNV, ApiDump_vkGetPhysicalDeviceCooperativeVectorPropertiesNV } },
        { "vkConvertCooperativeVectorMatrixNV", { format::ApiCallId::ApiCall_vkConvertCooperativeVectorMatrixNV, ApiDump_vkConvertCooperativeVectorMatrixNV } },
        { "vkCmdConvertCooperativeVectorMatrixNV", { format::ApiCallId::ApiCall_vkCmdConvertCooperativeVectorMatrixNV, ApiDump_vkCmdConvertCooperativeVectorMatrixNV } },
        { "vkSetLatencySleepModeNV", { format::ApiCallId::ApiCall_vkSetLatencySleepModeNV, ApiDump_vkSetLatencySleepModeNV } },
        { "vkLatencySleepNV", { format::ApiCallId::ApiCall_vkLatencySleepNV, ApiDump_vkLatencySleepNV } },
        { "vkSetLatencyMarkerNV", { format::ApiCallId::ApiCall_vkSetLatencyMarkerNV, ApiDump_vkSetLatencyMarkerNV } },
        { "vkGetLatencyTimingsNV", { format::ApiCallId::ApiCall_vkGetLatencyTimingsNV, ApiDump_vkGetLatencyTimingsNV } },
        { "vkQueueNotifyOutOfBandNV", { format::ApiCallId::ApiCall_vkQueueNotifyOutOfBandNV, ApiDump_vkQueueNotifyOutOfBandNV } },
        { "vkCreateDataGraphPipelinesARM", { format::ApiCallId::ApiCall_vkCreateDataGraphPipelinesARM, ApiDump_vkCreateDataGraphPipelinesARM } },
        { "vkCreateDataGraphPipelineSessionARM", { format::ApiCallId::ApiCall_vkCreateDataGraphPipelineSessionARM, ApiDump_vkCreateDataGraphPipelineSessionARM } },
        { "vkGetDataGraphPipelineSessionBindPointRequirementsARM", { format::ApiCallId::ApiCall_vkGetDataGraphPipelineSessionBindPointRequirementsARM, ApiDump_vkGetDataGraphPipelineSessionBindPointRequirementsARM } },
        { "vkGetDataGraphPipelineSessionMemoryRequirementsARM", { format::ApiCallId::ApiCall_vkGetDataGraphPipelineSessionMemoryRequirementsARM, ApiDump_vkGetDataGraphPipelineSessionMemoryRequirementsARM } },
        { "vkBindDataGraphPipelineSessionMemoryARM", { format::ApiCallId::ApiCall_vkBindDataGraphPipelineSessionMemoryARM, ApiDump_vkBindDataGraphPipelineSessionMemoryARM } },
        { "vkDestroyDataGraphPipelineSessionARM", { format::ApiCallId::ApiCall_vkDestroyDataGraphPipelineSessionARM, ApiDump_vkDestroyDataGraphPipelineSessionARM } },
        { "vkCmdDispatchDataGraphARM", { format::ApiCallId::ApiCall_vkCmdDispatchDataGraphARM, ApiDump_vkCmdDispatchDataGraphARM } },
        { "vkGetDataGraphPipelineAvailablePropertiesARM", { format::ApiCallId::ApiCall_vkGetDataGraphPipelineAvailablePropertiesARM, ApiDump_vkGetDataGraphPipelineAvailablePropertiesARM } },
        { "vkGetDataGraphPipelinePropertiesARM", { format::ApiCallId::ApiCall_vkGetDataGraphPipelinePropertiesARM, ApiDump_vkGetDataGraphPipelinePropertiesARM } },
        { "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM, ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM } },
        { "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM, ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM } },
        { "vkCmdSetAttachmentFeedbackLoopEnableEXT", { format::ApiCallId::ApiCall_vkCmdSetAttachmentFeedbackLoopEnableEXT, ApiDump_vkCmdSetAttachmentFeedbackLoopEnableEXT } },
        { "vkCmdBindTileMemoryQCOM", { format::ApiCallId::ApiCall_vkCmdBindTileMemoryQCOM, ApiDump_vkCmdBindTileMemoryQCOM } },
        { "vkCmdDecompressMemoryEXT", { format::ApiCallId::ApiCall_vkCmdDecompressMemoryEXT, ApiDump_vkCmdDecompressMemoryEXT } },
        { "vkCmdDecompressMemoryIndirectCountEXT", { format::ApiCallId::ApiCall_vkCmdDecompressMemoryIndirectCountEXT, ApiDump_vkCmdDecompressMemoryIndirectCountEXT } },
        { "vkGetPartitionedAccelerationStructuresBuildSizesNV", { format::ApiCallId::ApiCall_vkGetPartitionedAccelerationStructuresBuildSizesNV, ApiDump_vkGetPartitionedAccelerationStructuresBuildSizesNV } },
        { "vkCmdBuildPartitionedAccelerationStructuresNV", { format::ApiCallId::ApiCall_vkCmdBuildPartitionedAccelerationStructuresNV, ApiDump_vkCmdBuildPartitionedAccelerationStructuresNV } },
        { "vkGetGeneratedCommandsMemoryRequirementsEXT", { format::ApiCallId::ApiCall_vkGetGeneratedCommandsMemoryRequirementsEXT, ApiDump_vkGetGeneratedCommandsMemoryRequirementsEXT } },
        { "vkCmdPreprocessGeneratedCommandsEXT", { format::ApiCallId::ApiCall_vkCmdPreprocessGeneratedCommandsEXT, ApiDump_vkCmdPreprocessGeneratedCommandsEXT } },
        { "vkCmdExecuteGeneratedCommandsEXT", { format::ApiCallId::ApiCall_vkCmdExecuteGeneratedCommandsEXT, ApiDump_vkCmdExecuteGeneratedCommandsEXT } },
        { "vkCreateIndirectCommandsLayoutEXT", { format::ApiCallId::ApiCall_vkCreateIndirectCommandsLayoutEXT, ApiDump_vkCreateIndirectCommandsLayoutEXT } },
        { "vkDestroyIndirectCommandsLayoutEXT", { format::ApiCallId::ApiCall_vkDestroyIndirectCommandsLayoutEXT, ApiDump_vkDestroyIndirectCommandsLayoutEXT } },
        { "vkCreateIndirectExecutionSetEXT", { format::ApiCallId::ApiCall_vkCreateIndirectExecutionSetEXT, ApiDump_vkCreateIndirectExecutionSetEXT } },
        { "vkDestroyIndirectExecutionSetEXT", { format::ApiCallId::ApiCall_vkDestroyIndirectExecutionSetEXT, ApiDump_vkDestroyIndirectExecutionSetEXT } },
        { "vkUpdateIndirectExecutionSetPipelineEXT", { format::ApiCallId::ApiCall_vkUpdateIndirectExecutionSetPipelineEXT, ApiDump_vkUpdateIndirectExecutionSetPipelineEXT } },
        { "vkUpdateIndirectExecutionSetShaderEXT", { format::ApiCallId::ApiCall_vkUpdateIndirectExecutionSetShaderEXT, ApiDump_vkUpdateIndirectExecutionSetShaderEXT } },
        { "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV, ApiDump_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV } },
        { "vkGetMemoryMetalHandleEXT", { format::ApiCallId::ApiCall_vkGetMemoryMetalHandleEXT, ApiDump_vkGetMemoryMetalHandleEXT } },
        { "vkGetMemoryMetalHandlePropertiesEXT", { format::ApiCallId::ApiCall_vkGetMemoryMetalHandlePropertiesEXT, ApiDump_vkGetMemoryMetalHandlePropertiesEXT } },
        { "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM", { format::ApiCallId::ApiCall_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM, ApiDump_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM } },
        { "vkCmdEndRendering2EXT", { format::ApiCallId::ApiCall_vkCmdEndRendering2EXT, ApiDump_vkCmdEndRendering2EXT } },
        { "vkCmdBeginCustomResolveEXT", { format::ApiCallId::ApiCall_vkCmdBeginCustomResolveEXT, ApiDump_vkCmdBeginCustomResolveEXT } },
        { "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM, ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM } },
        { "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM, ApiDump_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM } },
        { "vkCmdSetComputeOccupancyPriorityNV", { format::ApiCallId::ApiCall_vkCmdSetComputeOccupancyPriorityNV, ApiDump_vkCmdSetComputeOccupancyPriorityNV } },
        { "vkGetPhysicalDeviceCooperativeMatrixProperties2EXT", { format::ApiCallId::ApiCall_vkGetPhysicalDeviceCooperativeMatrixProperties2EXT, ApiDump_vkGetPhysicalDeviceCooperativeMatrixProperties2EXT } },
        { "vkCmdSetPrimitiveRestartIndexEXT", { format::ApiCallId::ApiCall_vkCmdSetPrimitiveRestartIndexEXT, ApiDump_vkCmdSetPrimitiveRestartIndexEXT } },
        { "vkCreateAccelerationStructureKHR", { format::ApiCallId::ApiCall_vkCreateAccelerationStructureKHR, ApiDump_vkCreateAccelerationStructureKHR } },
        { "vkDestroyAccelerationStructureKHR", { format::ApiCallId::ApiCall_vkDestroyAccelerationStructureKHR, ApiDump_vkDestroyAccelerationStructureKHR } },
        { "vkCmdBuildAccelerationStructuresKHR", { format::ApiCallId::ApiCall_vkCmdBuildAccelerationStructuresKHR, ApiDump_vkCmdBuildAccelerationStructuresKHR } },
        { "vkCmdBuildAccelerationStructuresIndirectKHR", { format::ApiCallId::ApiCall_vkCmdBuildAccelerationStructuresIndirectKHR, ApiDump_vkCmdBuildAccelerationStructuresIndirectKHR } },
        { "vkCopyAccelerationStructureToMemoryKHR", { format::ApiCallId::ApiCall_vkCopyAccelerationStructureToMemoryKHR, ApiDump_vkCopyAccelerationStructureToMemoryKHR } },
        { "vkCopyMemoryToAccelerationStructureKHR", { format::ApiCallId::ApiCall_vkCopyMemoryToAccelerationStructureKHR, ApiDump_vkCopyMemoryToAccelerationStructureKHR } },
        { "vkWriteAccelerationStructuresPropertiesKHR", { format::ApiCallId::ApiCall_vkWriteAccelerationStructuresPropertiesKHR, ApiDump_vkWriteAccelerationStructuresPropertiesKHR } },
        { "vkCmdCopyAccelerationStructureKHR", { format::ApiCallId::ApiCall_vkCmdCopyAccelerationStructureKHR, ApiDump_vkCmdCopyAccelerationStructureKHR } },
        { "vkCmdCopyAccelerationStructureToMemoryKHR", { format::ApiCallId::ApiCall_vkCmdCopyAccelerationStructureToMemoryKHR, ApiDump_vkCmdCopyAccelerationStructureToMemoryKHR } },
        { "vkCmdCopyMemoryToAccelerationStructureKHR", { format::ApiCallId::ApiCall_vkCmdCopyMemoryToAccelerationStructureKHR, ApiDump_vkCmdCopyMemoryToAccelerationStructureKHR } },
        { "vkGetAccelerationStructureDeviceAddressKHR", { format::ApiCallId::ApiCall_vkGetAccelerationStructureDeviceAddressKHR, ApiDump_vkGetAccelerationStructureDeviceAddressKHR } },
        { "vkCmdWriteAccelerationStructuresPropertiesKHR", { format::ApiCallId::ApiCall_vkCmdWriteAccelerationStructuresPropertiesKHR, ApiDump_vkCmdWriteAccelerationStructuresPropertiesKHR } },
        { "vkGetDeviceAccelerationStructureCompatibilityKHR", { format::ApiCallId::ApiCall_vkGetDeviceAccelerationStructureCompatibilityKHR, ApiDump_vkGetDeviceAccelerationStructureCompatibilityKHR } },
        { "vkGetAccelerationStructureBuildSizesKHR", { format::ApiCallId::ApiCall_vkGetAccelerationStructureBuildSizesKHR, ApiDump_vkGetAccelerationStructureBuildSizesKHR } },
        { "vkCmdTraceRaysKHR", { format::ApiCallId::ApiCall_vkCmdTraceRaysKHR, ApiDump_vkCmdTraceRaysKHR } },
        { "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR", { format::ApiCallId::ApiCall_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR, ApiDump_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR } },
        { "vkCmdTraceRaysIndirectKHR", { format::ApiCallId::ApiCall_vkCmdTraceRaysIndirectKHR, ApiDump_vkCmdTraceRaysIndirectKHR } },
        { "vkGetRayTracingShaderGroupStackSizeKHR", { format::ApiCallId::ApiCall_vkGetRayTracingShaderGroupStackSizeKHR, ApiDump_vkGetRayTracingShaderGroupStackSizeKHR } },
        { "vkCmdSetRayTracingPipelineStackSizeKHR", { format::ApiCallId::ApiCall_vkCmdSetRayTracingPipelineStackSizeKHR, ApiDump_vkCmdSetRayTracingPipelineStackSizeKHR } },
        { "vkCmdDrawMeshTasksEXT", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksEXT, ApiDump_vkCmdDrawMeshTasksEXT } },
        { "vkCmdDrawMeshTasksIndirectEXT", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirectEXT, ApiDump_vkCmdDrawMeshTasksIndirectEXT } },
        { "vkCmdDrawMeshTasksIndirectCountEXT", { format::ApiCallId::ApiCall_vkCmdDrawMeshTasksIndirectCountEXT, ApiDump_vkCmdDrawMeshTasksIndirectCountEXT } },
    };

    return table;
}
GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
