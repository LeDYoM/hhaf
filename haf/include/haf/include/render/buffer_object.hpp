HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_BUFFER_OBJECT_INCLUDE_HPP
#define HAF_RENDER_BUFFER_OBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/render/buffer_subobject.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <haf/include/render/buffer_object_construction_params.hpp>
#include <haf/include/render/buffer_object_unsized.hpp>

namespace haf::render
{
class HAF_API BufferObject final
{
public:
    explicit BufferObject(
        BufferObjectConstructParams&& bufferObjectConstructParams);

    ~BufferObject();

    bool isValid() const;
    core::u32 handle() const noexcept;
    core::u32 size() const noexcept;
    core::u32 sizeOfStruct() const noexcept;

    BufferSubObjects const& subObjects() const noexcept;

private:
    BufferObjectUnsized m_bufferObjectUnsized;
    core::u32 m_size;
};
}  // namespace haf::render

#endif
