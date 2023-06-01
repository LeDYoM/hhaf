#include "scene_manager.hpp"
#include "component_register.hpp"

#include <haf/include/scene/scene_node.hpp>

#include "system/system_provider.hpp"
#include <hlog/include/hlog.hpp>

using namespace haf::sys;
using namespace haf::core;

namespace haf::scene
{
SceneManager::SceneManager(sys::SystemProvider& system_provider) :
    SystemBase{system_provider},
    m_scene_render_context_for_system{this->isystemProvider()}
{}

SceneManager::~SceneManager() = default;

void SceneManager::init()
{
    ComponentRegister component_register{*this};
    component_register();

    m_rootSceneNode = muptr<SceneNode>(&isystemProvider());
    m_scene_render_context_for_system.init();
}

void SceneManager::update()
{
    m_scene_render_context_for_system.beginFrame();
    m_rootSceneNode->update();
    m_scene_render_context_for_system.endFrame();
}

void SceneManager::finish()
{}

bool SceneManager::registerComponent(
    str_view componentType,
    component::ComponentCreateFunction component_create_function)
{
    return m_component_factory.registerObjectType(
        componentType, htps::move(component_create_function));
}

bool SceneManager::instanciateRootComponent(str_view componentType)
{
    return m_rootSceneNode->attachComponent(componentType) != nullptr;
}

sptr<component::Component> SceneManager::instantiateComponent(str_view name)
{
    sptr<component::Component> component{m_component_factory.create(name)};
    DisplayLog::warn_if(component == nullptr, "Component ", name,
                        " not found in component factory");
    return component;
}

rptr<SceneNode> SceneManager::rootSceneNode() const
{
    return m_rootSceneNode.get();
}

SceneRenderContextForSystem&
SceneManager::sceneRenderContextForSystem() noexcept
{
    return m_scene_render_context_for_system;
}

SceneRenderContextForSystem const& SceneManager::sceneRenderContextForSystem()
    const noexcept
{
    return m_scene_render_context_for_system;
}

SceneRenderContext& SceneManager::sceneRenderContext() noexcept
{
    return m_scene_render_context_for_system;
}

SceneRenderContext const& SceneManager::sceneRenderContext() const noexcept
{
    return m_scene_render_context_for_system;
}

SceneRenderContextView& SceneManager::sceneRenderContextView() noexcept
{
    return m_scene_render_context_for_system;
}

SceneRenderContextView const& SceneManager::sceneRenderContextView()
    const noexcept
{
    return m_scene_render_context_for_system;
}

}  // namespace haf::scene
