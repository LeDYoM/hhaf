#include <haf/include/scene/scene.hpp>

using namespace htps;

namespace haf::scene
{
Scene::Scene(htps::str name) : SceneNode{nullptr, std::move(name)}
{}

str Scene::nextSceneName()
{
    return "";
}

void Scene::onFinished()
{}

}  // namespace haf::scene
