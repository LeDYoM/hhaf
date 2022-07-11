#include "debug_variables.hpp"

using namespace htps;
using DebugVariableHandle = haf::debug::DebugVariables::DebugVariableHandle;
using DebugVariable_t     = haf::debug::DebugVariables::DebugVariable_t;
using VariablesGroup      = haf::debug::DebugVariables::VariablesGroup;
using DebugVariable       = haf::debug::DebugVariable;

void getVariableImp(DebugVariableHandle& index,
                    char const* const name,
                    VariablesGroup& variables)
{
    if (index < 0 || index > variables.size())
    {
        str str_name{name};
        if (auto const index_found{variables.cfind_index(str_name)};
            index_found.first)
        {
            index = static_cast<s64>(index_found.second);
        }
        else
        {
            variables.add(str_name,
                          DebugVariable{static_cast<DebugVariable_t>(0)});
            index = static_cast<s64>(variables.size() - 1);
        }
    }
}

void updateVariableImp(DebugVariableHandle const index,
                       function<DebugVariable_t(DebugVariable_t)> updater,
                       VariablesGroup& variables)
{
    DebugVariable value{variables.index(static_cast<size_type>(index))};
    value = updater(value.currentValue());
    variables.index(static_cast<size_type>(index)) = value;
}

namespace haf::debug
{
void DebugVariables::startFrame(time::TimePoint const& now)
{
    ++m_frames;
    if (time::ellapsedUpdate(m_last_time_update, now,
                             time::TimePoint_as_seconds(1U)))
    {
        for (auto& variable : m_frame_variables)
        {
            variable.second.updateReset(m_frames);
        }
        m_frames = 0U;
    }
}

void DebugVariables::getVariable(DebugVariablesScope const scope,
                                 DebugVariableHandle& index,
                                 char const* const name)
{
    getVariableImp(index, name, variablesGroup(scope));
}

void DebugVariables::updateVariable(DebugVariablesScope const scope,
                                    DebugVariableHandle const index,
                                    DebugVariable_t const value)
{
    updateVariableImp(
        index, [&value](auto const) { return value; }, variablesGroup(scope));
}

void DebugVariables::updateVariable(
    DebugVariablesScope const scope,
    DebugVariableHandle const index,
    function<DebugVariable_t(DebugVariable_t const)> updater)
{
    updateVariableImp(index, htps::move(updater), variablesGroup(scope));
}

void DebugVariables::incrementVariable(DebugVariablesScope const scope,
                                       DebugVariableHandle const index,
                                       DebugVariable_t const increment)
{
    updateVariable(scope, index,
                   [&increment](auto const v) { return v + increment; });
}

str DebugVariables::state() const
{
    str result{};

    for (auto const& element : m_frame_variables)
    {
        result += element.first;
        result += ":";
        result += str::to_str(element.second.accumulated());
    }
    return result;
}

DebugVariables::VariablesGroup& DebugVariables::variablesGroup(
    DebugVariablesScope const scope) noexcept
{
    switch (scope)
    {
        default:
        case DebugVariablesScope::Free:
            return m_free_variables;
            break;
        case DebugVariablesScope::Frame:
            return m_frame_variables;
            break;
    }
}

}  // namespace haf::debug
