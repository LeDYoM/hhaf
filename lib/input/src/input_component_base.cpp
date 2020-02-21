#include "input_component_base.hpp"

#include <lib/include/liblog.hpp>
#include <lib/input/include/key.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/input/i_include/get_inputsystem.hpp>

namespace lib::input
{
bool InputComponentBase::isPressed(const Key key)
{
    if (attachedNode())
    {
        return getInputSystem(attachedNode()).keyStates()[KeyIndex(key)];
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
} // namespace lib::scene
