#include <haf/include/scene/scene.hpp>
#include <haf/include/debug_utils/debug_actions.hpp>
#include <haf/include/component/component_container.hpp>

#include <haf/include/scene_components/scenemetrics.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;

namespace haf::scene
{
Scene::Scene(htps::str name) : SceneNode{nullptr, std::move(name)}
{}

str Scene::nextSceneName()
{
    return "";
}

void Scene::onCreated()
{}

void Scene::onFinished()
{}

void Scene::installDebugUtils()
{
    component<debug::DebugActions>()->addDebugAction(input::Key::I, [this]() {
        dataWrapper<SceneMetrics>()->move({0.0F, 100.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::K, [this]() {
        dataWrapper<SceneMetrics>()->move({0.0F, -100.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::J, [this]() {
        dataWrapper<SceneMetrics>()->move({100.0F, 0.0F});
    });
    component<debug::DebugActions>()->addDebugAction(input::Key::L, [this]() {
        dataWrapper<SceneMetrics>()->move({-100.0F, 0.0F});
    });
}

}  // namespace haf::scene
