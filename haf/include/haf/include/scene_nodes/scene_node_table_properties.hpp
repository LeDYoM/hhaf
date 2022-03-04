#ifndef HAF_SCENE_NODE_TABLE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODE_TABLE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/property_group.hpp>

namespace haf::scene
{
struct SceneNodeSize : PropertyStateBase<htps::vector2df>
{};
struct TableSize : PropertyStateBase<htps::vector2dst>
{};
struct TableSizeForNodes : PropertyStateBase<htps::vector2df>
{};

using TableNodeProperties =
    types::PropertyGroup<TableSize, SceneNodeSize, TableSizeForNodes>;

}  // namespace haf::scene

#endif
