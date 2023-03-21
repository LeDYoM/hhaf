HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCE_CAST_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_CAST_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/iresource.hpp>
#include <haf/include/resources/resource_codes.hpp>

#include <haf/include/resources/shader_code.hpp>
#include <haf/include/resources/shader.hpp>
#include <haf/include/resources/vertex_buffer_object.hpp>
#include <haf/include/resources/vertex_array_object.hpp>
#include <haf/include/resources/material.hpp>
#include <haf/include/resources/mesh.hpp>

namespace haf::res
{
template <ResourceType res_type>
struct ResourceTypeToType;

template <>
struct ResourceTypeToType<ResourceType::VertexShaderCode>
{
    using type = VertexShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::TessellationControlShaderCode>
{
    using type = TessellationControlShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::TessellationEvaluationShaderCode>
{
    using type = TessellationEvaluationShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::GeometryShaderCode>
{
    using type = GeometryShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::FragmentShaderCode>
{
    using type = FragmentShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::ComputeShaderCode>
{
    using type = ComputeShaderCode;
};

template <>
struct ResourceTypeToType<ResourceType::Shader>
{
    using type = Shader;
};

template <>
struct ResourceTypeToType<ResourceType::VertexBufferObject>
{
    using type = VertexBufferObject;
};

template <>
struct ResourceTypeToType<ResourceType::Material>
{
    using type = Material;
};

template <>
struct ResourceTypeToType<ResourceType::Mesh>
{
    using type = Mesh;
};

template <typename DestType>
core::sptr<DestType> safe_resource_cast(core::sptr<IResource> resource) noexcept
{
    using std::static_pointer_cast;

    if constexpr (std::is_same_v<DestType, VertexShaderCode>)
    {
        if (resource->resourceType() == ResourceType::VertexShaderCode)
        {
            return static_pointer_cast<VertexShaderCode>(core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, TessellationControlShaderCode>)
    {
        if (resource->resourceType() ==
            ResourceType::TessellationControlShaderCode)
        {
            return static_pointer_cast<TessellationControlShaderCode>(
                core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType,
                                      TessellationEvaluationShaderCode>)
    {
        if (resource->resourceType() ==
            ResourceType::TessellationEvaluationShaderCode)
        {
            return static_pointer_cast<TessellationEvaluationShaderCode>(
                core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, GeometryShaderCode>)
    {
        if (resource->resourceType() == ResourceType::GeometryShaderCode)
        {

            return static_pointer_cast<GeometryShaderCode>(
                core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, FragmentShaderCode>)
    {
        if (resource->resourceType() == ResourceType::FragmentShaderCode)
        {

            return static_pointer_cast<FragmentShaderCode>(
                core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, ComputeShaderCode>)
    {
        if (resource->resourceType() == ResourceType::ComputeShaderCode)
        {

            return static_pointer_cast<ComputeShaderCode>(core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, Shader>)
    {
        if (resource->resourceType() == ResourceType::Shader)
        {
            return static_pointer_cast<Shader>(core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, VertexBufferObject>)
    {
        if (resource->resourceType() == ResourceType::VertexBufferObject)
        {
            return static_pointer_cast<VertexBufferObject>(
                core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, VertexArrayObject>)
    {
        if (resource->resourceType() == ResourceType::VertexArrayObject)
        {
            return static_pointer_cast<VertexArrayObject>(core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, Material>)
    {
        if (resource->resourceType() == ResourceType::Material)
        {
            return static_pointer_cast<Shader>(core::move(resource));
        }
    }
    else if constexpr (std::is_same_v<DestType, Mesh>)
    {
        if (resource->resourceType() == ResourceType::Mesh)
        {
            return static_pointer_cast<Mesh>(core::move(resource));
        }
    }

    return nullptr;
}

template <typename DestType>
void safe_resource_cast(core::sptr<IResource> resource,
                        core::sptr<DestType>& dest) noexcept
{
    dest = safe_resource_cast<DestType>(core::move(resource));
}

}  // namespace haf::res

#endif
