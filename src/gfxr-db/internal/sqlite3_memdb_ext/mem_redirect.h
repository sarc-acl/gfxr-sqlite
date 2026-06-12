/********************************************************************************
    Copyright 2025 The Sokatoa Project Authors

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

#ifndef MEM_REDIRECT_H
#define MEM_REDIRECT_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
// C memory functions don't throw
#define MEM_REDIRECT_NO_EXCEPT noexcept
#else
#define MEM_REDIRECT_NO_EXCEPT /* nothing in C */
#endif

    /** malloc replacement
     *
     * Helper function to allocate memory in an environment where the base malloc function is redirected,
     * e.g. when running inside of electron on Linux/Macos, where the electron malloc
     * only returns limited memory.
     *
     */
    extern void* redirectMalloc(size_t size) MEM_REDIRECT_NO_EXCEPT;
    /** free replacement */
    extern void redirectFree(void* ptr) MEM_REDIRECT_NO_EXCEPT;
    /** realloc replacement */
    extern void* redirectRealloc(void* ptr, size_t size) MEM_REDIRECT_NO_EXCEPT;
    /** calloc replacement */
    extern void* redirectCalloc(size_t num, size_t size) MEM_REDIRECT_NO_EXCEPT;

#ifdef __cplusplus
}
#endif

#endif // MEM_REDIRECT_H
