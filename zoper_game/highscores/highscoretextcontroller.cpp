#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "highscorevalidator.hpp"
#include "../loaders/highscoresresources.hpp"
#include "../gameshareddata.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/scene_components/texteditorcomponent.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/scene_nodes/scenenodetext_properties.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/shareddata/shareddata.hpp>
#include <haf/include/shareddata/shareddataviewer.hpp>
#include <haf/include/input/input_component.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

namespace zoper
{
static constexpr char HighScoresFileName[] = "high_scores.txt";

HighScoreTextController::HighScoreTextController(SceneNode* parent, str name) :
    BaseClass{parent, std::move(name)}
{}

HighScoreTextController::~HighScoreTextController() = default;

void HighScoreTextController::onCreated()
{
    BaseClass::onCreated();

    normal_font_ = subSystem<res::IResourceRetriever>()
                       ->getTTFont(HighScoresResources::MenuFontId)
                       ->font(72);
    normal_color_        = colors::Blue;
    selected_color_      = colors::Red;
    animation_component_ = component<anim::AnimationComponent>();

    // Request the high scores.
    subSystem<sys::IFileSerializer>()->deserializeFromFile(HighScoresFileName,
                                                           high_scores_data_);

    // Request game score
    Score gameScore = dataWrapper<shdata::SharedDataViewer<GameSharedData>>()
                          ->view(GameSharedData::address())
                          ->score;
    Rectf32 textBox{
        rectFromSize(subSystem<ISceneMetricsView>()->currentView().size())
            .setLeftTop({0, 250})
            .setSize({2000, 1500})};
    prop<haf::scene::Position>().set(textBox.leftTop());
    prop<TableNodeProperties>().set<SceneNodeSize>(textBox.size());
    prop<TableSize>().set({3U, NumHighScore});

    size_type positionInTable{0U};
    const bool isInserting{
        high_scores_data_.tryInsertHighScore(gameScore, positionInTable)};

    size_type counter{0U};
    for (const auto& element : high_scores_data_.highScoresList())
    {
        addHighScoresLine(counter, element,
                          (isInserting && positionInTable == counter));
        ++counter;
    }

    if (!isInserting)
    {
        auto input_component{component<input::InputComponent>()};
        input_component->KeyPressed.connect(
            [this](const auto&) { Finished(); });
    }
}

void HighScoreTextController::addHighScoresLine(const size_type counter,
                                                const HighScore& element,
                                                const bool is_inserting)
{
    using namespace nodes;

    auto label(
        createNodeAt(vector2dst{0, counter}, make_str("label", 0, counter)));
    standarizeText(label);
    label->prop<SceneNodeTextProperties>().set<Text>(make_str(counter, "."));

    label = createNodeAt(vector2dst{1, counter}, make_str("label", 1, counter));
    standarizeText(label);
    label->prop<SceneNodeTextProperties>().set<Text>(make_str(element.score));

    label = createNodeAt(vector2dst{2, counter}, make_str("label", 2, counter));
    standarizeText(label);

    if (is_inserting)
    {
        addHighScoreEditor(label, counter);
    }
    else
    {
        label->prop<SceneNodeTextProperties>().set<Text>(element.name);
    }
}

void HighScoreTextController::addHighScoreEditor(
    const sptr<nodes::SceneNodeText>& label,
    const size_type counter)
{
    addEditAnimation(counter);
    auto editor{label->component<TextEditorComponent>()};
    editor->setTextValidator(muptr<HighScoreValidator>());
    editor->Accepted.connect([this, counter](const str& entry) mutable {
        high_scores_data_.setHighScoreName(counter, entry);
        saveHighScores();
        Finished();
    });
    editor->Rejected.connect(
        [editor_ = mwptr(editor)]() { editor_.lock()->enabled = true; });
}

void HighScoreTextController::addEditAnimation(const size_type line_index)
{
    LogAsserter::log_assert(line_index < prop<TableSize>().get().y,
                            "Invalid line_index");

    for_each_tableSceneNode_in_y(
        line_index,
        [this](const auto, const sptr<nodes::SceneNodeText>& element) {
            auto property_animation_builder =
                animation_component_
                    ->make_property_animation_builder<nodes::TextColor>(
                        element);
            property_animation_builder
                .duration(time::TimePoint_as_miliseconds(2000U))
                .startValue(colors::White)
                .endValue(colors::Black)
                .switchAnimation(true)
                .continuous();

            animation_component_->addAnimation(
                std::move(property_animation_builder));
        });
}

void HighScoreTextController::standarizeText(
    const sptr<nodes::SceneNodeText>& ntext)
{
    ntext->prop<nodes::SceneNodeTextProperties>()
        .put<nodes::TextColor>(normal_color_)
        .put<nodes::Font>(normal_font_);
}

void HighScoreTextController::saveHighScores()
{
    DisplayLog::info("Saving highscores...");

    subSystem<sys::IFileSerializer>()->serializeToFile(HighScoresFileName,
                                                       high_scores_data_);
    DisplayLog::info("High Scores saved");
}
}  // namespace zoper
