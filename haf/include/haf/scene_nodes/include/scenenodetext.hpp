#pragma once

#ifndef HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP
#define HAF_SCENE_NODES_SCENENODETEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/grouping_property.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene_nodes/include/scenenodetext_properties.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>

namespace haf::scene::nodes
{

class SceneNodeText : public SceneNode, public SceneNodeTextPropertiesContent
{
    using BaseClass = SceneNode;

public:
    using SceneNode::SceneNode;
    using SceneNodeTextPropertiesContent::prop;
    ~SceneNodeText() override;

protected:
    void update() override final;

private:
    void updateAlignmentX(mtps::f32 const textSizeX);
    void updateAlignmentY(mtps::f32 const textSizeY);
};
}  // namespace haf::scene::nodes

#endif
