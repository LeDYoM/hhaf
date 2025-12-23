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
std::uint_fast32_t current_index{0U};
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
    currentNode = &(memory_statistics[current_index]);
}

bool canAddNode() noexcept
{
    return current_index < kMemoryStatisticsMaxSize;
}

bool pushMemoryStatisticsQueue()
{
    if (canAddNode())
    {
        ++current_index;
        updateCurrentNode();
        resetMemoryStatisticsData(*currentNode);
        return true;
    }
    return false;
}

bool popMemoryStatisticsQueue()
{
    if (current_index > 0U)
    {
        currentNode[current_index - 1U] += currentNode[current_index];
        --current_index;
        updateCurrentNode();
        return true;
    }
    return false;
}

MemoryStatistics const* getDynamicEndMemoryStatistics() noexcept
{
    return std::next(currentNode);
}

MemoryStatistics const* getHeadMemoryStatistics() noexcept
{
    return currentNode;
}

MemoryStatistics* getMutableHeadMemoryStatistics() noexcept
{
    return currentNode;
}

MemoryStatistics getGlobalMemoryStatistics() noexcept
{
    MemoryStatistics* current_ms{std::begin(memory_statistics)};
    MemoryStatistics result{*current_ms++};
    MemoryStatistics const* ms_end{getDynamicEndMemoryStatistics()};

    while (current_ms != ms_end)
    {
        result += *current_ms++;
    }
    return result;
}

void onAllocated(std::size_t const size) noexcept
{
    auto* mstatistics{getMutableHeadMemoryStatistics()};

    mstatistics->num_alloc++;
    mstatistics->bytes_alloc += size;

}

void onDeallocate(std::size_t const size) noexcept
{
    auto* mstatistics{getMutableHeadMemoryStatistics()};

    if (currentNode != nullptr)
    {
        mstatistics->num_dealloc++;
        mstatistics->bytes_dealloc += size;
    }
}

}  // namespace memm
