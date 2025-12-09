module;

#include <iostream>

module memmanager:funcs;

import :configuration;
import :statistics;
import :platform;
import :bytes;

namespace memm
{
void installMemManager(int const argc, char const* argv[])
{
    Configuration config{paramsToConfiguration(argc, argv)};
    initPlatformMemManager(config);

    for (int i = 1; i < argc; ++i)
    {
        (void)(argv);
    }

    memm::initMemoryStatistics();
}

void installMemManager(Configuration const& configuration)
{
    
}

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

}  // namespace memm
