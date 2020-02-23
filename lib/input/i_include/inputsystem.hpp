#pragma once

#ifndef LIB_INPUTSYSTEM_INCLUDE_HPP
#define LIB_INPUTSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/input/include/key.hpp>

#include <lib/system/appservice.hpp>

namespace lib::input
{
class InputDriver;
}

namespace lib::sys
{
class InputSystem final : public HostedAppService
{
public:
    InputSystem(sys::SystemProvider& system_provider,
        sptr<input::InputDriver> input_driver);
    ~InputSystem() override;

    void update();

    const vector<input::Key> &pressedKeys() const noexcept;
    const vector<input::Key> &releasedKeys() const noexcept;
    const input::KeyStates &keyStates() const noexcept { return m_keyStates; }

    /// Force or simulate a key press.
    /// @param key @b Key to be added.
    void simulatePressKey(const input::Key key);

    /// Force or simulate a key release.
    /// @param key @b Key to be added.
    void simulateReleaseKey(const input::Key key);

private:
    void keyPressed(const input::Key key);
    void keyReleased(const input::Key key);

    sptr<input::InputDriver> input_driver_;
    input::KeyStates m_keyStates;
    vector<input::Key> m_pressedKeys;
    vector<input::Key> m_releasedKeys;
};
} // namespace lib::sys

#endif
