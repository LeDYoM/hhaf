#include "scenecontroller.hpp"
#include "scene.hpp"
#include "scenemanager.hpp"

#include <lib/system/include/isystemprovider.hpp>
#include <lib/include/liblog.hpp>

namespace lib::scene
{
SceneController::~SceneController() = default;

void SceneController::setSceneManager(SceneManager *scene_manager)
{
    log_assert(scene_manager_ == nullptr, "The scene_manager_ was set already");
    scene_manager_ = scene_manager;
}

bool SceneController::startScene(const mtps::str&sceneName)
{
    auto scene = scene_factory_.create(sceneName);
    startScene(mtps::sptr<Scene>(std::move(scene)));
    return true;
}

void SceneController::switchToNextScene()
{
    // Prepare next Scene
    mtps::sptr<Scene> nextScene{nullptr};
    if (scene_director_)
    {
        nextScene = scene_factory_.create(scene_director_(current_scene_->name()));
    }

    terminateCurrentScene();

    DisplayLog::info("Setting new scene: ", nextScene ? nextScene->name() : "<nullptr>");
    startScene(std::move(nextScene));
}

void SceneController::terminateCurrentScene()
{
    log_assert(current_scene_ != nullptr, "Unexpected nullptr in current_scene");
    DisplayLog::info("Terminating scene ", current_scene_->name());
    current_scene_->onFinished();
}

void SceneController::setSceneDirector(SceneDirectorType sceneDirector)
{
    scene_director_ = std::move(sceneDirector);
}

void SceneController::update()
{
    if (auto current_scene = currentScene())
    {
        current_scene->render(false);
    }
}

void SceneController::finish()
{
    if (!currentSceneIsNull())
    {
        terminateCurrentScene();
    }
}

mtps::sptr<Scene> SceneController::currentScene()
{
    return current_scene_;
}

void SceneController::startScene(mtps::sptr<Scene> scene)
{
    current_scene_ = std::move(scene);
    if (current_scene_)
    {
        if (scene_manager_)
        {
            current_scene_->scene_manager_ = scene_manager_;
            current_scene_->copySystemProvider(&(scene_manager_->isystemProvider()));
        }
        current_scene_->onCreated();
    }
}

bool SceneController::currentSceneIsNull()
{
    return current_scene_ == nullptr;
}

bool SceneController::isActive()
{
    return !currentSceneIsNull();
}
} // namespace lib::scene
