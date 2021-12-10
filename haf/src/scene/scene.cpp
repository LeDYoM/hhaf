#include <haf/include/scene/scene.hpp>
#include "scene_private.hpp"
#include <haf/include/debug_utils/debug_actions.hpp>
#include <haf/include/component/component_container.hpp>

#include <haf/include/scene_components/scenemetrics.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;

namespace haf::scene
{
Scene::Scene(htps::str name) :
    SceneNode{nullptr, std::move(name)}, p_{make_pimplp<ScenePrivate>(this)}
{}

Scene::~Scene() = default;

str Scene::nextSceneName()
{
    return "";
}

void Scene::onCreated()
{}

void Scene::onFinished()
{}

rptr<Scene::ScenePrivate> Scene::scenePrivate()
{
    return p_.get();
}

void Scene::installDebugUtils()
{
    component<debug::DebugActions>()->addDebugAction(input::Key::I, [this]() {
        subSystem<ISceneMetrics>()->move({0.0F, 100.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::K, [this]() {
        subSystem<ISceneMetrics>()->move({0.0F, -100.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::J, [this]() {
        subSystem<ISceneMetrics>()->move({100.0F, 0.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::L, [this]() {
        subSystem<ISceneMetrics>()->move({-100.0F, 0.0F});
    });
}

}  // namespace haf::scene
