#pragma once

#ifndef HAF_SCENE_SCENENODE_SIZE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_SIZE_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/grouping_property.hpp>
#include <mtypes/include/rect.hpp>

namespace haf::scene
{
struct NodeSize
{
    using value_type = mtps::Rectf32;
};

using SceneNodeSizeProperties = mtps::PropertyGroup<NodeSize>;
using SceneNodeSizePropertiesContent =
    mtps::PropertyContainer<SceneNodeSizeProperties>;

}  // namespace haf::scene

#endif
