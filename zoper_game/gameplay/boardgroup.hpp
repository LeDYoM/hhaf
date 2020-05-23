#pragma once

#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <mtypes/include/vector2d.hpp>

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/tablenode.hpp>

#include "boardscenenode.hpp"

#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{

class LevelProperties;
class Player;

class BoardGroup : public haf::scene::nodes::TableNode<BoardSceneNode>,
                   public haf::board::IBoardManagerActuator
{
private:
    using BaseClass = haf::scene::nodes::TableNode<BoardSceneNode>;

public:
    using BaseClass::BaseClass;

    ~BoardGroup() override;

    void configure(mtps::vector2dst size,
                   mtps::sptr<LevelProperties> level_properties);
    void createNewToken(const haf::board::BoardTileData data,
                        const mtps::vector2dst& board_position,
                        const mtps::vector2df& size);

    void tileRemoved(const mtps::vector2dst,
                     haf::board::SITilePointer&) override;
    void setLevel(const mtps::size_type level);

    haf::scene::Color getBackgroundTileColor(const mtps::size_type level,
                                             mtps::vector2dst position,
                                             const bool isCenter) const;

    mtps::sptr<board::BoardManager> boardModel() noexcept;
    const mtps::sptr<const board::BoardManager> boardModel() const noexcept;
    mtps::sptr<scene::SceneNode> tokensSceneNode() noexcept;
    const mtps::sptr<scene::SceneNode> tokensSceneNode() const noexcept;
    mtps::sptr<Player> player() noexcept;
    const mtps::sptr<Player> player() const noexcept;

    mtps::vector2df board2SceneFactor() const;
    mtps::vector2df board2Scene(const mtps::vector2dst& bPosition) const;
    mtps::vector2df tileSize() const;

private:
    mtps::sptr<haf::board::BoardManager> board_model_;
    mtps::sptr<Player> player_;
    mtps::sptr<haf::scene::SceneNode> tokens_scene_node;
    mtps::sptr<LevelProperties> level_properties_;

    void addPlayer();
};
}  // namespace zoper

#endif
