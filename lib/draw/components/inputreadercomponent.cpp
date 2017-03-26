#include "inputreadercomponent.hpp"

#include <lib/core/log.hpp>
#include <lib/include/key.hpp>
#include <lib/core/host.hpp>
#include <lib/core/window.hpp>
#include <lib/core/inputsystem.hpp>

namespace lib
{
	namespace draw
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

		void InputComponent::update()
		{
		}

		bool InputComponent::isPressed(const input::Key key)
		{
			return host().parentWindow().currentKeyStates()[key];
		}
	}
}
