module;

#include <cstddef>
#include <cstdint>

export module memmanager:memory_view;

import :statistics;

namespace memm
{
class MemoryView
{
public:
#pragma warning(push)
#pragma warning(disable : 4514)
    MemoryView() { pushMemoryStatisticsQueue(); }

    MemoryView(MemoryView const&) = delete;
    MemoryView& operator=(MemoryView const&) = delete;

    MemoryStatistics* getCurrentMemoryStatistics() const
    {
        return getHeadMemoryStatistics();
    }
    ~MemoryView() { popMemoryStatisticsQueue(); }
#pragma warning(pop)
};

}  // namespace memm
