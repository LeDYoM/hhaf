#include "scenenodes.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/include/liblog.hpp>

namespace lib::scene
{
SceneNodes::SceneNodes(const mtps::rptr<SceneNode> attached)
    : attached_{attached}
{
}

SceneNodes::~SceneNodes() = default;

void SceneNodes::renderGroups(const bool parentTransformationChanged)
{
    for (auto &&group : m_groups)
    {
        group->render(parentTransformationChanged);
    }
}

bool SceneNodes::moveLastBeforeNode(const mtps::sptr<SceneNode> &beforeNode)
{
    log_assert(!m_groups.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
    if (!beforeNode)
        return false;

    // Find the node to swap before to
    auto iterator(std::find(m_groups.begin(), m_groups.end(), beforeNode));

    // If beforeNode not found, nothing to do
    if (iterator == m_groups.end())
        return false;

    // If beforeNode is the last element, nothing to do
    if (iterator == std::prev(m_groups.end()))
        return false;

    auto last(std::prev(m_groups.end()));

    // Do not swap yourself
    if (*iterator == *last)
        return false;

    // Swap the iterators
    std::swap(*iterator, *last);
    return true;
}

mtps::sptr<SceneNode> SceneNodes::createSceneNode(mtps::str name)
{
    return createSceneNode<SceneNode>(std::move(name));
}

void SceneNodes::addSceneNode(mtps::sptr<SceneNode> node)
{
    m_groups.push_back(node);
    node->onCreated();
}

mtps::sptr<SceneNode> SceneNodes::groupByName(const mtps::str& name) const
{
    const auto iterator = sceneNodes().find_if([name](const auto& node)
    {
        return node->name() == name;
    });

    return iterator == sceneNodes().cend() ? nullptr : *iterator;
}

void SceneNodes::removeSceneNode(mtps::sptr<SceneNode> element)
{
    log_assert(element.get() != nullptr, "Received empty scene node to be deleted");
    log_assert(attached_ != element.get(), "Cannot delete myself from myself");
    log_assert(attached_ == element->parent(), " You must call removeSceneNode from the parent node");

    m_groups.erase_values(element);
}

void SceneNodes::clearSceneNodes()
{
    m_groups.clear();
}
} // namespace lib::scene
