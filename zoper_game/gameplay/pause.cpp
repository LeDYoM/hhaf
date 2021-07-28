#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/scene_components/animationcomponent.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/components/component_container.hpp>

#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/resourceretriever.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace haf::time;

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::onCreated()
{
    m_pauseText = createSceneNode<SceneNodeText>("pausetext");
    m_pauseText->prop<SceneNodeTextProperties>()
        .put<Text>("PAUSE")
        .put<Font>(subsystems()
                       .dataWrapper<res::ResourceRetriever>()
                       ->getTTFont(GameResources::ScoreFontId)
                       ->font(180U))
        .put<TextColor>(colors::White)
        .put<AlignmentSize>(
            subsystems().dataWrapper<SceneMetricsView>()->currentView().size())
        .put<AlignmentX>(AlignmentXModes::Center)
        .put<AlignmentY>(AlignmentYModes::Middle);

    prop<Visible>().set(false);
}

void PauseSceneNode::enterPause()
{
    prop<Visible>().set(true);
    components().ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(1000U), m_pauseText->prop<TextColor>(),
        Color{255U, 255U, 255U, 0U}, Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    prop<Visible>().set(false);
}
}  // namespace zoper
