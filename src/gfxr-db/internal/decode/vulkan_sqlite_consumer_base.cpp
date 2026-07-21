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

#include "vulkan_sqlite_consumer_base.h"
#include "vulkan_sqlite_consumer_base_tables.h"

#include "sqlite_utils.h"
#include "field_info.h"
#include "api_event_types.h"

#include "util/platform.h"
#include "util/file_path.h"

#include "decode/consumer_utils.h"
#include "decode/custom_vulkan_struct_to_sqlite.h"
#include "generated/generated_vulkan_enum_to_sqlite.h"
#include "generated/generated_vulkan_enum_to_string.h"

#include <string>
#include <string_view>
#include <sstream>
#include <cstdint>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)
using namespace util::platform;

VulkanSqliteConsumerBase::VulkanSqliteConsumerBase(sqlite3* db) : context(db), statements(db)
{
    statements.context = &context;
    CreateBaseTables(db);

    statements.CreateBasePreparedStatements();
}

void VulkanSqliteConsumerBase::UpdateCommandBufferCommands(const ApiCallInfo& call_info, format::HandleId commandBuffer)
{
    auto commandBufferRecordingIdIter = context.commandBufferHandleToRecordingId.find(ToInt64(commandBuffer));
    if (commandBufferRecordingIdIter == context.commandBufferHandleToRecordingId.end())
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Failed to update command buffer commands, failed to find command buffer recording for "
            "command buffer %" PRIu64,
            commandBuffer
        );
        return;
    }

    statements.InsertCommandBufferCommand(commandBufferRecordingIdIter->second, this->block_index_);
}

void VulkanSqliteConsumerBase::Initialize(
    const std::string_view gfxrVersion, const std::string_view vulkanVersion, const std::string_view inputFilepath
)
{
    ExecSQL(context.db, "BEGIN TRANSACTION");

    std::ostringstream metaDataSql;
    // clang-format off
    metaDataSql << "INSERT INTO metaData VALUES"
                    << " ('source path', '" << sqlEscape(inputFilepath) << "'),"
                    << " ('gfxr version', '" << sqlEscape(gfxrVersion) << "'),"
                    << " ('vulkan version', '" << sqlEscape(vulkanVersion) << "');";
    // clang-format on
    ExecSQL(context.db, metaDataSql.str().c_str());

    std::ostringstream apiTypesSql;
    // clang-format off
    apiTypesSql << "INSERT INTO apiEventTypes VALUES"
                    << " (" << APIEventTypes::META_COMMAND << ", 'META_COMMAND'),"
                    << " (" << APIEventTypes::VULKAN_API << ", 'VULKAN_API');";
    // clang-format on
    ExecSQL(context.db, apiTypesSql.str().c_str());

    // create the first frame (which may be deleted if there is a begin marker event at start of file)
    context.currentFrame = 1;
    statements.InsertFrame(1, 1);
}

void VulkanSqliteConsumerBase::BuildDebugLabelsTables()
{
    ExecSQL(
        context.db,
        "INSERT INTO queueDebugLabels"
        "    SELECT apiEvents.id, debugLabels.id, debugLabels.queueId"
        "    FROM debugLabels"
        "    INNER JOIN apiEvents ON ("
        "        debugLabels.beginApiEventId <= apiEvents.id"
        "        AND (debugLabels.endApiEventId >= apiEvents.id"
        "             OR debugLabels.endApiEventId IS NULL)"
        "        AND debugLabels.queueId IS NOT NULL)"
        "    INNER JOIN apiEventArguments ON ("
        "        apiEventArguments.apiEventId = apiEvents.id"
        "        AND apiEventArguments.name = 'queue')"
        "    ORDER BY debugLabels.endApiEventId - debugLabels.beginApiEventId"
    );
}

void VulkanSqliteConsumerBase::PostInitialize()
{
    // build lookup tables for debug label support
    BuildDebugLabelsTables();

    // finish the transaction started in Initialize
    ExecSQL(context.db, "END TRANSACTION");
}

void VulkanSqliteConsumerBase::TrimFirstFrame()
{
    ExecSQL(context.db, "UPDATE apiEvents SET frameId = NULL WHERE frameId = 1");
    ExecSQL(context.db, "DELETE FROM frames WHERE id = 1");
}

void VulkanSqliteConsumerBase::TrimFinalFrame()
{
    ExecSQL(context.db, "UPDATE apiEvents SET frameId = NULL WHERE frameId = (SELECT MAX(id) from frames)");
    ExecSQL(context.db, "DELETE FROM frames WHERE id = (SELECT MAX(id) from frames)");
}

void VulkanSqliteConsumerBase::LogUnsupportedPNext(PNextNode* pNext)
{
    while (pNext != nullptr)
    {
        const auto* header = reinterpret_cast<const VulkanMetaStructHeader*>(pNext->GetMetaStructPointer());
        LogUnsupportedPNext(*header->sType);
        pNext = header->pNext;
    }
}

void VulkanSqliteConsumerBase::LogUnsupportedPNext(VkStructureType type)
{
    auto [warningIter, inserted] = context.pNextWarnings.insert(type);
    if (inserted)
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Unsupported pNext structure VkStructureType %d (%s)",
            type,
            gfxrecon::util::ToString(type, gfxrecon::util::kToString_Unformatted, 0, 0).c_str()
        );
    }
}

void VulkanSqliteConsumerBase::ProcessStateBeginMarker(uint64_t frame_number)
{
    const auto functionId = statements.InsertFunctionName("StateBeginMarker");
    statements.InsertMetaApiEvent(this->block_index_, functionId, frame_number);

    // this is the beginning of initial state data, this is not part of the frame that the frame
    // number indicates but represents state of vulkan (optimized) prior to the beginning of the
    // initial frame, so call it frame 1 which will get updated to "NULL" from TrimFirstFrame
    statements.InsertAPIEventArgument(this->block_index_, 1, "frame_number", "uint64_t", "1");
}

void VulkanSqliteConsumerBase::FinalizeFrame(uint64_t frame_number)
{
    std::ostringstream updateFrameSql;
    updateFrameSql << "UPDATE frames SET endApiEventId = " << this->block_index_
                   << " WHERE (frames.id = " << frame_number << ");";
    ExecSQL(context.db, updateFrameSql.str().c_str());

    if (frame_number == 1)
    {
        // update the first frame with the actual beginning apiEvents.id
        // the apiEvents.id may be a value greater than 1 due to some meta commands
        // not currently being parsed by sqlite consumer (ex. SetEnvironmentVariablesCommand)
        // not an issue for trimmed captures due to the presence of a StateBeginMarker
        std::ostringstream updateFrame1Sql;
        updateFrame1Sql << "UPDATE frames SET beginApiEventId = (select min(apiEvents.id) from apiEvents)"
                           " WHERE (frames.id = 1);";
        ExecSQL(context.db, updateFrame1Sql.str().c_str());
    }

    if (context.currentFrame == frame_number)
    {
        context.currentFrame = frame_number + 1;
        statements.InsertFrame(context.currentFrame, this->block_index_);
    }
    else
    {
        GFXRECON_SQLITE_LOG_WARNING(
            "Finalized frame %" PRIu64 " not matching current frame: %" PRIu64, frame_number, context.currentFrame
        );
    }
}

void VulkanSqliteConsumerBase::ProcessStateEndMarker(uint64_t frame_number)
{
    const auto functionId = statements.InsertFunctionName("StateEndMarker");
    statements.InsertMetaApiEvent(this->block_index_, functionId, frame_number);

    statements.InsertAPIEventArgument(this->block_index_, 1, "frame_number", "uint64_t", std::to_string(frame_number));

    if (context.currentFrame == 1 && frame_number != 1)
    {
        // Finalize the initial state frame so it has a valid event range
        ExecSQL(
            context.db,
            ("UPDATE frames SET endApiEventId = " + std::to_string(this->block_index_) + " WHERE id = 1;").c_str()
        );
        ExecSQL(context.db, "UPDATE frames SET beginApiEventId = (SELECT MIN(id) FROM apiEvents) WHERE id = 1;");
    }
    if (context.currentFrame != frame_number)
    {
        statements.InsertFrame(frame_number, this->block_index_);
    }
    context.currentFrame = frame_number;
}

void VulkanSqliteConsumerBase::ProcessFrameEndMarker(uint64_t frame_number)
{
    const auto functionId = statements.InsertFunctionName("FrameEndMarker");
    statements.InsertMetaApiEvent(this->block_index_, functionId, frame_number);

    statements.InsertAPIEventArgument(this->block_index_, 1, "frame_number", "uint64_t", std::to_string(frame_number));

    FinalizeFrame(frame_number);
}

void VulkanSqliteConsumerBase::ProcessDisplayMessageCommand(const std::string& message)
{
    const auto functionId = statements.InsertFunctionName("DisplayMessageCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "frame_number", "TEXT", message);

    statements.InsertDisplayMessage(context.currentFrame, message);
}

void VulkanSqliteConsumerBase::ProcessFillMemoryCommand(
    uint64_t memoryId, uint64_t offset, uint64_t size, const uint8_t* data
)
{
    const auto functionId = statements.InsertFunctionName("FillMemoryCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "memory", "HANDLE", std::to_string(memoryId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "offset", "uint64_t", std::to_string(offset));
    statements.InsertAPIEventArgument(this->block_index_, 3, "size", "uint32_t", std::to_string(size));

    // TODO update this to new memory structures
    auto& statement = statements.memoryInsertStatement;
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(memoryId)));
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(offset)));
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_bind_int64(statement, 3, static_cast<sqlite_int64>(size)));
    GFXRECON_SQLITE_CHECK(
        context.db, sqlite3_bind_int64(statement, 4, static_cast<sqlite_int64>(context.currentFrame))
    );
    GFXRECON_SQLITE_CHECK_DONE(context.db, sqlite3_step(statement));

    // TODO figure out how to write out the binary data blob
    /*
    if (json_options_.dump_binaries)
    {
        std::string filename = GenerateFilename("fill_memory.bin");
        std::string basename = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
        std::string filepath = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
        if (WriteBinaryFile(filepath, size, data))
        {
            FieldToJson(jdata["data"], basename, json_options_);
        }
        else
        {
            FieldToJson(jdata["data"], "Unable to write file", json_options_);
        }
    }
    else
    {
        FieldToJson(jdata["data"], "[Binary data]", json_options_);
    } });
    */
}

void VulkanSqliteConsumerBase::ProcessResizeWindowCommand(format::HandleId surfaceId, uint32_t width, uint32_t height)
{
    const auto functionId = statements.InsertFunctionName("ResizeWindowCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "surface", "HANDLE", std::to_string(surfaceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "width", "uint32_t", std::to_string(width));
    statements.InsertAPIEventArgument(this->block_index_, 3, "height", "uint32_t", std::to_string(height));
}

void VulkanSqliteConsumerBase::ProcessResizeWindowCommand2(
    format::HandleId surfaceId, uint32_t width, uint32_t height, uint32_t preTransform
)
{
    const auto functionId = statements.InsertFunctionName("ResizeWindowCommand2");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "surface", "HANDLE", std::to_string(surfaceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "width", "uint32_t", std::to_string(width));
    statements.InsertAPIEventArgument(this->block_index_, 3, "height", "uint32_t", std::to_string(height));
    statements.InsertAPIEventArgument(this->block_index_, 4, "pre-transform", "uint32_t", std::to_string(preTransform));
}

void VulkanSqliteConsumerBase::ProcessCreateHardwareBufferCommand(
    format::HandleId deviceId,
    format::HandleId memoryId,
    uint64_t bufferId,
    uint32_t format,
    uint32_t width,
    uint32_t height,
    uint32_t stride,
    uint64_t usage,
    uint32_t layers,
    const std::vector<format::HardwareBufferPlaneInfo>& plane_info
)
{
    const auto functionId = statements.InsertFunctionName("CreateHardwareBuffer");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "memory", "HANDLE", std::to_string(memoryId));
    statements.InsertAPIEventArgument(this->block_index_, 3, "buffer pointer", "uint64_t", std::to_string(bufferId));
    statements.InsertAPIEventArgument(this->block_index_, 4, "format", "uint32_t", std::to_string(format));
    statements.InsertAPIEventArgument(this->block_index_, 5, "width", "uint32_t", std::to_string(width));
    statements.InsertAPIEventArgument(this->block_index_, 6, "height", "uint32_t", std::to_string(height));
    statements.InsertAPIEventArgument(this->block_index_, 7, "stride", "uint32_t", std::to_string(stride));
    statements.InsertAPIEventArgument(this->block_index_, 8, "usage", "uint64_t", std::to_string(usage));
    statements.InsertAPIEventArgument(this->block_index_, 9, "layers", "uint32_t", std::to_string(layers));

    // TODO possibly do something with the plane_info parameter, not originally captured in the export json consumer
}

void VulkanSqliteConsumerBase::ProcessDestroyHardwareBufferCommand(uint64_t bufferId)
{
    const auto functionId = statements.InsertFunctionName("DestroyHardwareBuffer");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "buffer id", "uint64_t", std::to_string(bufferId));
}

void VulkanSqliteConsumerBase::ProcessSetDevicePropertiesCommand(
    format::HandleId physicalDeviceId,
    uint32_t apiVersion,
    uint32_t driver_version,
    uint32_t vendor_id,
    uint32_t deviceId,
    uint32_t device_type,
    const uint8_t pipeline_cache_uuid[format::kUuidSize],
    const std::string& device_name
)
{
    const auto functionId = statements.InsertFunctionName("DevicePropertiesCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(
        this->block_index_, 1, "physical device", "HANDLE", std::to_string(physicalDeviceId)
    );
    statements.InsertAPIEventArgument(this->block_index_, 2, "api version", "uint32_t", std::to_string(apiVersion));
    statements.InsertAPIEventArgument(
        this->block_index_, 3, "driver version", "uint32_t", std::to_string(driver_version)
    );
    statements.InsertAPIEventArgument(this->block_index_, 4, "vendor id", "uint32_t", std::to_string(vendor_id));
    statements.InsertAPIEventArgument(this->block_index_, 5, "device id", "uint32_t", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 6, "device type", "uint32_t", std::to_string(device_type));
    statements.InsertAPIEventArgument(
        this->block_index_, 7, "pipeline cache uuid", "UUID", UUIDToString(format::kUuidSize, pipeline_cache_uuid)
    );
    statements.InsertAPIEventArgument(this->block_index_, 8, "device name", "TEXT", device_name);
}

void VulkanSqliteConsumerBase::ProcessSetDeviceMemoryPropertiesCommand(
    format::HandleId physicalDeviceId,
    const std::vector<format::DeviceMemoryType>& memory_types,
    const std::vector<format::DeviceMemoryHeap>& memory_heaps
)
{
    const auto functionId = statements.InsertFunctionName("SetDeviceMemoryPropertiesCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(
        this->block_index_, 1, "physical device", "HANDLE", std::to_string(physicalDeviceId)
    );

    // TODO possibly handle the memory_types and memory_heaps parameters, not originally captured in the export json
    // consumer
}

void VulkanSqliteConsumerBase::ProcessSetOpaqueAddressCommand(
    format::HandleId deviceId, format::HandleId objectId, uint64_t address
)
{
    const auto functionId = statements.InsertFunctionName("SetOpaqueAddressCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "object", "HANDLE", std::to_string(objectId));
    statements.InsertAPIEventArgument(this->block_index_, 3, "address", "uint64_t", std::to_string(address));
}

void VulkanSqliteConsumerBase::ProcessSetRayTracingShaderGroupHandlesCommand(
    format::HandleId deviceId, format::HandleId pipelineId, size_t dataSize, const uint8_t* data
)
{
    const auto functionId = statements.InsertFunctionName("SetRayTracingShaderGroupHandlesCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "pipeline", "HANDLE", std::to_string(pipelineId));
    statements.InsertAPIEventArgument(this->block_index_, 3, "data size", "size_t", std::to_string(dataSize));

    // TODO handle the data argument, need to determine if we should save it to file or attempt to store
    // it in the database as a blob somewhere
    /*
    if (json_options_.dump_binaries)
    {
        std::string filename = GenerateFilename("set_raytracing_shader_group_handle.bin");
        std::string basename = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
        std::string filepath = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
        if (WriteBinaryFile(filepath, dataSize, data))
        {
            FieldToJson(jdata["data"], basename, json_options_);
        }
        else
        {
            FieldToJson(jdata["data"], "Unable to write file", json_options_);
        }
    }
    else
    {
        FieldToJson(jdata["data"], "[Binary data]", json_options_);
    } });
    */
}

void VulkanSqliteConsumerBase::ProcessSetSwapchainImageStateCommand(
    format::HandleId deviceId,
    format::HandleId swapchainId,
    uint32_t last_presented_image,
    const std::vector<format::SwapchainImageStateInfo>& image_state
)
{
    const auto functionId = statements.InsertFunctionName("SetSwapchainImageStateCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "swapchain", "HANDLE", std::to_string(swapchainId));
    statements.InsertAPIEventArgument(
        this->block_index_, 3, "last presented image", "uint32_t", std::to_string(last_presented_image)
    );

    // TODO possibly handle the image_state parameter, originally not handled by the export json consumer (exported
    // 'not available')
}

void VulkanSqliteConsumerBase::ProcessBeginResourceInitCommand(
    format::HandleId deviceId, uint64_t max_resource_size, uint64_t max_copy_size
)
{
    const auto functionId = statements.InsertFunctionName("BeginResourceInitCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(
        this->block_index_, 2, "max resource size", "uint64_t", std::to_string(max_resource_size)
    );
    statements.InsertAPIEventArgument(
        this->block_index_, 3, "max copy size", "uint64_t", std::to_string(max_copy_size)
    );
}

void VulkanSqliteConsumerBase::ProcessEndResourceInitCommand(format::HandleId deviceId)
{
    const auto functionId = statements.InsertFunctionName("EndResourceInitCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
}

void VulkanSqliteConsumerBase::ProcessInitBufferCommand(
    format::HandleId deviceId, format::HandleId bufferId, uint64_t dataSize, const uint8_t* data
)
{
    const auto functionId = statements.InsertFunctionName("InitBufferCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "buffer", "HANDLE", std::to_string(bufferId));
    statements.InsertAPIEventArgument(this->block_index_, 3, "data size", "uint64_t", std::to_string(dataSize));

    // TODO handle the data argument, need to determine if we should save it to file or attempt to store
    // it in the database as a blob somewhere
    /*
    if (json_options_.dump_binaries)
    {
        std::string filename = GenerateFilename("init_buffer.bin");
        std::string basename = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
        std::string filepath = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
        if (WriteBinaryFile(filepath, dataSize, data))
        {
            FieldToJson(jdata["data"], basename, json_options_);
        }
        else
        {
            FieldToJson(jdata["data"], "Unable to write file", json_options_);
        }
    }
    else
    {
        FieldToJson(jdata["data"], "[Binary data]", json_options_);
    } });
    */
}

void VulkanSqliteConsumerBase::ProcessInitImageCommand(
    format::HandleId deviceId,
    format::HandleId imageId,
    uint64_t dataSize,
    uint32_t aspect,
    uint32_t layout,
    const std::vector<uint64_t>& level_sizes,
    const uint8_t* data
)
{
    const auto functionId = statements.InsertFunctionName("InitImageCommand");
    statements.InsertMetaApiEvent(this->block_index_, functionId, context.currentFrame);

    statements.InsertAPIEventArgument(this->block_index_, 1, "device", "HANDLE", std::to_string(deviceId));
    statements.InsertAPIEventArgument(this->block_index_, 2, "image", "HANDLE", std::to_string(imageId));
    statements.InsertAPIEventArgument(this->block_index_, 3, "data size", "uint64_t", std::to_string(dataSize));
    statements.InsertAPIEventArgument(this->block_index_, 4, "aspect", "uint32_t", std::to_string(aspect));
    statements.InsertAPIEventArgument(this->block_index_, 5, "layout", "uint32_t", std::to_string(layout));

    // TODO possibly handle the level_sizes parameter, originally not handled by the export json consumer (exported
    // 'not available')

    // TODO handle the data argument, need to determine if we should save it to file or attempt to store
    // it in the database as a blob somewhere
    /*
    if (json_options_.dump_binaries)
    {
        std::string filename = GenerateFilename("init_image.bin");
        std::string basename = gfxrecon::util::filepath::Join(json_options_.data_sub_dir, filename);
        std::string filepath = gfxrecon::util::filepath::Join(json_options_.root_dir, basename);
        if (WriteBinaryFile(filepath, dataSize, data))
        {
            FieldToJson(jdata["data"], basename, json_options_);
        }
        else
        {
            FieldToJson(jdata["data"], "Unable to write file", json_options_);
        }
    }
    else
    {
        FieldToJson(jdata["data"], "[Binary data]", json_options_);
    } });
    */
}

void VulkanSqliteConsumerBase::Process_vkCmdBuildAccelerationStructuresIndirectKHR(
    const ApiCallInfo& call_info,
    args::CmdBuildAccelerationStructuresIndirectKHR& args
)
{
    FieldInfo fieldInfo = { this->block_index_, 0, 0, 0 };
    const auto functionId = statements.InsertFunctionName("vkCmdBuildAccelerationStructureIndirectKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    statements.InsertApiEventReturns(this->block_index_, "void", "void");

    RecordField(statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(statements, fieldInfo, 2, "infoCount", "uint32_t", args.infoCount);
    FieldToSqlite(statements, fieldInfo, 3, "pInfos", &args.pInfos, " VkAccelerationStructureBuildGeometryInfoKHR");
    FieldToSqlite(statements, fieldInfo, 4, "pIndirectDeviceAddresses", &args.pIndirectDeviceAddresses, "VkDeviceAddress");
    FieldToSqlite(statements, fieldInfo, 5, "pIndirectStrides", &args.pIndirectStrides, "uint32_t");
    // TODO need to handle ppMaxPrimitiveCounts manually due to non-const --> const conversion not allowed
    // when retriving the internal pointer
    // FieldToSqlite(context, fieldInfo, 6, "ppMaxPrimitiveCounts", &args.ppMaxPrimitiveCounts, "uint32_t*");
}

void VulkanSqliteConsumerBase::ProcessAnnotation(
    uint64_t blockIndex, format::AnnotationType type, const std::string& label, const std::string& data
)
{
    const auto functionId = statements.InsertFunctionName("Annotation");
    statements.InsertMetaApiEvent(blockIndex, functionId, context.currentFrame);

    auto annotationId = ++context.currentAnnotationId;
    auto typeString = AnnotationTypeToString(type);

    auto& statement = statements.annotationInsertStatement;
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_reset(statement));
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_bind_int64(statement, 1, static_cast<sqlite_int64>(annotationId)));
    GFXRECON_SQLITE_CHECK(context.db, sqlite3_bind_int64(statement, 2, static_cast<sqlite_int64>(blockIndex)));
    GFXRECON_SQLITE_CHECK(
        context.db, sqlite3_bind_text64(statement, 3, typeString.data(), typeString.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(
        context.db, sqlite3_bind_text64(statement, 4, label.data(), label.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK(
        context.db, sqlite3_bind_text64(statement, 5, data.data(), data.size(), SQLITE_STATIC, SQLITE_UTF8)
    );
    GFXRECON_SQLITE_CHECK_DONE(context.db, sqlite3_step(statement));
    GFXRECON_SQLITE_CHECK_DONE(context.db, sqlite3_clear_bindings(statement));
}

void VulkanSqliteConsumerBase::Process_vkUpdateDescriptorSetWithTemplate(
    const ApiCallInfo& call_info,
    args::UpdateDescriptorSetWithTemplate& args
)
{
    FieldInfo fieldInfo = { this->block_index_, 0, 0, 0 };
    const auto functionId = statements.InsertFunctionName("vkUpdateDescriptorSetWithTemplate");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(statements, fieldInfo, 2, "descriptorSet", "VkDescriptorSet", args.descriptorSet);
    RecordField(
        statements, fieldInfo, 3, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", args.descriptorUpdateTemplate
    );
    FieldToSqlite(statements, fieldInfo, 4, "pData", &args.pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumerBase::Process_vkUpdateDescriptorSetWithTemplateKHR(
    const ApiCallInfo& call_info,
    args::UpdateDescriptorSetWithTemplateKHR& args
)
{
    FieldInfo fieldInfo = { this->block_index_, 0, 0, 0 };
    const auto functionId = statements.InsertFunctionName("vkUpdateDescriptorSetWithTemplateKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(statements, fieldInfo, 1, "device", "VkDevice", args.device);
    RecordField(statements, fieldInfo, 2, "descriptorSet", "VkDescriptorSet", args.descriptorSet);
    RecordField(
        statements, fieldInfo, 3, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", args.descriptorUpdateTemplate
    );
    FieldToSqlite(statements, fieldInfo, 4, "pData", &args.pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
}

void VulkanSqliteConsumerBase::Process_vkCmdPushDescriptorSetWithTemplate(
    const ApiCallInfo& call_info,
    format::HandleId commandBuffer,
    format::HandleId descriptorUpdateTemplate,
    format::HandleId layout,
    uint32_t set,
    DescriptorUpdateTemplateDecoder* pData
)
{
    FieldInfo fieldInfo = { this->block_index_, 0, 0, 0 };
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSetWithTemplate");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", descriptorUpdateTemplate
    );
    RecordField(statements, fieldInfo, 3, "layout", "VkPipelineLayout", layout);
    RecordField(statements, fieldInfo, 4, "set", "uint32_t", set);
    FieldToSqlite(statements, fieldInfo, 5, "pData", pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");
    UpdateCommandBufferCommands(call_info, commandBuffer);
}

void VulkanSqliteConsumerBase::Process_vkCmdPushDescriptorSetWithTemplateKHR(
    const ApiCallInfo& call_info,
    args::CmdPushDescriptorSetWithTemplateKHR& args
)
{
    FieldInfo fieldInfo = { this->block_index_, 0, 0, 0 };
    const auto functionId = statements.InsertFunctionName("vkCmdPushDescriptorSetWithTemplateKHR");
    statements.InsertApiEvent(this->block_index_, functionId, call_info.thread_id);

    RecordField(statements, fieldInfo, 1, "commandBuffer", "VkCommandBuffer", args.commandBuffer);
    RecordField(
        statements, fieldInfo, 2, "descriptorUpdateTemplate", "VkDescriptorUpdateTemplate", args.descriptorUpdateTemplate
    );
    RecordField(statements, fieldInfo, 3, "layout", "VkPipelineLayout", args.layout);
    RecordField(statements, fieldInfo, 4, "set", "uint32_t", args.set);
    FieldToSqlite(statements, fieldInfo, 5, "pData", &args.pData, "const void*");

    statements.InsertApiEventReturns(this->block_index_, "void", "void");

    UpdateCommandBufferCommands(call_info, args.commandBuffer);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
