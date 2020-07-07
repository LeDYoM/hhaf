#pragma once

#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/scene/include/renderizable.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;

class BoardTileSceneNode : public SceneNode
{
private:
    using BaseClass = SceneNode;

public:
    /**
     * @brief Inherit SceneNode constructors.
     */
    using SceneNode::SceneNode;

    /**
     * @brief Destroy the Board Tile Scene Node object
     */
    ~BoardTileSceneNode() override;

    /**
     * @brief Configure the size of this node.
     * 
     * @param tileBox Box for the containing tile.
     */
    void configure(const mtps::Rectf32 &tileBox);

    /**
     * @brief Set the Tile Color
     * @param color A @b Color containing the new color for the background part.
     */
    void setTileColor(Color color);

private:
    void createBackgroundTile(const mtps::Rectf32 &tileBox);

    mtps::sptr<Renderizable> background_tile_;
    mtps::sptr<RenderizableSceneNode> m_pointInCenter;
};
} // namespace zoper

#endif