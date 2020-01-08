#include "scenenode.hpp"
#include "scene.hpp"

#include <lib/scene/renderizables/renderizable.hpp>

#include <lib/include/liblog.hpp>

#include <lib/system/scenemanager.hpp>
#include "scenenodeblob.hpp"

namespace lib::scene
{
SceneNode::SceneNode(SceneNode *const parent, str name)
    : core::HasName{std::move(name)}, DataWrapperCreator{this},
      ComponentContainer{this}, SceneNodeBlob{*this},
      visible{true}, m_parent{parent}
{
}

SceneNode::~SceneNode() = default;

void SceneNode::render(bool parentTransformationChanged)
{
    if (visible())
    {
        // Update the node components
        updateComponents();

        // Update node
        update();

        bool local_transformation_needs_update{transformationNeedsUpdate()};

        if (parentTransformationChanged | local_transformation_needs_update)
        {
            updateGlobalTransformation(
                local_transformation_needs_update,
                m_parent ? m_parent->globalTransform() : Transform::Identity);
        }

        postUpdateComponents();
        for (auto &&group : m_groups)
        {
            group->render(parentTransformationChanged |
                          local_transformation_needs_update);
        }
    }
}

bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
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

sptr<SceneNode> SceneNode::createSceneNode(str name)
{
    return createSceneNode<SceneNode>(std::move(name));
}

void SceneNode::addSceneNode(sptr<SceneNode> node)
{
    m_groups.push_back(node);
    node->m_parent = this;
    node->onCreated();
}

sptr<SceneNode> SceneNode::groupByName(const str& name) const
{
    const auto iterator = sceneNodes().find_if([name](const auto& node)
    {
        return node->name() == name;
    });

    return iterator == sceneNodes().cend() ? nullptr : *iterator;
}

void SceneNode::removeSceneNode(sptr<SceneNode> element)
{
    log_assert(element.get() != nullptr, "Received empty scene node to be deleted");
    log_assert(this != element.get(), "Cannot delete myself from myself");
    log_assert(this == element->parent(), " You must call removeSceneNode from the parent node");

    m_groups.erase_values(element);
}

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

void SceneNode::clearSceneNodes()
{
    m_groups.clear();
}
} // namespace lib::scene
