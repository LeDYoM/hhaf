#ifndef HAF_SCENE_NODES_SCENE_NODE_LETTER_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENE_NODE_LETTER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>

namespace haf::scene::nodes
{
class SceneNodeLetter : public RenderizableSceneNode
{
    using BaseClass = RenderizableSceneNode;

public:
    using BaseClass::BaseClass;

    /**
     * @brief Expose TransformableSceneNode properties
     */
    using TransformableSceneNode::prop;
};

}  // namespace haf::scene::nodes

#endif
