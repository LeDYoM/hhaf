HAF_PRAGMA_ONCE
#ifndef HAF_TYPES_SCENE_TYPES_INCLUDE_HPP
#define HAF_TYPES_SCENE_TYPES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/rect.hpp>
#include <haf/include/types/scene_types.hpp>

namespace haf
{
using SceneUnit        = htps::f32;
using SceneCoordinates = fmath::vector2d<SceneUnit>;
using SceneBox         = fmath::Rect<SceneUnit>;
using SceneQuad        = fmath::Rect<SceneUnit>;

}  // namespace haf

#endif
