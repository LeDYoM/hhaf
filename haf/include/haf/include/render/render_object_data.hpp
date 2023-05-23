HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_OBJECT_DATA_INCLUDE_HPP
#define HAF_RENDER_OBJECT_DATA_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/render/buffer_object_construction_params.hpp>

namespace haf::render
{
template <typename T>
struct RenderObjectData
{
    core::str index;
    core::span<T> data;

    RenderObjectData(core::str&& _index, core::span<T> _data) :
        index{core::move(_index)}, data{core::move(_data)}
    {}

    BufferObjectUnsizedConstructParams bufferObjectUnsizedConstructParams()
        const noexcept
    {
        return BufferObjectUnsizedConstructParams{
            static_cast<const void*>(data.cbegin()),
            static_cast<core::s32>((data.empty() ? 1U : data.size()) *
                                   sizeof(T)),
            BufferUsage::Static, BufferMode::Draw,
            make_bufferSubObject(index, VertexFormat{getVertexFormat<T>()})};
    }

    BufferObjectConstructParams bufferObjectConstructParams() const noexcept
    {
        return BufferObjectConstructParams{bufferObjectUnsizedConstructParams(),
                                           data.size()};
    }
};

template <typename T>
RenderObjectData(core::str, core::span<T>) -> RenderObjectData<T>;

}  // namespace haf::render

#endif
