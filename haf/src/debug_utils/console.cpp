#include <haf/include/debug_utils/console.hpp>
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

    auto a  = createSceneNode<SceneNodeText>("scnText");
    a->Font = subSystem<res::IResourceRetriever>()->getBMPFont("console_font");

//    Position     = {100.0F, 0.0F};
//    Scale        = {1 / 2000.0F, 1 / 2000.0F};
//    a->Text      = "234 ABC abc";
    a->Text      = "AYi2_+q";
    a->TextColor = colors::Red;
    a->setLeftTopPositionScale({0.5F, 0.1F});
    a->TextBaseSizeProperty = TextBaseSize{'A', 0U};
//    a->Position = {-0.250F, -0.25F};
//    a->Scale = {0.5F, 0.5F};
}

void Console::setText(str const& text)
{
    (void)(text);
}

}  // namespace haf
