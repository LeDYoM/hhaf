#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_components/camera_component.hpp>

using namespace htps;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    SceneNodeProperties(true),
    component::ComponentContainer{this},
    sys::SubSystemViewer{&isystemProvider()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
}

SceneBox SceneNode::sceneView() const
{
    return ancestor<Scene>()->cameraComponent()->view();
}

SceneBox::vector_t SceneNode::sceneViewSize() const
{
    return sceneView().size();
}

}  // namespace haf::scene
