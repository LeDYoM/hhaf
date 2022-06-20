#include "pause_scene_node.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/color.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/animation/animation_component.hpp>

#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/component/component_container.hpp>

#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

#include <haf/include/animation/delta_property.hpp>

using namespace htps;

using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;
using namespace haf::time;

namespace zoper
{
PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::onCreated()
{
    pause_text_       = createSceneNode<SceneNodeText>("pausetext");
    pause_text_->Text = "PAUSE";
    pause_text_->Font = subSystem<res::IResourceRetriever>()
                            ->getTTFont(GameResources::ScoreFontId)
                            ->font(200U);
    pause_text_->TextColor = colors::White;

    pause_text_->Scale = {0.5F, 0.5F};
    Visible            = false;
}

void PauseSceneNode::enterPause()
{
    Visible = true;
    pause_text_->component(animation_component_);
    auto builder{animation_component_->make_property_animation_builder(
        &SceneNodeText::TextColor, colors::Transparent, colors::White)};
    builder.duration(TimePoint_as_miliseconds(1000U));

    animation_component_->addAnimation(htps::move(builder));
}

void PauseSceneNode::exitPause()
{
    Visible = false;
}
}  // namespace zoper
