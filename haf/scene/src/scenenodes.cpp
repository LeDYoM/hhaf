#include "scenenodes.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::scene
{
SceneNodes::SceneNodes(const rptr<SceneNode> scene_node) :
    scene_node_{scene_node}
{}

SceneNodes::~SceneNodes() = default;

void SceneNodes::addSceneNode(sptr<SceneNode> node)
{
    scene_nodes_group_.addSceneNode(node);
    node->onCreated();
}

sptr<SceneNode> SceneNodes::groupByName(const str& name) const
{
    const auto iterator = sceneNodes().find_if(
        [name](const auto& node) { return node->name() == name; });

    return iterator == sceneNodes().cend() ? nullptr : *iterator;
}

void SceneNodes::removeSceneNode(sptr<SceneNode> element)
{
    LogAsserter::log_assert(element.get() != nullptr,
                            "Received empty scene node to be deleted");
    LogAsserter::log_assert(scene_node_ != element.get(),
                            "Cannot delete myself from myself");
    LogAsserter::log_assert(
        scene_node_ == element->parent(),
        " You must call removeSceneNode from the parent node");

    scene_nodes_group_.removeSceneNode(std::move(element));
}

void SceneNodes::clearSceneNodes()
{
    scene_nodes_group_.clearSceneNodes();
}

const SceneNodesGroup::SceneNodeVector& SceneNodes::sceneNodes() const noexcept
{
    return scene_nodes_group_.sceneNodes();
}

SceneNodesGroup::SceneNodeVector& SceneNodes::sceneNodes() noexcept
{
    return scene_nodes_group_.sceneNodes();
}

}  // namespace haf::scene
