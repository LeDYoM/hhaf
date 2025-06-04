#include "memmanager_platform.hpp"
#include <memmanager/include/memmanager.hpp>
#include <memmanager/include/memory_view.hpp>
#include "memory_statistics_private.hpp"

#include <cstdlib>
#include <new>
#include <iostream>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#pragma warning(push)
#pragma warning(disable : 5039)

#include <windows.h>
#include <crtdbg.h>
#pragma warning(pop)

#ifndef NDEBUG
int crtDebugMemAllocHook(int allocType,
                         void* userData,
                         size_t size,
                         int blockType,
                         long requestIndex,
                         const unsigned char* fileName,
                         int lineIndex) noexcept
{
    (void)(lineIndex);
    (void)(fileName);
    (void)(blockType);
    (void)(blockType);
    (void)(requestIndex);
    (void)(size);
    (void)(userData);
    (void)(allocType);

    if (size == 104)  // break;

        return true;

    return true;
}
#endif  // NDEBUG

bool initPlatformMemManager(Configuration const&)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF |
                   _CRTDBG_CHECK_ALWAYS_DF);
    _CrtSetAllocHook(crtDebugMemAllocHook);
    return true;
}

#endif  // _MSC_VER
