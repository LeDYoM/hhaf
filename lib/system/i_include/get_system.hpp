#pragma once

#ifndef LIB_SYSTEM_INTERNAL_GET_INCLUDE_HPP
#define LIB_SYSTEM_INTERNAL_GET_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::scene
{
    class SceneNode;
}

namespace lib::sys
{
    template <typename SystemType>
    const SystemType& getSystem(rptr<const scene::SceneNode>);

    template <typename SystemType>
    SystemType& getSystem(rptr<scene::SceneNode>);

} // namespace lib::input

#endif
