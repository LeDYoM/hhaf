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

namespace haf::scene::nodes
{

class SceneNodeText : public SceneNode, public SceneNodeTextProperties
{
    using BaseClass = SceneNode;

public:
    using SceneNode::SceneNode;
    using SceneNode::prop;
    using SceneNodeTextProperties::prop;

protected:
    void update() override final;

private:
    void updateAlignmentX(htps::f32 const textSizeX);
    void updateAlignmentY(htps::f32 const textSizeY);
};
}  // namespace haf::scene::nodes

#endif
