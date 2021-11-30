#ifndef MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP
#define MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP

#include <cstddef>

namespace memm
{
void initMemoryStatistics();
void displayMemoryStatistics();
void destroyMemoryStatistics() noexcept;
struct MemoryStatistics
{
    std::size_t num_alloc_{0U};
    std::size_t num_dealloc_{0U};
    std::size_t bytes_alloc_{0U};
    std::size_t bytes_dealloc_{0U};
};

void resetMemoryStatisticsData(MemoryStatistics* const ms_data);

void pushMemoryStatisticsQueue();
void popMemoryStatisticsQueue();

MemoryStatistics* getHeadMemoryStatistics();
bool canAddNode();
void onAllocated(std::size_t size) noexcept;
void onDeallocate(std::size_t size) noexcept;
MemoryStatistics* getMemoryStatistics() noexcept;

}  // namespace memm

#endif
