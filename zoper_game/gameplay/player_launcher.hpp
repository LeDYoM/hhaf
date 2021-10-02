#ifndef ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP
#define ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP

#include "direction.hpp"
#include "levelproperties.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"
#include "gamescene_states.hpp"

#include "player.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/scene/scene_types.hpp>

namespace zoper
{
class Player;
class ScoreIncrementer;
class BoardGroup;

class PlayerLauncher
{
public:
    void operator()(ScoreIncrementer& score_incrementer,
                    BoardGroup& board_group,
                    htps::function<void(haf::types::WorldCoord)>
                        createScoreIncrementPoints);
};
}  // namespace zoper

#endif
