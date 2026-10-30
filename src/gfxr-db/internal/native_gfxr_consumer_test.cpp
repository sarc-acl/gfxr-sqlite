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

#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

#include "create_db_helper.h"
#include "format/format.h"
#include "test_resources_path.h"

using gfxrSqlite::getTestResourcesFolder;

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

static std::unique_ptr<gfxrSqlite::CreateDBHelper> createDatabase(const std::filesystem::path& gfxrFile)
{
    std::cout << "Loading gfxr file " << gfxrFile << '\n';
    std::string dbFilename = gfxrSqlite::createNewMemoryDbFilename();
    std::optional<std::string> logFilename;

    bool errorReported = false;
    gfxrSqlite::ReportErrorHandler reportError = [&errorReported](const std::string& error) {
        std::cerr << "ERROR: " << error << '\n';
        errorReported = true;
    };

    bool enforceForeignKeys = true;
    auto helper = std::make_unique<gfxrSqlite::CreateDBHelper>(
        gfxrFile.string(), dbFilename, logFilename, enforceForeignKeys, reportError
    );
    helper->createDatabase();
    if (errorReported)
    {
        std::cerr << "Failing due to reported error\n";
        return nullptr;
    }
    if (helper->getDB() == nullptr)
    {
        std::cerr << "Failed to create database\n";
        return nullptr;
    }
    return helper;
}

static std::optional<std::string> readCaptureStartQueueSubmitIndex(sqlite3* const dbHandle)
{
    gfxrSqlite::RunQuery query(dbHandle, "SELECT value FROM metaData WHERE key = 'capture start queue submit index'");
    std::string err;
    if (!query.run(&err) || query.Rows().empty())
    {
        return std::nullopt;
    }
    return std::get<std::string>(query.Rows()[0][0]);
}

// Copies test1.gfxr with a capture start queue submit index block right after the file header.
static std::filesystem::path writeGfxrWithQueueSubmitIndex(uint64_t queueSubmitIndex)
{
    std::ifstream in(getTestResourcesFolder() / "test1.gfxr", std::ios::binary);
    const std::vector<char> bytes{ std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };

    gfxrecon::format::FileHeader header;
    std::memcpy(&header, bytes.data(), sizeof(header));
    const size_t headerSize = sizeof(header) + header.num_options * sizeof(gfxrecon::format::FileOptionPair);

    gfxrecon::format::CaptureStartQueueSubmitIndexCommand command = {};
    command.meta_header.block_header.type = gfxrecon::format::BlockType::kMetaDataBlock;
    command.meta_header.block_header.size = sizeof(command) - sizeof(command.meta_header.block_header);
    command.meta_header.meta_data_id = gfxrecon::format::MakeMetaDataId(
        gfxrecon::format::ApiFamilyId::ApiFamily_Vulkan,
        gfxrecon::format::MetaDataType::kCaptureStartQueueSubmitIndexCommand
    );
    command.thread_id = 1;
    command.queue_submit_index = queueSubmitIndex;

    const auto path = std::filesystem::temp_directory_path() / "gfxr-sqlite-queue-submit-index.gfxr";
    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), headerSize);
    out.write(reinterpret_cast<const char*>(&command), sizeof(command));
    out.write(bytes.data() + headerSize, bytes.size() - headerSize);
    return path;
}

static bool runTest()
{
    if (!gfxrSqlite::configSqLite3())
    {
        std::cerr << "Failed to configure sqlite3\n";
        return false;
    }

    const auto test1 = createDatabase(getTestResourcesFolder() / "test1.gfxr");
    if (!test1 || !runSimpleQuery(test1->getDB()))
    {
        std::cerr << "Simple query test failed\n";
        return false;
    }
    if (readCaptureStartQueueSubmitIndex(test1->getDB()))
    {
        std::cerr << "A file without the block got a capture start queue submit index\n";
        return false;
    }

    const auto withIndexGfxr = writeGfxrWithQueueSubmitIndex(42);
    const auto withIndex = createDatabase(withIndexGfxr);
    std::filesystem::remove(withIndexGfxr);
    if (!withIndex || readCaptureStartQueueSubmitIndex(withIndex->getDB()) != "42")
    {
        std::cerr << "Capture start queue submit index was not stored\n";
        return false;
    }
    std::cout << "capture start queue submit index passed\n";
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
