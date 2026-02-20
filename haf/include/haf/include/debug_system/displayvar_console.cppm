module;

#include "system/get_system.hpp"

export module haf:debug_system:displayvar_console;

import :debug_system:console;
import :debug_system:debug_variable;
import :debug_system:debug_system;
import :components;
import :core;
import :resources;

namespace haf
{
class DisplayVarConsole : public component::Component
{
private:
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;

    void updateVar(core::str const& name, debug::DebugVariable const& variable)
    {
        (void)(m_variables_data.add(make_str(name, ":"),
                                    make_str(variable.value())));
    }

    void update() override
    {
        if (showDebugVariables())
        {
            for (auto&& debug_variable :
                 sys::getSystem<sys::DebugSystem>(attachedNode())
                     .debugVariables()
                     .debugVariables())
            {
                updateVar(debug_variable.first, debug_variable.second);
            }
        }

        {
            fast_u32 index{0U};
            for (auto const& variables : m_variables_data)
            {
                m_console->setText({0U, index}, variables.first);
                m_console->setText({1U, index}, variables.second);
                ++index;
            }
        }
        BaseClass::update();
    }

    void addRequirements(component::ComponentRequirements&)
    {
        c_req.component(m_console);
    }

    prop::PropertyState<bool> showDebugVariables{false};

private:
    core::PureDictionary m_variables_data;
    core::sptr<Console> m_console;
};
}  // namespace haf

#endif