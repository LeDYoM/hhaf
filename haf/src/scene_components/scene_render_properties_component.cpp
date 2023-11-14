#include <haf/include/scene_components/scene_render_properties_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"

using namespace haf::core;

namespace haf::scene
{
struct SceneRenderPropertiesComponent::PrivateComponentData
{
    SceneRenderContext* m_sceneRenderContext{nullptr};
};

SceneRenderPropertiesComponent::SceneRenderPropertiesComponent() :
    m_p{make_pimplp<PrivateComponentData>()}
{}

SceneRenderPropertiesComponent::~SceneRenderPropertiesComponent() = default;

void SceneRenderPropertiesComponent::onAttached()
{
    m_p->m_sceneRenderContext =
        &(sys::getSystem<scene::SceneManager>(attachedNode())
              .sceneRenderContext());
}

void SceneRenderPropertiesComponent::setViewMatrix(
    math::Matrix4x4 const& matrix)
{
    LogAsserter::log_assert(m_p->m_sceneRenderContext != nullptr);
    m_p->m_sceneRenderContext->setCameraMatrix(matrix);
}

void SceneRenderPropertiesComponent::setModelMatrix(
    math::Matrix4x4 const& matrix)
{
    LogAsserter::log_assert(m_p->m_sceneRenderContext != nullptr);
    m_p->m_sceneRenderContext->setCurrentModelViewMatrix(matrix);
}

math::Matrix4x4 const& SceneRenderPropertiesComponent::viewMatrix()
    const noexcept
{
    return m_p->m_sceneRenderContext->cameraMatrix();
}

math::Matrix4x4 const& SceneRenderPropertiesComponent::modelMatrix()
    const noexcept
{
    return m_p->m_sceneRenderContext->modelViewMatrix();
}

void SceneRenderPropertiesComponent::getOrUpdateRenderDataIndex(
    core::size_type& index,
    render::RenderData*& render_data) noexcept
{
    m_p->m_sceneRenderContext->getOrUpdateRenderDataIndex(index, render_data);
    
}

}  // namespace haf::scene
