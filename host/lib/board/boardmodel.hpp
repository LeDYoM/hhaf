#ifndef __LIB_BOARDMODEL_HPP__
#define __LIB_BOARDMODEL_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/core/compileconfig.hpp>
#include "itilescontroller.hpp"

namespace lib
{
	namespace board
	{
		class BoardModel
		{
		public:
			BoardModel(const vector2du32 &size, ITilesController *tController = nullptr);
			virtual ~BoardModel();

			WITilePointer getTile(const vector2du32 &position) const;
			inline bool tileEmpty(const vector2du32 &position) const { return getTile(position).lock() == nullptr; }
			void setTile(const vector2du32 &position, WITilePointer newTile);
			void deleteTile(const vector2du32 &position);
			bool moveTile(const vector2du32 &source, const vector2du32 &dest);
			void changeTileData(const vector2du32 &source, const BoardTileData &nv);

			inline bool validCoords(const vector2du32 &tPosition) const { return _tiles.size() > tPosition.x && _tiles[0].size() > tPosition.y; }
			inline bool validCoords(const vector2ds32 &tPosition) const { return tPosition.x >= 0 && tPosition.y >= 0 && validCoords(vector2du32(static_cast<u32>(tPosition.x), static_cast<u32>(tPosition.y))); }
			inline const vector2du32 size() const { return vector2du32{ _tiles.size(),_tiles[0].size() }; }

		private:
			void _setTile(const vector2du32 &position, WITilePointer newTile);
			std::vector<std::vector<WITilePointer>> _tiles;
			ITilesController *p_tController{ nullptr };
		};
	}
}

#endif
