#include "inputcomponent.hpp"

#include <lib/include/core/log.hpp>
#include <lib/include/key.hpp>
#include <lib/core/host.hpp>
#include <lib/core/window.hpp>
#include <lib/core/inputsystem.hpp>

namespace lib::scene
{
	using namespace input;

	class InputComponent::InputComponentPrivate
	{
	};
	InputComponent::InputComponent()
		: m_private{ new InputComponentPrivate } {}

	InputComponent::~InputComponent()
	{
		__ASSERT(m_private, "Destructing private class that is nullptr");
		delete m_private;
		m_private = nullptr;
	}

	void InputComponent::update()
	{
		if (!host().inputSystem().pressedKeys().empty()) {
			for (const auto &pressedKey : host().inputSystem().pressedKeys()) {
				KeyPressed(pressedKey);
			}
		}

		if (!host().inputSystem().releasedKeys().empty()) {
			for (const auto &releasedKey : host().inputSystem().releasedKeys()) {
				KeyReleased(releasedKey);
			}
		}
	}

	bool InputComponent::isPressed(const Key key)
	{
		return host().inputSystem().keyStates()[key];
	}

	bool InputComponent::isShiftPressed() const
	{
		return host().inputSystem().keyStates()[Key::LShift] || host().inputSystem().keyStates()[Key::RShift];
	}

	char InputComponent::toAscii(const Key key) noexcept
	{
		return static_cast<char>(key + (isShiftPressed() ? 127 : 65));
	}
}
