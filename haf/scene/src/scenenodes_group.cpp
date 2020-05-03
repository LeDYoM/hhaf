#include "scenenodes.hpp"
#include "scenenode.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::scene
{
void SceneNodesGroup::addSceneNode(sptr<SceneNode> node)
{
    m_groups.push_back(node);
}

void SceneNodesGroup::removeSceneNode(sptr<SceneNode> element)
{
    m_groups.erase_values(element);
}

void SceneNodesGroup::clearSceneNodes()
{
    m_groups.clear();
}

const SceneNodesGroup::SceneNodeVector& SceneNodesGroup::sceneNodes()
    const noexcept
{
    return m_groups;
}

SceneNodesGroup::SceneNodeVector& SceneNodesGroup::sceneNodes() noexcept
{
    return m_groups;
}

}  // namespace haf::scene
