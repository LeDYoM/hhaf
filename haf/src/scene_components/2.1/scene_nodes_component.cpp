#include <haf/include/scene_components/2.1/scene_nodes_component.hpp>
#include <haf/include/component/component_definition.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{
SceneNodeSPtr SceneNodesComponent::createSceneNode(str_view name)
{
    sptr<SceneNode> result{msptr<SceneNode>(attachedNode(), str{name})};
    addSceneNode(result);
    return result;
}

sptr<Component> SceneNodesComponent::createSceneNodeWithComponent(
    str_view name,
    str_view componentName)
{
    SceneNodeSPtr sceneNode{createSceneNode(name)};
    LogAsserter::log_assert(sceneNode != nullptr, "Invalid nullptr parameter");
    if (sceneNode != nullptr)
    {
        auto component{sceneNode->attachComponent(core::move(componentName))};

        return component;
    }

    removeSceneNode(name);
    return nullptr;
}

bool SceneNodesComponent::removeSceneNode(str_view name)
{
    sptr<SceneNode> scene_node{getByName(name)};
    if (scene_node != nullptr)
    {
        return removeSceneNode(scene_node);
    }
    return false;
}

bool SceneNodesComponent::removeSceneNode(SceneNodeSPtr sceneNode)
{
    LogAsserter::log_assert(sceneNode != nullptr,
                            "Received empty scene node to be deleted");

    auto const old_size{m_scene_nodes.size()};
    m_scene_nodes.erase_one<false>(sceneNode);
    bool const result{old_size == (m_scene_nodes.size() + 1U)};
    if (result)
    {
        onNodeRemoved(sceneNode);
    }
    return result;
}

bool SceneNodesComponent::removeSceneNode(size_type const index)
{
    auto sceneNode{getByIndex(index)};
    if (sceneNode)
    {
        return removeSceneNode(sceneNode);
    }
    return false;
}

SceneNodeSPtr SceneNodesComponent::getByName(str_view name)
{
    auto const iterator{m_scene_nodes.find_if(
        [&name](auto const& node) { return node->name() == name; })};

    return iterator == m_scene_nodes.cend() ? nullptr : *iterator;
}

SceneNodeSPtr SceneNodesComponent::getByIndex(size_type const index)
{
    if (index < m_scene_nodes.size())
    {
        return m_scene_nodes[index];
    }
    return nullptr;
}

void SceneNodesComponent::forEach(
    core::function<void(SceneNodeSPtr const&)> f) const
{
    for (SceneNodeSPtr const& node : m_scene_nodes)
    {
        f(node);
    }
}

size_type SceneNodesComponent::size() const noexcept
{
    return m_scene_nodes.size();
}

bool SceneNodesComponent::empty() const noexcept
{
    return m_scene_nodes.empty();
}

void SceneNodesComponent::addSceneNode(core::sptr<SceneNode>& node)
{
    m_scene_nodes.emplace_back(node);
    node->onCreated();
    onNodeAdded(node);
}

pair<size_type, bool> SceneNodesComponent::getIndex(
    SceneNodeSPtr const& sceneNode)
{
    auto const iterator{m_scene_nodes.cfind(sceneNode)};
    return {static_cast<size_type>(iterator - m_scene_nodes.cbegin()),
            iterator != m_scene_nodes.cend()};
}

void SceneNodesComponent::onAttached()
{
    addUpdater({this, &SceneNodesComponent::updateNodes});
}

void SceneNodesComponent::updateNodes()
{
    for (const auto& node : m_scene_nodes)
    {
        node->updateComponents();
    }
}

}  // namespace haf::scene
