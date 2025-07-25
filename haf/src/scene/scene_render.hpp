HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_INCLUDE_HPP

#include "haf_private.hpp"

namespace haf::scene
{
class SceneNode;
void HAF_PRIVATE render(SceneNode& scene_node);
void HAF_PRIVATE render(SceneNode& scene_node, uint32_t const index);

}  // namespace haf::scene

#endif
