#include "texteditorcomponent.hpp"
#include <lib/scene/nodes/scenenodetext.hpp>

namespace lib::scene
{

void TextEditorComponent::onAttached()
{
    BaseClass::onAttached();

    m_originalText = attachedNodeAs<nodes::SceneNodeText>()->text();
    attachedNodeAs<nodes::SceneNodeText>()->text.set("");

    m_receiver.connect(InputComponent::KeyPressed, [this](const Key &key)
    {
        if (enabled)
        {
            auto attachedTextNode(attachedNodeAs<nodes::SceneNodeText>());
            if (isAscii(key))
            {
                const char c_ascii{toAscii(key)};
                bool success{true};
                if (m_textValidator)
                {
                    success = m_textValidator->canAddChar(
                        attachedTextNode->text(),
                        c_ascii);
                }

                if (success)
                {
                    str new_text{attachedTextNode->text()};
                    new_text.append_char(c_ascii);
                    attachedTextNode->text.set(new_text);
                }
            }
            else if (key == Key::BackSpace && !attachedTextNode->text().empty())
            {
                attachedTextNode->text.set(
                    attachedTextNode->text().substr(0U,
                                                    attachedTextNode->text().size() - 1));
            }
            else if (key == Key::Return)
            {
                bool success{true};
                if (m_textValidator)
                {
                    success = m_textValidator->isValidText(attachedTextNode->text());
                }
                if (success)
                {
                    enabled = false;
                    Accepted(attachedTextNode->text());
                }
            }
            else if (key == Key::Escape)
            {
                attachedTextNode->text.set(m_originalText);
                enabled = false;
                Rejected();
            }
        }
    });
}
} // namespace lib::scene
