HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_CODE_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_CODE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/resource_codes.hpp>
#include <haf/include/resources/iresource.hpp>

namespace haf::res
{
enum class ShaderType : core::u32
{
    Vertex = 0U,
    TessellationControl,
    TessellationEvaluation,
    Geometry,
    Fragment,
    Compute,
    kNumShaderTypes
};

static constexpr auto to_str(ShaderType const sh_type)
{
    switch (sh_type)
    {
        case ShaderType::Vertex:
            return "Vertex";
            break;
        case ShaderType::TessellationControl:
            return "TessellationControl";
            break;
        case ShaderType::TessellationEvaluation:
            return "TessellationEvaluation";
            break;
        case ShaderType::Geometry:
            return "Geometry";
            break;
        case ShaderType::Fragment:
            return "Fragment";
            break;
        case ShaderType::Compute:
            return "Compute";
            break;
        case ShaderType::kNumShaderTypes:
            return "kNumShaderTypes";
            break;
    }
}

class IShaderCode : public IResource
{
public:
    explicit IShaderCode(core::RawMemory const& data) : m_data{data.to_str()} {}
    explicit IShaderCode(core::str data) noexcept : m_data{core::move(data)} {}
    explicit IShaderCode(core::str_view data) : m_data{data} {}

    core::str_view data() const noexcept { return m_data.to_view(); }

    virtual constexpr ShaderType shaderType() const noexcept = 0;

private:
    core::str m_data;
};

template <ShaderType shader_type>
class ShaderCode final : public IShaderCode
{
public:
    using IShaderCode::IShaderCode;
    static constexpr ResourceType const StaticResourceType{
        static_cast<ResourceType>(
            static_cast<core::u32>(ResourceType::VertexShaderCode) +
            static_cast<core::u32>(shader_type))};

    constexpr ShaderType shaderType() const noexcept override
    {
        return shader_type;
    }

    ResourceType resourceType() const noexcept override
    {
        return StaticResourceType;
    }
};

using VertexShaderCode = ShaderCode<ShaderType::Vertex>;
using TessellationControlShaderCode =
    ShaderCode<ShaderType::TessellationControl>;
using TessellationEvaluationShaderCode =
    ShaderCode<ShaderType::TessellationEvaluation>;
using GeometryShaderCode = ShaderCode<ShaderType::Geometry>;
using FragmentShaderCode = ShaderCode<ShaderType::Fragment>;
using ComputeShaderCode  = ShaderCode<ShaderType::Compute>;
}  // namespace haf::res

#endif
