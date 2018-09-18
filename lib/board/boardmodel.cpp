#include "boardmodel.hpp"
#include <lib/include/core/log.hpp>

namespace lib
{
    namespace board
    {
        BoardModelComponent::BoardModelComponent() {}
        BoardModelComponent::~BoardModelComponent() {}

        void BoardModelComponent::initialize(const vector2dst &size)
        {
            log_debug_info("BoardModelComponent initialize with size: ", size);
            _tiles.reserve(size.x);
            for (auto x = 0u; x < size.x; ++x) {
                _tiles.emplace_back(size.y);
            }
            _tiles.shrink_to_fit();
        }

        SITilePointer BoardModelComponent::getTile(const vector2dst &position) const noexcept
        {
            if (validCoords(position)) {
                return _tiles[position.x][position.y];
            }
            log_debug_error("Error getting tile in coords ", position.x, ",", position.y);
            return SITilePointer();
        }

        void BoardModelComponent::setTile(const lib::vector2dst &tPosition, SITilePointer newTile)
        {
            assert_release(tileEmpty(tPosition), "You can only set data in empty tiles");

            _setTile(tPosition, newTile);
            newTile->tileAdded(tPosition);
            TileAdded(tPosition, newTile);
        }

        void BoardModelComponent::deleteTile(const vector2dst &position)
        {
            assert_release(!tileEmpty(position), "You can only delete not empty tiles");

            SITilePointer current(getTile(position));
            current->tileRemoved(position);

            _tiles[position.x][position.y].reset();
            TileRemoved(position, current);
        }

        void BoardModelComponent::changeTileData(const vector2dst &source, const BoardTileData &nv)
        {
            assert_release(!tileEmpty(source), "You can only change data in not empty tiles");

            auto tile (getTile(source));
            BoardTileData ov{ tile->get() };

            tile->tileChanged(source, ov, nv);
            TileChanged(source, tile, ov, nv);
        }

        bool BoardModelComponent::moveTile(const vector2dst &source, const vector2dst &dest)
        {
            if (!tileEmpty(source))
            {
                log_debug_info("Moving tile from ", source, " to ", dest);

                SITilePointer sourceTile{ getTile(source) };
                SITilePointer destTile{ getTile(dest) };

                log_debug_info("Source Value: ", sourceTile->get());

                if (sourceTile)
                {
                    assert_release(!destTile, "Trying to move to a not empty tile: " , dest);

                    _setTile(dest, sourceTile);
                    _setTile(source, SITilePointer());

                    TileMoved(source, dest, sourceTile);
                    sourceTile->tileMoved(source, dest);
                    return true;
                }
            }
            else
            {
                log_debug_info("Trying to move empty tile: ", source.x , ",", source.y, " ignoring it");
            }
            return false;
        }

        void BoardModelComponent::_setTile(const vector2dst &position, SITilePointer newTile)
        {
            _tiles[position.x][position.y] = newTile;
        }
    }
}
