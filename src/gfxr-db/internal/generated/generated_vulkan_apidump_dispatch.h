/********************************************************************************
    Copyright 2024-2026 The Sokatoa Project Authors

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

/*
** This file is generated from the Khronos Vulkan XML API Registry.
**
*/

#ifndef  GFXRECON_GENERATED_VULKAN_APIDUMP_DISPATCH_H
#define  GFXRECON_GENERATED_VULKAN_APIDUMP_DISPATCH_H

#include "vulkan/vulkan.h"
#include "vk_video/vulkan_video_codec_h264std.h"
#include "vk_video/vulkan_video_codec_h264std_decode.h"
#include "vk_video/vulkan_video_codec_h264std_encode.h"
#include "vk_video/vulkan_video_codec_h265std.h"
#include "vk_video/vulkan_video_codec_h265std_decode.h"
#include "vk_video/vulkan_video_codec_h265std_encode.h"
#include "vk_video/vulkan_video_codecs_common.h"

#include <string_view>
#include <unordered_map>

#include "apidump_context.h"
#include "apidump_json.h"

#include "format/api_call_id.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Writes the parameter buffer for one recorded call. */
using PFN_ApiDumpEncode = void (*)(ApiDumpContext& ctx, const ApiDumpCall& call);

struct ApiDumpCommandInfo
{
    format::ApiCallId call_id;
    PFN_ApiDumpEncode encode;
};

using ApiDumpCommandTable = std::unordered_map<std::string_view, ApiDumpCommandInfo>;

/** Every command the decoder can parse, keyed by the name the layer records.
 *
 * A name missing from this table is a command gfxreconstruct does not decode, so there
 * is nothing useful to write for it; the processor skips and counts those.
 */
const ApiDumpCommandTable& GetApiDumpCommandTable();

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_GENERATED_VULKAN_APIDUMP_DISPATCH_H
