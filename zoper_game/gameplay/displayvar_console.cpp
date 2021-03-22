#include "displayvar_console.hpp"
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include "../loaders/mainmenuresources.hpp"

#include <haf/scene/include/scene.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/resources/include/iresourceretriever.hpp>
#include <haf/resources/include/ittfont.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
DisplayVarConsole::DisplayVarConsole(
    htps::rptr<haf::scene::SceneNode> const parent,
    str name) :
    SceneNode{parent, std::move(name)}
{
}

void DisplayVarConsole::init()
{
    auto a = createSceneNode<SceneNodeText>("scnText");
    a->prop<Font>().set(systemInterface<res::IResourceRetriever>()
                .getTTFont(MainMenuResources::MenuFontId)
                ->font(72));

    a->prop<Text>().set("abc");
}

DisplayVarConsole::~DisplayVarConsole() = default;

}  // namespace zoper
