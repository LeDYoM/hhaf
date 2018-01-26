#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/core/events/event.hpp>

namespace lib
{
    namespace board
    {
        using BoardTileData = s32;

        class ITile : public PropertyTrigger<BoardTileData>
        {
        public:
            using PropertyTrigger<BoardTileData>::PropertyTrigger;
            virtual ~ITile() = default;
        };

        using SITilePointer = sptr<ITile>;

        class TileEvent
        {
        public:
            TileEvent(vector2du32 &&_position, SITilePointer&& nTile)
                : position{ std::move(_position) }, tile{ std::move(nTile) } {}

            const vector2du32 position;
            const SITilePointer tile;
        };

        class TileAddedEvent : public TileEvent, public events::EventTemplate<TileAddedEvent>
        {
        public:
            TileAddedEvent(vector2du32 _position, SITilePointer nTile)
                : TileEvent{ std::move(_position), std::move(nTile) } {}
        };

        class TileDeletedEvent : public TileEvent, public events::EventTemplate<TileDeletedEvent>
        {
        public:
            TileDeletedEvent(vector2du32 _position, SITilePointer nTile)
                : TileEvent{ std::move(_position), std::move(nTile) } {}
        };

        class TileMovedEvent : public TileEvent, public events::EventTemplate<TileMovedEvent>
        {
        public:
            TileMovedEvent(vector2du32 _position, vector2du32 _dest, SITilePointer nTile)
                : TileEvent{ std::move(_position), std::move(nTile) }, dest{ std::move(_dest) } {}
            const vector2du32 dest;
        };

        class TileChangedEvent : public TileEvent, public events::EventTemplate<TileChangedEvent>
        {
        public:
            TileChangedEvent(vector2du32 _position, SITilePointer nTile, BoardTileData _ov, BoardTileData _nv)
                : TileEvent{ std::move(_position), std::move(nTile) }, ov{ std::move(_ov) }, nv{ std::move(_nv) } {}
            BoardTileData ov, nv;
        };
    }
}

#endif
