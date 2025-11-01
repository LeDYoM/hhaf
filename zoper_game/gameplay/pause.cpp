#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/color.hpp>
#include <haf/include/animation/animation_component.hpp>

#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/component/component_container.hpp>

#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

#include <haf/include/animation/delta_property.hpp>

using namespace haf;
using namespace haf::anim;
using namespace haf::core;
using namespace haf::scene;
using namespace haf::time;
using namespace haf::res;

namespace zoper
{

void Pause::onAttached()
{
    m_pause_text =
        attachedNode()->createSceneNode("pausetext")->component<Text>();
    m_pause_text->Text = "PAUSE";
    m_pause_text->Font = attachedNode()
                             ->subSystem<IResourceRetriever>()
                             ->getTTFont(GameResources::ScoreFontId)
                             ->font(200U);
    m_pause_text->TextColor = colors::White;

    m_pause_text->attachedNode()->component<Transformation>()->Scale = {0.5F,
                                                                        0.5F};
    m_pause_text->attachedNode()->hideChildren();
}

void Pause::enterPause()
{
    auto animation_component{
        m_pause_text->attachedNode()->component<AnimationComponent>()};
    auto builder{animation_component->make_property_animation_builder(
        &Text::TextColor, colors::Transparent, colors::White)};
    builder.duration(TimePoint_as_miliseconds(1000U))
        .actionBeforeStarting(
            [this]() { m_pause_text->attachedNode()->showChildren(); });

    animation_component->addAnimation(core::move(builder));
}

void Pause::exitPause()
{
    attachedNode()->Visible = false;
}
}  // namespace zoper
