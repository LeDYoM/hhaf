#include "boardutils.hpp"

using namespace lib;
using namespace mtps;

namespace zoper
{
void BoardUtils::for_each_token_in_line(
    const mtps::vector2dst &startPosition,
    const Direction &direction,
    const mtps::vector2dst &board_size,
    function<bool(const mtps::vector2dst &, const Direction &)> updatePredicate)
{
    mtps::vector2dst loopPosition{startPosition};
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