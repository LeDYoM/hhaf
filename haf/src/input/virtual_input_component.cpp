#include <haf/include/input/virtual_input_component.hpp>
#include "inputsystem.hpp"
#include <haf/include/input/key.hpp>

#include "system/get_system.hpp"

namespace haf::input
{
VirtualInputComponent::VirtualInputComponent()  = default;
VirtualInputComponent::~VirtualInputComponent() = default;

void VirtualInputComponent::update()
{
    if (attachedNode() != nullptr)
    {
        sys::InputSystem const& input_system{
            sys::getSystem<sys::InputSystem>(attachedNode())};

        for (auto const pressedKey : input_system.pressedKeys())
        {
            onKeyPressed(pressedKey);
        }

        for (auto const releasedKey : input_system.releasedKeys())
        {
            onKeyReleased(releasedKey);
        }
    }
}
}  // namespace haf::input
