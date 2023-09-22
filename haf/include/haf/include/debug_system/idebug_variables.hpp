HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_SYSTEM_IDEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_SYSTEM_IDEBUG_VARIABLES_INCLUDE_HPP

#include <haf/include/debug_system/debug_types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::debug
{
class IDebugVariables
{
public:
    virtual void getVariable(DebugVariableHandle& index,
                             char const* const name) = 0;

    virtual void setVariableValue(DebugVariableHandle const& index,
                                  core::str&& value) noexcept = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                                  core::str const& value)     = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                                  char const* const value)    = 0;

    template <typename T>
    void setVariableValue(DebugVariableHandle const& index, T&& value)
    {
        setVariableValue(index, core::str::to_str(core::move(value)));
    }

protected:
    ~IDebugVariables() = default;
};
}  // namespace haf::debug

#endif
