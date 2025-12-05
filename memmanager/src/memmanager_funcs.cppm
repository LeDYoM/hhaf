module;

#include <cstddef>
#include <iostream>

export module memmanager:funcs;

import :memory_view;
import :configuration;
import :statistics;
import :platform;

namespace memm
{
export void installMemManager(int const argc, char const* argv[])
{
    Configuration config{paramsToConfiguration(argc, argv)};
    initPlatformMemManager(config);

    for (int i = 1; i < argc; ++i)
    {
        (void)(argv);
    }

    memm::initMemoryStatistics();
}

struct Bytes
{
    uint64_t bytes;

    constexpr uint64_t KBytes() const noexcept { return bytes / 1024U; }

    constexpr uint64_t MBytes() const noexcept
    {
        return bytes / (1024U * 1024U);
    }

    constexpr uint64_t GBytes() const noexcept
    {
        return bytes / (1024U * 1024U * 1024U);
    }
};

export void finishMemManager(bool const display_log)
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

export void* mmalloc(std::size_t size)
{
    memm::onAllocated(size);
    return std::malloc(size);
}

export void mfree(void* block)
{
    memm::onDeallocate(0U);
    std::free(block);
}

export void mfree_with_size(void* block, std::size_t const size)
{
    memm::onDeallocate(size);
    std::free(block);
}
}  // namespace memm

export void* operator new(std::size_t size)
{
    return memm::mmalloc(size);
}

export void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return memm::mmalloc(size);
}

export void* operator new[](std::size_t size)
{
    return memm::mmalloc(size);
}

export void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return memm::mmalloc(size);
}

export void operator delete(void* data) noexcept
{
    return memm::mfree(data);
}

export void operator delete(void* data, const std::nothrow_t&) noexcept
{
    return memm::mfree(data);
}

export void operator delete(void* data, std::size_t size)
{
    return memm::mfree_with_size(data, size);
}

export void operator delete(void* data,
                            std::size_t size,
                            const std::nothrow_t&) noexcept
{
    return memm::mfree_with_size(data, size);
}

export void operator delete[](void* data)
{
    return memm::mfree(data);
}

export void operator delete[](void* data, std::size_t size)
{
    return memm::mfree_with_size(data, size);
}

export void operator delete[](void* data, const std::nothrow_t&) noexcept
{
    return memm::mfree(data);
}

export void operator delete[](void* data,
                              std::size_t size,
                              const std::nothrow_t&) noexcept
{
    return memm::mfree_with_size(data, size);
}
