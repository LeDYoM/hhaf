#ifndef HAF_SCENE_SCENENODE_SIZE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_SIZE_PROPERTIES_INCLUDE_HPP

#include <haf/include/types/property_group.hpp>
#include <htypes/include/rect.hpp>

namespace haf::scene
{
struct NodeSize : PropertyStateBase<htps::Rectf32> {};

using SceneNodeSizeProperties = types::PropertyGroup<NodeSize>;

}  // namespace haf::scene

#endif
