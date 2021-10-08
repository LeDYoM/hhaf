#ifndef ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <haf/include/types/property_group.hpp>
#include <haf/include/scene/color.hpp>

namespace zoper
{
struct BackgroundColor
{
    using value_type = haf::scene::Color;
};

using BoardTileSceneNodeProperties = haf::types::PropertyGroup<BackgroundColor>;

}  // namespace zoper

#endif