#pragma once

#ifndef LIB_BACKEND_INPUT_INCLUDE_HPP
#define LIB_BACKEND_INPUT_INCLUDE_HPP

#include <lib/include/backend/iinput.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>

namespace lib::backend::sfmlb
{
    class InputSystem : public IInput
    {
    public:
        InputSystem() = default;
        ~InputSystem() override = default;

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
