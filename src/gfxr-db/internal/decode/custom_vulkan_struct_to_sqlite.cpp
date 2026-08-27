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

#include "custom_vulkan_struct_to_sqlite.h"

#include "sqlite_utils.h"

#include "generated/generated_vulkan_struct_decoders.h"
#include "generated/generated_vulkan_struct_to_sqlite.h"
#include "generated/generated_vulkan_enum_to_sqlite.h"
#include "decode/descriptor_update_template_decoder.h"
#include "decode/custom_vulkan_struct_decoders.h"
#include "util/platform.h"
#include "util/defines.h"
#include "vulkan/vulkan.h"
#include "utf8_convert.h"

#include <cmath>
#include <string>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    float data,
    std::string_view typeName
)
{
    if (std::isnan(data))
    {
        // sqlite3 maps NaN numbers to a null database value.
        // Hence using a string value instead.
        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, "NaN");
    }
    else if (std::isinf(data))
    {
        const char* inf = (data < 0) ? "-inf" : "+inf";
        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, inf);
    }
    else
    {
        // Normal and denormal/subnormal numbers pass through unchanged and unremarked.
        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
    }
}

void HandleToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const format::HandleId data,
    std::string_view typeName
)
{
    if (data)
    {
        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void HandleToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const format::HandleId* data,
    size_t num_elements,
    std::string_view typeName
)
{
    if (data)
    {
        const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
        for (size_t i = 0; i < num_elements; ++i)
        {
            // generate the arrayMembers entries
            FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
            HandleToSqlite(statements, memberInfo, i, fieldName, data[i], typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StringArrayDecoder* data,
    std::string_view typeName
)
{
    if (data && data->GetPointer())
    {
        const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, "string");
        const auto decodedData = data->GetPointer();
        for (size_t i = 0; i < data->GetLength(); ++i)
        {
            // generate the arrayMembers entries
            FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
            FieldToSqlite(statements, memberInfo, i, fieldName, std::string(decodedData[i]), typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StringDecoder* data,
    std::string_view typeName
)
{
    if (data && data->GetPointer())
    {
        const auto decodedData = data->GetPointer();
        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, std::string(decodedData));
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StringDecoder& data,
    std::string_view typeName
)
{
    FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, &data, typeName);
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const WStringDecoder* data,
    std::string_view typeName
)
{
    if (data && data->GetPointer())
    {
        const auto decodedData = data->GetPointer();

        // Note: converting to UTF-8 should not affect visual representation but we avoid
        // complexity in storing UTF-16 encoded strings in the database
        // (specifically the command arguments table)
        std::string result = ::util::ConvertToUTF8(decodedData);

        RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, result);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    VkGeometryTypeKHR discriminant,
    const Decoded_VkAccelerationStructureGeometryDataKHR* data,
    std::string_view typeName
)
{
    if (data)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        switch (discriminant)
        {
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_TRIANGLES_KHR:
                FieldToSqlite(
                    statements,
                    memberInfo,
                    1,
                    "triangles",
                    data->triangles,
                    "VkAccelerationStructureGeometryTrianglesDataKHR"
                );
                break;
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_AABBS_KHR:
                FieldToSqlite(
                    statements, memberInfo, 2, "aabbs", data->aabbs, "VkAccelerationStructureGeometryAabbsDataKHR"
                );
                break;
            case VkGeometryTypeKHR::VK_GEOMETRY_TYPE_INSTANCES_KHR:
                FieldToSqlite(
                    statements,
                    memberInfo,
                    3,
                    "instances",
                    data->instances,
                    "VkAccelerationStructureGeometryInstancesDataKHR"
                );
                break;
            default:
                GFXRECON_SQLITE_LOG_WARNING_ONCE("Unknown GeometryType: %s", std::to_string(discriminant).c_str());
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkAccelerationStructureGeometryDataKHR");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkAccelerationStructureGeometryKHR* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(statements, memberInfo, 2, "geometryType", decoded_value.geometryType, "VkGeometryTypeKHR");
        FieldToSqlite(
            statements,
            memberInfo,
            3,
            "geometry",
            decoded_value.geometryType,
            meta_struct.geometry,
            "VkAccelerationStructureGeometryDataKHR"
        );
        FieldToSqlite(statements, memberInfo, 4, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkAccelerationStructureGeometryKHR");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDataGraphPipelineConstantARM* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(statements, memberInfo, 2, "id", decoded_value.id, "uint32_t");
        RecordFieldAsHex(statements, memberInfo, 3, "pConstantData", "void*", meta_struct.pConstantData);
        FieldToSqlite(statements, memberInfo, 4, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkDataGraphPipelineConstantARM");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkBaseOutStructure* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(statements, memberInfo, 2, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkBaseOutStructure");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkAccelerationStructureMotionInstanceNV* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkAccelerationStructureMotionInstanceNV& decoded_value = *data->decoded_value;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(
            statements, memberInfo, 1, "type", decoded_value.type, "VkAccelerationStructureMotionInstanceTypeNV"
        );
        FieldToSqlite(
            statements,
            memberInfo,
            2,
            "flags",
            VkAccelerationStructureMotionInstanceFlagsNV_t(),
            decoded_value.flags,
            "VkAccelerationStructureMotionInstanceFlagsNV"
        );
        // generated when included in the generator, error states there is no data field, so skip it
        // FieldToSqlite(statements, memberInfo, 3, "data", meta_struct.data,
        // "VkAccelerationStructureMotionInstanceDataNV");
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkAccelerationStructureMotionInstanceNV");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkClearValue* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "color", meta_struct.color, "VkClearColorValue");
        FieldToSqlite(statements, memberInfo, 2, "depthStencil.depth", decoded_value.depthStencil.depth, "float");
        FieldToSqlite(
            statements, memberInfo, 3, "depthStencil.stencil", decoded_value.depthStencil.stencil, "uint32_t"
        );
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkClearColorValue* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        FieldToSqlite(statements, memberInfo, 1, "float32", decoded_value.float32, 4, "float");
        FieldToSqlite(statements, memberInfo, 2, "int32", decoded_value.int32, 4, "int32_t");
        FieldToSqlite(statements, memberInfo, 3, "uint32", decoded_value.uint32, 4, "uint32_t");
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    int discriminant,
    const Decoded_VkDeviceOrHostAddressConstKHR* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case 0:
                RecordFieldAsHex(
                    statements, memberInfo, 1, "deviceAddress", "VkDeviceAddress", decoded_value.deviceAddress
                );
                break;
            case 1:
                RecordFieldAsHex(statements, memberInfo, 2, "hostAddress", "const void*", decoded_value.hostAddress);
                break;
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDeviceOrHostAddressConstKHR* data,
    std::string_view typeName
)
{
    FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, 0, data, typeName);
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    int discriminant,
    const Decoded_VkDeviceOrHostAddressKHR* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case 0:
                RecordFieldAsHex(
                    statements, memberInfo, 1, "deviceAddress", "VkDeviceAddress", decoded_value.deviceAddress
                );
                break;
            case 1:
                RecordFieldAsHex(statements, memberInfo, 2, "hostAddress", "void*", decoded_value.hostAddress);
                break;
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDeviceOrHostAddressKHR* data,
    std::string_view typeName
)
{
    FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, 0, data, typeName);
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    VkPipelineExecutableStatisticFormatKHR discriminant,
    const Decoded_VkPipelineExecutableStatisticValueKHR* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        switch (discriminant)
        {
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR:
                FieldToSqlite(statements, memberInfo, 1, "b32", decoded_value.b32, "VkBool32");
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR:
                FieldToSqlite(statements, memberInfo, 2, "i64", decoded_value.i64, "int64_t");
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR:
                FieldToSqlite(statements, memberInfo, 3, "u64", decoded_value.u64, "uint64_t");
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR:
                FieldToSqlite(statements, memberInfo, 4, "f64", decoded_value.f64, "double");
                break;
            case VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_MAX_ENUM_KHR:
                GFXRECON_SQLITE_LOG_WARNING_AT(
                    memberInfo.eventId, "Invalid format: VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_MAX_ENUM_KHR"
                );
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPipelineExecutableStatisticKHR* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(statements, memberInfo, 2, "name", &meta_struct.name, "char*");
        FieldToSqlite(statements, memberInfo, 3, "description", &meta_struct.description, "char*");
        FieldToSqlite(
            statements, memberInfo, 4, "format", decoded_value.format, "VkPipelineExecutableStatisticFormatKHR"
        );
        FieldToSqlite(
            statements,
            memberInfo,
            5,
            "value",
            decoded_value.format,
            meta_struct.value,
            "VkPipelineExecutableStatisticValueKHR"
        );
        FieldToSqlite(statements, memberInfo, 6, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_SECURITY_ATTRIBUTES* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "bInheritHandle", decoded_value.bInheritHandle, "BOOL");
        FieldToSqlite(statements, memberInfo, 2, "nLength", decoded_value.nLength, "DWORD");
        FieldToSqlite(
            statements, memberInfo, 3, "lpSecurityDescriptor", meta_struct.lpSecurityDescriptor->GetAddress(), "LPVOID"
        );
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDescriptorImageInfo* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        HandleToSqlite(statements, memberInfo, 1, "sampler", meta_struct.sampler, "VkSampler");
        HandleToSqlite(statements, memberInfo, 2, "imageView", meta_struct.imageView, "VkImageView");
        HandleToSqlite(statements, memberInfo, 3, "imageLayout", decoded_value.imageLayout, "VkImageLayout");
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    VkDescriptorType discriminant,
    const Decoded_VkDescriptorImageInfo* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        if (discriminant == VK_DESCRIPTOR_TYPE_SAMPLER || discriminant == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
        {
            // value is only read if its a sampler type
            // otherwise values can be invalid and out of range by default
            // https://registry.khronos.org/vulkan/specs/latest/man/html/VkWriteDescriptorSet.html#VUID-VkWriteDescriptorSet-descriptorType-00325
            HandleToSqlite(statements, memberInfo, 1, "sampler", meta_struct.sampler, "VkSampler");
        }
        // TODO: potentially handle other cases that could allow imageView/imageLayout to be invalid
        HandleToSqlite(statements, memberInfo, 2, "imageView", meta_struct.imageView, "VkImageView");
        HandleToSqlite(statements, memberInfo, 3, "imageLayout", decoded_value.imageLayout, "VkImageLayout");
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkWriteDescriptorSet* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        HandleToSqlite(statements, memberInfo, 2, "dstSet", meta_struct.dstSet, "VkDescriptorSet");
        FieldToSqlite(statements, memberInfo, 3, "dstBinding", decoded_value.dstBinding, "uint32_t");
        FieldToSqlite(statements, memberInfo, 4, "dstArrayElement", decoded_value.dstArrayElement, "uint32_t");
        FieldToSqlite(statements, memberInfo, 5, "descriptorCount", decoded_value.descriptorCount, "uint32_t");
        FieldToSqlite(statements, memberInfo, 6, "descriptorType", decoded_value.descriptorType, "VkDescriptorType");
        switch (decoded_value.descriptorType)
        {
            case VK_DESCRIPTOR_TYPE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            case VK_DESCRIPTOR_TYPE_SAMPLE_WEIGHT_IMAGE_QCOM:
            case VK_DESCRIPTOR_TYPE_BLOCK_MATCH_IMAGE_QCOM:
                FieldToSqlite(
                    statements,
                    memberInfo,
                    7,
                    "pImageInfo",
                    decoded_value.descriptorType,
                    meta_struct.pImageInfo->GetMetaStructPointer(),
                    "VkDescriptorImageInfo*"
                );
                break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
                FieldToSqlite(
                    statements, memberInfo, 7, "pBufferInfo", meta_struct.pBufferInfo, "VkDescriptorBufferInfo*"
                );
                break;
            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
                HandleToSqlite(
                    statements, memberInfo, 7, "pTexelBufferView", &meta_struct.pTexelBufferView, "VkBufferView*"
                );
                break;
            case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
            case VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV:
            case VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK:
            case VK_DESCRIPTOR_TYPE_TENSOR_ARM:
                // Nothing to do here for acceleration-structures inline-uniform-blocks and tensors,
                // as the rest of the data is stored in the pNext chain
                break;
            case VK_DESCRIPTOR_TYPE_PARTITIONED_ACCELERATION_STRUCTURE_NV:
            case VK_DESCRIPTOR_TYPE_MUTABLE_EXT:
                GFXRECON_SQLITE_LOG_WARNING_AT(
                    memberInfo.eventId, "Descriptor type not supported at " __FILE__ ", line: %d.", __LINE__
                );
                break;

            case VK_DESCRIPTOR_TYPE_MAX_ENUM:
                GFXRECON_SQLITE_LOG_WARNING_AT(memberInfo.eventId, "Invalid descriptor type: VK_DESCRIPTOR_TYPE_MAX_ENUM");
                break;
        }
        FieldToSqlite(statements, memberInfo, 8, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const VkPerformanceValueTypeINTEL discriminant,
    const Decoded_VkPerformanceValueDataINTEL* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        switch (discriminant)
        {
            case VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL:
                FieldToSqlite(statements, memberInfo, 1, "value32", decoded_value.value32, "uint32_t");
                break;
            case VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL:
                FieldToSqlite(statements, memberInfo, 2, "value64", decoded_value.value64, "uint64_t");
                break;
            case VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL:
                FieldToSqlite(statements, memberInfo, 3, "valueFloat", decoded_value.valueFloat, "float");
                break;
            case VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL:
                FieldToSqlite(statements, memberInfo, 4, "valueBool", decoded_value.valueBool, "VkBool32");
                break;
            case VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL:
                FieldToSqlite(statements, memberInfo, 5, "valueString", meta_struct.valueString, "const char*");
                break;
            case VK_PERFORMANCE_VALUE_TYPE_MAX_ENUM_INTEL:
                GFXRECON_SQLITE_LOG_WARNING_AT(
                    memberInfo.eventId, "Invalid performance value type: VK_PERFORMANCE_VALUE_TYPE_MAX_ENUM_INTEL"
                );
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPerformanceValueINTEL* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "type", decoded_value.type, "VkPerformanceValueTypeINTEL");
        FieldToSqlite(
            statements, memberInfo, 2, "data", decoded_value.type, meta_struct.data, "VkPerformanceValueDataINTEL"
        );
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkShaderModuleCreateInfo* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(
            statements,
            memberInfo,
            2,
            "flags",
            VkShaderModuleCreateFlags_t(),
            decoded_value.flags,
            "VkShaderModuleCreateFlags"
        );
        FieldToSqlite(statements, memberInfo, 3, "codeSize", decoded_value.codeSize, "size_t");
        // TODO: Use "[Binary data]" as placeholder until we support writing binary data to file.
        FieldToSqlite(statements, memberInfo, 4, "pCode", "[Binary data]", "const void*");
        FieldToSqlite(statements, memberInfo, 5, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPipelineCacheCreateInfo* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        const auto& decoded_value = *data->decoded_value;
        const auto& meta_struct = *data;
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(
            statements,
            memberInfo,
            2,
            "flags",
            VkPipelineCacheCreateFlags_t(),
            decoded_value.flags,
            "VkPipelineCacheCreateFlags"
        );
        FieldToSqlite(statements, memberInfo, 3, "initialDataSize", decoded_value.initialDataSize, "size_t");
        // TODO: Use "[Binary data]" as placeholder until we support writing binary data to file.
        FieldToSqlite(statements, memberInfo, 4, "pInitialData", "[Binary data]", "const void*");
        FieldToSqlite(statements, memberInfo, 5, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

template <>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const PointerDecoder<uint64_t, uint64_t>& data,
    std::string_view typeName
)
{
    if (data.GetPointer())
    {
        const auto decoded_value = data.GetPointer();
        const auto length = data.GetLength();
        if (length > 1)
        {
            const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
            for (size_t i = 0; i < length; ++i)
            {
                // generate the arrayMembers entries
                FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
                FieldToSqlite(statements, memberInfo, i, fieldName, decoded_value[i], typeName);
            }
        }
        else
        {
            FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, *decoded_value, typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const DescriptorUpdateTemplateDecoder* pData,
    std::string_view typeName
)
{
    if (pData)
    {
        const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(
            statements, memberInfo, 1, "imageInfos", pData->GetImageInfoMetaStructPointer(), "VkDescriptorImageInfo"
        );
        FieldToSqlite(
            statements, memberInfo, 2, "bufferInfos", pData->GetBufferInfoMetaStructPointer(), "VkDescriptorBufferInfo"
        );
        const auto texel_buffer_view_count = pData->GetTexelBufferViewCount();
        HandleToSqlite(
            statements,
            memberInfo,
            3,
            "bufferViews",
            pData->GetTexelBufferViewHandleIdsPointer(),
            texel_buffer_view_count,
            "VkBufferView"
        );
        const auto acceleration_structure_count = pData->GetAccelerationStructureKHRCount();
        HandleToSqlite(
            statements,
            memberInfo,
            4,
            "accelStructViews",
            pData->GetAccelerationStructureKHRHandleIdsPointer(),
            acceleration_structure_count,
            "VkAccelerationStructureKHR"
        );
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkDescriptorUpdateTemplate");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPushDescriptorSetWithTemplateInfoKHR* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkPushDescriptorSetWithTemplateInfoKHR& decoded_value = *data->decoded_value;
        const Decoded_VkPushDescriptorSetWithTemplateInfoKHR& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        HandleToSqlite(
            statements,
            memberInfo,
            2,
            "descriptorUpdateTemplate",
            meta_struct.descriptorUpdateTemplate,
            "VkDescriptorUpdateTemplate"
        );
        HandleToSqlite(statements, memberInfo, 3, "layout", meta_struct.layout, "VkPipelineLayout");
        FieldToSqlite(statements, memberInfo, 4, "set", decoded_value.set, "uint32_t");
        // TODO figure out how to decode the pData pointer (like the other functions do when they
        // decode their pData buffer parameters (see Decode_vkUpdateDescriptorSetWithTemplateKHR))
        // The biggest issue is not knowing the buffer size at this point, where does it come from?
        // FieldToSqlite(statements, memberInfo, "pData", &meta_struct.pData, "const void*");
        FieldToSqlite(statements, memberInfo, 5, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkPushDescriptorSetWithTemplateInfoKHR");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkIndirectCommandsLayoutTokenEXT* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkIndirectCommandsLayoutTokenEXT& decoded_value = *data->decoded_value;
        const Decoded_VkIndirectCommandsLayoutTokenEXT& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(statements, memberInfo, 2, "type", decoded_value.type, "VkIndirectCommandsTokenTypeEXT");
        // TODO figure out how to decode the data member
        // FieldToSqlite(statements, memberInfo, 3, "data", decoded_value.data, "VkIndirectCommandsTokenDataEXT");
        FieldToSqlite(statements, memberInfo, 4, "offset", decoded_value.offset, "uint32_t");
        FieldToSqlite(statements, memberInfo, 5, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "vkIndirectCommandsLayoutTokenEXT");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkImageToMemoryCopy* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkImageToMemoryCopy& decoded_value = *data->decoded_value;
        const Decoded_VkImageToMemoryCopy& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        // TODO: Use "[Binary data]" as placeholder until we support writing binary data to file.
        FieldToSqlite(statements, memberInfo, 2, "pHostPointer", "[Binary data]", "void*");
        FieldToSqlite(statements, memberInfo, 3, "memoryRowLength", decoded_value.memoryRowLength, "uint32_t");
        FieldToSqlite(statements, memberInfo, 4, "memoryImageHeight", decoded_value.memoryImageHeight, "uint32_t");
        FieldToSqlite(
            statements, memberInfo, 5, "imageSubresource", meta_struct.imageSubresource, "VkImageSubresourceLayers"
        );
        FieldToSqlite(statements, memberInfo, 6, "imageOffset", meta_struct.imageOffset, "VkOffset3D");
        FieldToSqlite(statements, memberInfo, 7, "imageExtent", meta_struct.imageExtent, "VkExtent3D");
        FieldToSqlite(statements, memberInfo, 8, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "VkImageToMemoryCopy");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkCopyImageToMemoryInfo* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkCopyImageToMemoryInfo& decoded_value = *data->decoded_value;
        const Decoded_VkCopyImageToMemoryInfo& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(
            statements, memberInfo, 2, "flags", VkHostImageCopyFlags_t(), decoded_value.flags, "VkHostImageCopyFlags"
        );
        HandleToSqlite(statements, memberInfo, 3, "srcImage", meta_struct.srcImage, "VkImage");
        FieldToSqlite(statements, memberInfo, 4, "srcImageLayout", decoded_value.srcImageLayout, "VkImageLayout");
        FieldToSqlite(statements, memberInfo, 5, "regionCount", decoded_value.regionCount, "uint32_t");
        FieldToSqlite(statements, memberInfo, 6, "pRegions", meta_struct.pRegions, "const VkImageToMemoryCopy*");
        FieldToSqlite(statements, memberInfo, 7, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "VkCopyImageToMemoryInfo");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkMemoryToImageCopy* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkMemoryToImageCopy& decoded_value = *data->decoded_value;
        const Decoded_VkMemoryToImageCopy& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        // TODO: Use "[Binary data]" as placeholder until we support writing binary data to file.
        FieldToSqlite(statements, memberInfo, 2, "pHostPointer", "[Binary data]", "const void*");
        FieldToSqlite(statements, memberInfo, 3, "memoryRowLength", decoded_value.memoryRowLength, "uint32_t");
        FieldToSqlite(statements, memberInfo, 4, "memoryImageHeight", decoded_value.memoryImageHeight, "uint32_t");
        FieldToSqlite(
            statements, memberInfo, 5, "imageSubresource", meta_struct.imageSubresource, "VkImageSubresourceLayers"
        );
        FieldToSqlite(statements, memberInfo, 6, "imageOffset", meta_struct.imageOffset, "VkOffset3D");
        FieldToSqlite(statements, memberInfo, 7, "imageExtent", meta_struct.imageExtent, "VkExtent3D");
        FieldToSqlite(statements, memberInfo, 8, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "VkMemoryToImageCopy");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkCopyMemoryToImageInfo* data,
    std::string_view typeName
)
{
    const uint64_t structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, typeName);

    if (data && data->decoded_value)
    {
        const VkCopyMemoryToImageInfo& decoded_value = *data->decoded_value;
        const Decoded_VkCopyMemoryToImageInfo& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };
        FieldToSqlite(statements, memberInfo, 1, "sType", decoded_value.sType, "VkStructureType");
        FieldToSqlite(
            statements, memberInfo, 2, "flags", VkHostImageCopyFlags_t(), decoded_value.flags, "VkHostImageCopyFlags"
        );
        HandleToSqlite(statements, memberInfo, 3, "dstImage", meta_struct.dstImage, "VkImage");
        FieldToSqlite(statements, memberInfo, 4, "dstImageLayout", decoded_value.dstImageLayout, "VkImageLayout");
        FieldToSqlite(statements, memberInfo, 5, "regionCount", decoded_value.regionCount, "uint32_t");
        FieldToSqlite(statements, memberInfo, 6, "pRegions", meta_struct.pRegions, "const VkMemoryToImageCopy*");
        FieldToSqlite(statements, memberInfo, 7, "pNext", meta_struct.pNext);
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "VkCopyMemoryToImageInfo");
    }
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkLayerSettingEXT* data,
    std::string_view typeName
)
{
    if (data && data->decoded_value)
    {
        const auto structId = RecordStruct(statements, fieldInfo, fieldIndex, fieldName, "VkLayerSettingEXT");
        const auto& decoded_value = *data->decoded_value;
        const Decoded_VkLayerSettingEXT& meta_struct = *data;
        FieldInfo memberInfo = { fieldInfo.eventId, structId, 0, 0 };

        FieldToSqlite(statements, memberInfo, 1, "pLayerName", meta_struct.pLayerName, "const char*");
        FieldToSqlite(statements, memberInfo, 2, "pSettingName", meta_struct.pSettingName, "const char*");
        FieldToSqlite(statements, memberInfo, 3, "type", decoded_value.type, "VkLayerSettingTypeEXT");
        FieldToSqlite(statements, memberInfo, 4, "valueCount", decoded_value.valueCount, "uint32_t");

        // TODO: pValues is a void* that points to different types based on the 'type' field
        // For now, we just record the pointer address as an integer in the database
        // The actual data interpretation would require decoding based on VkLayerSettingTypeEXT
        if (decoded_value.pValues)
        {
            RecordField(statements, memberInfo, 5, "pValues", "const void*",
                        reinterpret_cast<uint64_t>(decoded_value.pValues));
        }
        else
        {
            RecordNullMember(statements, memberInfo, 5, "pValues", "const void*");
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, "VkLayerSettingEXT");
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
