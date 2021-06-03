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

void* operator new (std::size_t size)
{
    return std::malloc(size);
}

void* operator new (std::size_t size, const std::nothrow_t&) noexcept
{
    return std::malloc(size);
}

void* operator new[](std::size_t size)
{
    return std::malloc(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return std::malloc(size);
}

void operator delete(void* data) noexcept
{
    return std::free(data);
}

void operator delete(void* data, const std::nothrow_t&) noexcept
{
    return std::free(data);
}

void operator delete(void* data,std::size_t)
{
    return std::free(data);
}

void operator delete(void* data, std::size_t, const std::nothrow_t&) noexcept
{
    return std::free(data);
}

void operator delete[](void* data)
{
    return std::free(data);
}

void operator delete[](void* data, std::size_t)
{
    return std::free(data);
}

void operator delete[](void* data, const std::nothrow_t&) noexcept
{
    return std::free(data);
}
