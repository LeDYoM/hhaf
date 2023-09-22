HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_TYPES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_TYPES_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::debug
{
using DebugVariableHandle = core::s64;

}  // namespace haf::debug

#ifdef HAF_DEBUG_VARIABLES
#define HAF_DEBUG_VARIABLE_NAME(v_id) debug_variable_id##v_id
#define HAF_DECLARE_DEBUG_VARIABLE(v_id) \
    haf::debug::DebugVariableHandle HAF_DEBUG_VARIABLE_NAME(v_id){-1};
#define FROM_COMPONENT_GET_DEBUG_VARIABLE(v_id) \
    attachedNode()->subSystem<debug::IDebugVariables>()->getVariable( \
        HAF_DEBUG_VARIABLE_NAME(v_id), #v_id);

#define FROM_COMPONENT_SET_DEBUG_VARIABLE_VALUE(v_id, value) \
    FROM_COMPONENT_GET_DEBUG_VARIABLE(v_id) \
    attachedNode()->subSystem<debug::IDebugVariables>()->setVariableValue( \
        HAF_DEBUG_VARIABLE_NAME(v_id), value);
#else
#define HAF_DECLARE_DEBUG_VARIABLE(v_id)
#define FROM_COMPONENT_GET_DEBUG_VARIABLE(v_id, value) \
#define FROM_COMPONENT_SET_DEBUG_VARIABLE_VALUE(v_id, value)
#endif

#endif
