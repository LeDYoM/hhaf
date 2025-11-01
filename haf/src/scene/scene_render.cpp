#include "scene_render.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_container.hpp>

namespace haf::scene
{
void processUnorderedComponents(SceneNode& scene_node)
{
    if (scene_node.Visible())
    {
        // Update the node components
        scene_node.updateUnorderedComponents();

        // Render the nodes added to this node
        for (auto&& group : scene_node.sceneNodes())
        {
            processUnorderedComponents(*group);
        }
    }
}

void processOrderedComponents(SceneNode& scene_node, core::u32 const index)
{
    if (scene_node.Visible())
    {
        // Update the node components
        scene_node.updateIndexedComponent(index);

        // Render the nodes added to this node
        for (auto&& group : scene_node.sceneNodes())
        {
            processOrderedComponents(*group, index);
        }
    }
}

}  // namespace haf::scene
