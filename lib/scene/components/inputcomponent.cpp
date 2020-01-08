#include "inputcomponent.hpp"

#include <lib/include/liblog.hpp>
#include <lib/include/key.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
using namespace input;

InputComponent::InputComponent() = default;
InputComponent::~InputComponent() = default;

void InputComponent::update()
{
    if (attachedNode())
    {
        const input::InputSystem &input_system{attachedNode()->inputSystem()};

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
