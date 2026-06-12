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

#include <filesystem> // For path manipulation (C++17 and later)
#include <iostream>   // For input/output operations
#include <optional>
#include <string> // For using std::string
#include <thread>

#include "create_db_helper.h"
#include "memdb_ext.h"
#include "sqlite3.h"

namespace {
// Reads the given .gfxr file and converts it to an in-memory database.
// Returns the pointer to the in-memory database, or nullptr at errors.
//
// Although this program will export the database to the disk later, an
// in-memory database is used because in the future Sherlock may access
// the database purely in memory, saving the cost to save/load it.
sqlite3 *openGfxrAsDatabase(const std::string &filePath) {
  int memDbInitErr = sqlite3MemdbExtInit();
  if (memDbInitErr != SQLITE_OK) [[unlikely]] {
    return nullptr;
  }

  std::string dbPath = "file:/memdb0?vfs=memdb_ext";
  std::optional<std::string> logFilename;
  bool hasHandledError = false;
  auto errorHandler = [&hasHandledError](const std::string &err) {
    hasHandledError = true;
    std::cerr << "ERROR: " << err << "\n";
  };

  gfxrSqlite::CreateDBHelper helper{filePath, dbPath, logFilename,
                                    // None of the callers of
                                    // `GFXRDataService.createGFXRDatabase`
                                    // in Application enforces foreign keys.
                                    false, errorHandler};
  helper.createDatabase();
  return hasHandledError ? nullptr : helper.getDB();
}

// Exports the given in-memory source database to a file on disk.
int exportDatabase(sqlite3 *sourceDb, const char *destinationFilename) {
  sqlite3 *destinationDb;
  int rc = sqlite3_open(destinationFilename, &destinationDb);
  if (rc != SQLITE_OK) {
    std::cerr << "ERROR: Cannot open destination database: "
              << sqlite3_errmsg(destinationDb) << "\n";
    sqlite3_close(destinationDb);
    return rc;
  }

  sqlite3_backup *backup =
      sqlite3_backup_init(destinationDb, "main", sourceDb, "main");
  if (backup) {
    do {
      rc = sqlite3_backup_step(backup, -1); // -1 copies all remaining pages
      if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED) {
        // Handle BUSY/LOCKED.  For simplicity, we'll just wait.
        // In a real application, you'd likely use a more sophisticated retry
        // mechanism.
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
      }
    } while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

    sqlite3_backup_finish(backup);
  }
  rc = sqlite3_errcode(destinationDb);
  sqlite3_close(destinationDb);
  return rc;
}
} // namespace

int main(int argc, char *argv[]) {
  // Check for optional output file path
  std::string outputPath;
  std::string gfxrFilePath;

  if (argc == 2) {
    gfxrFilePath = argv[1];
    outputPath = gfxrFilePath + ".sqlite3";
  } else if (argc == 4 && std::string(argv[1]) == "-o") {
    outputPath = argv[2];
    gfxrFilePath = argv[3];
  } else {
    std::cerr << "Usage: " << argv[0]
              << " [-o <output_path>] <path_to_gfxr_file>\n";
    return EXIT_FAILURE;
  }

  try {
    // If the output file exists, remove it.
    if (std::filesystem::exists(outputPath)) {
      std::filesystem::remove(outputPath);
    }

    sqlite3 *inMemoryDb = openGfxrAsDatabase(gfxrFilePath);
    if (inMemoryDb == nullptr) {
      std::cerr << "ERROR: Failed to convert file " << gfxrFilePath
                << " to a database\n";
      return EXIT_FAILURE;
    }

    if (SQLITE_OK != exportDatabase(inMemoryDb, outputPath.c_str())) {
      std::cerr << "ERROR: Failed to export database\n";
      return EXIT_FAILURE;
    }

    std::cout << "Database written to " << outputPath << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "ERROR: An unexpected error occurred: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
