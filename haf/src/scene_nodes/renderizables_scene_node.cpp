#include <haf/include/scene_nodes/renderizables_scene_node.hpp>

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

RenderizablesSceneNode::RenderizablesSceneNode(rptr<SceneNode> parent,
                                               str name) :
    SceneNodeBaseClass{parent, htps::move(name)}, renderizables_{this}
{}

void RenderizablesSceneNode::postRender(SceneRenderContext& sceneRenderContext)
{
    SceneNodeBaseClass::postRender(sceneRenderContext);
    renderizables_.updateRenderizables(
        sceneRenderContext.parentTransformationChanged_);
}

}  // namespace haf::scene
