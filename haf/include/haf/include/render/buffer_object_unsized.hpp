HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_BUFFER_OBJECT_UNSIZED_INCLUDE_HPP
#define HAF_RENDER_BUFFER_OBJECT_UNSIZED_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/render/buffer_subobject.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <haf/include/render/buffer_object_construction_params.hpp>

namespace haf::render
{
class BufferObjectUnsized final
{
public:
    explicit BufferObjectUnsized(BufferObjectUnsizedConstructParams&&
                                     bufferObjectUnsizedConstructParams);

    ~BufferObjectUnsized();

    bool isValid() const;
    core::u32 handle() const noexcept;
    core::u32 sizeOfStruct() const noexcept;

    BufferSubObjects const& subObjects() const noexcept;

    void *lock(core::s32 size = -1) noexcept;
    void unlock() noexcept;

private:
    RenderBuffer m_buffer_name;
    BufferSubObjects m_vertex_formats;
};
}  // namespace haf::render

#endif
