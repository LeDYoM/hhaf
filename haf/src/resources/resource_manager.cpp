#include "resource_manager.hpp"
#include "system/system_provider.hpp"
#include <hlog/include/hlog.hpp>

using namespace haf::res;
using namespace haf::core;
using namespace fmath;

namespace haf::sys
{
ResourceManager::ResourceManager(SystemProvider& system_provider) :
    SystemBase{system_provider}
{}

ResourceManager::~ResourceManager() noexcept = default;

void ResourceManager::init()
{
    bool isOk{m_default_resources.loadDefaultResources(*this)};
    m_shader_manager.init();
    (void)(isOk);
}

sptr<IResource> ResourceManager::findResource(str_view rid) const
{
    auto const resource{m_resources.find(rid)};
    return (resource == m_resources.end()) ? nullptr : resource->second;
}

sptr<IResource> ResourceManager::findResourceOfType(
    ResourceType const resourceType,
    str_view rid) const
{
    auto const resource{findResource(rid)};
    return (resource == nullptr || resource->resourceType() != resourceType)
        ? nullptr
        : resource;
}

bool ResourceManager::addResource(str_view rid, sptr<IResource> resource)
{
    bool const resourceExists{findResource(rid)};
    if (resourceExists)
    {
        logger::DisplayLog::warn(StaticTypeName, ": Resource ", rid, " already exists");
    }
    else
    {
        auto shader_opt{safe_resource_cast<Shader>(resource)};
        if (shader_opt)
        {
            m_shader_manager.addShader(rid, core::move(shader_opt));
        }
        m_resources.add(rid, core::move(resource), false);
    }
    return !resourceExists;
}

bool ResourceManager::createResource(str_view rid,
                                     str_view const r_type_id,
                                     RawMemory data)
{
    return createResource(rid, fromResourceTypeId(r_type_id), core::move(data));
}

bool ResourceManager::createResource(str_view rid,
                                     ResourceType const r_type,
                                     RawMemory data)
{
    switch (r_type)
    {
        case ResourceType::VertexShaderCode:
        {
            return addResource(rid, msptr<VertexShaderCode>(move(data)));
        }
        break;
        case ResourceType::FragmentShaderCode:
        {
            return addResource(rid,
                               msptr<FragmentShaderCode>(core::move(data)));
        }
        break;
        default:
        break;
    }
    LogAsserter::log_assert(false,
                            "[ResourceManager]: Invalid parameters for create "
                            "resource shader code");
    return false;
}

bool ResourceManager::createResource(str_view rid,
                                     ResourceType const r_type,
                                     span<vector4df> data)
{
    (void)(rid);
    (void)(r_type);
    (void)(data);
    switch (r_type)
    {
        case ResourceType::VertexBufferObject:
        {
//            return addResource(rid, msptr<VertexBufferObject>(0, move(data)));
        }
        break;
        default:
        break;
    }
    LogAsserter::log_assert(false,
                            "[ResourceManager]: Invalid parameters for create "
                            "resource for render data buffer");
    return false;
}

template <ResourceType res_type, typename ResType>
void setIfResource(
    str_view id,
    sptr<ResType>& res,
    function<sptr<IResource>(ResourceType const, str_view)> const&
        findResourceOfType) noexcept
{
    if (res == nullptr)
    {
        logger::DisplayLog::info(ResourceManager::StaticTypeName,
                         ": Looking for resource ", id);

        sptr<IResource> r{findResourceOfType(res_type, id)};

        if (r != nullptr)
        {
            safe_resource_cast(core::move(r), res);
        }
    }
}

bool ResourceManager::createResourceFromResources(
    str_view rid,
    ResourceType const resourceType,
    vector<str> resourceIds)
{
    auto findResourceOfType{
        make_function(this, &ResourceManager::findResourceOfType)};

    switch (resourceType)
    {
        case ResourceType::Shader:
        {
            sptr<VertexShaderCode> vs;
            sptr<FragmentShaderCode> fs;

            for (const auto& id : resourceIds)
            {
                setIfResource<ResourceType::VertexShaderCode>(
                    id.to_view(), vs, findResourceOfType);
                setIfResource<ResourceType::FragmentShaderCode>(
                    id.to_view(), fs, findResourceOfType);
            }
            auto shader{msptr<Shader>(core::move(vs), nullptr, nullptr, nullptr,
                                      core::move(fs), nullptr)};
            return addResource(rid, core::move(shader));
        }
        break;
        case ResourceType::VertexArrayObject:
        {
            sptr<Shader> shader;
            sptr<Mesh> mesh;
            setIfResource<ResourceType::Shader>(resourceIds[0].to_view(),
                                                shader, findResourceOfType);
            setIfResource<ResourceType::Mesh>(resourceIds[1].to_view(), mesh,
                                              findResourceOfType);

            LogAsserter::log_assert(shader != nullptr, "Shader is empty");
            LogAsserter::log_assert(mesh != nullptr, "Mesh is empty");

            if (shader != nullptr && mesh != nullptr)
            {
                auto vertex_array_object{msptr<VertexArrayObject>(
                    core::move(mesh), core::move(shader))};
                return addResource(rid, core::move(vertex_array_object));
            }
        }
        break;
        case ResourceType::Mesh:
        {
            vector<sptr<VertexBufferObject>> vertex_buffer_objects(
                resourceIds.size());
            sptr<VertexBufferObject> temp;
            for (u32 count{0U}; count < resourceIds.size(); ++count)
            {
                temp.reset();
                setIfResource<ResourceType::VertexBufferObject>(
                    resourceIds[count].to_view(), temp, findResourceOfType);

                if (temp)
                {
                    vertex_buffer_objects.push_back(core::move(temp));
                }
            }
            auto mesh{msptr<Mesh>(core::move(vertex_buffer_objects))};
            return addResource(rid, core::move(mesh));
        }
        break;
        default:
        break;
    }

    return false;
}

DefaultResources const& ResourceManager::defaultResources() const
{
    return m_default_resources;
}

ShaderManager const& ResourceManager::shaderManager() const noexcept
{
    return m_shader_manager;
}

ShaderManager& ResourceManager::shaderManager() noexcept
{
    return m_shader_manager;
}

}  // namespace haf::sys
