#pragma once

#ifndef HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define HAF_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/scenenodefactory.hpp>

namespace haf::scene
{
class SceneManager;

/**
 * @brief Class to control which @b Scene is active and which are not.
 * This controller class manages the creation, destruction and maintenance of
 * the @b Scene instances.
 */
class SceneController final
{
public:
    /**
     * @brief Type defining the function callback for an scene director
     */
    using SceneDirectorType = mtps::function<mtps::str(const mtps::str&)>;

    void setSceneManager(mtps::rptr<SceneManager> scene_manager);

    void switchToNextScene();
    void setSceneDirector(SceneDirectorType sceneDirector);
    void update();
    void finish();
    bool isActive();

    bool startScene(const mtps::str& sceneName);

    template <typename T>
    bool registerAndStartScene(const mtps::str& sceneName)
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
        if (sceneFactory_.registerSceneNodeType<T>())
        {
            return startScene(sceneName);
        }
        return false;
    }

    template <typename T>
    bool registerSceneNodeType()
    {
        return scene_factory_.registerSceneNodeType<T>();
    }

    template <typename T>
    inline bool startScene()
    {
        return startScene(T::StaticTypeName);
    }

    SceneNodeFactory& sceneNodeFactory() noexcept;
    const SceneNodeFactory& sceneNodeFactory() const noexcept;
    const mtps::sptr<Scene>& currentScene() const noexcept;
    bool currentSceneIsNull();

private:
    void startScene(mtps::sptr<Scene> scene);
    void terminateCurrentScene();
    void deferredSwitchScene();

    SceneDirectorType scene_director_;
    SceneNodeFactory scene_factory_;
    mtps::rptr<SceneManager> scene_manager_{nullptr};
    mtps::sptr<Scene> current_scene_{nullptr};
    bool switch_scene_{false};
};
}  // namespace haf::scene

#endif
