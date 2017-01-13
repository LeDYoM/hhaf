#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/core/events/event.hpp>

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

		class TileEvent
		{
		public:
			TileEvent(vector2du32 &&_position, WITilePointer&& nTile)
				: position{ std::move(_position) }, tile{ std::move(nTile) } {}

			const vector2du32 position;
			const WITilePointer tile;
		};

		class TileAddedEvent : public TileEvent, public events::EventTemplate<TileAddedEvent>
		{
		public:
			TileAddedEvent(vector2du32 _position, WITilePointer nTile)
				: TileEvent{ std::move(_position), std::move(nTile) } {}
		};

		class TileDeletedEvent : public TileEvent, public events::EventTemplate<TileDeletedEvent>
		{
		public:
			TileDeletedEvent(vector2du32 _position, WITilePointer nTile)
				: TileEvent{ std::move(_position), std::move(nTile) } {}
		};

		class TileMovedEvent : public TileEvent, public events::EventTemplate<TileMovedEvent>
		{
		public:
			TileMovedEvent(vector2du32 _position, vector2du32 _dest, WITilePointer nTile)
				: TileEvent{ std::move(_position), std::move(nTile) }, dest{ std::move(_dest) } {}
			const vector2du32 dest;
		};

		class TileChangedEvent : public TileEvent, public events::EventTemplate<TileChangedEvent>
		{
		public:
			TileChangedEvent(vector2du32 _position, WITilePointer nTile, BoardTileData _ov, BoardTileData _nv)
				: TileEvent{ std::move(_position), std::move(nTile) }, ov{ std::move(_ov) }, nv{ std::move(_nv) } {}
			BoardTileData ov, nv;
		};
	}
}

#endif
