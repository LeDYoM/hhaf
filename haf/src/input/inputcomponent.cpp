#include <haf/include/input/inputcomponent.hpp>
#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{

InputComponent::InputComponent()  = default;
InputComponent::~InputComponent() = default;

void InputComponent::update()
{
    if (attachedNode())
    {
        const sys::InputSystem& input_system{
            sys::getSystem<sys::InputSystem>(attachedNode())};

        for (const auto& pressedKey : input_system.pressedKeys())
        {
            KeyPressed(pressedKey);
        }

        for (const auto& releasedKey : input_system.releasedKeys())
        {
            KeyReleased(releasedKey);
        }
    }
}
}  // namespace haf::input
