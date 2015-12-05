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
			ITile(const BoardTileData &data) : _data{ data } {}
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

			virtual void tileSet(const vector2du32 &position, WITilePointer nTile) = 0;
			virtual void tileMoved(const vector2du32 &position, const vector2du32 &dest, WITilePointer tile) = 0;


		};
	}
}

#endif
