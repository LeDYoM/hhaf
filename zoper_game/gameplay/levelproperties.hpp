#ifndef __LEVELPROPERTIES_HPP__
#define __LEVELPROPERTIES_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>

namespace zoper
{
    using namespace lib;

	class LevelProperties
	{
	public:
		LevelProperties();
		virtual ~LevelProperties() = default;

        void setLevel(const u32 level);

        inline u32 millisBetweenTokens() const { return m_millisBetweenTokens; }
        inline u32 baseScore() const { return m_baseScore; }
        inline u32 stayTime() const { return m_stayTime; }
        inline u32 currentLevel() const { return m_level; }
        inline u32 stayTokens() const { return m_stayTokens; }
        static constexpr u32 maxLevelWithProperties{ 25u };
        scene::Color getBackgroundTileColor(vector2dst position, const bool isCenter) const;
	private:
        u32 m_level;
        u32 m_millisBetweenTokens;
        u32 m_baseScore;
        u32 m_stayTime;
        u32 m_stayTokens;
	};
}

#endif
