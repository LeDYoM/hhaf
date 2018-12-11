#include "inputsystem.hpp"

#include <lib/include/core/log.hpp>
#include <lib/include/backend/iwindow.hpp>
#include <lib/core/host.hpp>
#include <lib/core/window.hpp>

namespace lib::input
{
	InputSystem::InputSystem(core::Host& host) 
        : AppService{ host }, 
        m_keyStates{} {}

	InputSystem::~InputSystem() = default;

	void InputSystem::keyPressed(const Key key)
	{
		assert_release(key < Key::KeyCount, "Incorrect key value");
		m_keyStates[key] = true;
		m_pressedKeys.push_back(key);
	}

	void InputSystem::keyReleased(const Key key)
	{
		assert_release(key < Key::KeyCount, "Incorrect key value");
		m_keyStates[key] = false;
		m_releasedKeys.push_back(key);
	}

	void InputSystem::preUpdate()
	{
        auto input_driver(host().parentWindow().inputDriver());

        if (input_driver->arePendingKeyPresses() || input_driver->arePendingKeyReleases())
        {
			while (input_driver->arePendingKeyPresses())
            {
				keyPressed(input_driver->popKeyPress());
			}
			while (input_driver->arePendingKeyReleases())
            {
				keyReleased(input_driver->popKeyRelease());
			}
		}
	}

	void InputSystem::postUpdate()
	{
		m_pressedKeys.clear();
		m_releasedKeys.clear();
	}
	const vector<Key>& InputSystem::pressedKeys() const noexcept
	{
		return m_pressedKeys;
	}

	const vector<Key>& InputSystem::releasedKeys() const noexcept
	{
		return m_releasedKeys;
	}
}
