#pragma once

#ifndef LIB_BOARD_IBOARDMODEL_ACTUATOR_HPP
#define LIB_BOARD_IBOARDMODEL_ACTUATOR_HPP

#include <mtypes/include/types.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardModelActuator
{
public:
    virtual void tileAdded(const mtps::vector2dst, SITilePointer &) {}
    virtual void tileRemoved(const mtps::vector2dst, SITilePointer &) {}
    virtual void tileMoved(const mtps::vector2dst, const mtps::vector2dst, SITilePointer &) {}
    virtual void tileChanged(const mtps::vector2dst, SITilePointer &, const BoardTileData, const BoardTileData) {}
};
} // namespace haf::board

#endif
