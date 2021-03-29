#ifndef HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/grouping_property.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene_nodes/include/scenenodetext_properties.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>

#include <htypes/include/vector2d.hpp>

namespace haf::scene::nodes
{

class SceneNodeText : public SceneNode, public SceneNodeTextProperties
{
    using BaseClass = SceneNode;

public:
    /**
     * @brief Use SceneNode constructor
     */
    using SceneNode::SceneNode;

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
};
}  // namespace haf::scene::nodes

#endif
