#include "levelproperties.hpp"
#include <lib/core/randomizer.hpp>

namespace zoper
{
	LevelProperties::LevelProperties(const lib::u32 level)
	{
		setLevel(level);
	}

	void LevelProperties::setLevel(const lib::u32 level)
	{
		_level = level;

		_baseScore = 10 + _level;

		if (_level <= maxLevelWithProperties) {
			_millisBetweenTokens = 2600 - (_level * 100);
			_stayTime = 180 + (_level * 30);
			_stayTokens = 25 + (10 * _level);
		}
		else {
			_millisBetweenTokens = 250;
			_stayTime = 1200;
			_stayTokens = 400;
		}
	}

	lib::draw::Color LevelProperties::getBackgroundTileColor(const lib::u32 x, const lib::u32 y, const bool isCenter) const
	{
		if (_level <= maxLevelWithProperties)
		{
			if (isCenter) {
				if (_level < 9) {
					if (_level % 2) {
						return{ 10, 200, 50 };
					}
					else if (!(_level % 3)) {
						return{ 255, 70, 200 };
					}
					else {
						return{ 255,100,100 };
					}
				}
				else {
					if (!(x % 2)) {
						return (_level < 15) ? lib::draw::Color{ 128, 128, 128 } : lib::draw::Color{ 255, 100, 100 };
					}
					else {
						return ((_level < 15) ? lib::draw::Color{ 225, 255, 255 } : lib::draw::Color{ 100, 200, 200 });
					}
				}
			}
			else {
				if (_level < 2) {
					return lib::draw::colors::Black;
				}
				else if (_level < 3) {
					return{ 255, 128, 0 };
				}
				else if (_level < 5) {
					return{ 100, 128, 255 };
				}
				else if (_level < 10) {
					if (_level % 2) {
						return (x % 2) ? lib::draw::Color{ 0, 255, 255 } : lib::draw::Color{ 255, 100, 200 };
					}
					else {
						return (y % 2) ? lib::draw::Color{ 0, 255, 255 } : lib::draw::Color{ 255, 100, 200 };
					}
				}
				else if (_level < 15) {
					if (_level % 2) {
						if (x % 2) {
							return (y % 2) ? lib::draw::colors::White : lib::draw::Color{ 100,100,100 };
						}
						else {
							return (y % 2) ? lib::draw::Color{ 0, 128, 255 } : lib::draw::Color{ 10, 250, 100 };
						}
					}
					else {
						return (x % 2) ?
							((y % 2) ? lib::draw::Color{ 25,25,25 } : lib::draw::Color{ 10, 12, 250 }) :
							((y % 2) ? lib::draw::Color{ 250, 50, 10 } : lib::draw::Color{ 10, 200, 10 });
					}
				}
				else if (_level < maxLevelWithProperties)
				{
					return lib::draw::Color(static_cast<lib::u8>(_randomizer.getUInt(255, 0)),
						static_cast<lib::u8>(_randomizer.getUInt(255, 0)),
						static_cast<lib::u8>(_randomizer.getUInt(255, 0)));
				}
			}
		}
		return lib::draw::colors::Black;
	}
}