/********************************************************************************
    Copyright 2025 The Sokatoa Project Authors

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

#pragma once

#include <cstdlib>
#include <locale>
#include <string>

#ifdef _WIN32
#include <windows.h> // for WideCharToMultiByte
#endif

namespace util
{

    inline std::string ConvertToUTF8(const wchar_t* data)
    {
        std::string result;

        // On Windows, wcstombs uses the current locale's codepage (often Windows-1252 or similar), not UTF-8
        // On Linux/POSIX, it typically uses UTF-8 by default
        // WideCharToMultiByte with CP_UTF8 guarantees UTF-8 output on Windows

#ifdef _WIN32
        // Windows: Use WideCharToMultiByte for UTF-16 to UTF-8 conversion
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, data, -1, nullptr, 0, nullptr, nullptr);
        if (sizeNeeded > 0)
        {
            result.resize(sizeNeeded);
            WideCharToMultiByte(CP_UTF8, 0, data, -1, &result[0], sizeNeeded, nullptr, nullptr);
            result.resize(sizeNeeded - 1); // -1 to exclude one past null terminator
        }
#else
        // POSIX: Use wcstombs for wide char to multibyte conversion
        std::size_t sizeNeeded = std::wcstombs(nullptr, data, 0);
        if (sizeNeeded != static_cast<std::size_t>(-1) && sizeNeeded != 0)
        {
            result.resize(sizeNeeded + 1);
            std::wcstombs(&result[0], data, sizeNeeded + 1);
            result.resize(sizeNeeded); // -1 to exclude one past null terminator
        }
#endif
        return result;
    }

} // namespace util