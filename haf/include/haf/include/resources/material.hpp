HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_MATERIAL_RESOURCE_INCLUDE_HPP
#define HAF_SCENE_MATERIAL_RESOURCE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/shader.hpp>

namespace haf::res
{
class HAF_API Material : public IResource
{
    static constexpr ResourceType const StaticResourceType{
        ResourceType::Material};

    constexpr ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }

    explicit Material(core::sptr<Shader> shader);
    ~Material() override;

private:
    core::sptr<Shader> m_shader;
};
}  // namespace haf::res

#endif
