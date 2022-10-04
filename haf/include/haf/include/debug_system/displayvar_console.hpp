HTPS_PRAGMA_ONCE
#ifndef HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP
#define HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/dictionary.hpp>
#include <haf/include/debug_system/console.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/component/composed_component.hpp>

namespace haf
{
class DisplayVarConsole : public component::ComposedComponent<Console>
{
private:
    using BaseClass = component::ComposedComponent<Console>;

public:
    using BaseClass::BaseClass;
    void updateVar(htps::str const& name, debug::DebugVariable const& variable);
    void update() override;

    htps::PropertyState<bool> showDebugVariables{false};

private:
    htps::PureDictionary m_variables_data;
};
}  // namespace haf

#endif