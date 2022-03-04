#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene_nodes/renderizables_scene_node.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include "boardtile_scene_node_properties.hpp"

namespace zoper
{
class BoardTileSceneNode : public haf::scene::RenderizablesSceneNode,
                           public BoardTileSceneNodeProperties
{
    using BaseClass = haf::scene::RenderizablesSceneNode;

public:
    using BoardTileSceneNodeProperties::prop;
    using BaseClass::prop;

    /**
     * @brief Inherit SceneNode constructors.
     */
    using BaseClass::BaseClass;

    /**
     * @brief Destroy the Board Tile Scene Node object
     */
    ~BoardTileSceneNode() override;

    void update() override;

private:
    void updateBackgroundTile(htps::vector2df const& tile_size);

    htps::sptr<haf::render::Renderizable> background_tile_;
    htps::sptr<haf::scene::RenderizableSceneNode> point_in_center_;
};
}  // namespace zoper

#endif