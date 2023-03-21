#include <haf/include/render/mesh_component.hpp>
#include <haf/include/render/mesh_render_context.hpp>

#include <haf/include/component/component_definition.hpp>
#include <haf/include/scene_components/2.1/global_transformation_component.hpp>

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/scene_components/2.1/transformation_component.hpp>

using namespace haf::core;

namespace haf::render
{
void MeshComponent::onAttached()
{
    m_renderContext = core::msptr<MeshRenderContext>();
    getComponent<scene::TransformationComponent>()
        ->getComponent<scene::GlobalTransformationComponent>()
        ->setMeshRenderContext(m_renderContext);
    getComponent<MeshRenderComponent>()->setMeshRenderContext(m_renderContext);
}

}  // namespace haf::render
