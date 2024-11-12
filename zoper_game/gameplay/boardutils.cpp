#include "boardutils.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace fmath;

namespace zoper
{
void BoardUtils::for_each_coordinate(
    vector2dst startPosition,
    const Direction& direction,
    htps::function<bool(const vector2dst&)> updatePredicate)
{
    bool stay{true};

    while (stay)
    {
        stay &= updatePredicate(startPosition);
        startPosition = direction.applyToVector(startPosition);
    };
}

void BoardUtils::for_each_coordinate_in_rect(
    vector2dst const& startPosition,
    Direction const& direction,
    vector2dst const& board_size,
    function<bool(const vector2dst&)> updatePredicate)
{
    haf::LogAsserter::log_assert(
        (board_size.x > startPosition.x) && (board_size.y > startPosition.y),
        "Invalid initial point");

    for_each_coordinate(
        startPosition, direction,
        [&board_size, updatePredicate = htps::move(updatePredicate)](
            const vector2dst& v) {
            return (v.x < board_size.x) && (v.y < board_size.y) &&
                updatePredicate(v);
        });
}

}  // namespace zoper