#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene_components/renderizable.hpp>
#include <haf/include/scene_components/table_of_text.hpp>
#include <haf/include/animation/animation_component.hpp>
#include "../loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
class HighScoreTextController : public haf::scene::TableOfText
{
    using Base = haf::scene::TableOfText;

public:
    using Base::Base;

    void onAttached() override;

    haf::evt::emitter<> Finished;

private:
    void onAllTableElementsCreated(fmath::vector2dst const) override;
    void standarizeText(const htps::sptr<haf::scene::Text>& ntext);
    void saveHighScores();
    void addHighScoresLine(const htps::size_type counter,
                           const HighScore& element,
                           const bool is_inserting);
    void addHighScoreEditor(const htps::sptr<haf::scene::Text>& label,
                            const htps::size_type counter);
    void addEditAnimation(const htps::size_type line_index);
    HighScoresData m_high_scores_data;
    htps::sptr<haf::res::IFont> m_normal_font;

    haf::scene::Color m_normal_color;
    haf::scene::Color m_selected_color;
};
}  // namespace zoper

#endif
