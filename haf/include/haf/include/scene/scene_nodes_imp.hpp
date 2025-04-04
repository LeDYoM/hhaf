HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODES_IMPLEMENTATION_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODES_IMPLEMENTATION_INCLUDE_HPP

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_nodes.hpp>

namespace haf::scene
{
template <typename T>
bool SceneNodes::removeSceneNodesWithComponent<T>()
{
    SceneNodeVector scnNodeVector;
    for_each_sceneNode([](htps::sptr<SceneNode> const& element) {
        if (element->template componentOfType<T>() != nullptr)
        {
            scnNodeVector.push_back(element);
        }
    });
    removeSceneNodes(scnNodeVector);
}

}  // namespace haf::scene

#endif
