#pragma once

#ifndef LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/scenenodefactory.hpp>

namespace lib::scene
{
using SceneDirectorType = mtps::function<mtps::str(const mtps::str&)>;
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

    mtps::sptr<Scene> currentScene();
    bool isActive();

    bool startScene(const mtps::str&sceneName);

    template <typename T>
    bool registerAndStartScene(const mtps::str&sceneName)
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
    const mtps::sptr<Scene> currentScene() const noexcept { return current_scene_; }

private:
    void startScene(mtps::sptr<Scene> scene);
    void terminateCurrentScene();
    
    SceneDirectorType scene_director_;
    SceneNodeFactory scene_factory_;
    SceneManager *scene_manager_{nullptr};
    mtps::sptr<Scene> current_scene_{nullptr};
};
} // namespace lib::scene

#endif
