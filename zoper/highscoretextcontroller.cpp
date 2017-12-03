#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "loaders/highscoresresources.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	HighScoreTextController::HighScoreTextController(SceneNode *parent, str name)
		: BaseClass{ parent, "HighScreTextController" } {}

	HighScoreTextController::~HighScoreTextController() = default;

	void HighScoreTextController::create()
	{
		BaseClass::create();

		// Request the high scores.
		HighScoresData hsData;
		hsData.read();
/*		
		m_textGroup = createSceneNode<nodes::TextGroup>("HighScoresTextGroup");
		m_textGroup->characterSize = 36;
		m_textGroup->font = m_resources->mainFont;
		m_textGroup->color = colors::Green;
		m_textGroup->position = { 200,200 };
		m_textGroup->addText("Example1");
		m_textGroup->addText("Example2");
		*/
	}
}
