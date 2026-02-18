export module haf:debug_system:console;

import :component;
import :scene_components;
import :core;
import :resources;
import :scene_components;

namespace haf
{
namespace
{
const haf::scene::Color ConsoleTextColor{haf::scene::colors::Black};
constexpr htps::fast_u32 kNumLines{10U};
}  // namespace

class Console : public component::Component
{
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;

    void onAttached() override;
    {
        BaseClass::onAttached()

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
        test->TextColor                                    = colors::Green;
        attachedNode()->component<Transformation>()->Scale = {0.2F, 0.2F};
    }

    void tableNodeCreated(fmath::vector2dst const&,
                          htps::sptr<haf::scene::Text> const&)
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

    void setText(fmath::vector2dst const& nodeIndex, htps::str const& text)
    {
        m_textTableNode->nodeAt(nodeIndex)->Text.assignIfDifferent(text);
    }

private:
    void addRequirements(component::ComponentRequirements&) override
    {
        cReq.component(m_textTableNode);
    }

    htps::sptr<scene::TableOf<scene::Text>> m_textTableNode;
};
}  // namespace haf
