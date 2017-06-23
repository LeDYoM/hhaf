#include "inputcomponent.hpp"

#include <mtypes/include/log.hpp>
#include <lib/include/key.hpp>
#include <lib/core/host.hpp>
#include <lib/core/window.hpp>
#include <lib/core/inputsystem.hpp>

namespace lib
{
	namespace scene
	{
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

		void InputComponent::setOnKeyPressedHandler(KeyHandler_t keyHandlerPressed) noexcept
		{
			m_onKeyPressed = std::move(keyHandlerPressed);
		}

		void InputComponent::setOnKeyReleasedHandler(KeyHandler_t keyHandlerReleased) noexcept
		{
			m_onKeyReleased = std::move(keyHandlerReleased);
		}

		void InputComponent::update()
		{
			if (!host().inputSystem().pressedKeys().empty() && m_onKeyPressed) {
				for (const auto pressedKey : host().inputSystem().pressedKeys()) {
					m_onKeyPressed(pressedKey);
				}
			}

			if (!host().inputSystem().releasedKeys().empty() && m_onKeyReleased) {
				for (const auto releasedKey : host().inputSystem().releasedKeys()) {
					m_onKeyReleased(releasedKey);
				}
			}
		}

		bool InputComponent::isPressed(const input::Key key)
		{
			return host().inputSystem().keyStates()[key];
		}
	}
}
