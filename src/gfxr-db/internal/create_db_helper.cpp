/********************************************************************************
    Copyright 2023-2026 The Sokatoa Project Authors

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

#include "create_db_helper.h"

#include <cstdint>
#include <cctype>
#include <fstream>
#include <string>
#include <sstream>

#include "decode/vulkan_sqlite_consumer_ext.h"

// gfxreconstruct header
#include PROJECT_VERSION_HEADER_FILE
#include "apidump/apidump_processor.h"
#include "decode/file_processor.h"
#include "decode/decode_api_detection.h"
#include "generated/generated_vulkan_decoder.h"

#include "util/defines.h"
#include "util/logging.h"

#include "memdb_ext.h"

namespace gfxrSqlite
{

    // Index for unique in memory database names
    static std::uint64_t memoryDatabaseIndex = 0;

    /** Create a unique name memdb<number> and use the memdb virtual file system.
     *
     * The :memory: (or even its shared URL form "file:memdb1?mode=memory&cache=shared") support
     * does not allow for concurrent reads.
     *
     * Note: memdb_ext is an extension we add, its a copy of the stock memdb vfs (virtual file system),
     * but it uses realloc/free instead of the internal sqlite3 memory support which limits to 2 GB (or actually 1.6).
     * @return an url/file name to be passed to sqlite3 to create a in memory database
     */
    std::string createNewMemoryDbFilename()
    {
        return "file:/memdb" + std::to_string(memoryDatabaseIndex++) + "?vfs=memdb_ext";
    }

    inline bool fileExists(const char* filename)
    {
        FILE* f = fopen(filename, "r");
        if (f == nullptr)
        {
            return false;
        }
        auto res = fclose(f);
        logErrorIfNot(res == 0, "Failed to close file");
        return true;
    }

    inline const char* errorStateToString(gfxrecon::decode::BlockIOError err)
    {
        using Error = gfxrecon::decode::BlockIOError;
        switch (err)
        {
            case Error::kErrorNone:
                return "";
            case Error::kErrorInvalidFileDescriptor:
                return "Invalid file descriptor";
            case Error::kErrorOpeningFile:
                return "Error opening file";
            case Error::kErrorReadingFile:
                return "Error reading file";
            case Error::kErrorReadingFileHeader:
                return "Error reading file header";
            case Error::kErrorReadingBlockHeader:
                return "Error reading block header";
            case Error::kErrorReadingCompressedBlockHeader:
                return "Error reading compressed block header";
            case Error::kErrorReadingBlockData:
                return "Error reading block data";
            case Error::kErrorReadingCompressedBlockData:
                return "Error reading compressed block data";
            case Error::kErrorInvalidFourCC:
                return "Error reading FourCC";
            case Error::kErrorUnsupportedCompressionType:
                return "Unsupported compression type";
            default:
                return "Unknown error gfxrecon";
        }
    }

    inline void addErrorState(std::ostream& errMsg, const gfxrecon::decode::FileProcessor& file_processor)
    {
        auto errorState = file_processor.GetErrorState();
        if (errorState != gfxrecon::decode::BlockIOError::kErrorNone)
        {
            errMsg << ": " << errorStateToString(errorState);
        }
    }

    bool configSqLite3()
    {
        // configures memdb to use more memory, the default size is 1GB; this is 64GB
        // however memdb still is limited by sqlite3's max single memory block limit of 2GB.
        // We use our on extension memdb_ext instead, which does actually not read this config.
        int configErr = sqlite3_config(SQLITE_CONFIG_MEMDB_MAXSIZE, 0x1000000000uLL);
        if (configErr != SQLITE_OK) [[unlikely]]
        {
            return false;
        }
        // add memdb_ext vfs to support more than 2GB of memory.
        int memDbInitErr = sqlite3MemdbExtInit();
        if (memDbInitErr != SQLITE_OK) [[unlikely]]
        {
            return false;
        }
        return true;
    }

    void logConfigSqLite3Error()
    {
        GFXRECON_SQLITE_LOG_ERROR("configSqLite3 failed");
    }

    /** Whether the input is an api dump rather than a gfxr capture.
     *
     * Extension first, then a content sniff, because the profile folder names these .apidump while
     * the layer itself writes .json. DetectAPIs would reject either as a malformed gfxr, so the
     * branch has to happen before it.
     */
    bool isApiDumpFile(const std::string& filename)
    {
        if (filename.size() >= 8 && filename.compare(filename.size() - 8, 8, ".apidump") == 0)
        {
            return true;
        }

        std::ifstream input(filename, std::ios::binary);
        if (!input.is_open())
        {
            return false;
        }

        char c = 0;
        while (input.get(c))
        {
            if (std::isspace(static_cast<unsigned char>(c)) != 0)
            {
                continue;
            }

            // An api dump is a JSON array of frames; a gfxr capture starts with a binary magic.
            return c == '[';
        }

        return false;
    }

    void CreateDBHelper::createDatabase()
    {
        gfxrSqlite::DebugLogDuration log("OpenWorker::DoExecute");

        // setup gfxr logging
        gfxrecon::util::Log::Settings logSettings;
        if (m_logFilename.has_value())
        {
            logSettings.write_to_file = true;
            logSettings.file_name = m_logFilename.value();
            // just write to log file, don't duplicate output also to stdout.
            logSettings.write_to_console = false;
        }

        gfxrecon::util::Log::Init(logSettings.min_severity);
        gfxrecon::util::Log::UpdateWithSettings(logSettings);
        struct CloseLogHelper
        {
            ~CloseLogHelper() { gfxrecon::util::Log::Release(); }
        } closeLog;

        if (!m_inputFilename.has_value())
        {
            gfxrSqlite::debugLog("OpenWorker::Generate empty schema database");
            // generate empty schema db
            int err = sqlite3_open(m_dbFilename.c_str(), &m_db);
            if (err)
            {
                std::ostringstream errMsg;
                errMsg << "Failed to create database: " << sqlite3_errmsg(m_db);

                SetError(errMsg.str());
                return;
            }

            if (m_enforceForeignKeys)
            {
                gfxrecon::decode::ExecSQL(m_db, "PRAGMA foreign_keys = ON");
            }

            // construction of the consumer populates table schema
            {
                gfxrecon::decode::VulkanSqliteConsumerExt sqlite_consumer(m_db);
            }

            // immediately close the db
            checked_sqlite3_close(m_db);
            m_db = nullptr;
            return;
        }
        const auto& inputFilename = m_inputFilename.value();

        if (isApiDumpFile(inputFilename))
        {
            createDatabaseFromApiDump(inputFilename);
            return;
        }

        bool detected_d3d12 = false;
        bool detected_vulkan = false;
        bool detected_openxr = false;
        bool res =
            gfxrecon::decode::DetectAPIs(inputFilename.c_str(), detected_d3d12, detected_vulkan, detected_openxr);
        if (!res)
        {
            if (fileExists(inputFilename.c_str()))
            {
                SetError("Failed to detect APIs, file exists but is not a valid gfxr file.");
            }
            else
            {
                SetError("GFXR input file " + inputFilename + " does not exist");
            }
            return;
        }

        if (detected_d3d12)
        {
            SetError("Expected Vulkan based GFXR file, detected DirectX");
            return;
        }

        if (detected_openxr)
        {
            SetError("Expected Vulkan based GFXR file, detected OpenXR");
            return;
        }

        if (!detected_vulkan)
        {
            SetError("Expected Vulkan based GFXR file");
            return;
        }

        gfxrecon::decode::FileProcessor file_processor;
        if (!file_processor.Initialize(inputFilename.c_str()))
        {
            std::ostringstream errMsg;
            errMsg << "Failed to initialize trace";
            addErrorState(errMsg, file_processor);
            SetError(errMsg.str());
            return;
        }

        gfxrSqlite::debugLog("OpenWorker::Initialize");

        int err = sqlite3_open(m_dbFilename.c_str(), &m_db);
        if (err)
        {
            std::ostringstream errMsg;
            errMsg << "Failed to create database: " << sqlite3_errmsg(m_db);

            SetError(errMsg.str());
            return;
        }

        if (m_enforceForeignKeys)
        {
            gfxrecon::decode::ExecSQL(m_db, "PRAGMA foreign_keys = ON");
        }

        {
            gfxrecon::decode::VulkanSqliteConsumerExt sqlite_consumer(m_db);
            gfxrecon::decode::VulkanDecoder decoder;
            decoder.AddConsumer(&sqlite_consumer);
            file_processor.AddDecoder(&decoder);

            const std::string vulkan_version{ std::to_string(VK_VERSION_MAJOR(VK_HEADER_VERSION_COMPLETE)) + "." +
                                              std::to_string(VK_VERSION_MINOR(VK_HEADER_VERSION_COMPLETE)) + "." +
                                              std::to_string(VK_VERSION_PATCH(VK_HEADER_VERSION_COMPLETE)) };
            sqlite_consumer.Initialize(GetProjectVersionString(), vulkan_version, inputFilename);
            bool hasNextFrame = true;
            do
            {
                hasNextFrame = file_processor.ProcessNextFrame();
            } while (hasNextFrame);

            gfxrSqlite::debugLog("OpenWorker::Processed all frames");

            sqlite_consumer.PostInitialize();

            // the last frame is an extra frame due to frame delimitation being marked at end of frame
            // we remove it so as to not make it seem like we traced an additional frame with no data in it
            sqlite_consumer.TrimFinalFrame();
        }

        if (file_processor.GetErrorState() != gfxrecon::decode::BlockIOError::kErrorNone)
        {
            checked_sqlite3_close(m_db);
            m_db = nullptr;
            std::ostringstream errMsg;
            errMsg << "Failed to process trace";
            addErrorState(errMsg, file_processor);

            SetError(errMsg.str());
            return;
        }
    }


    void CreateDBHelper::createDatabaseFromApiDump(const std::string& inputFilename)
    {
        int err = sqlite3_open(m_dbFilename.c_str(), &m_db);
        if (err)
        {
            std::ostringstream errMsg;
            errMsg << "Failed to create database: " << sqlite3_errmsg(m_db);
            SetError(errMsg.str());
            return;
        }

        if (m_enforceForeignKeys)
        {
            gfxrecon::decode::ExecSQL(m_db, "PRAGMA foreign_keys = ON");
        }

        std::string readError;

        {
            // Identical to the gfxr path from here down: the same consumer, the same decoder, the
            // same finalisation. Only the thing feeding the decoder differs.
            gfxrecon::decode::VulkanSqliteConsumerExt sqlite_consumer(m_db);
            gfxrecon::decode::VulkanDecoder           decoder;
            decoder.AddConsumer(&sqlite_consumer);

            const std::string vulkan_version{ std::to_string(VK_VERSION_MAJOR(VK_HEADER_VERSION_COMPLETE)) + "." +
                                              std::to_string(VK_VERSION_MINOR(VK_HEADER_VERSION_COMPLETE)) + "." +
                                              std::to_string(VK_VERSION_PATCH(VK_HEADER_VERSION_COMPLETE)) };
            sqlite_consumer.Initialize(GetProjectVersionString(), vulkan_version, inputFilename);

            gfxrecon::decode::ApiDumpProcessor processor(
                decoder,
                [&sqlite_consumer](uint64_t apiEventId, uint64_t commandNumber) {
                    sqlite_consumer.InsertApiDumpCommandId(commandNumber, apiEventId);
                }
            );
            const bool ok = processor.ProcessFile(inputFilename, readError);

            GFXRECON_LOG_INFO("Converted api dump: %s", processor.DescribeConversion().c_str());

            // Persist the raw-address <-> assigned-handle-id pairing the processor discovered, so
            // tooling (e.g. shader extraction) can map the ids this database uses elsewhere (such as
            // shaderModules.handle) back to the address the api dump layer originally recorded for it.
            gfxrecon::decode::SqliteStatement insertHandleAddressStatement;
            gfxrecon::decode::PrepareStatement(
                m_db, "INSERT INTO apiDumpHandleAddresses VALUES (?, ?);", &insertHandleAddressStatement
            );
            for (const auto& minted : processor.Handles().MintedIds())
            {
                // Variable width, no zero padding, to match the api dump layer's own hex formatting
                // of handle values exactly (a VkShaderModule handle prints as e.g. "0x210000000021",
                // not zero-padded to 16 digits the way a full pointer address happens to be).
                const std::string address = gfxrecon::decode::to_hex_variable_width(minted.address);
                GFXRECON_SQLITE_CHECK(m_db, sqlite3_reset(insertHandleAddressStatement));
                GFXRECON_SQLITE_CHECK(
                    m_db, sqlite3_bind_int64(insertHandleAddressStatement, 1, static_cast<sqlite_int64>(minted.id))
                );
                GFXRECON_SQLITE_CHECK(
                    m_db,
                    sqlite3_bind_text64(
                        insertHandleAddressStatement, 2, address.data(), address.size(), SQLITE_STATIC, SQLITE_UTF8
                    )
                );
                GFXRECON_SQLITE_CHECK_DONE(m_db, sqlite3_step(insertHandleAddressStatement));
            }

            sqlite_consumer.PostInitialize();

            // As on the gfxr path, frame delimitation leaves a trailing empty frame behind.
            sqlite_consumer.TrimFinalFrame();

            if (!ok)
            {
                // A capture cut short by the app being killed is the common case, and everything
                // before the truncation is already in the database, so the rows are kept and the
                // problem is reported rather than discarding the conversion.
                GFXRECON_LOG_WARNING("Api dump ended early: %s", readError.c_str());
            }
        }
    }

} // namespace gfxrSqlite
