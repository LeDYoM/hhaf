#include "scene_controller.hpp"
#include "scene_manager.hpp"
#include "scene_render.hpp"
#include "../scene_components/scene_component_private.hpp"
#include "system/system_provider.hpp"
#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/system/isystem_provider.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace logger;
using namespace haf::component;

namespace haf::scene
{
void SceneController::setSceneManager(rptr<SceneManager> scene_manager)
{
    LogAsserter::log_assert(m_scene_manager == nullptr,
                            "The scene_manager_ was set already");
    LogAsserter::log_assert(scene_manager != nullptr,
                            "Invalid parameter scene_node");
    m_scene_manager = scene_manager;
}

bool SceneController::startScene(str const& sceneName)
{
    auto scene{m_component_factory.create(sceneName)};
    startScene(sptr<SceneComponent>(htps::move(scene)));
    return true;
}

void SceneController::switchToNextScene()
{
    m_switch_scene = true;
}

void SceneController::deferredSwitchScene()
{
    terminateCurrentScene();

    // Prepare next Scene
    sptr<SceneComponent> nextScene{nullptr};
    if (!m_exit_requested)
    {
        auto const next_scene_name{m_current_scene->nextSceneName()};

        if (!next_scene_name.empty())
        {
            nextScene = m_component_factory.create(next_scene_name);
            DisplayLog::error_if(nextScene == nullptr,
                                 "Requested next scene of type: ",
                                 next_scene_name, ", but cannot be created");
        }
    }

    //    DisplayLog::info("Setting new scene: ",
    //                     nextScene ? nextScene->name() : "<nullptr>");
    startScene(htps::move(nextScene));
}

void SceneController::terminateCurrentScene()
{
    LogAsserter::log_assert(m_current_scene != nullptr,
                            "Unexpected nullptr in current_scene");
    //    DisplayLog::info("Terminating scene ", m_current_scene->name());
    m_current_scene->onFinished();
}

void SceneController::update()
{
    if (m_switch_scene)
    {
        deferredSwitchScene();
        m_switch_scene = false;
    }

    if (m_current_scene != nullptr)
    {
        Matrix4x4 startMatrix{Matrix4x4::Identity};
        render(*m_root_scene_node,
               SceneRenderContext{false, startMatrix});
    }
}

void SceneController::finish()
{
    if (!currentSceneIsNull())
    {
        terminateCurrentScene();
    }
}

bool SceneController::setSystemProviderInScene(
    rptr<SceneComponent::SceneComponentPrivate> const scene_private,
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

void SceneController::startScene(sptr<SceneComponent> scene)
{
    m_current_scene = htps::move(scene);
    if (m_current_scene != nullptr)
    {
        if (m_scene_manager != nullptr)
        {
            m_root_scene_node = msptr<SceneNode>(nullptr, "Scene");
            m_current_scene->attachedNode_ = m_root_scene_node.get();

            if (!(setSystemProviderInScene(
                    m_current_scene->scenePrivate(),
                    &(m_scene_manager->isystemProvider()))))
            {
                DisplayLog::debug(
                    "Internal error: iSystemProvider was already set");
            }
            m_root_scene_node->attachComponent(m_current_scene);
        }
    }
}

bool SceneController::currentSceneIsNull()
{
    return m_current_scene == nullptr;
}

bool SceneController::isActive()
{
    return !currentSceneIsNull();
}

ComponentFactory& SceneController::componentFactory() noexcept
{
    return m_component_factory;
}

ComponentFactory const& SceneController::componentFactory() const noexcept
{
    return m_component_factory;
}

void SceneController::requestExit()
{
    m_exit_requested = true;
}

bool SceneController::exitRequested() const
{
    return m_exit_requested;
}

}  // namespace haf::scene
