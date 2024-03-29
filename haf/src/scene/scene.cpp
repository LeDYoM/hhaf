#include <haf/include/scene/scene.hpp>
#include "scene_private.hpp"
#include <haf/include/debug_utils/debug_actions.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/camera_component.hpp>

using namespace htps;

namespace haf::scene
{
Scene::Scene(htps::str name) :
    SceneNode{nullptr, htps::move(name)}, p_{make_pimplp<ScenePrivate>(this)}
{}

Scene::~Scene() = default;

str Scene::nextSceneName()
{
    return "";
}

rptr<Scene> Scene::sceneParent()
{
    return this;
}

rptr<Scene const> Scene::sceneParent() const
{
    return this;
}

void Scene::onCreated()
{
    if (p_->camera_component_ == nullptr)
    {
        p_->camera_component_ = component<CameraComponent>();
        LogAsserter::log_assert(p_->camera_component_ != nullptr,
                                "Cannot create camera component");
    }
}

sptr<CameraComponent> const& Scene::cameraComponent()
{
    return p_->camera_component_;
}

sptr<CameraComponent> const& Scene::cameraComponent() const
{
    return p_->camera_component_;
}

void Scene::onFinished()
{}

rptr<Scene::ScenePrivate> Scene::scenePrivate()
{
    return p_.get();
}

void Scene::installDebugUtils()
{
    component<debug::DebugActions>()->addDebugAction(input::Key::I, [this]() {
        cameraComponent()->moveView({0.0F, 0.1F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::K, [this]() {
        cameraComponent()->moveView({0.0F, -0.1F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::J, [this]() {
        cameraComponent()->moveView({0.1F, 0.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::L, [this]() {
        cameraComponent()->moveView({-0.1F, 0.0F});
    });
}

str Scene::completeName() const
{
    return name();
}

}  // namespace haf::scene
