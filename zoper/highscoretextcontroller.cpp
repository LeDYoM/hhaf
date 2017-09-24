#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include <lib/scene/nodes/textgroup.hpp>

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
		
		textGroup()->characterSize = 30;
		addText("Example1");
		addText("Example2");

	}
}
