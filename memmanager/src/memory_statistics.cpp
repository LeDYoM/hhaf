#include "memory_statistics.hpp"
#include <cstdint>

namespace memm
{
namespace
{
MemoryStatistics* memory_statistics{nullptr};
constexpr std::uint_fast32_t kMaxMemoryStatisticsSubBuffer{3U};
MemoryStatistics* memory_statics_subbuffer{nullptr};
std::uint_fast32_t current{0U};
MemoryStatistics* currentNode{nullptr};

void updateCurrentNode()
{
    currentNode = (memory_statics_subbuffer + current);
}

void resetMemoryStatisticsData(MemoryStatistics* const ms_data)
{
    (*ms_data).bytes_alloc_   = 0U;
    (*ms_data).bytes_dealloc_ = 0U;
    (*ms_data).num_alloc_     = 0U;
    (*ms_data).num_dealloc_   = 0U;
}

}  // namespace

void initMemoryStatistics()
{
    memory_statistics = new MemoryStatistics();
    memory_statics_subbuffer =
        new MemoryStatistics[kMaxMemoryStatisticsSubBuffer];
}

bool canAddNode() noexcept
{
    return current < kMaxMemoryStatisticsSubBuffer;
}

bool pushMemoryStatisticsQueue()
{
    if (current < kMaxMemoryStatisticsSubBuffer)
    {
        updateCurrentNode();
        ++current;
        resetMemoryStatisticsData(currentNode);
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

MemoryStatistics* getHeadMemoryStatistics()
{
    return currentNode;
}

void destroyMemoryStatistics() noexcept
{
    if (memory_statics_subbuffer != nullptr)
    {
        delete[] memory_statics_subbuffer;
    }

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
