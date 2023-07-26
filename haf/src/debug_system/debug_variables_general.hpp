HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_GENERAL_TEMPLATES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_GENERAL_TEMPLATES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>

namespace haf::debug::detail
{
void getVariable(auto& debug_variables,
                 DebugVariableHandle& index,
                 char const* const name)
{
    if (index < 0 ||
        index > static_cast<DebugVariableHandle>(debug_variables.size()))
    {
        if (auto const index_found{
                debug_variables.cfind_index(core::str{name})};
            index_found.first)
        {
            index = static_cast<DebugVariableHandle>(index_found.second);
        }
        else
        {
            debug_variables.add(core::str{name}, DebugVariable{});
            index =
                static_cast<DebugVariableHandle>(debug_variables.size() - 1);
        }
    }
}

}  // namespace haf::debug::detail

#endif
