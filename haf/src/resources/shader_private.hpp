HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_SHADER_PRIVATE_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_SHADER_PRIVATE_INCLUDE_HPP

#include <haf/include/resources/shader.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/menum.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/low_level_constants.hpp>
#include "default_shader_data.hpp"

namespace haf::res
{
struct Shader::ShaderPrivate
{
    ogl::Handle m_program{ogl::invalidHandle()};
    NamedIndexedVertexFormatContainer m_attribVertexFormat;
    NamedIndexedVertexFormatContainer m_uniformFormat;
};

using SHType =
    core::MEnum<ShaderType, ShaderType::Vertex, ShaderType::kNumShaderTypes>;

template <typename T>
using SHArray = core::array<T, SHType::size>;

constexpr void loadShaderCodesInHandles(
    SHArray<core::sptr<IShaderCode>>& shader_codes,
    SHArray<ogl::Handle>& shader_handles)
{
    constexpr SHArray<ogl::Handle (*)()> const create_shader_functions{
        ogl::createVertexShader,   ogl::createFragmentShader,
        ogl::createVertexShader,   ogl::createVertexShader,
        ogl::createFragmentShader, ogl::createVertexShader};

    for (SHType::numeric_type index{0}; index < SHType::size; ++index)
    {
        if (shader_codes[index] != nullptr)
        {
            auto const handle{create_shader_functions[index]()};
            shader_handles[SHType{shader_codes[index]->shaderType()}
                               .getNumeric()] = handle;
            (void)(ogl::compileShader(handle, shader_codes[index]->data()));
        }
    }
}

constexpr void attachAllShaders(ogl::Handle const program_handle,
                                SHArray<ogl::Handle> const& shader_handles)
{
    for (const auto& sh_handle : shader_handles)
    {
        if (ogl::isValid(sh_handle))
        {
            ogl::attachShader(program_handle, sh_handle);
        }
    }
}

constexpr void deleteAllShaders(SHArray<ogl::Handle> const& shader_handles)
{
    for (const auto& sh_handle : shader_handles)
    {
        if (ogl::isValid(sh_handle))
        {
            ogl::deleteShader(sh_handle);
        }
    }
}

template <bool attributes>
void fillData(ogl::Handle const program,
              NamedIndexedVertexFormatContainer& formats)
{
    auto const numData{[]() {
        if constexpr (attributes)
        {
            return ogl::getNumAttribs;
        }
        else
        {
            return ogl::getNumUniforms;
        }
    }()(program)};
    formats.clear();
    if (numData > 0U)
    {
        formats.reserve(numData);
        formats.clear();
        core::str name(256);
        for (auto index{0U}; index < numData; ++index)
        {
            core::s32 type{};
            core::s32 location{};
            core::s32 array_size{};
            []() {
                if constexpr (attributes)
                {
                    return ogl::getAttribData;
                }
                else
                {
                    return ogl::getUniformData;
                }
            }()(program, index, location, type, array_size, name);

            if (location > -1)
            {
                VertexFormat format;
                if (array_size > -1)
                {
                    format.arraySize = static_cast<core::u32>(array_size);
                }

                if (type == ogl::LowLevelConstants::f32vec4)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 4U;
                }
                else if (type == ogl::LowLevelConstants::f32vec3)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 3U;
                }
                else if (type == ogl::LowLevelConstants::f32vec2)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 2U;
                }
                else if (type == ogl::LowLevelConstants::f32vec1)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 1U;
                }
                else if (type == ogl::LowLevelConstants::s32vec1)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 1U;
                }
                else if (type == ogl::LowLevelConstants::f32mat4x4)
                {
                    format.bufferType  = BufferType::Float;
                    format.numElements = 16U;
                }

                formats.push_back({core::str{name}, {location, format}});
            }
        }
    }
}

inline void fillAttributes(
    ogl::Handle const program,
    NamedIndexedVertexFormatContainer& attribVertexFormat)
{
    fillData<true>(program, attribVertexFormat);
}

inline void fillUniforms(ogl::Handle const program,
                         NamedIndexedVertexFormatContainer& uniformsFormat)
{
    fillData<false>(program, uniformsFormat);
}

}  // namespace haf::res

#endif
