#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "highscorevalidator.hpp"
#include "../loaders/highscoresresources.hpp"
#include "../gameshareddata.hpp"
#include "../zoperprogramcontroller.hpp"

#include <lib/scene/components/texteditorcomponent.hpp>
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

        m_normalFont = parentScene()->sceneManager().host().resourceManager().getResource<TTFont>
                       ("menu.mainFont")->font(72);
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;

		// Request the high scores.
		m_hsData.read();

		// Request game score
		Score gameScore = app<ZoperProgramController>().gameSharedData->score;

		Rectf32 textBox{ rectFromSize(scenePerspective().size()).setLeftTop({ 0,250 }).setSize({ 2000, 1500 }) };
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();
        setTableSize({ 3, NumHighScore });

		size_type positionInTable;
		const bool isInserting{ m_hsData.tryInsertHighScore(gameScore, positionInTable) };
		{
			size_type counter{ 0 };
			for (const auto &element : m_hsData.highScoresList()) {
				auto label(createNodeAt(vector2dst{ 0, counter }, make_str("label", 0, counter)));
                standarizeText(label);
                label->text.set(Text_t(make_str(counter, ".")));

				label = createNodeAt(vector2dst{ 1, counter }, make_str("label", 1, counter));
                standarizeText(label);
                label->text.set(Text_t(make_str(element.score)));

				label = createNodeAt(vector2dst{ 2, counter }, make_str("label", 2, counter));
                standarizeText(label);

				if (isInserting && positionInTable == counter) {
//					auto editor(label->ensureComponentOfType<TextEditorComponent>());
//					editor->setTextValidator(msptr<HighScoreValidator>());
//                    editor->Accepted.connect([this,positionInTable,element](const str&entry) mutable {
//                        m_hsData.setHighScoreName(positionInTable, entry);
//						saveHighScores();
//						Finished();
//					});
				} else {
                    label->text.set(Text_t(element.name));
				}
				++counter;
			}
		}
	}

    void HighScoreTextController::standarizeText(const sptr<nodes::SceneNodeText> &ntext)
	{
        ntext->textColor.set(FillColor_t(m_normalColor));
        ntext->font.set(m_normalFont);
	}

	void HighScoreTextController::saveHighScores()
	{
        log_debug_error("Saving highscores is still not implemented");
	}
}
