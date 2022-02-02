#ifndef HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene/scenenodefactory.hpp>

namespace haf::sys
{
class SystemAccess;
}
namespace haf::scene
{
class SceneManager;

/**
 * @brief Class to control which @b Scene is active and which are not.
 * This controller class manages the creation, destruction and maintenance of
 * the @b Scene instances.
 */
class HAF_PRIVATE SceneController final
{
public:
    void setSceneManager(htps::rptr<SceneManager> scene_manager);
    bool setSystemProviderInScene(
        htps::rptr<Scene::ScenePrivate> const scene_private,
        htps::rptr<sys::ISystemProvider> const isystem_provider);

    /**
     * @brief Switch to the next scene. For that to success, the current
     * scene shouold return the next scene in the member overriden
     * @b Scene::nextSceneName() and it has to be previously registered.
     */
    void switchToNextScene();
    void update();
    void finish();
    bool isActive();

    bool startScene(htps::str const& sceneName);

    template <typename T>
    bool registerAndStartScene(htps::str const& sceneName)
    {
        if (scene_factory_.registerSceneNodeType<T>(sceneName))
        {
            return startScene(sceneName);
        }
        return false;
    }

    template <typename T>
    bool registerAndStartScene()
    {
        if (scene_factory_.registerSceneNodeType<T>())
        {
            return startScene(T::StaticTypeName);
        }
        return false;
    }

    template <typename T>
    bool registerSceneNodeType()
    {
        return scene_factory_.registerSceneNodeType<T>();
    }

    template <typename T>
    bool unregisterSceneNodeType()
    {
        return scene_factory_.unregisterSceneNodeType<T>();
    }

    template <typename T>
    bool startScene()
    {
        return startScene(T::StaticTypeName);
    }

    SceneNodeFactory& sceneNodeFactory() noexcept;
    SceneNodeFactory const& sceneNodeFactory() const noexcept;

    htps::sptr<Scene> const& currentScene() const noexcept;
    bool currentSceneIsNull();

    void requestExit();
    bool exitRequested() const;

private:
    void startScene(htps::sptr<Scene> scene);
    void terminateCurrentScene();
    void deferredSwitchScene();

    SceneNodeFactory scene_factory_;
    htps::rptr<SceneManager> scene_manager_{nullptr};
    htps::sptr<Scene> current_scene_{nullptr};
    bool switch_scene_{false};
    bool exit_requested_{false};
};

}  // namespace haf::scene

#endif
