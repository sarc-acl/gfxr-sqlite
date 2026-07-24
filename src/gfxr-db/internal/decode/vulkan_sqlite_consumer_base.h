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

#ifndef GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_BASE_H
#define GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_BASE_H

#include "util/defines.h"
#include "decode/annotation_handler.h"
#include "encode/vulkan_handle_wrapper_util.h"
#include "format/platform_types.h"
#include "generated/generated_vulkan_consumer.h"
#include "sqlite_utils.h"
#include "vulkan/vulkan.h"

#include "vulkan_sqlite_consumer_context.h"
#include "vulkan_sqlite_prepared_statements.h"

#include <cstdint>
#include <cstdio>
#include <string>
#include <map>
#include <optional>
#include <string_view>

#include "sqlite3.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)
GFXRECON_BEGIN_NAMESPACE(args)

// Hand-authored args structs for commands gfxreconstruct blacklists from its own Vulkan consumer
// codegen (see external/gfxreconstruct's vulkan_generators/blacklists.json) but that gfxr-sqlite still
// wants to track. These mirror the field lists the codegen produced the last time gfxr-sqlite's
// generated consumer was regenerated before each command was dropped upstream — see the matching
// "TODO: missing from upstream GFXR" declarations in VulkanSqliteConsumerBase below.

struct CmdPushDescriptorSetWithTemplate
{
    format::HandleId commandBuffer;
    format::HandleId descriptorUpdateTemplate;
    format::HandleId layout;
    uint32_t set;
    DescriptorUpdateTemplateDecoder pData;
};

struct CmdPushDescriptorSetWithTemplate2
{
    format::HandleId commandBuffer;
    StructPointerDecoder<Decoded_VkPushDescriptorSetWithTemplateInfo> pPushDescriptorSetWithTemplateInfo;
};

struct BuildAccelerationStructuresKHR
{
    VkResult result;
    format::HandleId device;
    format::HandleId deferredOperation;
    uint32_t infoCount;
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildGeometryInfoKHR> pInfos;
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*> ppBuildRangeInfos;
};

struct CopyAccelerationStructureKHR
{
    VkResult result;
    format::HandleId device;
    format::HandleId deferredOperation;
    StructPointerDecoder<Decoded_VkCopyAccelerationStructureInfoKHR> pInfo;
};

GFXRECON_END_NAMESPACE(args)

class VulkanSqliteConsumerBase : public VulkanConsumer, public AnnotationHandler
{
  public:
    VulkanSqliteConsumerBase(sqlite3* db);

    void Initialize(
        const std::string_view gfxrVersion, const std::string_view vulkanVersion, const std::string_view inputFilepath
    );

    void PostInitialize();

    void TrimFinalFrame();

    void UpdateCommandBufferCommands(const ApiCallInfo& callInfo, format::HandleId commandBuffer);

    void ProcessStateBeginMarker(uint64_t frameNumber) override;

    void ProcessStateEndMarker(uint64_t frameNumber) override;

    void ProcessFrameEndMarker(uint64_t frameNumber) override;

    void ProcessDisplayMessageCommand(const std::string& message) override;

    void ProcessFillMemoryCommand(uint64_t memoryId, uint64_t offset, uint64_t size, const uint8_t* data) override;

    void ProcessResizeWindowCommand(format::HandleId surfaceId, uint32_t width, uint32_t height) override;

    void ProcessResizeWindowCommand2(
        format::HandleId surfaceId, uint32_t width, uint32_t height, uint32_t preTransform
    ) override;

    void ProcessCreateHardwareBufferCommand(
        format::HandleId deviceId,
        format::HandleId memoryId,
        uint64_t bufferId,
        uint32_t format,
        uint32_t width,
        uint32_t height,
        uint32_t stride,
        uint64_t usage,
        uint32_t layers,
        const std::vector<format::HardwareBufferPlaneInfo>& planeInfo
    ) override;

    void ProcessDestroyHardwareBufferCommand(uint64_t bufferId) override;

    void ProcessSetDevicePropertiesCommand(
        format::HandleId physicalDeviceId,
        uint32_t apiVersion,
        uint32_t driverVersion,
        uint32_t vendor_id,
        uint32_t deviceId,
        uint32_t deviceType,
        const uint8_t pipeline_cache_uuid[format::kUuidSize],
        const std::string& deviceName
    ) override;

    void ProcessSetDeviceMemoryPropertiesCommand(
        format::HandleId physicalDeviceId,
        const std::vector<format::DeviceMemoryType>& memoryTypes,
        const std::vector<format::DeviceMemoryHeap>& memoryHeaps
    ) override;

    void ProcessSetOpaqueAddressCommand(
        format::HandleId deviceId, format::HandleId objectId, uint64_t address
    ) override;

    void ProcessSetRayTracingShaderGroupHandlesCommand(
        format::HandleId deviceId, format::HandleId pipelineId, size_t dataSize, const uint8_t* data
    ) override;

    void ProcessSetSwapchainImageStateCommand(
        format::HandleId deviceId,
        format::HandleId swapchainId,
        uint32_t lastPresentedImage,
        const std::vector<format::SwapchainImageStateInfo>& imageState
    ) override;

    void ProcessBeginResourceInitCommand(
        format::HandleId deviceId, uint64_t maxResourceSize, uint64_t maxCopySize
    ) override;

    void ProcessEndResourceInitCommand(format::HandleId deviceId) override;

    void ProcessInitBufferCommand(
        format::HandleId deviceId, format::HandleId bufferId, uint64_t dataSize, const uint8_t* data
    ) override;

    void ProcessInitImageCommand(
        format::HandleId deviceId,
        format::HandleId imageId,
        uint64_t dataSize,
        uint32_t aspect,
        uint32_t layout,
        const std::vector<uint64_t>& levelSizes,
        const uint8_t* data
    ) override;

    // TODO: missing from upstream GFXR (and thus never will be called)
    // This function is here because pData gets the wrong type when generated
    // (https://github.com/android-graphics/sokatoa/issues/1582)
    virtual void Process_vkCmdPushDescriptorSetWithTemplate(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplate& args
    );

    // This function is here because pData gets the wrong type when generated
    // (https://github.com/android-graphics/sokatoa/issues/1582)
    void Process_vkCmdPushDescriptorSetWithTemplateKHR(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplateKHR& args
    ) override;

    // gfxreconstruct's own VulkanConsumer doesn't declare a virtual for this command (blacklisted
    // upstream), so this provides the virtual slot for VulkanSqliteConsumer's generated override
    // (its normal auto-generated logging body) to hook into.
    virtual void Process_vkCmdPushDescriptorSetWithTemplate2(
        const ApiCallInfo& callInfo, args::CmdPushDescriptorSetWithTemplate2& args
    );

    // gfxreconstruct's own VulkanConsumer doesn't declare a virtual for this command (blacklisted
    // upstream), so this provides the virtual slot for VulkanSqliteConsumer's generated override
    // (its normal auto-generated logging body) to hook into.
    virtual void Process_vkBuildAccelerationStructuresKHR(
        const ApiCallInfo& callInfo, args::BuildAccelerationStructuresKHR& args
    );

    // gfxreconstruct's own VulkanConsumer doesn't declare a virtual for this command (blacklisted
    // upstream), so this provides the virtual slot for VulkanSqliteConsumer's generated override
    // (its normal auto-generated logging body) to hook into.
    virtual void Process_vkCopyAccelerationStructureKHR(
        const ApiCallInfo& callInfo, args::CopyAccelerationStructureKHR& args
    );

    // This function is here because pData gets the wrong type when generated
    // (https://github.com/android-graphics/sokatoa/issues/1582)
    void Process_vkUpdateDescriptorSetWithTemplate(
        const ApiCallInfo& callInfo, args::UpdateDescriptorSetWithTemplate& args
    ) override;

    // This function is here because pData gets the wrong type when generated
    // (https://github.com/android-graphics/sokatoa/issues/1582)
    void Process_vkUpdateDescriptorSetWithTemplateKHR(
        const ApiCallInfo& callInfo, args::UpdateDescriptorSetWithTemplateKHR& args
    ) override;

    void Process_vkCmdBuildAccelerationStructuresIndirectKHR(
        const ApiCallInfo& callInfo, args::CmdBuildAccelerationStructuresIndirectKHR& args
    ) override;

    /// @brief Convert annotations, which are simple {type:enum, key:string, value:string} objects.
    void ProcessAnnotation(
        uint64_t blockIndex, format::AnnotationType type, const std::string& label, const std::string& data
    ) override;

  protected:
    VulkanSqliteConsumerContext context;
    VulkanSqlitePreparedStatements statements;

    void FinalizeFrame(uint64_t frameNumber);
    void TrimFirstFrame();

    void LogUnsupportedPNext(PNextNode* pNext);
    void LogUnsupportedPNext(VkStructureType type);

    void LogUnsupportedDynamicState(VkDynamicState state);
    void LogUnsupportedDynamicState(const char* commandName);

    template <class T>
    inline bool HasData(const gfxrecon::decode::StructPointerDecoder<T>* structPtr)
    {
        return (structPtr != nullptr && !structPtr->IsNull() && structPtr->HasData());
    }
    template <class T>
    inline std::pair<bool, const T*> GetMetaStructPointer(const gfxrecon::decode::StructPointerDecoder<T>* structPtr)
    {
        if (!HasData(structPtr))
        {
            return { false, nullptr };
        }
        if (structPtr->IsArray())
        {
            return { false, nullptr };
        }
        auto decodedStruct = structPtr->GetMetaStructPointer();
        if (!decodedStruct)
        {
            return { false, nullptr };
        }
        return { true, decodedStruct };
    }

    template <class T>
    using MetaStructArray = std::tuple<bool, const T*, uint64_t>;

    template <class T>
    inline MetaStructArray<T> GetMetaStructArray(const gfxrecon::decode::StructPointerDecoder<T>* structPtr)
    {
        if (!HasData(structPtr))
        {
            return MetaStructArray<T>(false, (T*)nullptr, 0);
        }
        auto decodedStruct = structPtr->GetMetaStructPointer();
        if (!decodedStruct)
        {
            return MetaStructArray<T>(false, (T*)nullptr, 0);
        }
        if (!structPtr->IsArray())
        {
            return MetaStructArray<T>(true, (T*)decodedStruct, 1);
        }
        return MetaStructArray<T>(true, (T*)decodedStruct, structPtr->GetLength());
    }

    // Helper for Array2D case (StructPointerDecoder<T*> where T is the decoded struct type)
    // This version extracts a specific inner array by index from the 2D array structure
    template <class T>
    inline MetaStructArray<T> GetMetaStructArray2D(
        const gfxrecon::decode::StructPointerDecoder<T*>* structPtr, size_t index
    )
    {
        if (!HasData(structPtr))
        {
            return std::make_tuple(false, (const T*)nullptr, uint64_t(0));
        }
        if (!structPtr->IsArray2D())
        {
            return std::make_tuple(false, (const T*)nullptr, uint64_t(0));
        }
        auto decodedStruct = structPtr->GetMetaStructPointer();
        if (!decodedStruct)
        {
            return std::make_tuple(false, (const T*)nullptr, uint64_t(0));
        }
        // For Array2D, GetMetaStructPointer() returns T** (pointer to array of pointers).
        // Extract the specific inner array at the given index.
        if (index < structPtr->GetLength() && decodedStruct[index] != nullptr)
        {
            return std::make_tuple(true, decodedStruct[index], uint64_t(structPtr->GetInnerLength(index)));
        }
        return std::make_tuple(false, (const T*)nullptr, uint64_t(0));
    }

    template <class T>
    inline bool HasData(const gfxrecon::decode::PointerDecoder<T>* dataPtr)
    {
        return (dataPtr != nullptr && !dataPtr->IsNull() && dataPtr->HasData());
    }

    inline bool HasData(const gfxrecon::decode::StringArrayDecoder* dataPtr)
    {
        return (dataPtr != nullptr && !dataPtr->IsNull() && dataPtr->HasData());
    }

    template <class T>
    using PointerArray = std::tuple<bool, T*, uint64_t>;

    template <class T>
    inline PointerArray<T> GetPointerArray(const gfxrecon::decode::PointerDecoder<T>* dataPtr)
    {
        if (!HasData(dataPtr))
        {
            return PointerArray<T>(false, (T*)nullptr, 0);
        }
        auto decodedData = dataPtr->GetPointer();
        if (!decodedData)
        {
            return PointerArray<T>(false, (T*)nullptr, 0);
        }
        if (!dataPtr->IsArray())
        {
            return PointerArray<T>(true, (T*)decodedData, 1);
        }
        return PointerArray<T>(true, (T*)decodedData, dataPtr->GetLength());
    }

    inline PointerArray<char*> GetPointerArray(const gfxrecon::decode::StringArrayDecoder* dataPtr)
    {
        if (!HasData(dataPtr))
        {
            return PointerArray<char*>(false, (char**)nullptr, 0);
        }
        auto decodedData = dataPtr->GetPointer();
        if (!decodedData)
        {
            return PointerArray<char*>(false, (char**)nullptr, 0);
        }
        if (!dataPtr->IsArray())
        {
            return PointerArray<char*>(true, (char**)decodedData, 1);
        }
        return PointerArray<char*>(true, (char**)decodedData, dataPtr->GetLength());
    }

    template <class T>
    inline bool HasData(const gfxrecon::decode::HandlePointerDecoder<T>* handlePtr)
    {
        return (handlePtr != nullptr && !handlePtr->IsNull() && handlePtr->HasData());
    }
    template <class T>
    inline std::pair<bool, gfxrecon::format::HandleId> GetHandle(
        const gfxrecon::decode::HandlePointerDecoder<T>* handlePtr
    )
    {
        if (!HasData(handlePtr))
        {
            return { false, 0 };
        }
        if (handlePtr->IsArray())
        {
            return { false, 0 };
        }
        auto decodedHandle = handlePtr->GetPointer();
        if (!decodedHandle)
        {
            return { false, 0 };
        }
        return { true, *decodedHandle };
    }

    using HandleArray = std::tuple<bool, gfxrecon::format::HandleId*, uint64_t>;

    template <class T>
    inline HandleArray GetHandleArray(const gfxrecon::decode::HandlePointerDecoder<T>* handlePtr)
    {
        if (!HasData(handlePtr))
        {
            return HandleArray(false, (gfxrecon::format::HandleId*)nullptr, 0);
        }
        auto decodedHandle = handlePtr->GetPointer();
        if (!decodedHandle)
        {
            return HandleArray(false, (gfxrecon::format::HandleId*)nullptr, 0);
        }
        if (!handlePtr->IsArray())
        {
            return HandleArray(true, (gfxrecon::format::HandleId*)decodedHandle, 1);
        }
        return HandleArray(true, (gfxrecon::format::HandleId*)decodedHandle, handlePtr->GetLength());
    }

    void BuildDebugLabelsTables();
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_VULKAN_SQLITE_CONSUMER_BASE_H
