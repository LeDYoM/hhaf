#include <memmanager/include/memmanager.hpp>
#include <memmanager/include/memory_view.hpp>
#include "memory_statistics_private.hpp"
#include "memmanager_msc.hpp"

#include <cstdlib>
#include <new>
#include <iostream>

void installMemManager(int argc, char* argv[])
{
    initPlatformMemManager();

    for (int i = 1; i < argc; ++i)
    {
        (void)(argv);
    }

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
        std::cout << "[MemManager] Number of allocations: "
                  << mem_statistics->num_alloc_ << "\n";
        std::cout << "[MemManager] Number of deallocations: "
                  << mem_statistics->num_dealloc_ << "\n";
        Bytes allocated{mem_statistics->bytes_alloc_};
        std::cout << "[MemManager] Bytes allocated:\t" << allocated.bytes
                  << "\t(" << allocated.KBytes() << "KB)\t("
                  << allocated.MBytes() << "MB)"
                  << "\n";
        Bytes deallocated{mem_statistics->bytes_alloc_};
        std::cout << "[MemManager] Bytes deallocated:\t" << deallocated.bytes
                  << "\t(" << deallocated.KBytes() << "KB)\t("
                  << deallocated.MBytes() << "MB)";
        std::cout << std::endl;
    }

    memm::destroyMemoryStatistics();
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
