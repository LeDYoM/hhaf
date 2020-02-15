#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "highscorevalidator.hpp"
#include "../loaders/highscoresresources.hpp"
#include "../gameshareddata.hpp"
#include <lib/scene/components/texteditorcomponent.hpp>
#include <lib/resources/include/ittfont.hpp>
#include <lib/facades/include/resourceview.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/filesystem.hpp>
#include <lib/system/scenemanager.hpp>
#include <lib/shareddata/include/shareddataview.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

static constexpr char HighScoresFileName[] = "high_scores.txt";

HighScoreTextController::HighScoreTextController(SceneNode *parent, str name)
    : BaseClass{parent, "HighScreTextController"} {}

HighScoreTextController::~HighScoreTextController() = default;

void HighScoreTextController::onCreated()
{
    BaseClass::onCreated();

    auto resource_view = dataWrapper<ResourceView>();

    m_normalFont = resource_view->getTTFont("menu.mainFont")->font(72);
    m_normalColor = colors::Blue;
    m_selectedColor = colors::Red;

    // Request the high scores.
    sceneManager().systemProvider().fileSystem().deserializeFromFile(HighScoresFileName, m_hsData);

    // Request game score
    Score gameScore = dataWrapper<shdata::SharedDataView>()->dataAs<GameSharedData>().score;

    Rectf32 textBox{rectFromSize(scenePerspective().size()).setLeftTop({0, 250}).setSize({2000, 1500})};
    position = textBox.leftTop();
    sceneNodeSize = textBox.size();
    setTableSize({3U, NumHighScore});

    size_type positionInTable;
    const bool isInserting{m_hsData.tryInsertHighScore(gameScore, positionInTable)};
    {
        size_type counter{0};
        for (const auto &element : m_hsData.highScoresList())
        {
            auto label(createNodeAt(vector2dst{0, counter}, make_str("label", 0, counter)));
            standarizeText(label);
            label->text.set(make_str(counter, "."));

            label = createNodeAt(vector2dst{1, counter}, make_str("label", 1, counter));
            standarizeText(label);
            label->text.set(make_str(element.score));

            label = createNodeAt(vector2dst{2, counter}, make_str("label", 2, counter));
            standarizeText(label);

            if (isInserting && positionInTable == counter)
            {
                auto editor(label->addComponentOfType<TextEditorComponent>());
                editor->setTextValidator(msptr<HighScoreValidator>());
                editor->Accepted.connect([this, positionInTable](const str &entry) mutable {
                    m_hsData.setHighScoreName(positionInTable, entry);
                    saveHighScores();
                    Finished();
                });
                editor->Rejected.connect([editor_ = mwptr(editor)]()
                {
                    editor_.lock()->enabled = true;
                });
            }
            else
            {
                label->text.set(element.name);
            }
            ++counter;
        }
    }

    if (!isInserting)
    {
        auto input_component(addComponentOfType<InputComponent>());
        input_component->KeyPressed.connect([this](const auto&)
        {
            Finished();
        });
    }
}

void HighScoreTextController::standarizeText(const sptr<nodes::SceneNodeText> &ntext)
{
    ntext->textColor.set(m_normalColor);
    ntext->font.set(m_normalFont);
}

void HighScoreTextController::saveHighScores()
{
    DisplayLog::info("Saving highscores...");
    sceneManager().systemProvider().fileSystem().serializeToFile(HighScoresFileName, m_hsData);
    DisplayLog::info("High Scores saved");
}
} // namespace zoper
