#include "scene_private.hpp"
#include <haf/include/system/isystemprovider.hpp>
#include "scenecontroller.hpp"

using namespace htps;

namespace haf::scene
{
void Scene::ScenePrivate::setSystemProvider(
    htps::rptr<sys::ISystemProvider> isystem_provider)
{
    isystem_provider_ = isystem_provider;
    
}

void Scene::ScenePrivate::setSceneManager(htps::rptr<SceneManager> scene_manager)
{
    scene_manager_ = scene_manager;
}

}  // namespace haf::scene
