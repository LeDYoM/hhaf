#ifndef HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/scene_nodes/include/scenenodetext_properties.hpp>
#include <haf/scene/include/scenenode.hpp>

namespace haf::scene::nodes
{

class SceneNodeText : public SceneNode, public SceneNodeTextProperties
{
    using BaseClass = SceneNode;

public:
    /**
     * @brief Constructor
     */
    SceneNodeText(htps::rptr<SceneNode> parent, htps::str name);

    /**
     * @brief Expose SceneNode properties
     */
    using SceneNode::prop;

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
