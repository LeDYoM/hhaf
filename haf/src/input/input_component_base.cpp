#include <haf/include/input/input_component_base.hpp>
#include "inputsystem.hpp"

#include <haf/include/input/key.hpp>

#include <hlog/include/hlog.hpp>
#include "system/get_system.hpp"

namespace haf::input
{
bool InputComponentBase::isPressed(const Key key)
{
    if (attachedNode())
    {
        return sys::getSystem<sys::InputSystem>(attachedNode())
            .keyStates()[KeyIndex(key)];
    }
    return false;
}

bool InputComponentBase::isShiftPressed() const noexcept
{
    return false;
}

char InputComponentBase::toAscii(const Key key) const noexcept
{
    return static_cast<char>(KeyIndex(key) + (isShiftPressed() ? 65 : 65));
}
}  // namespace haf::input
