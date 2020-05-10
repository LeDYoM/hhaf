#include "scenecontrol.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/i_include/scenemanager.hpp>
#include <haf/scene/i_include/scenecontroller.hpp>
#include <haf/system/i_include/get_system.hpp>

namespace haf::scene
{
void SceneControl::switchToNextScene()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->switchToNextScene();
}

} // namespace haf::scene
