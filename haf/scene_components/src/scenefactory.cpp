#include "scenefactory.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <scene/i_include/scenecontroller.hpp>
#include <scene/include/scenenodefactory.hpp>
#include <system/i_include/get_system.hpp>

namespace
{
template <typename T>
mtps::uptr<T> createScene()
{
    return mtps::muptr<T>();
}

}

namespace haf::scene
{
void SceneFactory::switchToNextScene()
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()
        ->switchToNextScene();
}

bool SceneFactory::registerSceneType(const mtps::str& name) 
{
    sys::getSystem<scene::SceneManager>(attachedNode())
        .sceneController()->sceneNodeFactory().registerSceneNodeType(name, createScene);
}

} // namespace haf::scene
