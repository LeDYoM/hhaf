#include "inputcomponent.hpp"

#include <lib/include/core/log.hpp>
#include <lib/include/key.hpp>
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenemanager.hpp>

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
        if (attachedNode())
        {
            core::Host &host{ attachedNode()->parentScene()->sceneManager().host() };

            for (const auto &pressedKey : host.inputSystem().pressedKeys())
            {
                KeyPressed(pressedKey);
            }

            for (const auto &releasedKey : host.inputSystem().releasedKeys())
            {
                KeyReleased(releasedKey);
            }
        }
	}

	bool InputComponent::isPressed(const Key key)
	{
        if (attachedNode())
        {
            core::Host &host{ attachedNode()->parentScene()->sceneManager().host() };
            return host.inputSystem().keyStates()[key];
        }
        return false;
	}

	bool InputComponent::isShiftPressed() const
	{
/*        if (attachedNode())
        {
            const core::Host &host{ attachedNode()->parentScene()->sceneManager().host() };
            return host().inputSystem().keyStates()[Key::LShift] || host().inputSystem().keyStates()[Key::RShift];
        }
        */
        return false;
	}

	char InputComponent::toAscii(const Key key) noexcept
	{
		return static_cast<char>(key + (isShiftPressed() ? 127 : 65));
	}
}
