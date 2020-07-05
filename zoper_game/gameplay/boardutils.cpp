#include "boardutils.hpp"

using namespace haf;
using namespace mtps;

namespace zoper
{
void BoardUtils::for_each_coordinate(
    const vector2dst& startPosition,
    const Direction& direction,
    function<bool(const vector2dst&, const Direction&)> updatePredicate)
{
    vector2dst loopPosition{startPosition};
    bool stay{true};

    while (stay)
    {
        stay &= updatePredicate(loopPosition, direction);
        loopPosition = direction.applyToVector(loopPosition);
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
            return (board_size.x > v.x) && (board_size.y > v.y) &&
                updatePredicate(v, d);
        });
}

}  // namespace zoper