#pragma once

#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/grouping_property.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/scene_node_size.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/render/include/renderizable.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>
#include <haf/scene_nodes/include/scene_node_size.hpp>
#include "boardtilescenenode_properties.hpp"

namespace zoper
{
class BoardTileSceneNode : public haf::scene::SceneNode,
                           public haf::scene::SceneNodeSizeProperties,
                           public BoardTileSceneNodeProperties
{
public:
    using BaseClass = haf::scene::SceneNode;
    using haf::scene::SceneNodeSizeProperties::prop;
    using BoardTileSceneNodeProperties::prop;

    /**
     * @brief Inherit SceneNode constructors.
     */
    using haf::scene::SceneNode::SceneNode;

    /**
     * @brief Destroy the Board Tile Scene Node object
     */
    ~BoardTileSceneNode() override;

    void update() override;

private:
    void createBackgroundTile(const mtps::Rectf32& tileBox);

    mtps::sptr<haf::scene::Renderizable> background_tile_;
    mtps::sptr<haf::scene::RenderizableSceneNode> m_pointInCenter;
};
}  // namespace zoper

#endif