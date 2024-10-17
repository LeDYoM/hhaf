#include "scene_render.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/transformable_component.hpp>

using namespace htps;

namespace haf::scene
{
void render(SceneNode& scene_node, SceneRenderContext scene_render_context)
{
    if (scene_node.Visible())
    {
        // Update the node components
        /*
        auto const& transformable_component{
            scene_node.componentOfType<TransformableComponent>()};
        if (transformable_component != nullptr)
        {
            transformable_component->setSceneRenderContext(
                scene_render_context);
        }
        */
        scene_node.updateComponents();
        scene_node.update();
        scene_node.postRender(scene_render_context);

        // Render the nodes added to this node
        for (auto& group : scene_node.sceneNodes())
        {
            render(*group, scene_render_context);
        }
    }
}

void render(Scene& scene, SceneRenderContext scene_render_context)
{
    render(static_cast<SceneNode&>(scene), scene_render_context);
}

}  // namespace haf::scene
