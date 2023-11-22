#include <haf/include/scene/scene_node.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf::core;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str_view name) :
    sys::HasName{str{name}},
    SceneNodeParent{parent},
    sys::SystemAccess{&(parent->isystemProvider())},
    sys::SubSystemViewer{&isystemProvider()},
    m_component_container{this},
    m_scene_nodes_group{this}
{}

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    SceneNode{parent, str_view{name.c_str()}}
{}

SceneNode::SceneNode(rptr<sys::ISystemProvider> isystem_provider) :
    sys::HasName{"global"},
    SceneNodeParent{nullptr},
    sys::SystemAccess{isystem_provider},
    sys::SubSystemViewer{isystem_provider},
    m_component_container{this},
    m_scene_nodes_group{this}
{}

SceneNode::~SceneNode()
{
    logger::DisplayLog::debug(StaticTypeName, ": ", name(), ": Destroying");
    m_component_container.clearComponents();
}

str SceneNode::completeName() const
{
    auto const p{parent()};
    return (p == nullptr ? "" : p->completeName() + "::") + name();
}

}  // namespace haf::scene
