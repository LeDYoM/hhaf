#pragma once

#ifndef LIB_SCENE_ANIMABLETYPE_INCLUDE_HPP
#define LIB_SCENE_ANIMABLETYPE_INCLUDE_HPP

#include <lib/scene/include/color.hpp>

namespace lib::scene
{

template <typename PropertyType>
struct AnimableType
{
    using type = PropertyType;
};

template <>
struct AnimableType<Color>
{
    using type = ColorImp<s16>;
};

} // namespace lib::scene

#endif
