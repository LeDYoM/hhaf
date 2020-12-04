#include <haf/scene/i_include/scenecontroller.hpp>
#include <haf/scene/include/scene.hpp>
#include <haf/scene/i_include/scenemanager.hpp>

#include <haf/system/include/isystemprovider.hpp>
#include <system/i_include/systemprovider.hpp>
#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::scene
{
void SceneController::setSceneManager(rptr<SceneManager> scene_manager)
{
    LogAsserter::log_assert(scene_manager_ == nullptr,
                            "The scene_manager_ was set already");
    scene_manager_ = scene_manager;
}

bool SceneController::startScene(const str& sceneName)
{
    auto scene = scene_factory_.create(sceneName);
    startScene(sptr<Scene>(std::move(scene)));
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
    startScene(std::move(nextScene));
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

    if (auto current_scene = currentScene())
    {
        renderScene(*current_scene, false);
    }
}

void SceneController::renderScene(Scene& scene,
                                  bool parentTransformationChanged)
{
    render(scene, parentTransformationChanged);
}

void SceneController::render(SceneNode& scene_node,
                             bool parentTransformationChanged)
{
    if (scene_node.prop<Visible>().get())
    {
        // Update the node components
        scene_node.updateComponents();

        // Update node
        scene_node.update();

        parentTransformationChanged |=
            scene_node.updateLocalTransformationsIfNecessary();

        if (parentTransformationChanged)
        {
            scene_node.updateGlobalTransformation(
                scene_node.parent() ? scene_node.parent()->globalTransform()
                                    : Matrix4x4::Identity);
        }

        scene_node.updateRenderizables();
        for (SceneNodesGroup::SceneNodeVector::value_type& group :
             scene_node.sceneNodes())
        {
            render(*group, parentTransformationChanged);
        }
    }
}

void SceneController::finish()
{
    if (!currentSceneIsNull())
    {
        terminateCurrentScene();
    }
}

const sptr<Scene>& SceneController::currentScene() const noexcept
{
    return current_scene_;
}

void SceneController::startScene(sptr<Scene> scene)
{
    current_scene_ = std::move(scene);
    if (current_scene_)
    {
        if (scene_manager_)
        {
            current_scene_->scene_manager_ = scene_manager_;
            if (!(current_scene_->setSystemProvider(
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

const SceneNodeFactory& SceneController::sceneNodeFactory() const noexcept
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
