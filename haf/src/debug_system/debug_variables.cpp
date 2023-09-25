#include "debug_variables.hpp"

using namespace haf::core;

namespace haf::debug
{
void DebugVariables::startFrame(time::TimePoint const& now,
                                core::u64 const frameNumber)
{
    m_frames = frameNumber;

    getVariable(m_frames_debug_var, "FrameNum");
    setVariableValue(m_frames_debug_var, m_frames);
    getVariable(m_frameTime, "FrameTime");
    setVariableValue(m_frameTime, now.microseconds());

    for (auto&& element : m_debug_variables)
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
    if (index < 0 ||
        index > static_cast<DebugVariableHandle>(m_debug_variables.size()))
    {
        if (auto const index_found{
                m_debug_variables.cfind_index(core::str{name})};
            index_found.first)
        {
            index = static_cast<DebugVariableHandle>(index_found.second);
        }
        else
        {
            m_debug_variables.add(core::str{name}, DebugVariable{});
            index =
                static_cast<DebugVariableHandle>(m_debug_variables.size() - 1U);
        }
    }
}

void DebugVariables::setVariableValue(DebugVariableHandle const& index,
                                      str&& value) noexcept
{
    m_debug_variables.index(static_cast<core::size_type>(index))
        .setValue(core::move(value));
}

void DebugVariables::setVariableValue(DebugVariableHandle const& index,
                                      str const& value)
{
    m_debug_variables.index(static_cast<core::size_type>(index))
        .setValue(value);
}

void DebugVariables::setVariableValue(DebugVariableHandle const& index,
                                      char const* const value)
{
    m_debug_variables.index(static_cast<core::size_type>(index))
        .setValue(value);
}

size_type DebugVariables::size() const noexcept
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
    /*
        for (auto const& element : m_debug_variables)
        {
            result += element.first;
            result += ":\t";
            result += element.second.value();
            result += "\t";
            result += element.second.value() / m_frames;
            result += "\n";
        }
        */
    return result;
}

Dictionary<DebugVariable> const& DebugVariables::debugVariables() const noexcept
{
    return m_debug_variables;
}

}  // namespace haf::debug
