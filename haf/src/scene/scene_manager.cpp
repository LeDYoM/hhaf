#include "scene_manager.hpp"
#include "scene_controller.hpp"

#include <haf/include/component/component_factory.hpp>

#include "system/system_provider.hpp"
#include "window/window.hpp"
#include "resources/resource_manager.hpp"
#include "render/render_target.hpp"

#include <hlog/include/hlog.hpp>

#include <haf/include/scene_components/renderizable_group_component.hpp>
#include <haf/include/scene_components/transformation.hpp>

using namespace htps;
using namespace haf::sys;
using namespace haf::component;

namespace haf::scene
{
SceneManager::SceneManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, m_scene_controller{msptr<SceneController>()}
{
    m_scene_controller->setSceneManager(this);
}

SceneManager::~SceneManager() = default;

void SceneManager::start()
{
    addDefaultSceneSubsystems();
}

void SceneManager::update()
{
    m_scene_controller->update();
}

void SceneManager::finish()
{
    m_scene_controller->finish();
}

sptr<SceneController const> SceneManager::sceneController() const noexcept
{
    return m_scene_controller;
}

sptr<SceneController> SceneManager::sceneController() noexcept
{
    return m_scene_controller;
}

void SceneManager::switchToNextScene()
{
    m_scene_controller->switchToNextScene();
}

bool SceneManager::startScene(const htps::str& scene_name)
{
    return m_scene_controller->startScene(scene_name);
}

void SceneManager::requestExit()
{
    return m_scene_controller->requestExit();
}

bool SceneManager::exitRequested() const
{
    return m_scene_controller->exitRequested();
}

ComponentFactory& SceneManager::componentFactory()
{
    return m_scene_controller->componentFactory();
}

bool SceneManager::setNextApp(htps::str const&)
{
    return true;
}

SceneRenderContext& SceneManager::sceneRenderContext()
{
    return m_scene_controller->sceneRenderContext();
}

SceneRenderContext const& SceneManager::sceneRenderContext() const
{
    return m_scene_controller->sceneRenderContext();
}

void SceneManager::addDefaultSceneSubsystems()
{
    addSceneSubsystem(SceneSubsystem{str{Transformation::StaticTypeName},
                                     Transformation::StaticComponentOrder});

    addSceneSubsystem(
        SceneSubsystem{str{RenderizableGroupComponent::StaticTypeName},
                       RenderizableGroupComponent::StaticComponentOrder});
}

void SceneManager::addSceneSubsystem(SceneSubsystem&& scene_subsystem)
{
    m_scene_controller->addSceneSubsystem(core::move(scene_subsystem));
}

}  // namespace haf::scene
