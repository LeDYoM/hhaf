#include <haf/include/render/render_buffer.hpp>
#include <hogl/include/buffer_functions.hpp>

using namespace haf::core;

namespace
{
constexpr haf::ogl::BufferUsage convert(
    haf::render::BufferUsage const& bufferUsage) noexcept
{
    switch (bufferUsage)
    {
        default:
        case haf::render::BufferUsage::Static:
            return haf::ogl::BufferUsage::Static;
            break;

        case haf::render::BufferUsage::Dynamic:
            return haf::ogl::BufferUsage::Dynamic;
            break;
    }
}

constexpr haf::ogl::BufferMode convert(
    haf::render::BufferMode const& bufferMode) noexcept
{
    switch (bufferMode)
    {
        default:
        case haf::render::BufferMode::Draw:
            return haf::ogl::BufferMode::Draw;
            break;
    }
}
}  // namespace
namespace haf::render
{
RenderBuffer::RenderBuffer(const void* const data,
                           s32 const size,
                           BufferUsage const bufferUsage,
                           BufferMode const bufferMode) :
    m_handle{ogl::createRenderBuffer(data,
                                     size,
                                     convert(bufferUsage),
                                     convert(bufferMode))},
    m_size{size},
    m_bufferUsage{bufferUsage},
    m_bufferMode{bufferMode}
{}

void* RenderBuffer::lock(core::s32 const size) noexcept
{
    return ogl::getAddressForWriting(m_handle, size < 0 ? m_size : size);
}

void RenderBuffer::unlock() noexcept
{
    ogl::unlock(m_handle);
}

}  // namespace haf::render
