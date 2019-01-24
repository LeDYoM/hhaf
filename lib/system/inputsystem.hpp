#pragma once

#ifndef LIB_INPUTSYSTEM_INCLUDE_HPP
#define LIB_INPUTSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>

#include <lib/system/appservice.hpp>

namespace lib
{
    namespace backend
    {
        class IInputDriver;
    }

    namespace input
	{
        class InputSystem final : public AppService
        {
        public:
            InputSystem(backend::IInputDriver* const input_driver);
            ~InputSystem();

            void injectInputDriver(backend::IInputDriver *a_input_driver);

            void keyPressed(const Key key);
            void keyReleased(const Key key);
            void update();

            const vector<Key> &pressedKeys() const noexcept;
            const vector<Key> &releasedKeys() const noexcept;
            const KeyStates &keyStates() const noexcept { return m_keyStates; }

        private:
            void updateInputDriver(backend::IInputDriver *const input_driver);
            backend::IInputDriver* input_driver_[2];
            KeyStates m_keyStates;
			vector<Key> m_pressedKeys;
			vector<Key> m_releasedKeys;

		};
	}
}

#endif
