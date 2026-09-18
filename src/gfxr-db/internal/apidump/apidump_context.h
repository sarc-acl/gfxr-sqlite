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

#ifndef GFXRECON_DECODE_APIDUMP_CONTEXT_H
#define GFXRECON_DECODE_APIDUMP_CONTEXT_H

#include <cstdint>
#include <string_view>
#include <vector>

#include "apidump_encoder.h"
#include "apidump_enum_lookup.h"
#include "apidump_handle_map.h"
#include "apidump_json.h"
#include "apidump_value_parse.h"

#include "format/format.h"
#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Counters describing what the adapter could not represent faithfully.
 *
 * Reported at the end of a conversion. A clean capture should produce zeros; anything else points
 * at a gap in the generated tables or at a layer option that was not enabled.
 */
struct ApiDumpConversionStats
{
    uint64_t unknown_enum_names{ 0 };
    uint64_t unparsable_scalars{ 0 };
    uint64_t unknown_structure_types{ 0 };
    uint64_t unknown_commands{ 0 };

    /** Placeholders left by optimizing the .apidump (see api-dump-optimize.ts and
     * ApiDumpCall::IsAnnotation), skipped without decoding. Expected to be nonzero for an
     * optimized capture - unlike the other counters here, this is not a sign of anything wrong. */
    uint64_t optimized_commands{ 0 };
};

/** The state the generated encoders thread through a single call.
 *
 * Every method takes an ApiDumpNode and appends its parameter buffer representation. A node that is
 * absent or null encodes as a null pointer rather than failing, because a layer is free to omit
 * anything it did not expand and the gfxreconstruct decoders handle null throughout.
 */
class ApiDumpContext
{
  public:
    ApiDumpContext(ApiDumpEncoder& encoder, ApiDumpHandleMap& handles) : encoder_(encoder), handles_(handles) {}

    ApiDumpEncoder& Encoder() { return encoder_; }

    ApiDumpHandleMap& Handles() { return handles_; }

    const ApiDumpConversionStats& Stats() const { return stats_; }

    ApiDumpConversionStats& MutableStats() { return stats_; }

    /** Reads a count member, for the rare array that is present but was not expanded. */
    size_t Length(const ApiDumpNode& node) const
    {
        uint64_t value = 0;
        if (!node.HasValue() || !ParseUnsigned(node.ValueString(), value))
        {
            return 0;
        }

        return static_cast<size_t>(value);
    }

    //
    // Scalars, pointers to scalars and arrays of scalars.
    //
    // The names match gfxreconstruct's encoder methods so the generator can reuse its type naming
    // unchanged, and so the encoded width stays tied to the name rather than to sizeof, which is
    // what keeps size_t and the Vk basetypes correct.
    //

#define GFXRECON_APIDUMP_SCALAR(NAME, ENCODE_T)                                                              \
    void NAME##Value(const ApiDumpNode& node)                                                                \
    {                                                                                                        \
        encoder_.Encode##NAME##Value(ParseOr<ENCODE_T>(node));                                                \
    }                                                                                                        \
    void NAME##Ptr(const ApiDumpNode& node)                                                                  \
    {                                                                                                        \
        encoder_.EncodePointer<ENCODE_T>(ParseOr<ENCODE_T>(node), node.Address(), node.IsNullPointer(),       \
                                         node.HasData());                                                    \
    }                                                                                                        \
    void NAME##Array(const ApiDumpNode& node, size_t length_hint = 0)                                        \
    {                                                                                                        \
        EncodeScalarArray<ENCODE_T>(node, length_hint);                                                      \
    }

    GFXRECON_APIDUMP_SCALAR(Int8, int8_t)
    GFXRECON_APIDUMP_SCALAR(Int16, int16_t)
    GFXRECON_APIDUMP_SCALAR(Int32, int32_t)
    GFXRECON_APIDUMP_SCALAR(Int64, int64_t)
    GFXRECON_APIDUMP_SCALAR(UInt8, uint8_t)
    GFXRECON_APIDUMP_SCALAR(UInt16, uint16_t)
    GFXRECON_APIDUMP_SCALAR(UInt32, uint32_t)
    GFXRECON_APIDUMP_SCALAR(UInt64, uint64_t)
    GFXRECON_APIDUMP_SCALAR(Float, float)
    GFXRECON_APIDUMP_SCALAR(Double, double)

#undef GFXRECON_APIDUMP_SCALAR

    void SizeTValue(const ApiDumpNode& node) { encoder_.EncodeSizeTValue(ParseOr<uint64_t>(node)); }

    void SizeTPtr(const ApiDumpNode& node)
    {
        encoder_.EncodePointer<format::SizeTEncodeType>(
            ParseOr<uint64_t>(node), node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    void SizeTArray(const ApiDumpNode& node, size_t length_hint = 0)
    {
        EncodeScalarArray<format::SizeTEncodeType>(node, length_hint);
    }

    /** An opaque pointer, recorded as an address with no contents. */
    void VoidPtrValue(const ApiDumpNode& node) { encoder_.EncodeVoidPtrValue(node.Address()); }

    void FunctionPtrValue(const ApiDumpNode& node) { encoder_.EncodeVoidPtrValue(node.Address()); }

    //
    // Enums and bitmasks.
    //

    /** Encodes an enum, resolving the recorded name through the generated table.
     *
     * The layer writes a bare name unless show_enum_value is on, in which case the value arrives
     * with a leading integer that is taken directly. Both spellings are accepted so a database can
     * be built from captures taken either way.
     */
    template <typename T>
    void EnumValue(const ApiDumpNode& node, bool (*parse)(std::string_view, T&))
    {
        encoder_.EncodeEnumValue(ResolveEnum(node, parse));
    }

    template <typename T>
    void EnumPtr(const ApiDumpNode& node, bool (*parse)(std::string_view, T&))
    {
        encoder_.EncodePointer<format::EnumEncodeType>(
            static_cast<format::EnumEncodeType>(ResolveEnum(node, parse)),
            node.Address(),
            node.IsNullPointer(),
            node.HasData()
        );
    }

    template <typename T>
    void EnumArray(const ApiDumpNode& node, bool (*parse)(std::string_view, T&), size_t length_hint = 0)
    {
        const size_t count = ArrayLength(node, length_hint);
        std::vector<format::EnumEncodeType> values;
        values.reserve(count);

        for (size_t i = 0; i < node.ElementCount(); ++i)
        {
            values.push_back(static_cast<format::EnumEncodeType>(ResolveEnumText(node.ElementScalar(i), parse)));
        }

        values.resize(count);
        encoder_.EncodeArray<format::EnumEncodeType>(
            values.data(), count, node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    /** A 32 bit bitmask whose bits enum is known, so names can be resolved when there is no number. */
    template <typename BitsT>
    void FlagsValue(const ApiDumpNode& node, bool (*parse)(std::string_view, BitsT&))
    {
        encoder_.EncodeFlagsValue(ResolveFlags(node, parse));
    }

    /** A 32 bit bitmask with no bits enum, which is always recorded numerically. */
    void FlagsValue(const ApiDumpNode& node) { encoder_.EncodeFlagsValue(ParseOr<uint32_t>(node)); }

    template <typename BitsT>
    void FlagsArray(const ApiDumpNode& node, bool (*parse)(std::string_view, BitsT&), size_t length_hint = 0)
    {
        const size_t                         count = ArrayLength(node, length_hint);
        std::vector<format::FlagsEncodeType> values;
        values.reserve(count);

        for (size_t i = 0; i < node.ElementCount(); ++i)
        {
            values.push_back(static_cast<format::FlagsEncodeType>(ResolveFlagsText(node.ElementScalar(i), parse)));
        }

        values.resize(count);
        encoder_.EncodeArray<format::FlagsEncodeType>(
            values.data(), count, node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    void FlagsArray(const ApiDumpNode& node, size_t length_hint = 0)
    {
        EncodeScalarArray<format::FlagsEncodeType>(node, length_hint);
    }

    template <typename BitsT>
    void Flags64Value(const ApiDumpNode& node, bool (*parse)(std::string_view, BitsT&))
    {
        encoder_.EncodeFlags64Value(ResolveFlags64(node, parse));
    }

    void Flags64Value(const ApiDumpNode& node) { encoder_.EncodeFlags64Value(ParseOr<uint64_t>(node)); }

    //
    // Handles.
    //

    /** An input handle: resolved through the map, allocating an id if never seen. */
    void VulkanHandleValue(const ApiDumpNode& node, VkObjectType type)
    {
        encoder_.EncodeHandleIdValue(handles_.Get(type, HandleAddress(node)));
    }

    /** An output handle from a create or allocate, which always starts a new identity. */
    void VulkanHandleCreatedPtr(const ApiDumpNode& node, VkObjectType type)
    {
        encoder_.EncodeHandleIdPointer(
            handles_.Create(type, HandleAddress(node)), node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    /** An output handle from a getter, where repeat calls must resolve to the same identity. */
    void VulkanHandleRetrievedPtr(const ApiDumpNode& node, VkObjectType type)
    {
        encoder_.EncodeHandleIdPointer(
            handles_.Get(type, HandleAddress(node)), node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    void VulkanHandlePtr(const ApiDumpNode& node, VkObjectType type)
    {
        encoder_.EncodeHandleIdPointer(
            handles_.Get(type, HandleAddress(node)), node.Address(), node.IsNullPointer(), node.HasData()
        );
    }

    void VulkanHandleArray(const ApiDumpNode& node, VkObjectType type, size_t length_hint = 0)
    {
        EncodeHandleArray(node, type, length_hint, false);
    }

    void VulkanHandleCreatedArray(const ApiDumpNode& node, VkObjectType type, size_t length_hint = 0)
    {
        EncodeHandleArray(node, type, length_hint, true);
    }

    /** Drops the identity of a destroyed or freed handle so a recycled address starts fresh. */
    void ReleaseHandle(const ApiDumpNode& node, VkObjectType type) { handles_.Release(type, HandleAddress(node)); }

    void ReleaseHandleArray(const ApiDumpNode& node, VkObjectType type)
    {
        for (size_t i = 0; i < node.ElementCount(); ++i)
        {
            handles_.Release(type, HandleAddress(node.ElementAt(i)));
        }
    }

    //
    // Strings.
    //

    void StringValue(const ApiDumpNode& node)
    {
        const std::string_view text = node.ValueString();
        encoder_.EncodeString(text.data(), text.size(), node.Address(), node.IsNullPointer(), node.HasData());
    }

    void StringArray(const ApiDumpNode& node, size_t length_hint = 0)
    {
        const bool   is_null  = node.IsNullPointer();
        const bool   has_data = node.HasData();
        const size_t count    = ArrayLength(node, length_hint);

        encoder_.EncodeStringArrayPreamble(count, node.Address(), is_null, has_data);

        // The elements follow only when the array carries data, matching
        // ParameterEncoder::EncodeBasicStringArray. Writing them unconditionally would desynchronise
        // the buffer for an array the layer recorded but did not expand, which is what
        // VkLayerSettingEXT pValues looks like in a real capture.
        if (is_null || !has_data)
        {
            return;
        }

        for (size_t i = 0; i < count; ++i)
        {
            const ApiDumpNode      element = node.ElementAt(i);
            const std::string_view text    = element.IsPresent() ? node.ElementScalar(i) : std::string_view{};
            encoder_.EncodeString(
                text.data(), text.size(), element.Address(), !element.IsPresent(), element.IsPresent()
            );
        }
    }

  private:
    /** How many elements to encode: the expanded count when there is one, else the declared count. */
    size_t ArrayLength(const ApiDumpNode& node, size_t length_hint) const
    {
        const size_t expanded = node.ElementCount();
        return (expanded > 0) ? expanded : length_hint;
    }

    uint64_t HandleAddress(const ApiDumpNode& node) const
    {
        uint64_t value = 0;
        if (!ParseUnsigned(node.ValueString(), value))
        {
            return 0;
        }

        return value;
    }

    template <typename T>
    T ParseOr(const ApiDumpNode& node)
    {
        T value{};
        if (!node.HasValue())
        {
            return value;
        }

        if (!ParseScalar<T>(node.ValueString(), value))
        {
            ++stats_.unparsable_scalars;
        }

        return value;
    }

    template <typename T>
    void EncodeScalarArray(const ApiDumpNode& node, size_t length_hint)
    {
        const size_t   count = ArrayLength(node, length_hint);
        std::vector<T> values;
        values.reserve(count);

        for (size_t i = 0; i < node.ElementCount(); ++i)
        {
            T value{};
            if (!ParseScalar<T>(node.ElementScalar(i), value))
            {
                ++stats_.unparsable_scalars;
            }
            values.push_back(value);
        }

        // A present but unexpanded array still has to carry its length, so pad rather than shorten.
        values.resize(count);
        encoder_.EncodeArray<T>(values.data(), count, node.Address(), node.IsNullPointer(), node.HasData());
    }

    void EncodeHandleArray(const ApiDumpNode& node, VkObjectType type, size_t length_hint, bool created)
    {
        const size_t                  count = ArrayLength(node, length_hint);
        std::vector<format::HandleId> ids;
        ids.reserve(count);

        for (size_t i = 0; i < node.ElementCount(); ++i)
        {
            const uint64_t address = HandleAddress(node.ElementAt(i));
            ids.push_back(created ? handles_.Create(type, address) : handles_.Get(type, address));
        }

        ids.resize(count);
        encoder_.EncodeHandleIdArray(ids.data(), count, node.Address(), node.IsNullPointer(), node.HasData());
    }

    template <typename T>
    T ResolveEnum(const ApiDumpNode& node, bool (*parse)(std::string_view, T&))
    {
        return ResolveEnumText(node.ValueString(), parse);
    }

    template <typename T>
    T ResolveEnumText(std::string_view text, bool (*parse)(std::string_view, T&))
    {
        T value{};

        // A leading digit means the layer emitted the number, which is exact and needs no table.
        // Parsed as signed because enum values can be negative: every VkResult error code is, so
        // reading them as unsigned would fail the parse and fall through to the name table with a
        // string that is not a name, quietly yielding 0, which is VK_SUCCESS.
        int64_t numeric = 0;
        if (ParseLeadingSigned(text, numeric))
        {
            value = static_cast<T>(numeric);
            return value;
        }

        if (!text.empty() && !parse(text, value))
        {
            ++stats_.unknown_enum_names;
        }

        return value;
    }

    template <typename BitsT>
    uint32_t ResolveFlags(const ApiDumpNode& node, bool (*parse)(std::string_view, BitsT&))
    {
        return static_cast<uint32_t>(ResolveFlagsText(node.ValueString(), parse));
    }

    template <typename BitsT>
    uint64_t ResolveFlags64(const ApiDumpNode& node, bool (*parse)(std::string_view, BitsT&))
    {
        return ResolveFlagsText(node.ValueString(), parse);
    }

    /** Resolves a bitmask, which is written as "130 (NAME | NAME)" or occasionally as names alone. */
    template <typename BitsT>
    uint64_t ResolveFlagsText(std::string_view text, bool (*parse)(std::string_view, BitsT&))
    {
        uint64_t numeric = 0;
        if (ParseLeadingUnsigned(text, numeric))
        {
            return numeric;
        }

        uint64_t combined = 0;
        size_t   start    = 0;

        while (start <= text.size())
        {
            size_t end = text.find('|', start);
            if (end == std::string_view::npos)
            {
                end = text.size();
            }

            std::string_view token = text.substr(start, end - start);
            while (!token.empty() && ((token.front() == ' ') || (token.front() == '\t')))
            {
                token.remove_prefix(1);
            }
            while (!token.empty() && ((token.back() == ' ') || (token.back() == '\t')))
            {
                token.remove_suffix(1);
            }

            if (!token.empty())
            {
                BitsT bit{};
                if (parse(token, bit))
                {
                    combined |= static_cast<uint64_t>(bit);
                }
                else
                {
                    ++stats_.unknown_enum_names;
                }
            }

            if (end == text.size())
            {
                break;
            }

            start = end + 1;
        }

        return combined;
    }

    ApiDumpEncoder&        encoder_;
    ApiDumpHandleMap&      handles_;
    ApiDumpConversionStats stats_;
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_CONTEXT_H
