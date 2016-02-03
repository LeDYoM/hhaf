#include "levelproperties.hpp"
#include <lib/core/randomizer.hpp>

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
			_stayTime = 1200;
			_stayTokens = 400;
		}
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
						return sf::Color(10, 200, 50);
					}
					else if (!(_level%3))
					{
						return sf::Color(255, 70, 200);
					}
					else
					{
						return sf::Color(255,100,100);
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
				if (_level < 2)
				{
					return sf::Color::Black;
				}
				else if (_level < 3)
				{
					return sf::Color(255, 128, 0);
				}
				else if (_level < 5)
				{
					return sf::Color(100, 128, 255);
				}
				else if (_level < 10)
				{
					if (_level % 2)
					{
						return (x % 2) ? sf::Color(0, 255, 255) : sf::Color(255, 100, 200);
					}
					else
					{
						return (y % 2) ? sf::Color(0, 255, 255) : sf::Color(255, 100, 200);
					}
				}
				else if (_level < 15)
				{
					if (_level % 2)
					{
						if (x % 2)
						{
							if (y % 2)
							{
								return sf::Color(255, 255, 255);
							}
							else
							{
								return sf::Color(100, 100, 100);
							}
						}
						else
						{
							if (y % 2)
							{
								return sf::Color(0, 128, 255);
							}
							else
							{
								return sf::Color(10, 250, 100);
							}
						}
					}
					else
					{
						if (x % 2)
						{
							if (y % 2)
							{
								return sf::Color(25, 25, 25);
							}
							else
							{
								return sf::Color(10, 12, 250);
							}
						}
						else
						{
							if (y % 2)
							{
								return sf::Color(250, 50, 10);
							}
							else
							{
								return sf::Color(10, 200, 10);
							}
						}
					}
				}
				else if (_level < maxLevelWithProperties)
				{
					return sf::Color(static_cast<lib::u8>(_randomizer.getUInt(255, 0)), 
						static_cast<lib::u8>(_randomizer.getUInt(255, 0)),
						static_cast<lib::u8>(_randomizer.getUInt(255, 0)));
				}

			}
		}
		return sf::Color::Black;
	}

}
