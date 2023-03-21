HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_MESH_RENDER_COMPONENT_INCLUDE_HPP
#define HAF_RENDER_MESH_RENDER_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/resources/vertex_array_object.hpp>
#include <haf/include/render/has_mesh_render_context.hpp>

namespace haf::render
{
class HAF_API MeshRenderComponent final
    : public component::ComponentBase<"MeshRenderComponent">,
      public HasMeshRenderContext
{
public:
    void setMeshRenderContext(
        core::wptr<render::MeshRenderContext> wmesh_render_context) override;

    void onAttached() override;
    void updateRender();

private:
    core::sptr<res::VertexArrayObject> m_vao_object;
};

}  // namespace haf::render

#endif
