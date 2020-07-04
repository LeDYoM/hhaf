#pragma once

#ifndef ZOPER_BOARDUTILS_INCLUDE_HPP
#define ZOPER_BOARDUTILS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/function.hpp>

#include "direction.hpp"

namespace zoper
{

class BoardUtils
{
public:
    /**
     * @brief For a rectangle, given a start point and a direction, the update
     * predicate will be coll for each position from the starting point up to
     * when the update function return false.
     *
     * @param startPosition
     * @param direction
     * @param board_size
     * @param updatePredicate
     */
    static void for_each_coordinate(
        const mtps::vector2dst& startPosition,
        const Direction& direction,
        mtps::function<bool(const mtps::vector2dst&, const Direction&)>
            updatePredicate);

    static void for_each_coordinate_in_rect(
        const mtps::vector2dst& startPosition,
        const Direction& direction,
        const mtps::vector2dst& board_size,
        mtps::function<bool(const mtps::vector2dst&, const Direction&)>
            updatePredicate);

};
}  // namespace zoper

#endif
