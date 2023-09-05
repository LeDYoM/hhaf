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
    if (!node.componentContainer().components().empty())
    {
        auto current{node.componentContainer().components().end()};
        while (current-- != node.componentContainer().components().begin())
        {
            walkComponent(**current);
        }
    }

    for (sptr<SceneNode> const& sceneNode : node.sceneNodesGroup())
    {
        walk(*sceneNode);
    }
}

void SceneWalker::walkComponent(Component& component)
{
    component.updateComponent();
}

}  // namespace haf::scene
