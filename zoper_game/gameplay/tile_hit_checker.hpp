#ifndef ZOOPER_TILE_HIT_LAUNCHER_INCLUDE_HPP
#define ZOOPER_TILE_HIT_LAUNCHER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/scene_types.hpp>
#include <boardmanager/include/itile.hpp>
#include <boardmanager/include/board_types.hpp>

namespace zoper
{
class ScoreIncrementer;
class BoardGroup;

class TileHitChecker
{
public:
    TileHitChecker(haf::types::sptr<BoardGroup> board_group,
                   haf::board::ITile::BoardTileData token_type,
                   ScoreIncrementer& score_incrementer,
                   haf::SceneCoordinates& lastTokenPosition,
                   haf::function<void(haf::board::BoardPositionType)>
                       createScoreIncrementPoints);

    bool operator()(haf::board::BoardPositionType const& loopPosition);

private:
    haf::types::sptr<BoardGroup> board_group_;
    haf::board::ITile::BoardTileData const tokenType;
    ScoreIncrementer& score_incrementer_;
    haf::SceneCoordinates& last_token_position_;
    htps::function<void(haf::board::BoardPositionType)>
        createScoreIncrementPoints_;
};
}  // namespace zoper

#endif
