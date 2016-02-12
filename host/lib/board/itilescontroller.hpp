#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include <lib/include/types.hpp>

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
			inline void setData(const BoardTileData &nv) { _data = nv; }
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

			virtual void tileAdded(const vector2du32 &position, WITilePointer nTile) = 0;
			virtual void tileDeleted(const vector2du32 &position, WITilePointer nTile) = 0;
			virtual void tileMoved(const vector2du32 &position, const vector2du32 &dest, WITilePointer tile) = 0;
			virtual void tileChanged(const vector2du32 &position, WITilePointer nTile,const BoardTileData &ov, const BoardTileData &nv) = 0;
		};
	}
}

#endif
