#include "scenenodes.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/include/liblog.hpp>

using namespace mtps;

namespace lib::scene
{
SceneNodes::SceneNodes(const rptr<SceneNode> scene_node) :
    scene_node_{scene_node}
{}

SceneNodes::~SceneNodes() = default;

void SceneNodes::renderGroups(const bool parentTransformationChanged)
{
    scene_nodes_group_.renderGroups(parentTransformationChanged);
}

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
    log_assert(element.get() != nullptr,
               "Received empty scene node to be deleted");
    log_assert(scene_node_ != element.get(),
               "Cannot delete myself from myself");
    log_assert(scene_node_ == element->parent(),
               " You must call removeSceneNode from the parent node");

    scene_nodes_group_.removeSceneNode(std::move(element));
}

void SceneNodes::clearSceneNodes()
{
    scene_nodes_group_.clearSceneNodes();
}
}  // namespace lib::scene
