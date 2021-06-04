#ifndef MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP
#define MEMMANAGER_MEMORY_STATISTICS_INCLUDE_HPP

#include <cstdint>

namespace memm
{
void initMemoryStatistics();
void displayMemoryStatistics();
void destroyMemoryStatistics() noexcept;

class MemoryStatistics
{
public:
    std::size_t m_numAlloc{0U};
    std::size_t m_numDealloc{0U};
    std::size_t m_BytesAlloc{0U};
    std::size_t m_BytesDealloc{0U};
};

void onAllocated(std::size_t size) noexcept;
void onDeallocate(std::size_t size) noexcept;
MemoryStatistics* getMemoryStatistics() noexcept;

}  // namespace memm

#endif
