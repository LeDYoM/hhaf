#pragma once

#ifndef LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <lib/include/backend/iinputdriver.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>

namespace lib::backend::sfmlb
{
    class InputDriver : public IInputDriver
    {
    public:
        InputDriver() = default;
        ~InputDriver() override = default;

        bool arePendingKeyPresses() const override;
        bool arePendingKeyReleases() const override;

        input::Key popKeyPress() override;
        input::Key popKeyRelease() override;

        void keyEvent(const sf::Event &e);

        std::queue<input::Key> m_keysPressed;
        std::queue<input::Key> m_keysReleased;

    };
}

#endif
