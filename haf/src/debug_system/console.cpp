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

void Console::onAttached()
{
    BaseClass::onAttached();
    composedComponent()->onTableNodeCreated +=
        make_function(this, &Console::tableNodeCreated);
    composedComponent()->TableSize = {2, kNumLines};
    composedComponent()->createTableNodesIfNecessary();
    composedComponent()->onTableNodeCreated +=
        make_function(this, &Console::tableNodeCreated);
}

void Console::setText(htps::vector2dst const& nodeIndex, htps::str const& text)
{
    composedComponent()->nodeAt(nodeIndex)->Text.assignIfDifferent(text);
}

void Console::tableNodeCreated(
    htps::vector2dst const& /*index*/,
    htps::sptr<haf::scene::nodes::SceneNodeText> const& node)
{
    node->Text      = "AAAAAAAAAA";
    node->TextColor = ConsoleTextColor;
    node->Font =
        attachedNode()->subSystem<res::IResourceRetriever>()->getBMPFont(
            "console_font");
    // Allow for 20U "A" characters
    node->TextBaseSizeProperty = TextBaseSize{'A', 10U};
}

}  // namespace haf
