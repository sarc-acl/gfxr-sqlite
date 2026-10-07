/********************************************************************************
    Copyright 2026 The Sokatoa Project Authors

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

#include "apidump_handle_map.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

format::HandleId ApiDumpHandleMap::Get(VkObjectType type, uint64_t address)
{
    if (address == 0)
    {
        return format::kNullHandleId;
    }

    const Key  key{ static_cast<int64_t>(type), address };
    const auto found = ids_.find(key);

    if (found != ids_.end())
    {
        return found->second;
    }

    // First sighting without a create. Expected for a trimmed capture that begins after the object
    // already existed; giving it an id anyway keeps the reference resolvable instead of dropping it.
    ++lazily_allocated_;
    const format::HandleId id = next_id_++;
    ids_.emplace(key, id);
    minted_.push_back({ id, address });
    return id;
}

format::HandleId ApiDumpHandleMap::Create(VkObjectType type, uint64_t address)
{
    if (address == 0)
    {
        return format::kNullHandleId;
    }

    const Key key{ static_cast<int64_t>(type), address };

    // Overwrite rather than reuse: a create returning an address that is still mapped means the
    // driver recycled it, and the new object must not inherit the old object's id.
    const format::HandleId id = next_id_++;
    ids_[key]                 = id;
    minted_.push_back({ id, address });
    return id;
}

void ApiDumpHandleMap::Release(VkObjectType type, uint64_t address)
{
    if (address == 0)
    {
        return;
    }

    ids_.erase(Key{ static_cast<int64_t>(type), address });
}

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)
