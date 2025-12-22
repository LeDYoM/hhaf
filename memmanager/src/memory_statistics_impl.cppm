module;

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <iterator>

module memmanager:statistics_impl;

import :statistics_class;
import :constants;

namespace memm
{
MemoryStatistics memory_statistics[kMemoryStatisticsMaxSize];
std::uint_fast32_t current{0U};
MemoryStatistics* currentNode{memory_statistics};

void resetMemoryStatisticsData(MemoryStatistics& ms_data)
{
    ms_data = MemoryStatistics{};
}

void initMemoryStatistics()
{
    std::ranges::for_each(memory_statistics, resetMemoryStatisticsData);
}

void destroyMemoryStatistics() noexcept
{}

void updateCurrentNode()
{
    currentNode = &(memory_statistics[current]);
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

MemoryStatistics const* getHeadMemoryStatistics() noexcept
{
    return currentNode;
}

MemoryStatistics getGlobalMemoryStatistics() noexcept
{
    MemoryStatistics* current_ms{std::begin(memory_statistics)};
    MemoryStatistics result{*current_ms};

    while (current_ms != getHeadMemoryStatistics())
    {
        result += *(current_ms++);
    }
    return result;
}

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
