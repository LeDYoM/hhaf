#include "input_component_base.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/input/include/key.hpp>
#include <haf/input/i_include/inputsystem.hpp>
#include <haf/system/i_include/get_system.hpp>

namespace haf::input
{
bool InputComponentBase::isPressed(const Key key)
{
    if (attachedNode())
    {
        return sys::getSystem<sys::InputSystem>(attachedNode()).keyStates()[KeyIndex(key)];
    }
    return false;
}

bool InputComponentBase::isShiftPressed() const
{
    return false;
}

char InputComponentBase::toAscii(const Key key) noexcept
{
    return static_cast<char>(KeyIndex(key) + (isShiftPressed() ? 65 : 65));
}
} // namespace haf::scene
