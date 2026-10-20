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

#ifndef GFXRECON_DECODE_APIDUMP_STRUCT_ENCODE_H
#define GFXRECON_DECODE_APIDUMP_STRUCT_ENCODE_H

#include <cstddef>

#include "apidump_context.h"
#include "apidump_json.h"

#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Writes the body of one struct into the parameter buffer.
 *
 * Specialised per struct by generated_vulkan_struct_from_apidump.cpp, and by hand in
 * custom_vulkan_struct_from_apidump.cpp for the structs and unions gfxreconstruct also hand writes.
 *
 * Declared but not defined, so a struct that has neither a generated nor a hand written
 * specialisation is a link error rather than silently encoding nothing.
 */
template <typename T>
void StructFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value);

/** Encodes the pNext chain hanging off a struct. Generated from the registry. */
void PNextFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value);

/** Mirrors gfxreconstruct's EncodeStructPtr: preamble, then the body when there is data. */
template <typename T>
void StructPtrFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value)
{
    const bool is_null  = value.IsNullPointer();
    const bool has_data = value.HasData();

    ctx.Encoder().EncodeStructPtrPreamble(value.Address(), is_null, has_data);

    if (!is_null && has_data)
    {
        StructFromApiDump<T>(ctx, value);
    }
}

/** Mirrors gfxreconstruct's EncodeStructArray.
 *
 * The element count comes from the expanded elements when the layer wrote them, falling back to a
 * declared count member for the rare array that is present but was not expanded. The preamble
 * carries the count either way, matching EncodeStructArrayPreamble, which writes the length even
 * when the data is omitted.
 */
template <typename T>
void StructArrayFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value, size_t length_hint = 0)
{
    const bool   is_null  = value.IsNullPointer();
    const bool   has_data = value.HasData();
    const size_t expanded = value.ElementCount();
    const size_t count    = (expanded > 0) ? expanded : length_hint;

    ctx.Encoder().EncodeStructArrayPreamble(count, value.Address(), is_null, has_data);

    if (!is_null && has_data && (count > 0))
    {
        for (size_t i = 0; i < expanded; ++i)
        {
            StructFromApiDump<T>(ctx, value.ElementAt(i));
        }
    }
}

/** Mirrors gfxreconstruct's EncodeStructArray2D, for an array of pointers to structs such as
 * VkAccelerationStructureBuildGeometryInfoKHR ppGeometries or vkCmdBuildAccelerationStructuresKHR
 * ppBuildRangeInfos. StructPointerDecoder<T*> asserts the kIsArray2D attribute, so these must not be
 * encoded as a plain struct array.
 *
 * The layer writes each element as a struct pointer: its address and, when it followed it, the
 * members of the one struct it points to - or an elements list, should it ever write more. It never
 * writes the inner count the registry declares (a range info array holds pInfos[i].geometryCount
 * entries, but only the first is dumped). So each inner array is encoded with the number of structs
 * actually recorded: StructPointerDecoder<T*> reads an inner array's count and then exactly that many
 * structs, whatever kHasData says, and must never be told of more than are written.
 */
template <typename T>
void StructArray2DFromApiDump(ApiDumpContext& ctx, const ApiDumpNode& value, size_t length_hint = 0)
{
    const bool   is_null  = value.IsNullPointer();
    const bool   has_data = value.HasData();
    const size_t expanded = value.ElementCount();
    const size_t count    = (expanded > 0) ? expanded : length_hint;

    ctx.Encoder().EncodeStructArray2DPreamble(count, value.Address(), is_null, has_data);

    if (is_null || !has_data)
    {
        return;
    }

    for (size_t i = 0; i < count; ++i)
    {
        // Absent, and so a null pointer, past the elements the layer recorded.
        const ApiDumpNode inner = value.ElementAt(i);

        if (inner.HasElements())
        {
            const size_t inner_count = inner.ElementCount();
            ctx.Encoder().EncodeStructArrayPreamble(inner_count, inner.Address(), false, true);
            for (size_t j = 0; j < inner_count; ++j)
            {
                StructFromApiDump<T>(ctx, inner.ElementAt(j));
            }
        }
        else if (inner.HasMembers())
        {
            ctx.Encoder().EncodeStructArrayPreamble(1, inner.Address(), false, true);
            StructFromApiDump<T>(ctx, inner);
        }
        else
        {
            // Null, or a pointer the layer did not follow: no structs, so a count of zero.
            ctx.Encoder().EncodeStructArrayPreamble(0, inner.Address(), inner.IsNullPointer(), false);
        }
    }
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_STRUCT_ENCODE_H
