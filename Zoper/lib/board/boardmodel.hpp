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

			WITilePointer getTile(u32 x, u32 y) const;
			inline bool tileEmpty(u32 x, u32 y) const { return getTile(x, y).lock() == nullptr; }
			void setTile(u32 x, u32 y, WITilePointer newTile);
			void moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest, bool ignoreEmptySource = false);

		private:
			void _setTile(u32 x, u32 y, WITilePointer newTile);
			inline bool validCoords(u32 x, u32 y) const { return _tiles.size() > x && _tiles[0].size() > y; }
			std::vector<std::vector<WITilePointer>> _tiles;
			ITilesController *p_tController{ nullptr };
		};
	}
}

#endif
