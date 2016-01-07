#include "levelproperties.hpp"

namespace zoper
{
	LevelProperties::LevelProperties(const lib::u32 level)
	{
		setLevel(level);
	}


	LevelProperties::~LevelProperties()
	{
	}

	void LevelProperties::setLevel(const lib::u32 level)
	{
		_level = level;

		_baseScore = 10 + _level;

		if (_level <= maxLevelWithProperties)
		{
			_millisBetweenTokens = 2600 - (_level * 100);
			_stayTime = 180 + (_level * 30);
			_stayTokens = 25 + (10 * _level);
		}
		else
		{
			_millisBetweenTokens = 250;
			_stayTime = 12000;
			_stayTokens = 400;
		}
		_millisBetweenTokens = 250;
		_stayTokens = 1;
	}

	const sf::Color LevelProperties::getBackgroundTileColor(const lib::u32 x, const lib::u32 y, const bool isCenter) const
	{
		if (_level <= maxLevelWithProperties)
		{
			if (isCenter)
			{
				if (_level < 9)
				{
					if (_level%2)
					{
						return sf::Color::Green;
					}
					else if (!(_level%3))
					{
						return sf::Color(255, 70, 200);
					}
					else
					{
						return sf::Color::Red;
					}
				}
				else
				{
					if (!(x % 2))
					{
						if (_level < 15)
						{
							return sf::Color(128, 128, 128);
						}
						else
						{
							return sf::Color(255, 100, 100);
						}
					}
					else
					{
						if (_level < 15)
						{
							return sf::Color(225, 255, 255);
						}
						else
						{
							return sf::Color(100, 200, 200);
						}
					}
				}
			}
			else
			{
				return sf::Color::Black;
			}
		}
		return sf::Color::Black;
	}

}
