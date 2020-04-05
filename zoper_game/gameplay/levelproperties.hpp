#pragma once

#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/time/include/timercomponent.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/scene/include/color.hpp>

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
               mtps::sptr<time::TimerComponent> m_sceneTimerComponent);

    inline size_t millisBetweenTokens() const { return m_millisBetweenTokens; }
    inline size_t baseScore() const { return m_baseScore; }
    inline size_t stayCounter() const { return m_stayCounter; }
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

    mtps::uptr<time::Timer> m_levelTimer;
    time::TimerConnectorSPtr m_updateLevelDataTimer;
    mtps::sptr<time::TimerComponent> m_sceneTimerComponent;

    mtps::size_type m_consumedTokens{0U};
    LevelType m_currentLevel{0U};
    mtps::size_type m_millisBetweenTokens{0U};
    mtps::size_type m_baseScore{0U};
    mtps::size_type m_stayCounter{0U};
    mtps::size_type m_currentScore{0U};
    GameMode m_gameMode;
    mtps::sptr<GameHudSceneNode> m_gameHud;
};
} // namespace zoper

#endif
