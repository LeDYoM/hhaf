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
class InputSystem final : public AppService
{
public:
    InputSystem(sptr<input::InputDriver> input_driver);
    ~InputSystem() override;

    void update();

    const vector<Key> &pressedKeys() const noexcept;
    const vector<Key> &releasedKeys() const noexcept;
    const KeyStates &keyStates() const noexcept { return m_keyStates; }

    /// Force or simulate a key press.
    /// @param key @b Key to be added.
    void simulatePressKey(const Key key);

    /// Force or simulate a key release.
    /// @param key @b Key to be added.
    void simulateReleaseKey(const Key key);

private:
    void keyPressed(const Key key);
    void keyReleased(const Key key);

    sptr<input::InputDriver> input_driver_;
    KeyStates m_keyStates;
    vector<Key> m_pressedKeys;
    vector<Key> m_releasedKeys;
};
} // namespace lib::sys

#endif
