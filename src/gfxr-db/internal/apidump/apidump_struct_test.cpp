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

/** Round trips generated struct encoders through the real gfxreconstruct decoders.
 *
 * The encoder tests pin down the wire primitives; this pins down the generated code that calls
 * them. Each case feeds JSON in the shape the api dump layer writes, runs the generated
 * StructFromApiDump, then decodes the buffer with the stock DecodeStruct and checks the fields came
 * back. That covers member order, array handling, enum and bitmask resolution, nested pNext chains
 * and the hand written specializations, all against the decoder that the sqlite consumer runs on.
 */

#include <cstdio>
#include <string>

#include "nlohmann/json.hpp"

#include "apidump_context.h"
#include "apidump_encoder.h"
#include "apidump_handle_map.h"
#include "apidump_json.h"
#include "apidump_struct_encode.h"
#include "generated_vulkan_struct_from_apidump.h"

#include "decode/decode_allocator.h"
#include "decode/pointer_decoder.h"
#include "decode/struct_pointer_decoder.h"
#include "generated/generated_vulkan_struct_decoders.h"

// The structs on the shared blacklist are hand written on the decode side too, so validating the
// hand written encoders means decoding them with gfxreconstruct's own hand written decoders.
#include "decode/custom_vulkan_struct_decoders.h"

using namespace gfxrecon::decode;

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

/** Encodes one struct from JSON text and decodes it back into its gfxreconstruct meta struct. */
template <typename T, typename DecodedT>
class RoundTrip
{
  public:
    explicit RoundTrip(const std::string& json_text) : parsed_(nlohmann::json::parse(json_text))
    {
        ApiDumpContext ctx(encoder_, handles_);

        // StructPointerDecoder reads a pointer preamble before the body, so the encode side has to
        // be the pointer form rather than the bare struct body.
        StructPtrFromApiDump<T>(ctx, ApiDumpNode(&parsed_));
        stats_ = ctx.Stats();

        bytes_read_ = decoder_.Decode(encoder_.GetData(), encoder_.GetDataSize());
    }

    bool ConsumedEverything() const { return bytes_read_ == encoder_.GetDataSize(); }

    const T* Decoded() const { return decoder_.GetPointer(); }

    const DecodedT* Meta() const { return decoder_.GetMetaStructPointer(); }

    const ApiDumpConversionStats& Stats() const { return stats_; }

    ApiDumpHandleMap& Handles() { return handles_; }

  private:
    nlohmann::json                 parsed_;
    ApiDumpEncoder                 encoder_;
    ApiDumpHandleMap               handles_;
    ApiDumpConversionStats         stats_;
    StructPointerDecoder<DecodedT> decoder_;
    size_t                         bytes_read_{ 0 };
};

void TestBufferCreateInfo()
{
    std::printf("VkBufferCreateInfo\n");

    // Taken from the sample capture, including the UNUSED array and the bitmask spelling.
    const std::string json = R"JSON({
        "type": "const VkBufferCreateInfo*", "name": "pCreateInfo", "address": "0x6d59f030d0",
        "members": [
            { "type": "VkStructureType", "name": "sType", "value": "VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO" },
            { "type": "const void*", "name": "pNext", "address": "address" },
            { "type": "VkBufferCreateFlags", "name": "flags", "value": "0" },
            { "type": "VkDeviceSize", "name": "size", "value": "208" },
            { "type": "VkBufferUsageFlags", "name": "usage",
              "value": "130 (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)" },
            { "type": "VkSharingMode", "name": "sharingMode", "value": "VK_SHARING_MODE_EXCLUSIVE" },
            { "type": "uint32_t", "name": "queueFamilyIndexCount", "value": "0" },
            { "type": "const uint32_t*", "name": "pQueueFamilyIndices", "address": "UNUSED", "value": "UNUSED" }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkBufferCreateInfo, Decoded_VkBufferCreateInfo> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkBufferCreateInfo* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("sType", decoded->sType == VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO);
        Expect("pNext null", decoded->pNext == nullptr);
        Expect("size", decoded->size == 208);
        Expect("usage from the numeric prefix",
               decoded->usage == (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));
        Expect("sharingMode from the name", decoded->sharingMode == VK_SHARING_MODE_EXCLUSIVE);
        Expect("queueFamilyIndexCount", decoded->queueFamilyIndexCount == 0);
        Expect("UNUSED array decoded as null", decoded->pQueueFamilyIndices == nullptr);
    }

    Expect("no unknown enum names", trip.Stats().unknown_enum_names == 0);
    Expect("no unparsable scalars", trip.Stats().unparsable_scalars == 0);
}

void TestNestedPNextChain()
{
    std::printf("nested pNext chain\n");

    // The shape the sample capture has on vkCreateDevice: each link nested in the previous one.
    const std::string json = R"JSON({
        "type": "const VkDeviceCreateInfo*", "name": "pCreateInfo", "address": "0x1000",
        "members": [
            { "type": "VkStructureType", "name": "sType", "value": "VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO" },
            { "type": "VkPhysicalDeviceFeatures2*", "name": "pNext", "address": "0x2000",
              "members": [
                  { "type": "VkStructureType", "name": "sType",
                    "value": "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2" },
                  { "type": "VkPhysicalDeviceFaultFeaturesEXT*", "name": "pNext", "address": "0x3000",
                    "members": [
                        { "type": "VkStructureType", "name": "sType",
                          "value": "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT" },
                        { "type": "void*", "name": "pNext", "address": "address" },
                        { "type": "VkBool32", "name": "deviceFault", "value": "1" },
                        { "type": "VkBool32", "name": "deviceFaultVendorBinary", "value": "0" }
                    ] },
                  { "type": "VkPhysicalDeviceFeatures", "name": "features",
                    "members": [ { "type": "VkBool32", "name": "robustBufferAccess", "value": "1" } ] }
              ] },
            { "type": "VkDeviceCreateFlags", "name": "flags", "value": "0" },
            { "type": "uint32_t", "name": "queueCreateInfoCount", "value": "0" },
            { "type": "const VkDeviceQueueCreateInfo*", "name": "pQueueCreateInfos", "address": "address" },
            { "type": "uint32_t", "name": "enabledLayerCount", "value": "0" },
            { "type": "const char* const*", "name": "ppEnabledLayerNames", "address": "address" },
            { "type": "uint32_t", "name": "enabledExtensionCount", "value": "0" },
            { "type": "const char* const*", "name": "ppEnabledExtensionNames", "address": "address" },
            { "type": "const VkPhysicalDeviceFeatures*", "name": "pEnabledFeatures", "address": "address" }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkDeviceCreateInfo, Decoded_VkDeviceCreateInfo> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkDeviceCreateInfo* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("sType", decoded->sType == VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);

        const auto* features2 = reinterpret_cast<const VkPhysicalDeviceFeatures2*>(decoded->pNext);
        Expect("first chain link present", features2 != nullptr);

        if (features2 != nullptr)
        {
            Expect("first link sType", features2->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2);
            Expect("first link body decoded", features2->features.robustBufferAccess == VK_TRUE);

            const auto* fault = reinterpret_cast<const VkPhysicalDeviceFaultFeaturesEXT*>(features2->pNext);
            Expect("second chain link present", fault != nullptr);

            if (fault != nullptr)
            {
                Expect("second link sType",
                       fault->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT);
                Expect("second link body decoded", fault->deviceFault == VK_TRUE);
                Expect("chain terminates", fault->pNext == nullptr);
            }
        }
    }

    Expect("no unknown structure types", trip.Stats().unknown_structure_types == 0);
}

void TestArraysAndHandles()
{
    std::printf("arrays, handles and nested structs\n");

    const std::string json = R"JSON({
        "type": "const VkRenderPassBeginInfo*", "name": "pRenderPassBegin", "address": "0x6d59f031a8",
        "members": [
            { "type": "VkStructureType", "name": "sType", "value": "VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO" },
            { "type": "const void*", "name": "pNext", "address": "address" },
            { "type": "VkRenderPass", "name": "renderPass", "value": "0x120000000012" },
            { "type": "VkFramebuffer", "name": "framebuffer", "value": "0x240000000024" },
            { "type": "VkRect2D", "name": "renderArea", "members": [
                { "type": "VkOffset2D", "name": "offset", "members": [
                    { "type": "int32_t", "name": "x", "value": "0" },
                    { "type": "int32_t", "name": "y", "value": "-5" } ] },
                { "type": "VkExtent2D", "name": "extent", "members": [
                    { "type": "uint32_t", "name": "width", "value": "1440" },
                    { "type": "uint32_t", "name": "height", "value": "3200" } ] } ] },
            { "type": "uint32_t", "name": "clearValueCount", "value": "2" },
            { "type": "const VkClearValue*", "name": "pClearValues", "address": "0x6d59f031e8", "elements": [
                { "type": "const VkClearValue (Union)", "name": "[0]", "address": "0x6d59f031e8", "members": [
                    { "type": "VkClearColorValue (Union)", "name": "color", "members": [
                        { "type": "uint32_t[4]", "name": "uint32", "address": "0x6d59f031e8", "elements": [
                            { "type": "uint32_t", "name": "[0]", "value": "1" },
                            { "type": "uint32_t", "name": "[1]", "value": "2" },
                            { "type": "uint32_t", "name": "[2]", "value": "3" },
                            { "type": "uint32_t", "name": "[3]", "value": "4" } ] } ] } ] },
                { "type": "const VkClearValue (Union)", "name": "[1]", "address": "0x6d59f031f8", "members": [
                    { "type": "VkClearColorValue (Union)", "name": "color", "members": [
                        { "type": "uint32_t[4]", "name": "uint32", "address": "0x6d59f031f8", "elements": [
                            { "type": "uint32_t", "name": "[0]", "value": "10" },
                            { "type": "uint32_t", "name": "[1]", "value": "20" },
                            { "type": "uint32_t", "name": "[2]", "value": "30" },
                            { "type": "uint32_t", "name": "[3]", "value": "40" } ] } ] } ] } ] }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkRenderPassBeginInfo, Decoded_VkRenderPassBeginInfo> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkRenderPassBeginInfo* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("nested struct, signed member", decoded->renderArea.offset.y == -5);
        Expect("nested struct, unsigned member", decoded->renderArea.extent.width == 1440);
        Expect("array count", decoded->clearValueCount == 2);
        Expect("union array decoded",
               (decoded->pClearValues != nullptr) && (decoded->pClearValues[0].color.uint32[0] == 1) &&
                   (decoded->pClearValues[1].color.uint32[3] == 40));
    }

    // Handles become gfxreconstruct ids, so the meta struct is where they land, not the plain struct.
    const Decoded_VkRenderPassBeginInfo* meta = trip.Meta();
    Expect("meta struct present", meta != nullptr);

    if (meta != nullptr)
    {
        Expect("render pass got an id", meta->renderPass != 0);
        Expect("framebuffer got an id", meta->framebuffer != 0);
        Expect("distinct handles got distinct ids", meta->renderPass != meta->framebuffer);
    }
}

void TestStringsAndCustomStruct()
{
    std::printf("strings and a hand written struct\n");

    // VkLayerSettingEXT is hand written on both sides; its pValues array is typed by the setting.
    const std::string json = R"JSON({
        "type": "const VkLayerSettingEXT", "name": "[0]", "address": "0x6dec649b50",
        "members": [
            { "type": "const char*", "name": "pLayerName", "value": "VK_LAYER_LUNARG_api_dump" },
            { "type": "const char*", "name": "pSettingName", "value": "log_filename" },
            { "type": "VkLayerSettingTypeEXT", "name": "type", "value": "VK_LAYER_SETTING_TYPE_STRING_EXT" },
            { "type": "uint32_t", "name": "valueCount", "value": "1" },
            { "type": "const void*", "name": "pValues", "address": "0x6dec649c00", "elements": [
                { "type": "const char*", "name": "[0]", "value": "/data/data/app/sokatoa_capture.json" } ] }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkLayerSettingEXT, Decoded_VkLayerSettingEXT> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkLayerSettingEXT* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("layer name string", (decoded->pLayerName != nullptr) &&
                                        (std::string(decoded->pLayerName) == "VK_LAYER_LUNARG_api_dump"));
        Expect("setting name string", (decoded->pSettingName != nullptr) &&
                                          (std::string(decoded->pSettingName) == "log_filename"));
        Expect("setting type", decoded->type == VK_LAYER_SETTING_TYPE_STRING_EXT);
        Expect("value count", decoded->valueCount == 1);
    }
}

void TestShaderModuleDerivedLength()
{
    std::printf("derived array length\n");

    // pCode's length is codeSize / 4, and its elements are bare strings rather than objects.
    const std::string json = R"JSON({
        "type": "const VkShaderModuleCreateInfo*", "name": "pCreateInfo", "address": "0x6d59f02808",
        "members": [
            { "type": "VkStructureType", "name": "sType",
              "value": "VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO" },
            { "type": "const void*", "name": "pNext", "address": "address" },
            { "type": "VkShaderModuleCreateFlags", "name": "flags", "value": "0" },
            { "type": "size_t", "name": "codeSize", "value": "12" },
            { "type": "const uint32_t*", "name": "pCode", "address": "0xb400006fa3ada810",
              "elements": [ "0x07230203", "0x00010500", "0x000d000a" ] }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkShaderModuleCreateInfo, Decoded_VkShaderModuleCreateInfo> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkShaderModuleCreateInfo* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("codeSize", decoded->codeSize == 12);
        Expect("bare string elements parsed as hex",
               (decoded->pCode != nullptr) && (decoded->pCode[0] == 0x07230203u) &&
                   (decoded->pCode[2] == 0x000d000au));
    }
}

/** An array the layer recorded but did not expand.
 *
 * Regression test. VkLayerSettingEXT pValues arrives from a real capture as an address with no
 * elements, and the string array used to emit a null string preamble per element anyway. That is
 * four bytes gfxreconstruct never writes when kHasData is clear, and it desynchronised everything
 * after it: the whole VkInstanceCreateInfo that contained the chain decoded as garbage.
 */
void TestUnexpandedStringArray()
{
    std::printf("array present but not expanded\n");

    const std::string json = R"JSON({
        "type": "const VkLayerSettingEXT", "name": "[0]", "address": "0x6dec649b50",
        "members": [
            { "type": "const char*", "name": "pLayerName", "value": "VK_LAYER_LUNARG_api_dump" },
            { "type": "const char*", "name": "pSettingName", "value": "log_filename" },
            { "type": "VkLayerSettingTypeEXT", "name": "type", "value": "VK_LAYER_SETTING_TYPE_STRING_EXT" },
            { "type": "uint32_t", "name": "valueCount", "value": "1" },
            { "type": "const void*", "name": "pValues", "address": "0x6d62eb3678" }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkLayerSettingEXT, Decoded_VkLayerSettingEXT> trip(json);

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkLayerSettingEXT* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("preceding members survive", (decoded->pSettingName != nullptr) &&
                                                (std::string(decoded->pSettingName) == "log_filename"));
        Expect("count still recorded", decoded->valueCount == 1);
    }
}

/** A declared array length that lies about the payload behind it.
 *
 * Regression test for the crash this guards against: a corrupted or hand edited .apidump can carry
 * a count field for an array the layer did not expand that is far larger than anything real, which
 * used to flow straight into std::vector::reserve/resize and throw std::bad_alloc or
 * std::length_error, aborting the whole conversion. See ApiDumpContext::kMaxUnexpandedArrayLength.
 */
void TestOversizedLengthHintClamped()
{
    std::printf("oversized declared array length is clamped, not thrown\n");

    // valueCount is far larger than kMaxUnexpandedArrayLength; pValues carries no elements at all,
    // the case where ArrayLength falls back to the declared count instead of the expanded one.
    const std::string json = R"JSON({
        "type": "const VkLayerSettingEXT", "name": "[0]", "address": "0x6dec649b50",
        "members": [
            { "type": "const char*", "name": "pLayerName", "value": "VK_LAYER_LUNARG_api_dump" },
            { "type": "const char*", "name": "pSettingName", "value": "log_filename" },
            { "type": "VkLayerSettingTypeEXT", "name": "type", "value": "VK_LAYER_SETTING_TYPE_UINT32_EXT" },
            { "type": "uint32_t", "name": "valueCount", "value": "4000000000" },
            { "type": "const void*", "name": "pValues", "address": "0x6d62eb3678" }
        ]
    })JSON";

    DecoderAllocGuard<true> guard;
    RoundTrip<VkLayerSettingEXT, Decoded_VkLayerSettingEXT> trip(json);

    // Reaching this line at all is most of the point: the old code threw out of the RoundTrip
    // constructor above instead.
    Expect("buffer consumed exactly", trip.ConsumedEverything());
    Expect("hint was clamped rather than trusted", trip.Stats().oversized_length_hints == 1);
}

/** One triangles geometry, the body of a VkAccelerationStructureGeometryKHR as the layer writes it,
 * shared by the ppGeometries tests below. Taken from an AnTuTu capture. */
const char* const kTrianglesGeometryMembers = R"JSON("members": [
    { "type": "VkStructureType", "name": "sType", "value": "1000150006" },
    { "type": "const void*", "name": "pNext", "address": "address" },
    { "type": "VkGeometryTypeKHR", "name": "geometryType", "value": "0" },
    { "type": "VkAccelerationStructureGeometryDataKHR (Union)", "name": "geometry", "members": [
        { "type": "VkAccelerationStructureGeometryTrianglesDataKHR", "name": "triangles", "members": [
            { "type": "VkStructureType", "name": "sType", "value": "1000150005" },
            { "type": "const void*", "name": "pNext", "address": "address" },
            { "type": "VkFormat", "name": "vertexFormat", "value": "106" },
            { "type": "VkDeviceOrHostAddressConstKHR (Union)", "name": "vertexData", "members": [
                { "type": "VkDeviceAddress", "name": "deviceAddress", "value": "0x37b080000" },
                { "type": "const void*", "name": "hostAddress", "address": "0x37b080000" } ] },
            { "type": "VkDeviceSize", "name": "vertexStride", "value": "12" },
            { "type": "uint32_t", "name": "maxVertex", "value": "1500" },
            { "type": "VkIndexType", "name": "indexType", "value": "1000165000" },
            { "type": "VkDeviceOrHostAddressConstKHR (Union)", "name": "indexData", "members": [
                { "type": "VkDeviceAddress", "name": "deviceAddress", "value": "0x0" },
                { "type": "const void*", "name": "hostAddress", "address": "address" } ] },
            { "type": "VkDeviceOrHostAddressConstKHR (Union)", "name": "transformData", "members": [
                { "type": "VkDeviceAddress", "name": "deviceAddress", "value": "0x0" },
                { "type": "const void*", "name": "hostAddress", "address": "address" } ] } ] } ] },
    { "type": "VkGeometryFlagsKHR", "name": "flags", "value": "0" }
])JSON";

/** A VkAccelerationStructureBuildGeometryInfoKHR with the given pGeometries and ppGeometries nodes. */
std::string BuildGeometryInfoJson(const std::string& geometries, const std::string& pointer_geometries)
{
    return R"JSON({
        "type": "const VkAccelerationStructureBuildGeometryInfoKHR*", "name": "pInfo", "address": "0x7191ff5690",
        "members": [
            { "type": "VkStructureType", "name": "sType", "value": "1000150000" },
            { "type": "const void*", "name": "pNext", "address": "address" },
            { "type": "VkAccelerationStructureTypeKHR", "name": "type", "value": "1" },
            { "type": "VkBuildAccelerationStructureFlagsKHR", "name": "flags", "value": "8" },
            { "type": "VkBuildAccelerationStructureModeKHR", "name": "mode", "value": "0" },
            { "type": "VkAccelerationStructureKHR", "name": "srcAccelerationStructure", "value": "0x0" },
            { "type": "VkAccelerationStructureKHR", "name": "dstAccelerationStructure", "value": "0xb4000072d48706f0" },
            { "type": "uint32_t", "name": "geometryCount", "value": "1" },
            )JSON" +
           geometries + ",\n" + pointer_geometries + R"JSON(,
            { "type": "VkDeviceOrHostAddressKHR (Union)", "name": "scratchData", "members": [
                { "type": "VkDeviceAddress", "name": "deviceAddress", "value": "0x3796c6f00" },
                { "type": "void*", "name": "hostAddress", "address": "0x3796c6f00" } ] }
        ]
    })JSON";
}

/** Checks the members of the build geometry info that every ppGeometries test shares. */
void ExpectBuildGeometryInfo(const VkAccelerationStructureBuildGeometryInfoKHR* decoded)
{
    Expect("type", decoded->type == VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR);
    Expect("geometryCount", decoded->geometryCount == 1);
    // scratchData is the member after ppGeometries, so it only decodes right if ppGeometries
    // consumed exactly the bytes it was encoded with.
    Expect("scratchData after ppGeometries", decoded->scratchData.deviceAddress == 0x3796c6f00);
}

/** A build geometry info whose ppGeometries is null, which is how nearly every application fills it
 * in, here exactly as an AnTuTu capture recorded it. ppGeometries is a 2D struct array
 * (geometryCount pointers to one geometry each), and StructPointerDecoder<T*> asserts the kIsArray2D
 * attribute even when the pointer is null; it used to be encoded as a plain struct array, so every
 * api dump with a vkGetAccelerationStructureBuildSizesKHR or vkCmdBuildAccelerationStructuresKHR call
 * aborted the conversion. */
void TestBuildGeometryInfoNullPointerGeometries()
{
    std::printf("VkAccelerationStructureBuildGeometryInfoKHR with a null ppGeometries\n");

    const std::string json = BuildGeometryInfoJson(
        std::string(R"JSON({ "type": "const VkAccelerationStructureGeometryKHR*", "name": "pGeometries",
            "address": "0x7191ff60a0", "elements": [ { "type": "const VkAccelerationStructureGeometryKHR",
            "name": "[0]", "address": "0x7191ff60a0", )JSON") +
            kTrianglesGeometryMembers + " } ] }",
        R"JSON({ "type": "const VkAccelerationStructureGeometryKHR* const*", "name": "ppGeometries", "address": "address" })JSON"
    );

    DecoderAllocGuard<true> guard;
    RoundTrip<VkAccelerationStructureBuildGeometryInfoKHR, Decoded_VkAccelerationStructureBuildGeometryInfoKHR> trip(
        json
    );

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkAccelerationStructureBuildGeometryInfoKHR* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        ExpectBuildGeometryInfo(decoded);
        Expect("ppGeometries null", decoded->ppGeometries == nullptr);
        Expect("pGeometries decoded", decoded->pGeometries != nullptr);
        if (decoded->pGeometries != nullptr)
        {
            Expect("pGeometries[0] maxVertex", decoded->pGeometries[0].geometry.triangles.maxVertex == 1500);
        }
    }
}

/** The same geometry passed through ppGeometries instead, which the layer writes as one struct pointer
 * per element, each carrying the members of the one geometry it points to. */
void TestBuildGeometryInfoPointerGeometries()
{
    std::printf("VkAccelerationStructureBuildGeometryInfoKHR with ppGeometries\n");

    const std::string json = BuildGeometryInfoJson(
        R"JSON({ "type": "const VkAccelerationStructureGeometryKHR*", "name": "pGeometries", "address": "address" })JSON",
        std::string(R"JSON({ "type": "const VkAccelerationStructureGeometryKHR* const*", "name": "ppGeometries",
            "address": "0x7191ff5000", "elements": [ { "type": "const VkAccelerationStructureGeometryKHR*",
            "name": "[0]", "address": "0x7191ff60a0", )JSON") +
            kTrianglesGeometryMembers + " } ] }"
    );

    DecoderAllocGuard<true> guard;
    RoundTrip<VkAccelerationStructureBuildGeometryInfoKHR, Decoded_VkAccelerationStructureBuildGeometryInfoKHR> trip(
        json
    );

    Expect("buffer consumed exactly", trip.ConsumedEverything());

    const VkAccelerationStructureBuildGeometryInfoKHR* decoded = trip.Decoded();
    Expect("decoded", decoded != nullptr);

    if (decoded != nullptr)
    {
        ExpectBuildGeometryInfo(decoded);
        Expect("pGeometries null", decoded->pGeometries == nullptr);
        Expect("ppGeometries decoded", (decoded->ppGeometries != nullptr) && (decoded->ppGeometries[0] != nullptr));
        if ((decoded->ppGeometries != nullptr) && (decoded->ppGeometries[0] != nullptr))
        {
            const VkAccelerationStructureGeometryKHR* geometry = decoded->ppGeometries[0];
            Expect("ppGeometries[0] geometryType", geometry->geometryType == VK_GEOMETRY_TYPE_TRIANGLES_KHR);
            Expect("ppGeometries[0] vertexFormat", geometry->geometry.triangles.vertexFormat == VK_FORMAT_R32G32B32_SFLOAT);
            Expect("ppGeometries[0] maxVertex", geometry->geometry.triangles.maxVertex == 1500);
        }
    }
}

/** vkCmdBuildAccelerationStructuresKHR ppBuildRangeInfos, as an AnTuTu capture recorded it, plus a
 * null element. The layer dumps only the first range info each element points to, not the
 * pInfos[i].geometryCount the registry declares, so each inner array has to be encoded with the one
 * struct actually recorded. */
void TestBuildRangeInfos2D()
{
    std::printf("vkCmdBuildAccelerationStructuresKHR ppBuildRangeInfos\n");

    const std::string json = R"JSON({
        "type": "const VkAccelerationStructureBuildRangeInfoKHR* const*", "name": "ppBuildRangeInfos",
        "address": "0x7191ff5580",
        "elements": [
            { "type": "const VkAccelerationStructureBuildRangeInfoKHR*", "name": "[0]", "address": "0x7191ff6110",
              "members": [
                { "type": "uint32_t", "name": "primitiveCount", "value": "500" },
                { "type": "uint32_t", "name": "primitiveOffset", "value": "0" },
                { "type": "uint32_t", "name": "firstVertex", "value": "0" },
                { "type": "uint32_t", "name": "transformOffset", "value": "0" } ] },
            { "type": "const VkAccelerationStructureBuildRangeInfoKHR*", "name": "[1]", "address": "0x7191ff6218",
              "members": [
                { "type": "uint32_t", "name": "primitiveCount", "value": "240" },
                { "type": "uint32_t", "name": "primitiveOffset", "value": "16" },
                { "type": "uint32_t", "name": "firstVertex", "value": "3" },
                { "type": "uint32_t", "name": "transformOffset", "value": "0" } ] },
            { "type": "const VkAccelerationStructureBuildRangeInfoKHR*", "name": "[2]", "address": "address" }
        ]
    })JSON";

    const nlohmann::json parsed = nlohmann::json::parse(json);
    ApiDumpEncoder       encoder;
    ApiDumpHandleMap     handles;
    ApiDumpContext       ctx(encoder, handles);
    StructArray2DFromApiDump<VkAccelerationStructureBuildRangeInfoKHR>(ctx, ApiDumpNode(&parsed));

    DecoderAllocGuard<true>                                                 guard;
    StructPointerDecoder<Decoded_VkAccelerationStructureBuildRangeInfoKHR*> decoder;
    const size_t bytes_read = decoder.Decode(encoder.GetData(), encoder.GetDataSize());

    Expect("buffer consumed exactly", bytes_read == encoder.GetDataSize());
    Expect("decoded as a 2D array", decoder.IsArray2D());
    Expect("outer length", decoder.GetLength() == 3);

    VkAccelerationStructureBuildRangeInfoKHR** ranges = decoder.GetPointer();
    Expect("decoded", ranges != nullptr);
    if ((ranges != nullptr) && (decoder.GetLength() == 3))
    {
        Expect("[0] holds the one recorded range", decoder.GetInnerLength(0) == 1);
        Expect("[0] primitiveCount", (ranges[0] != nullptr) && (ranges[0][0].primitiveCount == 500));
        Expect("[1] primitiveOffset", (ranges[1] != nullptr) && (ranges[1][0].primitiveOffset == 16));
        Expect("[1] firstVertex", (ranges[1] != nullptr) && (ranges[1][0].firstVertex == 3));
        Expect("[2] null", ranges[2] == nullptr);
    }
}

/** vkCmdBuildAccelerationStructuresIndirectKHR ppMaxPrimitiveCounts, an array of pointers to uint32_t
 * arrays, which PointerDecoder<T*> asserts as kIsArray2D just as StructPointerDecoder<T*> does for
 * struct arrays. Covers each shape an element can take: a single value, an expanded array, and null. */
void TestMaxPrimitiveCounts2D()
{
    std::printf("vkCmdBuildAccelerationStructuresIndirectKHR ppMaxPrimitiveCounts\n");

    const std::string json = R"JSON({
        "type": "const uint32_t* const*", "name": "ppMaxPrimitiveCounts", "address": "0x1000",
        "elements": [
            { "type": "const uint32_t*", "name": "[0]", "address": "0x2000", "value": "7" },
            { "type": "const uint32_t*", "name": "[1]", "address": "0x3000", "elements": [ "3", "4" ] },
            { "type": "const uint32_t*", "name": "[2]", "address": "address" }
        ]
    })JSON";

    const nlohmann::json parsed = nlohmann::json::parse(json);
    ApiDumpEncoder       encoder;
    ApiDumpHandleMap     handles;
    ApiDumpContext       ctx(encoder, handles);
    ctx.UInt32Array2D(ApiDumpNode(&parsed));

    DecoderAllocGuard<true>  guard;
    PointerDecoder<uint32_t*> decoder;
    const size_t              bytes_read = decoder.DecodeUInt32(encoder.GetData(), encoder.GetDataSize());

    Expect("buffer consumed exactly", bytes_read == encoder.GetDataSize());
    Expect("outer length", decoder.GetLength() == 3);

    uint32_t** counts = decoder.GetPointer();
    Expect("decoded", counts != nullptr);
    if ((counts != nullptr) && (decoder.GetLength() == 3))
    {
        Expect("[0] single value", (decoder.GetInnerLength(0) == 1) && (counts[0] != nullptr) && (counts[0][0] == 7));
        Expect("[1] expanded array",
               (decoder.GetInnerLength(1) == 2) && (counts[1] != nullptr) && (counts[1][0] == 3) && (counts[1][1] == 4));
        Expect("[2] null", counts[2] == nullptr);
    }
    Expect("no unparsable scalars", ctx.Stats().unparsable_scalars == 0);
}

} // namespace

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    TestBufferCreateInfo();
    TestNestedPNextChain();
    TestArraysAndHandles();
    TestStringsAndCustomStruct();
    TestShaderModuleDerivedLength();
    TestUnexpandedStringArray();
    TestOversizedLengthHintClamped();
    TestBuildGeometryInfoNullPointerGeometries();
    TestBuildGeometryInfoPointerGeometries();
    TestBuildRangeInfos2D();
    TestMaxPrimitiveCounts2D();

    if (g_failures == 0)
    {
        std::printf("\nGenerated struct encoders round trip through the gfxreconstruct decoders.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
