module;

#include <cstddef>
#include <cstdint>

export module memmanager:memoryview;

#include "memory_statistics.hpp"

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

#endif
