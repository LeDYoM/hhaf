#ifndef ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP
#define ZOOPER_PLAYER_LAUNCHER__INCLUDE_HPP

#include "direction.hpp"
#include "levelproperties.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"
#include "gamescene_states.hpp"

#include "player.hpp"

namespace zoper
{
class Player;
class ScoreIncrementer;
class BoardGroup;

class PlayerLauncher
{
public:
    void operator()(Player& player,
                    ScoreIncrementer& score_incrementer,
                    BoardGroup& board_group);
};
}  // namespace zoper

#endif
