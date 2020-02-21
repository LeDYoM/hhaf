#include "inputcomponent.hpp"

#include <lib/include/liblog.hpp>
#include <lib/input/include/key.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>

namespace lib::input
{
InputComponent::InputComponent() = default;
InputComponent::~InputComponent() = default;

void InputComponent::update()
{
    if (attachedNode())
    {
        const sys::InputSystem &input_system{attachedNode()->inputSystem()};

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
} // namespace lib::input
