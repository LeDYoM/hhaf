#include "inputsystem.hpp"

#include <lib/include/core/log.hpp>
#include <lib/include/backend/iwindow.hpp>
#include <lib/core/host.hpp>
#include <lib/core/window.hpp>

namespace lib::input
{
	InputSystem::InputSystem(core::Host& host) 
        : AppService{ host }, m_keyStates {} {}

	InputSystem::~InputSystem() = default;

	void InputSystem::keyPressed(const Key key)
	{
		__ASSERT(key < Key::KeyCount, "Incorrect key value");
		m_keyStates[key] = true;
		m_pressedKeys.push_back(key);
	}

	void InputSystem::keyReleased(const Key key)
	{
		__ASSERT(key < Key::KeyCount, "Incorrect key value");
		m_keyStates[key] = false;
		m_releasedKeys.push_back(key);
	}

	void InputSystem::preUpdate()
	{
		auto &window( host().parentWindow() );
		if (window.arePendingKeyPresses() || window.arePendingKeyReleases()) {
			while (window.arePendingKeyPresses()) {
				keyPressed(window.popKeyPress());
			}
			while (window.arePendingKeyReleases()) {
				keyReleased(window.popKeyRelease());
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
