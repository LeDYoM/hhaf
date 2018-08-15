#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP__
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>

#include "../gameshareddata.hpp"

namespace zoper
{
    using namespace lib;

	class LevelProperties
	{
	public:
		LevelProperties();
        virtual ~LevelProperties();
        void setMode(GameMode gameMode);
        void setLevel(const size_type level);

        inline size_t millisBetweenTokens() const { return m_millisBetweenTokens; }
        inline size_t baseScore() const { return m_baseScore; }
        inline size_t stayCounter() const { return m_stayCounter; }
        inline size_t currentLevel() const { return m_level; }
        static constexpr size_t maxLevelWithProperties{ 25u };
        scene::Color getBackgroundTileColor(vector2dst position, const bool isCenter) const;
	private:
        size_t m_level;
        size_t m_millisBetweenTokens;
        size_t m_baseScore;
        size_t m_stayCounter;
        GameMode m_gameMode;
	};
}

#endif
