#include "highscoretextcontroller.hpp"
#include "highscoresdata.hpp"
#include "highscorevalidator.hpp"
#include "../loaders/highscoresresources.hpp"
#include "../gameshareddata.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/scene_components/texteditorcomponent.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/shareddata/shared_data_viewer.hpp>
#include <haf/include/input/input_component.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace fmath;

namespace zoper
{
static constexpr char HighScoresFileName[] = "high_scores.txt";

void HighScoreTextController::onAttached()
{
    Base::onAttached();
    TableSize = {3U, NumHighScore};
}

void HighScoreTextController::onAllTableElementsCreated(fmath::vector2dst const)
{
    set_property_for_each_table_node(&Text::TextBaseSizeProperty,
                                     TextBaseSize{'A', 8U});

    m_normal_font = attachedNode()
                        ->subSystem<res::IResourceRetriever>()
                        ->getTTFont(HighScoresResources::MenuFontId)
                        ->font(72);
    m_normal_color   = colors::Blue;
    m_selected_color = colors::Red;

    // Request the high scores.
    attachedNode()->subSystem<sys::IFileSerializer>()->deserializeFromFile(
        HighScoresFileName, m_high_scores_data);

    // Request game score
    Score gameScore = shdata::SharedDataViewer<GameSharedData>(
                          attachedNode()->subSystem<shdata::ISharedData>())
                          .view(GameSharedData::address())
                          ->score;

    size_type positionInTable{0U};
    const bool isInserting{
        m_high_scores_data.tryInsertHighScore(gameScore, positionInTable)};

    size_type counter{0U};
    for (const auto& element : m_high_scores_data.highScoresList())
    {
        addHighScoresLine(counter, element,
                          (isInserting && positionInTable == counter));
        ++counter;
    }

    if (!isInserting)
    {
        auto input_component{
            attachedNode()->component<input::InputComponent>()};
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
    label->Text = make_str(counter, ".");

    label = text(vector2dst{1U, counter});
    standarizeText(label);
    label->Text = make_str(element.score);

    label = text(vector2dst{2U, counter});
    standarizeText(label);

    if (is_inserting)
    {
        addHighScoreEditor(label, counter);
    }
    else
    {
        label->Text = element.name;
    }
}

void HighScoreTextController::addHighScoreEditor(const sptr<Text>& label,
                                                 const size_type counter)
{
    addEditAnimation(counter);
    auto editor{label->attachedNode()->component<TextEditorComponent>()};
    editor->setTextValidator(muptr<HighScoreValidator>());
    editor->Accepted.connect([this, counter](const str& entry) mutable {
        m_high_scores_data.setHighScoreName(counter, entry);
        saveHighScores();
        Finished();
    });
    editor->Rejected.connect(
        [editor = htps::wptr(editor)]() { editor.lock()->enabled = true; });
}

void HighScoreTextController::addEditAnimation(const size_type line_index)
{
    LogAsserter::log_assert(line_index < TableSize().y, "Invalid line_index");

    for_each_outerSceneNode_in_y(
        line_index, [this](const auto, sptr<scene::Text> const& element) {
            sptr<anim::AnimationComponent> animation_component;
            element->attachedNode()->component(animation_component);
/*
            auto property_animation_builder{
                animation_component->make_property_animation_builder(
                    &Text::TextColor, colors::Blue,
                    colors::Black)};
            property_animation_builder
                .duration(time::TimePoint_as_miliseconds(2000U))
                .switchAnimation(true)
                .continuous();

            animation_component->addAnimation(
                htps::move(property_animation_builder));
                */
        });
}

void HighScoreTextController::standarizeText(const sptr<Text>& ntext)
{
    ntext->TextColor = m_normal_color;
    ntext->Font      = m_normal_font;
}

void HighScoreTextController::saveHighScores()
{
    DisplayLog::info("Saving highscores...");

    attachedNode()->subSystem<sys::IFileSerializer>()->serializeToFile(
        HighScoresFileName, m_high_scores_data);
    DisplayLog::info("High Scores saved");
}

}  // namespace zoper
