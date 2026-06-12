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

#include "mem_redirect.h"

#ifdef WIN32

/* On Windows, electron does not limit runtime's malloc helpers. */

template <typename FunctionType>
static FunctionType lookupNextFunction(const char* functionName, FunctionType baseImpl)
{
    (void)functionName;
    return baseImpl;
}
#else
#include <dlfcn.h>

#include <cstring>
#include <cstdio>

#define DEBUG_OUTPUT 0

static bool endsWith(const char* fullName, const char* partialName)
{
    std::size_t fullNameLen = std::strlen(fullName);
    std::size_t partialNameLen = std::strlen(partialName);
    if (fullNameLen < partialNameLen)
    {
        return false;
    }
    return std::strcmp(fullName + fullNameLen - partialNameLen, partialName) == 0;
}

/** To detect that this function is from electron's overload, we don't just want to skip every malloc overload,
 * hence we check for "electron" to be the binary name implementing the base implementation
 *
 * this is not a very robust check, any improvements/alternative are welcome.
 */
template <typename FunctionType>
static bool isElectronFunction(FunctionType baseImpl)
{
    Dl_info info{};
    int res = dladdr(reinterpret_cast<const void*>(baseImpl), &info);
#if DEBUG_OUTPUT
    std::fprintf(
        stderr,
        "info for function %s, info.dli_fname: %s\n",
        info.dli_sname ? info.dli_sname : "<na>",
        info.dli_fname ? info.dli_fname : "<na>"
    );
#endif
    if (res == 0 || info.dli_fname == nullptr)
    {
        // We did not find a definition of this symbol, unexpected
        return false;
    }
    else if (endsWith(info.dli_fname, "/electron"))
    {
        // Running in the debug environment, memory functions are defined in electron
        return true;
    }
    else if (endsWith(info.dli_fname, "/sokatoa"))
    {
        // Running in the packages environment, memory functions are defined in sokatoa
        return true;
    }

    // Anything else, for example when running in a node/test environment, dli_sname is
    // "/lib/x86_64-linux-gnu/libc.so.6"
    return false;
}

template <typename FunctionType>
static FunctionType lookupNextFunction(const char* functionName, FunctionType baseImpl)
{
    if (!isElectronFunction(baseImpl))
    {
        return baseImpl;
    }
    void* nextFunction = dlsym(RTLD_NEXT, functionName);
#if DEBUG_OUTPUT
    std::fprintf(stderr, "looking up next function %s, found %p\n", functionName, nextFunction);
#endif
    if (nextFunction != NULL)
    {
        return reinterpret_cast<FunctionType>(nextFunction);
    }
    return baseImpl;
}
#endif

void* redirectMalloc(size_t size) MEM_REDIRECT_NO_EXCEPT
{
    static auto mallocPtr = lookupNextFunction("malloc", &malloc);
    return mallocPtr(size);
}

void redirectFree(void* ptr) MEM_REDIRECT_NO_EXCEPT
{
    static auto freePtr = lookupNextFunction("free", &free);
    freePtr(ptr);
}

void* redirectRealloc(void* ptr, size_t size) MEM_REDIRECT_NO_EXCEPT
{
    static auto reallocPtr = lookupNextFunction("realloc", &realloc);
    return reallocPtr(ptr, size);
}

void* redirectCalloc(size_t num, size_t size) MEM_REDIRECT_NO_EXCEPT
{
    static auto callocPtr = lookupNextFunction("calloc", &calloc);
    return callocPtr(num, size);
}
