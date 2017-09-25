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
		
		textGroup()->characterSize = m_characterSize;
		textGroup()->font = m_font;
		addText("Example1");
		addText("Example2");

	}
}
