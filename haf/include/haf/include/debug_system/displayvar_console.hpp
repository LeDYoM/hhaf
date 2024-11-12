HTPS_PRAGMA_ONCE
#ifndef HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP
#define HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/dictionary.hpp>
#include <haf/include/debug_system/console.hpp>
#include <haf/include/debug_system/debug_variable.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

namespace haf
{
class DisplayVarConsole : public component::Component
{
private:
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;
    void updateVar(htps::str const& name, debug::DebugVariable const& variable);
    void update() override;
    void addRequirements(component::ComponentRequirements&);

    prop::PropertyState<bool> showDebugVariables{false};

private:
    htps::PureDictionary m_variables_data;
    htps::sptr<Console> m_console;
};
}  // namespace haf

#endif