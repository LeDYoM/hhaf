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
    a->prop<Text>().set("AYi2_+q");
    a->prop<TextColor>().set(colors::Red);
    a->setLeftTopPositionScale({0.5F, 0.1F});
    a->setBaseSizeFromText('A', 10U);
//    a->prop<Position>().set({-0.250F, -0.25F});
//    a->prop<Scale>().set({0.5F, 0.5F});
}

void Console::setText(str const& text)
{
    (void)(text);
}

}  // namespace zoper
