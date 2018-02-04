#ifndef __LIB_BOARDMODEL_HPP__
#define __LIB_BOARDMODEL_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include "itilescontroller.hpp"
#include <lib/scene/components/icomponent.hpp>

namespace lib
{
    namespace board
    {
        class BoardModelComponent : public scene::IComponent
        {
        public:
            BoardModelComponent();
            ~BoardModelComponent();

            virtual void update() override final {}
            void initialize(const vector2dst &size);

            SITilePointer getTile(const vector2dst &position) const noexcept;
            inline bool tileEmpty(const vector2dst &position) const noexcept { return getTile(position) == nullptr; }
            void setTile(const vector2dst &position, SITilePointer newTile);
            void deleteTile(const vector2dst &position);
            bool moveTile(const vector2dst &source, const vector2dst &dest);
            void changeTileData(const vector2dst &source, const BoardTileData &nv);

            inline bool validCoords(const vector2dst &tPosition) const noexcept { return _tiles.size() > tPosition.x && _tiles[0].size() > tPosition.y; }
            inline const vector2dst size() const noexcept { return vector2dst{ _tiles.size(),_tiles[0].size() }; }

            emitter<const vector2dst, SITilePointer> TileAdded;
            emitter<const vector2dst, SITilePointer> TileRemoved;
            emitter<const vector2dst, const vector2dst, SITilePointer> TileMoved;
            emitter<const vector2dst, SITilePointer, const BoardTileData, const BoardTileData> TileChanged;

        private:
            void _setTile(const vector2dst &position, SITilePointer newTile);
            vector<vector<SITilePointer>> _tiles;
        };
    }
}

#endif
