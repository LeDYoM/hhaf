#ifndef HAF_SCENE_SCENE_RENDER_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::scene
{
class Scene;
class SceneNode;

void render(Scene& scene, bool const parent_transformation_changed);
void render(SceneNode& scene_node, bool parent_transformation_changed);

}  // namespace haf::scene

#endif
