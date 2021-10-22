#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/animation/animation_component.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/component/component_container.hpp>

#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

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
    pause_text_ = createSceneNode<SceneNodeText>("pausetext");
    pause_text_->prop<SceneNodeTextProperties>()
        .put<Text>("PAUSE")
        .put<Font>(
                       subSystem<res::IResourceRetriever>()
                       ->getTTFont(GameResources::ScoreFontId)
                       ->font(180U))
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
    pause_text_->component(animation_component_);

    auto builder{
        animation_component_->make_property_animation_builder_from_attached<
            TextColor, SceneNodeText>()};
    builder.startValue(Color{colors::White, Color::Transparent})
        .endValue(Color{colors::White, Color::Opaque})
        .duration(TimePoint_as_miliseconds(1000U));

    animation_component_->addAnimation(std::move(builder));
}

void PauseSceneNode::exitPause()
{
    prop<Visible>().set(false);
}
}  // namespace zoper
