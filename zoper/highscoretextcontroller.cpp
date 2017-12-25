#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "loaders/highscoresresources.hpp"

#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	HighScoreTextController::HighScoreTextController(SceneNode *parent, str name)
		: BaseClass{ parent, "HighScreTextController" } {}

	HighScoreTextController::~HighScoreTextController() = default;

	void HighScoreTextController::onCreated()
	{
		BaseClass::onCreated();

		m_normalFont = resourceManager().getResource<TTFont>("menu.mainFont", "resources/oldct.ttf");
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;
		m_normalCharacterSize = 72;

		// Request the high scores.
		HighScoresData hsData;
		hsData.read();

		Rectf32 textBox{ rectFromSize(scenePerspective().size()).setLeftTop({ 0,750 }).setSize({ 2000,4 * 150 }) };
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();
		tableSize.set({ 3, NumHighScore });

		for (auto i{ 0UL }; i < NumHighScore; ++i) {
			auto label(createNodeAt(vector2dst{ 0, i }, make_str("label", 0, i)));
			standarizeText(label->node());
			label->node()->text.set(make_str(i, "."));

			label = createNodeAt(vector2dst{ 1, i }, make_str("label", 1, i));
			standarizeText(label->node());
			label->node()->text.set(make_str("100000"));

			label = createNodeAt(vector2dst{ 2, i }, make_str("label", 2, i));
			standarizeText(label->node());
			label->node()->text.set(make_str("AAA"));
		}
	}

	void HighScoreTextController::standarizeText(const sptr<scene::nodes::NodeText> &ntext)
	{
		ntext->color = m_normalColor;
		ntext->font = m_normalFont;
		ntext->characterSize = m_normalCharacterSize;
	}
}
