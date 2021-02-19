#include <haf/scene_components/include/app_initializer.hpp>
#include <haf/scene_components/include/scenefactory.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <haf/scene_components/include/scenefactory.hpp>

#include <scene/i_include/scenecontroller.hpp>
#include <system/i_include/get_system.hpp>

namespace haf::scene
{
SceneNodeFactory& AppInitializer::sceneNodeFactory()
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->sceneNodeFactory();
}

bool AppInitializer::startScene(const htps::str& scene_name)
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->startScene(scene_name);
}

}  // namespace haf::scene
