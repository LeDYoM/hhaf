#pragma once

#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "itile.hpp"
#include <lib/scene/include/icomponent.hpp>

namespace lib::board
{
class IBoardModelActuator;

class BoardModelComponent : public scene::IComponent
{
public:
    BoardModelComponent();
    ~BoardModelComponent() override;

    virtual void update() override final {}
    void initialize(const mtps::vector2dst &size, IBoardModelActuator *boardModelActuator);

    SITilePointer getTile(const mtps::vector2dst &position) const noexcept;
    inline bool tileEmpty(const mtps::vector2dst &position) const noexcept { return getTile(position) == nullptr; }
    void setTile(const mtps::vector2dst &position, SITilePointer newTile);
    void deleteTile(const mtps::vector2dst &position);
    bool moveTile(const mtps::vector2dst &source, const mtps::vector2dst &dest);
    void changeTileData(const mtps::vector2dst &source, const BoardTileData &nv);
    void swapTileData(const mtps::vector2dst &lhs, const mtps::vector2dst &rhs);

    inline bool validCoords(const mtps::vector2dst &tPosition) const noexcept
    {
        return _tiles.size() > tPosition.x && _tiles[0U].size() > tPosition.y;
    }

    inline const mtps::vector2dst size() const noexcept { return mtps::vector2dst{_tiles.size(), _tiles[0].size()}; }

private:
    void _setTile(const mtps::vector2dst &position, SITilePointer newTile);

    IBoardModelActuator *m_actuator{nullptr};
    mtps::vector<mtps::vector<SITilePointer>> _tiles;
};
} // namespace lib::board

#endif
