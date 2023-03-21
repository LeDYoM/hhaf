#include <haf/include/input/keyboard_input_component.hpp>
#include "input_system.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{
void KeyboardInputComponent::onAttached()
{
    addUpdater({this, &KeyboardInputComponent::update});
}

void KeyboardInputComponent::update()
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
