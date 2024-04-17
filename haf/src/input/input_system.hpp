HAF_PRAGMA_ONCE
#ifndef HAF_INPUTSYSTEM_INCLUDE_HPP
#define HAF_INPUTSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/input/key.hpp>

#include "system/system_base.hpp"
#include "keyboard_data.hpp"

namespace haf::input
{
class InputDriverWrapper;
}

namespace haf::sys
{
/**
 * @brief System responsible of managing everything related with inputs from
 * the user.
 */
class InputSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;

    void preUpdate();
    void update();
    void postUpdate();

    core::vector<input::Key> const& pressedKeys() const noexcept;
    core::vector<input::Key> const& releasedKeys() const noexcept;
    input::KeyStates const& keyStates() const noexcept;
    input::KeyState keyState(input::Key const key) const noexcept;

    bool shiftPressed() const noexcept;
    bool controlPressed() const noexcept;

    /**
     * @brief Force or simulate a key press.
     * @param key Key to be added.
     */
    void simulatePressKey(const input::Key key);

    /**
     * @brief Force or simulate a key release.
     * @param key Key to be added.
     */
    void simulateReleaseKey(const input::Key key);

    void setSharedKeyboardData(
        core::sptr<input::KeyboardData> shared_keyboard_data);

private:
    void keyPressed(input::Key const key);
    void keyReleased(input::Key const key);

    core::sptr<input::InputDriverWrapper> input_driver_wrapper_;
    core::sptr<input::KeyboardData> m_shared_keyboard_data;
};
}  // namespace haf::sys

#endif
