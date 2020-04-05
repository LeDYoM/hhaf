#pragma once

#ifndef LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP
#define LIB_BACKEND_SFMLB_INPUTDRIVER_INCLUDE_HPP

#include <backend_dev/include/iinputdriver.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>

namespace haf::backend::sfmlb
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

    void keyPressed(const input::Key) override;
    void keyReleased(const input::Key) override;

    void keyEvent(const sf::Event &e);

    std::queue<input::Key> m_keysPressed;
    std::queue<input::Key> m_keysReleased;
};
} // namespace haf::backend::sfmlb

#endif
