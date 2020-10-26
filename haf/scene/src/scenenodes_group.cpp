#include <haf/scene/include/scenenodes.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::scene
{
void SceneNodesGroup::addSceneNode(sptr<SceneNode> node)
{
    groups_.push_back(node);
}

bool SceneNodesGroup::removeSceneNode(sptr<SceneNode> element)
{
    auto const old_size = groups_.size();
    groups_.erase_one(element);
    return old_size == groups_.size() + 1U;
}

void SceneNodesGroup::clearSceneNodes()
{
    groups_.clear();
}

const SceneNodesGroup::SceneNodeVector& SceneNodesGroup::sceneNodes()
    const noexcept
{
    return groups_;
}

SceneNodesGroup::SceneNodeVector& SceneNodesGroup::sceneNodes() noexcept
{
    return groups_;
}

}  // namespace haf::scene
