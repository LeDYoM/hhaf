#include "texteditorcomponent.hpp"
#include <haf/scene_nodes/include/scenenodetext.hpp>

using namespace mtps;

namespace haf::scene
{
void TextEditorComponent::onAttached()
{
    BaseClass::onAttached();

    using namespace haf::scene::nodes;

    auto const& text_prop(attachedNodeAs<nodes::SceneNodeText>());
    m_originalText = text_prop->get<Text>();
    text_prop->set<Text>("");

    using namespace haf::input;

    m_receiver.connect(
        InputComponent::KeyPressed, [this](Key const& key) {
            if (enabled)
            {
                auto const& text_prop(attachedNodeAs<nodes::SceneNodeText>());
                if (isAscii(key))
                {
                    const char c_ascii{this->toAscii(key)};
                    bool success{true};
                    if (m_textValidator)
                    {
                        success = m_textValidator->canAddChar(
                            text_prop->get<Text>(), c_ascii);
                    }

                    if (success)
                    {
                        str new_text{text_prop->get<Text>()};
                        new_text.append_char(c_ascii);
                        text_prop->set<Text>(std::move(new_text));
                    }
                }
                else if (key == Key::BackSpace &&
                         !text_prop->get<Text>().empty())
                {
                    text_prop->set<Text>(text_prop->get<Text>().substr(
                        0U, text_prop->get<Text>().size() - 1));
                }
                else if (key == Key::Return)
                {
                    bool success{true};
                    if (m_textValidator)
                    {
                        success =
                            m_textValidator->isValidText(text_prop->get<Text>());
                    }
                    if (success)
                    {
                        enabled = false;
                        Accepted(text_prop->get<Text>());
                    }
                }
                else if (key == Key::Escape)
                {
                    text_prop->set<Text>(m_originalText);
                    enabled = false;
                    Rejected();
                }
            }
        });
}
}  // namespace haf::scene
