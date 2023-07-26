#include "debug_variables_str.hpp"
#include "debug_variables_general.hpp"

using namespace haf::core;
using DebugVariableHandle = haf::debug::DebugVariableHandle;

namespace haf::debug
{
void DebugVariablesStr::startFrame(time::TimePoint const& /*now*/)
{
}

void DebugVariablesStr::getVariable(DebugVariableHandle& index,
                                    char const* const name)
{
    detail::getVariable(m_debug_variables, index, name);
}

bool DebugVariablesStr::getVariableValue(DebugVariableHandle& index,
                                         str& value)
{
    if (index > -1)
    {
        value = m_debug_variables.index(static_cast<size_type>(index));
        return true;
    }
    return false;
}

void DebugVariablesStr::setVariable(DebugVariableHandle const index,
                                    str const& newValue)
{
    m_debug_variables.index(static_cast<size_type>(index)) = newValue;
}

htps::size_type DebugVariablesStr::size() const noexcept
{
    return m_debug_variables.size();
}

bool DebugVariablesStr::empty() const noexcept
{
    return m_debug_variables.empty();
}

Dictionary<str> const& DebugVariablesStr::debugVariables() const noexcept
{
    return m_debug_variables;
}

}  // namespace haf::debug
