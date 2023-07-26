HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_STR_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_STR_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/debug_system/debug_types.hpp>

namespace haf::debug
{
class DebugVariablesStr final
{
public:
    void getVariable(DebugVariableHandle& index, char const* const name);

    bool getVariableValue(DebugVariableHandle& index, core::str& value);

    void setVariable(DebugVariableHandle const index,
                     core::str const& newValue = core::str{});

    void startFrame(time::TimePoint const& now);
    void endFrame();

    core::size_type size() const noexcept;
    bool empty() const noexcept;
    core::Dictionary<core::str> const& debugVariables() const noexcept;

private:
    core::Dictionary<core::str> m_debug_variables;
};

}  // namespace haf::debug

#endif
