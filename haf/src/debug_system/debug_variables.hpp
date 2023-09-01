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

    void setVariableValue(DebugVariableHandle const& index,
                          core::str&& value) noexcept;
    void setVariableValue(DebugVariableHandle const& index,
                          core::str const& value);
    void setVariableValue(DebugVariableHandle const& index,
                          char const* const value);

    template <typename T>
    void setVariableValue(DebugVariableHandle const& index, T&& value)
    {
        setVariableValue(index, core::str::to_str(core::move(value)));
    }

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
