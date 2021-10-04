#include <haf/include/scene/scene.hpp>
#include <haf/include/debug/debug_actions.hpp>
#include <haf/include/component/component_container.hpp>

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
{
    components().component<debug::DebugActions>()->addDebugAction(input::Key::I,
                                                                  []() {});
}

void Scene::onFinished()
{}

}  // namespace haf::scene
