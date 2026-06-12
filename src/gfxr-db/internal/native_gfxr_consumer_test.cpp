/********************************************************************************
    Copyright 2025-2026 The Sokatoa Project Authors

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

#include "run_query.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>

#include "create_db_helper.h"
#include "executable_path.h"

const auto TestResourcesFolderName = "test-resources";

static std::filesystem::path getTestResourcesFolder()
{
    auto binPath = gfxrSqlite::getExecutablePath();
    std::filesystem::path bin = binPath;
    auto path = bin.parent_path();
    for (;;)
    {
        auto testResources = path / TestResourcesFolderName;
        if (exists(testResources))
        {
            return testResources;
        }
        // Detect root by checking that parent_path() actually reduces the path.
        // `has_parent_path()` returns true even at filesystem roots on Windows,
        // which would otherwise spin this loop forever.
        auto parent = path.parent_path();
        if (parent == path)
        {
            throw std::runtime_error("test-resources folder not found in any parent of " + binPath);
        }
        path = parent;
    }
}

static bool runSimpleQuery(sqlite3* const dbHandle)
{
    const char* sql = "SELECT * FROM frames";
    gfxrSqlite::RunQuery query(dbHandle, sql);
    std::string err;
    bool res = query.run(&err);
    if (!err.empty())
    {
        std::cerr << "Query failed with error: " << err << '\n';
        return false;
    }
    if (!res)
    {
        std::cerr << "Query failed!\n";
        return false;
    }
    if (query.Headers()[0] != "id" || query.Headers()[1] != "beginApiEventId" || query.Headers()[2] != "endApiEventId")
    {
        std::cerr << "Unexpected headers.\n";
        return false;
    }
    if (query.Rows().size() != 2)
    {
        std::cerr << "Unexpected row count.\n";
        return false;
    }
    if (query.Rows()[0].size() != 3 || query.Rows()[1].size() != 3)
    {
        std::cerr << "Unexpected row size.\n";
        return false;
    }
    // Row 0: initial state frame (frameIndex=1)
    if (std::get<std::int64_t>(query.Rows()[0][0]) != 1)
    {
        std::cerr << "Unexpected frameIndex for initial state frame.\n";
        return false;
    }
    // Row 1: first real frame (frameIndex=10)
    if (std::get<std::int64_t>(query.Rows()[1][0]) != 10)
    {
        std::cerr << "Unexpected frame id.\n";
        return false;
    }
    std::cout << "runSimpleQuery passed\n";
    return true;
}

static bool runTest()
{
    if (!gfxrSqlite::configSqLite3())
    {
        std::cerr << "Failed to configure sqlite3\n";
        return false;
    }

    auto test1Gfxr = getTestResourcesFolder() / "test1.gfxr";
    std::cout << "Loading gfxr file " << test1Gfxr << '\n';
    std::string dbFilename = gfxrSqlite::createNewMemoryDbFilename();
    std::optional<std::string> logFilename;

    bool errorReported = false;
    gfxrSqlite::ReportErrorHandler reportError = [&errorReported](const std::string& error) {
        std::cerr << "ERROR: " << error << '\n';
        errorReported = true;
    };

    bool enforceForeignKeys = true;
    gfxrSqlite::CreateDBHelper helper(test1Gfxr.string(), dbFilename, logFilename, enforceForeignKeys, reportError);
    helper.createDatabase();
    if (errorReported)
    {
        std::cerr << "Failing due to reported error\n";
        return false;
    }
    const auto dbHandle = helper.getDB();
    if (dbHandle == nullptr)
    {
        std::cerr << "Failed to create database\n";
        return false;
    }
    if (!runSimpleQuery(dbHandle))
    {
        std::cerr << "Simple query test failed\n";
        return false;
    }
    return true;
}

int main()
{
    std::cout << "\nRunning native tests\n";

    try
    {
        if (!runTest())
        {
            std::cerr << "Test failed\n";
            return 1;
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Failed with exception: " << ex.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Failed with unknown exception \n";
        return 1;
    }

    std::cout << "test succeeded\n";
    return 0;
}
