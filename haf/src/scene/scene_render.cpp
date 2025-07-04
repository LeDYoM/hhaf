#include "scene_render.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;

namespace haf::scene
{
void render(SceneNode& scene_node, SceneRenderContext scene_render_context)
{
    if (scene_node.Visible())
    {
        // Update the node components
        scene_node.updateComponents();

        // Render the nodes added to this node
        for (auto& group : scene_node.sceneNodes())
        {
            render(*group, scene_render_context);
        }
    }
}
/*
void render(Scene& scene, SceneRenderContext scene_render_context)
{
    render(static_cast<SceneNode&>(scene), scene_render_context);
}
*/

}  // namespace haf::scene
