#include "scene_walker.hpp"
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_nodes_group.hpp>

using namespace haf::core;

namespace haf::scene
{

void SceneWalker::walk(SceneNode& node)
{
    node.updateComponents();


    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode);
    }
}

}  // namespace haf::scene
