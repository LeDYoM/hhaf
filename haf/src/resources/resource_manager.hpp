HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCEMANAGER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include "system/system_base.hpp"
#include "default_resources.hpp"
#include "shader_manager.hpp"

#include <haf/include/resources/resource_codes.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/resource_cast.hpp>

namespace haf::res
{
class Shader;
}  // namespace haf::res

namespace haf::sys
{
class ResourceManager final : public SystemBase
{
public:
    static constexpr char StaticTypeName[] = "ResourceManager";

    explicit ResourceManager(sys::SystemProvider& system_provider);
    ~ResourceManager();

    void init();

    bool createResource(core::str_view rid,
                     core::str_view const r_type_id,
                     core::RawMemory data);

    bool createResource(core::str_view rid,
                     res::ResourceType const r_type,
                     core::RawMemory data);

    bool createResource(core::str_view rid,
                     res::ResourceType const r_type,
                     core::span<fmath::vector4df> data);

    bool createResourceFromResources(core::str_view rid,
                                     res::ResourceType const resourceType,
                                     core::vector<core::str> resourceIds);

    template <typename T>
    bool aquireResource(core::str_view rid, core::sptr<T>& res) const
    {
        res = safe_resource_cast<T>(
            findResourceOfType(T::StaticResourceType, rid));
        return res != nullptr;
    }

    res::DefaultResources const& defaultResources() const;
    bool addResource(core::str_view rid, core::sptr<res::IResource> resource);
    res::ShaderManager& shaderManager() noexcept;
    res::ShaderManager const& shaderManager() const noexcept;

private:
    core::sptr<res::IResource> findResource(core::str_view rid) const;
    core::sptr<res::IResource> findResourceOfType(
        res::ResourceType const resourceType,
        core::str_view rid) const;

    core::Dictionary<core::sptr<res::IResource>> m_resources;
    res::DefaultResources m_default_resources;
    res::ShaderManager m_shader_manager;
};

}  // namespace haf::sys

#endif
