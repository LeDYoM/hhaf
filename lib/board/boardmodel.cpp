#include "boardmodel.hpp"
#include <mtypes/include/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace board
	{
		BoardModelComponent::BoardModelComponent()
		{
			logConstruct_NOPARAMS;
		}

		BoardModelComponent::~BoardModelComponent()
		{
			_tiles.clear();
			logDestruct_NOPARAMS;
		}

		void BoardModelComponent::initialize(const vector2du32 &size)
		{
			log_debug_info("BoardModelComponent initialize with size: ", size);
			_tiles.reserve(size.x);
			for (auto x = 0u; x < size.x; ++x) {
				//				vector<SITilePointer> column(size.y);
				_tiles.emplace_back(size.y);
			}
			_tiles.shrink_to_fit();
		}

		SITilePointer BoardModelComponent::getTile(const vector2du32 &position) const noexcept
		{
			if (validCoords(position)) {
				return _tiles[position.x][position.y];
			}
			log_debug_error("Error getting tile in coords ", position.x, ",", position.y);
			return SITilePointer();
		}

		void BoardModelComponent::setTile(const lib::vector2du32 &tPosition, SITilePointer newTile)
		{
			__ASSERT(tileEmpty(tPosition), "You can only set data in empty tiles");

			_setTile(tPosition, newTile);
			host().eventManager().addEvent(msptr<TileAddedEvent>(tPosition, newTile));
		}

		void BoardModelComponent::deleteTile(const vector2du32 &position)
		{
			__ASSERT(!tileEmpty(position), "You can only delete not empty tiles");
			SITilePointer current = getTile(position);
			_tiles[position.x][position.y].reset();
			host().eventManager().addEvent(msptr<TileDeletedEvent>(position, current));
		}

		void BoardModelComponent::changeTileData(const vector2du32 &source, const BoardTileData &nv)
		{
			__ASSERT(!tileEmpty(source), "You can only change data in not empty tiles");

			auto tile (getTile(source));
			BoardTileData ov{ tile->get() };
			tile->set(nv);
			host().eventManager().addEvent(msptr<TileChangedEvent>(source, tile, ov, nv));
		}

		bool BoardModelComponent::moveTile(const vector2du32 &source, const vector2du32 &dest)
		{
			if (!tileEmpty(source)) {
				log_debug_info("Moving tile from ", source, " to ", dest);

				SITilePointer sourceTile{ getTile(source) };
				SITilePointer destTile{ getTile(dest) };

				log_debug_info("Source Value: ", sourceTile->get());

				if (sourceTile)	{
					__ASSERT(!destTile, "Trying to move to a not empty tile: " , dest, " contains ", destTile->get());

					_setTile(dest, sourceTile);
					_setTile(source, SITilePointer());

					host().eventManager().addEvent(msptr<TileMovedEvent>(source, dest, sourceTile));
					return true;
				}
			}
			else {
				log_debug_info("Trying to move empty tile: ", source.x , ",", source.y, " ignoring it");
			}
			return false;
		}

		void BoardModelComponent::_setTile(const vector2du32 &position, SITilePointer newTile)
		{
			_tiles[position.x][position.y] = newTile;
		}
	}
}
