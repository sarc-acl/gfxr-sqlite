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

#ifndef GFXRECON_DECODE_APIDUMP_SEQUENCER_H
#define GFXRECON_DECODE_APIDUMP_SEQUENCER_H

#include <cstdint>
#include <functional>

#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Supplies the block indices and frame numbers an api dump does not record.
 *
 * A .gfxr carries a block index per record, which the sqlite consumer stores as `apiEvents.id`, and
 * explicit frame end markers. An api dump has neither, so both are synthesised here: calls are
 * numbered in document order, and each frame object produces one end marker.
 *
 * Frame numbers are shifted by one because api dump counts frames from zero and the sqlite schema
 * counts from one, with `VulkanSqliteConsumerBase::Initialize` having already opened frame 1.
 *
 * `FinalizeFrame` in the consumer only advances its own counter when the frame number it is handed
 * matches the frame it currently has open, and warns otherwise. That makes it important to emit a
 * marker for every frame in order, including ones whose api dump frame held no calls, and to fill
 * in any frame number the dump skipped.
 */
class ApiDumpSequencer
{
  public:
    /** Emits a frame end marker for a db frame number. */
    using FrameEndEmitter = std::function<void(uint64_t db_frame_number)>;

    explicit ApiDumpSequencer(FrameEndEmitter emit_frame_end) : emit_frame_end_(std::move(emit_frame_end)) {}

    /** Converts an api dump frame number to the db frame it belongs to. */
    static uint64_t ToDbFrame(uint64_t apidump_frame_number) { return apidump_frame_number + 1; }

    /** Consumes and returns the next block index. Block indices start at 1. */
    uint64_t NextBlockIndex() { return next_block_index_++; }

    /** The block index that will be handed out next, without consuming it. */
    uint64_t PeekBlockIndex() const { return next_block_index_; }

    /** Closes an api dump frame, emitting markers for it and for any frames the dump skipped.
     *
     * Each marker consumes a block index of its own, matching gfxreconstruct, where a frame marker
     * is a block in the stream and therefore occupies an `apiEvents` row.
     */
    void EndFrame(uint64_t apidump_frame_number)
    {
        const uint64_t db_frame = ToDbFrame(apidump_frame_number);

        // Frame 1 is already open, so the first frame to close is 1. Anything beyond the next
        // expected frame means the dump skipped a number; close the gap so the consumer's counter
        // keeps step instead of warning on every later frame.
        while (next_db_frame_ < db_frame)
        {
            emit_frame_end_(next_db_frame_);
            ++next_db_frame_;
            ++skipped_frames_;
        }

        if (db_frame < next_db_frame_)
        {
            // Frame numbers went backwards, which the consumer cannot represent. Dropping the
            // marker keeps its counter consistent; the caller reports the anomaly.
            ++out_of_order_frames_;
            return;
        }

        emit_frame_end_(db_frame);
        next_db_frame_ = db_frame + 1;
    }

    /** Tells the sequencer that db frame `db_frame` is already open, so the next EndFrame call for
     * it closes it normally instead of gap-filling the frames a collapsed setup region skipped
     * over. Called once, right after a StateEndMarker opens the real capture's first frame. */
    void ResumeAt(uint64_t db_frame) { next_db_frame_ = db_frame; }

    uint64_t SkippedFrameCount() const { return skipped_frames_; }

    uint64_t OutOfOrderFrameCount() const { return out_of_order_frames_; }

  private:
    FrameEndEmitter emit_frame_end_;

    uint64_t next_block_index_{ 1 };
    uint64_t next_db_frame_{ 1 };
    uint64_t skipped_frames_{ 0 };
    uint64_t out_of_order_frames_{ 0 };
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_SEQUENCER_H
