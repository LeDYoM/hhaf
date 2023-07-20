HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
#include <haf/include/debug_system/debug_types.hpp>

namespace haf::debug
{
class DebugVariables final
{
public:
    void getVariable(DebugVariableHandle& index, char const* const name);

    bool getVariableValue(DebugVariableHandle& index, DebugVariable& value);

    void incrementVariable(DebugVariableHandle const index,
                           DebugVariable::value_type const increment =
                               static_cast<DebugVariable::value_type>(1));

    void setVariable(DebugVariableHandle const index,
                     DebugVariable::value_type const newValue =
                         static_cast<DebugVariable::value_type>(0));

    core::str state() const;

    void startFrame(time::TimePoint const& now);
    void endFrame();

    core::size_type size() const noexcept;
    bool empty() const noexcept;
    core::Dictionary<DebugVariable> const& debugVariables() const noexcept;

private:
    core::Dictionary<DebugVariable> m_debug_variables;
    time::TimePoint m_last_time_update{0U};
    core::u64 m_frames{0U};
};

}  // namespace haf::debug

#endif
