#include <haf/include/debug_system/console.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
//#include "../loaders/mainmenuresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace haf
{

void Console::onCreated()
{
    BaseClass::onCreated();
    TableSize = {2, 5};

//    auto a  = createSceneNode<SceneNodeText>("scnText");
//    a->Font = subSystem<res::IResourceRetriever>()->getBMPFont("console_font");

//    a->Text      = "AYi2_+q";
//    a->TextColor = colors::Red;
//    a->setLeftTopPositionScale({0.1F, 0.05F});
}

void Console::setText(str const& text)
{
    (void)(text);
}

void Console::onAllTableElementsCreated(htps::vector2dst const /*table_size*/)
{
    nodeAt(0, 0)->Text = "Hello2";
    nodeAt(0, 0)->TextColor = colors::Red;
    nodeAt(0, 0)->Font = subSystem<res::IResourceRetriever>()->getBMPFont("console_font");
    // Allow for 20U characters
    nodeAt(0, 0)->TextBaseSizeProperty = TextBaseSize{'A', 20U};
}

}  // namespace haf
