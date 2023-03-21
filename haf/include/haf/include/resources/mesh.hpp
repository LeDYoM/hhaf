HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_MESH_RESOURCE_INCLUDE_HPP
#define HAF_RESOURCES_MESH_RESOURCE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/shader.hpp>

namespace haf::res
{
class HAF_API Mesh : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{ResourceType::Mesh};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    static constexpr auto staticTypeName()
    {
        return resourceTypeName(StaticResourceType);
    }

    explicit Mesh(
        core::vector<core::sptr<VertexBufferObject>> vertex_buffer_objects);
    ~Mesh() override;

    core::rptr<VertexBufferObject> vertexBufferObject(
        core::size_type const index) const noexcept;

    core::vector<core::sptr<VertexBufferObject>> const& vertexBufferObjects()
        const noexcept;

private:
    core::vector<core::sptr<VertexBufferObject>> m_vertex_buffer_objects;
};
}  // namespace haf::res

#endif
