#pragma once

#ifndef LIB_BOARD_IBOARDMODEL_ACTUATOR_HPP
#define LIB_BOARD_IBOARDMODEL_ACTUATOR_HPP

#include <mtypes/include/types.hpp>
#include "itilescontroller.hpp"

namespace lib::board
{
    class IBoardModelActuator
    {
    public:
        virtual void tileAdded(const vector2dst, SITilePointer) {}
        virtual void tileRemoved(const vector2dst, SITilePointer) {}
        virtual void tileMoved(const vector2dst, const vector2dst, SITilePointer) {}
        virtual void tileChanged(const vector2dst, SITilePointer, const BoardTileData, const BoardTileData) {}
    };
}

#endif
