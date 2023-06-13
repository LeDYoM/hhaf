#include <haf/include/scene/scene_node.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf::core;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str_view name) :
    sys::HasName{str{name}},
    SceneNodeParent{parent},
    sys::SystemAccess{&(parent->isystemProvider())},
    component::ComponentContainer{this},
    sys::SubSystemViewer{&isystemProvider()},
    SceneNodesGroup{this}
{}

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    SceneNode{parent, str_view{name.c_str()}}
{}

SceneNode::SceneNode(rptr<sys::ISystemProvider> isystem_provider) :
    sys::HasName{"global"},
    SceneNodeParent{nullptr},
    sys::SystemAccess{isystem_provider},
    component::ComponentContainer{this},
    sys::SubSystemViewer{isystem_provider},
    SceneNodesGroup{this}
{}

SceneNode::~SceneNode()
{
    DisplayLog::debug(StaticTypeName, ": ", name(), ": Destroying");
    component::ComponentContainer::clearComponents();
}

void SceneNode::update()
{
    ComponentContainer::updateComponents();
    SceneNodesGroup::updateNodes();
}

str SceneNode::completeName() const
{
    auto const p{parent()};
    return (p == nullptr ? "" : p->completeName() + "::") + name();
}

}  // namespace haf::scene
