#pragma once

#ifndef LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/scene.hpp>
#include <lib/scene/scenenodefactory.hpp>

namespace lib::scene
{
using SceneDirectorType = function<str(const str &)>;
class SceneManager;

class SceneController
{
public:
    virtual ~SceneController();

    void setSceneManager(SceneManager *scene_manager);

    void switchToNextScene();
    void setSceneDirector(SceneDirectorType sceneDirector);
    void update();
    void finish();

    sptr<Scene> currentScene();
    bool isActive();

    bool startScene(const str &sceneName);

    template <typename T>
    bool registerAndStartScene(const str &sceneName)
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

    inline SceneNodeFactory &sceneNodeFactory() noexcept { return scene_factory_; }
    inline const SceneNodeFactory &sceneNodeFactory() const noexcept { return scene_factory_; }
    bool currentSceneIsNull();
    const sptr<Scene> currentScene() const noexcept { return current_scene_; }

private:
    void startScene(sptr<Scene> scene);
    void terminateCurrentScene();
    
    SceneDirectorType scene_director_;
    SceneNodeFactory scene_factory_;
    SceneManager *scene_manager_{nullptr};
    sptr<Scene> current_scene_{nullptr};
};
} // namespace lib::scene

#endif
