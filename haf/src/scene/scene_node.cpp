#include <haf/include/scene/scene_node.hpp>

#include <haf/include/scene/scene.hpp>

using namespace haf::types;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    uptr<sys::DataWrapperCreator> subsystems_;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{std::move(parent)},
    SceneNodes{this},
    sys::SystemAccess{ancestor<Scene>() != nullptr
                          ? &(ancestor<Scene>()->isystemProvider())
                          : nullptr},
    SceneNodeProperties(true),
    component::ComponentContainer{this},
    sys::DataWrapperCreator{this},
    sys::SubSystemViewer{this},
    p_{make_pimplp<SceneNodePrivate>()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
}

}  // namespace haf::scene
