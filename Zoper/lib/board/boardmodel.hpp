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
		using BoardTile = s32;
		class BoardModel
		{
		public:
			BoardModel(u32 w, u32 h, ITilesController *tController = nullptr);
			virtual ~BoardModel();

			int getTile(u32 x, u32 y) const;
			inline bool tileEmpty(u32 x, u32 y) const { return getTile(x, y) == _emptyValue; }
			void setTile(u32 x, u32 y, s32 newTile);
			void moveTile(u32 xSource, u32 ySource, u32 xDest, u32 yDest);

		private:
			s32 _setTile(u32 x, u32 y, u32 newTile);
			inline bool validCoords(u32 x, u32 y) const { return _tiles.size() > x && _tiles[0].size() > y; }
			std::vector<std::vector<s32>> _tiles;
			ITilesController *p_tController{ nullptr };
			BoardTile _emptyValue{ 0 };

		};
	}
}

#endif
