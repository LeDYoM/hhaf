HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_BUFFER_OBJECT_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_BUFFER_OBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/core/math_types.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/types.hpp>
#include <haf/include/resources/vertex_buffer_subobject.hpp>
#include <haf/include/resources/vertex_formats.hpp>

namespace haf::res
{
class HAF_API VertexBufferObject : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{
        ResourceType::VertexBufferObject};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    VertexBufferObject(core::str index, core::span<core::vector4df> data);
    VertexBufferObject(core::str index, core::span<core::vector3df> data);
    VertexBufferObject(core::str index, core::span<core::f32> data);
    VertexBufferObject(core::array<core::str, 3U> const& indexes,
                       core::span<Position3fNormal3fTextureCoordinates2f> data);

    ~VertexBufferObject() override;

    bool isValid() const override;
    core::u32 handle() const noexcept;
    core::u32 size() const noexcept;
    core::u32 sizeOfStruct() const noexcept;

    core::vector<VertexBufferSubObject> const& subObjects() const noexcept;

private:
    struct RenderDataBufferPriv;
    core::PImplPointer<RenderDataBufferPriv> m_p;
};
}  // namespace haf::res

#endif
