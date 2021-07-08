#ifndef HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/include/scene_nodes/scenenodetext_properties.hpp>
#include <haf/include/scene/transformable_scenenode.hpp>

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
    SceneNodeText(htps::rptr<SceneNode> parent, htps::str name);

    /**
     * @brief Expose TransformableSceneNode properties
     */
    using TransformableSceneNode::prop;

    /**
     * @brief Expose Text properties
     */
    using SceneNodeTextProperties::prop;

protected:
    void update() override final;
    htps::size_type inner_transformation_;
};
}  // namespace haf::scene::nodes

#endif
