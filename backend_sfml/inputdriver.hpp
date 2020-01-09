#pragma once

#ifndef LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <backend_dev/include/iinputdriver.hpp>
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

        Key popKeyPress() override;
        Key popKeyRelease() override;

        void keyPressed(const Key) override;
        void keyReleased(const Key) override;

        void keyEvent(const sf::Event &e);

        std::queue<Key> m_keysPressed;
        std::queue<Key> m_keysReleased;
    };
}

#endif
