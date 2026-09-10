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

/** Covers the handle identity and frame sequencing rules.
 *
 * These two carry the rules that are easy to get subtly wrong and hard to notice afterwards: an
 * address recycled after a destroy has to become a new object, and the consumer's frame counter
 * only advances when it is handed frames in order.
 */

#include <cstdio>
#include <vector>

#include "apidump_handle_map.h"
#include "apidump_sequencer.h"

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

void TestHandleIdentity()
{
    std::printf("handle identity\n");

    ApiDumpHandleMap map;

    const uint64_t address = 0x290000000029ull;

    const gfxrecon::format::HandleId first = map.Create(VK_OBJECT_TYPE_BUFFER, address);
    Expect("ids start at 1", first == 1);
    Expect("lookup resolves to the created id", map.Get(VK_OBJECT_TYPE_BUFFER, address) == first);
    Expect("repeat lookup is stable", map.Get(VK_OBJECT_TYPE_BUFFER, address) == first);

    // The orphaned objects scene recycles addresses on purpose, which is the case this rule exists
    // for: after the destroy, the same address is a different object.
    map.Release(VK_OBJECT_TYPE_BUFFER, address);
    const gfxrecon::format::HandleId second = map.Create(VK_OBJECT_TYPE_BUFFER, address);
    Expect("recycled address gets a new id", second != first);
    Expect("old id is not resurrected", map.Get(VK_OBJECT_TYPE_BUFFER, address) == second);

    // Creating over a live address means the driver recycled it without us seeing the destroy;
    // the new object still must not inherit the old identity.
    const gfxrecon::format::HandleId third = map.Create(VK_OBJECT_TYPE_BUFFER, address);
    Expect("create over a live address is a new id", third != second);

    // Non-dispatchable handle values are only unique per type on many drivers.
    const gfxrecon::format::HandleId image = map.Create(VK_OBJECT_TYPE_IMAGE, address);
    Expect("same address, different type, different id", image != third);
    Expect("buffer id survives the image create", map.Get(VK_OBJECT_TYPE_BUFFER, address) == third);

    Expect("null address maps to the null handle",
           map.Get(VK_OBJECT_TYPE_BUFFER, 0) == gfxrecon::format::kNullHandleId);
    Expect("creating a null address stays null",
           map.Create(VK_OBJECT_TYPE_BUFFER, 0) == gfxrecon::format::kNullHandleId);
}

void TestLazyAllocation()
{
    std::printf("handles first seen without a create\n");

    ApiDumpHandleMap map;

    // A trimmed capture references objects that existed before the dump window opened, and getters
    // such as vkGetDeviceQueue produce handles with no create at all.
    const gfxrecon::format::HandleId queue = map.Get(VK_OBJECT_TYPE_QUEUE, 0xb400006e53b85070ull);
    Expect("unknown address still resolves", queue != gfxrecon::format::kNullHandleId);
    Expect("repeat getter returns the same id", map.Get(VK_OBJECT_TYPE_QUEUE, 0xb400006e53b85070ull) == queue);
    Expect("lazy allocation is counted", map.LazilyAllocatedCount() == 1);

    map.Create(VK_OBJECT_TYPE_BUFFER, 0x1234ull);
    Expect("a create is not counted as lazy", map.LazilyAllocatedCount() == 1);
}

void TestSequencerBlockIndices()
{
    std::printf("block indices\n");

    std::vector<uint64_t> markers;
    ApiDumpSequencer      sequencer([&](uint64_t frame) { markers.push_back(frame); });

    Expect("block indices start at 1", sequencer.NextBlockIndex() == 1);
    Expect("block indices increment", sequencer.NextBlockIndex() == 2);
    Expect("peek does not consume", sequencer.PeekBlockIndex() == 3);
    Expect("peek really did not consume", sequencer.NextBlockIndex() == 3);
}

void TestSequencerFrames()
{
    std::printf("frame markers\n");

    std::vector<uint64_t> markers;
    ApiDumpSequencer      sequencer([&](uint64_t frame) { markers.push_back(frame); });

    Expect("api dump frame 0 is db frame 1", ApiDumpSequencer::ToDbFrame(0) == 1);
    Expect("api dump frame 27 is db frame 28", ApiDumpSequencer::ToDbFrame(27) == 28);

    // The shape both sample captures have: every frame present, in order.
    for (uint64_t frame = 0; frame < 28; ++frame)
    {
        sequencer.EndFrame(frame);
    }

    bool contiguous = (markers.size() == 28);
    for (size_t i = 0; contiguous && (i < markers.size()); ++i)
    {
        contiguous = (markers[i] == (i + 1));
    }

    Expect("28 frames produce markers 1..28 in order", contiguous);
    Expect("nothing was treated as skipped", sequencer.SkippedFrameCount() == 0);
}

void TestSequencerGaps()
{
    std::printf("frame numbering anomalies\n");

    {
        std::vector<uint64_t> markers;
        ApiDumpSequencer      sequencer([&](uint64_t frame) { markers.push_back(frame); });

        // A dump that jumps from frame 0 to frame 3 must still close 2 and 3, or the consumer's
        // counter falls behind and warns on every later frame.
        sequencer.EndFrame(0);
        sequencer.EndFrame(3);

        const bool filled = (markers.size() == 4) && (markers[0] == 1) && (markers[1] == 2) &&
                            (markers[2] == 3) && (markers[3] == 4);

        Expect("a gap is filled with markers", filled);

        // Api dump frames 1 and 2 were the ones missing; db frame 4 is frame 3's own marker and is
        // not a skip.
        Expect("the two skipped frames are counted", sequencer.SkippedFrameCount() == 2);
    }

    {
        std::vector<uint64_t> markers;
        ApiDumpSequencer      sequencer([&](uint64_t frame) { markers.push_back(frame); });

        sequencer.EndFrame(5);
        const size_t after_first = markers.size();
        sequencer.EndFrame(2);

        Expect("a backwards frame emits nothing", markers.size() == after_first);
        Expect("backwards frames are counted", sequencer.OutOfOrderFrameCount() == 1);
    }
}

} // namespace

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    TestHandleIdentity();
    TestLazyAllocation();
    TestSequencerBlockIndices();
    TestSequencerFrames();
    TestSequencerGaps();

    if (g_failures == 0)
    {
        std::printf("\nHandle identity and frame sequencing behave as specified.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
