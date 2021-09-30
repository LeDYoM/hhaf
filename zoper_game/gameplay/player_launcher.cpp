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

void PlayerLauncher::operator()(
    ScoreIncrementer& score_incrementer,
    BoardGroup& board_group,
    htps::function<void(htps::vector2df)> createScoreIncrementPoints)
{
    haf::DisplayLog::info("Launching player");
    vector2df lastTokenPosition{};

    BoardUtils::for_each_coordinate_in_rect(
        board_group.player()->boardPosition(),
        board_group.player()->currentDirection(),
        board_group.boardManager()->size(),
        [&board_group, tokenType = board_group.player()->value(),
         &score_incrementer, &lastTokenPosition,
         &createScoreIncrementPoints](const vector2dst& loopPosition) {
            bool result{true};
            bool found{false};

            if (!board_group.boardManager()->tileEmpty(loopPosition) &&
                TokenZones::toBoardBackgroundType(
                    board_group.boardManager()->backgroundData(loopPosition)) !=
                    TokenZones::BoardBackgroundType::Center)
            {
                sptr<board::ITile> currentToken{
                    board_group.boardManager()->getTile(loopPosition)};
                auto const currentTokenType{currentToken->value()};

                if (currentTokenType == tokenType)
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    score_incrementer.addHit();

                    // Delete the token
                    board_group.boardManager()->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one and
                    // change the type of the token for the previous type of the
                    // player
                    board_group.boardManager()->swapTileData(
                        board_group.player()->boardPosition(), loopPosition);

                    DisplayLog::info("Player type changed to ",
                                     board_group.player()->value());

                    // Exit the loop
                    result = false;
                }
            }

            // Store the position of this last cosumed token
            lastTokenPosition = board_group.board2Scene(loopPosition);

            if (found)
            {
                DisplayLog::info("Tile with same color found");
                DisplayLog::info("Creating points to score");
                createScoreIncrementPoints(lastTokenPosition);
            }
            return result;
        });
    DisplayLog::info("Launching player");
    board_group.player()->launchAnimation(lastTokenPosition);
}

}  // namespace zoper
