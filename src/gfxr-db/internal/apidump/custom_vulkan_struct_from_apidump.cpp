/********************************************************************************
    Copyright 2026 The Sokatoa Project Authors

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

/** Hand written api dump encoders for the structs gfxreconstruct also hand writes.
 *
 * These are the structs on the shared blacklist plus every union, which the generators skip for the
 * same reason on both sides: their encoding is not a straight walk of their members. Unions need a
 * discriminator, and several structs encode a member conditionally.
 *
 * Each one mirrors its counterpart in gfxreconstruct's framework/encode/custom_vulkan_struct_encoders.cpp.
 * The layout must agree exactly, because the buffers these produce are parsed by the stock
 * gfxreconstruct decoders, so where gfxreconstruct picks one union member these pick the same one
 * rather than choosing independently.
 */

#include "apidump_context.h"
#include "apidump_struct_encode.h"

#include "generated_vulkan_enum_from_string.h"
#include "generated_vulkan_struct_from_apidump.h"

#include "util/logging.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace
{

/** Reads an enum member of a struct, tolerating both the name and the numeric spelling. */
template <typename T>
T ReadEnum(ApiDumpContext& ctx, const ApiDumpNode& node, bool (*parse)(std::string_view, T&))
{
    T value{};

    // Signed, so that a negative enum such as a VkResult error code survives the numeric path.
    int64_t numeric = 0;
    if (ParseLeadingSigned(node.ValueString(), numeric))
    {
        return static_cast<T>(numeric);
    }

    if (!node.ValueString().empty() && !parse(node.ValueString(), value))
    {
        ++ctx.MutableStats().unknown_enum_names;
    }

    return value;
}

/** VkDescriptorImageInfo, whose handles gfxreconstruct encodes conditionally on descriptor type.
 *
 * A sampler is only meaningful for sampler descriptors and an image view for everything else; the
 * other is encoded as a raw id because the driver ignores it and it may not be a real handle.
 * Feeding an ignored handle through the map would invent an object that never existed.
 */
void DescriptorImageInfoFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value, VkDescriptorType type)
{
    if ((type == VK_DESCRIPTOR_TYPE_SAMPLER) || (type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER))
    {
        ctx.VulkanHandleValue(value["sampler"], VK_OBJECT_TYPE_SAMPLER);
    }
    else
    {
        ctx.UInt64Value(value["sampler"]);
    }

    if (type != VK_DESCRIPTOR_TYPE_SAMPLER)
    {
        ctx.VulkanHandleValue(value["imageView"], VK_OBJECT_TYPE_IMAGE_VIEW);
    }
    else
    {
        ctx.UInt64Value(value["imageView"]);
    }

    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
}

/** The shared tail of VkMemoryToImageCopy and VkImageToMemoryCopy. */
void HostImageCopyRegionFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);

    // gfxreconstruct sizes the host pointer from the image format it tracked at capture time. An
    // api dump records no memory contents at all, so the pointer is encoded as an address only.
    ctx.VoidPtrValue(value["pHostPointer"]);

    ctx.UInt32Value(value["memoryRowLength"]);
    ctx.UInt32Value(value["memoryImageHeight"]);
    StructFromApiDump<VkImageSubresourceLayers>(ctx, value["imageSubresource"]);
    StructFromApiDump<VkOffset3D>(ctx, value["imageOffset"]);
    StructFromApiDump<VkExtent3D>(ctx, value["imageExtent"]);
}

/** A union member the parent struct always selects for itself, so reaching it means a bug. */
void UnreachableUnion(ApiDumpContext& ctx, const char* name)
{
    ++ctx.MutableStats().unknown_structure_types;
    GFXRECON_LOG_WARNING("StructFromApiDump: %s encoded standalone; its parent should select a member", name);
}

} // namespace

//
// Unions with no discriminator. gfxreconstruct encodes the widest member and lets the decoder
// reinterpret, so these read the matching member out of the JSON, which dumps every variant.
//

template <> void StructFromApiDump<VkClearColorValue>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Array(value["uint32"], 4);
}

template <> void StructFromApiDump<VkClearValue>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    // VkClearColorValue is the larger of the two members, so it is the one gfxreconstruct encodes.
    StructFromApiDump<VkClearColorValue>(ctx, value["color"]);
}

template <> void StructFromApiDump<VkPipelineExecutableStatisticValueKHR>(
    ApiDumpContext& ctx, const ApiDumpNode& value
)
{
    ctx.UInt64Value(value["u64"]);
}

template <> void StructFromApiDump<VkDeviceOrHostAddressKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["deviceAddress"]);
}

template <> void StructFromApiDump<VkDeviceOrHostAddressConstKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt64Value(value["deviceAddress"]);
}

template <> void StructFromApiDump<VkPerformanceCounterResultKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    // A performance counter result is interpreted using the counter description that produced it,
    // which the encoding does not carry; the widest member preserves the bits either way.
    ctx.UInt64Value(value["uint64"]);
}

//
// The plain base structs.
//

template <> void StructFromApiDump<VkBaseInStructure>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

template <> void StructFromApiDump<VkBaseOutStructure>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
}

//
// Structs whose member encoding depends on a discriminator.
//

template <> void StructFromApiDump<VkDescriptorImageInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    // Standalone, with no descriptor type in hand. Both handles are encoded as raw ids, matching
    // what gfxreconstruct does for the member it considers ignored.
    ctx.UInt64Value(value["sampler"]);
    ctx.UInt64Value(value["imageView"]);
    ctx.EnumValue(value["imageLayout"], EnumFromString_VkImageLayout);
}

template <> void StructFromApiDump<VkWriteDescriptorSet>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["dstSet"], VK_OBJECT_TYPE_DESCRIPTOR_SET);
    ctx.UInt32Value(value["dstBinding"]);
    ctx.UInt32Value(value["dstArrayElement"]);
    ctx.UInt32Value(value["descriptorCount"]);
    ctx.EnumValue(value["descriptorType"], EnumFromString_VkDescriptorType);

    const VkDescriptorType descriptor_type =
        ReadEnum(ctx, value["descriptorType"], EnumFromString_VkDescriptorType);

    bool omit_image_data        = true;
    bool omit_buffer_data       = true;
    bool omit_texel_buffer_data = true;

    switch (descriptor_type)
    {
        case VK_DESCRIPTOR_TYPE_SAMPLER:
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
        case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            omit_image_data = false;
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
            omit_buffer_data = false;
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
        case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
            omit_texel_buffer_data = false;
            break;
        default:
            // The remaining types carry their handles in a pNext structure instead.
            break;
    }

    const ApiDumpNode image_info   = value["pImageInfo"];
    const ApiDumpNode buffer_info  = value["pBufferInfo"];
    const ApiDumpNode texel_buffer = value["pTexelBufferView"];
    const size_t      count        = ctx.Length(value["descriptorCount"]);

    // The array length is written even when the data is omitted, matching EncodeStructArrayPreamble.
    const size_t image_count = (image_info.ElementCount() > 0) ? image_info.ElementCount() : count;
    ctx.Encoder().EncodeStructArrayPreamble(
        image_count, image_info.Address(), image_info.IsNullPointer(), !omit_image_data && image_info.HasData()
    );

    if (!omit_image_data && !image_info.IsNullPointer() && image_info.HasData())
    {
        for (size_t i = 0; i < image_info.ElementCount(); ++i)
        {
            DescriptorImageInfoFromApiDump(ctx, image_info.ElementAt(i), descriptor_type);
        }
    }

    if (omit_buffer_data)
    {
        const size_t buffer_count = (buffer_info.ElementCount() > 0) ? buffer_info.ElementCount() : count;
        ctx.Encoder().EncodeStructArrayPreamble(
            buffer_count, buffer_info.Address(), buffer_info.IsNullPointer(), false
        );
    }
    else
    {
        StructArrayFromApiDump<VkDescriptorBufferInfo>(ctx, buffer_info, count);
    }

    if (omit_texel_buffer_data)
    {
        const size_t texel_count = (texel_buffer.ElementCount() > 0) ? texel_buffer.ElementCount() : count;
        ctx.Encoder().EncodeHandleIdArray(
            nullptr, texel_count, texel_buffer.Address(), texel_buffer.IsNullPointer(), false
        );
    }
    else
    {
        ctx.VulkanHandleArray(texel_buffer, VK_OBJECT_TYPE_BUFFER_VIEW, count);
    }
}

template <> void StructFromApiDump<VkPerformanceValueINTEL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["type"], EnumFromString_VkPerformanceValueTypeINTEL);

    const VkPerformanceValueTypeINTEL type =
        ReadEnum(ctx, value["type"], EnumFromString_VkPerformanceValueTypeINTEL);

    const ApiDumpNode data = value["data"];

    if (type == VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL)
    {
        ctx.StringValue(data["valueString"]);
    }
    else
    {
        ctx.UInt64Value(data["value64"]);
    }
}

template <> void StructFromApiDump<VkAccelerationStructureGeometryKHR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["geometryType"], EnumFromString_VkGeometryTypeKHR);

    const VkGeometryTypeKHR geometry_type = ReadEnum(ctx, value["geometryType"], EnumFromString_VkGeometryTypeKHR);
    const ApiDumpNode       geometry      = value["geometry"];

    switch (geometry_type)
    {
        case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
            StructFromApiDump<VkAccelerationStructureGeometryTrianglesDataKHR>(ctx, geometry["triangles"]);
            break;
        case VK_GEOMETRY_TYPE_AABBS_KHR:
            StructFromApiDump<VkAccelerationStructureGeometryAabbsDataKHR>(ctx, geometry["aabbs"]);
            break;
        case VK_GEOMETRY_TYPE_INSTANCES_KHR:
            StructFromApiDump<VkAccelerationStructureGeometryInstancesDataKHR>(ctx, geometry["instances"]);
            break;
        default:
            break;
    }

    ctx.FlagsValue(value["flags"], EnumFromString_VkGeometryFlagBitsKHR);
}

template <> void StructFromApiDump<VkAccelerationStructureMotionInstanceNV>(
    ApiDumpContext& ctx, const ApiDumpNode& value
)
{
    ctx.EnumValue(value["type"], EnumFromString_VkAccelerationStructureMotionInstanceTypeNV);
    ctx.FlagsValue(value["flags"]);

    const VkAccelerationStructureMotionInstanceTypeNV type =
        ReadEnum(ctx, value["type"], EnumFromString_VkAccelerationStructureMotionInstanceTypeNV);
    const ApiDumpNode data = value["data"];

    switch (type)
    {
        case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_STATIC_NV:
            StructFromApiDump<VkAccelerationStructureInstanceKHR>(ctx, data["staticInstance"]);
            break;
        case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MATRIX_MOTION_NV:
            StructFromApiDump<VkAccelerationStructureMatrixMotionInstanceNV>(ctx, data["matrixMotionInstance"]);
            break;
        case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV:
            StructFromApiDump<VkAccelerationStructureSRTMotionInstanceNV>(ctx, data["srtMotionInstance"]);
            break;
        default:
            break;
    }
}

template <> void StructFromApiDump<VkPushDescriptorSetWithTemplateInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.VulkanHandleValue(value["descriptorUpdateTemplate"], VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE);
    ctx.VulkanHandleValue(value["layout"], VK_OBJECT_TYPE_PIPELINE_LAYOUT);
    ctx.UInt32Value(value["set"]);
}

template <> void StructFromApiDump<VkIndirectExecutionSetCreateInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkIndirectExecutionSetInfoTypeEXT);

    const VkIndirectExecutionSetInfoTypeEXT type =
        ReadEnum(ctx, value["type"], EnumFromString_VkIndirectExecutionSetInfoTypeEXT);
    const ApiDumpNode info = value["info"];

    switch (type)
    {
        case VK_INDIRECT_EXECUTION_SET_INFO_TYPE_PIPELINES_EXT:
            StructPtrFromApiDump<VkIndirectExecutionSetPipelineInfoEXT>(ctx, info["pPipelineInfo"]);
            break;
        case VK_INDIRECT_EXECUTION_SET_INFO_TYPE_SHADER_OBJECTS_EXT:
            StructPtrFromApiDump<VkIndirectExecutionSetShaderInfoEXT>(ctx, info["pShaderInfo"]);
            break;
        default:
            break;
    }
}

template <> void StructFromApiDump<VkIndirectCommandsLayoutTokenEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkIndirectCommandsTokenTypeEXT);

    const VkIndirectCommandsTokenTypeEXT type =
        ReadEnum(ctx, value["type"], EnumFromString_VkIndirectCommandsTokenTypeEXT);
    const ApiDumpNode data = value["data"];

    switch (type)
    {
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_EXT:
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_SEQUENCE_INDEX_EXT:
            StructPtrFromApiDump<VkIndirectCommandsPushConstantTokenEXT>(ctx, data["pPushConstant"]);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_EXT:
            StructPtrFromApiDump<VkIndirectCommandsVertexBufferTokenEXT>(ctx, data["pVertexBuffer"]);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_EXT:
            StructPtrFromApiDump<VkIndirectCommandsIndexBufferTokenEXT>(ctx, data["pIndexBuffer"]);
            break;
        case VK_INDIRECT_COMMANDS_TOKEN_TYPE_EXECUTION_SET_EXT:
            StructPtrFromApiDump<VkIndirectCommandsExecutionSetTokenEXT>(ctx, data["pExecutionSet"]);
            break;
        default:
            break;
    }

    ctx.UInt32Value(value["offset"]);
}

template <> void StructFromApiDump<VkCopyMemoryToImageInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkHostImageCopyFlagBits);
    ctx.VulkanHandleValue(value["dstImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["dstImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);

    const ApiDumpNode regions = value["pRegions"];
    const size_t      count   = (regions.ElementCount() > 0) ? regions.ElementCount()
                                                             : ctx.Length(value["regionCount"]);

    ctx.Encoder().EncodeStructArrayPreamble(count, regions.Address(), regions.IsNullPointer(), regions.HasData());

    for (size_t i = 0; i < regions.ElementCount(); ++i)
    {
        HostImageCopyRegionFromApiDump(ctx, regions.ElementAt(i));
    }
}

template <> void StructFromApiDump<VkMemoryToImageCopy>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    HostImageCopyRegionFromApiDump(ctx, value);
}

template <> void StructFromApiDump<VkCopyImageToMemoryInfo>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.FlagsValue(value["flags"], EnumFromString_VkHostImageCopyFlagBits);
    ctx.VulkanHandleValue(value["srcImage"], VK_OBJECT_TYPE_IMAGE);
    ctx.EnumValue(value["srcImageLayout"], EnumFromString_VkImageLayout);
    ctx.UInt32Value(value["regionCount"]);

    const ApiDumpNode regions = value["pRegions"];
    const size_t      count   = (regions.ElementCount() > 0) ? regions.ElementCount()
                                                             : ctx.Length(value["regionCount"]);

    ctx.Encoder().EncodeStructArrayPreamble(count, regions.Address(), regions.IsNullPointer(), regions.HasData());

    for (size_t i = 0; i < regions.ElementCount(); ++i)
    {
        HostImageCopyRegionFromApiDump(ctx, regions.ElementAt(i));
    }
}

template <> void StructFromApiDump<VkImageToMemoryCopy>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    HostImageCopyRegionFromApiDump(ctx, value);
}

template <> void StructFromApiDump<VkLayerSettingEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.StringValue(value["pLayerName"]);
    ctx.StringValue(value["pSettingName"]);
    ctx.EnumValue(value["type"], EnumFromString_VkLayerSettingTypeEXT);
    ctx.UInt32Value(value["valueCount"]);

    const VkLayerSettingTypeEXT type   = ReadEnum(ctx, value["type"], EnumFromString_VkLayerSettingTypeEXT);
    const ApiDumpNode           values = value["pValues"];
    const size_t                count  = ctx.Length(value["valueCount"]);

    switch (type)
    {
        case VK_LAYER_SETTING_TYPE_BOOL32_EXT:
        case VK_LAYER_SETTING_TYPE_UINT32_EXT:
            ctx.UInt32Array(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_INT32_EXT:
            ctx.Int32Array(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_INT64_EXT:
            ctx.Int64Array(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_UINT64_EXT:
            ctx.UInt64Array(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_FLOAT32_EXT:
            ctx.FloatArray(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_FLOAT64_EXT:
            ctx.DoubleArray(values, count);
            break;
        case VK_LAYER_SETTING_TYPE_STRING_EXT:
            ctx.StringArray(values, count);
            break;
        default:
            break;
    }
}

template <> void StructFromApiDump<VkDescriptorGetInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.EnumValue(value["type"], EnumFromString_VkDescriptorType);

    const VkDescriptorType type = ReadEnum(ctx, value["type"], EnumFromString_VkDescriptorType);
    const ApiDumpNode      data = value["data"];

    switch (type)
    {
        case VK_DESCRIPTOR_TYPE_SAMPLER:
            ctx.VulkanHandlePtr(data["pSampler"], VK_OBJECT_TYPE_SAMPLER);
            break;
        case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
        case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
        case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
        {
            const char* member = (type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) ? "pCombinedImageSampler"
                                 : (type == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)     ? "pInputAttachmentImage"
                                 : (type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE)        ? "pSampledImage"
                                                                                     : "pStorageImage";
            const ApiDumpNode image = data[member];

            ctx.Encoder().EncodeStructPtrPreamble(image.Address(), image.IsNullPointer(), image.HasData());
            if (!image.IsNullPointer() && image.HasData())
            {
                DescriptorImageInfoFromApiDump(ctx, image, type);
            }
            break;
        }
        case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            StructPtrFromApiDump<VkDescriptorAddressInfoEXT>(ctx, data["pUniformTexelBuffer"]);
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
            StructPtrFromApiDump<VkDescriptorAddressInfoEXT>(ctx, data["pStorageTexelBuffer"]);
            break;
        case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            StructPtrFromApiDump<VkDescriptorAddressInfoEXT>(ctx, data["pUniformBuffer"]);
            break;
        case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            StructPtrFromApiDump<VkDescriptorAddressInfoEXT>(ctx, data["pStorageBuffer"]);
            break;
        case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
            ctx.UInt64Value(data["accelerationStructure"]);
            break;
        default:
            break;
    }
}

template <> void StructFromApiDump<VkDataGraphPipelineConstantARM>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.EnumValue(value["sType"], EnumFromString_VkStructureType);
    PNextFromApiDump(ctx, value["pNext"]);
    ctx.UInt32Value(value["id"]);

    // gfxreconstruct derives the constant data size from the VkTensorDescriptionARM in the pNext
    // chain. Here the layer either expanded the bytes or it did not, so the recorded element count
    // is both simpler and closer to what was actually captured.
    ctx.UInt8Array(value["pConstantData"]);
}

//
// Win32 platform structs, reachable through VkExportMemoryWin32HandleInfoKHR. gfxreconstruct hand
// writes these in framework/encode/custom_common_struct_encoders.cpp; the layouts must match.
//
// An Android api dump will never contain them, but the encoders are generated from the full
// registry on every platform, so the specializations have to exist for the library to link.
//

template <> void StructFromApiDump<ACL>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["AclRevision"]);
    ctx.UInt8Value(value["Sbz1"]);
    ctx.UInt16Value(value["AclSize"]);
    ctx.UInt16Value(value["AceCount"]);
    ctx.UInt16Value(value["Sbz2"]);
}

template <> void StructFromApiDump<SECURITY_DESCRIPTOR>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt8Value(value["Revision"]);
    ctx.UInt8Value(value["Sbz1"]);
    ctx.UInt16Value(value["Control"]);

    // gfxreconstruct packs each variable length SID into a byte array. An api dump has no way to
    // record one, so both arrays are encoded empty, which is the shape the decoder expects for an
    // absent owner or group.
    ctx.UInt8Array(value["Owner"]);
    ctx.UInt8Array(value["Group"]);

    StructPtrFromApiDump<ACL>(ctx, value["Sacl"]);
    StructPtrFromApiDump<ACL>(ctx, value["Dacl"]);
}

template <> void StructFromApiDump<SECURITY_ATTRIBUTES>(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    ctx.UInt32Value(value["nLength"]);
    StructPtrFromApiDump<SECURITY_DESCRIPTOR>(ctx, value["lpSecurityDescriptor"]);
    ctx.Int32Value(value["bInheritHandle"]);
}

//
// Union payloads. A parent always selects the active member, so these are only reachable through a
// path that should not exist; they encode nothing rather than guessing a member.
//

template <> void StructFromApiDump<VkAccelerationStructureGeometryDataKHR>(ApiDumpContext& ctx, const ApiDumpNode&)
{
    UnreachableUnion(ctx, "VkAccelerationStructureGeometryDataKHR");
}

template <> void StructFromApiDump<VkAccelerationStructureMotionInstanceDataNV>(
    ApiDumpContext& ctx, const ApiDumpNode&
)
{
    UnreachableUnion(ctx, "VkAccelerationStructureMotionInstanceDataNV");
}

template <> void StructFromApiDump<VkDescriptorDataEXT>(ApiDumpContext& ctx, const ApiDumpNode&)
{
    UnreachableUnion(ctx, "VkDescriptorDataEXT");
}

template <> void StructFromApiDump<VkIndirectCommandsTokenDataEXT>(ApiDumpContext& ctx, const ApiDumpNode&)
{
    UnreachableUnion(ctx, "VkIndirectCommandsTokenDataEXT");
}

template <> void StructFromApiDump<VkIndirectExecutionSetInfoEXT>(ApiDumpContext& ctx, const ApiDumpNode&)
{
    UnreachableUnion(ctx, "VkIndirectExecutionSetInfoEXT");
}

template <> void StructFromApiDump<VkPerformanceValueDataINTEL>(ApiDumpContext& ctx, const ApiDumpNode&)
{
    UnreachableUnion(ctx, "VkPerformanceValueDataINTEL");
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
