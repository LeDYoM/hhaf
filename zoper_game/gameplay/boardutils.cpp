#include "boardutils.hpp"

using namespace haf;
using namespace mtps;

namespace zoper
{
void BoardUtils::for_each_token_in_line(
    const vector2dst &startPosition,
    const Direction &direction,
    const vector2dst &board_size,
    function<bool(const vector2dst &, const Direction &)> updatePredicate)
{
    vector2dst loopPosition{startPosition};
    bool stay{true};

    log_assert((board_size.x > loopPosition.x) &&
                (board_size.y > loopPosition.y), "Invalid initial point");

    while(stay)
    {
        stay &= updatePredicate(loopPosition, direction);
        loopPosition = direction.applyToVector(loopPosition);
        stay &= (board_size.x > loopPosition.x) &&
                (board_size.y > loopPosition.y);
    };
}

} // namespace zoper