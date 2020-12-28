#include "boardutils.hpp"

using namespace haf;
using namespace mtps;

namespace zoper
{
void BoardUtils::for_each_coordinate(
    vector2dst startPosition,
    const Direction& direction,
    function<bool(const vector2dst&, const Direction&)> updatePredicate)
{
    bool stay{true};

    while (stay)
    {
        stay &= updatePredicate(startPosition, direction);
        startPosition = direction.applyToVector(startPosition);
    };
}

void BoardUtils::for_each_coordinate_in_rect(
    const vector2dst& startPosition,
    const Direction& direction,
    const vector2dst& board_size,
    function<bool(const vector2dst&, const Direction&)> updatePredicate)
{
    LogAsserter::log_assert(
        (board_size.x > startPosition.x) && (board_size.y > startPosition.y),
        "Invalid initial point");

    for_each_coordinate(
        startPosition, direction,
        [&board_size, updatePredicate = std::move(updatePredicate)](
            const vector2dst& v, const Direction& d) {
            return (v.x < board_size.x) && (v.y < board_size.y) &&
                updatePredicate(v, d);
        });
}

}  // namespace zoper