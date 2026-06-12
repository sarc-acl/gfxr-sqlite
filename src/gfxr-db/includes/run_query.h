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

#ifndef RUN_QUERY_H
#define RUN_QUERY_H

#include "sqlite3.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace gfxrSqlite
{
    class RunQuery
    {
      public:
        RunQuery(sqlite3* db, const char* sql_query) : m_db{ db }, m_sql_query{ sql_query } {}

        using ResultRow = std::vector<std::variant<std::string, std::nullptr_t, double, std::int64_t>>;

        bool run(std::string* errorDetails)
        {
            sqlite3_stmt* stmt = nullptr;
            int err = sqlite3_prepare_v2(m_db, m_sql_query.c_str(), -1, &stmt, NULL);
            if (SQLITE_OK != err)
            {
                *errorDetails = "Failed to prepare query.  Is the query valid? ErrorCode: " + std::to_string(err) +
                    " - " + sqlite3_errmsg(m_db) + "\n" + m_sql_query;
                return false;
            }
            try
            {
                for (int i = 0; i < sqlite3_column_count(stmt); i++)
                {
                    m_headers.push_back(sqlite3_column_name(stmt, i));
                }

                while (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    ResultRow columns;

                    for (int i = 0; i < sqlite3_column_count(stmt); i++)
                    {
                        auto colType = sqlite3_column_type(stmt, i);
                        if (colType == SQLITE_NULL)
                        {
                            columns.emplace_back(nullptr);
                        }
                        else if (colType == SQLITE_BLOB)
                        {
                            // We don't support binary data, use other services to retrieve the information.
                            columns.emplace_back(std::string("[Binary Data]"));
                        }
                        else if (colType == SQLITE_INTEGER)
                        {
                            columns.emplace_back(sqlite3_column_int64(stmt, i));
                        }
                        else if (colType == SQLITE_FLOAT)
                        {
                            columns.emplace_back(sqlite3_column_double(stmt, i));
                        }
                        else
                        {
                            const char* columnText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                            columns.emplace_back(columnText);
                        }
                    }
                    m_rows.emplace_back(std::move(columns));
                }

                return SqlFinalize(stmt, errorDetails);
            }
            catch (...)
            {
                SqlFinalize(stmt, errorDetails);
                throw;
            }
        }

        const std::vector<std::string>& Headers() const { return m_headers; }
        const std::vector<ResultRow>& Rows() const { return m_rows; }

      private:
        bool SqlFinalize(sqlite3_stmt* stmt, std::string* errorDetails)
        {
            int err = sqlite3_finalize(stmt);
            if (SQLITE_OK != err)
            {
                *errorDetails =
                    "Failed to finalize query. ErrorCode: " + std::to_string(err) + " - " + sqlite3_errmsg(m_db);
                return false;
            }
            return true;
        }

        sqlite3* m_db{ nullptr };
        std::string m_sql_query;
        std::vector<std::string> m_headers;
        std::vector<ResultRow> m_rows;
    };

} // namespace gfxrSqlite
#endif // RUN_QUERY_H
