module;

#include "system/get_system.hpp"

export module haf:input:input_component;

import :component:component;
import :key;
import :core;
import :input_system;

namespace haf::input
{
class InputComponentBase : public component::Component
{
public:
    bool isPressed(const Key key)
    {
        if (attachedNode())
        {
            return sys::getSystem<sys::InputSystem>(attachedNode())
                .keyState(key);
        }
        return false;
    }

    static constexpr inline bool isAscii(const Key key) noexcept
    {
        return key >= Key::A && key <= Key::Z;
    }

    virtual char toAscii(Key const key) const noexcept
    {
        return static_cast<char>(keyIndex(key) + (isShiftPressed() ? 65 : 65));
    }

    virtual bool isShiftPressed() const noexcept { return false; }
};
}  // namespace haf::input
