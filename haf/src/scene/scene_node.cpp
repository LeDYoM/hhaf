#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_components/camera_component.hpp>

using namespace htps;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{htps::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
//    SceneNodeProperties(true),
    component::ComponentContainer{this},
    sys::SubSystemViewer{&isystemProvider()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::update()
{}

void SceneNode::postUpdate(SceneRenderContext& /*sceneRenderContext*/)
{
}

void SceneNode::clearAll()
{
    clearSceneNodes();
}

SceneBox SceneNode::sceneView() const
{
    return sceneParent()->cameraComponent()->view();
}

SceneBox::vector_t SceneNode::sceneViewSize() const
{
    return sceneView().size();
}

rptr<Scene> SceneNode::sceneParent()
{
    return ancestor<Scene>();
}

rptr<Scene const> SceneNode::sceneParent() const
{
    return cancestor<Scene>();
}

}  // namespace haf::scene
