#include <haf/include/scene_nodes/renderizables_scene_node.hpp>

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

RenderizablesSceneNode::RenderizablesSceneNode(rptr<SceneNode> parent,
                                               str name) :
    SceneNodeBaseClass{parent, std::move(name)}, render::Renderizables{this}
{}

void RenderizablesSceneNode::postUpdate(SceneRenderContext& sceneRenderContext)
{
    SceneNodeBaseClass::postUpdate(sceneRenderContext);
    Renderizables::updateRenderizables(
        sceneRenderContext.parentTransformationChanged_);
}

}  // namespace haf::scene
