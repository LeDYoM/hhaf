#pragma once

#ifndef LIB_INPUTSYSTEM_INTERNAL_GET_INCLUDE_HPP
#define LIB_INPUTSYSTEM_INTERNAL_GET_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class SceneNode;
}
namespace lib::sys
{
    class InputSystem;
}

namespace lib::input
{
    const sys::InputSystem& getInputSystem(rptr<const scene::SceneNode> );
    sys::InputSystem& getInputSystem(rptr<scene::SceneNode>);

} // namespace lib::input

#endif
