#include "scene_walker.hpp"
#include "scene_subsystems/scene_manager subsystem_group.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_nodes_group.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{
void SceneWalker::startWalk(
    SceneNode& rootNode,
    SceneManagerSubSystemGroup& sceneManagerSubSystemGroup)
{
    for (auto&& sub_systen : sceneManagerSubSystemGroup.subsystems())
    {
        walk(rootNode, *sub_systen);
    }
}

void SceneWalker::walk(SceneNode& node,
                       ISceneManagerSubSystem& iSceneManagerSubSystem)
{
    node.componentContainer().updateComponents(iSceneManagerSubSystem);

    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode, iSceneManagerSubSystem);
    }
}

}  // namespace haf::scene
