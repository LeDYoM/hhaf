#include <haf/include/resources/vertex_buffer_subobject.hpp>
#include <haf/include/resources/vertex_buffer_object.hpp>
#include <hogl/include/types.hpp>

using namespace haf::core;

namespace haf::res
{
VertexBufferObject const* const VertexBufferSubObject::parent() const noexcept
{
    return m_parent;
}

str const& VertexBufferSubObject::index() const noexcept
{
    return m_index;
}

VertexFormat VertexBufferSubObject::vertexFormat() const noexcept
{
    return m_vertex_format;
}

u32 VertexBufferSubObject::elementSize() const noexcept
{
    return m_element_size;
}

u32 VertexBufferSubObject::offset() const noexcept
{
    return m_offset;
}

}  // namespace haf::res