#ifndef MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP
#define MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP

#include <cstddef>
#include <cstdint>

namespace memm
{
struct MemoryStatistics
{
    std::uint64_t num_alloc_{0U};
    std::uint64_t num_dealloc_{0U};
    std::uint64_t bytes_alloc_{0U};
    std::uint64_t bytes_dealloc_{0U};
};

bool pushMemoryStatisticsQueue();
bool popMemoryStatisticsQueue();

MemoryStatistics* getHeadMemoryStatistics();
bool canAddNode() noexcept;
MemoryStatistics* getMemoryStatistics() noexcept;

}  // namespace memm

#endif
