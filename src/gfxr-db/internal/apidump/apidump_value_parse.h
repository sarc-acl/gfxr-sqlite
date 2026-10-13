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

#ifndef GFXRECON_DECODE_APIDUMP_VALUE_PARSE_H
#define GFXRECON_DECODE_APIDUMP_VALUE_PARSE_H

#include <cstdint>
#include <string_view>
#include <type_traits>

#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Scalar parsing for api dump value strings.
 *
 * Every scalar in an api dump is written as text: integers in decimal, handles and some pointers in
 * hex, floats through the layer's ostream. Bitmasks and, with show_enum_value, enums carry a
 * trailing " (NAME | NAME)" after the number, which these parsers stop at rather than reject.
 */

/** Parses an unsigned integer, accepting a 0x prefix. Stops at the first character that does not
 *  belong, so a bitmask's trailing names are ignored. */
bool ParseUnsigned(std::string_view text, uint64_t& out);

/** Parses a signed integer, accepting a leading '-' and a 0x prefix. */
bool ParseSigned(std::string_view text, int64_t& out);

/** Parses a floating point value, accepting nan and inf spellings. */
bool ParseDouble(std::string_view text, double& out);

/** Parses whichever of the above suits T, narrowing to T afterwards.
 *
 * Narrowing rather than range checking is deliberate: the value came from a real API call, so a
 * value that does not fit means the recorded text is wrong, and reproducing the same truncation the
 * driver saw is more useful than substituting a zero.
 */
template <typename T>
bool ParseScalar(std::string_view text, T& out)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        double value = 0.0;
        if (!ParseDouble(text, value))
        {
            return false;
        }
        out = static_cast<T>(value);
        return true;
    }
    else if constexpr (std::is_signed_v<T>)
    {
        int64_t value = 0;
        if (!ParseSigned(text, value))
        {
            return false;
        }
        out = static_cast<T>(value);
        return true;
    }
    else
    {
        uint64_t value = 0;
        if (!ParseUnsigned(text, value))
        {
            return false;
        }
        out = static_cast<T>(value);
        return true;
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_VALUE_PARSE_H
