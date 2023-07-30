HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
#include <haf/include/debug_system/debug_types.hpp>

namespace haf::debug
{
enum class DebugVariablesAction : core::u32
{
    Set       = 0U,
    Add       = 1U,
    Substract = 2U
};

class DebugVariables final
{
public:
    void getVariable(DebugVariableHandle& index, char const* const name);

    void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeInteger value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          time::TimePoint value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          core::s32 value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          core::u32 value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeFloat value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeString&& value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeString const& value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          char const* const value) noexcept;

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
    DebugVariableHandle m_frames_debug_var;
    DebugVariableHandle m_frameTime;
};

}  // namespace haf::debug

#endif
