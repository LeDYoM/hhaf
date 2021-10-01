#ifndef ZOOPER_TOKEN_HIT_LAUNCHER_INCLUDE_HPP
#define ZOOPER_TOKEN_HIT_LAUNCHER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>

#include <boardmanager/include/itile.hpp>

namespace zoper
{
class ScoreIncrementer;
class BoardGroup;

class TileHitChecker
{
public:
    TileHitChecker(
        BoardGroup& board_group,
        haf::board::ITile::BoardTileData token_type,
        ScoreIncrementer score_incrementer,
        htps::vector2df& lastTokenPosition,
        htps::function<void(htps::vector2df)> createScoreIncrementPoints);

    bool operator()(htps::vector2dst const& loopPosition);

private:
    BoardGroup& board_group_;
    haf::board::ITile::BoardTileData tokenType;
    ScoreIncrementer& score_incrementer_;
    htps::vector2df& lastTokenPosition_;
    htps::function<void(htps::vector2df)> createScoreIncrementPoints_;
};
}  // namespace zoper

#endif
