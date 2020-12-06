#ifndef HAF_INPUTSYSTEM_INCLUDE_HPP
#define HAF_INPUTSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <haf/input/include/key.hpp>

#include <system/i_include/systembase.hpp>

namespace haf::input
{
class InputDriver;
}

namespace haf::sys
{
class InputSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;

    void update();

    const mtps::vector<input::Key>& pressedKeys() const noexcept;
    const mtps::vector<input::Key>& releasedKeys() const noexcept;
    const input::KeyStates& keyStates() const noexcept { return m_keyStates; }

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
     * @param input_driver  mtps::Objectto be set.
     */
    void setInputDriver(mtps::sptr<input::InputDriver> input_driver);

private:
    void keyPressed(const input::Key key);
    void keyReleased(const input::Key key);

    mtps::sptr<input::InputDriver> input_driver_;
    input::KeyStates m_keyStates{};
    mtps::vector<input::Key> m_pressedKeys;
    mtps::vector<input::Key> m_releasedKeys;
};
}  // namespace haf::sys

#endif
