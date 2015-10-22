#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

namespace lib
{
	namespace board
	{
		using BoardTileData = s32;


		class ITile
		{
		public:
			ITile(const BoardTileData data) : _data{ data } {}
			virtual ~ITile() {}
			inline const BoardTileData &getData() const { return _data; }
		private:
			BoardTileData _data;
		};
		typedef sptr<ITile> SITilePointer;
		typedef wptr<ITile> WITilePointer;

		class ITilesController
		{
		public:

			ITilesController() {}
			virtual ~ITilesController() {}

			virtual void tileSet(u32 x, u32 y, WITilePointer nTile) = 0;
			virtual void tileMoved(u32 xSource, u32 ySource, u32 xDest, u32 yDest, WITilePointer tile) = 0;

		};
	}
}

#endif
