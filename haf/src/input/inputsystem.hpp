#ifndef HAF_INPUTSYSTEM_INCLUDE_HPP
#define HAF_INPUTSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <haf/include/input/key.hpp>

#include "system/systembase.hpp"

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

    const htps::vector<input::Key>& pressedKeys() const noexcept;
    const htps::vector<input::Key>& releasedKeys() const noexcept;
    const input::KeyStates& keyStates() const noexcept { return key_states_; }

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
     * @param input_driver  htps::Objectto be set.
     */
    void setInputDriverWrapper(
        htps::sptr<input::InputDriverWrapper> input_driver);

private:
    void keyPressed(input::Key const key);
    void keyReleased(input::Key const key);

    htps::sptr<input::InputDriverWrapper> input_driver_wrapper_;
    input::KeyStates key_states_{};
    htps::vector<input::Key> pressed_keys_;
    htps::vector<input::Key> released_keys_;
};
}  // namespace haf::sys

#endif
