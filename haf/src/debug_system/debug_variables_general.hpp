HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUG_VARIABLES_GENERAL_TEMPLATES_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_VARIABLES_GENERAL_TEMPLATES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/debug_system/debug_types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>

namespace haf::debug::detail
{
template <typename T>
void setVariableValue(auto& debug_variables,
                      DebugVariableHandle const& index,
                      T value,
                      DebugVariablesAction const action) noexcept
{
    using TypeToUse = std::remove_cvref_t<decltype(value)>;
    switch (action)
    {
        case DebugVariablesAction::Set:
        {
            debug_variables.index(static_cast<core::size_type>(index))
                .setValue(core::move(value));
        }
        break;
        case DebugVariablesAction::Add:
        {
            auto& debug_var{
                debug_variables.index(static_cast<core::size_type>(index))};
            setVariableValue(
                debug_variables, index,
                debug_var.value<TypeToUse>() + static_cast<TypeToUse>(value),
                DebugVariablesAction::Set);
        }
        break;
    }
}

}  // namespace haf::debug::detail

#endif
