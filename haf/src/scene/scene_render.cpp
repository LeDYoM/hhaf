#include "scene_render.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/renderizables_scene_node.hpp>
#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;

namespace haf::scene
{
void render(SceneNode& scene_node, SceneRenderContext scene_render_context)
{
    if (scene_node.prop<Visible>().get())
    {
        // Update the node components
        scene_node.updateComponents();
        scene_node.update();

        // Update the transformation (local and global)
        if (auto* const transformable_scene_node =
                dynamic_cast<TransformableSceneNode*>(&scene_node);
            transformable_scene_node != nullptr)
        {
            scene_render_context.parentTransformationChanged_ =
                transformable_scene_node->updateTransformations(
                    scene_render_context.parentTransformationChanged_,
                    scene_node.parentAs<TransformableSceneNode>()
                        ? scene_node.parentAs<TransformableSceneNode>()
                              ->globalTransform()
                        : Matrix4x4::Identity);
        }

        // Update the renderizables added to this node
        if (auto* const renderizable_scene_node{
                dynamic_cast<RenderizablesSceneNode*>(&scene_node)};
            renderizable_scene_node != nullptr)
        {
            renderizable_scene_node->updateRenderizables(
                scene_render_context.parentTransformationChanged_);
        }

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
