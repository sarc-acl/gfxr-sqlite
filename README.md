# gfxr-sqlite

A C++ library and command-line tool for decoding [GFXReconstruct](https://github.com/LunarG/gfxreconstruct) `.gfxr` Vulkan capture files into [SQLite](https://www.sqlite.org/) databases.

The resulting database exposes Vulkan API events, command buffers, descriptors, resources, and per-frame state as queryable SQL tables, making it convenient to analyze and visualize Vulkan workloads.

## What's in the box

| Target              | Type       | Purpose                                                                                  |
| ------------------- | ---------- | ---------------------------------------------------------------------------------------- |
| `gfxr-sqlite-library`   | static lib | Core decoder. Embeds SQLite. Links against gfxreconstruct's `decode`/`format`/`util`.    |
| `gfxr-sqlite`       | executable | CLI wrapper that converts a single `.gfxr` file to a `.sqlite3` file on disk.            |
| `gfxr-sqlite-test`      | executable | Native C++ test for the library.                                                         |

## Building standalone

### Prerequisites

-   CMake 3.15+
-   A C++20 compiler (MSVC 2019+, Clang 12+, or GCC 11+)
-   Python 3.8+ (used by gfxreconstruct's build scripts and the SQLite-consumer code generators)
-   Platform libraries: zlib, lz4 (zstd optional)
    -   Linux: `apt install zlib1g-dev liblz4-dev libzstd-dev`
    -   macOS: bundled in `external/gfxreconstruct/external/precompiled/macos`
    -   Windows: bundled in `external/gfxreconstruct/external/precompiled/win64`

### One-step build (recommended)

The repo ships with a top-level build script that handles submodule init, builds gfxreconstruct, and builds gfxr-sqlite end-to-end:

```bash
git clone https://github.com/sarc-acl/gfxr-sqlite.git
cd gfxr-sqlite
python3 scripts/build.py
```

That's it — the script:

1. Initializes the nested `external/gfxreconstruct` submodule (overriding the `update = none` set in `.gitmodules`).
2. Builds gfxreconstruct via [scripts/build_dependencies.py](scripts/build_dependencies.py) with the same flags Sokatoa uses (no OpenXR, no D3D12, hidden symbol visibility).
3. Configures and builds the gfxr-sqlite CMake project.

Options:

```bash
python3 scripts/build.py debug              # debug build (default is release)
python3 scripts/build.py --clean            # clean rebuild (deps + project)
python3 scripts/build.py --skip-deps        # skip the gfxreconstruct rebuild
python3 scripts/build.py -j 8               # limit parallel compile jobs to 8
                                            # (default 0 = all cores)
```

If you only need to (re-)build the gfxreconstruct dependency:

```bash
python3 scripts/build_dependencies.py [release|debug] [--clean] [-j N]
```

Artifacts land under `out/build/` (or `out/dbuild/` for debug):

-   `gfxr-sqlite` (or `Release/gfxr-sqlite.exe` on MSVC) — the CLI
-   `libgfxr-sqlite-library.a` (or `gfxr-sqlite-library.lib`) — the static library
-   `gfxr-sqlite-test` — the native test executable

### Manual build

If you'd rather drive each step yourself (or you already have a built gfxreconstruct elsewhere on disk), the manual flow is:

```bash
# 1. Init the nested gfxreconstruct submodule (the `-c` flag overrides update=none).
git -c submodule.external/gfxreconstruct.update=checkout \
    submodule update --init --recursive external/gfxreconstruct

# 2. Build gfxreconstruct.
( cd external/gfxreconstruct && \
  python3 scripts/build.py -c release \
    --skip-check-code-style --skip-tests --skip-d3d12-support \
    --cmake-extra=GFXRECON_ENABLE_OPENXR=OFF \
    --cmake-extra=CMAKE_CXX_VISIBILITY_PRESET=hidden )

# 3. Configure + build gfxr-sqlite.
cmake -S . -B out/build -DCMAKE_BUILD_TYPE=Release
cmake --build out/build --config Release --parallel
```

To reuse an existing gfxreconstruct checkout (instead of the nested submodule), pass `-DGFXR_SQLITE_GFXR_PATH=/path/to/gfxreconstruct` to the cmake configure step and skip step 1+2.

## Running the CLI

```bash
gfxr-sqlite path/to/capture.gfxr
# produces path/to/capture.gfxr.sqlite3

gfxr-sqlite -o my_capture.sqlite3 path/to/capture.gfxr
# writes to my_capture.sqlite3
```

The output `.sqlite3` file can be opened with any SQLite client. Schema documentation lives in the headers under [src/gfxr-db/includes/](src/gfxr-db/includes/).

## Example queries

The schema captures Vulkan API events under `apiEvents`, with each event's Vulkan function name resolved through the `functionNames` lookup table. Higher-level structure tables (`frames`, `queueSubmits`, `commandBufferRecordings`, `commandBufferCommands`, etc.) reference `apiEvents` by id. The patterns below illustrate the most common joins.

### List frames

```sql
SELECT
    id          AS frameId,
    beginApiEventId,
    endApiEventId
FROM frames
ORDER BY id;
```

### Queue submits in a given frame

`queueSubmits.apiEventId` points to the `vkQueueSubmit` (or `vkQueueSubmit2`) call itself; join `apiEvents` + `functionNames` to recover the function name.

```sql
SELECT
    qs.id           AS queueSubmitId,
    qs.frameId,
    qs.queueId,
    q.familyIndex   AS queueFamily,
    fn.name         AS submitFunction
FROM queueSubmits qs
JOIN queues        q  ON q.id  = qs.queueId
JOIN apiEvents     ae ON ae.id = qs.apiEventId
JOIN functionNames fn ON fn.id = ae.functionNameId
WHERE qs.frameId = 42
ORDER BY qs.id;
```

### Command buffer recordings submitted in a frame

A queue submit fans out through `queueSubmitBatches` → `queueSubmitBuffers` → `commandBufferRecordings`. Each recording belongs to one `commandBuffers` row (the long-lived handle).

```sql
SELECT
    qs.id           AS queueSubmitId,
    qsb.idx         AS batchIdx,
    qsbuf.idx       AS bufferIdx,
    cbr.id          AS recordingId,
    cb.id           AS commandBufferId,
    printf('0x%x', cb.handle) AS commandBufferHandle
FROM queueSubmits             qs
JOIN queueSubmitBatches       qsb   ON qsb.queueSubmitId         = qs.id
JOIN queueSubmitBuffers       qsbuf ON qsbuf.queueSubmitBatchId  = qsb.id
JOIN commandBufferRecordings  cbr   ON cbr.id                    = qsbuf.commandBufferRecordingId
JOIN commandBuffers           cb    ON cb.id                     = cbr.commandBufferId
WHERE qs.frameId = 42
ORDER BY qs.id, qsb.idx, qsbuf.idx;
```

### Recorded commands inside a command buffer (with resolved function names)

Every `vkCmd*` call inside a recording lives in `commandBufferCommands`, pointing at the underlying `apiEvents` row. Join through `functionNames` to get readable names. Commands are returned in API-event order (which matches recording order).

```sql
SELECT
    cbc.apiEventId,
    fn.name AS functionName
FROM commandBufferCommands cbc
JOIN apiEvents     ae ON ae.id = cbc.apiEventId
JOIN functionNames fn ON fn.id = ae.functionNameId
WHERE cbc.commandBufferRecordingId = 7
ORDER BY cbc.apiEventId;
```

### Frame → submits → recordings → commands, end-to-end

The full hierarchy in one query. Useful for sanity-checking the structure of a particular frame.

```sql
SELECT
    qs.frameId,
    qs.id         AS queueSubmitId,
    cbr.id        AS recordingId,
    cbc.apiEventId,
    fn.name       AS functionName
FROM queueSubmits             qs
JOIN queueSubmitBatches       qsb   ON qsb.queueSubmitId         = qs.id
JOIN queueSubmitBuffers       qsbuf ON qsbuf.queueSubmitBatchId  = qsb.id
JOIN commandBufferRecordings  cbr   ON cbr.id                    = qsbuf.commandBufferRecordingId
JOIN commandBufferCommands    cbc   ON cbc.commandBufferRecordingId = cbr.id
JOIN apiEvents                ae    ON ae.id = cbc.apiEventId
JOIN functionNames            fn    ON fn.id = ae.functionNameId
WHERE qs.frameId = 42
ORDER BY qs.id, cbr.id, cbc.apiEventId;
```

### Inspecting a single API event's arguments

`apiEventArguments` holds the argument list (one row per arg, with `idx` for order) for every recorded call.

```sql
SELECT idx, name, type, value
FROM apiEventArguments
WHERE apiEventId = 12345
ORDER BY idx;
```

## Integrating as a static library

`gfxr-sqlite`'s CMake supports being consumed via `add_subdirectory()`. The relevant cache variables:

| Variable                         | Default                                     | Purpose                                                                                       |
| -------------------------------- | ------------------------------------------- | --------------------------------------------------------------------------------------------- |
| `GFXR_SQLITE_GFXR_PATH`          | `<this-dir>/external/gfxreconstruct`        | Path to a gfxreconstruct source tree (root). Override to reuse a parent project's copy.       |
| `GFXR_SQLITE_BUILD_EXECUTABLE`   | `ON` standalone / `OFF` as subdirectory     | Build the `gfxr-sqlite` CLI executable.                                                       |
| `GFXR_SQLITE_BUILD_TEST`         | `ON` standalone / `OFF` as subdirectory     | Build the `gfxr-sqlite-test` test executable.                                                     |

### Example: parent CMake project

```cmake
# In your parent CMakeLists.txt, before add_subdirectory:
set(GFXR_SQLITE_GFXR_PATH "${CMAKE_SOURCE_DIR}/third_party/gfxreconstruct"
    CACHE PATH "Path to gfxreconstruct sources" FORCE)
set(GFXR_SQLITE_BUILD_EXECUTABLE OFF CACHE BOOL "" FORCE)
set(GFXR_SQLITE_BUILD_TEST OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/gfxr-sqlite)

add_library(my_consumer ...)
target_link_libraries(my_consumer PRIVATE gfxr-sqlite-library)
```

`gfxr-sqlite-library` exports its public include directories (the `gfxr-db/includes` headers, plus gfxreconstruct framework + Vulkan-Headers paths). Consumers get them automatically by linking.

### Public headers

The headers you'll typically include:

```cpp
#include "create_db_helper.h"   // gfxrSqlite::CreateDBHelper — drives the decode
#include "gfxr_db_manager.h"    // wraps an open SQLite connection
#include "memdb_ext.h"          // optional in-memory VFS extension
#include "sqlite3.h"            // embedded SQLite amalgamation
```

A minimal usage pattern (see [src/tools/gfxr_sqlite_main.cpp](src/tools/gfxr_sqlite_main.cpp) for a complete example):

```cpp
#include "create_db_helper.h"
#include "memdb_ext.h"
#include "sqlite3.h"

sqlite3MemdbExtInit();
auto errorHandler = [](const std::string& err) { std::cerr << err << '\n'; };
gfxrSqlite::CreateDBHelper helper{
    /*gfxrPath=*/"capture.gfxr",
    /*dbPath=*/"file:/memdb0?vfs=memdb_ext",
    /*logFilename=*/std::nullopt,
    /*enforceForeignKeys=*/false,
    errorHandler};
helper.createDatabase();
sqlite3* db = helper.getDB();
// ... query db ...
```

## Regenerating the Vulkan consumer code

A subset of the decoder is generated from gfxreconstruct's Vulkan registry. The generators live under [src/gfxr-db/internal/generated/](src/gfxr-db/internal/generated/). To regenerate (only needed after a Vulkan registry update or generator change):

```bash
python3 src/gfxr-db/internal/generated/generate_vulkan.py
# uses external/gfxreconstruct by default; override with --gfxr-dir <path>
```

## License

Apache-2.0. See individual source files for copyright headers.
