HTPS_PRAGMA_ONCE
#ifndef HAF_TYPES_SCENE_TYPES_INCLUDE_HPP
#define HAF_TYPES_SCENE_TYPES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <haf/include/types/scene_types.hpp>

namespace haf
{
using SceneUnit        = htps::f32;
using SceneCoordinates = htps::vector2d<SceneUnit>;
using SceneBox         = htps::Rect<SceneUnit>;
using SceneQuad        = htps::Rect<SceneUnit>;

}  // namespace haf

#endif
