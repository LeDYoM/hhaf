#pragma once

#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>

#include "boardscenenode.hpp"

#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{
using namespace lib;
class LevelProperties;

class BoardGroup : public scene::nodes::TableNode<BoardSceneNode>,
                   public board::IBoardModelActuator
{
private:
    using BaseClass = scene::nodes::TableNode<BoardSceneNode>;

public:
    BoardGroup(scene::SceneNode *parent, str name, vector2dst size);
    ~BoardGroup() override;

    void setUp(sptr<LevelProperties> level_properties);
    void createNewToken(
        const board::BoardTileData data,
        const vector2dst& board_position,
        const vector2df& size);

    void onCreated() override;

    void tileRemoved(const vector2dst, board::SITilePointer&) override;

    void setLevel(const size_type level);

    scene::Color getBackgroundTileColor(const size_type level,
                                        vector2dst position, const bool isCenter) const;

    sptr<board::BoardModelComponent> p_boardModel;
    sptr<scene::SceneNode> m_mainBoardrg;
    sptr<LevelProperties> level_properties_;

private:
    vector2df board2SceneFactor() const;
    vector2df board2Scene(const lib::vector2dst &bPosition) const;
    vector2df tileSize() const;
};
} // namespace zoper

#endif
