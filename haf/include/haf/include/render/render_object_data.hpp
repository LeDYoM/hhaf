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
    static constexpr core::u32 SIZE{getkNumSubElements<T>()};
    core::array<core::str, SIZE> index;
    core::span<T> data;

    RenderObjectData(core::array<core::str, SIZE>&& _index,
                     core::span<T> _data) :
        index{core::move(_index)}, data{core::move(_data)}
    {}

    RenderObjectData(core::str&& _index, core::span<T> _data) :
        index{core::array{core::move(_index)}}, data{core::move(_data)}
    {
        static_assert(SIZE == 1U);
    }

    BufferObjectUnsizedConstructParams bufferObjectUnsizedConstructParams()
        const noexcept
    {
        return BufferObjectUnsizedConstructParams{
            static_cast<const void*>(data.cbegin()),
            static_cast<core::s32>((data.empty() ? 1U : data.size()) *
                                   sizeof(T)),
            BufferUsage::Static, BufferMode::Draw,
            make_bufferSubObjects(core::move(index), getVertexFormats<T>())};
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
