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

#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

// Header only helper to log
// Adds timing and thread information in addition to just using printf.
// Also instrumented code can be compiled out.
#define SQLITE_CONSUMER_DEBUG_LOG 0

// Macro expanding to an annotation telling compilers the function takes printf style arguments.
// Gets the offset of the format argument, and assumes the variable arguments start just after it.
#if defined(__clang__) || defined(__GNUC__)
#define SQLITE_CONSUMER_PRINTF_ATTR(FMT) __attribute__((format(printf, (FMT), (FMT) + 1)))
#else
#define SQLITE_CONSUMER_PRINTF_ATTR(FMT) /* nothing*/
#endif
namespace gfxrSqlite
{

    // declaration to annotate the printf formatting attribute for supported compilers
    inline void debugLog(const char* format, ...) SQLITE_CONSUMER_PRINTF_ATTR(1);
} // namespace gfxrSqlite

#if SQLITE_CONSUMER_DEBUG_LOG
#include <chrono>
#include <thread>
#include <sstream>
#include <cstdio>
#include <cstdarg>

namespace gfxrSqlite
{
    /** Returns the first time this method was called. To log with relative times. */
    inline std::chrono::steady_clock::time_point startTime()
    {
        static auto start = std::chrono::steady_clock::now();
        return start;
    }

    /** Single log entry: (note: be careful with %, as those are interpreted with printf semantic. If in doubt, use "%s"
     * as format) */
    inline void debugLog(const char* format, ...)
    {
        std::ostringstream ss;
        ss << std::this_thread::get_id();
        auto start = startTime();
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        ss << " " << elapsed.count() << " ms";
        va_list args;

        char buf[2048];
        va_start(args, format);
        int len = vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);
        if (len >= 0)
        {
            buf[sizeof(buf) - 1] = 0; // just in case.
            const char* dotDotDotIfCut = static_cast<std::size_t>(len) < sizeof(buf) - 1 ? "" : "...";
            std::fprintf(stderr, "%s %s%s\n", ss.str().c_str(), buf, dotDotDotIfCut);
        }
        else
        {
            std::fprintf(stderr, "format error in %s!\n", format);
        }
    }

    /** Create a stack instance for start/end time logging */
    class DebugLogDuration
    {
      public:
        DebugLogDuration(const char* ctx) : mCtx(ctx) { debugLog("%s-begin", mCtx); }

        ~DebugLogDuration() { debugLog("%s-end", mCtx); }

      private:
        DebugLogDuration& operator=(const DebugLogDuration&) = delete;
        DebugLogDuration(const DebugLogDuration&) = delete;
        DebugLogDuration() = delete;
        const char* mCtx;
    };
} // namespace gfxrSqlite
#else // SQLITE_CONSUMER_DEBUG_LOG

// Disabled logging setup
namespace gfxrSqlite
{
    inline void debugLog(const char* /*ctx*/, ...) {}

    class DebugLogDuration
    {
      public:
        DebugLogDuration(const char* /*ctx*/) {};
        ~DebugLogDuration() = default;

      private:
        DebugLogDuration& operator=(const DebugLogDuration&) = delete;
        DebugLogDuration(const DebugLogDuration&) = delete;
        DebugLogDuration() = delete;
    };

} // namespace gfxrSqlite
#endif

#endif // CONSUMER_H
