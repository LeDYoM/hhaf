#include "boardmodel.hpp"
#include "../log.hpp"

namespace lib
{
	namespace board
	{
		BoardModel::BoardModel(u32 w, u32 h, ITilesController *tController)
		{
			p_tController = tController;
			LOG_CONSTRUCT(" w: " << w << " h: " << h);
			for (u32 x = 0; x < w; ++x)
			{
				std::vector<WITilePointer> column;
				for (u32 y = 0; y < h; ++y)
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

		WITilePointer BoardModel::getTile(u32 x, u32 y) const
		{
			if (validCoords(x, y))
			{
				return _tiles[x][y];
			}
			__ASSERT(false, "Error getting tile in coords " << x << "," << y);
			return WITilePointer();
		}

		void BoardModel::setTile(u32 x, u32 y, WITilePointer newTile)
		{
			_setTile(x, y, newTile);
			if (p_tController) p_tController->tileSet(x, y, newTile);
		}

		void BoardModel::moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest, bool ignoreEmptySource)
		{
			if (!tileEmpty(xSource, ySource))
			{
				SITilePointer sourceTile{ getTile(xSource, ySource) };
				WITilePointer destTile{ getTile(xDest, yDest) };

				LOG_DEBUG("Moving tile from " << xSource << "," << ySource << " to " << xDest << "," << yDest <<
					". Source Value: " << sourceTile->getData());

				if (sourceTile)
				{
					//			__ASSERT(!tileEmpty(xSource, ySource), "Tile " << xSource << "," << ySource << " is empty");
					__ASSERT(!destTile.lock(), "Trying to move to a not empty tile: " << xDest << "," << yDest << " contains " << destTile.lock()->getData());

					_setTile(xDest, yDest, sourceTile);
					_setTile(xSource, ySource, WITilePointer());

					if (p_tController) p_tController->tileMoved(xSource, ySource, xDest, yDest, sourceTile);
				}
			}
			else
			{
				if (!ignoreEmptySource)
				{
					__ASSERT(false, "Trying to move an empty tile: " << xSource << "," << ySource);
				}
				else
				{
					LOG_DEBUG("Trying to move empty tile: " << xSource << "," << ySource << " ignoring it");
				}
			}
		}

		void BoardModel::_setTile(u32 x, u32 y, WITilePointer newTile)
		{
			// Implicit error checking
			// By default, we can only set in empty tiles.
			__ASSERT(tileEmpty(x,y), "You can only set data in empty tiles");

			_tiles[x][y] = newTile;
		}
	}
}
