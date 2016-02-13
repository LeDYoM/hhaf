#ifndef __LEVELPROPERTIES_HPP__
#define __LEVELPROPERTIES_HPP__

#include <lib/include/types.hpp>
#include <lib/core/randomizer.hpp>
#include <SFML/Graphics/Color.hpp>

namespace zoper
{
	class LevelProperties
	{
	public:
		LevelProperties(const lib::u32 level = 0);
		virtual ~LevelProperties();

		void setLevel(const lib::u32 level);

		inline lib::u32 millisBetweenTokens() const { return _millisBetweenTokens; }
		inline lib::u32 baseScore() const { return _baseScore; }
		inline lib::u32 stayTime() const { return _stayTime; }
		inline lib::u32 currentLevel() const { return _level; }
		inline lib::u32 stayTokens() const { return _stayTokens; }
		const lib::u32 maxLevelWithProperties{ 25u };
		const sf::Color getBackgroundTileColor(const lib::u32 x, const lib::u32 y, const bool isCenter) const;
	private:
		lib::Randomizer _randomizer;
		lib::u32 _level;
		lib::u32 _millisBetweenTokens;
		lib::u32 _baseScore;
		lib::u32 _stayTime;
		lib::u32 _stayTokens;
	};
}

#endif
