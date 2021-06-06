#include <haf/include/scene_components/scenefactory.hpp>
#include <haf/include/scene/scenenode.hpp>
#include "scene/scenemanager.hpp"
#include "scene/scenecontroller.hpp"
#include "system/get_system.hpp"

namespace haf::scene
{
SceneNodeFactory& SceneFactory::sceneNodeFactory()
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->sceneNodeFactory();
}

}  // namespace haf::scene
