#include <haf/include/input/keyboard_input_manager.hpp>
#include "input_system.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include "system/get_system.hpp"
#include "input/input_system.hpp"

namespace haf::input
{
KeyboardInputManager::KeyboardInputManager(
    sys::ISystemProvider& systemProvider) noexcept :
    m_system_provider{systemProvider}
{}

void KeyboardInputManager::update()
{
    const sys::InputSystem& input_system{
        sys::getSystem<sys::InputSystem>(&m_system_provider)};

    for (const auto& pressedKey : input_system.pressedKeys())
    {
        KeyPressed(pressedKey);
    }

    for (const auto& releasedKey : input_system.releasedKeys())
    {
        KeyReleased(releasedKey);
    }
}
}  // namespace haf::input
