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
			if (validCoords(x, y))
			{
				s32 oldTile = _tiles[x][y];
				_tiles[x][y] = newTile;
				if (p_tController) p_tController->tileSet(x, y, oldTile, newTile);
			}
			else
			{
				__ASSERT(false, "Error getting tile in coords " << x << "," << y);
			}
		}

		void BoardModel::moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest)
		{
			s32 sValue = getTile(xSource, ySource);
			s32 dValue = getTile(xDest, yDest);

			LOG_DEBUG("Moving tile from " << xSource << "," << ySource << " to " << xDest << "," << yDest << 
				". Source Value: " << sValue << ". Erased value: " << dValue);

			setTile(xDest, yDest, sValue);
			if (p_tController) p_tController->tileMoved(xSource, ySource, xDest, yDest, sValue,dValue);
		}
	}
}
