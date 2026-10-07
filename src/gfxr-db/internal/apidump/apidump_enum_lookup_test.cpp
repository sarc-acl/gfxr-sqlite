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

/** Checks the generated enum name tables resolve the spellings an api dump actually contains.
 *
 * The tables are sorted by the generator and binary searched at runtime, so the two orderings have
 * to agree. They do only because Vulkan enumerant spellings are ASCII, where Python's code point
 * ordering and std::string_view's byte ordering coincide. VkFormat is the interesting case: it
 * mixes digits, underscores and a lowercase x in names like VK_FORMAT_ASTC_10x10_SRGB_BLOCK, so a
 * disagreement between the two orderings would show up there first.
 */

#include <cstdio>
#include <string_view>

#include "apidump_enum_lookup.h"
#include "generated_vulkan_enum_from_string.h"

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

template <typename T>
void ExpectEnum(const char* name, bool (*parse)(std::string_view, T&), T want)
{
    T got{};
    const bool found = parse(name, got);
    Expect(name, found && (got == want));
}

void TestPlainEnums()
{
    std::printf("plain enums\n");

    ExpectEnum("VK_SHARING_MODE_EXCLUSIVE", EnumFromString_VkSharingMode, VK_SHARING_MODE_EXCLUSIVE);
    ExpectEnum("VK_SHARING_MODE_CONCURRENT", EnumFromString_VkSharingMode, VK_SHARING_MODE_CONCURRENT);
    ExpectEnum("VK_IMAGE_LAYOUT_UNDEFINED", EnumFromString_VkImageLayout, VK_IMAGE_LAYOUT_UNDEFINED);
    ExpectEnum("VK_INDEX_TYPE_UINT32", EnumFromString_VkIndexType, VK_INDEX_TYPE_UINT32);
    ExpectEnum("VK_SUCCESS", EnumFromString_VkResult, VK_SUCCESS);
    ExpectEnum("VK_ERROR_DEVICE_LOST", EnumFromString_VkResult, VK_ERROR_DEVICE_LOST);
}

/** VkFormat is the large, ordering-sensitive table. */
void TestFormatOrdering()
{
    std::printf("VkFormat ordering\n");

    ExpectEnum("VK_FORMAT_UNDEFINED", EnumFromString_VkFormat, VK_FORMAT_UNDEFINED);
    ExpectEnum("VK_FORMAT_R8G8B8A8_UNORM", EnumFromString_VkFormat, VK_FORMAT_R8G8B8A8_UNORM);
    ExpectEnum("VK_FORMAT_D32_SFLOAT_S8_UINT", EnumFromString_VkFormat, VK_FORMAT_D32_SFLOAT_S8_UINT);
    ExpectEnum("VK_FORMAT_ASTC_10x10_SRGB_BLOCK", EnumFromString_VkFormat, VK_FORMAT_ASTC_10x10_SRGB_BLOCK);
    ExpectEnum("VK_FORMAT_ASTC_10x5_UNORM_BLOCK", EnumFromString_VkFormat, VK_FORMAT_ASTC_10x5_UNORM_BLOCK);
    ExpectEnum("VK_FORMAT_ASTC_4x4_UNORM_BLOCK", EnumFromString_VkFormat, VK_FORMAT_ASTC_4x4_UNORM_BLOCK);
    ExpectEnum("VK_FORMAT_BC7_SRGB_BLOCK", EnumFromString_VkFormat, VK_FORMAT_BC7_SRGB_BLOCK);
}

/** The alias spellings the base generator drops, which the layer may well be the one to print. */
void TestAliases()
{
    std::printf("alias spellings\n");

    ExpectEnum(
        "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
    );
    ExpectEnum(
        "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2
    );

    // The sample capture dumps this one by its promoted spelling and this one by its extension
    // spelling, so both have to resolve.
    ExpectEnum(
        "VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO
    );
    ExpectEnum(
        "VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO_KHR",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO
    );
}

/** sTypes taken verbatim from the sample .apidump, the ones the pNext dispatch will hit. */
void TestSampleCaptureStructureTypes()
{
    std::printf("structure types from the sample capture\n");

    ExpectEnum(
        "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO
    );
    ExpectEnum(
        "VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT
    );
    ExpectEnum(
        "VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO
    );
    ExpectEnum(
        "VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT",
        EnumFromString_VkStructureType,
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT
    );
}

void TestUnknownNames()
{
    std::printf("unknown names\n");

    VkFormat format{};
    Expect("unknown name rejected", !EnumFromString_VkFormat("VK_FORMAT_NOT_A_REAL_FORMAT", format));
    Expect("empty name rejected", !EnumFromString_VkFormat("", format));

    // A prefix of a real name must not match: binary search has to compare the whole string.
    Expect("prefix rejected", !EnumFromString_VkFormat("VK_FORMAT_R8G8B8A8_UNOR", format));
}

/** The numeric fast path, used for bitmasks and for enums under the show_enum_value layer option. */
void TestLeadingUnsigned()
{
    std::printf("leading integer parse\n");

    uint64_t value = 0;

    Expect(
        "bitmask with names",
        ParseLeadingUnsigned("130 (VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)", value) &&
            (value == 130)
    );

    Expect("bare zero", ParseLeadingUnsigned("0", value) && (value == 0));
    Expect("plain integer", ParseLeadingUnsigned("4096", value) && (value == 4096));
    Expect("name only is not numeric", !ParseLeadingUnsigned("VK_SHARING_MODE_EXCLUSIVE", value));
    Expect("empty is not numeric", !ParseLeadingUnsigned("", value));
}

/** The signed numeric path, which enums need and bitmasks do not.
 *
 * Every VkResult error code is negative. Reading the numeric form as unsigned would fail the parse,
 * fall through to the name table with a string that is not a name, and quietly yield 0, which is
 * VK_SUCCESS: a failed call would be recorded as a successful one. Nothing exercises this until the
 * layer runs with show_enum_value, which is exactly why it is pinned down here.
 */
void TestLeadingSigned()
{
    std::printf("leading signed integer parse\n");

    int64_t value = 0;

    Expect("negative", ParseLeadingSigned("-4", value) && (value == -4));
    Expect("negative maps to the right enum",
           ParseLeadingSigned("-4", value) && (static_cast<VkResult>(value) == VK_ERROR_DEVICE_LOST));
    Expect("out of host memory", ParseLeadingSigned("-1", value) &&
                                     (static_cast<VkResult>(value) == VK_ERROR_OUT_OF_HOST_MEMORY));
    Expect("positive", ParseLeadingSigned("12", value) && (value == 12));
    Expect("explicit plus", ParseLeadingSigned("+7", value) && (value == 7));
    Expect("zero", ParseLeadingSigned("0", value) && (value == 0));
    Expect("large extension value", ParseLeadingSigned("1000156000", value) && (value == 1000156000));
    Expect("name is not numeric", !ParseLeadingSigned("VK_ERROR_DEVICE_LOST", value));
    Expect("lone minus is not numeric", !ParseLeadingSigned("-", value));
    Expect("empty is not numeric", !ParseLeadingSigned("", value));
}

} // namespace

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    TestPlainEnums();
    TestFormatOrdering();
    TestAliases();
    TestSampleCaptureStructureTypes();
    TestUnknownNames();
    TestLeadingUnsigned();
    TestLeadingSigned();

    if (g_failures == 0)
    {
        std::printf("\nGenerated enum name tables resolve correctly.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
