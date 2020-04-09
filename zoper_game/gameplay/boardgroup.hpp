#pragma once

#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/tablenode.hpp>

#include "boardscenenode.hpp"

#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{
using namespace haf;
class LevelProperties;
class Player;

class BoardGroup : public scene::nodes::TableNode<BoardSceneNode>,
                   public board::IBoardModelActuator
{
private:
    using BaseClass = scene::nodes::TableNode<BoardSceneNode>;

public:
    BoardGroup(scene::SceneNode *parent, mtps::str name, mtps::vector2dst size);
    ~BoardGroup() override;

    void configure(mtps::sptr<LevelProperties> level_properties);
    void createNewToken(
        const board::BoardTileData data,
        const mtps::vector2dst& board_position,
        const mtps::vector2df& size);

    void onCreated() override;
    void tileRemoved(const mtps::vector2dst, board::SITilePointer&) override;
    void setLevel(const mtps::size_type level);

    scene::Color getBackgroundTileColor(const mtps::size_type level,
                                        mtps::vector2dst position, const bool isCenter) const;

    mtps::sptr<board::BoardModelComponent> boardModel() noexcept { return p_boardModel; }
    const mtps::sptr<const board::BoardModelComponent> boardModel() const noexcept { return p_boardModel; }

    mtps::sptr<scene::SceneNode> tokensSceneNode() noexcept { return tokens_scene_node; }
    const mtps::sptr<scene::SceneNode> tokensSceneNode() const noexcept { return tokens_scene_node; }

    mtps::sptr<Player> player() noexcept { return player_; }
    const mtps::sptr<Player> player() const noexcept { return player_; }

    mtps::vector2df board2SceneFactor() const;
    mtps::vector2df board2Scene(const mtps::vector2dst &bPosition) const;
    mtps::vector2df tileSize() const;

private:
    mtps::sptr<board::BoardModelComponent> p_boardModel;
    mtps::sptr<Player> player_;
    mtps::sptr<scene::SceneNode> tokens_scene_node;
    mtps::sptr<LevelProperties> level_properties_;

    void addPlayer();
};
} // namespace zoper

#endif
