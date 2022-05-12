HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODE_TABLE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_NODE_TABLE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/property_group.hpp>

namespace haf::scene
{
struct TableSize : htps::PropertyStateBase<htps::vector2dst>
{};
struct TableSizeForNodes : htps::PropertyStateBase<htps::vector2df>
{};

using TableNodeProperties = htps::PropertyGroup<TableSize, TableSizeForNodes>;

}  // namespace haf::scene

#endif
