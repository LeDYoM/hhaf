#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include <lib/scene/nodes/textgroup.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	HighScoreTextController::HighScoreTextController(SceneNode *parent, sptr<scene::TTFont> font, const u32 characterSize)
		: SceneNode{ parent, "HighScreTextController" }, m_font{ std::move(font) }, m_characterSize{ characterSize } {}
	HighScoreTextController::~HighScoreTextController() = default;

	void HighScoreTextController::create()
	{
		ParentClassType::create();

		// Request the highscores.
		HighScoresData hsData;
		hsData.read();
		
		m_textGroup = createSceneNode<nodes::TextGroup>("HighScoresTextGroup");
		m_textGroup->characterSize = m_characterSize;
		m_textGroup->font = m_font;
		m_textGroup->color = colors::Green;
		m_textGroup->position = { 200,200 };
		m_textGroup->addText("Example1");
		m_textGroup->addText("Example2");
	}
}
