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

    core::str const& index() const noexcept { return m_index; }
    core::s32 location() const noexcept { return m_location; }
    VertexFormat vertexFormat() const noexcept { return m_vertex_format; }
};

using BufferSubObjects = core::vector<BufferSubObject>;

BufferSubObject make_bufferSubObject(core::str&& index,
                                     VertexFormat&& data) noexcept;

BufferSubObject make_bufferSubObject(core::str&& index,
                                     core::s32 const location,
                                     VertexFormat&& data) noexcept;

template <core::size_type N>
constexpr BufferSubObjects make_bufferSubObjects(
    core::array<core::str, N> indexes,
    core::array<VertexFormat, N> data)
{
    BufferSubObjects result{N};
    for (core::size_type i{0U}; i < N; ++i)
    {
        result.emplace_back(
            make_bufferSubObject(core::move(indexes[i]), core::move(data[i])));
    }
    return result;
}

core::s32 getIndexForName(BufferSubObjects const& container,
                          core::str const& name);

VertexFormat getVertexFormatForIndex(BufferSubObjects const& container,
                                     core::s32 const index);

VertexFormat getVertexFormatForName(BufferSubObjects const& container,
                                    core::str_view const index);

bool indexExists(BufferSubObjects const& container, core::s32 const index);

core::u32 bufferStructSize(BufferSubObjects const& bufferSubObjects);

}  // namespace haf::render

#endif
