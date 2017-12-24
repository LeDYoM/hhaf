#pragma once

#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP__
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/streams.hpp>

namespace zoper
{
	using namespace lib;

	constexpr u32 NumHighScore = 10;

	struct HighScore
	{
		str name{};
		u32 score{ 0 };
	};

	class HighScoresData
	{
	public:

		using HighScoresList = array<HighScore, NumHighScore>;
		void read();
		void store();
	private:
		HighScoresList m_highScoreList;
	};

}

#endif
