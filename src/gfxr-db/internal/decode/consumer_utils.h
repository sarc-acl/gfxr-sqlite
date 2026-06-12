/*
** Copyright (c) 2024 The Sokatoa Authors
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
*/
#ifndef GFXRECON_DECODE_CONSUMER_UTILS_H
#define GFXRECON_DECODE_CONSUMER_UTILS_H

#include "sqlite_utils.h"

#include "format/format.h"
#include "encode/vulkan_handle_wrapper_util.h"

#include <sstream>
#include <iomanip>
#include <stdint.h>
#include <string>

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

inline std::string AnnotationTypeToString(const format::AnnotationType& type)
{
    std::string str;
    switch (type)
    {
        case format::AnnotationType::kUnknown:
            str.assign("kUnknown");
            break;
        case format::AnnotationType::kText:
            str.assign("kText");
            break;
        case format::AnnotationType::kJson:
            str.assign("kJson");
            break;
        case format::AnnotationType::kXml:
            str.assign("kXml");
            break;
        default:
            str.assign("OUT_OF_RANGE_ERROR");
            GFXRECON_SQLITE_LOG_WARNING(
                "format::AnnotationType with out of range value: %lu", static_cast<long unsigned>(type)
            );
            break;
    }
    return str;
}

inline std::string UUIDToString(uint32_t size, const uint8_t* uuid)
{
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex;
    for (size_t i = 0; i < size; ++i)
    {
        stream << (uint32_t)uuid[i];
    }
    return stream.str();
}

/**
 * Sqlite does not support unsigned 64 bit values, and gfxreconstruct uses some known
 * constants that are at the top of the uint64 value range.
 * This function checks for those known values (skipping the warning in these cases)
 * and produce a warning if the handle value is outside of the range.
 * The resulting value will be negative if the value is outside of int64 max range
 * regardless of if it matches one of the known constants or not.
 * Values under the int64 max range will remain the same.
 */
inline int64_t ToInt64(const gfxrecon::format::HandleId handle)
{
    if (handle != gfxrecon::encode::vulkan_wrappers::kTempQueueId &&
        handle != gfxrecon::encode::vulkan_wrappers::kTempCommandPoolId &&
        handle != gfxrecon::encode::vulkan_wrappers::kTempCommandBufferId)
    {
        if (handle > static_cast<uint64_t>(std::numeric_limits<int64_t>::max()))
        {
            GFXRECON_SQLITE_LOG_WARNING(
                "HandleId value %" PRIu64
                " greater than Sqlite supported signed int64; will be converted to a negative value",
                handle
            );
        }
    }
    return static_cast<int64_t>(handle);
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_CONSUMER_UTILS_H
