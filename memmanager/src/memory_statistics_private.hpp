#ifndef MEMMANAGER_MEMORY_STATISTICS_PRIVATE_INCLUDE_HPP
#define MEMMANAGER_MEMORY_STATISTICS_PRIVATE_INCLUDE_HPP

#include <cstddef>
#include <memmanager/include/memory_view.hpp>

namespace memm
{
void initMemoryStatistics();
void destroyMemoryStatistics() noexcept;
void onAllocated(std::size_t const size) noexcept;
void onDeallocate(std::size_t const size) noexcept;

}  // namespace memm

#endif
