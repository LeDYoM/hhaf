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
	constexpr lib::u32 NumWays = 4;

	class GameData
	{
	public:
		GameData();
		virtual ~GameData();

		struct TokenZone
		{
			lib::Rectu32 zone;
			Direction direction;
			lib::u32 size;
		};

		lib::vector2du32 size{ 18,12 };
		lib::Rectu32 centerRect{ 7,4,4,4 };

		lib::array<TokenZone, NumWays> tokenZones;

		lib::Timer levelClock;
		lib::u32 consumedTokens{ 0 };

		lib::s32 gameMode{ 0 };
		lib::u32 startLevel{ 0 };
		lib::u32 score{ 0 };

		enum GameModes : lib::u8
		{
			Token = 0,
			Time = 1,
		} _gameMode{ Token };

		void generateTokenZones();
	};

}

#endif
