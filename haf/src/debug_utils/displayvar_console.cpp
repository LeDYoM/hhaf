#include <haf/include/debug_utils/displayvar_console.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>

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
    Console{parent, std::move(name)}
{}

}  // namespace zoper
