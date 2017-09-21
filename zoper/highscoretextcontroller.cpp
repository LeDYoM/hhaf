#include "highscoretextcontroller.hpp"

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

	}
}
