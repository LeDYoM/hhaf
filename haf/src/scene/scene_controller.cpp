#include "scene_controller.hpp"
#include "scene_manager.hpp"
#include "scene_render.hpp"
#include "scene_private.hpp"
#include "system/system_provider.hpp"
#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/system/isystem_provider.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
void SceneController::setSceneManager(rptr<SceneManager> scene_manager)
{
    LogAsserter::log_assert(scene_manager_ == nullptr,
                            "The scene_manager_ was set already");
    LogAsserter::log_assert(scene_manager != nullptr,
                            "Invalid parameter scene_node");
    scene_manager_ = scene_manager;
}

bool SceneController::startScene(str const& sceneName)
{
    auto scene = scene_factory_.create(sceneName);
    startScene(sptr<Scene>(htps::move(scene)));
    return true;
}

void SceneController::switchToNextScene()
{
    switch_scene_ = true;
}

void SceneController::deferredSwitchScene()
{
    terminateCurrentScene();

    // Prepare next Scene
    sptr<Scene> nextScene{nullptr};
    if (!exit_requested_)
    {
        auto const next_scene_name = current_scene_->nextSceneName();

        if (!next_scene_name.empty())
        {
            nextScene = scene_factory_.create(next_scene_name);
            DisplayLog::error_if(nextScene == nullptr,
                                 "Requested next scene of type: ",
                                 next_scene_name, ", but cannot be created");
        }
    }

    DisplayLog::info("Setting new scene: ",
                     nextScene ? nextScene->name() : "<nullptr>");
    startScene(htps::move(nextScene));
}

void SceneController::terminateCurrentScene()
{
    LogAsserter::log_assert(current_scene_ != nullptr,
                            "Unexpected nullptr in current_scene");
    DisplayLog::info("Terminating scene ", current_scene_->name());
    current_scene_->onFinished();
}

void SceneController::update()
{
    if (switch_scene_)
    {
        deferredSwitchScene();
        switch_scene_ = false;
    }

    if (current_scene_ != nullptr)
    {
        Matrix4x4 startMatrix{Matrix4x4::Identity};
        render(*current_scene_, SceneRenderContext{false, startMatrix});
    }
}

void SceneController::finish()
{
    if (!currentSceneIsNull())
    {
        terminateCurrentScene();
    }
}

sptr<Scene> const& SceneController::currentScene() const noexcept
{
    return current_scene_;
}

bool SceneController::setSystemProviderInScene(
    rptr<Scene::ScenePrivate> const scene_private,
    rptr<sys::ISystemProvider> const isystem_provider)
{
    LogAsserter::log_assert(scene_private->iSystemProvider() == nullptr,
                            "You should not use this function"
                            " if isystemProvider is already set");

    LogAsserter::log_assert(isystem_provider != nullptr,
                            "Parameter is nullptr");

    // Invalid data. Exit performing no action.
    if (scene_private->iSystemProvider() != nullptr ||
        isystem_provider == nullptr)
    {
        return false;
    }

    // Valid data. Perform action and return true.
    scene_private->setSystemProvider(isystem_provider);
    return true;
}

void SceneController::startScene(sptr<Scene> scene)
{
    current_scene_ = htps::move(scene);
    if (current_scene_ != nullptr)
    {
        if (scene_manager_ != nullptr)
        {
            if (!(setSystemProviderInScene(
                    current_scene_->scenePrivate(),
                    &(scene_manager_->isystemProvider()))))
            {
                DisplayLog::debug(
                    "Internal error: iSystemProvider was already set");
            }
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

SceneNodeFactory& SceneController::sceneNodeFactory() noexcept
{
    return scene_factory_;
}

SceneNodeFactory const& SceneController::sceneNodeFactory() const noexcept
{
    return scene_factory_;
}

void SceneController::requestExit()
{
    exit_requested_ = true;
}

bool SceneController::exitRequested() const
{
    return exit_requested_;
}

}  // namespace haf::scene
