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
class SystemAccess;

template <typename SystemType>
const SystemType &getSystem(mtps::rptr<const SystemAccess>);

template <typename SystemType>
SystemType &getSystem(mtps::rptr<SystemAccess>);

template <typename SystemType>
const SystemType &getSystem(mtps::rptr<const scene::SceneNode>);

template <typename SystemType>
SystemType &getSystem(mtps::rptr<scene::SceneNode>);
} // namespace lib::sys

#endif
