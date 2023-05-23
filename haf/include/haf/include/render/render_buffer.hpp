HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDER_BUFFER_INCLUDE_HPP
#define HAF_RENDER_RENDER_BUFFER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/render/types.hpp>

namespace haf::render
{
class RenderBuffer
{
public:
    RenderBuffer(const void* const data,
                 core::s32 const size,
                 BufferUsage const bufferUsage,
                 BufferMode const bufferMode);

    core::u32 handle() const noexcept { return m_handle; }

    void* lock(core::s32 const size = -1) noexcept;
    void unlock() noexcept;

private:
    core::u32 m_handle;
    core::s32 m_size;
    BufferUsage m_bufferUsage;
    BufferMode m_bufferMode;
};
}  // namespace haf::render

#endif
