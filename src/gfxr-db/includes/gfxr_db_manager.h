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

#ifndef GFXR_DB_MANAGER_H
#define GFXR_DB_MANAGER_H

#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "sqlite3.h"

namespace gfxrSqlite
{
    class GfxrDbManager;

    /** A database connection managed by a GfxrDbManager. */
    class GfxrDbConnection
    {
      public:
        /**
         * @brief Construct a new GfxrDbConnection object.
         *
         * Acquires and manages a database connection from a GfxrDbManager.
         * @param manager The manager that owns the connection.
         * @param database The sqlite3 database handle.
         */
        GfxrDbConnection(GfxrDbManager* manager, sqlite3* database) : m_dbManager(manager), m_db(database) {}

        ~GfxrDbConnection() { Release(); }

        /**
         * Releases the sqlite3 connection back to the manager. The instance becomes invalid
         * afterwards.
         */
        void Release();

        sqlite3* db() const { return m_db; }

      private:
        GfxrDbManager* m_dbManager = nullptr;
        sqlite3* m_db = nullptr;

        GfxrDbConnection(const GfxrDbConnection&) = delete;
        GfxrDbConnection& operator=(const GfxrDbConnection&) = delete;
        GfxrDbConnection(GfxrDbConnection&&) = delete;
        GfxrDbConnection& operator=(GfxrDbConnection&&) = delete;
    };

    /**
     * The database manager for a GFXR file.
     *
     * Create a new instance to open a different GFXR file.
     */
    class GfxrDbManager
    {
      public:
        GfxrDbManager();
        ~GfxrDbManager();

        /**
         * @brief Initializes the database manager with a specified or generated filename.
         *
         * This function prepares the GfxrDbManager instance for opening a database.
         * It validates that the manager is in a 'Created' state before proceeding,
         * ensuring that initialization only occurs once per object instance.
         *
         * The function determines the filename for the database connection. If a valid
         * file path is provided, it will be used. Otherwise, a unique name for a new
         * in-memory database will be generated.
         *
         * @param dbFilename An optional string containing the path to the database file.
         * - If a non-empty string is provided, that path will be used.
         * - If the optional is empty or contains an empty string, a name
         * for a new in-memory database will be generated internally.
         *
         * @return true on success.
         *
         * @note This method must be called before any other database operations. It is an
         * error to call it more than once on the same instance.
         */
        bool Init(std::optional<std::string> dbFilename);

        const std::string& getDbFilename() const { return m_dbFilename; }

        /**
         * @brief Sets the active database connection for the manager.
         *
         * This function is typically called by a worker thread after a database file has
         * been successfully opened. It hands off the connection handle to the manager,
         * adds it to the connection pool, and transitions the manager state to Open.
         *
         * @param db A pointer to the active sqlite3 database handle. If nullptr, it
         * indicates a failure to open, and the manager state is set to Closed.
         */
        void SetDB(sqlite3* db);

        /**
         * @brief Acquires a database connection to perform a query.
         *
         * Before executing a query, this function is called to get an available sqlite3
         * connection from the pool. If all connections are in use, it dynamically opens a
         * new one. It also increments the counter for currently running queries.
         *
         * @return A std::pair containing the GfxrDbConnection handle and an error string.
         * On failure (e.g., manager is not open, or a new connection fails),
         * the handle will be nullptr and the string will contain the error message.
         */
        std::pair<std::shared_ptr<GfxrDbConnection>, std::string> RequestConnection();

        /**
         * @brief Releases a database connection after a query is complete.
         *
         * This function returns the sqlite3 handle to the pool of unused connections,
         * making it available for subsequent queries.
         *
         * @param db The sqlite3 handle that is no longer in use.
         *
         * @note The `Release` function and destruction of a GfxrDbConnection object returned by
         *  `RequestConnection` will automatically release the connection to the manager (done by
         *  invoking `ReleaseConnection`). It's usually unnecessary to explicitly call
         * `ReleaseConnection` anywhere else.
         */
        void ReleaseConnection(sqlite3* db);

        /**
         * @brief Initiates the closing of all database connections.
         *
         * This function transitions the manager's state to Closing. The actual
         * closing of connections is deferred until all currently running queries
         * have completed. It's safe to call this even if the manager is already
         * closed.
         *
         * @return An empty string on success, or an error message if the manager
         * is in an invalid state.
         */
        std::string Close();

      private:
        /**
         * @brief Checks if conditions are met to perform the actual close operation.
         *
         * If the manager is in the 'Closing' state and there are no
         * more running queries, it proceeds to close all database connections.
         */
        void DelayedClose();

        /**
         * @brief Forcibly closes all open sqlite3 connections.
         *
         * This internal helper iterates through the entire pool of database
         * connections, closes each one, and clears the internal tracking lists. It
         * logs an error if any connections were still marked as 'in-use'.
         */
        void InternalCloseAllDbs();

        // All the DB connections which were opened
        std::vector<sqlite3*> m_dbConnections;
        // All the currently unused db connections. Connections are removed while running a query.
        std::vector<sqlite3*> m_unusedConnections;

        std::string m_dbFilename; // database filename or sqlite special name for an in memory database.

        enum class State
        {
            Created, // initial state
            Opening, // while trying to open
            Open,    // successful open
            Closing, // got request to close, but still ongoing requests
            Closed   // closed after being open, or when opening failed.
        };
        State m_state{ State::Created };

        GfxrDbManager(const GfxrDbManager&) = delete;
        GfxrDbManager& operator=(const GfxrDbManager&) = delete;
        GfxrDbManager(GfxrDbManager&&) = delete;
        GfxrDbManager& operator=(GfxrDbManager&&) = delete;
    };

} // namespace gfxrSqlite

#endif // GFXR_DB_MANAGER_H
