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

#ifndef GFXR_SQLITE_TEST_RESOURCES_PATH_H
#define GFXR_SQLITE_TEST_RESOURCES_PATH_H

#include <filesystem>
#include <stdexcept>
#include <string>

#include "executable_path.h"

namespace gfxrSqlite
{

    inline constexpr const char* kTestResourcesFolderName = "test-resources";

    /** Finds the checked in test-resources folder by walking up from the running executable.
     *
     * Locating it this way rather than through a path baked in at configure time keeps the tests
     * runnable from a build tree, an install tree or ctest, on any platform.
     */
    inline std::filesystem::path getTestResourcesFolder()
    {
        const auto            binPath = getExecutablePath();
        std::filesystem::path path    = std::filesystem::path(binPath).parent_path();

        for (;;)
        {
            auto testResources = path / kTestResourcesFolderName;
            if (exists(testResources))
            {
                return testResources;
            }

            // Detect root by checking that parent_path() actually reduces the path.
            // `has_parent_path()` returns true even at filesystem roots on Windows, which would
            // otherwise spin this loop forever.
            auto parent = path.parent_path();
            if (parent == path)
            {
                throw std::runtime_error("test-resources folder not found in any parent of " + binPath);
            }

            path = parent;
        }
    }

} // namespace gfxrSqlite

#endif // GFXR_SQLITE_TEST_RESOURCES_PATH_H
