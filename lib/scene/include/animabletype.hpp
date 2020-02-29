#pragma once

#ifndef LIB_SCENE_ANIMABLETYPE_INCLUDE_HPP
#define LIB_SCENE_ANIMABLETYPE_INCLUDE_HPP

namespace lib::scene
{

template <typename PropertyType>
struct AnimableType
{
    using type = PropertyType;
};

} // namespace lib::scene

#endif
