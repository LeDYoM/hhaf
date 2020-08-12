#pragma once

#ifndef ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP
#define ZOPER_BOARD_TILE_SCENENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/grouping_property.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/scene/include/renderizable.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>
#include <haf/scene_nodes/include/scene_node_size.hpp>

namespace zoper
{
using namespace haf;
using namespace haf::scene;

struct BackgroundColor
{
    using value_type = Color;
};

using BoardTileSceneNodeProperties = mtps::PropertyGroup<BackgroundColor>;

class BoardTileSceneNode : public SceneNode,
                           public SceneNodeSizeProperties,
                           public BoardTileSceneNodeProperties
{
public:
    using BaseClass = SceneNode;
    using SceneNodeSizeProperties::prop;
    using BoardTileSceneNodeProperties::prop;

    /**
     * @brief Inherit SceneNode constructors.
     */
    using SceneNode::SceneNode;

    /**
     * @brief Destroy the Board Tile Scene Node object
     */
    ~BoardTileSceneNode() override;

    void update() override;

private:
    void createBackgroundTile(const mtps::Rectf32& tileBox);

    mtps::sptr<Renderizable> background_tile_;
    mtps::sptr<RenderizableSceneNode> m_pointInCenter;
};
}  // namespace zoper

#endif