#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene_nodes/include/scenenodetext.hpp>
#include <lib/scene_components/include/animationcomponent.hpp>
#include <lib/scene_components/include/scenemetrics.hpp>

#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ittfont.hpp>
#include <lib/resources/include/resourceview.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace haf::time;

PauseSceneNode::PauseSceneNode(scene::SceneNode *const parent, str name)
    : SceneNode{parent, std::move(name)}
{
    auto resources_viewer = dataWrapper<ResourceView>();

    m_pauseText = createSceneNode<SceneNodeText>("pausetext");
    m_pauseText->text.set("PAUSE");
    m_pauseText->font.set(resources_viewer->getTTFont(GameResources::ScoreFontId)->font(180));
    m_pauseText->textColor.set(colors::White);
    m_pauseText->alignmentSize.set(dataWrapper<SceneMetrics>()->currentView().size());
    m_pauseText->alignmentX.set(SceneNodeText::AlignmentX::Center);
    m_pauseText->alignmentY.set(SceneNodeText::AlignmentY::Middle);

    visible.set(false);
}

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::enterPause()
{
    visible.set(true);
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(1000U),
        m_pauseText->textColor, Color{255U, 255U, 255U, 0U},
        Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    visible = false;
}
} // namespace zoper