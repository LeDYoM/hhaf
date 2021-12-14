#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <haf/include/time/timerconnector.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/scene/color.hpp>

#include "../gameshareddata.hpp"
#include "gamehud.hpp"

namespace zoper
{
using namespace haf;

using LevelType = htps::size_type;

class LevelProperties : public haf::component::IComponent
{
public:
    void configure(htps::size_type const currentLevel,
                   GameMode const gameMode,
                   htps::sptr<time::TimerComponent> scene_timer_component);

    htps::size_type millisBetweenTokens() const;
    htps::size_type baseScore() const noexcept { return base_score_; }
    htps::size_type stayCounter() const noexcept { return stay_counter_; }
    LevelType currentLevel() const noexcept { return current_level_; }
    void increaseScore(const htps::size_type scoreIncrement);
    void nextLevel();
    static constexpr size_t maxLevelWithProperties{25U};

    void tokenConsumed();
    htps::emitter<const LevelType> levelChanged;

private:
    void updateGoals();
    void updateLevelData();
    void setLevel(LevelType const currentLevel);
    void setScore(htps::size_type const new_score);

    time::TimerConnectorSPtr level_timer_;
    time::TimerConnectorSPtr update_level_data_timer_;
    htps::sptr<time::TimerComponent> scene_timer_component_;

    htps::size_type consumed_tokens_{0U};
    LevelType current_level_{0U};
    htps::size_type millis_between_tokens_{0U};
    htps::size_type base_score_{0U};
    htps::size_type stay_counter_{0U};
    htps::size_type current_score_{0U};
    GameMode game_mode_;
    htps::sptr<GameHudSceneNode> game_hud_;
};
}  // namespace zoper

#endif
