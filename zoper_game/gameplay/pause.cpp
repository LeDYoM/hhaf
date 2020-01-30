#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/resources_interface/include/itexture.hpp>
#include <lib/resources_interface/include/ittfont.hpp>

#include <lib/system/scenemanager.hpp>
#include <lib/facades/include/resourceview.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

PauseSceneNode::PauseSceneNode(scene::SceneNode *const parent, str name)
    : SceneNode{parent, std::move(name)}
{
    auto resources_viewer = dataWrapper<ResourceView>();

    m_pauseText = createSceneNode<SceneNodeText>("pausetext");
    m_pauseText->text.set("PAUSE");
    m_pauseText->font.set(resources_viewer->getTTFont(GameResources::ScoreFontId)->font(180));
    m_pauseText->textColor.set(colors::White);
    m_pauseText->alignmentSize.set(scenePerspective().size());
    m_pauseText->alignmentX.set(SceneNodeText::AlignmentX::Center);
    m_pauseText->alignmentY.set(SceneNodeText::AlignmentY::Middle);

    visible.set(false);
}

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::enterPause()
{
    visible.set(true);
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(TimePoint_as_miliseconds(1000U),
                                             m_pauseText->textColor, Color{255U, 255U, 255U, 0U},
                                             Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    visible = false;
}
} // namespace zoper
