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

}  // namespace haf::scene
