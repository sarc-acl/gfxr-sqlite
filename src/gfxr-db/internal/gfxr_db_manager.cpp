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

#include "gfxr_db_manager.h"

#include <sstream>

#include "create_db_helper.h"
#include "debug_log.h"

namespace gfxrSqlite
{
    void GfxrDbConnection::Release()
    {
        if (m_dbManager != nullptr && m_db != nullptr)
        {
            m_dbManager->ReleaseConnection(m_db);
            m_dbManager = nullptr;
            m_db = nullptr;
        }
    }

    GfxrDbManager::GfxrDbManager()
    {
        gfxrSqlite::debugLog("GfxrDbManager");
    }

    GfxrDbManager::~GfxrDbManager()
    {
        gfxrSqlite::debugLog("~GfxrDbManager");
        logErrorIfNot(
            m_dbConnections.size() == m_unusedConnections.size(),
            "Ongoing queries, %lld",
            static_cast<long long>(m_dbConnections.size() - m_unusedConnections.size())
        );

        logErrorIfNot(m_dbConnections.empty(), "Error, sqlite3 database was not explicitly closed!");

        InternalCloseAllDbs();
    }

    bool GfxrDbManager::Init(std::optional<std::string> dbFilename)
    {
        gfxrSqlite::DebugLogDuration log("GfxrDbManager::Init");

        if (m_state != State::Created)
        {
            // Invalid state, each instance must be initialized only once.
            return false;
        }
        m_state = State::Opening;

        if (dbFilename.has_value() && !dbFilename.value().empty())
        {
            m_dbFilename = dbFilename.value();
        }
        else
        {
            m_dbFilename = createNewMemoryDbFilename();
        }
        return true;
    }

    void GfxrDbManager::SetDB(sqlite3* db)
    {
        gfxrSqlite::DebugLogDuration log("GfxrDbManager::SetDB");

        logErrorIfNot(m_state == State::Opening, "error: Unexpected state %d in SdtDB", static_cast<int>(m_state));

        // report of (worker thread) DB opening request. Is called with a nullptr db if opening failed.
        logErrorIfNot(m_dbConnections.empty(), "expected no use before SetDB");
        if (db)
        {
            m_dbConnections.push_back(db);
            m_unusedConnections.push_back(db);
            m_state = State::Open;
        }
        else
        {
            m_state = State::Closed;
        }
    }

    std::pair<std::shared_ptr<GfxrDbConnection>, std::string> GfxrDbManager::RequestConnection()
    {
        gfxrSqlite::DebugLogDuration log("GfxrDbManager::RequestConnection");

        if (m_state != State::Open)
        {
            return { nullptr, "Invalid state, database not in open state" };
        }

        if (m_dbConnections.empty())
        {
            return { nullptr, "Database is not open" };
        }

        // Find or if necessary create a database connection
        sqlite3* db = nullptr;
        if (m_unusedConnections.empty())
        {
            int openErr = sqlite3_open(m_dbFilename.c_str(), &db);
            if (openErr)
            {
                std::ostringstream errMsg;
                errMsg << "Failed to open database " << m_dbFilename << ": " << sqlite3_errmsg(db);
                // On failure, close the handle sqlite3_open may have returned
                if (db)
                {
                    sqlite3_close(db);
                }
                return { nullptr, errMsg.str() };
            }
            m_dbConnections.push_back(db);
        }
        else
        {
            db = m_unusedConnections.back();
            m_unusedConnections.pop_back();
        }

        // On success, create the connection wrapper and return it in a shared_ptr
        return { std::make_shared<GfxrDbConnection>(this, db), "" };
    }

    void GfxrDbManager::ReleaseConnection(sqlite3* db)
    {
        gfxrSqlite::DebugLogDuration log("GfxrDbManager::ReleaseConnection");

        m_unusedConnections.push_back(db);
        DelayedClose();
    }

    std::string GfxrDbManager::Close()
    {
        gfxrSqlite::DebugLogDuration log("GfxrDbManager::Close");

        // Allowing to call close when already closed for simpler error handling in clients.
        if (m_state == State::Closed || m_state == State::Closing)
        {
            return "";
        }

        if (m_state != State::Open)
        {
            return "Invalid state, database not in open state";
        }

        if (m_dbConnections.empty())
        {
            return "Database is not open";
        }
        m_state = State::Closing;

        DelayedClose();

        return "";
    }

    void GfxrDbManager::DelayedClose()
    {
        logErrorIfNot(
            m_state == State::Closing || m_state == State::Open,
            "error: Unexpected state %d in DelayedClose",
            static_cast<int>(m_state)
        );

        if (m_state == State::Closing && m_dbConnections.size() == m_unusedConnections.size())
        {
            InternalCloseAllDbs();
            m_state = State::Closed;
        }
    }

    void GfxrDbManager::InternalCloseAllDbs()
    {
        logErrorIfNot(m_dbConnections.size() == m_unusedConnections.size(), "connections still in use");
        for (auto& connection : m_dbConnections)
        {
            checked_sqlite3_close(connection);
            connection = nullptr;
        }
        m_dbConnections.clear();
        m_unusedConnections.clear();
    }
} // namespace gfxrSqlite
