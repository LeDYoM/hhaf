#pragma once

#ifndef HAF_SCENE_ANIMABLETYPE_INCLUDE_HPP
#define HAF_SCENE_ANIMABLETYPE_INCLUDE_HPP

#include <haf/scene/include/color.hpp>

namespace haf::scene
{

template <typename PropertyType>
struct AnimableType
{
    using type = PropertyType;
};

template <>
struct AnimableType<Color>
{
    using type = ColorImp<mtps::s16>;
};

}  // namespace haf::scene

#endif
