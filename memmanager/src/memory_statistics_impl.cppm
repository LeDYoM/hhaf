module;

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <iterator>

module memmanager:statistics;

import :statistics_class;
import :constants;

namespace memm
{
MemoryStatistics memory_statistics[kMemoryStatisticsMaxSize];
std::uint_fast32_t current{0U};
MemoryStatistics* currentNode{nullptr};

void updateCurrentNode()
{
    currentNode = &(memory_statistics[current]);
}

void resetMemoryStatisticsData(MemoryStatistics& ms_data)
{
    ms_data = MemoryStatistics{};
}

void initMemoryStatistics()
{
    std::ranges::for_each(memory_statistics, resetMemoryStatisticsData);
}

bool canAddNode() noexcept
{
    return current < kMemoryStatisticsMaxSize;
}

bool pushMemoryStatisticsQueue()
{
    if (current < kMemoryStatisticsMaxSize)
    {
        updateCurrentNode();
        ++current;
        resetMemoryStatisticsData(*currentNode);
        return true;
    }
    return false;
}

bool popMemoryStatisticsQueue()
{
    if (current > 0U)
    {
        --current;
        updateCurrentNode();
        return true;
    }
    return false;
}

MemoryStatistics* getHeadMemoryStatistics() noexcept
{
    return currentNode;
}

MemoryStatistics getGlobalMemoryStatistics() noexcept
{
    MemoryStatistics* current_ms{std::begin(memory_statistics)};
    MemoryStatistics result{*current_ms};

    while (current_ms != getHeadMemoryStatistics())
    {

    }
    return result;
}

void destroyMemoryStatistics() noexcept
{}

void onAllocated(std::size_t const size) noexcept
{
    auto* mstatistics{getHeadMemoryStatistics()};

    mstatistics->num_alloc++;
    mstatistics->bytes_alloc += size;

}

void onDeallocate(std::size_t const size) noexcept
{
    auto* mstatistics{getHeadMemoryStatistics()};

    if (currentNode != nullptr)
    {
        mstatistics->num_dealloc++;
        mstatistics->bytes_dealloc += size;
    }
}

}  // namespace memm
