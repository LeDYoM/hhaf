#ifndef ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP
#define ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP

#include <htypes/include/types.hpp>

#include "direction.hpp"
#include "levelproperties.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"
#include "gamescene_states.hpp"

#include "player.hpp"

#include <boardmanager/include/board_types.hpp>

namespace zoper
{
class Player;
class ScoreIncrementer;
class BoardGroup;

class PlayerLauncher
{
public:
    void operator()(ScoreIncrementer& score_incrementer,
                    htps::sptr<BoardGroup> board_group,
                    htps::function<void(haf::board::BoardPositionType)>
                        createScoreIncrementPoints);
};
}  // namespace zoper

#endif
