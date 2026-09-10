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

#ifndef GFXRECON_DECODE_APIDUMP_PROCESSOR_H
#define GFXRECON_DECODE_APIDUMP_PROCESSOR_H

#include <cstdint>
#include <string>

#include "apidump_context.h"
#include "apidump_encoder.h"
#include "apidump_handle_map.h"
#include "apidump_json.h"
#include "apidump_sequencer.h"

#include "decode/vulkan_decoder_base.h"
#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Drives a VulkanDecoder from an api dump file, in place of a FileProcessor.
 *
 * Everything downstream of the decoder is the ordinary gfxreconstruct path, so a database built
 * this way goes through the same consumer as one built from a .gfxr. What this class supplies is
 * what a .gfxr carries in its own structure and an api dump does not: a block index per call, and
 * frame end markers.
 */
class ApiDumpProcessor
{
  public:
    explicit ApiDumpProcessor(VulkanDecoderBase& decoder);

    /** Streams the file, encoding each call and handing it to the decoder.
     *
     * Returns false and fills `error` if the document could not be parsed. Whatever was processed
     * before the failure has already reached the consumer, which matters because captures are
     * routinely cut short by the app being killed.
     */
    bool ProcessFile(const std::string& path, std::string& error);

    uint64_t ProcessedCallCount() const { return processed_calls_; }

    uint64_t SkippedCallCount() const { return context_.Stats().unknown_commands; }

    const ApiDumpConversionStats& Stats() const { return context_.Stats(); }

    const ApiDumpHandleMap& Handles() const { return handles_; }

    /** A one line summary of anything that could not be represented faithfully. */
    std::string DescribeConversion() const;

  private:
    void OnFrameBegin(uint64_t apidump_frame_number);
    void OnCall(const ApiDumpCall& call);
    void OnFrameEnd(uint64_t apidump_frame_number);

    VulkanDecoderBase& decoder_;
    ApiDumpEncoder     encoder_;
    ApiDumpHandleMap   handles_;
    ApiDumpContext     context_;
    ApiDumpSequencer   sequencer_;

    uint64_t processed_calls_{ 0 };
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_PROCESSOR_H
