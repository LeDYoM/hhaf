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
                          DebugVariable::ValueTypeInteger value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          time::TimePoint value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          core::s32 value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          core::u32 value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeFloat value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeString&& value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          DebugVariable::ValueTypeString const& value) = 0;
    virtual void setVariableValue(DebugVariableHandle const& index,
                          char const* const value) = 0;

protected:
    ~IDebugVariables() = default;
};
}  // namespace haf::debug

#endif
