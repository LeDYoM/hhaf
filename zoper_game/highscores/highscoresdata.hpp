#pragma once

#ifndef ZOPER_HIGHSCORESDATA_INCLUDE_HPP__
#define ZOPER_HIGHSCORESDATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/streams.hpp>

namespace zoper
{
	using namespace lib;

	constexpr size_type NumHighScore = 10;
	using Score = size_type;

	struct HighScore
	{
		str name{};
		Score score{ 0 };
	};

	class HighScoresData
	{
	public:
		using HighScoresList = array<HighScore, NumHighScore>;
		HighScoresData();
		bool positionForScore(const Score score, size_type &positionInTable);
		bool tryInsertHighScore(const Score score, size_type &positionInTable);
		void setHighScoreName(const size_type positionInTable, const str&nName);
		void read();
		void store();
		const HighScore &operator[](const size_type index) const { return m_highScoreList[index]; }
		const HighScoresList &highScoresList() const noexcept { return m_highScoreList; }
	private:
		HighScoresList m_highScoreList;
	};

}

#endif
