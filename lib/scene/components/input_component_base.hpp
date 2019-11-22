#pragma once

#ifndef LIB_INPUT_COMPONENT_BASE_INCLUDE_HPP
#define LIB_INPUT_COMPONENT_BASE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/include/key.hpp>

namespace lib::scene
{
class InputComponentBase : public IComponent
{
public:
    bool isPressed(const input::Key key);

    static inline bool isAscii(const input::Key key) noexcept
    {
        return key >= input::Key::A && key <= input::Key::Z;
    }

    char toAscii(const input::Key key) noexcept;
    bool isShiftPressed() const;
};
} // namespace lib::scene

#endif
