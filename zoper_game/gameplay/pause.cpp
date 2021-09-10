#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/animation/animation_component.hpp>
#include <haf/include/animation/property_animation_builder.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/component/component_container.hpp>

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
    TimePoint const pause_animation_time{TimePoint_as_miliseconds(1000U)};

    prop<Visible>().set(true);
    components().component(animation_component_);

    auto property_animation_builder =
        animation_component_->make_property_animation_builder<TextColor>(
            m_pauseText);

    property_animation_builder
        ->startValue(Color{colors::White, Color::Transparent})
        .endValue(Color{colors::White, Color::Opaque})
        .duration(pause_animation_time);
    animation_component_->addAnimation(std::move(property_animation_builder));
}

void PauseSceneNode::exitPause()
{
    prop<Visible>().set(false);
}
}  // namespace zoper
