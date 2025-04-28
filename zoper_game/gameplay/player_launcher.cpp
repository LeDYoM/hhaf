#include "player_launcher.hpp"
#include "scoreutils.hpp"
#include "player.hpp"
#include "boardutils.hpp"
#include "boardgroup.hpp"
#include "tile_hit_checker.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::render;
using namespace haf::scene;

namespace zoper
{
void PlayerLauncher::operator()(
    ScoreIncrementer& score_incrementer,
    sptr<BoardGroup> board_group,
    htps::function<void(board::BoardPositionType)> createScoreIncrementPoints)
{
    DisplayLog::info("Launching player");
    haf::SceneCoordinates lastTokenPosition{};

    TileHitChecker tile_hit_checker{board_group, board_group->player()->value(),
                                    score_incrementer, lastTokenPosition,
                                    createScoreIncrementPoints};
    BoardUtils::for_each_coordinate_in_rect(
        board_group->player()->boardPosition(),
        board_group->player()->currentDirection(),
        board_group->boardManager()->size(), tile_hit_checker);

    DisplayLog::info("Launching player");
    board_group->player()->launchPlayerAnimation(lastTokenPosition);
}

}  // namespace zoper
