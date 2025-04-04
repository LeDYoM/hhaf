#include <haf/include/debug_system/displayvar_console.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>

#include "system/get_system.hpp"
#include "debug_system/debug_system.hpp"

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace haf
{
void DisplayVarConsole::updateVar(str const& name,
                                  debug::DebugVariable const& variable)
{
    (void)(m_variables_data.add(make_str(name, ":"),
                                make_str(variable.value())));
}

void DisplayVarConsole::update()
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

void DisplayVarConsole::addRequirements(component::ComponentRequirements& c_req)
{
    c_req.component(m_console);
}

}  // namespace haf
