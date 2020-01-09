#include "levelproperties.hpp"

#include <lib/include/liblog.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::sys;

void LevelProperties::setUp(const size_type currentLevel,
                            const GameMode gameMode,
                            sptr<scene::TimerComponent> sceneTimerComponent)
{
    if (!m_levelTimer)
    {
        m_levelTimer = attachedNode()->dataWrapper<scene::Timer>();
    }
    log_assert(sceneTimerComponent != nullptr, "m_sceneNodeComponent already contains a value");
    log_assert(m_sceneTimerComponent == nullptr, "Passed nullptr sceneTimerComponent");

    m_gameMode = gameMode;
    m_sceneTimerComponent.swap(sceneTimerComponent);

    m_updateLevelDataTimer = m_sceneTimerComponent->addTimer(
        TimerType::Continuous,
        TimePoint_as_miliseconds(120),
        [this](TimePoint /*realEllapsed*/)
        {
            updateLevelData();
        });

    m_gameHud = attachedNode()->createSceneNode<GameHudSceneNode>("hud");

    m_currentScore = 0U;
    setLevel(currentLevel);
}

void LevelProperties::setLevel(const LevelType currentLevel)
{
    m_levelTimer->restart();

    m_currentLevel = currentLevel;
    m_baseScore = 10 + m_currentLevel;
    m_consumedTokens = 0U;

    if (m_currentLevel <= maxLevelWithProperties)
    {
        m_millisBetweenTokens = 1350 - (m_currentLevel * 50U);
        m_stayCounter = ((m_gameMode == GameMode::Time) ? 180 + (m_currentLevel * 30)
                                                        : 25 + (10 * m_currentLevel));
    }
    else
    {
        m_millisBetweenTokens = 50;
        m_stayCounter = ((m_gameMode == GameMode::Time) ? 1200
                                                        : 400);
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

void LevelProperties::increaseScore(const size_type scoreIncrement)
{
    m_currentScore += scoreIncrement;
    m_gameHud->setScore(m_currentScore);
}

void LevelProperties::nextLevel()
{
    setLevel(m_currentLevel + 1);
}

void LevelProperties::updateGameSharedData(sptr<GameSharedData> game_shared_data)
{
    game_shared_data->endLevel = m_currentLevel;
    game_shared_data->score = m_currentScore;
}

} // namespace zoper
