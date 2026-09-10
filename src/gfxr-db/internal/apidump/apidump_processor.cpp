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

#include "apidump_processor.h"

#include <sstream>

#include "generated_vulkan_apidump_dispatch.h"

#include "decode/decode_allocator.h"
#include "util/logging.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

ApiDumpProcessor::ApiDumpProcessor(VulkanDecoderBase& decoder) :
    decoder_(decoder), context_(encoder_, handles_),
    sequencer_([this](uint64_t db_frame) {
        // A frame marker is a block of its own in a .gfxr, so it takes a block index and lands in
        // apiEvents the same way a call does.
        const uint64_t block_index = sequencer_.NextBlockIndex();
        decoder_.SetCurrentBlockIndex(block_index);
        decoder_.DispatchFrameEndMarker(db_frame);
    })
{}

bool ApiDumpProcessor::ProcessFile(const std::string& path, std::string& error)
{
    ApiDumpReader reader(
        [this](uint64_t frame_number) { OnFrameBegin(frame_number); },
        [this](const ApiDumpCall& call) { OnCall(call); },
        [this](uint64_t frame_number) { OnFrameEnd(frame_number); }
    );

    return reader.Read(path, error);
}

void ApiDumpProcessor::OnFrameBegin(uint64_t)
{
    // Frame 1 is already open when the consumer initialises, and every later frame is opened by
    // the marker that closed the one before, so there is nothing to do here.
}

void ApiDumpProcessor::OnCall(const ApiDumpCall& call)
{
    const std::string_view name  = call.Name();
    const auto&            table = GetApiDumpCommandTable();
    const auto             found = table.find(name);

    if (found == table.end())
    {
        // A command gfxreconstruct does not decode. Skipping it without taking a block index keeps
        // apiEvents contiguous; the alternative would leave a hole no row ever fills.
        ++context_.MutableStats().unknown_commands;
        GFXRECON_LOG_WARNING("ApiDumpProcessor: no decoder for %.*s, skipping",
                             static_cast<int>(name.size()),
                             name.data());
        return;
    }

    const uint64_t block_index = sequencer_.NextBlockIndex();
    decoder_.SetCurrentBlockIndex(block_index);

    // The decoders allocate their backing storage from DecodeAllocator, which asserts unless a
    // Begin/End scope is open. FileProcessor opens one per block; so does this.
    //
    // The <true> matters: DecoderAllocGuard defaults to <false>, an empty struct that guards
    // nothing.
    DecoderAllocGuard<true> alloc_guard;

    encoder_.Reset();
    found->second.encode(context_, call);

    ApiCallInfo call_info{};
    call_info.index     = block_index;
    call_info.thread_id = static_cast<format::ThreadId>(call.ThreadId());

    decoder_.DecodeFunctionCall(found->second.call_id, call_info, encoder_.GetData(), encoder_.GetDataSize());

    ++processed_calls_;
}

void ApiDumpProcessor::OnFrameEnd(uint64_t apidump_frame_number)
{
    sequencer_.EndFrame(apidump_frame_number);
}

std::string ApiDumpProcessor::DescribeConversion() const
{
    const ApiDumpConversionStats& stats = context_.Stats();

    std::ostringstream summary;
    summary << processed_calls_ << " calls";

    if (stats.unknown_commands > 0)
    {
        summary << ", " << stats.unknown_commands << " skipped as undecodable";
    }
    if (stats.unknown_enum_names > 0)
    {
        summary << ", " << stats.unknown_enum_names << " unrecognised enum names";
    }
    if (stats.unknown_structure_types > 0)
    {
        summary << ", " << stats.unknown_structure_types << " unrecognised structure types";
    }
    if (stats.unparsable_scalars > 0)
    {
        summary << ", " << stats.unparsable_scalars << " unparsable values";
    }
    if (handles_.LazilyAllocatedCount() > 0)
    {
        // Expected for a trimmed capture, where objects already existed when the dump began.
        summary << ", " << handles_.LazilyAllocatedCount() << " handles first seen without a create";
    }
    if (sequencer_.SkippedFrameCount() > 0)
    {
        summary << ", " << sequencer_.SkippedFrameCount() << " frame numbers missing from the dump";
    }
    if (sequencer_.OutOfOrderFrameCount() > 0)
    {
        summary << ", " << sequencer_.OutOfOrderFrameCount() << " out of order frames dropped";
    }

    return summary.str();
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
