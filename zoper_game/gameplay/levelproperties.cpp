#include "levelproperties.hpp"
#include "gamescenedata.hpp"

#include <lib/core/host.hpp>
#include <lib/core/randomizer.hpp>
#include <lib/include/core/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::core;

    void LevelProperties::setUp(const size_type currentLevel,
        const GameMode gameMode, sptr<GameSceneData> gameSceneData,
        sptr<scene::TimerComponent> sceneTimerComponent)
    {
        assert_debug(m_sceneTimerComponent != nullptr, "Passed nullptr sceneTimerComponent");
        assert_debug(m_gameSceneData != nullptr, "Passed nullptr gameSceneData");

        m_gameMode = gameMode;
        m_gameSceneData.swap(gameSceneData);
        m_sceneTimerComponent.swap(sceneTimerComponent);

        m_updateLevelDataTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimeFromMillis(120),
            [this](Time realEllapsed) {
            updateLevelData();
        });

        setLevel(currentLevel);
    }

    void LevelProperties::setLevel(const LevelType currentLevel)
    {
        m_levelTimer.restart();

        m_currentLevel = currentLevel;
		m_baseScore = 10 + m_currentLevel;
        m_consumedTokens = 0U;

		if (m_currentLevel <= maxLevelWithProperties) 
        {
			m_millisBetweenTokens = 2600 - (m_currentLevel * 100);
            m_stayCounter = ((m_gameMode == GameMode::Time)?
                                 180 + (m_currentLevel * 30)
                                :
                                 25 + (10 * m_currentLevel));
		}
        else
        {
			m_millisBetweenTokens = 50;
            m_stayCounter = ((m_gameMode == GameMode::Time)?
                                 1200
                               :
                                 400);
		}

        levelChanged(currentLevel);
        updateGoals();
        updateLevelData();

        log_debug_info("Level set: ", m_currentLevel);
        log_debug_info("Millis between tokens: ", millisBetweenTokens());
        log_debug_info("Current base score: ", baseScore());
        log_debug_info("Seconds or tokensto next level: ", stayCounter());
	}

    void LevelProperties::tokenConsumed()
    {
        ++m_consumedTokens;
        updateLevelData();
    }

    void LevelProperties::updateGoals()
    {
        m_gameSceneData->m_scoreQuad->text(vector2dst{ 1,0 })->text.set(Text_t(make_str(m_currentLevel + 1)));
        m_gameSceneData->m_goalQuad->text(vector2dst{ 1,1 })->text.set(Text_t(make_str(m_stayCounter)));
    }

    void LevelProperties::updateLevelData()
    {
        switch (m_gameMode)
        {
        default:
        case GameMode::Token:
            m_gameSceneData->m_goalQuad->text(vector2dst{ 1,0 })->text.set(Text_t(m_consumedTokens));
            if (m_consumedTokens >= m_stayCounter)
                setLevel(m_currentLevel + 1);
            break;

        case GameMode::Time:
            m_gameSceneData->m_goalQuad->text(vector2dst{ 1,0 })->text.set(
                Text_t(static_cast<u16>(
                    m_levelTimer.ellapsed().asSeconds())));
            if (m_levelTimer.ellapsed().asSeconds() >= m_stayCounter)
                setLevel(m_currentLevel + 1);
            break;
        }
    }
}
