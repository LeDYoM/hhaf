#include "debug_system.hpp"
#include <memmanager/include/memory_view.hpp>

#include "system/get_system.hpp"
#include "time/time_system.hpp"
#include "static_build_data_display.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
DebugSystem::~DebugSystem()
{
    DisplayLog::debug(StaticTypeName, ": ", m_debug_variables.state());
}

void DebugSystem::logBuildStaticData()
{
    debug::logBuildStaticData();
}

void DebugSystem::onStartPreUpdate()
{
    m_debug_variables.startFrame(
        getSystem<TimeSystem>(systemAccessPtr()).nowFrame());
}

void DebugSystem::onFinishPostUpdate()
{}

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

debug::DebugVariables& DebugSystem::debugVariables()
{
    return m_debug_variables;
}

void DebugSystem::getVariable(debug::DebugVariableHandle& index,
                              char const* const name)
{
    m_debug_variables.getVariable(index, name);
}

bool DebugSystem::getVariableValue(debug::DebugVariableHandle& index,
                                   debug::DebugVariable& value)
{
    return m_debug_variables.getVariableValue(index, value);
}

void DebugSystem::incrementVariable(
    debug::DebugVariableHandle const index,
    debug::DebugVariable::value_type const increment)
{
    m_debug_variables.incrementVariable(index, increment);
}

void DebugSystem::setVariable(debug::DebugVariableHandle const index,
                              debug::DebugVariable::value_type const newValue)
{
    m_debug_variables.setVariable(index, newValue);
}

}  // namespace haf::sys
