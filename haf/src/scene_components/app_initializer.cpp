#include <haf/include/scene_components/app_initializer.hpp>
#include <haf/include/scene_components/scenefactory.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene_components/scenefactory.hpp>

#include "scene/scenemanager.hpp"
#include "scene/scenecontroller.hpp"
#include "system/get_system.hpp"

namespace haf::scene
{
SceneNodeFactory& AppInitializer::sceneNodeFactory()
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->sceneNodeFactory();
}

bool AppInitializer::startScene(htps::str const& scene_name)
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->startScene(scene_name);
}

}  // namespace haf::scene
