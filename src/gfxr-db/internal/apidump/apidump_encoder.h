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

#ifndef GFXRECON_DECODE_APIDUMP_ENCODER_H
#define GFXRECON_DECODE_APIDUMP_ENCODER_H

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "format/format.h"
#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Writes gfxreconstruct parameter buffers from api dump JSON.
 *
 * This is a deliberate re-implementation of the subset of `gfxrecon::encode::ParameterEncoder` that
 * the api dump adapter needs, rather than a use of it. `encode/parameter_encoder.h` includes
 * `encode/vulkan_handle_wrapper_util.h` under GFXRECON_ENABLE_VULKAN, which pulls capture side
 * state (including a file scope `VulkanStateHandleTable`) into what is otherwise a decode only
 * library. gfxr-sqlite does not define GFXRECON_ENABLE_VULKAN, so it would not even compile the
 * same variant of that header as the gfxreconstruct libraries it links against.
 *
 * The other reason is the shape of the API. ParameterEncoder derives both the encoded capture
 * address and the null-ness of every pointer from a live C++ pointer, which the adapter does not
 * have: an api dump records the capture address as a string alongside the data. So every pointer,
 * array and string primitive here takes the capture address and a has_data flag explicitly.
 *
 * The byte layout must match ParameterEncoder exactly or the gfxreconstruct decoders will
 * mis-parse it. The encoder round trip tests replay each primitive through the real generated
 * decoders to keep the two from drifting.
 */
class ApiDumpEncoder
{
  public:
    void Reset() { buffer_.clear(); }

    const uint8_t* GetData() const { return buffer_.data(); }

    size_t GetDataSize() const { return buffer_.size(); }

    //
    // Values. These mirror the ParameterEncoder Encode*Value overloads.
    //

    void EncodeInt8Value(int8_t value) { WriteValue(value); }
    void EncodeUInt8Value(uint8_t value) { WriteValue(value); }
    void EncodeInt16Value(int16_t value) { WriteValue(value); }
    void EncodeUInt16Value(uint16_t value) { WriteValue(value); }
    void EncodeInt32Value(int32_t value) { WriteValue(value); }
    void EncodeUInt32Value(uint32_t value) { WriteValue(value); }
    void EncodeInt64Value(int64_t value) { WriteValue(value); }
    void EncodeUInt64Value(uint64_t value) { WriteValue(value); }
    void EncodeFloatValue(float value) { WriteValue(value); }
    void EncodeDoubleValue(double value) { WriteValue(value); }

    void EncodeSizeTValue(size_t value) { WriteValue(static_cast<format::SizeTEncodeType>(value)); }
    void EncodeHandleIdValue(format::HandleId value) { WriteValue(static_cast<format::HandleEncodeType>(value)); }
    void EncodeAddressValue(uint64_t value) { WriteValue(static_cast<format::AddressEncodeType>(value)); }
    void EncodeVoidPtrValue(uint64_t value) { EncodeAddressValue(value); }

    template <typename T>
    void EncodeEnumValue(T value)
    {
        WriteValue(static_cast<format::EnumEncodeType>(value));
    }

    template <typename T>
    void EncodeFlagsValue(T value)
    {
        WriteValue(static_cast<format::FlagsEncodeType>(value));
    }

    template <typename T>
    void EncodeFlags64Value(T value)
    {
        WriteValue(static_cast<format::Flags64EncodeType>(value));
    }

    //
    // Pointers to a single value.
    //
    // `address` is the capture address; 0 means "not recorded", which clears kHasAddress. Pass
    // is_null when the api dump showed no pointee at all, and has_data false when it recorded a
    // non-null pointer whose contents it did not dump, as for vkCmdPushConstants pValues.
    //

    template <typename EncodeT, typename T>
    void EncodePointer(const T& value, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(format::PointerAttributes::kIsSingle, is_null, address, has_data);
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);

            if ((attribs & format::PointerAttributes::kHasData) == format::PointerAttributes::kHasData)
            {
                WriteValue(static_cast<EncodeT>(value));
            }
        }
    }

    void EncodeHandleIdPointer(format::HandleId value, uint64_t address, bool is_null, bool has_data)
    {
        EncodePointer<format::HandleEncodeType>(value, address, is_null, has_data);
    }

    /** Encodes a null pointer of an arbitrary kind, for a parameter the api dump omitted. */
    void EncodeNullPointer(uint32_t kind_bits)
    {
        WriteValue(static_cast<uint32_t>(kind_bits | format::PointerAttributes::kIsNull));
    }

    //
    // Arrays.
    //
    // ParameterEncoder always writes the element count for a non-null array, even when the data
    // itself is omitted, so the count is written outside the kHasData branch here too.
    //

    template <typename EncodeT, typename T>
    void EncodeArray(const T* values, size_t len, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(format::PointerAttributes::kIsArray, is_null, address, has_data);
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);
            EncodeSizeTValue(len);

            if ((attribs & format::PointerAttributes::kHasData) == format::PointerAttributes::kHasData)
            {
                for (size_t i = 0; i < len; ++i)
                {
                    WriteValue(static_cast<EncodeT>(values[i]));
                }
            }
        }
    }

    void
    EncodeHandleIdArray(const format::HandleId* values, size_t len, uint64_t address, bool is_null, bool has_data)
    {
        EncodeArray<format::HandleEncodeType>(values, len, address, is_null, has_data);
    }

    //
    // Struct preambles. The struct body is written by the caller immediately afterwards.
    //

    void EncodeStructPtrPreamble(uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(
            format::PointerAttributes::kIsStruct | format::PointerAttributes::kIsSingle, is_null, address, has_data
        );
        WriteValue(attribs);
        WriteAddressIfPresent(attribs, address);
    }

    void EncodeStructArrayPreamble(size_t len, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(
            format::PointerAttributes::kIsStruct | format::PointerAttributes::kIsArray, is_null, address, has_data
        );
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);
            EncodeSizeTValue(len);
        }
    }

    void EncodeStructArray2DPreamble(size_t len, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(
            format::PointerAttributes::kIsStruct | format::PointerAttributes::kIsArray2D, is_null, address, has_data
        );
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);
            EncodeSizeTValue(len);
        }
    }

    //
    // Strings. The length is the character count without the terminator, and is always written for
    // a non-null string, matching ParameterEncoder EncodeBasicString.
    //

    void EncodeString(const char* str, size_t len, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(
            format::PointerAttributes::kIsString | format::PointerAttributes::kIsSingle, is_null, address, has_data
        );
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);
            EncodeSizeTValue(len);

            if ((attribs & format::PointerAttributes::kHasData) == format::PointerAttributes::kHasData)
            {
                for (size_t i = 0; i < len; ++i)
                {
                    WriteValue(static_cast<format::CharEncodeType>(str[i]));
                }
            }
        }
    }

    /** Writes the outer descriptor of a string array; each element follows via EncodeString. */
    void EncodeStringArrayPreamble(size_t len, uint64_t address, bool is_null, bool has_data)
    {
        const uint32_t attribs = MakeAttribs(
            format::PointerAttributes::kIsString | format::PointerAttributes::kIsArray, is_null, address, has_data
        );
        WriteValue(attribs);

        if (!is_null)
        {
            WriteAddressIfPresent(attribs, address);
            EncodeSizeTValue(len);
        }
    }

    void EncodeRawBytes(const void* bytes, size_t num_bytes) { Write(bytes, num_bytes); }

  private:
    static uint32_t MakeAttribs(uint32_t kind, bool is_null, uint64_t address, bool has_data)
    {
        uint32_t attribs = kind;

        if (is_null)
        {
            attribs |= format::PointerAttributes::kIsNull;
        }
        else
        {
            // An api dump only records an address when it expanded the pointee, so a zero address
            // stands for "not recorded" rather than for a null pointer, which is_null already
            // covers. The decoders treat a missing address as an unknown one.
            if (address != 0)
            {
                attribs |= format::PointerAttributes::kHasAddress;
            }

            if (has_data)
            {
                attribs |= format::PointerAttributes::kHasData;
            }
        }

        return attribs;
    }

    void WriteAddressIfPresent(uint32_t attribs, uint64_t address)
    {
        if ((attribs & format::PointerAttributes::kHasAddress) == format::PointerAttributes::kHasAddress)
        {
            EncodeAddressValue(address);
        }
    }

    template <typename T>
    void WriteValue(T value)
    {
        static_assert(std::is_trivially_copyable<T>::value, "parameter buffer values must be trivially copyable");
        Write(&value, sizeof(T));
    }

    void Write(const void* data, size_t size)
    {
        const auto* bytes = static_cast<const uint8_t*>(data);
        buffer_.insert(buffer_.end(), bytes, bytes + size);
    }

    std::vector<uint8_t> buffer_;
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_ENCODER_H
