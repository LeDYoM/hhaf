#include "tile_hit_checker.hpp"
#include "player_launcher.hpp"
#include "scoreutils.hpp"
#include "player.hpp"
#include "boardutils.hpp"
#include "boardgroup.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf;
using namespace haf::render;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
TileHitChecker::TileHitChecker(
    BoardGroup& board_group,
    haf::board::ITile::BoardTileData token_type,
    ScoreIncrementer score_incrementer,
    vector2df& lastTokenPosition,
    function<void(vector2df)> createScoreIncrementPoints) :
    board_group_{board_group},
    tokenType{token_type},
    score_incrementer_{score_incrementer},
    lastTokenPosition_{lastTokenPosition},
    createScoreIncrementPoints_{std::move(createScoreIncrementPoints)}
{}

bool TileHitChecker::operator()(vector2dst const& loopPosition)
{
    bool result{true};

    if (!board_group_.boardManager()->tileEmpty(loopPosition) &&
        TokenZones::toBoardBackgroundType(
            board_group_.boardManager()->backgroundData(loopPosition)) !=
            TokenZones::BoardBackgroundType::Center)
    {
        // Store the position of this last cosumed token
        lastTokenPosition_ = board_group_.board2Scene(loopPosition);

        if (board_group_.boardManager()->getTile(loopPosition)->value() ==
            tokenType)
        {
            // If we found a token with the same color than the player:

            // Increment the number of tokens deleted in a row
            score_incrementer_.addHit();

            // Delete the token
            board_group_.boardManager()->deleteTile(loopPosition);

            // You found a token, launch animation
            DisplayLog::info("Tile with same color found");
            DisplayLog::info("Creating points to score");
            createScoreIncrementPoints_(lastTokenPosition_);
        }
        else
        {
            // If we found a token, but it is from another color:

            // Change the type of the player to this new one and
            // change the type of the token for the previous type of the
            // player
            board_group_.boardManager()->swapTileData(
                board_group_.player()->boardPosition(), loopPosition);

            DisplayLog::info("Player type changed to ",
                             board_group_.player()->value());

            // Exit the loop
            result = false;
        }
    }

    return result;
}

}  // namespace zoper
