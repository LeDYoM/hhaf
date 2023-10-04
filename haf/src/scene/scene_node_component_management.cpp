#include <haf/include/scene/scene_node_component_management.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{
SceneNodeComponentManagerment::SceneNodeComponentManagerment(
    sptr<SceneNode> scene_node) noexcept :
    m_scene_node{*scene_node}
{}

SceneNodeComponentManagerment::SceneNodeComponentManagerment(
    rptr<SceneNode> scene_node) noexcept :
    m_scene_node{*scene_node}
{}

SceneNodeComponentManagerment::SceneNodeComponentManagerment(
    SceneNode& scene_node) noexcept :
    m_scene_node{scene_node}
{}

pair<SceneNodeSPtr, sptr<component::Component>>
SceneNodeComponentManagerment::createSceneNodeWithComponent(
    str_view name,
    str_view componentName)
{
    SceneNodeSPtr sceneNode{
        m_scene_node.sceneNodesGroup().createSceneNode(name)};
    LogAsserter::log_assert(sceneNode != nullptr, "Invalid nullptr parameter");
    if (sceneNode != nullptr)
    {
        auto component{sceneNode->componentContainer().attachComponent(
            core::move(componentName))};

        return {sceneNode, component};
    }

    m_scene_node.sceneNodesGroup().removeSceneNode(name);
    return {nullptr, nullptr};
}

}  // namespace haf::scene
