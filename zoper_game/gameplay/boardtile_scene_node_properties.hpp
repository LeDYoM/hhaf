#ifndef ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/property_group.hpp>
#include <haf/include/scene/color.hpp>

namespace zoper
{
struct BackgroundColor : htps::PropertyStateBase<haf::scene::Color> {};

using BoardTileSceneNodeProperties = htps::PropertyGroup<BackgroundColor>;

}  // namespace zoper

#endif