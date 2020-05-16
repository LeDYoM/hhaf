#include "scenecontrol.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <scene/i_include/scenecontroller.hpp>
#include <system/i_include/get_system.hpp>

namespace haf::scene
{
void SceneControl::switchToNextScene()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->switchToNextScene();
}

void SceneControl::setSceneDirector(SceneDirectorType scene_director)
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->setSceneDirector(std::move(scene_director));
}

bool SceneControl::startScene(const mtps::str& scene_name)
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->startScene(scene_name);
}

}  // namespace haf::scene
