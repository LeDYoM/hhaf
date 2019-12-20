#include "scenecontroller.hpp"
#include "scenemanager.hpp"
#include "scene.hpp"

#include <lib/include/liblog.hpp>

namespace lib::scene
{
    void SceneController::setSceneManager(SceneManager *scene_manager)
    {
        log_assert(scene_manager_ == nullptr, "The scene_manager_ was set already");
        scene_manager_ = scene_manager;
    }

    bool SceneController::startScene(const str &sceneName)
    {
        auto scene = scene_factory_.create(sceneName);
        startScene(sptr<Scene>(std::move(scene)));
        return true;
    }

    void SceneController::terminateScene()
    {
        DisplayLog::info("Terminating scene ", this->currentState()->name());
        sptr<Scene> nextScene;
        if (scene_director_)
        {
            nextScene = scene_factory_.create(scene_director_(currentState()->name()));
        }

        DisplayLog::info("Setting new scene: ", nextScene ? nextScene->name() : "<nullptr>");
        startScene(std::move(nextScene));
    }

    void SceneController::setSceneDirector(SceneDirectorType sceneDirector)
    {
        scene_director_ = std::move(sceneDirector);
    }

    void SceneController::update()
    {
        BaseClass::update();
        if (auto current_scene = currentScene())
        {
            current_scene->render(false);
        }
    }

    void SceneController::finish()
    {
        while (BaseClass::hasActiveState())
        {
            this->pop_state();
            BaseClass::update();
        }
    }

    sptr<Scene> SceneController::currentScene()
    {
        return BaseClass::currentState();
    }

    void SceneController::startScene(sptr<Scene> scene)
    {
        if (scene)
        {
            scene->m_sceneManager = scene_manager_;
            scene->onCreated();
        }
        
        this->StateFinished.connect([](const sptr<Scene>& scene)
        {
            if (scene)
            {
                scene->onFinished();
            }
        });

        if (!BaseClass::hasActiveState())
        {
            BaseClass::start(std::move(scene));
        }
        else
        {
            BaseClass::setState(std::move(scene));
        }
    }

    bool SceneController::currentSceneIsNull()
    {
        return currentScene() == nullptr;
    }

    bool SceneController::isActive()
    {
        return !currentSceneIsNull() && hasActiveState();
    }
}
