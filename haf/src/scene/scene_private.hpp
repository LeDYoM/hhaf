#ifndef HAF_SCENE_SCENE_PRIVATE_INCLUDE_HPP
#define HAF_SCENE_SCENE_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/scene.hpp>

namespace haf::sys
{
class ISystemProvider;
}
namespace haf::scene
{
class SceneManager;

class Scene::ScenePrivate final
{
public:
    void setSystemProvider(htps::rptr<sys::ISystemProvider> isystem_provider);
    void setSceneManager(htps::rptr<SceneManager> scene_manager);

    htps::rptr<SceneManager> sceneManager() const { return scene_manager_; }
    htps::rptr<sys::ISystemProvider> iSystemProvider() const
    {
        return isystem_provider_;
    }

private:
    htps::rptr<SceneManager> scene_manager_{nullptr};
    htps::rptr<sys::ISystemProvider> isystem_provider_{nullptr};
};
}  // namespace haf::scene

#endif
