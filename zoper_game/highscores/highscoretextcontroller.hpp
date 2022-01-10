#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/resources/ifont.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_table.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/animation/animation_component.hpp>
#include "../loaders/highscoresresources.hpp"
#include "highscoresdata.hpp"

namespace zoper
{
using namespace haf;
using namespace haf::scene;

class HighScoreTextController : public nodes::TableNode<nodes::SceneNodeText>
{
    using BaseClass = nodes::TableNode<nodes::SceneNodeText>;

public:
    using BaseClass::prop;

    HighScoreTextController(scene::SceneNode* parent, htps::str name);
    virtual ~HighScoreTextController();

    virtual void onCreated() override;

    htps::emitter<> Finished;

private:
    void standarizeText(const htps::sptr<nodes::SceneNodeText>& ntext);
    void saveHighScores();
    void addHighScoresLine(const htps::size_type counter,
                           const HighScore& element,
                           const bool is_inserting);
    void addHighScoreEditor(const htps::sptr<nodes::SceneNodeText>& label,
                            const htps::size_type counter);
    void addEditAnimation(const htps::size_type line_index);
    HighScoresData high_scores_data_;
    htps::sptr<res::IFont> normal_font_;
    htps::sptr<anim::AnimationComponent> animation_component_;

    Color normal_color_;
    Color selected_color_;
};
}  // namespace zoper

#endif
