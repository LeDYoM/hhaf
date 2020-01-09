#include "virtual_input_component.hpp"

#include <lib/include/liblog.hpp>
#include <lib/include/key.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
VirtualInputComponent::VirtualInputComponent() = default;
VirtualInputComponent::~VirtualInputComponent() = default;

void VirtualInputComponent::update()
{
    if (attachedNode())
    {
        const sys::InputSystem &input_system{attachedNode()->inputSystem()};

        for (const auto &pressedKey : input_system.pressedKeys())
        {
            onKeyPressed(pressedKey);
        }

        for (const auto &releasedKey : input_system.releasedKeys())
        {
            onKeyReleased(releasedKey);
        }
    }
}
} // namespace lib::scene
