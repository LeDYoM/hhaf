#ifndef __LEVELPROPERTIES_HPP__
#define __LEVELPROPERTIES_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/color.hpp>

namespace zoper
{
	class LevelProperties
	{
	public:
		LevelProperties();
		virtual ~LevelProperties() = default;

		void setLevel(const lib::u32 level);

		inline lib::u32 millisBetweenTokens() const { return m_millisBetweenTokens; }
		inline lib::u32 baseScore() const { return m_baseScore; }
		inline lib::u32 stayTime() const { return m_stayTime; }
		inline lib::u32 currentLevel() const { return m_level; }
		inline lib::u32 stayTokens() const { return m_stayTokens; }
		static constexpr lib::u32 maxLevelWithProperties{ 25u };
		lib::scene::Color getBackgroundTileColor(const lib::u32 x, const lib::u32 y, const bool isCenter) const;
	private:
		lib::u32 m_level;
		lib::u32 m_millisBetweenTokens;
		lib::u32 m_baseScore;
		lib::u32 m_stayTime;
		lib::u32 m_stayTokens;
	};
}

#endif
