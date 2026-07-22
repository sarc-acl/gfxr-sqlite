/********************************************************************************
    Copyright 2024-2025 The Sokatoa Project Authors

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

#ifndef GFXRECON_DECODE_SQLITE_UTILS_H
#define GFXRECON_DECODE_SQLITE_UTILS_H

#include "util/defines.h"
#include "util/logging.h"

#include "sqlite3.h"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <optional>
#include <ostream>
#include <sstream>
#include <type_traits>
#include <variant>

#define GFXRECON_SQLITE_LOG_WARNING(message, ...) GFXRECON_LOG_WARNING("SQLite Consumer - " message, ##__VA_ARGS__);
#define GFXRECON_SQLITE_LOG_ERROR(message, ...) GFXRECON_LOG_ERROR("SQLite Consumer - " message, ##__VA_ARGS__);

#define GFXRECON_SQLITE_LOG_WARNING_ONCE(message, ...) \
    GFXRECON_LOG_WARNING_ONCE("SQLite Consumer - " message, ##__VA_ARGS__);

#define GFXRECON_SQLITE_CHECK(db, statement)              \
    do                                                    \
    {                                                     \
        int err = statement;                              \
        if (err != SQLITE_OK) [[unlikely]]                \
        {                                                 \
            GFXRECON_SQLITE_LOG_ERROR(                    \
                "Error %d at offset %d running %s: %s\n", \
                err,                                      \
                sqlite3_error_offset(db),                 \
                #statement,                               \
                sqlite3_errmsg(db)                        \
            );                                            \
        }                                                 \
    } while (false)

#define GFXRECON_SQLITE_CHECK_DONE(db, statement)         \
    do                                                    \
    {                                                     \
        int err = statement;                              \
        if (err != SQLITE_DONE) [[unlikely]]              \
        {                                                 \
            GFXRECON_SQLITE_LOG_ERROR(                    \
                "Error %d at offset %d running %s: %s\n", \
                err,                                      \
                sqlite3_error_offset(db),                 \
                #statement,                               \
                sqlite3_errmsg(db)                        \
            );                                            \
        }                                                 \
    } while (false)

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

namespace impl
{
    template <typename T>
    struct to_arg_type_helper
    {
        using Type = T;
    };

    template <>
    struct to_arg_type_helper<std::string>
    {
        using Type = std::string_view;
    };
} // namespace impl

// For value passing, map a type to type to use for argument passing.
// E.g. std::string to std::string_view.
template <typename T>
using to_arg_type = impl::to_arg_type_helper<T>::Type;

// concept for rejecting suboptimal argument types
//
// instantiate the template with std::string_view instead of std::string.
// Avoids possible memory copying just to pass the argument around
template <class T>
concept invalid_arg_type = std::is_same_v<T, std::string>;

template <typename T>
std::string to_hex_variable_width(T value)
{
    std::ostringstream stream;
    stream << "0x" << std::hex << value;
    return stream.str();
}

template <typename T>
std::string to_hex_fixed_width(T value)
{
    std::ostringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << value;
    return stream.str();
}

inline std::string uuid_to_string(uint32_t size, const uint8_t* uuid)
{
    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex;
    for (size_t i = 0; i < size; ++i)
    {
        stream << (uint32_t)uuid[i];
    }
    return stream.str();
}

// Wrapper to automatically finalize a statement
class SqliteStatement final
{
  public:
    SqliteStatement() = default;
    ~SqliteStatement()
    {
        // Calling sqlite3_finalize(nullptr) is a no-op
        sqlite3_finalize(statement);
    }
    SqliteStatement(const SqliteStatement& other) = delete;
    SqliteStatement& operator=(const SqliteStatement& other) = delete;

    operator sqlite3_stmt*() const { return statement; }

    sqlite3_stmt* statement = nullptr;
};

template <int N>
inline void PrepareStatement(sqlite3* db, const char (&sql)[N], SqliteStatement* statement)
{
    if (statement->statement != nullptr)
    {
        // Likely indicates a copy/paste error with the same statement object passed to multiple PrepareStatement calls
        GFXRECON_LOG_WARNING(
            "Preparing statement with query\n%s\nbut it was already prepared with query\n%s",
            sql,
            sqlite3_sql(statement->statement)
        );
        GFXRECON_SQLITE_CHECK(db, sqlite3_finalize(statement->statement));
    }

    // sqlite3_prepare_v3 wants a null-terminated string and a size including that null terminator (otherwise it needs
    // to copy the string). This function takes a fixed-size char array, and N includes that null terminator.

    // https://www.sqlite.org/c3ref/c_prepare_normalize.html#sqlitepreparepersistent gives better performance for
    // queries that will be ran many times.
    int err = sqlite3_prepare_v3(db, sql, N, SQLITE_PREPARE_PERSISTENT, &statement->statement, nullptr);
    if (err != SQLITE_OK)
    {
        GFXRECON_SQLITE_LOG_ERROR(
            "Error %d preparing statement at offset %d: %s\nQuery:\n%s",
            err,
            sqlite3_error_offset(db),
            sqlite3_errmsg(db),
            sql
        );
    }
}

inline void PrepareStatement(sqlite3* db, const std::string& sql, SqliteStatement* statement)
{
    if (statement->statement != nullptr)
    {
        // Likely indicates a copy/paste error with the same statement object passed to multiple PrepareStatement calls
        GFXRECON_LOG_WARNING(
            "Preparing statement with query\n%s\nbut it was already prepared with query\n%s",
            sql.c_str(),
            sqlite3_sql(statement->statement)
        );
        GFXRECON_SQLITE_CHECK(db, sqlite3_finalize(statement->statement));
    }

    // sqlite3_prepare_v3 wants a null-terminated string and a size including that null terminator (otherwise it needs
    // to copy the string) and std::string_view isn't guaranteed to be null-terminated (since it can be a substring).
    // In practice, according to https://stackoverflow.com/a/57257485, string_view literals are null-terminated, but
    // it's easier to just take a std::string here (which might be copied from a string_view if needed) and provide a/
    // second version for string literals.

    // https://www.sqlite.org/c3ref/c_prepare_normalize.html#sqlitepreparepersistent gives better performance for
    // queries that will be ran many times.
    int err = sqlite3_prepare_v3(
        db, sql.c_str(), static_cast<int>(sql.size() + 1), SQLITE_PREPARE_PERSISTENT, &statement->statement, nullptr
    );
    if (err != SQLITE_OK)
    {
        GFXRECON_SQLITE_LOG_ERROR(
            "Error %d preparing statement at offset %d: %s\nQuery:\n%s",
            err,
            sqlite3_error_offset(db),
            sqlite3_errmsg(db),
            sql.c_str()
        );
    }
}

template <typename T>
    requires(!invalid_arg_type<T>)
inline int BindGeneric(sqlite3_stmt* statement, int index, const T& value)
{
    constexpr bool is_string_assignable = std::is_assignable_v<std::string_view, T>;
    constexpr bool is_int = std::is_integral_v<T> || std::is_enum_v<T>;
    constexpr bool is_float = std::is_floating_point_v<T>;

    static_assert(is_string_assignable || is_int || is_float);

    if constexpr (is_string_assignable)
    {
        std::string_view v = value;
        return sqlite3_bind_text64(statement, index, v.data(), v.size(), SQLITE_STATIC, SQLITE_UTF8);
    }
    else if constexpr (is_int)
    {
        static_assert(sizeof(T) <= sizeof(sqlite_int64));
        return sqlite3_bind_int64(statement, index, static_cast<sqlite_int64>(value));
    }
    else if constexpr (is_float)
    {
        static_assert(sizeof(T) <= sizeof(double));
        return sqlite3_bind_double(statement, index, static_cast<double>(value));
    }
}

inline int BindOptInt64(sqlite3_stmt* statement, int index, std::optional<int64_t> value)
{
    if (value.has_value())
    {
        return sqlite3_bind_int64(statement, index, value.value());
    }
    else
    {
        return sqlite3_bind_null(statement, index);
    }
}

inline std::optional<int64_t> ColumnOptInt64(sqlite3_stmt* statement, int index)
{
    if (sqlite3_column_type(statement, index) == SQLITE_NULL)
    {
        return std::nullopt;
    }
    else
    {
        return static_cast<int64_t>(sqlite3_column_int64(statement, index));
    }
}

inline int BindOptDouble(sqlite3_stmt* statement, int index, std::optional<double> value)
{
    if (value.has_value())
    {
        return sqlite3_bind_double(statement, index, value.value());
    }
    else
    {
        return sqlite3_bind_null(statement, index);
    }
}

[[nodiscard]] inline std::string ValueOrNull(std::optional<int64_t> value)
{
    if (value.has_value())
    {
        return std::to_string(value.value());
    }
    else
    {
        return "NULL";
    }
}

inline void ExecSQL(sqlite3* db, const char* sql)
{
    char* errMsg = NULL;
    int err = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (err != SQLITE_OK)
    {
        GFXRECON_SQLITE_LOG_ERROR("Error %d at offset %d running %s: %s\n", err, sqlite3_error_offset(db), sql, errMsg);
        sqlite3_free(errMsg);
    }
}

using SQLData = std::variant<std::string, double, sqlite3_int64, std::nullptr_t>;
using SQLRowData = std::vector<SQLData>;
using SQLResults = std::vector<SQLRowData>;

inline const SQLData NullPtr{ nullptr };

[[nodiscard]] inline SQLResults ExecSQLWithResult(sqlite3* db, const char* sql)
{
    SQLResults rows;
    sqlite3_stmt* stmt = nullptr;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (SQLITE_OK != err)
    {
        GFXRECON_SQLITE_LOG_ERROR(
            "Failed to prepare query.  Is the query valid? ErrorCode: %d - %s \n %s", err, sqlite3_errmsg(db), sql
        );
        return rows;
    }
    try
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            SQLRowData columns;
            for (int i = 0; i < sqlite3_column_count(stmt); i++)
            {
                auto colType = sqlite3_column_type(stmt, i);
                if (colType == SQLITE_NULL)
                {
                    columns.push_back(NullPtr);
                }
                else if (colType == SQLITE_BLOB)
                {
                    // We don't support binary data, use other services to retrieve the information.
                    columns.push_back(std::string("[Binary Data]"));
                }
                else if (colType == SQLITE_INTEGER)
                {
                    columns.push_back(sqlite3_column_int64(stmt, i));
                }
                else if (colType == SQLITE_FLOAT)
                {
                    columns.push_back(sqlite3_column_double(stmt, i));
                }
                else
                {
                    const char* columnText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    columns.push_back(columnText);
                }
            }
            rows.emplace_back(std::move(columns));
        }
    }
    catch (...)
    {
        GFXRECON_SQLITE_LOG_ERROR("Received unknown exception while processing sqlite query");
        // don't rethrow here, just return an empty result (clear partial results)
        rows.clear();
    }

    err = sqlite3_finalize(stmt);
    if (SQLITE_OK != err)
    {
        GFXRECON_SQLITE_LOG_ERROR("Failed to finalize query. ErrorCode: %d - %s", err, sqlite3_errmsg(db));
    }
    return rows;
}

// type used for overloading the operator << for ostream.
template <class T>
struct EscapedFormatting
{
    const T& field;
};

// Escape for SQL-Lite, prints every single quote twice
inline void escapedStream(std::ostream& os, std::string_view f)
{
    auto pos = f.data();
    const auto end = f.data() + f.size();
    auto next = std::find(pos, end, '\'');
    while (next != end)
    {
        os << std::string_view(pos, next - pos) << '\'';
        pos = next;
        next = std::find(next + 1, end, '\'');
    }
    os << std::string_view(pos, next - pos);
}

// custom formatting with escaping
template <class T>
inline std::ostream& operator<<(std::ostream& os, const EscapedFormatting<T>& f)
{
    if constexpr (std::is_assignable_v<std::string_view, T>)
    {
        // For strings (string_view, string, const char*) escape.
        escapedStream(os, std::string_view(f.field));
    }
    else
    {
        os << f.field;
    }
    return os;
}

/** Helper function to print a type in a SQL escaped format, more specifically to double any single quote
 *
 * E.g.:
 * int main() {
 *     std::cout << sqlEscape("He'llo ") << sqlEscape(2) << " Don't escape this";
 *     return 0;
 * }
 */

template <class T>
inline EscapedFormatting<T> sqlEscape(const T& t)
{
    return { t };
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_SQLITE_UTILS_H
