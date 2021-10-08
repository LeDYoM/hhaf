#include <haf/include/scene_components/scenecontrol.hpp>
#include <haf/include/scene/scene_node.hpp>
#include "scene/scenemanager.hpp"
#include "scene/scenecontroller.hpp"
#include "system/get_system.hpp"

namespace haf::scene
{
void SceneControl::switchToNextScene()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->switchToNextScene();
}

bool SceneControl::startScene(const htps::str& scene_name)
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->startScene(scene_name);
}

void SceneControl::requestExit()
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->requestExit();
}

bool SceneControl::exitRequested() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->exitRequested();
}

}  // namespace haf::scene
