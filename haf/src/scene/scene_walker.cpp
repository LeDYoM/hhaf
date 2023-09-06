#include "scene_walker.hpp"
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_nodes_group.hpp>
#include <haf/include/component/component.hpp>

using namespace haf::core;
using namespace haf::component;

namespace haf::scene
{

void SceneWalker::walk(SceneNode& node)
{
    node.componentContainer().updateComponents();

    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode);
    }
}

}  // namespace haf::scene
