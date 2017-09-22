#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	HighScoreTextController::HighScoreTextController() = default;
	HighScoreTextController::~HighScoreTextController() = default;

	void HighScoreTextController::onAttached()
	{
		ParentClassType::onAttached();

		// Request the highscores.
		HighScoresData hsData;
		hsData.read();
		
		add
	}
}
