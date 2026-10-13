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

#include "apidump_value_parse.h"

#include <cstdlib>
#include <string>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace
{

std::string_view TrimLeadingSpace(std::string_view text)
{
    size_t index = 0;
    while ((index < text.size()) && ((text[index] == ' ') || (text[index] == '\t')))
    {
        ++index;
    }

    return text.substr(index);
}

bool ParseHexDigits(std::string_view text, uint64_t& out)
{
    uint64_t value = 0;
    size_t   index = 0;

    for (; index < text.size(); ++index)
    {
        const char c = text[index];
        uint64_t   digit;

        if ((c >= '0') && (c <= '9'))
        {
            digit = static_cast<uint64_t>(c - '0');
        }
        else if ((c >= 'a') && (c <= 'f'))
        {
            digit = static_cast<uint64_t>(c - 'a') + 10;
        }
        else if ((c >= 'A') && (c <= 'F'))
        {
            digit = static_cast<uint64_t>(c - 'A') + 10;
        }
        else
        {
            break;
        }

        value = (value * 16) + digit;
    }

    if (index == 0)
    {
        return false;
    }

    out = value;
    return true;
}

bool ParseDecimalDigits(std::string_view text, uint64_t& out)
{
    uint64_t value = 0;
    size_t   index = 0;

    for (; index < text.size(); ++index)
    {
        const char c = text[index];
        if ((c < '0') || (c > '9'))
        {
            break;
        }

        value = (value * 10) + static_cast<uint64_t>(c - '0');
    }

    if (index == 0)
    {
        return false;
    }

    out = value;
    return true;
}

bool HasPrefixIgnoringCase(std::string_view text, std::string_view prefix)
{
    if (text.size() < prefix.size())
    {
        return false;
    }

    for (size_t i = 0; i < prefix.size(); ++i)
    {
        const char a = (text[i] >= 'A' && text[i] <= 'Z') ? static_cast<char>(text[i] + 32) : text[i];
        if (a != prefix[i])
        {
            return false;
        }
    }

    return true;
}

} // namespace

bool ParseUnsigned(std::string_view text, uint64_t& out)
{
    const std::string_view trimmed = TrimLeadingSpace(text);

    if (HasPrefixIgnoringCase(trimmed, "0x"))
    {
        return ParseHexDigits(trimmed.substr(2), out);
    }

    return ParseDecimalDigits(trimmed, out);
}

bool ParseSigned(std::string_view text, int64_t& out)
{
    std::string_view trimmed  = TrimLeadingSpace(text);
    bool             negative = false;

    if (!trimmed.empty() && ((trimmed[0] == '-') || (trimmed[0] == '+')))
    {
        negative = (trimmed[0] == '-');
        trimmed  = trimmed.substr(1);
    }

    uint64_t magnitude = 0;
    if (!ParseUnsigned(trimmed, magnitude))
    {
        return false;
    }

    // Cast before negating so that the most negative value of the target width round trips rather
    // than overflowing a positive int64_t.
    out = negative ? static_cast<int64_t>(0ull - magnitude) : static_cast<int64_t>(magnitude);
    return true;
}

bool ParseDouble(std::string_view text, double& out)
{
    const std::string_view trimmed = TrimLeadingSpace(text);
    if (trimmed.empty())
    {
        return false;
    }

    // strtod needs a terminated buffer, and the recorded text is short enough that copying it is
    // not worth avoiding. It handles nan, inf and hex floats, all of which an ostream can produce.
    const std::string terminated(trimmed);

    char*        end   = nullptr;
    const double value = std::strtod(terminated.c_str(), &end);

    if (end == terminated.c_str())
    {
        return false;
    }

    out = value;
    return true;
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
