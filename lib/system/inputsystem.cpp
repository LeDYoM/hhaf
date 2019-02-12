#include "inputsystem.hpp"

#include <lib/include/core/log.hpp>
#include <backend_dev/include/iinputdriver.hpp>

namespace lib::input
{
	InputSystem::InputSystem(backend::IInputDriver* const input_driver)
        : AppService{ }, input_driver_{ input_driver, nullptr }, m_keyStates{} {}

	InputSystem::~InputSystem() = default;

    void InputSystem::injectInputDriver(backend::IInputDriver * a_input_driver)
    {
        input_driver_[1] = a_input_driver;
    }

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

	void InputSystem::update()
	{
        m_pressedKeys.clear();
        m_releasedKeys.clear();

        std::for_each(
            std::begin(input_driver_), 
            std::end(input_driver_),
            [this](backend::IInputDriver* const id) 
            { 
                if (id != nullptr)
                {
                    updateInputDriver(id);
                }
            }

        );
	}

    const vector<Key>& InputSystem::pressedKeys() const noexcept
	{
		return m_pressedKeys;
	}

	const vector<Key>& InputSystem::releasedKeys() const noexcept
	{
		return m_releasedKeys;
	}

    void InputSystem::updateInputDriver(backend::IInputDriver * const input_driver)
    {
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
}
