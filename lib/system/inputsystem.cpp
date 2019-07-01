#include "inputsystem.hpp"

#include <lib/include/liblog.hpp>
#include <backend_dev/include/iinputdriver.hpp>

namespace lib::input
{
	InputSystem::InputSystem(backend::IInputDriver* const input_driver)
        : AppService{ }, input_driver_{ input_driver }, m_keyStates{} {}

	InputSystem::~InputSystem() = default;

	void InputSystem::update()
	{
        m_pressedKeys.clear();
        m_releasedKeys.clear();

        if (input_driver_->arePendingKeyPresses() || input_driver_->arePendingKeyReleases())
        {
            while (input_driver_->arePendingKeyPresses())
            {
                keyPressed(input_driver_->popKeyPress());
            }
            while (input_driver_->arePendingKeyReleases())
            {
                keyReleased(input_driver_->popKeyRelease());
            }
        }
    }

    const vector<Key>& InputSystem::pressedKeys() const noexcept
    {
        return m_pressedKeys;
    }

    const vector<Key>& InputSystem::releasedKeys() const noexcept
    {
        return m_releasedKeys;
    }

    void InputSystem::keyPressed(const Key key)
    {
        assert_release(key < Key::KeyCount, "Incorrect key value");
        log_debug_info("InputSystem: Key pressed: ", key);
        m_keyStates[key] = true;
        m_pressedKeys.push_back(key);
    }

    void InputSystem::keyReleased(const Key key)
    {
        assert_release(key < Key::KeyCount, "Incorrect key value");
        log_debug_info("InputSystem: Key released: ", key);
        m_keyStates[key] = false;
        m_releasedKeys.push_back(key);
    }

    void InputSystem::pressKey(const Key key)
    {
        input_driver_->keyPressed(key);
    }

    void InputSystem::releaseKey(const Key key)
    {
        input_driver_->keyReleased(key);
    }
}
