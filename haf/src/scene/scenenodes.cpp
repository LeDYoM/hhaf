#include <haf/include/scene/scenenodes.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
SceneNodes::SceneNodes(rptr<SceneNode> const scene_node) :
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
    auto const iterator{sceneNodes().find_if(
        [&name](auto const& node) { return node->name() == name; })};

    return iterator == sceneNodes().cend() ? nullptr : *iterator;
}

htps::sptr<SceneNode> SceneNodes::getShared(
    htps::rptr<SceneNode> node = nullptr) const
{
    if (node == nullptr)
    {
        node = scene_node_;
    }

    auto const iterator = sceneNodes().find_if(
        [&node](auto const& rhs_node) { return node == rhs_node.get(); });

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

    auto const old_size{scene_nodes_.size()};
    scene_nodes_.erase_one(element);
    return old_size == (scene_nodes_.size() + 1U);
}

bool SceneNodes::removeSceneNode(htps::str const& name)
{
    if (auto node{getByName(name)}; node != nullptr)
    {
        return removeSceneNode(std::move(node));
    }
    return false;
}

bool SceneNodes::autoRemove()
{
    auto this_parent{scene_node_->parentAs<SceneNode>()};
    LogAsserter::log_assert(this_parent != nullptr,
                            "Error removing a node without parent");
    auto this_shared = this_parent->getShared(scene_node_);
    LogAsserter::log_assert(this_shared != nullptr,
                            "Cannot find this node on the parent");
    return this_parent->removeSceneNode(std::move(this_shared));
}

void SceneNodes::clearSceneNodes()
{
    scene_nodes_.clear();
}

SceneNodes::SceneNodeVector const& SceneNodes::sceneNodes() const noexcept
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
    std::for_each(sceneNodes().cbegin(), sceneNodes().cend(), action);
}

void SceneNodes::for_each_sceneNode(
    htps::function<void(htps::sptr<SceneNode const> const&)> action) const
{
    std::for_each(sceneNodes().cbegin(), sceneNodes().cend(), action);
}

}  // namespace haf::scene
