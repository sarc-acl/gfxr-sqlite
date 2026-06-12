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

#include "executable_path.h"

#include <string>

#ifdef _WIN32
#include <windows.h> //GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h> //readlink
#endif

namespace gfxrSqlite
{

    std::string getExecutablePath()
    {
#ifdef _WIN32
        char path[MAX_PATH]{};
        if (GetModuleFileNameA(NULL, path, MAX_PATH) <= 0)
        {
            return "";
        }
        return path;
#else
        char result[PATH_MAX]{};
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        return std::string(result, (count > 0) ? count : 0);
#endif
    }

} // namespace gfxrSqlite
