#include "scenenodes.hpp"
#include "scenenode.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::scene
{
void SceneNodesGroup::addSceneNode(sptr<SceneNode> node)
{
    groups_.push_back(node);
}

void SceneNodesGroup::removeSceneNode(sptr<SceneNode> element)
{
    groups_.erase_values(element);
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
