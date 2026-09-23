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

    if (g_failures == 0)
    {
        std::printf("\nGenerated struct encoders round trip through the gfxreconstruct decoders.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
