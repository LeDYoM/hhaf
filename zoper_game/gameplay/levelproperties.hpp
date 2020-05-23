#pragma once

#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <haf/time/include/timercomponent.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/scene/include/color.hpp>

#include "../gameshareddata.hpp"
#include "gamehud.hpp"

namespace zoper
{
using namespace haf;

using LevelType = mtps::size_type;

class LevelProperties : public haf::scene::IComponent
{
public:
    void configure(const mtps::size_type currentLevel,
               const GameMode gameMode,
               mtps::sptr<time::TimerComponent> scene_timer_component);

    inline size_t millisBetweenTokens() const noexcept { return millis_between_tokens_; }
    inline size_t baseScore() const noexcept { return base_score_; }
    inline size_t stayCounter() const noexcept { return stay_counter_; }
    inline LevelType currentLevel() const noexcept { return current_level_; }
    void increaseScore(const mtps::size_type scoreIncrement);
    void nextLevel();
    static constexpr size_t maxLevelWithProperties{25U};

    void tokenConsumed();
    mtps::emitter<const LevelType> levelChanged;

private:
    void updateGoals();
    void updateLevelData();
    void setLevel(const LevelType currentLevel);
    void setScore(const mtps::size_type new_score);

    mtps::uptr<time::Timer> level_timer_;
    time::TimerConnectorSPtr update_levelData_timer_;
    mtps::sptr<time::TimerComponent> scene_timerComponent_;

    mtps::size_type consumed_tokens_{0U};
    LevelType current_level_{0U};
    mtps::size_type millis_between_tokens_{0U};
    mtps::size_type base_score_{0U};
    mtps::size_type stay_counter_{0U};
    mtps::size_type current_score_{0U};
    GameMode game_mode_;
    mtps::sptr<GameHudSceneNode> game_hud_;
};
} // namespace zoper

#endif
