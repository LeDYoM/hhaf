#include <haf/scene_components/include/scenefactory.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <haf/scene_components/include/scenefactory.hpp>

#include <scene/i_include/scenecontroller.hpp>
#include <system/i_include/get_system.hpp>

namespace haf::scene
{
SceneNodeFactory& SceneFactory::sceneNodeFactory()
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->sceneNodeFactory();
}

}  // namespace haf::scene
