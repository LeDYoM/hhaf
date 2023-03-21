#include <haf/include/render/has_mesh_render_context.hpp>
#include <haf/include/render/mesh_render_context.hpp>

using namespace haf::core;

namespace haf::render
{
HasMeshRenderContext::~HasMeshRenderContext() = default;

void HasMeshRenderContext::setMeshRenderContext(
    wptr<MeshRenderContext> wmesh_render_context)
{
    m_mesh_render_context = wmesh_render_context;
}

bool HasMeshRenderContext::hasMeshRenderContext() const noexcept
{
    return !(m_mesh_render_context.expired());
}

sptr<MeshRenderContext> HasMeshRenderContext::meshRenderContext() const noexcept
{
    return m_mesh_render_context.lock();
}

}  // namespace haf::render
