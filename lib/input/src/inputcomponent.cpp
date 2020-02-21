#include <lib/input/include/inputcomponent.hpp>

#include <lib/include/liblog.hpp>
#include <lib/input/include/key.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/input/i_include/get_inputsystem.hpp>

namespace lib::input
{

InputComponent::InputComponent() = default;
InputComponent::~InputComponent() = default;

void InputComponent::update()
{
    if (attachedNode())
    {
        const sys::InputSystem &input_system{getInputSystem(attachedNode())};

        for (const auto &pressedKey : input_system.pressedKeys())
        {
            KeyPressed(pressedKey);
        }

        for (const auto &releasedKey : input_system.releasedKeys())
        {
            KeyReleased(releasedKey);
        }
    }
}
} // namespace lib::scene
