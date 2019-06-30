#pragma once

#ifndef LIB_BOARD_ITILE_HPP
#define LIB_BOARD_ITILE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib::board
{
    using BoardTileData = s32;

    class ITile
    {
    public:
        constexpr ITile() noexcept {}
        virtual ~ITile() = default;

        PropertyTrigger<BoardTileData> data;
        virtual void tileAdded(const vector2dst & /* position */) {}
        virtual void tileRemoved(const vector2dst & /* position */) {}
        virtual void tileChanged(const vector2dst & /*position */,
            const BoardTileData /* oldValue */,
            const BoardTileData /* newValue */)
        {}

        virtual void tileMoved(const vector2dst& /* source */, 
            const vector2dst& /* dest */) {}
    };

    using SITilePointer = sptr<ITile>;
}

#endif
