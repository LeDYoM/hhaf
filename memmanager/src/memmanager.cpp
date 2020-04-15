#include <memmanager/include/memmanager.hpp>

#include <new>

#ifdef _MSC_VER
#include <windows.h>
#include <crtdbg.h>

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

    if (requestIndex == 141160)  // break;

        return true;

    return true;
}

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

void*  mmalloc(unsigned long long size)
{
    return std::malloc(size);
}

void mfree(void* block)
{
    free(block);
}
