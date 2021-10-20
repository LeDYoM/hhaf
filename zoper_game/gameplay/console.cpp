#include "console.hpp"
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include "../loaders/mainmenuresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace haf
{

void Console::onCreated()
{
    BaseClass::onCreated();

    auto a = createSceneNode<SceneNodeText>("scnText");
    a->prop<Font>().set(
        dataWrapper<res::ResourceRetriever>()->getBMPFont(
            "console_font"));

    prop<Position>().set(vector2df{100.0F, 0.0F});
    a->prop<Text>().set("1234 ABC abc");
    a->prop<TextColor>().set(colors::Red);
    //    a->prop<Scale>().set({1, 1});
}

void Console::setText(str const& text)
{
    (void)(text);
}

}  // namespace zoper
