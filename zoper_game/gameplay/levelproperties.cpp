#include "levelproperties.hpp"
#include "../gameshareddata.hpp"

#include <lib/include/liblog.hpp>
#include <lib/shareddata/include/shareddataview.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::sys;

void LevelProperties::configure(const mtps::size_type currentLevel,
                                const GameMode gameMode,
                                mtps::sptr<time::TimerComponent> sceneTimerComponent)
{
    using namespace time;

    if (!m_levelTimer)
    {
        m_levelTimer = attachedNode()->dataWrapper<Timer>();
    }
    log_assert(sceneTimerComponent != nullptr, "m_sceneNodeComponent already contains a value");
    log_assert(m_sceneTimerComponent == nullptr, "Passed nullptr sceneTimerComponent");

    m_gameMode = gameMode;
    m_sceneTimerComponent.swap(sceneTimerComponent);

    m_updateLevelDataTimer = m_sceneTimerComponent->addTimer(
        TimerType::Continuous,
        TimePoint_as_miliseconds(120),
        [this](TimePoint /*realEllapsed*/) {
            updateLevelData();
        });

    m_gameHud = attachedNode()->createSceneNode<GameHudSceneNode>("hud");

    setScore(0U);
    setLevel(currentLevel);
}

void LevelProperties::setScore(const mtps::size_type new_score)
{
    m_currentScore = new_score;
    auto game_shared_data_view = attachedNode()->dataWrapper<shdata::SharedDataView>();
    auto game_shared_data = game_shared_data_view->dataAs<GameSharedData>().score = m_currentScore;
    m_gameHud->setScore(m_currentScore);
}

void LevelProperties::setLevel(const LevelType currentLevel)
{
    m_levelTimer->restart();

    m_currentLevel = currentLevel;

    {
        auto game_shared_data_view = attachedNode()->dataWrapper<shdata::SharedDataView>();
        game_shared_data_view->dataAs<GameSharedData>().endLevel = m_currentLevel;
    }

    m_baseScore = 2U * m_currentLevel;
    m_consumedTokens = 0U;

    if (m_currentLevel <= maxLevelWithProperties)
    {
        m_millisBetweenTokens = 1350U - (m_currentLevel * 50U);
        m_stayCounter = ((m_gameMode == GameMode::Time) ? 180U + (m_currentLevel * 30U)
                                                        : 25U + (10U * m_currentLevel));
    }
    else
    {
        m_millisBetweenTokens = 50;
        m_stayCounter = ((m_gameMode == GameMode::Time) ? 1200U
                                                        : 400U);
    }

    levelChanged(currentLevel);
    updateGoals();
    updateLevelData();
    increaseScore(0U);

    DisplayLog::info("Level set: ", m_currentLevel);
    DisplayLog::info("Millis between tokens: ", millisBetweenTokens());
    DisplayLog::info("Current base score: ", baseScore());
    DisplayLog::info("Seconds or tokens to next level: ", stayCounter());
}

void LevelProperties::tokenConsumed()
{
    ++m_consumedTokens;
    updateLevelData();
}

void LevelProperties::updateGoals()
{
    m_gameHud->setLevel(m_currentLevel);
    m_gameHud->setStayCounter(m_stayCounter);
}

void LevelProperties::updateLevelData()
{
    switch (m_gameMode)
    {
    default:
    case GameMode::Token:
        m_gameHud->setConsumedTokens(m_consumedTokens);

        if (m_consumedTokens >= m_stayCounter)
        {
            nextLevel();
        }
        break;

    case GameMode::Time:
        m_gameHud->setEllapsedTimeInSeconds(m_levelTimer->ellapsed().seconds());

        if (m_levelTimer->ellapsed().seconds() >= m_stayCounter)
        {
            nextLevel();
        }
        break;
    }
}

void LevelProperties::increaseScore(const mtps::size_type scoreIncrement)
{
    setScore(m_currentScore + scoreIncrement);
}

void LevelProperties::nextLevel()
{
    setLevel(m_currentLevel + 1);
}

} // namespace zoper
