###############################################################################
# Copyright (c) 2018-2023 LunarG, Inc.
# Copyright (c) 2018-2023 Valve Corporation.
# Copyright (c) 2020-2023 Advanced Micro Devices, Inc.
# Copyright (c) 2023-2026 The Sokatoa Project Authors
# All rights reserved
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
###############################################################################
cmake_minimum_required(VERSION 3.15)

project(gfxr-sqlite LANGUAGES C CXX)

# Detect standalone build (top-level) vs. consumed via add_subdirectory().
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(GFXR_SQLITE_IS_TOP_LEVEL ON)
else ()
    set(GFXR_SQLITE_IS_TOP_LEVEL OFF)
endif ()

# Path to gfxreconstruct. Standalone builds default to the nested submodule;
# consumers (e.g. Sokatoa's gfxr-consumer) override this before add_subdirectory().
set(GFXR_SQLITE_GFXR_PATH "${CMAKE_CURRENT_LIST_DIR}/external/gfxreconstruct"
    CACHE PATH "Path to the gfxreconstruct sources used by gfxr-sqlite")

option(GFXR_SQLITE_BUILD_EXECUTABLE "Build the standalone gfxr-sqlite CLI executable" ${GFXR_SQLITE_IS_TOP_LEVEL})
option(GFXR_SQLITE_BUILD_TEST "Build the gfxr-sqlite-test native test executable" ${GFXR_SQLITE_IS_TOP_LEVEL})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN "YES")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GFXR_PATH "${GFXR_SQLITE_GFXR_PATH}")
list(APPEND CMAKE_MODULE_PATH "${GFXR_PATH}/cmake")

set(GFXR_DB_SRC_PATH "${CMAKE_CURRENT_LIST_DIR}/src/gfxr-db")
set(GFXR_TOOLS_SRC_PATH "${CMAKE_CURRENT_LIST_DIR}/src/tools")

# -----------------------------------------------------------------------------
# gfxr-sqlite-library: the core static library that decodes .gfxr -> SQLite.
# -----------------------------------------------------------------------------
add_library(gfxr-sqlite-library STATIC "")

# Enabling PIC as consumers may place the static library into a shared library
# (e.g. Sokatoa's gfxr-consumer NAPI addon).
set_property(TARGET gfxr-sqlite-library PROPERTY POSITION_INDEPENDENT_CODE ON)

target_compile_features(gfxr-sqlite-library PUBLIC cxx_std_20)

if (MSVC)
    set_property(TARGET gfxr-sqlite-library PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<IF:$<CONFIG:DEBUG>,Debug,>DLL")

    set(PRECOMPILED_ARCH "64")
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(PRECOMPILED_ARCH "32")
    endif ()

    list(APPEND CMAKE_PREFIX_PATH
        "${GFXR_PATH}/external/precompiled/win${PRECOMPILED_ARCH}")

    target_compile_options(gfxr-sqlite-library PUBLIC /W4 /wd4100 /wd4127 /wd4505)
    target_compile_definitions(gfxr-sqlite-library PUBLIC _CRT_SECURE_NO_WARNINGS)
else ()
    target_compile_options(gfxr-sqlite-library PUBLIC -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wno-missing-field-initializers)
endif ()

if (APPLE)
    add_link_options(-Wl,-dead_strip -Wl,-dead_strip_dylibs)
    list(PREPEND CMAKE_PREFIX_PATH "${GFXR_PATH}/external/precompiled/macos")
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(gfxr-sqlite-library PUBLIC -Wno-gnu-zero-variadic-macro-arguments)
endif ()

target_compile_definitions(gfxr-sqlite-library PUBLIC SQLITE_USE_URI=1)
# Multi-threaded mode. A single connection must not be used concurrently.
target_compile_definitions(gfxr-sqlite-library PUBLIC SQLITE_THREADSAFE=2)

find_package(LZ4)
find_package(ZLIB)
find_package(ZSTD)

if (NOT TARGET windows_specific)
    add_library(windows_specific INTERFACE)
    target_compile_definitions(windows_specific INTERFACE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        VK_USE_PLATFORM_WIN32_KHR
        $<$<BOOL:${HEADLESS}>:VK_USE_PLATFORM_HEADLESS>)
endif ()

if (NOT TARGET linux_specific)
    add_library(linux_specific INTERFACE)
    target_compile_definitions(linux_specific INTERFACE _FILE_OFFSET_BITS=64 PAGE_GUARD_ENABLE_UCONTEXT_WRITE_DETECTION
        $<$<BOOL:${HEADLESS}>:VK_USE_PLATFORM_HEADLESS>)
endif ()

if (NOT TARGET platform_specific)
    add_library(platform_specific INTERFACE)
    target_link_libraries(platform_specific INTERFACE
        $<$<BOOL:${WIN32}>:windows_specific>
        $<$<NOT:$<BOOL:${WIN32}>>:linux_specific>)
endif ()

if (BUILD_WERROR)
    if (MSVC)
        target_compile_options(platform_specific INTERFACE /WX)
    else ()
        target_compile_options(platform_specific INTERFACE -Werror)
    endif ()
endif ()

if (MSVC)
    target_compile_options(platform_specific INTERFACE /MP)
endif ()

target_sources(gfxr-sqlite-library
    PRIVATE
        ${GFXR_DB_SRC_PATH}/internal/create_db_helper.cpp
        ${GFXR_DB_SRC_PATH}/internal/gfxr_db_manager.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/vulkan_sqlite_consumer_ext.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/vulkan_sqlite_consumer_tables.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/vulkan_sqlite_prepared_statements.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/vulkan_sqlite_consumer_base.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/vulkan_sqlite_consumer_base_tables.cpp
        ${GFXR_DB_SRC_PATH}/internal/decode/custom_vulkan_struct_to_sqlite.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_sqlite_consumer.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_struct_to_sqlite.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_enum_to_sqlite.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_process_features.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_enum_from_string.cpp
        ${GFXR_DB_SRC_PATH}/internal/apidump/apidump_json.cpp
        ${GFXR_DB_SRC_PATH}/internal/apidump/apidump_handle_map.cpp
        ${GFXR_DB_SRC_PATH}/internal/apidump/apidump_value_parse.cpp
        ${GFXR_DB_SRC_PATH}/internal/apidump/apidump_processor.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_apidump_dispatch.cpp
        ${GFXR_DB_SRC_PATH}/internal/apidump/custom_vulkan_struct_from_apidump.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_struct_from_apidump.cpp
        ${GFXR_DB_SRC_PATH}/internal/generated/generated_vulkan_pnext_from_apidump.cpp
        ${GFXR_DB_SRC_PATH}/internal/sqlite3_memdb_ext/memdb_ext.c
        ${GFXR_DB_SRC_PATH}/internal/sqlite3_memdb_ext/mem_redirect.cpp
        ${GFXR_DB_SRC_PATH}/sqlite3/sqlite3.c
        ${GFXR_PATH}/tools/platform_debug_helper.cpp
)

if (MSVC)
    # Force inclusion of "gfxrecon_disable_popup_result" variable in linking.
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        target_link_options(gfxr-sqlite-library PUBLIC "LINKER:/Include:_gfxrecon_disable_popup_result")
    else ()
        target_link_options(gfxr-sqlite-library PUBLIC "LINKER:/Include:gfxrecon_disable_popup_result")
    endif ()
endif ()

if (MSVC)
    set(BUILD_DIR "windows")
elseif (APPLE)
    set(BUILD_DIR "darwin")
else ()
    set(BUILD_DIR "linux")
endif ()

# GFXR uses dbuild for debug builds, build for release builds.
set(GFXR_PATH_BUILD "${GFXR_PATH}/$<IF:$<CONFIG:DEBUG>,dbuild,build>")

target_include_directories(gfxr-sqlite-library PUBLIC
    ${GFXR_PATH}
    ${GFXR_PATH_BUILD}/${BUILD_DIR}/x64/cmake_output
    ${GFXR_PATH}/tools
    ${GFXR_PATH}/framework
    ${GFXR_PATH}/external/Vulkan-Headers/include
    ${GFXR_PATH}/external/VulkanMemoryAllocator/include
    ${GFXR_DB_SRC_PATH}/includes
    ${GFXR_DB_SRC_PATH}/internal
    ${GFXR_DB_SRC_PATH}/sqlite3
    ${GFXR_DB_SRC_PATH}/internal/apidump
    ${GFXR_DB_SRC_PATH}/internal/generated
    ${GFXR_PATH}/external/nlohmann-json/include
)

if (APPLE)
    target_include_directories(gfxr-sqlite-library PUBLIC ${GFXR_PATH_BUILD}/${BUILD_DIR}/universal/cmake_output)
endif ()

target_compile_definitions(gfxr-sqlite-library PUBLIC VK_NO_PROTOTYPES VK_ENABLE_BETA_EXTENSIONS)
# Define PROJECT_VERSION_HEADER_FILE macro for gfxreconstruct version header
target_compile_definitions(gfxr-sqlite-library PRIVATE PROJECT_VERSION_HEADER_FILE="project_version_$<CONFIG>.h")

if (MSVC)
    set(GFXR_OUTPUT_SUBFOLDER "$<IF:$<CONFIG:DEBUG>,Debug,Release>")
else ()
    set(GFXR_OUTPUT_SUBFOLDER .)
endif ()

set(GFXR_BUILD_DIR ${GFXR_PATH_BUILD}/${BUILD_DIR})

target_link_directories(gfxr-sqlite-library PUBLIC
    ${GFXR_BUILD_DIR}/x64/cmake_output/framework/decode/${GFXR_OUTPUT_SUBFOLDER}
    ${GFXR_BUILD_DIR}/x64/cmake_output/framework/graphics/${GFXR_OUTPUT_SUBFOLDER}
    ${GFXR_BUILD_DIR}/x64/cmake_output/framework/format/${GFXR_OUTPUT_SUBFOLDER}
    ${GFXR_BUILD_DIR}/x64/cmake_output/framework/util/${GFXR_OUTPUT_SUBFOLDER}
    ${GFXR_BUILD_DIR}/x64/cmake_output/${GFXR_OUTPUT_SUBFOLDER})
if (APPLE)
    target_link_directories(gfxr-sqlite-library PUBLIC
        ${GFXR_BUILD_DIR}/universal/cmake_output/framework/decode/${GFXR_OUTPUT_SUBFOLDER}
        ${GFXR_BUILD_DIR}/universal/cmake_output/framework/graphics/${GFXR_OUTPUT_SUBFOLDER}
        ${GFXR_BUILD_DIR}/universal/cmake_output/framework/format/${GFXR_OUTPUT_SUBFOLDER}
        ${GFXR_BUILD_DIR}/universal/cmake_output/framework/util/${GFXR_OUTPUT_SUBFOLDER}
        ${GFXR_BUILD_DIR}/universal/cmake_output/${GFXR_OUTPUT_SUBFOLDER})
endif ()

target_link_libraries(gfxr-sqlite-library
    gfxrecon_graphics gfxrecon_decode gfxrecon_format gfxrecon_util project_version
    platform_specific
    $<$<BOOL:${WIN32}>:version.lib>
    LZ4::LZ4 ZLIB::ZLIB)
if (TARGET ZSTD::ZSTD)
    target_link_libraries(gfxr-sqlite-library ZSTD::ZSTD)
endif ()

# -----------------------------------------------------------------------------
# gfxr-sqlite: standalone CLI executable.
# -----------------------------------------------------------------------------
if (GFXR_SQLITE_BUILD_EXECUTABLE)
    add_executable(gfxr-sqlite ${GFXR_TOOLS_SRC_PATH}/gfxr_sqlite_main.cpp)
    if (MSVC)
        set_property(TARGET gfxr-sqlite PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<IF:$<CONFIG:DEBUG>,Debug,>DLL")
    endif ()
    target_link_libraries(gfxr-sqlite PRIVATE gfxr-sqlite-library)
endif ()

# -----------------------------------------------------------------------------
# gfxr-sqlite-test: native test executable for the library.
# -----------------------------------------------------------------------------
if (GFXR_SQLITE_BUILD_TEST)
    # Only register with ctest for a standalone build. When gfxr-sqlite is pulled in via
    # add_subdirectory from Sokatoa's gfxr-consumer, the parent owns test registration.
    if (GFXR_SQLITE_IS_TOP_LEVEL)
        enable_testing()
    endif ()

    add_executable(gfxr-sqlite-test
        ${GFXR_DB_SRC_PATH}/internal/native_gfxr_consumer_test.cpp
        ${GFXR_DB_SRC_PATH}/internal/executable_path.cpp)
    if (MSVC)
        set_property(TARGET gfxr-sqlite-test PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<IF:$<CONFIG:DEBUG>,Debug,>DLL")
    endif ()
    target_link_libraries(gfxr-sqlite-test PRIVATE gfxr-sqlite-library)

    # Tests for the api dump ingest path. Kept as separate executables because each one pins down a
    # different layer of it and they are useful to run in isolation while working on the generators.
    #
    # apidump-encoder-test is the odd one out: it is the only place allowed to include
    # encode/parameter_encoder.h, which it uses to assert ApiDumpEncoder produces byte identical
    # output. The library itself must never include that header, for the reasons on ApiDumpEncoder.
    foreach (apidump_test IN ITEMS convert encoder enum-lookup json state struct)
        string(REPLACE "-" "_" apidump_test_source ${apidump_test})
        # executable_path.cpp is not part of the library, and the tests that locate test-resources
        # need it; it is cheap enough to give to all of them rather than special casing.
        add_executable(apidump-${apidump_test}-test
            ${GFXR_DB_SRC_PATH}/internal/apidump/apidump_${apidump_test_source}_test.cpp
            ${GFXR_DB_SRC_PATH}/internal/executable_path.cpp)
        if (MSVC)
            set_property(TARGET apidump-${apidump_test}-test
                PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<IF:$<CONFIG:DEBUG>,Debug,>DLL")
        endif ()
        target_link_libraries(apidump-${apidump_test}-test PRIVATE gfxr-sqlite-library)
    endforeach ()

    # gfxrecon_encode is deliberately not a dependency of gfxr-sqlite-library, so its output
    # directory is not on the library's link path either. Only this test needs it.
    #
    # Both architecture directories are listed for the same reason the library lists both: gfxr
    # builds x64 everywhere except macOS, where it builds universal.
    target_link_directories(apidump-encoder-test PRIVATE
        ${GFXR_BUILD_DIR}/x64/cmake_output/framework/encode/${GFXR_OUTPUT_SUBFOLDER})
    if (APPLE)
        target_link_directories(apidump-encoder-test PRIVATE
            ${GFXR_BUILD_DIR}/universal/cmake_output/framework/encode/${GFXR_OUTPUT_SUBFOLDER})
    endif ()
    target_link_libraries(apidump-encoder-test PRIVATE gfxrecon_encode)

    add_test(NAME apidump-encoder COMMAND apidump-encoder-test)
    add_test(NAME apidump-enum-lookup COMMAND apidump-enum-lookup-test)
    add_test(NAME apidump-state COMMAND apidump-state-test)
    add_test(NAME apidump-struct COMMAND apidump-struct-test)

    # Both of these locate test-resources/test1.apidump by walking up from the executable, so they
    # need no arguments; apidump-json-test still accepts a path for pointing at a full capture.
    add_test(NAME apidump-json COMMAND apidump-json-test)
    add_test(NAME apidump-convert COMMAND apidump-convert-test)
endif ()
