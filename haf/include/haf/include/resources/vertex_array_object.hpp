HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCE_VERTEX_ARRAY_OBJECT_INCLUDE_HPP
#define HAF_RESOURCE_VERTEX_ARRAY_OBJECT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>

#include <haf/include/resources/vertex_buffer_object.hpp>
#include <haf/include/resources/mesh.hpp>
#include <haf/include/resources/shader.hpp>

namespace haf::res
{
class HAF_API VertexArrayObject : public IResource
{
public:
    static constexpr ResourceType const StaticResourceType{
        ResourceType::VertexArrayObject};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    static constexpr auto staticTypeName()
    {
        return resourceTypeName(StaticResourceType);
    }

    VertexArrayObject(core::sptr<Mesh> mesh, core::sptr<Shader> shader);
    ~VertexArrayObject() override;

    bool isValid() const override;
    core::u32 handle() const;

    void render();

    core::sptr<Shader>& shader() noexcept;
    friend struct ShaderVaoHelper;

private:
    void associateBuffersToAttribsInCurrentShader();

    struct VertexArrayObjectPriv;
    core::PImplPointer<VertexArrayObjectPriv> m_p;
};
}  // namespace haf::res

#endif
