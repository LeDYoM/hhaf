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

} // namespace haf::scene
