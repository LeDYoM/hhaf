#include "texteditorcomponent.hpp"

namespace lib::scene
{
	using namespace input;

	void TextEditorComponent::onAttached()
	{
		BaseClass::onAttached();

		m_receiver.connect(InputComponent::KeyPressed, [this](const Key&key) {
			if (isAscii(key)) {
				const char c_ascii{ toAscii(key) };
				bool success{ true };
				if (m_textValidator) {
					success = m_textValidator->canAddChar(c_ascii);
				}
				if (success) {
					m_text += make_str(c_ascii);
				}
			} else if (key == Key::BackSpace && !m_text.empty()) {
				m_text.pop_char();
			} else if (key == Key::Return) {
				bool success{ true };
				if (m_textValidator) {
					success = m_textValidator->isValidText(m_text);
				}
				if (success) {
					accepted(m_text);
				}
			}
			else if (key == Key::Escape) {
				rejected();
			}
		});
		//		InputComponent::KeyReleased.connect(keyReleased);
	}
	void TextEditorComponent::update()
	{
		BaseClass::update();
	}
}
