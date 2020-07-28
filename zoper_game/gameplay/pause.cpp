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

PauseSceneNode::PauseSceneNode(scene::SceneNode* const parent, str name) :
    SceneNode{parent, std::move(name)}
{
    auto resources_viewer = dataWrapper<res::ResourceView>();

    m_pauseText = createSceneNode<SceneNodeText>("pausetext");
    m_pauseText->text.set("PAUSE");
    m_pauseText->font.set(
        resources_viewer->getTTFont(GameResources::ScoreFontId)->font(180));
    m_pauseText->textColor.set(colors::White);
    m_pauseText->alignmentSize.set(
        dataWrapper<SceneMetricsView>()->currentView().size());
    m_pauseText->alignmentX.set(SceneNodeText::AlignmentX::Center);
    m_pauseText->alignmentY.set(SceneNodeText::AlignmentY::Middle);

    sceneNodeProperties().set<Visible>(false);
}

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::enterPause()
{
    sceneNodeProperties().set<Visible>(true);
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(1000U), m_pauseText->textColor,
        Color{255U, 255U, 255U, 0U}, Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    sceneNodeProperties().set<Visible>(false);
}
}  // namespace zoper
