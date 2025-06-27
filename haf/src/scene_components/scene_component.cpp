#include "scene_component_private.hpp"
#include <haf/include/debug_system/debug_actions.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/debug_system/displayvar_console.hpp>
#include <haf/include/scene_components/table_component.hpp>

using namespace htps;

namespace haf::scene
{
SceneComponent::SceneComponent() :
    component::Component{}, p_{make_pimplp<SceneComponentPrivate>(this)}
{}

SceneComponent::~SceneComponent() = default;

str SceneComponent::nextSceneName()
{
    return "";
}
/*
rptr<SceneComponent> SceneComponent::sceneParent()
{
    return this;
}

rptr<SceneComponent const> SceneComponent::sceneParent() const
{
    return this;
}
*/
void SceneComponent::onAttached()
{
    if (p_->camera_component_ == nullptr)
    {
        p_->camera_component_ = attachedNode()->component<CameraComponent>();
        LogAsserter::log_assert(p_->camera_component_ != nullptr,
                                "Cannot create camera component");
    }
}

sptr<CameraComponent> const& SceneComponent::cameraComponent()
{
    return p_->camera_component_;
}

sptr<CameraComponent> const& SceneComponent::cameraComponent() const
{
    return p_->camera_component_;
}

void SceneComponent::onFinished()
{}

rptr<SceneComponent::SceneComponentPrivate> SceneComponent::scenePrivate()
{
    return p_.get();
}

void SceneComponent::installDebugUtils()
{
    attachedNode()->component<debug::DebugActions>()->addDebugAction(
        input::Key::I, [this]() { cameraComponent()->moveView({0.0F, 0.1F}); });
    attachedNode()->component<debug::DebugActions>()->addDebugAction(
        input::Key::K,
        [this]() { cameraComponent()->moveView({0.0F, -0.1F}); });
    attachedNode()->component<debug::DebugActions>()->addDebugAction(
        input::Key::J, [this]() { cameraComponent()->moveView({0.1F, 0.0F}); });
    attachedNode()->component<debug::DebugActions>()->addDebugAction(
        input::Key::L,
        [this]() { cameraComponent()->moveView({-0.1F, 0.0F}); });
}

str SceneComponent::completeName() const
{
    return attachedNode()->name();
}

void SceneComponent::initDebugUtils()
{
    sptr<SceneNode> nodeConsole{
        attachedNode()->createSceneNode("m_display_var_console")};
    p_->m_display_var_console = nodeConsole->component<DisplayVarConsole>();

    debug::DebugVariable a{1};
    p_->m_display_var_console->updateVar("Test", a);
    p_->m_display_var_console->showDebugVariables = true;
    installDebugUtils();
    nodeConsole->component<Transformation>()->Position = {0.1f, 0.1f};
}

}  // namespace haf::scene
