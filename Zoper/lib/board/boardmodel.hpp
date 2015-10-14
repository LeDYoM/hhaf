#ifndef __LIB_BOARDMODEL_HPP__
#define __LIB_BOARDMODEL_HPP__

#include <vector>
#include "../types.hpp"
#include "../compileconfig.hpp"
#include "itilescontroller.hpp"

namespace lib
{
	namespace board
	{
		class BoardModel
		{
		public:
			BoardModel(u32 w, u32 h, ITilesController *tController = nullptr);
			virtual ~BoardModel();

			int getTile(u32 x, u32 y) const;
			void setTile(u32 x, u32 y, s32 newTile);
			void moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest);

		private:
			inline bool validCoords(u32 x, u32 y) const { return _tiles.size() > x && _tiles[0].size() > y; }
			std::vector<std::vector<s32>> _tiles;
			ITilesController *p_tController{ nullptr };
		};
	}
}

#endif
