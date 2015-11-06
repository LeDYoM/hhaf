#include "boardmodel.hpp"
#include "../log.hpp"

namespace lib
{
	namespace board
	{
		BoardModel::BoardModel(const vector2du32 &size, ITilesController *tController)
		{
			p_tController = tController;
			LOG_CONSTRUCT(" w: " << size.x << " h: " << size.y);
			for (auto x = 0u; x < size.x; ++x)
			{
				std::vector<WITilePointer> column;
				for (auto y = 0u; y < size.y; ++y)
				{
					column.push_back(WITilePointer());
				}
				_tiles.push_back(column);
			}
		}

		BoardModel::~BoardModel()
		{
			LOG_DESTRUCT_NOPARAMS;
			_tiles.clear();
			p_tController = nullptr;
		}

		WITilePointer BoardModel::getTile(const vector2du32 &position) const
		{
			if (validCoords(position))
			{
				return _tiles[position.x][position.y];
			}
			__ASSERT(false, "Error getting tile in coords " << position.x << "," << position.y);
			return WITilePointer();
		}

		void BoardModel::setTile(const lib::vector2du32 &tPosition, WITilePointer newTile)
		{
			// By default, we can only set in empty tiles.
			__ASSERT(tileEmpty(tPosition), "You can only set data in empty tiles");

			_setTile(tPosition, newTile);
			if (p_tController) p_tController->tileSet(tPosition, newTile);
		}

		void BoardModel::moveTile(const vector2du32 &source, const vector2du32 &dest, bool ignoreEmptySource)
		{
			if (!tileEmpty(source))
			{
				SITilePointer sourceTile{ getTile(source) };
				WITilePointer destTile{ getTile(dest) };

				LOG_DEBUG("Moving tile from " << source.x << "," << source.y << " to " << dest.x << "," << dest.y <<
					". Source Value: " << sourceTile->getData());

				if (sourceTile)
				{
					//			__ASSERT(!tileEmpty(xSource, ySource), "Tile " << xSource << "," << ySource << " is empty");
					__ASSERT(!destTile.lock(), "Trying to move to a not empty tile: " << dest.x << "," << dest.y << " contains " << destTile.lock()->getData());

					_setTile(dest, sourceTile);
					_setTile(source, WITilePointer());

					if (p_tController) p_tController->tileMoved(source, dest, sourceTile);
				}
			}
			else
			{
				if (!ignoreEmptySource)
				{
					__ASSERT(false, "Trying to move an empty tile: " << source.x << "," << source.y);
				}
				else
				{
					LOG_DEBUG("Trying to move empty tile: " << source.x << "," << source.y << " ignoring it");
				}
			}
		}

		void BoardModel::_setTile(const vector2du32 &position, WITilePointer newTile)
		{
			_tiles[position.x][position.y] = newTile;
		}
	}
}
