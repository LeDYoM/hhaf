#ifndef ZOPER_BOARDUTILS_INCLUDE_HPP
#define ZOPER_BOARDUTILS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/function.hpp>

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
        htps::vector2dst startPosition,
        Direction const& direction,
        htps::function<bool(const htps::vector2dst&)> updatePredicate);

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
        htps::vector2dst const& startPosition,
        Direction const& direction,
        htps::vector2dst const& board_size,
        htps::function<bool(const htps::vector2dst&)> updatePredicate);
};
}  // namespace zoper

#endif
