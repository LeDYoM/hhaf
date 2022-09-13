#ifndef MEMMANAGER_MEMORY_VIEW_INCLUDE_HPP
#define MEMMANAGER_MEMORY_VIEW_INCLUDE_HPP

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

class MemoryView
{
public:
#pragma warning( push )
#pragma warning( disable : 4514 )
    MemoryView() { pushMemoryStatisticsQueue(); }

    MemoryView(MemoryView const&) = delete;
    MemoryView& operator=(MemoryView const&) = delete;

    MemoryStatistics* getCurrentMemoryStatistics() const
    {
        return getHeadMemoryStatistics();
    }
    ~MemoryView() { popMemoryStatisticsQueue(); }
#pragma warning( pop )
};

}  // namespace memm

#endif
