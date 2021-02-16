#ifndef HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/grouping_property.hpp>

namespace haf::scene
{
struct SceneNodeSize
{
    using value_type = mtps::vector2df;
};

struct TableSize
{
    using value_type = mtps::vector2dst;
};

using TableNodeProperties = mtps::PropertyGroup<TableSize, SceneNodeSize>;

}  // namespace haf::scene

#endif
