#include <haf/include/scene/scene_node.hpp>

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
    sys::DataWrapperCreator{this},
    sys::SubSystemViewer{parent != nullptr ? &(parent->isystemProvider())
                                           : nullptr}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
}

}  // namespace haf::scene
