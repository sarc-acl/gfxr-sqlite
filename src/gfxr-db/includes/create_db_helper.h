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

#ifndef CREATE_DB_HELPER_H
#define CREATE_DB_HELPER_H

#include <cstdarg>
#include <cstdint>
#include <string>
#include <functional>
#include <optional>
#include <sstream>

#include "sqlite3.h"

#include "debug_log.h"

namespace gfxrSqlite
{

    /** Log helper function, logs if condition is false. Supports printf style formatting. */
    inline void logErrorIfNot(bool condition, const char* format, ...)
    {
        if (!condition)
        {
            va_list args;
            va_start(args, format);
            vfprintf(stderr, format, args);
            va_end(args);
            fprintf(stderr, "\n");
        }
    }
    inline void checked_sqlite3_close(sqlite3* db)
    {
        gfxrSqlite::debugLog("checked_sqlite3_close");
        int res = sqlite3_close(db);
        logErrorIfNot(res == SQLITE_OK, "failed to close sqlite3 db");
    }

    bool configSqLite3();

    /** A wrapper function to avoid #include tree of `gfxreconstruct` in this header file. */
    void logConfigSqLite3Error();

    /** Create a unique in-memory database file name using the memdb virtual file system. */
    std::string createNewMemoryDbFilename();

    using ReportErrorHandler = std::function<void(const std::string& error)>;

    /** Class to create an SQL database from an GFXR */
    class CreateDBHelper
    {
      public:
        CreateDBHelper(
            const std::optional<std::string>& inputFilename,
            const std::string& dbFilename,
            const std::optional<std::string>& logFilename,
            bool enforceForeignKeys,
            ReportErrorHandler reportError
        ) :
            m_inputFilename{ inputFilename }, m_dbFilename{ dbFilename }, m_logFilename{ logFilename },
            m_enforceForeignKeys{ enforceForeignKeys }, m_reportErrorHandler(reportError)
        {}

        void createDatabase();

        sqlite3* getDB() const { return m_db; }

      private:
        void SetError(const std::string& error) { m_reportErrorHandler(error); }

        sqlite3* m_db{ nullptr };
        std::optional<std::string> m_inputFilename; // No m_inputFilename means to create empty schema db
        std::string m_dbFilename;                 // database filename or sqlite special name for an in memory database.
        std::optional<std::string> m_logFilename; // if set logs to the file
        bool m_enforceForeignKeys;
        ReportErrorHandler m_reportErrorHandler;
    };
} // namespace gfxrSqlite

#endif // CREATE_DB_HELPER_H
