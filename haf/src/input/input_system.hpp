HAF_PRAGMA_ONCE
#ifndef HAF_INPUTSYSTEM_INCLUDE_HPP
#define HAF_INPUTSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/input/key.hpp>

#include "system/system_base.hpp"

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

    bool shitPressed() const noexcept;
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

    /**
     * @brief Set the Input Driver object
     * @param input_driver  mcs::Objectto be set.
     */
    void setInputDriverWrapper(
        htps::sptr<input::InputDriverWrapper> input_driver);

private:
    void keyPressed(input::Key const key);
    void keyReleased(input::Key const key);

    core::sptr<input::InputDriverWrapper> input_driver_wrapper_;
    input::KeyStates key_states_{};
    core::vector<input::Key> pressed_keys_;
    core::vector<input::Key> released_keys_;
};
}  // namespace haf::sys

#endif
