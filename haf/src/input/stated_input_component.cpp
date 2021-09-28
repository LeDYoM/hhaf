#include <haf/include/input/stated_input_component.hpp>
#include "inputsystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"

namespace haf::input
{

StatedInputComponent::StatedInputComponent()  = default;
StatedInputComponent::~StatedInputComponent() = default;

void StatedInputComponent::update()
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
