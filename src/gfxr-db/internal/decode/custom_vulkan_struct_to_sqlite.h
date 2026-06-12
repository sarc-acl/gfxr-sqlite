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

#ifndef GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_SQLITE_H
#define GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_SQLITE_H

#include "util/defines.h"
#include "vulkan/vulkan.h"

#include "decode/field_info.h"
#include "decode/vulkan_sqlite_consumer_context.h"

#include "decode/custom_vulkan_struct_decoders.h"
#include "generated/generated_vulkan_enum_to_sqlite.h"
#include "generated/generated_vulkan_struct_decoders.h"
#include "generated/generated_vulkan_struct_to_sqlite.h"

#include "sqlite3.h"
#include "sqlite_utils.h"
#include "decode/vulkan_sqlite_prepared_statements.h"

#include <string_view>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

class DescriptorUpdateTemplateDecoder;

// clang-format off
[[nodiscard("Returns the assigned Struct Id for the array recorded into the database.")]]
inline uint64_t RecordStruct(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    std::string_view fieldType
)
// clang-format on
{
    // create the struct entry
    auto structId = statements.InsertStruct(fieldType);

    // record the struct id into the proper field info
    RecordField(statements, fieldInfo, fieldIndex, fieldName, "STRUCT", structId);

    return structId;
}

// clang-format off
[[nodiscard("Returns the assigned Array Id for the array recorded into the database.")]]
inline uint64_t RecordArray(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    std::string_view fieldType
)
// clang-format on
{
    // create the array entry
    auto arrayId = statements.InsertArray(fieldType);

    // record the array id into the proper field info
    RecordField(statements, fieldInfo, fieldIndex, fieldName, "ARRAY", arrayId);

    return arrayId;
}

inline void RecordNullMember(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    std::string_view typeName
)
{
    RecordField<std::string_view>(statements, fieldInfo, fieldIndex, fieldName, typeName, "null");
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    short data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    int data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    long data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    long long data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    unsigned short data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    unsigned int data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    unsigned long data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    unsigned long long data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

/// Convert floats to Sqlite entries
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    float data,
    std::string_view typeName
);

/// @note This is unused dead code currently (try placing a breakpoint on it).
/// ported from the custom_struct_to_json file, note above originated from matching function signature
inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    double data,
    std::string_view typeName
)
{
    RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

inline void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    std::string_view data,
    std::string_view typeName
)
{
    RecordField<std::string_view>(statements, fieldInfo, fieldIndex, fieldName, typeName, data);
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StringArrayDecoder* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StringDecoder* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const WStringDecoder* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkClearValue* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkClearColorValue* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    int discriminant,
    const Decoded_VkDeviceOrHostAddressConstKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDeviceOrHostAddressConstKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    int discriminant,
    const Decoded_VkDeviceOrHostAddressKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDeviceOrHostAddressKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    VkPipelineExecutableStatisticFormatKHR discriminant,
    const Decoded_VkPipelineExecutableStatisticValueKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPipelineExecutableStatisticKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_SECURITY_ATTRIBUTES* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkAccelerationStructureGeometryKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkAccelerationStructureMotionInstanceNV* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkDescriptorImageInfo* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkWriteDescriptorSet* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPerformanceValueINTEL* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkShaderModuleCreateInfo* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPipelineCacheCreateInfo* data,
    std::string_view typeName
);

template <typename T>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const T* data,
    size_t num_elements,
    std::string_view typeName
)
{
    if (data)
    {
        const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
        for (size_t i = 0; i < num_elements; ++i)
        {
            FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
            FieldToSqlite(statements, memberInfo, i, fieldName, data[i], typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const PointerDecoder<DecodedType, OutputDecodedType>* data,
    std::string_view typeName
)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length = data->GetLength();

        if (data->IsArray())
        {
            FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, decoded_value, length, typeName);
        }
        else if (length == 1)
        {
            RecordField(statements, fieldInfo, fieldIndex, fieldName, typeName, *decoded_value);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

// Reference to pointer version wraps pointer to pointer version above.
template <typename DecodedType, typename OutputDecodedType = DecodedType>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const PointerDecoder<DecodedType, OutputDecodedType>& data,
    std::string_view typeName
)
{
    FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, &data, typeName);
}

template <>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const PointerDecoder<uint64_t, uint64_t>& data,
    std::string_view typeName
);

template <typename DecodedType>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const StructPointerDecoder<DecodedType>* data,
    std::string_view typeName
)
{
    if (data)
    {
        const auto meta_struct = data->GetMetaStructPointer();
        const auto length = data->GetLength();

        if (data->IsArray())
        {
            const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
            for (size_t i = 0; i < length; ++i)
            {
                FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
                FieldToSqlite(statements, memberInfo, i, fieldName, &meta_struct[i], typeName);
            }
        }
        else if (length == 1)
        {
            FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, meta_struct, typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

template <typename DecodedType>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    StructPointerDecoder<DecodedType*>* data,
    std::string_view typeName
)
{
    if (data)
    {
        const auto meta_struct = data->GetMetaStructPointer();
        const auto length = data->GetLength();
        if (data->IsArray())
        {
            const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
            for (size_t i = 0; i < length; ++i)
            {
                FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
                FieldToSqlite(statements, memberInfo, i, fieldName, meta_struct[i], typeName);
            }
        }
        else if (length == 1)
        {
            FieldToSqlite(statements, fieldInfo, fieldIndex, fieldName, *meta_struct, typeName);
        }
    }
    else
    {
        RecordNullMember(statements, fieldInfo, fieldIndex, fieldName, typeName);
    }
}

template <typename THandle>
void HandleToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const HandlePointerDecoder<THandle>* data,
    std::string_view typeName
)
{
    if (data && data->GetPointer())
    {
        const auto decoded_value = data->GetPointer();
        const auto length = data->GetLength();

        if (data->IsArray())
        {
            const auto currentArrayId = RecordArray(statements, fieldInfo, fieldIndex, fieldName, typeName);
            for (size_t i = 0; i < length; ++i)
            {
                FieldInfo memberInfo = { fieldInfo.eventId, 0, currentArrayId, i };
                HandleToSqlite(statements, memberInfo, i, fieldName, decoded_value[i], typeName);
            }
        }
        else if (length == 1)
        {
            HandleToSqlite(statements, fieldInfo, fieldIndex, fieldName, *decoded_value, typeName);
        }
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
    const format::HandleId data,
    std::string_view typeName
);

void HandleToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const format::HandleId* data,
    size_t num_elements,
    std::string_view typeName
);

/// @brief Thunk to HandleToSqlite for manual conversion functions which forget to
/// use that for the array form.
template <typename THandle>
void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const HandlePointerDecoder<THandle>* data,
    std::string_view typeName
)
{
    HandleToSqlite(statements, fieldInfo, fieldIndex, fieldName, data, typeName);
}

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const DescriptorUpdateTemplateDecoder* pData,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkPushDescriptorSetWithTemplateInfoKHR* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkIndirectCommandsLayoutTokenEXT* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkMemoryToImageCopy* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkCopyMemoryToImageInfo* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkImageToMemoryCopy* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkCopyImageToMemoryInfo* data,
    std::string_view typeName
);

void FieldToSqlite(
    VulkanSqlitePreparedStatements& statements,
    const FieldInfo& fieldInfo,
    size_t fieldIndex,
    std::string_view fieldName,
    const Decoded_VkLayerSettingEXT* data,
    std::string_view typeName
);

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_CUSTOM_VULKAN_STRUCT_TO_SQLITE_H
