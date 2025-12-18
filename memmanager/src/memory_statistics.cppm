module;

#include <cstddef>
#include <cstdint>

export module memmanager:statistics;

import :statistics_class;

namespace memm
{
export void initMemoryStatistics();
export void destroyMemoryStatistics() noexcept;

bool pushMemoryStatisticsQueue();
bool popMemoryStatisticsQueue();

MemoryStatistics* getHeadMemoryStatistics() noexcept;
MemoryStatistics getGlobalMemoryStatistics() noexcept;
bool canAddNode() noexcept;

export void onAllocated(std::size_t const size) noexcept;
export void onDeallocate(std::size_t const size) noexcept;

}  // namespace memm
