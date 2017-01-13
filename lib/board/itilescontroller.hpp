#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace board
	{
		using BoardTileData = s32;


		class ITile
		{
		public:
			ITile(const BoardTileData &data) : _data{ data } {}
			virtual ~ITile() = default;
			inline const BoardTileData &getData() const noexcept { return _data; }
			inline void setData(const BoardTileData &nv) { _data = nv; }
		private:
			BoardTileData _data;
		};

		using SITilePointer = sptr<ITile>;
		using WITilePointer = wptr<ITile>;

		class ITilesController
		{
		public:

			ITilesController() = default;
			virtual ~ITilesController() = default;

			virtual void tileAdded(const vector2du32 &position, WITilePointer nTile) = 0;
			virtual void tileDeleted(const vector2du32 &position, WITilePointer nTile) = 0;
			virtual void tileMoved(const vector2du32 &position, const vector2du32 &dest, WITilePointer tile) = 0;
			virtual void tileChanged(const vector2du32 &position, WITilePointer nTile,const BoardTileData &ov, const BoardTileData &nv) = 0;
		};
	}
}

#endif
