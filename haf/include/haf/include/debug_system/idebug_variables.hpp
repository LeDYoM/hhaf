HTPS_PRAGMA_ONCE
#ifndef HAF_DEBUG_SYSTEM_IDEBUG_VARIABLES_INCLUDE_HPP
#define HAF_DEBUG_SYSTEM_IDEBUG_VARIABLES_INCLUDE_HPP

#include <haf/include/debug_system/debug_types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>

namespace haf::debug
{
class IDebugVariables
{
public:
    virtual void getVariable(DebugVariableHandle& index,
                             char const* const name) = 0;

    virtual bool getVariableValue(DebugVariableHandle& index,
                                  DebugVariable& value) = 0;

    virtual void incrementVariable(
        DebugVariableHandle const index,
        DebugVariable::value_type const increment =
            static_cast<DebugVariable::value_type>(1)) = 0;

    virtual void setVariable(
        DebugVariableHandle const index,
        DebugVariable::value_type const newValue =
            static_cast<DebugVariable::value_type>(0)) = 0;
protected:
    ~IDebugVariables() = default;
};
}  // namespace haf::debug

#endif
