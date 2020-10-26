#include <haf/scene_components/include/scenecontrol.hpp>
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

bool SceneControl::startScene(const mtps::str& scene_name)
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
