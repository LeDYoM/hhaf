#include <haf/include/resources/mesh.hpp>

using namespace haf::core;

namespace haf::res
{
Mesh::Mesh(vector<sptr<VertexBufferObject>> vertex_buffer_objects) :
    m_vertex_buffer_objects{core::move(vertex_buffer_objects)}
{}

Mesh::~Mesh() = default;

rptr<VertexBufferObject> Mesh::vertexBufferObject(
    size_type const index) const noexcept
{
    return ((index < m_vertex_buffer_objects.size())
                ? m_vertex_buffer_objects[index].get()
                : nullptr);
}

vector<sptr<VertexBufferObject>> const& Mesh::vertexBufferObjects()
    const noexcept
{
    return m_vertex_buffer_objects;
}

}  // namespace haf::res
