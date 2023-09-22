#include "scene_walker.hpp"
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_nodes_group.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/scene/scene_update_time.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{
void SceneWalker::startWalk(SceneNode& rootNode)
{
    using scene::num_begin;
    using scene::num_end;
    using scene::SceneUpdateTime;
    using scene::toEnum;
    for (auto i{num_begin<SceneUpdateTime>()}; i < num_end<SceneUpdateTime>();
         ++i)
    {
        walk(rootNode, toEnum<SceneUpdateTime>(i));
    }
}

void SceneWalker::walk(SceneNode& node)
{
//    node.componentContainer().updateComponents();

    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode);
    }
}

void SceneWalker::walk(SceneNode& node, SceneUpdateTime const sceneUpdateTime)
{
    node.componentContainer().updateComponents(sceneUpdateTime);

    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode, sceneUpdateTime);
    }
}

}  // namespace haf::scene
