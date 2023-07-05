#include <haf/include/resources/vertex_array_object.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/vao_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "vertex_array_object_private.hpp"

using namespace haf::core;

namespace haf::res
{
VertexArrayObject::VertexArrayObject(sptr<Mesh> mesh, sptr<Shader> shader) :
    m_p{make_pimplp<VertexArrayObjectPriv>(ogl::generateVertexArrayObject(),
                                           core::move(mesh),
                                           core::move(shader),
                                           0U)}
{
    DisplayLog::debug(staticTypeName(), ": Creating vao...");
    DisplayLog::debug(staticTypeName(), ": vao id: ", m_p->m_vao);
    DisplayLog::debug(staticTypeName(), ": Setting shader in vao...");
    DisplayLog::debug(staticTypeName(), ": vao ", m_p->m_vao,
                      " associated to shader ", m_p->m_shader->handle());
    m_p->associateBuffersToAttribsInCurrentShader(m_p->m_mesh);
}

VertexArrayObject::~VertexArrayObject() = default;

bool VertexArrayObject::isValid() const
{
    return ogl::isValid(m_p->m_vao);
}

u32 VertexArrayObject::handle() const
{
    return static_cast<u32>(m_p->m_vao);
}

void VertexArrayObject::render()
{
    m_p->render();
}

sptr<Shader>& VertexArrayObject::shader() noexcept
{
    return m_p->m_shader;
}

}  // namespace haf::res
