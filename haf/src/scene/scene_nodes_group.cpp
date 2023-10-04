#include <haf/include/scene/scene_nodes_group.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{
SceneNodesGroup::SceneNodesGroup(core::rptr<SceneNode> sceneNode) :
    m_scene_node{sceneNode}
{}

SceneNodeSPtr SceneNodesGroup::createSceneNode(str_view name)
{
    sptr<SceneNode> result{msptr<SceneNode>(m_scene_node, str{name})};
    addSceneNode(result);
    return result;
}

bool SceneNodesGroup::removeSceneNode(str_view name)
{
    sptr<SceneNode> scene_node{getByName(name)};
    if (scene_node != nullptr)
    {
        return removeSceneNode(scene_node);
    }
    return false;
}

bool SceneNodesGroup::removeSceneNode(SceneNodeSPtr sceneNode)
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

bool SceneNodesGroup::removeSceneNode(size_type const index)
{
    auto sceneNode{getByIndex(index)};
    if (sceneNode)
    {
        return removeSceneNode(sceneNode);
    }
    return false;
}

SceneNodeSPtr SceneNodesGroup::getByName(str_view name)
{
    auto const iterator{m_scene_nodes.find_if(
        [&name](auto const& node) { return node->name() == name; })};

    return iterator == m_scene_nodes.cend() ? nullptr : *iterator;
}

SceneNodeSPtr SceneNodesGroup::getByIndex(size_type const index)
{
    if (index < m_scene_nodes.size())
    {
        return m_scene_nodes[index];
    }
    return nullptr;
}

SceneNodesGroup::SceneNodesVector const& SceneNodesGroup::sceneNodes() const
{
    return m_scene_nodes;
}

size_type SceneNodesGroup::size() const noexcept
{
    return m_scene_nodes.size();
}

bool SceneNodesGroup::empty() const noexcept
{
    return m_scene_nodes.empty();
}

void SceneNodesGroup::addSceneNode(core::sptr<SceneNode>& node)
{
    m_scene_nodes.emplace_back(node);
    node->onCreated();
    onNodeAdded(node);
}

pair<size_type, bool> SceneNodesGroup::getIndex(SceneNodeSPtr const& sceneNode)
{
    auto const iterator{m_scene_nodes.cfind(sceneNode)};
    return {static_cast<size_type>(iterator - m_scene_nodes.cbegin()),
            iterator != m_scene_nodes.cend()};
}

}  // namespace haf::scene
