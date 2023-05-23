#include <haf/include/resources/vertex_buffer_object.hpp>
#include <haf/include/render/buffer_object.hpp>

using namespace haf::core;

namespace haf::res
{
struct VertexBufferObject::VertexBufferObjectPriv
{
    render::BufferObject m_buffer_object;
};

VertexBufferObject::VertexBufferObject(
    render::BufferObjectConstructParams&& bufferObjectConstructParams) :
    m_p{make_pimplp<VertexBufferObjectPriv>(
        render::BufferObject{core::move(bufferObjectConstructParams)})}
{}

VertexBufferObject::~VertexBufferObject() = default;

bool VertexBufferObject::isValid() const
{
    return m_p != nullptr && m_p->m_buffer_object.isValid();
}

u32 VertexBufferObject::handle() const noexcept
{
    return m_p->m_buffer_object.handle();
}

u32 VertexBufferObject::vertexFormatSize() const noexcept
{
    return m_p->m_buffer_object.vertexFormatSize();
}

u32 VertexBufferObject::size() const noexcept
{
    return m_p->m_buffer_object.size();
}

render::BufferSubObject const& VertexBufferObject::subObject()
    const noexcept
{
    return m_p->m_buffer_object.subObject();
}

}  // namespace haf::res