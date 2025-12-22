module;

#include <cstddef>

export module memmanager:statistics;

import :statistics_class;
import :statistics_impl;

namespace memm
{
void initMemoryStatistics();
export void destroyMemoryStatistics() noexcept;

export bool canAddNode() noexcept;

export bool pushMemoryStatisticsQueue();
export bool popMemoryStatisticsQueue();

export MemoryStatistics const* getHeadMemoryStatistics() noexcept;
export MemoryStatistics getGlobalMemoryStatistics() noexcept;

void onAllocated(std::size_t const size) noexcept;
void onDeallocate(std::size_t const size) noexcept;

}  // namespace memm
