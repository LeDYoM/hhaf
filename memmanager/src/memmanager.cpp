#include <memmanager/include/memmanager.hpp>
#include <memmanager/include/memory_view.hpp>
#include "memory_statistics.hpp"

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

    if (requestIndex == 7755)  // break;

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

struct Bytes
{
    uint64_t bytes;

    uint64_t KBytes() const noexcept { return bytes / 1024U; }
    uint64_t MBytes() const noexcept { return bytes / (1024U * 1024U); }
};

void finishMemManager(bool const display_log)
{
    if (display_log)
    {
        memm::MemoryStatistics const* mem_statistics{
            memm::getMemoryStatistics()};
        std::cout << "[MemManager] Number of allocations: " << mem_statistics->num_alloc_
                  << "\n";
        std::cout << "[MemManager] Number of deallocations: " << mem_statistics->num_dealloc_
                  << "\n";
        Bytes allocated{mem_statistics->bytes_alloc_};
        std::cout << "[MemManager] Bytes allocated:\t" << allocated.bytes << "\t("
                  << allocated.KBytes() << "KB)\t(" << allocated.MBytes()
                  << "MB)"
                  << "\n";
        Bytes deallocated{mem_statistics->bytes_alloc_};
        std::cout << "[MemManager] Bytes deallocated:\t" << deallocated.bytes << "\t("
                  << deallocated.KBytes() << "KB)\t(" << deallocated.MBytes()
                  << "MB)";
        std::cout << std::endl;
    }

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
