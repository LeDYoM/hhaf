#include "debug_system.hpp"
#include <memmanager/include/memory_view.hpp>

using namespace htps;

namespace haf::sys
{
DebugSystem::~DebugSystem() = default;

debug::MemoryDataInitializer DebugSystem::startMemoryCounter()
{
    return debug::MemoryDataInitializer{this};
}

bool DebugSystem::pushMemoryDataStatistics()
{
    return memm::pushMemoryStatisticsQueue();
}

bool DebugSystem::popMemoryDataStatistics()
{
    return memm::popMemoryStatisticsQueue();
}

bool DebugSystem::canAddNode() const noexcept
{
    return memm::canAddNode();
}

size_type DebugSystem::getHeadAllocations() const noexcept
{
    return static_cast<size_type>(memm::getHeadMemoryStatistics()->num_alloc_);
}

size_type DebugSystem::getHeadDeallocations() const noexcept
{
    return static_cast<size_type>(
        memm::getHeadMemoryStatistics()->num_dealloc_);
}

size_type DebugSystem::getHeadAllocatedByes() const noexcept
{
    return static_cast<size_type>(
        memm::getHeadMemoryStatistics()->bytes_alloc_);
}

size_type DebugSystem::getHeadDeallocatedByes() const noexcept
{
    return static_cast<size_type>(
        memm::getHeadMemoryStatistics()->bytes_dealloc_);
}

}  // namespace haf::sys
