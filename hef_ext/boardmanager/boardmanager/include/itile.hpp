#pragma once

#ifndef LIB_BOARD_ITILE_HPP
#define LIB_BOARD_ITILE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib::board
{
using BoardTileData = mtps::s32;

class ITile
{
public:
    constexpr ITile() noexcept {}
    virtual ~ITile() {}

    mtps::PropertyState<BoardTileData> data;
    virtual void tileAdded(const mtps::vector2dst & /* position */) {}
    virtual void tileRemoved(const mtps::vector2dst & /* position */) {}
    virtual void tileChanged(const mtps::vector2dst & /*position */,
                             const BoardTileData /* oldValue */,
                             const BoardTileData /* newValue */) {}

    virtual void tileMoved(const mtps::vector2dst & /* source */,
                           const mtps::vector2dst & /* dest */) {}
};

using SITilePointer = mtps::sptr<ITile>;
} // namespace lib::board

#endif
