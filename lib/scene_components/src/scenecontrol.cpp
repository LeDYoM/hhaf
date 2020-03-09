#include "scenecontrol.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/i_include/scenemanager.hpp>
#include <lib/scene/i_include/scenecontroller.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::scene
{
void SceneControl::switchToNextScene()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->switchToNextScene();
}

} // namespace lib::scene
