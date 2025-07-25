HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_INCLUDE_HPP

#include "haf_private.hpp"

#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneNode;
void HAF_PRIVATE render(SceneNode& scene_node);
void HAF_PRIVATE render(SceneNode& scene_node, core::u32 const index);

}  // namespace haf::scene

#endif
