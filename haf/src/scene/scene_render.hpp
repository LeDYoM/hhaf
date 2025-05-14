HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_RENDER_INCLUDE_HPP
#define HAF_SCENE_SCENE_RENDER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "haf_private.hpp"
#include <haf/include/scene/scene_render_context.hpp>

namespace haf::scene
{
class Scene;
class SceneNode;

// void HAF_PRIVATE render(Scene& scene, SceneRenderContext
// scene_render_context);
void HAF_PRIVATE render(SceneNode& scene_node,
                        SceneRenderContext scene_render_context);

template<typename T>
void HAF_PRIVATE subsystemUpdateNode(T& subsystem, SceneNode& node)
{
    subsystem.updateNode(node);
}

}  // namespace haf::scene

#endif
