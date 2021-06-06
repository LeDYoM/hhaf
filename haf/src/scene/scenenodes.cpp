#include <haf/include/scene/scenenodes.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
SceneNodes::SceneNodes(const rptr<SceneNode> scene_node) :
    scene_node_{scene_node}
{}

SceneNodes::~SceneNodes() = default;

void SceneNodes::addSceneNode(sptr<SceneNode> node)
{
    scene_nodes_.emplace_back(node);
    node->onCreated();
}

sptr<SceneNode> SceneNodes::getByName(const str& name) const
{
    const auto iterator = sceneNodes().find_if(
        [name](const auto& node) { return node->name() == name; });

    return iterator == sceneNodes().cend() ? nullptr : *iterator;
}

bool SceneNodes::removeSceneNode(sptr<SceneNode> element)
{
    LogAsserter::log_assert(element != nullptr,
                            "Received empty scene node to be deleted");
    LogAsserter::log_assert(scene_node_ != element.get(),
                            "Cannot delete myself from myself");
    LogAsserter::log_assert(
        scene_node_ == element->parent(),
        " You must call removeSceneNode from the parent node");

    auto const old_size = scene_nodes_.size();
    scene_nodes_.erase_one(element);
    return old_size == scene_nodes_.size() + 1U;
}

bool SceneNodes::removeSceneNode(htps::str const& name)
{
    auto node = getByName(name);
    if (node != nullptr)
    {
        return removeSceneNode(std::move(node));
    }
    return false;
}

void SceneNodes::clearSceneNodes()
{
    scene_nodes_.clear();
}

const SceneNodes::SceneNodeVector& SceneNodes::sceneNodes() const noexcept
{
    return scene_nodes_;
}

SceneNodes::SceneNodeVector& SceneNodes::sceneNodes() noexcept
{
    return scene_nodes_;
}

void SceneNodes::for_each_sceneNode(
    htps::function<void(htps::sptr<SceneNode> const&)> action)
{
    std::for_each(sceneNodes().begin(), sceneNodes().end(), action);
}

void SceneNodes::for_each_sceneNode(
    htps::function<void(htps::sptr<SceneNode const> const&)> action) const
{
    std::for_each(sceneNodes().cbegin(), sceneNodes().cend(), action);
}

}  // namespace haf::scene
