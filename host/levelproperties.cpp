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

	void LevelProperties::setLevel(const lib::u32 level)
	{
		m_level = level;

		m_baseScore = 10 + m_level;

		if (m_level <= maxLevelWithProperties) {
			m_millisBetweenTokens = 2600 - (m_level * 100);
			m_stayTime = 180 + (m_level * 30);
			m_stayTokens = 25 + (10 * m_level);
		}
		else {
			m_millisBetweenTokens = 250;
			m_stayTime = 1200;
			m_stayTokens = 400;
		}
	}

	Color LevelProperties::getBackgroundTileColor(const u32 x, const u32 y, const bool isCenter) const
	{
		if (m_level <= maxLevelWithProperties)
		{
			if (isCenter) {
				if (m_level < 9) {
					if (m_level % 2) {
						return{ 10, 200, 50 };
					}
					else if (!(m_level % 3)) {
						return{ 255, 70, 200 };
					}
					else {
						return{ 255,100,100 };
					}
				}
				else {
					if (!(x % 2)) {
						return (m_level < 15) ? lib::scene::Color{ 128, 128, 128 } : lib::scene::Color{ 255, 100, 100 };
					}
					else {
						return ((m_level < 15) ? lib::scene::Color{ 225, 255, 255 } : lib::scene::Color{ 100, 200, 200 });
					}
				}
			}
			else {
				if (m_level < 2) {
					return lib::scene::colors::Black;
				}
				else if (m_level < 3) {
					return{ 255, 128, 0 };
				}
				else if (m_level < 5) {
					return{ 100, 128, 255 };
				}
				else if (m_level < 10) {
					if (m_level % 2) {
						return (x % 2) ? lib::scene::Color{ 0, 255, 255 } : lib::scene::Color{ 255, 100, 200 };
					}
					else {
						return (y % 2) ? lib::scene::Color{ 0, 255, 255 } : lib::scene::Color{ 255, 100, 200 };
					}
				}
				else if (m_level < 15) {
					if (m_level % 2) {
						if (x % 2) {
							return (y % 2) ? lib::scene::colors::White : lib::scene::Color{ 100,100,100 };
						}
						else {
							return (y % 2) ? lib::scene::Color{ 0, 128, 255 } : lib::scene::Color{ 10, 250, 100 };
						}
					}
					else {
						return (x % 2) ?
							((y % 2) ? lib::scene::Color{ 25,25,25 } : lib::scene::Color{ 10, 12, 250 }) :
							((y % 2) ? lib::scene::Color{ 250, 50, 10 } : lib::scene::Color{ 10, 200, 10 });
					}
				}
				else if (m_level < maxLevelWithProperties)
				{
					const auto &rnd(host().randomizer());
					return lib::scene::Color(static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)),
						static_cast<lib::u8>(rnd.getUInt(255, 0)));
				}
			}
		}
		return lib::scene::colors::Black;
	}
}