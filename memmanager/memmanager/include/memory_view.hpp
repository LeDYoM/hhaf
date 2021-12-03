#ifndef MEMMANAGER_MEMORY_VIEW_INCLUDE_HPP
#define MEMMANAGER_MEMORY_VIEW_INCLUDE_HPP

#include <cstddef>

namespace memm
{
struct MemoryStatistics
{
    std::size_t num_alloc_{0U};
    std::size_t num_dealloc_{0U};
    std::size_t bytes_alloc_{0U};
    std::size_t bytes_dealloc_{0U};
};

bool pushMemoryStatisticsQueue();
bool popMemoryStatisticsQueue();

MemoryStatistics* getHeadMemoryStatistics();
bool canAddNode() noexcept;
MemoryStatistics* getMemoryStatistics() noexcept;

class MemoryView
{
public:
    MemoryView() { pushMemoryStatisticsQueue(); }

    MemoryView(MemoryView const&) = delete;
    MemoryView& operator=(MemoryView const&) = delete;

    MemoryStatistics* getCurrentMemoryStatistics() const
    {
        return getHeadMemoryStatistics();
    }
    ~MemoryView() { popMemoryStatisticsQueue(); }
};

}  // namespace memm

#endif
