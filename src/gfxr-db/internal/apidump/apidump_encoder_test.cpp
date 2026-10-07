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

/** Differential test pinning ApiDumpEncoder to the gfxreconstruct wire format.
 *
 * ApiDumpEncoder re-implements a subset of gfxrecon::encode::ParameterEncoder rather than using it,
 * for the reasons documented on the class. That buys a decode-only dependency graph at the cost of
 * a silent-drift risk: if gfxreconstruct ever changes how a pointer preamble or an array length is
 * laid out, the adapter would keep producing buffers that the decoders parse into garbage.
 *
 * So this test encodes the same inputs through both encoders and asserts the bytes are identical.
 * The test is the one place allowed to include encode/parameter_encoder.h; the shipping library
 * must not. It also decodes one buffer through the real generated decoder as an end-to-end check
 * that byte equality actually buys correct parsing.
 */

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "apidump_encoder.h"

#include "decode/value_decoder.h"
#include "encode/parameter_encoder.h"
#include "format/format.h"
#include "generated/generated_vulkan_struct_decoders.h"
#include "util/memory_output_stream.h"

namespace
{

int g_failures = 0;

/** Compares an ApiDumpEncoder buffer against a ParameterEncoder buffer and reports any mismatch. */
void ExpectSameBytes(
    const char*                            what,
    const gfxrecon::decode::ApiDumpEncoder& actual,
    const gfxrecon::util::MemoryOutputStream& expected
)
{
    const size_t actual_size   = actual.GetDataSize();
    const size_t expected_size = expected.GetDataSize();

    if ((actual_size == expected_size) && (std::memcmp(actual.GetData(), expected.GetData(), actual_size) == 0))
    {
        std::printf("  ok    %s (%zu bytes)\n", what, actual_size);
        return;
    }

    ++g_failures;
    std::printf("  FAIL  %s: %zu bytes vs %zu expected\n", what, actual_size, expected_size);

    const auto* actual_bytes   = actual.GetData();
    const auto* expected_bytes = expected.GetData();
    const size_t common        = (actual_size < expected_size) ? actual_size : expected_size;

    for (size_t i = 0; i < common; ++i)
    {
        if (actual_bytes[i] != expected_bytes[i])
        {
            std::printf("        first difference at byte %zu: 0x%02x vs 0x%02x\n", i, actual_bytes[i],
                        expected_bytes[i]);
            break;
        }
    }
}

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

/** Scalars, enums, flags and handles. */
void TestValues()
{
    std::printf("values\n");

    gfxrecon::util::MemoryOutputStream   stream;
    gfxrecon::encode::ParameterEncoder   expected(&stream);
    gfxrecon::decode::ApiDumpEncoder     actual;

    expected.EncodeUInt32Value(0xdeadbeefu);
    expected.EncodeInt32Value(-42);
    expected.EncodeUInt64Value(0x0123456789abcdefull);
    expected.EncodeFloatValue(0.15625f);
    expected.EncodeSizeTValue(4096);
    expected.EncodeHandleIdValue(7);
    expected.EncodeEnumValue(VK_SHARING_MODE_EXCLUSIVE);
    expected.EncodeFlagsValue(static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));

    actual.EncodeUInt32Value(0xdeadbeefu);
    actual.EncodeInt32Value(-42);
    actual.EncodeUInt64Value(0x0123456789abcdefull);
    actual.EncodeFloatValue(0.15625f);
    actual.EncodeSizeTValue(4096);
    actual.EncodeHandleIdValue(7);
    actual.EncodeEnumValue(VK_SHARING_MODE_EXCLUSIVE);
    actual.EncodeFlagsValue(static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));

    ExpectSameBytes("scalar values", actual, stream);
}

/** A pointer to a single value, in each of its three states. */
void TestSinglePointers()
{
    std::printf("single pointers\n");

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        const uint32_t value = 1234;
        expected.EncodeUInt32Ptr(&value);
        actual.EncodePointer<uint32_t>(value, reinterpret_cast<uint64_t>(&value), false, true);

        ExpectSameBytes("non-null with data", actual, stream);
    }

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        expected.EncodeUInt32Ptr(static_cast<const uint32_t*>(nullptr));
        actual.EncodePointer<uint32_t>(0u, 0, true, false);

        ExpectSameBytes("null", actual, stream);
    }

    {
        // The api dump case: the layer recorded a non-null address but never dumped the pointee,
        // as it does for vkCmdPushConstants pValues.
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        const uint32_t value = 99;
        expected.EncodeUInt32Ptr(&value, /*omit_data=*/true);
        actual.EncodePointer<uint32_t>(value, reinterpret_cast<uint64_t>(&value), false, false);

        ExpectSameBytes("non-null, data omitted", actual, stream);
    }
}

/** Arrays, including the count-query idiom where the array pointer is null. */
void TestArrays()
{
    std::printf("arrays\n");

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        const uint32_t values[] = { 1, 2, 3, 4 };
        expected.EncodeUInt32Array(values, 4);
        actual.EncodeArray<uint32_t>(values, 4, reinterpret_cast<uint64_t>(values), false, true);

        ExpectSameBytes("uint32 array", actual, stream);
    }

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        expected.EncodeUInt32Array(nullptr, 0);
        actual.EncodeArray<uint32_t>(static_cast<const uint32_t*>(nullptr), 0, 0, true, false);

        ExpectSameBytes("null array (count query)", actual, stream);
    }

    {
        // Handles widen to 64 bits on the wire even though VkBuffer is a pointer on 64-bit builds.
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        const gfxrecon::format::HandleId ids[] = { 3, 5, 8 };
        expected.EncodeHandleIdArray(ids, 3);
        actual.EncodeHandleIdArray(ids, 3, reinterpret_cast<uint64_t>(ids), false, true);

        ExpectSameBytes("handle id array", actual, stream);
    }
}

/** Struct preambles, single and array. */
void TestStructPreambles()
{
    std::printf("struct preambles\n");

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        VkBufferCreateInfo info{};
        expected.EncodeStructPtrPreamble(&info);
        actual.EncodeStructPtrPreamble(reinterpret_cast<uint64_t>(&info), false, true);

        ExpectSameBytes("struct pointer", actual, stream);
    }

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        expected.EncodeStructPtrPreamble(nullptr);
        actual.EncodeStructPtrPreamble(0, true, false);

        ExpectSameBytes("null struct pointer", actual, stream);
    }

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        VkSubmitInfo submits[2]{};
        expected.EncodeStructArrayPreamble(submits, 2);
        actual.EncodeStructArrayPreamble(2, reinterpret_cast<uint64_t>(submits), false, true);

        ExpectSameBytes("struct array", actual, stream);
    }
}

/** Strings, which always carry their length. */
void TestStrings()
{
    std::printf("strings\n");

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        const char* text = "VK_LAYER_LUNARG_api_dump";
        expected.EncodeString(text);
        actual.EncodeString(text, std::strlen(text), reinterpret_cast<uint64_t>(text), false, true);

        ExpectSameBytes("string", actual, stream);
    }

    {
        gfxrecon::util::MemoryOutputStream stream;
        gfxrecon::encode::ParameterEncoder expected(&stream);
        gfxrecon::decode::ApiDumpEncoder   actual;

        expected.EncodeString(nullptr);
        actual.EncodeString(nullptr, 0, 0, true, false);

        ExpectSameBytes("null string", actual, stream);
    }
}

/** Encodes a whole VkBufferCreateInfo the way the generated adapter will, then decodes it.
 *
 * Byte equality with ParameterEncoder is the real guarantee; this adds an end-to-end check that
 * the bytes actually round trip through the decoder the sqlite consumer is driven by.
 */
void TestStructRoundTrip()
{
    std::printf("VkBufferCreateInfo round trip\n");

    gfxrecon::decode::ApiDumpEncoder actual;

    const uint32_t queue_families[] = { 0, 1 };
    const uint64_t struct_address   = 0x6d59f030d0ull;
    const uint64_t array_address    = 0x6d59f030f0ull;

    actual.EncodeStructPtrPreamble(struct_address, false, true);
    actual.EncodeEnumValue(VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO);
    actual.EncodeStructPtrPreamble(0, true, false); // pNext
    actual.EncodeFlagsValue(static_cast<VkBufferCreateFlags>(0));
    actual.EncodeUInt64Value(208);
    actual.EncodeFlagsValue(
        static_cast<VkBufferUsageFlags>(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
    );
    actual.EncodeEnumValue(VK_SHARING_MODE_CONCURRENT);
    actual.EncodeUInt32Value(2);
    actual.EncodeArray<uint32_t>(queue_families, 2, array_address, false, true);

    // The struct decoders allocate their backing storage from DecodeAllocator, which asserts unless
    // a Begin/End scope is open. FileProcessor opens one per block, so ApiDumpProcessor has to do
    // the same around every call it dispatches.
    //
    // Note the explicit <true>: DecoderAllocGuard defaults to <false>, which is an empty struct
    // that silently guards nothing.
    gfxrecon::decode::DecoderAllocGuard<true> alloc_guard;

    gfxrecon::decode::StructPointerDecoder<gfxrecon::decode::Decoded_VkBufferCreateInfo> decoder;
    const size_t bytes_read = decoder.Decode(actual.GetData(), actual.GetDataSize());

    Expect("consumed the whole buffer", bytes_read == actual.GetDataSize());

    const VkBufferCreateInfo* decoded = decoder.GetPointer();
    Expect("decoded a struct", decoded != nullptr);

    if (decoded != nullptr)
    {
        Expect("sType", decoded->sType == VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO);
        Expect("pNext is null", decoded->pNext == nullptr);
        Expect("size", decoded->size == 208);
        Expect("usage", decoded->usage ==
                            (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT));
        Expect("sharingMode", decoded->sharingMode == VK_SHARING_MODE_CONCURRENT);
        Expect("queueFamilyIndexCount", decoded->queueFamilyIndexCount == 2);
        Expect("pQueueFamilyIndices", (decoded->pQueueFamilyIndices != nullptr) &&
                                          (decoded->pQueueFamilyIndices[0] == 0) &&
                                          (decoded->pQueueFamilyIndices[1] == 1));
    }

    Expect("capture address preserved", decoder.GetAddress() == struct_address);
}

} // namespace

int main()
{
    // Unbuffered so a failing assertion inside the gfxreconstruct decoders does not swallow the
    // progress output that says which check was running.
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    TestValues();
    TestSinglePointers();
    TestArrays();
    TestStructPreambles();
    TestStrings();
    TestStructRoundTrip();

    if (g_failures == 0)
    {
        std::printf("\nApiDumpEncoder matches the gfxreconstruct wire format.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
