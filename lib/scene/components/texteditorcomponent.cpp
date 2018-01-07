#include "texteditorcomponent.hpp"

namespace lib::scene
{
	using namespace input;

	void TextEditorComponent::onAttached()
	{
		BaseClass::onAttached();
		
		m_originalText = node()->text();
		node()->text.set("");

		m_receiver.connect(InputComponent::KeyPressed, [this](const Key&key) {
			if (isAscii(key)) {
				const char c_ascii{ toAscii(key) };
				bool success{ true };
				if (m_textValidator) {
					success = m_textValidator->canAddChar(node()->text(), c_ascii);
				}
				if (success) {
					node()->text.set(node()->text() + make_str(c_ascii));
				}
			} else if (key == Key::BackSpace && !node()->text().empty()) {
				node()->text.set(node()->text().substr(0, node()->text().size() - 1));
			} else if (key == Key::Return) {
				bool success{ true };
				if (m_textValidator) {
					success = m_textValidator->isValidText(node()->text());
				}
				if (success) {
					Accepted(node()->text());
				}
			}
			else if (key == Key::Escape) {
				node()->text.set(m_originalText);
				Rejected();
			}
		});
	}
}
