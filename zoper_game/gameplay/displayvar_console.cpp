#include "displayvar_console.hpp"
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include "../loaders/mainmenuresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/ittfont.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
DisplayVarConsole::DisplayVarConsole(
    htps::rptr<haf::scene::SceneNode> const parent,
    str name) :
    Console{parent, std::move(name)}
{}

}  // namespace zoper
