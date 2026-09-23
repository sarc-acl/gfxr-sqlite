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

/** Converts the checked in .apidump fixture through the real CreateDBHelper path.
 *
 * The other tests each pin down one layer. This one runs the whole thing the way the CLI and the
 * node addon do, and asserts on the database that comes out, so a regression anywhere between the
 * json reader and the sqlite consumer shows up here.
 *
 * The fixture is a slice of a real orphanedObjects capture: the setup frame, the frame where the
 * scene destroys and recreates its objects, and three steady state frames.
 */

#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include "sqlite3.h"

#include "create_db_helper.h"
#include "test_resources_path.h"

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

/** Runs one scalar query, returning -1 when the query fails. */
int64_t QueryScalar(sqlite3* db, const char* sql)
{
    sqlite3_stmt* statement = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK)
    {
        std::printf("  FAIL  query failed to prepare: %s (%s)\n", sql, sqlite3_errmsg(db));
        ++g_failures;
        return -1;
    }

    int64_t result = -1;
    if (sqlite3_step(statement) == SQLITE_ROW)
    {
        result = sqlite3_column_int64(statement, 0);
    }

    sqlite3_finalize(statement);
    return result;
}

} // namespace

int main()
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);

    std::filesystem::path fixture;
    try
    {
        fixture = gfxrSqlite::getTestResourcesFolder() / "test1.apidump";
    }
    catch (const std::exception& e)
    {
        std::printf("  FAIL  %s\n", e.what());
        return 1;
    }

    if (!std::filesystem::exists(fixture))
    {
        std::printf("  FAIL  fixture missing: %s\n", fixture.string().c_str());
        return 1;
    }

    const auto database = std::filesystem::temp_directory_path() / "apidump_convert_test.sqlite3";
    std::error_code ignored;
    std::filesystem::remove(database, ignored);

    std::printf("converting %s\n", fixture.filename().string().c_str());

    std::vector<std::string> errors;
    gfxrSqlite::CreateDBHelper helper{ fixture.string(),
                                       database.string(),
                                       std::nullopt,
                                       /*enforceForeignKeys=*/false,
                                       [&errors](const std::string& error) { errors.push_back(error); } };
    helper.createDatabase();

    for (const auto& error : errors)
    {
        std::printf("  FAIL  conversion reported: %s\n", error.c_str());
        ++g_failures;
    }

    sqlite3* db = helper.getDB();
    Expect("database was created", db != nullptr);
    if (db == nullptr)
    {
        return 1;
    }

    // The fixture holds 288 calls, and every frame contributes one end marker, which occupies an
    // apiEvents row of its own exactly as a frame marker block does in a .gfxr.
    const int64_t calls  = QueryScalar(db, "select count(*) from apiEvents where apiEventTypeId = 2");
    const int64_t markers = QueryScalar(db, "select count(*) from apiEvents where apiEventTypeId = 1");
    std::printf("  info  %lld api calls, %lld meta events\n",
                static_cast<long long>(calls),
                static_cast<long long>(markers));
    Expect("every call in the fixture became an api event", calls == 288);
    Expect("frame markers were emitted", markers > 0);

    // Api dump frame 0 is tagged isSetupFrame, so it is bracketed with a StateBeginMarker /
    // StateEndMarker pair and folded into db frame 1 instead of getting its own frame end marker -
    // the same shape a trimmed .gfxr's initial state has. Frames 10 through 13 are real frames and
    // map to db frames 11 through 14, with no filler frames for the gap the setup region collapsed.
    Expect("frames start at 1", QueryScalar(db, "select min(id) from frames") == 1);
    Expect("the setup frame holds the setup calls",
           QueryScalar(db, "select count(*) from apiEvents where frameId = 1") > 100);
    Expect("a state begin marker brackets the setup frame",
           QueryScalar(
               db,
               "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
               " where f.name = 'StateBeginMarker'"
           ) == 1);
    Expect("a state end marker closes the setup frame",
           QueryScalar(
               db,
               "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
               " where f.name = 'StateEndMarker'"
           ) == 1);
    Expect("no filler frames were left for the range the setup region collapsed",
           QueryScalar(db, "select count(*) from frames where id > 1 and id < 11") == 0);

    // Object identity. The scene destroys objects and lets the driver hand the same addresses back,
    // which is the case the handle map exists for: a create must never resolve to a live id.
    const int64_t createCalls =
        QueryScalar(db,
                    "select count(*) from apiEvents e join functionNames f on f.id = e.functionNameId"
                    " where f.name = 'vkCreateBuffer'");
    const int64_t bufferRows     = QueryScalar(db, "select count(*) from buffers");
    const int64_t distinctBuffers = QueryScalar(db, "select count(distinct handle) from buffers");
    std::printf("  info  %lld vkCreateBuffer calls, %lld buffer rows\n",
                static_cast<long long>(createCalls),
                static_cast<long long>(bufferRows));
    Expect("every buffer create produced a row", (createCalls > 0) && (bufferRows == createCalls));
    Expect("recycled addresses did not collapse into one object", distinctBuffers == bufferRows);

    // Every id the handle map mints gets recorded alongside the raw address that produced it, so
    // e.g. a shaderModules.handle can be resolved back to the api dump's own handle value (needed
    // to build a shader extraction handle map). This must hold even for a recycled address, which
    // is exactly what the buffers above exercise.
    const int64_t handleAddressRows = QueryScalar(db, "select count(*) from apiDumpHandleAddresses");
    Expect("handle addresses were recorded", handleAddressRows > 0);
    const int64_t buffersWithAddress = QueryScalar(
        db,
        "select count(*) from buffers join apiDumpHandleAddresses"
        " on apiDumpHandleAddresses.handle = buffers.handle");
    Expect("every buffer's id resolves back to a raw address", buffersWithAddress == bufferRows);

    // Instances resolve, which only happens if the whole VkInstanceCreateInfo decoded: it carries a
    // pNext chain, a nested struct and two string arrays, so a single byte of drift loses it.
    Expect("instances were recorded", QueryScalar(db, "select count(*) from instances") > 0);
    Expect("application name survived",
           QueryScalar(db, "select count(*) from instances where applicationName != ''") > 0);

    // Command buffer contents, which is what makes the capture worth browsing at all.
    Expect("command buffer commands were recorded",
           QueryScalar(db, "select count(*) from commandBufferCommands") > 0);

    if (g_failures == 0)
    {
        std::printf("\nThe fixture converts to a well formed database.\n");
        return 0;
    }

    std::printf("\n%d check(s) failed.\n", g_failures);
    return 1;
}
