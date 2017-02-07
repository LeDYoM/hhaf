#include "boardmodel.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace board
	{
		BoardModel::BoardModel(const vector2du32 &size)
		{
			logConstruct(" w: ", size.x, " h: ", size.y);
			_tiles.reserve(size.x);
			for (auto x = 0u; x < size.x; ++x) {
//				std::vector<SITilePointer> column(size.y);
				_tiles.emplace_back(size.y);
			}
			_tiles.shrink_to_fit();
		}

		BoardModel::~BoardModel()
		{
			_tiles.clear();
			logDestruct_NOPARAMS;
		}

		SITilePointer BoardModel::getTile(const vector2du32 &position) const noexcept
		{
			if (validCoords(position)) {
				return _tiles[position.x][position.y];
			}
			logError("Error getting tile in coords ", position.x, ",", position.y);
			return SITilePointer();
		}

		void BoardModel::setTile(const lib::vector2du32 &tPosition, SITilePointer newTile)
		{
			__ASSERT(tileEmpty(tPosition), "You can only set data in empty tiles");

			_setTile(tPosition, newTile);
			host().eventManager().addEvent(msptr<TileAddedEvent>(tPosition, newTile));
		}

		void BoardModel::deleteTile(const vector2du32 &position)
		{
			__ASSERT(!tileEmpty(position), "You can only delete not empty tiles");
			SITilePointer current = getTile(position);
			_tiles[position.x][position.y].reset();
			host().eventManager().addEvent(msptr<TileDeletedEvent>(position, current));
		}

		void BoardModel::changeTileData(const vector2du32 &source, const BoardTileData &nv)
		{
			__ASSERT(!tileEmpty(source), "You can only change data in not empty tiles");

			auto tile (getTile(source));
			BoardTileData ov{ tile->get() };
			tile->set(nv);
			host().eventManager().addEvent(msptr<TileChangedEvent>(source, tile, ov, nv));
		}

		bool BoardModel::moveTile(const vector2du32 &source, const vector2du32 &dest)
		{
			if (!tileEmpty(source)) {
				logDebug("Moving tile from ", source, " to ", dest);

				SITilePointer sourceTile{ getTile(source) };
				SITilePointer destTile{ getTile(dest) };

				logDebug("Source Value: ", sourceTile->get());

				if (sourceTile)	{
					__ASSERT(!destTile, "Trying to move to a not empty tile: " , dest, " contains ", destTile->get());

					_setTile(dest, sourceTile);
					_setTile(source, SITilePointer());

					host().eventManager().addEvent(msptr<TileMovedEvent>(source, dest, sourceTile));
					return true;
				}
			}
			else {
				logDebug("Trying to move empty tile: ", source.x , ",", source.y, " ignoring it");
			}
			return false;
		}

		void BoardModel::_setTile(const vector2du32 &position, SITilePointer newTile)
		{
			_tiles[position.x][position.y] = newTile;
		}
	}
}
