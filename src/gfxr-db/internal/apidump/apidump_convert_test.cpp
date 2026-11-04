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

/** Converts the checked in .apidump fixture through the real CreateDBHelper path.
 *
 * The other tests each pin down one layer. This one runs the whole thing the way the CLI and the
 * node addon do, and asserts on the database that comes out, so a regression anywhere between the
 * json reader and the sqlite consumer shows up here.
 *
 * The fixture is a slice of a real orphanedObjects capture: the setup frame, the frame where the
 * scene destroys and recreates its objects, and three steady state frames.
 */

#include <cstdio>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "sqlite3.h"

#include "create_db_helper.h"
#include "test_resources_path.h"

namespace
{

int g_failures = 0;

void Expect(const char* what, bool condition)
{
    if (condition)
    {
        std::printf("  ok    %s\n", what);
    }
    else
    {
        ++g_failures;
        std::printf("  FAIL  %s\n", what);
    }
}

/** Runs one scalar query, returning -1 when the query fails. */
int64_t QueryScalar(sqlite3* db, const char* sql)
{
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::printf("  FAIL  query failed to prepare: %s (%s)\n", sql, sqlite3_errmsg(db));
        ++g_failures;
        return -1;
    }

    int64_t result = -1;
    if (sqlite3_step(statement) == SQLITE_ROW)
    {
        result = sqlite3_column_int64(statement, 0);
    }

    sqlite3_finalize(statement);
    return result;
}

/** One api dump value node, the way the layer writes a scalar. */
std::string Value(const char* type, const char* name, const char* value)
{
    return std::string("{\"type\":\"") + type + "\",\"name\":\"" + name + "\",\"value\":\"" + value + "\"}";
}

/** A pointer the layer wrote an address for and did not expand. */
std::string Address(const char* type, const char* name, const char* address)
{
    return std::string("{\"type\":\"") + type + "\",\"name\":\"" + name + "\",\"address\":\"" + address + "\"}";
}

std::string Call(const char* name, const std::string& args, const char* returnValue = nullptr)
{
    std::string call = std::string("{\"name\":\"") + name + "\",\"thread\":\"Thread 1\",\"args\":[" + args + "]";
    if (returnValue != nullptr)
    {
        call += std::string(",\"returnValue\":\"") + returnValue + "\"";
    }
    return call + "}";
}

/** A dump holding the commands gfxreconstruct decodes by hand, plus a vkMapMemory.
 *
 * Those commands sit on gfxreconstruct's generator blacklists, so the api dump generator used to skip
 * them with the rest of the blacklist, and every call came out as "no decoder". The vkMapMemory is
 * here because its void** ppData must be encoded as a pointer: written as a bare address the decoder
 * read half of it as flag bits and went on to fill an array of whatever length followed.
 */
std::string HandWrittenCommandsDump()
{
    const std::string createInfo =
        "{\"type\":\"const VkRayTracingPipelineCreateInfoKHR\",\"name\":\"[0]\",\"address\":\"0x1000\",\"members\":["
        + Value("VkStructureType", "sType", "1000150015") + "," + Address("const void*", "pNext", "address") + ","
        + Value("VkPipelineCreateFlags", "flags", "0") + "," + Value("uint32_t", "stageCount", "0") + ","
        + Value("uint32_t", "groupCount", "0") + "," + Value("uint32_t", "maxPipelineRayRecursionDepth", "1") + ","
        + Value("VkPipelineLayout", "layout", "0x20") + "," + Value("VkPipeline", "basePipelineHandle", "0x0") + ","
        + Value("int32_t", "basePipelineIndex", "0") + "]}";

    const std::string createRayTracing = Call(
        "vkCreateRayTracingPipelinesKHR",
        Value("VkDevice", "device", "0x10") + "," + Value("VkDeferredOperationKHR", "deferredOperation", "0x0") + ","
            + Value("VkPipelineCache", "pipelineCache", "0x0") + "," + Value("uint32_t", "createInfoCount", "1")
            + ",{\"type\":\"const VkRayTracingPipelineCreateInfoKHR*\",\"name\":\"pCreateInfos\",\"address\":\"0x1000\","
              "\"elements\":["
            + createInfo + "]}," + Address("const VkAllocationCallbacks*", "pAllocator", "address")
            + ",{\"type\":\"VkPipeline*\",\"name\":\"pPipelines\",\"address\":\"0x2000\",\"elements\":["
              "{\"type\":\"VkPipeline\",\"name\":\"[0]\",\"address\":\"0x2000\",\"value\":\"0x30\"}]}",
        "0"
    );

    const std::string join = Call(
        "vkDeferredOperationJoinKHR",
        Value("VkDevice", "device", "0x10") + "," + Value("VkDeferredOperationKHR", "operation", "0x40"), "0"
    );

    const std::string updateTemplate =
        Value("VkDevice", "device", "0x10") + "," + Value("VkDescriptorSet", "descriptorSet", "0x50") + ","
        + Value("VkDescriptorUpdateTemplate", "descriptorUpdateTemplate", "0x60") + ","
        + Address("const void*", "pData", "0x3000");

    const std::string pushTemplate =
        Value("VkCommandBuffer", "commandBuffer", "0x70") + ","
        + Value("VkDescriptorUpdateTemplate", "descriptorUpdateTemplate", "0x60") + ","
        + Value("VkPipelineLayout", "layout", "0x20") + "," + Value("uint32_t", "set", "0") + ","
        + Address("const void*", "pData", "0x3000");

    // The info struct is expanded and carries pData as a member, which the decoder reads from the
    // stream straight after the struct instead.
    const std::string pushTemplate2 =
        Value("VkCommandBuffer", "commandBuffer", "0x70")
        + ",{\"type\":\"const VkPushDescriptorSetWithTemplateInfo*\",\"name\":\"pPushDescriptorSetWithTemplateInfo\","
          "\"address\":\"0x4000\",\"members\":["
        + Value("VkStructureType", "sType", "1000000000") + "," + Address("const void*", "pNext", "address") + ","
        + Value("VkDescriptorUpdateTemplate", "descriptorUpdateTemplate", "0x60") + ","
        + Value("VkPipelineLayout", "layout", "0x20") + "," + Value("uint32_t", "set", "0") + ","
        + Address("const void*", "pData", "0x3000") + "]}";

    const std::string mapMemory = Call(
        "vkMapMemory",
        Value("VkDevice", "device", "0x10") + "," + Value("VkDeviceMemory", "memory", "0x80") + ","
            + Value("VkDeviceSize", "offset", "0") + "," + Value("VkDeviceSize", "size", "96") + ","
            + Value("VkMemoryMapFlags", "flags", "0") + "," + Address("void**", "ppData", "0xb4000078754b7ea8"),
        "0"
    );

    return "[{\"frameNumber\":\"0\",\"apiCalls\":[" + createRayTracing + "," + join + ","
           + Call("vkUpdateDescriptorSetWithTemplate", updateTemplate) + ","
           + Call("vkUpdateDescriptorSetWithTemplateKHR", updateTemplate) + ","
           + Call("vkCmdPushDescriptorSetWithTemplateKHR", pushTemplate) + ","
           + Call("vkCmdPushDescriptorSetWithTemplate2KHR", pushTemplate2) + "," + mapMemory + "]}]";
}

int64_t CountCalls(sqlite3* db, const char* functionName)
{
    const std::string sql = std::string("select count(*) from apiEvents e join functionNames f on f.id = "
                                        "e.functionNameId where f.name = '") +
                            functionName + "'";
    return QueryScalar(db, sql.c_str());
}

/** Converts HandWrittenCommandsDump and checks each command became an api event. */
void CheckHandWrittenCommands()
{
    std::printf("converting a dump of the hand decoded commands\n");

    const auto dump     = std::filesystem::temp_directory_path() / "apidump_handwritten_test.apidump";
    const auto database = std::filesystem::temp_directory_path() / "apidump_handwritten_test.sqlite3";
    std::error_code ignored;
    std::filesystem::remove(database, ignored);

    {
        std::ofstream out(dump, std::ios::binary | std::ios::trunc);
        out << HandWrittenCommandsDump();
    }

    std::vector<std::string> errors;
    gfxrSqlite::CreateDBHelper helper{ dump.string(),
                                       database.string(),
                                       std::nullopt,
                                       /*enforceForeignKeys=*/false,
                                       [&errors](const std::string& error) { errors.push_back(error); } };
    helper.createDatabase();

    for (const auto& error : errors)
    {
        std::printf("  FAIL  conversion reported: %s\n", error.c_str());
        ++g_failures;
    }

    sqlite3* db = helper.getDB();
    Expect("hand decoded commands: database was created", db != nullptr);
    if (db == nullptr)
    {
        return;
    }

    Expect("every call became an api event",
           QueryScalar(db, "select count(*) from apiEvents where apiEventTypeId = 2") == 7);
    Expect("vkCreateRayTracingPipelinesKHR was decoded", CountCalls(db, "vkCreateRayTracingPipelinesKHR") == 1);
    Expect("vkDeferredOperationJoinKHR was decoded", CountCalls(db, "vkDeferredOperationJoinKHR") == 1);
    Expect("vkUpdateDescriptorSetWithTemplate was decoded", CountCalls(db, "vkUpdateDescriptorSetWithTemplate") == 1);
    Expect("vkUpdateDescriptorSetWithTemplateKHR was decoded",
           CountCalls(db, "vkUpdateDescriptorSetWithTemplateKHR") == 1);
    Expect("vkCmdPushDescriptorSetWithTemplateKHR was decoded",
           CountCalls(db, "vkCmdPushDescriptorSetWithTemplateKHR") == 1);
    Expect("vkCmdPushDescriptorSetWithTemplate2KHR was decoded",
           CountCalls(db, "vkCmdPushDescriptorSetWithTemplate2KHR") == 1);

    // The ray tracing create has a stream layout of its own, so it surviving end to end is the check
    // that the encoder matches the hand written decoder: the pipeline and its info row must exist,
    // and the VkResult after pPipelines must have been read from the right place.
    Expect("the ray tracing pipeline was recorded", QueryScalar(db, "select count(*) from raytracingPipelineInfos") == 1);
    Expect("its result was read from the right place",
           QueryScalar(db,
                       "select count(*) from apiEventReturns r join apiEvents e on e.id = r.apiEventId"
                       " join functionNames f on f.id = e.functionNameId"
                       " where f.name = 'vkCreateRayTracingPipelinesKHR' and r.value = 0") == 1);

    // vkMapMemory's result follows ppData, so reading it back as VK_SUCCESS shows ppData consumed
    // exactly the bytes the encoder wrote.
    Expect("vkMapMemory was decoded", CountCalls(db, "vkMapMemory") == 1);
    Expect("vkMapMemory's result follows ppData correctly",
           QueryScalar(db,
                       "select count(*) from apiEventReturns r join apiEvents e on e.id = r.apiEventId"
                       " join functionNames f on f.id = e.functionNameId"
                       " where f.name = 'vkMapMemory' and r.value = 0") == 1);
}

/** A vkCreateDevice whose only features come from feature structs chained on pNext.
 *
 * Trimmed from a real capture. The feature walker used to read each struct's VkBool32s out of the
 * decoder's 16 byte meta struct rather than the struct it points at, so the names it recorded were
 * whatever followed in memory. The values alternate so a lucky read cannot reproduce them.
 */
std::string DeviceFeaturePNextDump()
{
    const std::string fault =
        "{\"type\":\"VkPhysicalDeviceFaultFeaturesEXT*\",\"name\":\"pNext\",\"address\":\"0x5100\",\"members\":["
        + Value("VkStructureType", "sType", "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT") + ","
        + Address("void*", "pNext", "address") + "," + Value("VkBool32", "deviceFault", "1") + ","
        + Value("VkBool32", "deviceFaultVendorBinary", "0") + "]}";

    static constexpr const char* atomicFloatMembers[] = {
        "shaderBufferFloat32Atomics", "shaderBufferFloat32AtomicAdd", "shaderBufferFloat64Atomics",
        "shaderBufferFloat64AtomicAdd", "shaderSharedFloat32Atomics", "shaderSharedFloat32AtomicAdd",
        "shaderSharedFloat64Atomics", "shaderSharedFloat64AtomicAdd", "shaderImageFloat32Atomics",
        "shaderImageFloat32AtomicAdd", "sparseImageFloat32Atomics", "sparseImageFloat32AtomicAdd",
    };
    std::string atomicFloat =
        "{\"type\":\"VkPhysicalDeviceShaderAtomicFloatFeaturesEXT*\",\"name\":\"pNext\",\"address\":\"0x5000\","
        "\"members\":["
        + Value("VkStructureType", "sType", "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT") + ","
        + fault;
    for (size_t i = 0; i < std::size(atomicFloatMembers); ++i)
    {
        atomicFloat += "," + Value("VkBool32", atomicFloatMembers[i], (i % 2 == 0) ? "1" : "0");
    }
    atomicFloat += "]}";

    const std::string createInfo =
        "{\"type\":\"const VkDeviceCreateInfo*\",\"name\":\"pCreateInfo\",\"address\":\"0x4000\",\"members\":["
        + Value("VkStructureType", "sType", "VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO") + "," + atomicFloat + ","
        + Value("VkDeviceCreateFlags", "flags", "0") + "," + Value("uint32_t", "queueCreateInfoCount", "0") + ","
        + Address("const VkDeviceQueueCreateInfo*", "pQueueCreateInfos", "address") + ","
        + Value("uint32_t", "enabledLayerCount", "0") + ","
        + Address("const char* const*", "ppEnabledLayerNames", "address") + ","
        + Value("uint32_t", "enabledExtensionCount", "0") + ","
        + Address("const char* const*", "ppEnabledExtensionNames", "address") + ","
        + Address("const VkPhysicalDeviceFeatures*", "pEnabledFeatures", "address") + "]}";

    const std::string createDevice = Call(
        "vkCreateDevice",
        Value("VkPhysicalDevice", "physicalDevice", "0x10") + "," + createInfo + ","
            + Address("const VkAllocationCallbacks*", "pAllocator", "address")
            + ",{\"type\":\"VkDevice*\",\"name\":\"pDevice\",\"address\":\"0x6000\",\"value\":\"0x20\"}",
        "VK_SUCCESS"
    );

    return "[{\"frameNumber\":\"0\",\"apiCalls\":[" + createDevice + "]}]";
}

/** Runs one query returning a single text value, returning "<error>" when the query fails. */
std::string QueryText(sqlite3* db, const char* sql)
{
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::printf("  FAIL  query failed to prepare: %s (%s)\n", sql, sqlite3_errmsg(db));
        ++g_failures;
        return "<error>";
    }

    std::string result;
    if (sqlite3_step(statement) == SQLITE_ROW && sqlite3_column_text(statement, 0) != nullptr)
    {
        result = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
    }

    sqlite3_finalize(statement);
    return result;
}

/** Converts DeviceFeaturePNextDump and checks exactly the enabled pNext features were recorded. */
void CheckDeviceFeaturePNext()
{
    std::printf("converting a vkCreateDevice with pNext feature structs\n");

    const auto dump     = std::filesystem::temp_directory_path() / "apidump_device_features_test.apidump";
    const auto database = std::filesystem::temp_directory_path() / "apidump_device_features_test.sqlite3";
    std::error_code ignored;
    std::filesystem::remove(database, ignored);

    {
        std::ofstream out(dump, std::ios::binary | std::ios::trunc);
        out << DeviceFeaturePNextDump();
    }

    std::vector<std::string> errors;
    gfxrSqlite::CreateDBHelper helper{ dump.string(),
                                       database.string(),
                                       std::nullopt,
                                       /*enforceForeignKeys=*/false,
                                       [&errors](const std::string& error) { errors.push_back(error); } };
    helper.createDatabase();

    for (const auto& error : errors)
    {
        std::printf("  FAIL  conversion reported: %s\n", error.c_str());
        ++g_failures;
    }

    sqlite3* db = helper.getDB();
    Expect("device features: database was created", db != nullptr);
    if (db == nullptr)
    {
        return;
    }

    Expect("the device was recorded", QueryScalar(db, "select count(*) from devices") == 1);

    const std::string expected = "deviceFault,shaderBufferFloat32Atomics,shaderBufferFloat64Atomics,"
                                 "shaderImageFloat32Atomics,shaderSharedFloat32Atomics,"
                                 "shaderSharedFloat64Atomics,sparseImageFloat32Atomics";
    const std::string actual =
        QueryText(db, "select group_concat(name, ',') from (select name from deviceEnabledFeatures order by name)");
    if (actual != expected)
    {
        std::printf("  info  recorded features: %s\n", actual.c_str());
    }
    Expect("exactly the enabled pNext features were recorded", actual == expected);
}

/** Checks the vertex data addresses, in geometry order, of the first build info whose geometry 0
 * starts at firstAddress and which has geometryCount geometries. The addresses are printed in hex
 * without a prefix. The subquery's ordering feeds group_concat, which sqlite honours in practice. */
void ExpectVertexAddresses(
    sqlite3* db, const char* what, int64_t firstAddress, int geometryCount, const std::string& expected
)
{
    const std::string infoId =
        "(select g0.accelerationStructureBuildGeometryInfoId from accelerationStructureBuildGeometries g0"
        " join accelerationStructureBuildTriangleDatas t0 on t0.id = g0.triangleDataId"
        " where g0.idx = 0 and t0.vertexDataAddress = " + std::to_string(firstAddress) +
        " and (select count(*) from accelerationStructureBuildGeometries gc"
        " where gc.accelerationStructureBuildGeometryInfoId = g0.accelerationStructureBuildGeometryInfoId) = " +
        std::to_string(geometryCount) + " limit 1)";
    const std::string sql =
        "select group_concat(printf('%x', t.vertexDataAddress), ',') from ("
        " select g.triangleDataId from accelerationStructureBuildGeometries g"
        " where g.accelerationStructureBuildGeometryInfoId = " + infoId +
        " order by g.idx) o join accelerationStructureBuildTriangleDatas t on t.id = o.triangleDataId";

    const std::string actual = QueryText(db, sql.c_str());
    Expect(what, actual == expected);
    if (actual != expected)
    {
        std::printf("  info  expected %s, got %s\n", expected.c_str(), actual.c_str());
    }
}

/** Converts the raytracing scene capture and checks every acceleration structure build geometry was stored.
 *
 * The capture holds 147 vkCmdBuildAccelerationStructuresKHR calls with 172 build infos. 18 of those
 * infos pass their geometries through ppGeometries (2 or 3 each, the scene's test cases 22 to 25) and
 * the rest through pGeometries. ppGeometries used to be indexed by build info rather than by
 * geometry, so each ppGeometries info stored one geometry, and the wrong one.
 *
 * Range infos are deliberately not checked: the api dump records one range info per build info
 * rather than one per geometry (sokatoa-internal#6698), so the dump has too few to match.
 */
void CheckRaytracingBuildGeometries()
{
    std::printf("converting the raytracing scene capture\n");

    const auto database = std::filesystem::temp_directory_path() / "apidump_raytracing_test.sqlite3";
    std::error_code ignored;
    std::filesystem::remove(database, ignored);

    std::filesystem::path fixture;
    try
    {
        fixture = gfxrSqlite::getTestResourcesFolder() / "test_raytracing.apidump";
    }
    catch (const std::exception& e)
    {
        std::printf("  FAIL  %s\n", e.what());
        ++g_failures;
        return;
    }

    std::vector<std::string> errors;
    gfxrSqlite::CreateDBHelper helper{ fixture.string(),
                                       database.string(),
                                       std::nullopt,
                                       /*enforceForeignKeys=*/false,
                                       [&errors](const std::string& error) { errors.push_back(error); } };
    helper.createDatabase();

    for (const auto& error : errors)
    {
        std::printf("  FAIL  conversion reported: %s\n", error.c_str());
        ++g_failures;
    }

    sqlite3* db = helper.getDB();
    Expect("raytracing: database was created", db != nullptr);
    if (db == nullptr)
    {
        return;
    }

    Expect("every build info was recorded",
           QueryScalar(db, "select count(*) from accelerationStructureBuildGeometryInfos") == 172);

    // Build infos by how many geometries they stored. The capture has 103 single geometry infos, 54
    // with two and 15 with three. Before the fix the 18 ppGeometries infos all landed in "1".
    const std::string geometriesPerInfo = QueryText(
        db,
        "select group_concat(geometries || 'x' || infos, ',') from ("
        " select geometries, count(*) as infos from ("
        "  select i.id, count(g.idx) as geometries from accelerationStructureBuildGeometryInfos i"
        "  left join accelerationStructureBuildGeometries g on g.accelerationStructureBuildGeometryInfoId = i.id"
        "  group by i.id)"
        " group by geometries order by geometries)"
    );
    Expect("every build info stored all of its geometries", geometriesPerInfo == "1x103,2x54,3x15");
    if (geometriesPerInfo != "1x103,2x54,3x15")
    {
        std::printf("  info  geometries x build infos: %s\n", geometriesPerInfo.c_str());
    }

    Expect("geometry indices run from 0 with no gaps",
           QueryScalar(db,
                       "select count(*) from (select accelerationStructureBuildGeometryInfoId from"
                       " accelerationStructureBuildGeometries group by accelerationStructureBuildGeometryInfoId"
                       " having min(idx) != 0 or max(idx) != count(*) - 1)") == 0);

    // The capture's geometries are 170 triangles and 86 instances (a TLAS build each), no AABBs.
    // geometryType is 0 for triangles and 2 for instances.
    const std::string geometryTypes = QueryText(
        db,
        "select group_concat(type || 'x' || geometries, ',') from ("
        " select type, count(*) as geometries from accelerationStructureBuildGeometries"
        " group by type order by type)"
    );
    Expect("geometry types were kept", geometryTypes == "0x170,2x86");
    if (geometryTypes != "0x170,2x86")
    {
        std::printf("  info  geometry types x geometries: %s\n", geometryTypes.c_str());
    }

    // The stored order shows which pointer ended up at which index. Each sequence below is the
    // vertex data addresses of one build info, picked out by its first address and geometry count.
    //
    // ppGeometries (test cases 24 and 25's build info 1): consecutive 36 byte triangles in one
    // vertex buffer. Before the fix this stored only the second triangle.
    ExpectVertexAddresses(db, "ppGeometries, 3 geometries", 0x306480000, 3, "306480000,306480024,306480048");

    // pGeometries, from the other frames: the order must survive the move into the shared helper,
    // including a build that points two geometries at the same vertex data and one that jumps
    // between buffers.
    ExpectVertexAddresses(db, "pGeometries, 2 geometries", 0x306280000, 2, "306280000,306280024");
    ExpectVertexAddresses(db, "pGeometries, 3 geometries, repeated address", 0x306200000, 3,
                          "306200000,306200000,306200024");
    ExpectVertexAddresses(db, "pGeometries, 3 geometries, separate buffers", 0x306300000, 3,
                          "306300000,304d80000,306300060");
}

} // namespace

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    std::filesystem::path fixture;
    try
    {
        fixture = gfxrSqlite::getTestResourcesFolder() / "test1.apidump";
    }
    catch (const std::exception& e)
    {
        std::printf("  FAIL  %s\n", e.what());
        return 1;
    }

    if (!std::filesystem::exists(fixture))
    {
        std::printf("  FAIL  fixture missing: %s\n", fixture.string().c_str());
        return 1;
    }

    const auto database = std::filesystem::temp_directory_path() / "apidump_convert_test.sqlite3";
    std::error_code ignored;
    std::filesystem::remove(database, ignored);

    std::printf("converting %s\n", fixture.filename().string().c_str());

    std::vector<std::string> errors;
    gfxrSqlite::CreateDBHelper helper{ fixture.string(),
                                       database.string(),
                                       std::nullopt,
                                       /*enforceForeignKeys=*/false,
                                       [&errors](const std::string& error) { errors.push_back(error); } };
    helper.createDatabase();

    for (const auto& error : errors)
    {
        std::printf("  FAIL  conversion reported: %s\n", error.c_str());
        ++g_failures;
    }

    sqlite3* db = helper.getDB();
    Expect("database was created", db != nullptr);
    if (db == nullptr)
    {
        return 1;
    }

    // The fixture holds 288 calls, and every frame contributes one end marker, which occupies an
    // apiEvents row of its own exactly as a frame marker block does in a .gfxr.
    const int64_t calls  = QueryScalar(db, "select count(*) from apiEvents where apiEventTypeId = 2");
    const int64_t markers = QueryScalar(db, "select count(*) from apiEvents where apiEventTypeId = 1");
    std::printf("  info  %lld api calls, %lld meta events\n",
                static_cast<long long>(calls),
                static_cast<long long>(markers));
    Expect("every call in the fixture became an api event", calls == 288);
    Expect("frame markers were emitted", markers > 0);

    // Api dump frame 0 is tagged isSetupFrame, so it is bracketed with a StateBeginMarker /
    // StateEndMarker pair and folded into db frame 1 instead of getting its own frame end marker -
    // the same shape a trimmed .gfxr's initial state has. Frames 10 through 13 are real frames and
    // map to db frames 11 through 14, with no filler frames for the gap the setup region collapsed.
    Expect("frames start at 1", QueryScalar(db, "select min(id) from frames") == 1);
    Expect("the setup frame holds the setup calls",
           QueryScalar(db, "select count(*) from apiEvents where frameId = 1") > 100);
    Expect("a state begin marker brackets the setup frame",
           QueryScalar(
               db,
               "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
               " where f.name = 'StateBeginMarker'"
           ) == 1);
    Expect("a state end marker closes the setup frame",
           QueryScalar(
               db,
               "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
               " where f.name = 'StateEndMarker'"
           ) == 1);
    Expect("no filler frames were left for the range the setup region collapsed",
           QueryScalar(db, "select count(*) from frames where id > 1 and id < 11") == 0);

    // Object identity. The scene destroys objects and lets the driver hand the same addresses back,
    // which is the case the handle map exists for: a create must never resolve to a live id.
    const int64_t createCalls =
        QueryScalar(db,
                    "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
                    " where f.name = 'vkCreateBuffer'");
    const int64_t bufferRows     = QueryScalar(db, "select count(*) from buffers");
    const int64_t distinctBuffers = QueryScalar(db, "select count(distinct handle) from buffers");
    std::printf("  info  %lld vkCreateBuffer calls, %lld buffer rows\n",
                static_cast<long long>(createCalls),
                static_cast<long long>(bufferRows));
    Expect("every buffer create produced a row", (createCalls > 0) && (bufferRows == createCalls));
    Expect("recycled addresses did not collapse into one object", distinctBuffers == bufferRows);

    // Every id the handle map mints gets recorded alongside the raw address that produced it, so
    // e.g. a shaderModules.handle can be resolved back to the api dump's own handle value (needed
    // to build a shader extraction handle map). This must hold even for a recycled address, which
    // is exactly what the buffers above exercise.
    const int64_t handleAddressRows = QueryScalar(db, "select count(*) from apiDumpHandleAddresses");
    Expect("handle addresses were recorded", handleAddressRows > 0);
    const int64_t buffersWithAddress = QueryScalar(
        db,
        "select count(*) from buffers join apiDumpHandleAddresses"
        " on apiDumpHandleAddresses.handle = buffers.handle");
    Expect("every buffer's id resolves back to a raw address", buffersWithAddress == bufferRows);

    // Instances resolve, which only happens if the whole VkInstanceCreateInfo decoded: it carries a
    // pNext chain, a nested struct and two string arrays, so a single byte of drift loses it.
    Expect("instances were recorded", QueryScalar(db, "select count(*) from instances") > 0);
    Expect("application name survived",
           QueryScalar(db, "select count(*) from instances where applicationName != ''") > 0);

    // Command buffer contents, which is what makes the capture worth browsing at all.
    Expect("command buffer commands were recorded",
           QueryScalar(db, "select count(*) from commandBufferCommands") > 0);

    CheckHandWrittenCommands();
    CheckDeviceFeaturePNext();
    CheckRaytracingBuildGeometries();

    if (g_failures == 0)
    {
        std::printf("\nThe fixture converts to a well formed database.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
