#include <haf/include/render/buffer_object_unsized.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>

using namespace haf::core;

namespace haf::render
{
BufferObjectUnsized::BufferObjectUnsized(
    BufferObjectUnsizedConstructParams&& bufferObjectUnsizedConstructParams) :
    m_buffer_name{core::move(bufferObjectUnsizedConstructParams.data),
                  core::move(bufferObjectUnsizedConstructParams.dataSize),
                  core::move(bufferObjectUnsizedConstructParams.bufferUsage),
                  core::move(bufferObjectUnsizedConstructParams.bufferMode)},
    m_vertex_format{
        core::move(bufferObjectUnsizedConstructParams.vertexFormat)}
{}

BufferObjectUnsized::~BufferObjectUnsized() = default;

bool BufferObjectUnsized::isValid() const
{
    return ogl::isValid(m_buffer_name.handle());
}

u32 BufferObjectUnsized::handle() const noexcept
{
    return static_cast<u32>(m_buffer_name.handle());
}

u32 BufferObjectUnsized::vertexFormatSize() const noexcept
{
    return m_vertex_format.vertexFormatSize();
}

BufferSubObject const& BufferObjectUnsized::subObject() const noexcept
{
    return m_vertex_format;
}

void *BufferObjectUnsized::lock(core::s32 size) noexcept
{
    return m_buffer_name.lock(size);
}

void BufferObjectUnsized::unlock() noexcept
{
    m_buffer_name.unlock();
}

}  // namespace haf::render
