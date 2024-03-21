#include "debug_system.hpp"
#include <memmanager/include/memory_view.hpp>

#include "system/get_system.hpp"
#include "time/time_system.hpp"
#include "static_build_data_display.hpp"
#include <hlog/include/hlog.hpp>

#include "haf_imgui.hpp"

using namespace haf::core;
using namespace haf::debug;
using namespace haf::time;

namespace haf::sys
{
DebugSystem::~DebugSystem()
{
    logger::DisplayLog::debug(StaticTypeName, ": ", m_debug_variables.state());
}

void DebugSystem::logBuildStaticData()
{
    debug::logBuildStaticData();
}

void DebugSystem::preUpdate()
{
    m_debug_variables.startFrame(
        getSystem<TimeSystem>(systemAccessPtr()).nowFrame(),
        getSystem<TimeSystem>(systemAccessPtr()).currentFrame());
}

void DebugSystem::postUpdate()
{}

MemoryDataInitializer DebugSystem::startMemoryCounter()
{
    return MemoryDataInitializer{this};
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

DebugVariables& DebugSystem::debugVariables()
{
    return m_debug_variables;
}

void DebugSystem::getVariable(DebugVariableHandle& index,
                              char const* const name)
{
    m_debug_variables.getVariable(index, name);
}

void DebugSystem::setVariableValue(DebugVariableHandle const& index,
                                   str&& value) noexcept
{
    m_debug_variables.setVariableValue(index, core::move(value));
}

void DebugSystem::setVariableValue(DebugVariableHandle const& index,
                                   str const& value)
{
    m_debug_variables.setVariableValue(index, value);
}

void DebugSystem::setVariableValue(DebugVariableHandle const& index,
                                   char const* const value)
{
    m_debug_variables.setVariableValue(index, value);
}

void DebugSystem::init()
{
    himgui::init();
}

void DebugSystem::update()
{
    himgui::initFrame();
    himgui::initWindow();
    himgui::addMessage("Test message");
    str temp;
    str temp_value;

    for (auto const& [name, value] : m_debug_variables.debugVariables())
    {
        temp = name + ":" + value.value();
        himgui::addMessage(temp.c_str());
    }

    himgui::finishWindow();
    himgui::finishFrame();
}

void DebugSystem::finish()
{
    himgui::shutdown();
}

}  // namespace haf::sys
