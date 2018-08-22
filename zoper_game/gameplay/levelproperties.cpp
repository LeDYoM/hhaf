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
        m_gameMode = gameMode;
        m_gameSceneData.swap(gameSceneData);
        m_sceneTimerComponent.swap(sceneTimerComponent);

        assert_debug(m_sceneTimerComponent != nullptr, "Passed nullptr sceneTimerComponent");
        assert_debug(m_gameSceneData != nullptr, "Passed nullptr gameSceneData");

        m_updateLevelDataTimer = m_sceneTimerComponent->addTimer(
            TimerType::Continuous,
            TimeFromMillis(120),
            [this](Time realEllapsed) {
            updateLevelData();
        });

        setLevel(currentLevel);
    }

    void LevelProperties::setLevel(const size_type currentLevel)
    {
		m_baseScore = 10 + currentLevel;

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

        updateGoals();
        updateLevelData();

        log_debug_info("Level set: ", m_currentLevel);
        log_debug_info("Millis between tokens: ", millisBetweenTokens());
        log_debug_info("Current base score: ", baseScore());
        log_debug_info("Seconds or tokensto next level: ", stayCounter());
	}

    Color LevelProperties::getBackgroundTileColor(vector2dst position, const bool isCenter) const
	{
		if (m_currentLevel <= maxLevelWithProperties) 
        {
			if (isCenter) {
				if (m_currentLevel < 9) {
					if (m_currentLevel % 2) {
						return{ 10, 200, 50 };
					} else if (!(m_currentLevel % 3)) {
						return{ 255, 70, 200 };
					} else {
						return{ 255,100,100 };
					}
				} else {
					if (!(position.x % 2)) {
						return (m_currentLevel < 15) ? Color{ 128, 128, 128 } : Color{ 255, 100, 100 };
					} else {
						return ((m_currentLevel < 15) ? Color{ 225, 255, 255 } : Color{ 100, 200, 200 });
					}
				}
			}
			else 
            {
				if (m_currentLevel < 2) {
					return colors::Black;
				}
				else if (m_currentLevel < 3) {
					return{ 255, 128, 0 };
				}
				else if (m_currentLevel < 5) {
					return{ 100, 128, 255 };
				}
				else if (m_currentLevel < 10) {
					if (m_currentLevel % 2) {
						return (position.x % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
					} else {
						return (position.y % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
					}
				}
				else if (m_currentLevel < 15) {
					if (m_currentLevel % 2) {
						if (position.x % 2) {
							return (position.y % 2) ? colors::White : Color{ 100,100,100 };
						} else {
							return (position.y % 2) ? Color{ 0, 128, 255 } : Color{ 10, 250, 100 };
						}
					}
					else {
						return (position.x % 2) ?
							((position.y % 2) ? Color{ 25,25,25 } : Color{ 10, 12, 250 }) :
							((position.y % 2) ? Color{ 250, 50, 10 } : Color{ 10, 200, 10 });
					}
				}
				else if (m_currentLevel < maxLevelWithProperties) {
					const auto &rnd(host().randomizer());
					return Color(static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)));
				}
			}
		}
		return lib::scene::colors::Black;
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
                    m_levelTimer.getElapsedTime().asSeconds())));
            if (m_levelTimer.getElapsedTime().asSeconds() >= m_stayCounter)
                setLevel(m_currentLevel + 1);
            break;
        }
    }
}
