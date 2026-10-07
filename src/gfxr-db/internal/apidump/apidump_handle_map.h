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

#ifndef GFXRECON_DECODE_APIDUMP_HANDLE_MAP_H
#define GFXRECON_DECODE_APIDUMP_HANDLE_MAP_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "format/format.h"
#include "format/platform_types.h"
#include "util/defines.h"

GFXRECON_BEGIN_NAMESPACE(gfxrecon)
GFXRECON_BEGIN_NAMESPACE(decode)

/** Maps the runtime handle addresses in an api dump onto gfxreconstruct handle ids.
 *
 * gfxreconstruct assigns every object a small monotonic id at capture time, and the whole sqlite
 * schema keys objects by that id. An api dump instead records whatever the driver returned, which
 * is a pointer for dispatchable handles and a driver-chosen 64 bit value otherwise. This class
 * stands in for the capture time wrapper table.
 *
 * Addresses get recycled: a driver will happily hand back an address that a destroyed object used
 * to occupy. Releasing on destroy is what keeps the recycled address from being folded into the
 * lifetime of the object that used to live there.
 *
 * The key includes the object type, not just the address. Non-dispatchable handles are only unique
 * per type on many drivers, and a single api dump can contain more than one VkInstance and VkDevice
 * (the sample capture has two of each), so addresses are not globally unique.
 */
class ApiDumpHandleMap
{
  public:
    /** An id as it was minted, paired with the raw address that produced it. */
    struct AddressRecord
    {
        format::HandleId id;
        uint64_t         address;
    };

    /** Returns the id for an address, allocating one if this is the first sighting.
     *
     * Allocating on demand matters for objects created before the dump window opened, and for the
     * handles that arrive from a getter rather than a create, such as vkGetDeviceQueue queues and
     * vkGetSwapchainImagesKHR images. Repeated getter calls return the same address and so resolve
     * to the same id, which is what gfxreconstruct does too.
     */
    format::HandleId Get(VkObjectType type, uint64_t address);

    /** Returns a freshly allocated id, discarding any previous binding for this address.
     *
     * Used for the output handle of a create or allocate, so that an address reused after a destroy
     * starts a new object rather than resurrecting the old one.
     */
    format::HandleId Create(VkObjectType type, uint64_t address);

    /** Drops the binding for a destroyed or freed handle. */
    void Release(VkObjectType type, uint64_t address);

    /** Number of ids handed out so far. */
    uint64_t AllocatedCount() const { return next_id_ - 1; }

    /** How many addresses were resolved without ever having been created.
     *
     * A non-zero count is expected for a trimmed capture, where the dump starts after some objects
     * already exist, but a surprising count is a hint that a create is being missed.
     */
    uint64_t LazilyAllocatedCount() const { return lazily_allocated_; }

    /** Every id ever minted, in minting order, paired with the address that produced it.
     *
     * Recorded independently of `ids_`, which drops an entry on Release(): a destroyed object's row
     * still exists in the sqlite database (with its destroyApiEventId set), so its address must stay
     * recoverable even after the handle that produced it has been released.
     */
    const std::vector<AddressRecord>& MintedIds() const { return minted_; }

  private:
    struct Key
    {
        int64_t  type;
        uint64_t address;

        bool operator==(const Key& other) const { return (type == other.type) && (address == other.address); }
    };

    struct KeyHash
    {
        size_t operator()(const Key& key) const
        {
            // Addresses are allocator output, so their low bits carry most of the entropy; mixing
            // in the type keeps the two handle spaces from colliding systematically.
            const uint64_t mixed = key.address ^ (static_cast<uint64_t>(key.type) * 0x9e3779b97f4a7c15ull);
            return static_cast<size_t>(mixed ^ (mixed >> 32));
        }
    };

    std::unordered_map<Key, format::HandleId, KeyHash> ids_;
    format::HandleId                                   next_id_{ 1 };
    uint64_t                                           lazily_allocated_{ 0 };
    std::vector<AddressRecord>                         minted_;
};

GFXRECON_END_NAMESPACE(decode)
GFXRECON_END_NAMESPACE(gfxrecon)

#endif // GFXRECON_DECODE_APIDUMP_HANDLE_MAP_H
