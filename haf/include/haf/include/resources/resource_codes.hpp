HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCE_CODES_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_CODES_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::res
{
static constexpr char const kNullResource[]{"Null"};
static constexpr char const kVertexShaderCode[]{"VertexShaderCode"};
static constexpr char const kTessellationControlShaderCode[]{
    "TessellationControlShaderCode"};
static constexpr char const kTessellationEvaluationShaderCode[]{
    "TessellationEvaluationShaderCode"};
static constexpr char const kGeometryShaderCode[]{"GeometryShaderCode"};
static constexpr char const kFragmentShaderCode[]{"FragmentShaderCode"};
static constexpr char const kComputeShaderCode[]{"ComputeShaderCode"};
static constexpr char const kShader[]{"Shader"};
static constexpr char const kRenderDataBuffer[]{"VertexBufferObject"};
static constexpr char const kVertexArrayObject[]{"VertexArrayObject"};
static constexpr char const kMaterial[]{"Material"};
static constexpr char const kMesh[]{"Mesh"};
static constexpr char const kImage[]{"Image"};
static constexpr char const kTexture[]{"FragmentShaderCode"};
static constexpr char const kFont[]{"ComputeShaderCode"};
static constexpr char const kRawData[]{"RawData"};
static constexpr char const kTextData[]{"TextData"};

static constexpr char const kNullResourceId[]{"nul"};
static constexpr char const kVertexShaderCodeId[]{"vsc"};
static constexpr char const kTessellationControlShaderCodeId[]{"tesc"};
static constexpr char const kTessellationEvaluationShaderCodeId[]{"tcsc"};
static constexpr char const kGeometryShaderCodeId[]{"gsc"};
static constexpr char const kFragmentShaderCodeId[]{"fsc"};
static constexpr char const kComputeShaderCodeId[]{"csc"};
static constexpr char const kShaderId[]{"shr"};
static constexpr char const kRenderDataBufferId[]{"rdb"};
static constexpr char const kVertexArrayObjectId[]{"vao"};
static constexpr char const kMaterialId[]{"mtl"};
static constexpr char const kMeshId[]{"msh"};
static constexpr char const kImageId[]{"img"};
static constexpr char const kTextureId[]{"tex"};
static constexpr char const kFontId[]{"fnt"};
static constexpr char const kRawDataId[]{"rad"};
static constexpr char const kTextDataId[]{"ted"};

enum class ResourceType : core::u32
{
    Unknown = 0U,
    NullResource,
    VertexShaderCode,
    TessellationControlShaderCode,
    TessellationEvaluationShaderCode,
    GeometryShaderCode,
    FragmentShaderCode,
    ComputeShaderCode,
    Shader,
    VertexBufferObject,
    VertexArrayObject,
    Material,
    Mesh,
    Image,
    Texture,
    Font,
    RawData,
    TextData
};

static constexpr core::str_view resourceTypeName(
    ResourceType const resource_type)
{
    switch (resource_type)
    {
        case ResourceType::NullResource:
            return kNullResource;
            break;
        case ResourceType::VertexShaderCode:
            return kVertexShaderCode;
            break;
        case ResourceType::TessellationControlShaderCode:
            return kTessellationControlShaderCode;
            break;
        case ResourceType::TessellationEvaluationShaderCode:
            return kTessellationEvaluationShaderCode;
            break;
        case ResourceType::GeometryShaderCode:
            return kGeometryShaderCode;
            break;
        case ResourceType::FragmentShaderCode:
            return kFragmentShaderCode;
            break;
        case ResourceType::ComputeShaderCode:
            return kVertexShaderCode;
            break;
        case ResourceType::Shader:
            return kShader;
            break;
        case ResourceType::VertexBufferObject:
            return kRenderDataBuffer;
            break;
        case ResourceType::VertexArrayObject:
            return kVertexArrayObject;
            break;
        case ResourceType::Material:
            return kMaterial;
            break;
        case ResourceType::Mesh:
            return kMesh;
            break;
        case ResourceType::Image:
            return kImage;
            break;
        case ResourceType::Texture:
            return kTexture;
            break;
        case ResourceType::Font:
            return kFont;
            break;
        case ResourceType::RawData:
            return kRawData;
            break;
        case ResourceType::TextData:
            return kTextData;
            break;
    }
    return "";
}

static constexpr core::str_view resourceTypeId(ResourceType const resource_type)
{
    switch (resource_type)
    {
        case ResourceType::NullResource:
            return kNullResourceId;
            break;
        case ResourceType::VertexShaderCode:
            return kVertexShaderCodeId;
            break;
        case ResourceType::TessellationControlShaderCode:
            return kTessellationControlShaderCodeId;
            break;
        case ResourceType::TessellationEvaluationShaderCode:
            return kTessellationEvaluationShaderCodeId;
            break;
        case ResourceType::GeometryShaderCode:
            return kGeometryShaderCodeId;
            break;
        case ResourceType::FragmentShaderCode:
            return kFragmentShaderCodeId;
            break;
        case ResourceType::ComputeShaderCode:
            return kComputeShaderCodeId;
            break;
        case ResourceType::Shader:
            return kShaderId;
            break;
        case ResourceType::VertexBufferObject:
            return kRenderDataBufferId;
            break;
        case ResourceType::VertexArrayObject:
            return kVertexArrayObjectId;
            break;
        case ResourceType::Material:
            return kMaterialId;
            break;
        case ResourceType::Mesh:
            return kMeshId;
            break;
        case ResourceType::Image:
            return kImageId;
            break;
        case ResourceType::Texture:
            return kTextureId;
            break;
        case ResourceType::Font:
            return kFontId;
            break;
        case ResourceType::RawData:
            return kRawDataId;
            break;
        case ResourceType::TextData:
            return kTextDataId;
            break;
    }
    return "";
}

static constexpr ResourceType fromResourceTypeId(core::str_view rid)
{
    if (rid == kNullResourceId)
    {
        return ResourceType::NullResource;
    }
    else if (rid == kVertexShaderCodeId)
    {
        return ResourceType::VertexShaderCode;
    }
    else if (rid == kTessellationControlShaderCodeId)
    {
        return ResourceType::TessellationControlShaderCode;
    }
    else if (rid == kTessellationEvaluationShaderCodeId)
    {
        return ResourceType::TessellationEvaluationShaderCode;
    }
    else if (rid == kGeometryShaderCodeId)
    {
        return ResourceType::GeometryShaderCode;
    }
    else if (rid == kFragmentShaderCodeId)
    {
        return ResourceType::FragmentShaderCode;
    }
    else if (rid == kComputeShaderCodeId)
    {
        return ResourceType::ComputeShaderCode;
    }
    else if (rid == kShaderId)
    {
        return ResourceType::Shader;
    }
    else if (rid == kRenderDataBufferId)
    {
        return ResourceType::VertexBufferObject;
    }
    else if (rid == kVertexArrayObject)
    {
        return ResourceType::VertexArrayObject;
    }
    else if (rid == kMaterialId)
    {
        return ResourceType::Shader;
    }
    else if (rid == kMeshId)
    {
        return ResourceType::Material;
    }
    else if (rid == kImageId)
    {
        return ResourceType::Image;
    }
    else if (rid == kTextureId)
    {
        return ResourceType::Texture;
    }
    else if (rid == kFontId)
    {
        return ResourceType::Font;
    }
    else if (rid == kRawDataId)
    {
        return ResourceType::RawData;
    }
    else if (rid == kTextDataId)
    {
        return ResourceType::TextData;
    }

    return ResourceType::NullResource;
}

}  // namespace haf::res

#endif
