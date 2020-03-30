#include "scenenodes.hpp"
#include "scenenode.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/include/liblog.hpp>

namespace lib::scene
{

void SceneNodesGroup::renderGroups(const bool parentTransformationChanged)
{
    for (auto&& group : m_groups)
    {
        group->render(parentTransformationChanged);
    }
}

void SceneNodesGroup::addSceneNode(mtps::sptr<SceneNode> node)
{
    m_groups.push_back(node);
}

void SceneNodesGroup::removeSceneNode(mtps::sptr<SceneNode> element)
{
    m_groups.erase_values(element);
}

void SceneNodesGroup::clearSceneNodes()
{
    m_groups.clear();
}
}  // namespace lib::scene
