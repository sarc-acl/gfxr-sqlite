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
#include <string>
#include <sstream>

#include "decode/vulkan_sqlite_consumer_ext.h"

// gfxreconstruct header
#include PROJECT_VERSION_HEADER_FILE
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

} // namespace gfxrSqlite
