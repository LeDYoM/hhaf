#include "highscoresdata.hpp"
#include <lib/core/serializer.hpp>
#include <mtypes/include/log.hpp>

namespace zoper
{
	using namespace lib;
	constexpr char hsfile[] = "hscores.txt";

	HighScoresData::HighScoresData()
	{
		size_type counter{ 1 };
		for (auto &element : m_highScoreList) {
			element.name = "AAA";
			element.score = counter * 100;
			++counter;
		}
	}

	bool HighScoresData::positionForScore(const Score score, size_type & positionInTable)
	{
		for (u32 i{ 0U }; i < NumHighScore; ++i) {
			if (score > m_highScoreList[i].score) {
				positionInTable = i;
				return true;
			}
		}
		return false;
	}

	bool HighScoresData::tryInsetHighScore(const Score score, size_type &positionInTable)
	{
		if (positionForScore(score, positionInTable)) {
			m_highScoreList.insert(positionInTable, { "",score });
			return true;
		}
		return false;
	}

	void HighScoresData::read()
	{
		log_debug_info("Reading high scores files...");
		Serializer<HighScoresList> sHScoreList;
		sHScoreList.deserialize(hsfile, m_highScoreList);
	}

	void HighScoresData::store()
	{
		log_debug_info("Writing high scores file");
		Serializer<HighScoresList> sHScoreList;
		sHScoreList.serialize(hsfile, m_highScoreList);
	}

	inline SerializationStreamIn& operator>>(SerializationStreamIn&ssi, HighScore &data)
	{
		ssi >> data.name;
		ssi >> data.score;
		return ssi;
	}

	inline SerializationStreamOut& operator<<(SerializationStreamOut&sso, const HighScore&data)
	{
		sso << data.name;
		sso << data.score;
		return sso;
	}
}