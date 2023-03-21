HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_BUFFER_SUBOBJECT_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_BUFFER_SUBOBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/types.hpp>

namespace haf::res
{
class VertexBufferObject;

struct HAF_API VertexBufferSubObject
{
    VertexBufferObject* m_parent;
    core::str m_index;
    VertexFormat m_vertex_format;
    core::u32 m_element_size;
    core::u32 m_offset;

    VertexBufferObject const* const parent() const noexcept;
    core::str const& index() const noexcept;
    core::u32 bufferName() const noexcept;
    VertexFormat vertexFormat() const noexcept;
    core::u32 elementSize() const noexcept;
    core::u32 offset() const noexcept;
};

}  // namespace haf::res

#endif
