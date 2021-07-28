#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <haf/include/time/timercomponent.hpp>
#include <haf/include/components/icomponent.hpp>
#include <haf/include/scene/color.hpp>

#include "../gameshareddata.hpp"
#include "gamehud.hpp"

namespace zoper
{
using namespace haf;

using LevelType = htps::size_type;

class LevelProperties : public haf::scene::IComponent
{
public:
    void configure(const htps::size_type currentLevel,
                   const GameMode gameMode,
                   htps::sptr<time::TimerComponent> scene_timer_component);

    htps::size_type millisBetweenTokens() const;
    inline size_t baseScore() const noexcept { return base_score_; }
    inline size_t stayCounter() const noexcept { return stay_counter_; }
    inline LevelType currentLevel() const noexcept { return current_level_; }
    void increaseScore(const htps::size_type scoreIncrement);
    void nextLevel();
    static constexpr size_t maxLevelWithProperties{25U};

    void tokenConsumed();
    htps::emitter<const LevelType> levelChanged;

private:
    void updateGoals();
    void updateLevelData();
    void setLevel(const LevelType currentLevel);
    void setScore(const htps::size_type new_score);

    htps::uptr<time::Timer> level_timer_;
    time::TimerConnectorSPtr update_levelData_timer_;
    htps::sptr<time::TimerComponent> scene_timerComponent_;

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
