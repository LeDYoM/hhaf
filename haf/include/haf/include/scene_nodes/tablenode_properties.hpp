#ifndef HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/property_group.hpp>

namespace haf::scene
{
struct SceneNodeSize : PropertyStateBase<htps::vector2df> {};
struct TableSize : PropertyStateBase<htps::vector2dst> {};

using TableNodeProperties = types::PropertyGroup<TableSize, SceneNodeSize>;

}  // namespace haf::scene

#endif
