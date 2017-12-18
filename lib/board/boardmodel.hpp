#ifndef __LIB_BOARDMODEL_HPP__
#define __LIB_BOARDMODEL_HPP__

#include <mtypes/include/types.hpp>
#include "itilescontroller.hpp"
#include <lib/scene/components/icomponent.hpp>

namespace lib
{
	namespace board
	{
		class BoardModelComponent : public scene::IComponent
		{
		public:
			BoardModelComponent();
			~BoardModelComponent();

			virtual void update() override final {}
			void initialize(const vector2du32 &size);

			SITilePointer getTile(const vector2du32 &position) const noexcept;
			inline bool tileEmpty(const vector2du32 &position) const noexcept { return getTile(position) == nullptr; }
			void setTile(const vector2du32 &position, SITilePointer newTile);
			void deleteTile(const vector2du32 &position);
			bool moveTile(const vector2du32 &source, const vector2du32 &dest);
			void changeTileData(const vector2du32 &source, const BoardTileData &nv);

			inline bool validCoords(const vector2du32 &tPosition) const noexcept { return _tiles.size() > tPosition.x && _tiles[0].size() > tPosition.y; }
			inline bool validCoords(const vector2ds32 &tPosition) const noexcept { return tPosition.x >= 0 && tPosition.y >= 0 && validCoords(vector2du32{ static_cast<u32>(tPosition.x), static_cast<u32>(tPosition.y) }); }
			inline const vector2dst size() const noexcept { return vector2dst{ _tiles.size(),_tiles[0].size() }; }

		private:
			void _setTile(const vector2du32 &position, SITilePointer newTile);
			vector<vector<SITilePointer>> _tiles;
		};
	}
}

#endif
