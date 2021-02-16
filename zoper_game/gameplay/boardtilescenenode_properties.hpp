#ifndef ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/grouping_property.hpp>
#include <haf/scene/include/color.hpp>

namespace zoper
{
struct BackgroundColor
{
    using value_type = haf::scene::Color;
};

using BoardTileSceneNodeProperties = mtps::PropertyGroup<BackgroundColor>;


}  // namespace zoper

#endif