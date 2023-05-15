HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_BUFFER_OBJECT_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_BUFFER_OBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/render/buffer_subobject.hpp>
#include <haf/include/render/render_object_data.hpp>

namespace haf::res
{
class HAF_API VertexBufferObject final : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{
        ResourceType::VertexBufferObject};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    explicit VertexBufferObject(
        render::BufferObjectConstructParams&& bufferObjectConstructParams);

    template <typename T>
    VertexBufferObject(render::RenderObjectData<T>&& render_object_data) :
        VertexBufferObject{
            core::move(render_object_data.bufferObjectConstructParams())}
    {}

    template <typename U, typename T>
    VertexBufferObject(U&& index, core::span<T> data) :
        VertexBufferObject{render::RenderObjectData<T>{core::forward<U>(index),
                                                       core::move(data)}}
    {}

    ~VertexBufferObject() override;

    bool isValid() const override;
    core::u32 handle() const noexcept;
    core::u32 size() const noexcept;
    core::u32 sizeOfStruct() const noexcept;

    core::vector<render::BufferSubObject> const& subObjects() const noexcept;

private:
    struct VertexBufferObjectPriv;
    core::PImplPointer<VertexBufferObjectPriv> m_p;
};
}  // namespace haf::res

#endif
