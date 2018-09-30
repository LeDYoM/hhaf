#pragma once

#ifndef LIB_BOARD_BOARDMODEL_HPP
#define LIB_BOARD_BOARDMODEL_HPP

#include <mtypes/include/types.hpp>
#include "itile.hpp"
#include <lib/scene/components/icomponent.hpp>

namespace lib::board
{
    class IBoardModelActuator;

    class BoardModelComponent : public scene::IComponent
    {
    public:
        BoardModelComponent();
        ~BoardModelComponent() override;

        virtual void update() override final {}
        void initialize(const vector2dst &size, IBoardModelActuator* boardModelActuator);

        SITilePointer getTile(const vector2dst &position) const noexcept;
        inline bool tileEmpty(const vector2dst &position) const noexcept { return getTile(position) == nullptr; }
        void setTile(const vector2dst &position, SITilePointer newTile);
        void deleteTile(const vector2dst &position);
        bool moveTile(const vector2dst &source, const vector2dst &dest);
        void changeTileData(const vector2dst &source, const BoardTileData &nv);

        inline bool validCoords(const vector2dst &tPosition) const noexcept { return _tiles.size() > tPosition.x && _tiles[0].size() > tPosition.y; }
        inline const vector2dst size() const noexcept { return vector2dst{ _tiles.size(),_tiles[0].size() }; }

    private:
        void _setTile(const vector2dst &position, SITilePointer newTile);

        IBoardModelActuator* m_actuator;
        vector<vector<SITilePointer>> _tiles;
    };
}

#endif
