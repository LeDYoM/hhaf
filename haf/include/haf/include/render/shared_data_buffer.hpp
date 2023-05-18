HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_SHARED_DATA_BUFFER_INCLUDE_HPP
#define HAF_RENDER_SHARED_DATA_BUFFER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/render/buffer_object_unsized.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <haf/include/render/buffer_object_construction_params.hpp>
#include <haf/include/render/render_object_data.hpp>

namespace haf::render
{
class SharedDataBuffer final
{
public:
    static constexpr const core::str_view StaticTypeName = "SharedDataBuffer";

    explicit SharedDataBuffer(BufferObjectUnsizedConstructParams&&
                                  bufferObjectUnsizedConstructParams);

    template <typename T>
    SharedDataBuffer(render::RenderObjectData<T>&& render_object_data) :
        SharedDataBuffer{
            core::move(render_object_data.bufferObjectUnsizedConstructParams())}
    {}

    template <typename U, typename T>
    SharedDataBuffer(U&& index, core::span<T> data) :
        SharedDataBuffer{
            RenderObjectData<T>{core::forward<U>(index), core::move(data)}}
    {}

    template <typename T, typename U>
    SharedDataBuffer(U&& index) :
        SharedDataBuffer{
            RenderObjectData<T>{core::forward<U>(index), core::span<T>{}}}
    {}

    ~SharedDataBuffer();

    bool autoBindToDefault();
    bool setBindingPoint(core::u32 const bindingPoint);

    template <typename T>
    bool write(T const& element)
    {
        T* const address{static_cast<T*>(lockForWrite(sizeof(T)))};
        *address = element;
        unlock();
        return true;
    }

    bool isValid() const;
    core::u32 handle() const noexcept;
    core::u32 sizeOfStruct() const noexcept;

    BufferSubObjects const& subObjects() const noexcept;

private:
    void *lockForWrite(core::u32 const size);
    void unlock();
    BufferObjectUnsized m_buffer_object_unsized;
};
}  // namespace haf::render

#endif
