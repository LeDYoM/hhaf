#include "highscoresdata.hpp"
#include <lib/core/serializer.hpp>
#include <mtypes/include/log.hpp>

namespace zoper
{
	using namespace lib;
	constexpr char hsfile[] = "hscores.txt";

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

	inline lib::SerializationStreamIn& operator>>(lib::SerializationStreamIn&ssi, HighScore &data)
	{
		ssi >> data.name;
		ssi >> data.score;
		return ssi;
	}

	inline lib::SerializationStreamOut& operator<<(lib::SerializationStreamOut&sso, const HighScore&data)
	{
		sso << data.name;
		sso << data.score;
		return sso;
	}
}