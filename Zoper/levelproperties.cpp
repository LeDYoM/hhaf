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

		if (_level >= maxLevelWithProperties)
		{
			_millisBetweenTokens = 2600 - (_level * 100);
			_stayTime = 180 + (_level * 30);
			_stayTokens = 25 + (10 * _level);
		}
		else
		{
			_millisBetweenTokens = 50;
			_stayTime = 12000;
			_stayTokens = 400;
		}
	}

}
