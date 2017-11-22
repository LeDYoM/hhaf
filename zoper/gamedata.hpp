#pragma once

#ifndef ZOPER_GAMEDATA_INCLUDE_HPP__
#define ZOPER_GAMEDATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/streams.hpp>
#include <lib/core/timer.hpp>

#include "direction.hpp"

namespace zoper
{
	using namespace lib;
	constexpr size_type NumWays = 4;

	enum class GameMode : u8
	{
		Token = 0,
		Time = 1,
	};

	class GameData
	{
	public:
		GameData();
		virtual ~GameData();

		struct TokenZone
		{
			Rectu32 zone;
			Direction direction;
			size_type size;
		};

		vector2du32 size{ 18,12 };
		Rectu32 centerRect{ 7,4,4,4 };

		array<TokenZone, NumWays> tokenZones;

		Timer levelClock;
		u32 consumedTokens{ 0 };

		GameMode gameMode{ GameMode::Token };
		u32 startLevel{ 0 };
		u32 score{ 0 };

        class StartGameData
        {
        public:
            bool exitGame{ false };
            GameMode gameMode{ GameMode::Token };
            u32 startLevel{ 0 };
        };

        StartGameData startGameData;
		void generateTokenZones();
	};
}

#endif
