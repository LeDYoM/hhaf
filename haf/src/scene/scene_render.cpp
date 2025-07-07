#include "scene_render.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_container.hpp>

namespace haf::scene
{
void render(SceneNode& scene_node)
{
    if (scene_node.Visible())
    {
        // Update the node components
        scene_node.updateComponents();

        // Render the nodes added to this node
        for (auto&& group : scene_node.sceneNodes())
        {
            render(*group);
        }
    }
}

}  // namespace haf::scene
