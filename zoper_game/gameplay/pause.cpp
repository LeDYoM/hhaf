#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>

#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ittfont.hpp>
#include <haf/resources/include/resourceview.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace haf::time;

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::onCreated()
{
    auto resources_viewer = dataWrapper<res::ResourceView>();

    m_pauseText = createSceneNode<SceneNodeText>("pausetext");
    m_pauseText->prop<SceneNodeTextProperties>()
        .put<Text>("PAUSE")
        .put<Font>(
            resources_viewer->getTTFont(GameResources::ScoreFontId)->font(180U))
        .put<TextColor>(colors::White)
        .put<AlignmentSize>(
            dataWrapper<SceneMetricsView>()->currentView().size())
        .put<AlignmentX>(AlignmentXModes::Center)
        .put<AlignmentY>(AlignmentYModes::Middle);

    prop<Visible>().set(false);
}

void PauseSceneNode::enterPause()
{
    prop<Visible>().set(true);
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(1000U),
        m_pauseText->prop<TextColor>(),
        Color{255U, 255U, 255U, 0U}, Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    prop<Visible>().set(false);
}
}  // namespace zoper
