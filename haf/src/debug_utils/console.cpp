#include <haf/include/debug_utils/console.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
//#include "../loaders/mainmenuresources.hpp"

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

void Console::onCreated()
{
    BaseClass::onCreated();

    auto a = createSceneNode<SceneNodeText>("scnText");
    a->prop<Font>().set(
        subSystem<res::IResourceRetriever>()->getBMPFont(
            "console_font"));

//    prop<Position>().set(vector2df{100.0F, 0.0F});
//    prop<Scale>().set({1 / 2000.0F, 1 / 2000.0F});
//    a->prop<Text>().set("234 ABC abc");
    a->prop<Text>().set("i2");
    a->prop<TextColor>().set(colors::Red);
//    a->prop<Scale>().set({1, 1});
}

void Console::setText(str const& text)
{
    (void)(text);
}

}  // namespace zoper
