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

/** Exercises the streaming api dump reader against a real capture.
 *
 * Takes the .apidump path on the command line so it can be pointed at either the trimmed or the
 * full capture; the checks are about shape rather than exact contents, apart from the specific
 * nodes below that pin down how pointers, arrays and pNext chains are represented.
 */

#include <cstdio>
#include <cstring>
#include <map>
#include <string>

#include <filesystem>

#include "apidump_json.h"
#include "test_resources_path.h"

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

} // namespace

int main(int argc, char** argv)
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    // Defaults to the checked in fixture so ctest can run it with no arguments, but still takes a
    // path so it can be pointed at a full capture while working on the reader.
    std::string path;
    if (argc >= 2)
    {
        path = argv[1];
    }
    else
    {
        try
        {
            path = (gfxrSqlite::getTestResourcesFolder() / "test1.apidump").string();
        }
        catch (const std::exception& e)
        {
            std::printf("  FAIL  %s\n", e.what());
            return 1;
        }
    }

    uint64_t                     frames_begun = 0;
    uint64_t                     frames_ended = 0;
    uint64_t                     calls        = 0;
    std::map<uint64_t, uint64_t> calls_per_frame;
    uint64_t                     current_frame = 0;

    // Details of the first vkCreateBuffer seen, checked after the parse.
    bool        saw_create_buffer      = false;
    bool        create_buffer_ok       = false;
    std::string create_buffer_detail;

    // Details of the first vkCreateInstance, which carries the nested pNext chain.
    bool saw_create_instance = false;
    bool pnext_nested_ok     = false;

    // The count-query form of vkGetSwapchainImagesKHR, where the array pointer is null.
    int  swapchain_query_calls  = 0;
    bool swapchain_null_array   = false;
    bool swapchain_filled_array = false;

    ApiDumpReader reader(
        [&](uint64_t frame_number) {
            ++frames_begun;
            current_frame = frame_number;
        },
        [&](const ApiDumpCall& call) {
            ++calls;
            ++calls_per_frame[current_frame];

            const std::string_view name = call.Name();

            if (!saw_create_buffer && (name == "vkCreateBuffer"))
            {
                saw_create_buffer = true;

                const ApiDumpNode device      = call.Arg("device");
                const ApiDumpNode create_info = call.Arg("pCreateInfo");
                const ApiDumpNode allocator   = call.Arg("pAllocator");
                const ApiDumpNode out_buffer  = call.Arg("pBuffer");
                const ApiDumpNode size        = create_info["size"];
                const ApiDumpNode sharing     = create_info["sharingMode"];
                const ApiDumpNode queue_fams  = create_info["pQueueFamilyIndices"];

                create_buffer_ok =
                    // A dispatchable handle argument carries its value directly.
                    (device.Address() == 0) && !device.ValueString().empty() &&
                    // An expanded struct pointer: not null, has data, has a capture address.
                    !create_info.IsNullPointer() && create_info.HasData() && (create_info.Address() != 0) &&
                    // A genuinely null pointer.
                    allocator.IsNullPointer() && !allocator.HasData() &&
                    // The output handle: a pointer carrying a single value.
                    !out_buffer.IsNullPointer() && out_buffer.HasData() && !out_buffer.ValueString().empty() &&
                    // Nested member lookup by name.
                    (size.ValueString() == "208") &&
                    (sharing.ValueString() == "VK_SHARING_MODE_EXCLUSIVE") &&
                    // UNUSED, because queueFamilyIndexCount is 0.
                    queue_fams.IsNullPointer();

                create_buffer_detail = "device=" + std::string(device.ValueString()) +
                                       " size=" + std::string(size.ValueString()) +
                                       " sharing=" + std::string(sharing.ValueString());
            }

            if (!saw_create_instance && (name == "vkCreateInstance"))
            {
                saw_create_instance = true;

                // pNext chains nest inside each struct's members, which is what lets the generated
                // pNext encoder recurse the same way gfxreconstruct's does.
                const ApiDumpNode create_info = call.Arg("pCreateInfo");
                const ApiDumpNode pnext       = create_info["pNext"];
                const ApiDumpNode stype       = pnext["sType"];

                pnext_nested_ok = pnext.HasData() && !pnext.IsNullPointer() &&
                                  (stype.ValueString() == "VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT");
            }

            if (name == "vkGetSwapchainImagesKHR")
            {
                ++swapchain_query_calls;
                const ApiDumpNode images = call.Arg("pSwapchainImages");

                if (images.IsNullPointer())
                {
                    swapchain_null_array = true;
                }
                else if (images.ElementCount() > 0)
                {
                    swapchain_filled_array = true;
                }
            }
        },
        [&](uint64_t) { ++frames_ended; }
    );

    std::string error;
    std::printf("streaming %s\n", path.c_str());

    if (!reader.Read(path, error))
    {
        std::printf("  FAIL  read: %s\n", error.c_str());
        return 1;
    }

    Expect("frame begin and end are balanced", frames_begun == frames_ended);
    Expect("saw frames", frames_begun > 0);
    Expect("saw calls", calls > 0);
    Expect("reader call count agrees", reader.CallCount() == calls);

    std::printf("  info  %llu frames, %llu calls\n",
                static_cast<unsigned long long>(frames_begun),
                static_cast<unsigned long long>(calls));

    Expect("found a vkCreateBuffer", saw_create_buffer);
    if (saw_create_buffer)
    {
        std::printf("  info  %s\n", create_buffer_detail.c_str());
        Expect("vkCreateBuffer nodes read correctly", create_buffer_ok);
    }

    Expect("found a vkCreateInstance", saw_create_instance);
    if (saw_create_instance)
    {
        Expect("pNext chain nests inside members", pnext_nested_ok);
    }

    if (swapchain_query_calls > 0)
    {
        std::printf("  info  %d vkGetSwapchainImagesKHR calls\n", swapchain_query_calls);
        Expect("count-query form has a null array", swapchain_null_array);
        Expect("populated form has elements", swapchain_filled_array);
    }

    if (g_failures == 0)
    {
        std::printf("\nStreaming reader handled the capture.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
