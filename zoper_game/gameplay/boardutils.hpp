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
     * @param startPosition Position where to start the processing
     * @param direction @b Direction to where the loop will move the position
     * @param updatePredicate Function to call for each position
     */
    static void for_each_coordinate(
        const mtps::vector2dst& startPosition,
        const Direction& direction,
        mtps::function<bool(const mtps::vector2dst&, const Direction&)>
            updatePredicate);

    /**
     * @brief For a rectangle, given a start point and a direction, the update
     * predicate will be coll for each position from the starting point up to
     * when the update function return false or we pass the bounds given from
     * board_size
     *
     * @param startPosition Position where to start the processing
     * @param direction @b Direction to where the loop will move the position
     * @param board_size Bounds of the rect to check
     * @param updatePredicate Function to call for each position
     */
    static void for_each_coordinate_in_rect(
        const mtps::vector2dst& startPosition,
        const Direction& direction,
        const mtps::vector2dst& board_size,
        mtps::function<bool(const mtps::vector2dst&, const Direction&)>
            updatePredicate);

};
}  // namespace zoper

#endif
