#include <haf/include/debug_system/displayvar_console.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

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
    m_variables_data.add(make_str(name, ":"), make_str(variable.value()));
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
            composedComponent()->setText({0U, index}, variables.first);
            composedComponent()->setText({1U, index}, variables.second);
            ++index;
        }
    }
    BaseClass::update();
}

}  // namespace haf
