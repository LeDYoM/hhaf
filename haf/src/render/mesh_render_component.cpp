#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <haf/include/render/mesh_render_context.hpp>

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include "scene/scene_manager.hpp"

namespace haf::render
{

void MeshRenderComponent::onAttached()
{
    addUpdater({this, &MeshRenderComponent::updateRender});

    auto& rManager{sys::getSystem<sys::ResourceManager>(attachedNode())};
    //    rManager.aquireResource("quad_vao", m_vao_object);
    rManager.aquireResource("cube_vao", m_vao_object);
}

void MeshRenderComponent::setMeshRenderContext(
    core::wptr<render::MeshRenderContext> wmesh_render_context)
{
    HasMeshRenderContext::setMeshRenderContext(wmesh_render_context);
    auto mrc{meshRenderContext()};
    mrc->shader = m_vao_object->shader();
}

void MeshRenderComponent::updateRender()
{
    m_vao_object->shader()->setUniform("haf_object_position",
                                       meshRenderContext()->modelViewMatrix());
    m_vao_object->render();
}

}  // namespace haf::render
