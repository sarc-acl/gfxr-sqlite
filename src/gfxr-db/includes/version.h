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

#ifndef VERSION_H
#define VERSION_H

#define GFXR_DB_VERSION_MAJOR 1
#define GFXR_DB_VERSION_MINOR 0
#define GFXR_DB_VERSION_PATCH 4

#define GFXR_DB_STRINGIFY_IMPL(x) #x
#define GFXR_DB_STRINGIFY(x) GFXR_DB_STRINGIFY_IMPL(x)

#define GFXR_DB_VERSION_STRING               \
    GFXR_DB_STRINGIFY(GFXR_DB_VERSION_MAJOR) \
    "." GFXR_DB_STRINGIFY(GFXR_DB_VERSION_MINOR) "." GFXR_DB_STRINGIFY(GFXR_DB_VERSION_PATCH)

namespace gfxrSqlite
{
    inline const char* version()
    {
        return GFXR_DB_VERSION_STRING;
    }

    // Encodes major/minor/patch into the single integer SQLite's PRAGMA user_version stores.
    constexpr int versionNumber()
    {
        return (GFXR_DB_VERSION_MAJOR * 10000) + (GFXR_DB_VERSION_MINOR * 100) + GFXR_DB_VERSION_PATCH;
    }
} // namespace gfxrSqlite

#endif // VERSION_H
