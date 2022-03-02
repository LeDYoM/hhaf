#ifndef HAF_SCENE_NODES_SCENE_NODE_TEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENE_NODE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/scene_nodes/scene_node_text_properties.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>

namespace haf::scene::nodes
{

class SceneNodeText : public TransformableSceneNode,
                      public SceneNodeTextProperties
{
    using BaseClass = TransformableSceneNode;

public:
    /**
     * @brief Constructor
     */
    SceneNodeText(types::rptr<SceneNode> parent, htps::str name);

    void onCreated() override;

    /**
     * @brief Expose TransformableSceneNode properties
     */
    using TransformableSceneNode::prop;

    /**
     * @brief Expose Text properties
     */
    using SceneNodeTextProperties::prop;

    void setBaseScaleForCurrentView();

protected:
    void update() override final;
    types::size_type inner_transformation_;
};

}  // namespace haf::scene::nodes

#endif
