HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_BUFFER_SUBOBJECT_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_BUFFER_SUBOBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/render/types.hpp>
#include <haf/include/render/vertex_formats.hpp>

namespace haf::render
{

struct HAF_API BufferSubObject
{
    core::str m_index;
    core::s32 m_location;
    VertexFormat m_vertex_format;

    constexpr core::str const& index() const noexcept { return m_index; }
    constexpr core::s32 location() const noexcept { return m_location; }
    constexpr VertexFormat vertexFormat() const noexcept
    {
        return m_vertex_format;
    }
    constexpr core::u32 vertexFormatSize() const noexcept
    {
        return m_vertex_format.sizeOfElement();
    }
};

using BufferSubObjects = core::vector<BufferSubObject>;

BufferSubObject make_bufferSubObject(core::str index,
                                     VertexFormat&& data) noexcept;

BufferSubObject make_bufferSubObject(core::str index,
                                     core::s32 const location,
                                     VertexFormat&& data) noexcept;

core::s32 getIndexForName(BufferSubObjects const& container,
                          core::str const& name);

VertexFormat getVertexFormatForIndex(BufferSubObjects const& container,
                                     core::s32 const index);

VertexFormat getVertexFormatForName(BufferSubObjects const& container,
                                    core::str_view const index);

bool indexExists(BufferSubObjects const& container, core::s32 const index);

}  // namespace haf::render

#endif
