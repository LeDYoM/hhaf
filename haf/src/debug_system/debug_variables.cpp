#include "debug_variables.hpp"

using namespace htps;
using DebugVariableHandle = haf::debug::DebugVariableHandle;
using DebugVariable_t     = haf::debug::DebugVariable;

namespace haf::debug
{
void DebugVariables::startFrame(time::TimePoint const& now)
{
    ++m_frames;
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
    if (index < 0 ||
        index > static_cast<DebugVariableHandle>(m_debug_variables.size()))
    {
        str str_name{name};
        if (auto const index_found{m_debug_variables.cfind_index(str_name)};
            index_found.first)
        {
            index = static_cast<s64>(index_found.second);
        }
        else
        {
            m_debug_variables.add(
                str_name,
                DebugVariable{static_cast<DebugVariable::value_type>(0)});
            index =
                static_cast<DebugVariableHandle>(m_debug_variables.size() - 1);
        }
    }
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

void DebugVariables::incrementVariable(
    DebugVariableHandle const index,
    DebugVariable::value_type const increment)
{
    auto const value{m_debug_variables.index(static_cast<size_type>(index))};
    m_debug_variables.index(static_cast<size_type>(index)) =
        (value + increment);
}

void DebugVariables::setVariable(DebugVariableHandle const index,
                                 DebugVariable::value_type const newValue)
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
