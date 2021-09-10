#include "memory_statistics.hpp"

namespace memm
{
MemoryStatistics* memory_statistics{nullptr};

void initMemoryStatistics()
{
    memory_statistics = new MemoryStatistics();
}

void displayMemoryStatistics()
{}

void destroyMemoryStatistics() noexcept
{
    if (memory_statistics != nullptr)
    {
        delete memory_statistics;
        memory_statistics = nullptr;
    }
}

MemoryStatistics* getMemoryStatistics() noexcept
{
    return memory_statistics;
}

void onAllocated(std::size_t size) noexcept
{
    if (memory_statistics != nullptr)
    {
        memory_statistics->num_alloc_++;
        memory_statistics->bytes_alloc_ += size;
    }
}

void onDeallocate(std::size_t size) noexcept
{
    if (memory_statistics != nullptr)
    {
        memory_statistics->num_dealloc_++;
        memory_statistics->bytes_dealloc_ += size;
    }
}

}  // namespace memm
