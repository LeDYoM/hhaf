#pragma once

#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP__
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/streams.hpp>

namespace zoper
{
	constexpr lib::u32 NumHighScore = 10;

	struct HighScore
	{
		lib::str name{};
		lib::u32 score{ 0 };
	};

	class HighScoresData
	{
	public:
		using HighScoresList = lib::array<HighScore, NumHighScore>;
		void read();
		void store();
	private:
		HighScoresList m_highScoreList;
	};

}

#endif
