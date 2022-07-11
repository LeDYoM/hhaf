HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/dictionary.hpp>
#include <htypes/include/function.hpp>

#include "debug_variable.hpp"

#include <haf/include/time/time_point.hpp>

namespace haf::debug
{
class DebugVariables final
{
public:
    enum class DebugVariablesScope : htps::u8
    {
        Free  = 0U,
        Frame = 1U
    };

    using DebugVariable_t     = htps::f64;
    using DebugVariableHandle = htps::s64;
    using VariablesGroup      = htps::Dictionary<DebugVariable>;

    void getVariable(DebugVariablesScope const scope,
                     DebugVariableHandle& index,
                     char const* const name);
    void updateVariable(DebugVariablesScope const scope,
                        DebugVariableHandle const index,
                        DebugVariable_t const value);
    void updateVariable(
        DebugVariablesScope const scope,
        DebugVariableHandle const index,
        htps::function<DebugVariable_t(DebugVariable_t const)> updater);

    void incrementVariable(
        DebugVariablesScope const scope,
        DebugVariableHandle const index,
        DebugVariable_t const increment = static_cast<DebugVariable_t>(1));

    htps::str state() const;
    void startFrame(time::TimePoint const& now);
    void endFrame();

private:
    VariablesGroup& variablesGroup(DebugVariablesScope const scope) noexcept;
    VariablesGroup m_free_variables;
    VariablesGroup m_frame_variables;
    VariablesGroup m_frame_medium_variable;
    time::TimePoint m_last_time_update{0U};
    htps::u64 m_frames{0U};
};

}  // namespace haf::debug

#endif
