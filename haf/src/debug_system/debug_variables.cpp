#include "debug_variables.hpp"

using namespace htps;
using DebugVariableHandle = haf::debug::DebugVariables::DebugVariableHandle;
using DebugVariable_t     = haf::debug::DebugVariable_t;

namespace haf::debug
{
void DebugVariables::startFrame(time::TimePoint const& now)
{
    ++m_frames;
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
                str_name, DebugVariable_t{static_cast<DebugVariable_t>(0)});
            index =
                static_cast<DebugVariableHandle>(m_debug_variables.size() - 1);
        }
    }
}

bool DebugVariables::getVariableValue(DebugVariableHandle& index,
                                      DebugVariable_t& value)
{
    if (index > -1)
    {
        value = m_debug_variables.index(static_cast<size_type>(index));
        return true;
    }
    return false;
}

void DebugVariables::incrementVariable(DebugVariableHandle const index,
                                       DebugVariable_t const increment)
{
    auto const value{m_debug_variables.index(static_cast<size_type>(index))};
    m_debug_variables.index(static_cast<size_type>(index)) =
        (value + increment);
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
        result += element.second;
        result += "\t";
        result += element.second / m_frames;
        result += "\n";
    }
    return result;
}

}  // namespace haf::debug
