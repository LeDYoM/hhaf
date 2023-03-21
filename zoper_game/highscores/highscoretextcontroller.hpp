#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_table_text.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/animation/animation_component.hpp>
#include "../loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
class HighScoreTextController : public haf::scene::nodes::TextTableNode
{
    using BaseClass = haf::scene::nodes::TextTableNode;

public:
    using BaseClass::BaseClass;

    void onCreated() override;

    evt::emitter<> Finished;

private:
    void onAllTableElementsCreated(htps::vector2dst const) override;
    void standarizeText(
        const htps::sptr<haf::scene::nodes::SceneNodeText>& ntext);
    void saveHighScores();
    void addHighScoresLine(const htps::size_type counter,
                           const HighScore& element,
                           const bool is_inserting);
    void addHighScoreEditor(
        const htps::sptr<haf::scene::nodes::SceneNodeText>& label,
        const htps::size_type counter);
    void addEditAnimation(const htps::size_type line_index);
    HighScoresData high_scores_data_;
    htps::sptr<haf::res::IFont> normal_font_;

    haf::scene::Color normal_color_;
    haf::scene::Color selected_color_;
};
}  // namespace zoper

#endif
