#pragma once

#ifndef HAF_TYPES_SCENE_TYPES_INCLUDE_HPP
#define HAF_TYPES_SCENE_TYPES_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf
{
using SceneUnit        = htps::f32;
using SceneCoordinates = htps::vector2d<SceneUnit>;
using SceneBox         = htps::Rect<SceneUnit>;

}  // namespace haf

#endif
