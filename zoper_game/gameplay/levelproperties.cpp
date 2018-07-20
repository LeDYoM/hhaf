#include "levelproperties.hpp"
#include <lib/core/host.hpp>
#include <lib/core/randomizer.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::core;

	LevelProperties::LevelProperties()
	{
        setLevel(0);
    }

    LevelProperties::~LevelProperties()
    {

    }

    void LevelProperties::setMode(GameMode gameMode)
    {
        m_gameMode = gameMode;
    }

	void LevelProperties::setLevel(const u32 level)
	{
		m_level = level;

		m_baseScore = 10 + m_level;

		if (m_level <= maxLevelWithProperties) {
			m_millisBetweenTokens = 2600 - (m_level * 100);
            m_stayCounter = ((m_gameMode == GameMode::Time)?
                                 180 + (m_level * 30)
                                :
                                 25 + (10 * m_level));
		} else {
			m_millisBetweenTokens = 50;
            m_stayCounter = ((m_gameMode == GameMode::Time)?
                                 1200
                               :
                                 400);
		}

        log_debug_info("Level set: ", currentLevel());
        log_debug_info("Millis between tokens: ", millisBetweenTokens());
        log_debug_info("Current base score: ", baseScore());
        log_debug_info("Seconds or tokensto next level: ", stayCounter());
	}

    Color LevelProperties::getBackgroundTileColor(vector2dst position, const bool isCenter) const
	{
		if (m_level <= maxLevelWithProperties) {
			if (isCenter) {
				if (m_level < 9) {
					if (m_level % 2) {
						return{ 10, 200, 50 };
					} else if (!(m_level % 3)) {
						return{ 255, 70, 200 };
					} else {
						return{ 255,100,100 };
					}
				} else {
					if (!(position.x % 2)) {
						return (m_level < 15) ? Color{ 128, 128, 128 } : Color{ 255, 100, 100 };
					} else {
						return ((m_level < 15) ? Color{ 225, 255, 255 } : Color{ 100, 200, 200 });
					}
				}
			}
			else {
				if (m_level < 2) {
					return colors::Black;
				}
				else if (m_level < 3) {
					return{ 255, 128, 0 };
				}
				else if (m_level < 5) {
					return{ 100, 128, 255 };
				}
				else if (m_level < 10) {
					if (m_level % 2) {
						return (position.x % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
					} else {
						return (position.y % 2) ? Color{ 0, 255, 255 } : Color{ 255, 100, 200 };
					}
				}
				else if (m_level < 15) {
					if (m_level % 2) {
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
				else if (m_level < maxLevelWithProperties) {
					const auto &rnd(host().randomizer());
					return Color(static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)));
				}
			}
		}
		return lib::scene::colors::Black;
	}
}
