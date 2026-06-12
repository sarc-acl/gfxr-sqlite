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

#ifndef VULKAN_SQLITE_CONSUMER_BASE_TABLES_H
#define VULKAN_SQLITE_CONSUMER_BASE_TABLES_H

#include "util/defines.h"
#include "sqlite3.h"
#include "vulkan_sqlite_consumer_context.h"
#include "vulkan_sqlite_prepared_statements.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

void CreateBaseTables(sqlite3* db);

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // VULKAN_SQLITE_CONSUMER_BASE_TABLES_H
