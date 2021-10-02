#ifndef ZOOPER_TILE_HIT_LAUNCHER_INCLUDE_HPP
#define ZOOPER_TILE_HIT_LAUNCHER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/function.hpp>
#include <haf/include/scene/scene_types.hpp>

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
        ScoreIncrementer& score_incrementer,
        htps::vector2df& lastTokenPosition,
        haf::function<void(haf::types::WorldCoord)> createScoreIncrementPoints);

    bool operator()(htps::vector2dst const& loopPosition);

private:
    BoardGroup& board_group_;
    haf::board::ITile::BoardTileData const tokenType;
    ScoreIncrementer& score_incrementer_;
    htps::vector2df& last_token_position_;
    htps::function<void(htps::vector2df)> createScoreIncrementPoints_;
};
}  // namespace zoper

#endif
