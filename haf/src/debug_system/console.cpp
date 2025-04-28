#include <haf/include/debug_system/console.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>

#include <haf/include/scene_components/text.hpp>

using namespace htps;
using namespace fmath;
using namespace haf::scene;

namespace
{
const haf::scene::Color ConsoleTextColor{haf::scene::colors::Black};
constexpr htps::fast_u32 kNumLines{10U};
}  // namespace

namespace haf
{

void Console::onAttached()
{
    BaseClass::onAttached();

    /*
        m_textTableNode->onTableNodeCreated +=
            make_function(this, &Console::tableNodeCreated);
        m_textTableNode->TableSize = {2, kNumLines};
        m_textTableNode->createTableNodesIfNecessary();
    */

    m_textTableNode->onTableNodeCreated +=
        make_function(this, &Console::tableNodeCreated);
    m_textTableNode->TableSize = {2, kNumLines};
    m_textTableNode->createTableNodesIfNecessary();

    htps::sptr<Text> test{attachedNode()->component<Text>()};
    test->Text = "Hello";
    test->Font =
        attachedNode()->subSystem<res::IResourceRetriever>()->getBMPFont(
            "console_font");
    test->TextColor       = colors::Green;
    attachedNode()->Scale = {0.2F, 0.2F};
}

void Console::setText(fmath::vector2dst const& nodeIndex, htps::str const& text)
{
    m_textTableNode->nodeAt(nodeIndex)->Text.assignIfDifferent(text);
}

void Console::tableNodeCreated(vector2dst const& /*index*/,
                               sptr<Text> const& text)
{
    //    auto text{node->component<Text>()};
    text->Text      = "CC";
    text->TextColor = ConsoleTextColor;
    text->Font =
        attachedNode()->subSystem<res::IResourceRetriever>()->getBMPFont(
            "console_font");
    // Allow for 20U "A" characters
    text->TextBaseSizeProperty = TextBaseSize{'A', 10U};
}

void Console::addRequirements(component::ComponentRequirements& cReq)
{
    cReq.component(m_textTableNode);
}

}  // namespace haf
