#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/property_group.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene_nodes/scene_node_size.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/renderizables_scenenode.hpp>
#include <haf/include/scene_nodes/renderizable_scenenode.hpp>
#include <haf/include/scene_nodes/scene_node_size.hpp>
#include "boardtilescenenode_properties.hpp"

namespace zoper
{
class BoardTileSceneNode : public haf::scene::RenderizablesSceneNode,
                           public haf::scene::SceneNodeSizeProperties,
                           public BoardTileSceneNodeProperties
{
    using BaseClass = haf::scene::RenderizablesSceneNode;

public:
    using BoardTileSceneNodeProperties::prop;
    using haf::scene::SceneNodeSizeProperties::prop;

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
    void createBackgroundTile(const htps::Rectf32& tileBox);

    htps::sptr<haf::render::Renderizable> background_tile_;
    htps::sptr<haf::scene::RenderizableSceneNode> point_in_center_;
};
}  // namespace zoper

#endif