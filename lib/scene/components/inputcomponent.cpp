#include "inputcomponent.hpp"

#include <lib/include/liblog.hpp>
#include <lib/include/key.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{
    using namespace input;

    class InputComponent::InputComponentPrivate
    {
    };
    InputComponent::InputComponent()
        : priv_{ new InputComponentPrivate } {}

    InputComponent::~InputComponent() = default;

    void InputComponent::update()
    {
        if (attachedNode())
        {
            const input::InputSystem& input_system{ attachedNode()->inputSystem() };

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

    bool InputComponent::isPressed(const Key key)
    {
        if (attachedNode())
        {
            return attachedNode()->inputSystem().keyStates()[key];
        }
        return false;
    }

    bool InputComponent::isShiftPressed() const
    {
    /*        if (attachedNode())
        {
            const core::Host &host{ attachedNode()->parentScene()->sceneManager().host() };
            return host().inputSystem().keyStates()[Key::LShift] || host().inputSystem().keyStates()[Key::RShift];
        }
        */
        return false;
    }

    char InputComponent::toAscii(const Key key) noexcept
    {
        return static_cast<char>(key + (isShiftPressed() ? 127 : 65));
    }
}
