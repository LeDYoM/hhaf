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

class TileHitChecker
{
public:
    explicit TileHitChecker(
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

    bool operator()(vector2dst const& loopPosition)
    {
        bool result{true};
        bool found{false};

        if (!board_group_.boardManager()->tileEmpty(loopPosition) &&
            TokenZones::toBoardBackgroundType(
                board_group_.boardManager()->backgroundData(loopPosition)) !=
                TokenZones::BoardBackgroundType::Center)
        {
            sptr<board::ITile> currentToken{
                board_group_.boardManager()->getTile(loopPosition)};
            auto const currentTokenType{currentToken->value()};

            if (currentTokenType == tokenType)
            {
                // If we found a token with the same color than the player:

                // Increment the number of tokens deleted in a row
                score_incrementer_.addHit();

                // Delete the token
                board_group_.boardManager()->deleteTile(loopPosition);

                // At least you found one token
                found = true;
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

        // Store the position of this last cosumed token
        lastTokenPosition_ = board_group_.board2Scene(loopPosition);

        if (found)
        {
            DisplayLog::info("Tile with same color found");
            DisplayLog::info("Creating points to score");
            createScoreIncrementPoints_(lastTokenPosition_);
        }
        return result;
    }

private:
    BoardGroup& board_group_;
    haf::board::ITile::BoardTileData tokenType;
    ScoreIncrementer& score_incrementer_;
    vector2df& lastTokenPosition_;
    function<void(vector2df)> createScoreIncrementPoints_;
};

void PlayerLauncher::operator()(
    ScoreIncrementer& score_incrementer,
    BoardGroup& board_group,
    htps::function<void(htps::vector2df)> createScoreIncrementPoints)
{
    haf::DisplayLog::info("Launching player");
    vector2df lastTokenPosition{};

    TileHitChecker tile_hit_checker{board_group, board_group.player()->value(),
                                    score_incrementer, lastTokenPosition,
                                    createScoreIncrementPoints};
    BoardUtils::for_each_coordinate_in_rect(
        board_group.player()->boardPosition(),
        board_group.player()->currentDirection(),
        board_group.boardManager()->size(), tile_hit_checker);

    DisplayLog::info("Launching player");
    board_group.player()->launchAnimation(lastTokenPosition);
}

}  // namespace zoper
