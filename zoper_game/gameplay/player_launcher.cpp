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

void PlayerLauncher::operator()(Player& player,
                                ScoreIncrementer& score_incrementer,
                                BoardGroup& board_group)
{
    haf::DisplayLog::info("Launching player");
    auto const loopDirection{player.currentDirection()};
    auto const loopPosition{player.boardPosition()};
    auto const tokenType{player.value()};
    vector2df lastTokenPosition{};

    BoardUtils::for_each_coordinate_in_rect(
        loopPosition, loopDirection, board_group.boardManager()->size(),
        [this, tokenType, &score_incrementer, &lastTokenPosition](
            const vector2dst& loopPosition, const Direction&) {
            bool result{true};
            bool found{false};

            if (!board_group.boardManager()->tileEmpty(loopPosition) &&
                TokenZones::toBoardBackgroundType(
                    m_boardGroup->boardManager()->backgroundData(
                        loopPosition)) !=
                    TokenZones::BoardBackgroundType::Center)
            {
                sptr<board::ITile> currentToken{
                    m_boardGroup->boardManager()->getTile(loopPosition)};
                auto const currentTokenType{currentToken->value()};

                if (currentTokenType == tokenType)
                {
                    // If we found a token with the same color than the player:

                    // Increment the number of tokens deleted in a row
                    score_incrementer.addHit();

                    // Delete the token
                    m_boardGroup->boardManager()->deleteTile(loopPosition);

                    // At least you found one token
                    found = true;
                }
                else
                {
                    // If we found a token, but it is from another color:

                    // Change the type of the player to this new one and
                    // change the type of the token for the previous type of the
                    // player
                    m_boardGroup->boardManager()->swapTileData(
                        m_boardGroup->player()->boardPosition(), loopPosition);

                    DisplayLog::info("Player type changed to ",
                                     m_boardGroup->player()->value());

                    // Exit the loop
                    result = false;
                }
            }

            // Store the position of this last cosumed token
            lastTokenPosition = m_boardGroup->board2Scene(loopPosition);

            if (found)
            {
                DisplayLog::info("Tile with same color found");
                DisplayLog::info("Creating points to score");
                p_->createScoreIncrementPoints(*this, lastTokenPosition);
            }
            return result;
        });
    DisplayLog::info("Launching player");
    m_boardGroup->player()->launchAnimation(lastTokenPosition);
}

}  // namespace zoper
