#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "highscorevalidator.hpp"
#include "../loaders/highscoresresources.hpp"
#include "../gameshareddata.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/scene_components/texteditorcomponent.hpp>
#include <haf/include/scene_nodes/scene_node_text_properties.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>
#include <haf/include/input/input_component.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_nodes/scene_node_text_properties.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
static constexpr char HighScoresFileName[] = "high_scores.txt";

void HighScoreTextController::onCreated()
{
    BaseClass::onCreated();
    prop<TableSize>().set({3U, NumHighScore});
}

void HighScoreTextController::onAllTableElementsCreated(htps::vector2dst const)
{
//    prop<Scale>() = {0.5F, 0.5F};
    set_property_for_each_tableSceneNode<TextBaseSizeProperty>(
        TextBaseSize{'A', 8U});

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
    Score gameScore = shdata::SharedDataViewer<GameSharedData>(
                          subSystem<shdata::ISharedData>())
                          .view(GameSharedData::address())
                          ->score;

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

    auto label{text(vector2dst{0U, counter})};
    standarizeText(label);
    label->prop<SceneNodeTextProperties>().set<Text>(make_str(counter, "."));

    label = text(vector2dst{1U, counter});
    standarizeText(label);
    label->prop<SceneNodeTextProperties>().set<Text>(make_str(element.score));

    label = text(vector2dst{2U, counter});
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
                htps::move(property_animation_builder));
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
