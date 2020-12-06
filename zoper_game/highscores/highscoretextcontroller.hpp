#ifndef ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP
#define ZOPER_HIGHSCORETEXTCONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/resources/include/ifont.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>
#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>
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
    using TransformationProperties::prop;

    HighScoreTextController(scene::SceneNode* parent, mtps::str name);
    virtual ~HighScoreTextController();

    virtual void onCreated() override;

    mtps::emitter<> Finished;

private:
    void standarizeText(const mtps::sptr<nodes::SceneNodeText>& ntext);
    void saveHighScores();
    void addHighScoresLine(const mtps::size_type counter,
                           const HighScore& element,
                           const bool is_inserting);
    void addHighScoreEditor(const mtps::sptr<SceneNode>& label,
                            const mtps::size_type counter);
    void addEditAnimation(const mtps::size_type line_index);
    HighScoresData m_hsData;
    mtps::sptr<res::IFont> m_normalFont;
    mtps::sptr<scene::AnimationComponent> animation_component_;

    Color m_normalColor;
    Color m_selectedColor;
};
}  // namespace zoper

#endif
