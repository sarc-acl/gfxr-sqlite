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

#ifndef GFXRECON_DECODE_APIDUMP_ENUM_LOOKUP_H
#define GFXRECON_DECODE_APIDUMP_ENUM_LOOKUP_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <utility>

#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Runtime support for the generated enum name lookups.
 *
 * An api dump records enums by name only unless the layer was run with show_enum_value, so the
 * adapter needs the inverse of gfxreconstruct's enum-to-string tables. The generated tables are
 * sorted by name at generation time and searched here, rather than being loaded into hash maps:
 * Vulkan has tens of thousands of enumerants across ~1600 enums, and this library is linked into a
 * Node addon where that much static initialisation would be paid on every process start.
 */
template <typename T, size_t N>
bool LookupEnumName(const std::pair<std::string_view, T> (&table)[N], std::string_view name, T& out)
{
    const auto* end   = table + N;
    const auto* found = std::lower_bound(
        table,
        end,
        name,
        [](const std::pair<std::string_view, T>& entry, std::string_view key) { return entry.first < key; }
    );

    if ((found == end) || (found->first != name))
    {
        return false;
    }

    out = found->second;
    return true;
}

/** Reads the leading integer of an api dump value string.
 *
 * Bitmasks are always dumped as "130 (VK_BUFFER_USAGE_TRANSFER_DST_BIT | ...)", and enums gain the
 * same leading integer when the layer runs with show_enum_value, so a leading digit is the fast and
 * exact path for both. Returns false when the value starts with a name instead, which is when the
 * generated name tables are consulted.
 */
inline bool ParseLeadingSigned(std::string_view text, int64_t& out)
{
    size_t index = 0;
    while ((index < text.size()) && ((text[index] == ' ') || (text[index] == '\t')))
    {
        ++index;
    }

    bool negative = false;
    if ((index < text.size()) && ((text[index] == '-') || (text[index] == '+')))
    {
        negative = (text[index] == '-');
        ++index;
    }

    const size_t first_digit = index;
    uint64_t     magnitude   = 0;

    while ((index < text.size()) && (text[index] >= '0') && (text[index] <= '9'))
    {
        magnitude = (magnitude * 10) + static_cast<uint64_t>(text[index] - '0');
        ++index;
    }

    if (index == first_digit)
    {
        return false;
    }

    out = negative ? -static_cast<int64_t>(magnitude) : static_cast<int64_t>(magnitude);
    return true;
}

inline bool ParseLeadingUnsigned(std::string_view text, uint64_t& out)
{
    size_t index = 0;
    while ((index < text.size()) && ((text[index] == ' ') || (text[index] == '\t')))
    {
        ++index;
    }

    const size_t first_digit = index;
    uint64_t     value       = 0;

    while ((index < text.size()) && (text[index] >= '0') && (text[index] <= '9'))
    {
        value = (value * 10) + static_cast<uint64_t>(text[index] - '0');
        ++index;
    }

    if (index == first_digit)
    {
        return false;
    }

    out = value;
    return true;
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_ENUM_LOOKUP_H
