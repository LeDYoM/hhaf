#include <haf/include/debug_system/displayvar_console.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace haf
{
DisplayVarConsole::DisplayVarConsole(
    htps::rptr<haf::scene::SceneNode> const parent,
    str name) :
    Console{parent, htps::move(name)}
{}

void DisplayVarConsole::updateVar(str const& name, s64 const value)
{
    m_variables_data.add(name, make_str(name, ": ", value));
}

void DisplayVarConsole::update()
{
    {
        fast_u32 index{0U};
        for (auto const& variables : m_variables_data)
        {
            nodeAt(0U, index++)->Text = variables.second;
        }
    }
    BaseClass::update();
}

}  // namespace haf
