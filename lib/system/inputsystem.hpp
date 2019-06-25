#pragma once

#ifndef LIB_INPUTSYSTEM_INCLUDE_HPP
#define LIB_INPUTSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>

#include <lib/system/appservice.hpp>

namespace lib::backend
{
    class IInputDriver;
}

 namespace lib::input
{
    class InputSystem final : public AppService
    {
    public:
        InputSystem(backend::IInputDriver* const input_driver);
        ~InputSystem() override;

        void update();

        const vector<Key> &pressedKeys() const noexcept;
        const vector<Key> &releasedKeys() const noexcept;
        const KeyStates &keyStates() const noexcept { return m_keyStates; }

        /// Force or simulate a key press.
        /// @param key @b Key to be added.
        void pressKey(const Key key);

        /// Force or simulate a key release.
        /// @param key @b Key to be added.
        void releaseKey(const Key key);

    private:
        void keyPressed(const Key key);
        void keyReleased(const Key key);

        backend::IInputDriver* input_driver_;
        KeyStates m_keyStates;
        vector<Key> m_pressedKeys;
        vector<Key> m_releasedKeys;

    };
}

#endif
