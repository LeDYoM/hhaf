HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_TYPES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_TYPES_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::debug
{
using DebugVariableHandle = htps::s64;

}  // namespace haf::debug

#ifdef HAF_DEBUG_VARIABLES
#define HAF_DEBUG_VARIABLE_NAME(v_id) debug_variable_id##v_id
#define HAF_DECLARE_DEBUG_VARIABLE(v_id) \
    static haf::debug::DebugVariableHandle HAF_DEBUG_VARIABLE_NAME(v_id){-1};
#else
#define HAF_DECLARE_DEBUG_VARIABLE(v_id)
#endif

#endif
