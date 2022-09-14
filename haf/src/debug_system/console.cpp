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

static const haf::scene::Color ConsoleTextColor{haf::scene::colors::Black};
static constexpr htps::fast_u32 kNumLines{10U};
namespace haf
{

void Console::onCreated()
{
    BaseClass::onCreated();
    TableSize = {1, kNumLines};
}

void Console::setText(str const& text)
{
    (void)(text);
}

void Console::tableNodeCreated(
    htps::vector2dst index,
    htps::sptr<haf::scene::nodes::SceneNodeText> const&)
{
    nodeAt(index)->Text      = "Hello2";
    nodeAt(index)->TextColor = ConsoleTextColor;
    nodeAt(index)->Font =
        subSystem<res::IResourceRetriever>()->getBMPFont("console_font");
    // Allow for 20U "A" characters
//    nodeAt(index)->TextBaseSizeProperty = TextBaseSize{'A', 10U};
}

void Console::onAllTableElementsCreated(htps::vector2dst const /*table_size*/)
{
}

}  // namespace haf
