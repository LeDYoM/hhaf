#include <haf/include/render/mesh_render_component.hpp>
#include <haf/include/component/component_definition.hpp>

#include "system/get_system.hpp"
#include "resources/resource_manager.hpp"
#include "scene/scene_manager.hpp"
#include <haf/include/resources/vertex_array_object.hpp>

#include <haf/include/debug_system/idebug_variables.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace haf::core;

namespace haf::render
{
struct MeshRenderComponent::PrivateComponentData
{
    core::sptr<res::VertexArrayObject> m_vao_object;
};

MeshRenderComponent::MeshRenderComponent() :
    m_p{make_pimplp<PrivateComponentData>()}
{}

MeshRenderComponent::~MeshRenderComponent() = default;

void MeshRenderComponent::onAttached()
{
    addUpdater({this, &MeshRenderComponent::updateRender});

    auto& rManager{sys::getSystem<sys::ResourceManager>(attachedNode())};
    //    rManager.aquireResource("quad_vao", m_vao_object);
    rManager.aquireResource("cube_vao", m_p->m_vao_object);
}

sptr<res::Shader> MeshRenderComponent::shader() const noexcept
{
    return m_p->m_vao_object->shader();
}

void MeshRenderComponent::updateRender()
{
    static int a = 0;
    ++a;

    FROM_COMPONENT_SET_DEBUG_VARIABLE_VALUE(vertex_render, (54 + a));

    m_p->m_vao_object->shader()->setUniform(
        "haf_object_position",
        sys::getSystem<scene::SceneManager>(attachedNode())
            .sceneRenderContext()
            .modelViewMatrix());

    m_p->m_vao_object->render();
}

}  // namespace haf::render
