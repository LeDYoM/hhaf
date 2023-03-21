#include <haf/include/resources/vertex_buffer_object.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <cstddef>

using namespace haf::core;

namespace haf::res
{
struct VertexBufferObject::RenderDataBufferPriv
{
    ogl::Handle m_buffer_name;
    u32 m_size;
    u32 m_struct_size;
    vector<VertexBufferSubObject> m_subObjects;
};

VertexBufferObject::VertexBufferObject(str index, span<vector4df> data) :
    m_p{make_pimplp_forward<RenderDataBufferPriv>(
        ogl::createRenderBuffer(data),
        data.size(),
        sizeof(f32) * 4U,
        vector<VertexBufferSubObject>{{this, core::move(index),
                                       VertexFormat{BufferType::Float, 4U},
                                       sizeof(f32), 0U}})}
{}

VertexBufferObject::VertexBufferObject(str index, span<vector3df> data) :
    m_p{make_pimplp_forward<RenderDataBufferPriv>(
        ogl::createRenderBuffer(data),
        data.size(),
        sizeof(f32) * 3U,
        vector<VertexBufferSubObject>{{this, core::move(index),
                                       VertexFormat{BufferType::Float, 3U},
                                       sizeof(f32), 0U}})}
{}

VertexBufferObject::VertexBufferObject(str index, span<f32> data) :
    m_p{make_pimplp_forward<RenderDataBufferPriv>(
        ogl::createRenderBuffer(data),
        data.size(),
        sizeof(f32) * 1U,
        vector<VertexBufferSubObject>{{this, core::move(index),
                                       VertexFormat{BufferType::Float, 1U},
                                       sizeof(f32)}})}
{}

VertexBufferObject::VertexBufferObject(
    array<str, 3U> const& indexes,
    span<Position3fNormal3fTextureCoordinates2f> data) :
    m_p{make_pimplp<RenderDataBufferPriv>(
        ogl::createRenderBuffer(data),
        data.size(),
        sizeof(f32) * (3U + 3U + 2U),
        vector<VertexBufferSubObject>{
            {this, indexes[0], VertexFormat{BufferType::Float, 3U},
             sizeof(f32),
             offsetof(Position3fNormal3fTextureCoordinates2f, position)},
            {this, indexes[1], VertexFormat{BufferType::Float, 3U},
             sizeof(f32),
             offsetof(Position3fNormal3fTextureCoordinates2f, normal)},
            {this, indexes[2], VertexFormat{BufferType::Float, 2U},
             sizeof(f32),
             offsetof(Position3fNormal3fTextureCoordinates2f, textureuv)}})}
{}

VertexBufferObject::~VertexBufferObject() = default;

bool VertexBufferObject::isValid() const
{
    return ogl::isValid(m_p->m_buffer_name);
}

u32 VertexBufferObject::handle() const noexcept
{
    return static_cast<u32>(m_p->m_buffer_name);
}

u32 VertexBufferObject::sizeOfStruct() const noexcept
{
    return m_p->m_struct_size;
}

u32 VertexBufferObject::size() const noexcept
{
    return m_p->m_size;
}

vector<VertexBufferSubObject> const& VertexBufferObject::subObjects()
    const noexcept
{
    return m_p->m_subObjects;
}

}  // namespace haf::res