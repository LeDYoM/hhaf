#include <memmanager/include/memmanager.hpp>
#include <cstdlib>
#include <new>

#ifdef _MSC_VER
#include <windows.h>
#include <crtdbg.h>

#ifndef NDEBUG
static int crtDebugMemAllocHook(int allocType,
                                void* userData,
                                size_t size,
                                int blockType,
                                long requestIndex,
                                const unsigned char* fileName,
                                int lineIndex)
{
    lineIndex;
    fileName;
    blockType;
    blockType;
    size;
    userData;
    allocType;

    if (requestIndex == 160)  // break;

        return true;

    return true;
}
#endif
#endif

void installMemManager()
{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetAllocHook(crtDebugMemAllocHook);
#endif
}

void finishMemManager()
{
#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
}

void* mmalloc(std::size_t size)
{
    return std::malloc(size);
}

void mfree(void* block)
{
    free(block);
}
