#include "pause.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/resources/texture.hpp>
#include <lib/resources/ttfont.hpp>

#include <lib/system/resourcemanager.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>

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
    m_pauseText->text.set(Text_t("PAUSE"));
    m_pauseText->font.set(resources_viewer->getTTFont(GameResources::ScoreFontId)->font(180));
    m_pauseText->textColor.set(colors::White);
    {
        auto align(m_pauseText->addComponentOfType<AlignedTextComponent>());
        align->alignmentSize.set(parentScene()->scenePerspective().size());
        align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
        align->alignmentY.set(AlignedTextComponent::AlignmentY::Middle);
    }

    visible.set(false);
}

PauseSceneNode::~PauseSceneNode() = default;

void PauseSceneNode::enterPause()
{
    visible.set(true);
    auto animationComponent(addComponentOfType<AnimationComponent>());
    animationComponent->addPropertyAnimation(TimePoint_as_miliseconds(1000U),
                                             m_pauseText->textColor, Color{255U, 255U, 255U, 0U},
                                             Color{255U, 255U, 255U, 255U});
}

void PauseSceneNode::exitPause()
{
    visible = false;
}
} // namespace zoper
