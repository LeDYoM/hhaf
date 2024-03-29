#include <memmanager/include/memmanager.hpp>
#include "memory_statistics.hpp"

#include <cstdlib>
#include <new>

#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#pragma warning( push )
#pragma warning( disable : 5039 )

#include <windows.h>
#include <crtdbg.h>
#pragma warning( pop )

#ifndef NDEBUG
static int crtDebugMemAllocHook(int allocType,
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
    (void)(size);
    (void)(userData);
    (void)(allocType);

    if (requestIndex == 73838)  // break;

        return true;

    return true;
}
#endif  // NDEBUG
#endif  // _MSC_VER

void installMemManager()
{
#ifdef _MSC_VER
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetAllocHook(crtDebugMemAllocHook);
#endif
    memm::initMemoryStatistics();
}

void finishMemManager()
{
    memm::destroyMemoryStatistics();

#ifdef _MSC_VER
    _CrtDumpMemoryLeaks();
#endif
}

void* mmalloc(std::size_t size)
{
    memm::onAllocated(size);
    return std::malloc(size);
}

void mfree(void* block)
{
    memm::onDeallocate(0U);
    std::free(block);
}

void mfree_with_size(void* block, std::size_t const size)
{
    memm::onDeallocate(size);
    std::free(block);
}

void* operator new(std::size_t size)
{
    return mmalloc(size);
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return mmalloc(size);
}

void* operator new[](std::size_t size)
{
    return mmalloc(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return mmalloc(size);
}

void operator delete(void* data) noexcept
{
    return mfree(data);
}

void operator delete(void* data, const std::nothrow_t&) noexcept
{
    return mfree(data);
}

void operator delete(void* data, std::size_t size)
{
    return mfree_with_size(data, size);
}

void operator delete(void* data,
                     std::size_t size,
                     const std::nothrow_t&) noexcept
{
    return mfree_with_size(data, size);
}

void operator delete[](void* data)
{
    return mfree(data);
}

void operator delete[](void* data, std::size_t size)
{
    return mfree_with_size(data, size);
}

void operator delete[](void* data, const std::nothrow_t&) noexcept
{
    return mfree(data);
}

void operator delete[](void* data,
                       std::size_t size,
                       const std::nothrow_t&) noexcept
{
    return mfree_with_size(data, size);
}
