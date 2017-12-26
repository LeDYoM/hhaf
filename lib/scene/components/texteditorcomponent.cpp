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
				node()->text.set(node()->text() + make_str(c_ascii));
			}
		});
		//		InputComponent::KeyReleased.connect(keyReleased);
	}
	void TextEditorComponent::update()
	{
		BaseClass::update();
	}
}
