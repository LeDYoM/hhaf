#include "debug_variables.hpp"
#include "debug_variables_general.hpp"

using namespace haf::core;
using DebugVariableHandle = haf::debug::DebugVariableHandle;
using DebugVariable_t     = haf::debug::DebugVariable;

namespace haf::debug
{
void DebugVariables::startFrame(time::TimePoint const& now)
{
    ++m_frames;

    getVariable(m_frames_debug_var, "FrameNum");
    //incrementVariable(m_frames_debug_var);
    getVariable(m_frameTime, "FrameTime");
    setVariable(m_frameTime,DebugVariable(now.nanoseconds()));

    for (auto& element : m_debug_variables)
    {
        element.second.incrementFrame();
    }
    if (time::ellapsedUpdate(m_last_time_update, now,
                             time::TimePoint_as_seconds(1U)))
    {
    }
}

void DebugVariables::getVariable(DebugVariableHandle& index,
                                 char const* const name)
{
    detail::getVariable(m_debug_variables, index, name);
}

bool DebugVariables::getVariableValue(DebugVariableHandle& index,
                                      DebugVariable& value)
{
    if (index > -1)
    {
        value = m_debug_variables.index(static_cast<size_type>(index));
        return true;
    }
    return false;
}

void DebugVariables::setVariable(DebugVariableHandle const index,
                                 DebugVariable const& newValue)
{
    m_debug_variables.index(static_cast<size_type>(index)) = newValue;
}

htps::size_type DebugVariables::size() const noexcept
{
    return m_debug_variables.size();
}

bool DebugVariables::empty() const noexcept
{
    return m_debug_variables.empty();
}

str DebugVariables::state() const
{
    str result{"Frames: "};
    result += m_frames;
    result += "\n";

    for (auto const& element : m_debug_variables)
    {
        result += element.first;
        result += ":\t";
        result += element.second.value();
        result += "\t";
        result += element.second.value() / m_frames;
        result += "\n";
    }
    return result;
}

Dictionary<DebugVariable> const& DebugVariables::debugVariables() const noexcept
{
    return m_debug_variables;
}

}  // namespace haf::debug
