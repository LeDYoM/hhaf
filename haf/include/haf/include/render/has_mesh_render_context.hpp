HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_HAS_MESH_RENDER_CONTEXT_INCLUDE_HPP
#define HAF_RENDER_HAS_MESH_RENDER_CONTEXT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>

namespace haf::render
{
class MeshRenderContext;

class HasMeshRenderContext
{
public:
    virtual ~HasMeshRenderContext();
    virtual void setMeshRenderContext(
        core::wptr<render::MeshRenderContext> wmesh_render_context);

    bool hasMeshRenderContext() const noexcept;
    core::sptr<MeshRenderContext> meshRenderContext() const noexcept;
private:
    core::wptr<MeshRenderContext> m_mesh_render_context;
};

}  // namespace haf::render

#endif
