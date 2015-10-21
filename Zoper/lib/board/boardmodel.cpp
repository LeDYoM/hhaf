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
				std::vector<s32> column;
				for (u32 y = 0; y < h; ++y)
				{
					column.push_back(0);
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

		int BoardModel::getTile(u32 x, u32 y) const
		{
			if (validCoords(x, y))
			{
				return _tiles[x][y];
			}
			__ASSERT(false, "Error getting tile in coords " << x << "," << y);
			return -1;
		}

		void BoardModel::setTile(u32 x, u32 y, s32 newTile)
		{
			_setTile(x, y, newTile);
			if (p_tController) p_tController->tileSet(x, y, newTile, newTile);
		}

		void BoardModel::moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest)
		{
			s32 sValue = getTile(xSource, ySource);

			LOG_DEBUG("Moving tile from " << xSource << "," << ySource << " to " << xDest << "," << yDest << 
				". Source Value: " << getTile(xSource, ySource) << ". Erased value: " << getTile(xDest, yDest));

			if (!tileEmpty(xSource, ySource))
			{
				//			__ASSERT(!tileEmpty(xSource, ySource), "Tile " << xSource << "," << ySource << " is empty");
				__ASSERT(tileEmpty(xDest, yDest), "Trying to move to a not empty tile: " << xDest << "," << yDest << " contains " << getTile(xDest, yDest));

				_setTile(xDest, yDest, sValue);
				_setTile(xSource, ySource, _emptyValue);

				if (p_tController) p_tController->tileMoved(xSource, ySource, xDest, yDest, sValue);
			}
		}

		s32 BoardModel::_setTile(u32 x, u32 y, u32 newTile)
		{
			// Implicit error checking
			s32 oldTile = getTile(x, y);

			_tiles[x][y] = newTile;
			return oldTile;
		}
	}
}
