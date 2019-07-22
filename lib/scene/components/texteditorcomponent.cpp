#include "texteditorcomponent.hpp"
#include <lib/scene/nodes/scenenodetext.hpp>

namespace lib::scene
{
	using namespace input;

    void TextEditorComponent::onAttached()
    {
        BaseClass::onAttached();
        
        m_originalText = attachedNodeAs<nodes::SceneNodeText>()->text()();
        attachedNodeAs<nodes::SceneNodeText>()->text.set(Text_t(""));

        m_receiver.connect(InputComponent::KeyPressed, [this](const Key&key) {
            auto attachedTextNode(attachedNodeAs<nodes::SceneNodeText>());
            if (isAscii(key)) {
                const char c_ascii{ toAscii(key) };
                bool success{ true };
                if (m_textValidator) {
                    success = m_textValidator->canAddChar(attachedTextNode->text()(), c_ascii);
                }
                if (success) {
                    attachedTextNode->text.set(Text_t(attachedTextNode->text()() + make_str(c_ascii)));
                }
            }
            else if (key == Key::BackSpace && !attachedTextNode->text()().empty()) 
            {
                attachedTextNode->text.set(
                    Text_t(attachedTextNode->text()().substr(0, 
                        attachedTextNode->text()().size() - 1)));
            }
            else if (key == Key::Return) {
                bool success{ true };
                if (m_textValidator) {
                    success = m_textValidator->isValidText(attachedTextNode->text()());
                }
                if (success) {
                    Accepted(attachedTextNode->text()());
                }
            }
            else if (key == Key::Escape) {
                attachedTextNode->text.set(Text_t(m_originalText));
                Rejected();
            }
        });
    }
}
