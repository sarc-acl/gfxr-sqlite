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

#ifndef GFXRECON_DECODE_APIDUMP_JSON_H
#define GFXRECON_DECODE_APIDUMP_JSON_H

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>

#include "nlohmann/json.hpp"

#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** A view over one argument, struct member or array element of an api dump call.
 *
 * Nodes look like `{ "type": ..., "name": ..., "address"?: ..., "value"?: ..., "members"?: [...],
 * "elements"?: [...] }`. Every scalar is written as a JSON string, including numbers.
 *
 * Lookups return an absent node rather than failing, so generated code can ask for a member the
 * layer chose not to write without checking first.
 */
class ApiDumpNode
{
  public:
    ApiDumpNode() = default;

    explicit ApiDumpNode(const nlohmann::json* node) : node_(node) {}

    bool IsPresent() const { return node_ != nullptr; }

    std::string_view Name() const { return StringField("name"); }

    std::string_view TypeName() const { return StringField("type"); }

    /** Finds a struct member by its recorded "name". */
    ApiDumpNode Member(std::string_view member_name) const;

    ApiDumpNode operator[](std::string_view member_name) const { return Member(member_name); }

    bool HasValue() const { return HasField("value") && !IsUnusedPlaceholder(); }

    /** The raw recorded text, empty when this node has no scalar value. */
    std::string_view ValueString() const { return IsUnusedPlaceholder() ? std::string_view{} : StringField("value"); }

    bool HasMembers() const { return HasField("members"); }

    bool HasElements() const { return HasField("elements"); }

    bool IsExpanded() const { return HasMembers() || HasElements(); }

    /** Whether the dump recorded any pointee at all for this node.
     *
     * A null pointer is written as `"address": "address"` (or `"NULL"` once the layer runs with
     * show_null_pointers) with nothing else, and an argument the layer skipped for a failed
     * validity check is written as `"UNUSED"`. Both land here.
     */
    bool IsNullPointer() const { return !IsPresent() || (!IsExpanded() && !HasValue() && (Address() == 0)); }

    /** Whether the pointee contents were recorded.
     *
     * False for a non-null pointer the layer declined to expand, such as vkCmdPushConstants
     * pValues, which carries a real address and no data. That distinction has to survive into the
     * parameter buffer, because the gfxreconstruct decoders treat "null" and "present but omitted"
     * differently.
     */
    bool HasData() const { return IsExpanded() || HasValue(); }

    /** The capture address, or 0 when the dump did not record a usable one. */
    uint64_t Address() const;

    size_t ElementCount() const;

    ApiDumpNode ElementAt(size_t index) const;

    /** Whether the element at this index is a bare string rather than an object.
     *
     * Scalar arrays are written that way; VkShaderModuleCreateInfo pCode is a list of plain
     * "0x07230203" strings with no per element type or name.
     */
    bool ElementIsScalar(size_t index) const;

    std::string_view ElementScalar(size_t index) const;

  private:
    /** Whether this node is a member the layer skipped rather than one carrying a real value.
     *
     * A failed validity check is written as `{ "address": "UNUSED", "value": "UNUSED" }`, so the
     * node has a "value" field that must not be read as data. VkBufferCreateInfo
     * pQueueFamilyIndices looks like that whenever queueFamilyIndexCount is 0.
     *
     * Both fields have to be the placeholder before the value is suppressed. "UNUSED" is a legal
     * string for a debug label to contain, but such a node would carry a real address or none at
     * all, never the placeholder.
     */
    bool IsUnusedPlaceholder() const;

    bool HasField(const char* field) const;
    std::string_view StringField(const char* field) const;

    const nlohmann::json* node_ = nullptr;
};

/** A view over one entry of a frame's apiCalls array. */
class ApiDumpCall
{
  public:
    ApiDumpCall() = default;

    explicit ApiDumpCall(const nlohmann::json* call) : call_(call) {}

    bool IsPresent() const { return call_ != nullptr; }

    /** Whether this is not a real recorded call but an `{ "annotation": ... }` placeholder left by
     * optimizing a .apidump: a command buffer recording, or an object's
     * whole create-to-destroy lifetime, that never survived to the captured frames. There is
     * nothing here to decode, so callers should skip it before looking at Name() or anything else -
     * an annotation has no "name", which would otherwise just read as an unrecognised command.
     */
    bool IsAnnotation() const;

    std::string_view Name() const;

    /** The recorded thread, written as "Thread 1". Returns 0 when it cannot be read. */
    uint64_t ThreadId() const;

    /** Finds an argument by name, returning an absent node when the layer omitted it. */
    ApiDumpNode Arg(std::string_view arg_name) const;

    /** The return value node, absent for a void command. */
    ApiDumpNode ReturnValue() const;

    std::string_view ReturnTypeName() const;

  private:
    const nlohmann::json* call_ = nullptr;
};

/** Streams an .apidump file, materialising one call at a time.
 *
 * An api dump is much larger than the equivalent .gfxr and nlohmann's DOM costs well over the
 * document size in memory, so the whole file is never held at once. A SAX pass walks the outer
 * structure and builds a DOM only for the call currently being handled.
 *
 * The reader assumes each frame object writes "frameNumber" before "apiCalls", which is the order
 * the layer emits. If that ever changes the reader reports an error rather than silently
 * attributing calls to the wrong frame.
 */
class ApiDumpReader
{
  public:
    /** Called when a frame object begins, with the frame number exactly as recorded and whether
     * the layer tagged it "isSetupFrame" (holds only always_dump_setup calls, recorded because it
     * happened but not itself part of the captured range).
     *
     * Fired once "apiCalls" is reached, not as soon as "frameNumber" is, so that an "isSetupFrame"
     * appearing between the two has already been seen.
     */
    using FrameBeginHandler = std::function<void(uint64_t frame_number, bool is_setup_frame)>;

    /** Called when a frame object ends, after all of its calls have been handled. */
    using FrameEndHandler = std::function<void(uint64_t frame_number)>;

    using CallHandler = std::function<void(const ApiDumpCall& call)>;

    ApiDumpReader(FrameBeginHandler on_frame_begin, CallHandler on_call, FrameEndHandler on_frame_end) :
        on_frame_begin_(std::move(on_frame_begin)), on_call_(std::move(on_call)), on_frame_end_(std::move(on_frame_end))
    {}

    /** Reads the file, invoking the handlers in document order.
     *
     * Returns false and fills `error` on a malformed document. A capture cut short by the app being
     * killed is the common case; whatever parsed before the truncation has already been handled by
     * then, so a caller that wants a partial database can keep what it has.
     */
    bool Read(const std::string& path, std::string& error);

    /** Number of calls handled so far, useful for reporting a truncation point. */
    uint64_t CallCount() const { return call_count_; }

  private:
    FrameBeginHandler on_frame_begin_;
    CallHandler on_call_;
    FrameEndHandler on_frame_end_;
    uint64_t call_count_{ 0 };
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_JSON_H
