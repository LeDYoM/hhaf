#pragma once

#ifndef ZOPER_LEVELPROPERTIES_INCLUDE_HPP
#define ZOPER_LEVELPROPERTIES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/color.hpp>

#include "../gameshareddata.hpp"

namespace zoper
{
    using namespace lib;

    class GameSceneData;

	class LevelProperties
	{
	public:
        void setGameData(const size_type currentLevel, const GameMode gameMode, sptr<GameSceneData> gameSceneData);

        inline size_t millisBetweenTokens() const { return m_millisBetweenTokens; }
        inline size_t baseScore() const { return m_baseScore; }
        inline size_t stayCounter() const { return m_stayCounter; }
        static constexpr size_t maxLevelWithProperties{ 25U };
        scene::Color getBackgroundTileColor(vector2dst position, const bool isCenter) const;

        size_type m_consumedTokens{ 0U };
	private:
        void updateGoals();
        void updateLevelData();

        size_type m_currentLevel{ 0U };
        size_t m_millisBetweenTokens{ 0U };
        size_t m_baseScore{ 0U };
        size_t m_stayCounter{ 0U };
        GameMode m_gameMode;
        sptr<GameSceneData> m_gameSceneData;
    };
}

#endif
