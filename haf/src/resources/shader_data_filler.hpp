HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_SHADER_SHADER_DATA_FILLER_INCLUDE_HPP
#define HAF_RESOURCES_SHADER_SHADER_DATA_FILLER_INCLUDE_HPP

#include <hogl/include/types.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/low_level_constants.hpp>
#include "shader_private.hpp"

namespace haf::res
{
enum class FillDataMode
{
    Attributes       = 0U,
    Uniforms         = 1U,
    UniformBlocks    = 2U,
    UniformBlockData = 3U,
};

template <FillDataMode fill_data_mode>
void fillData(ogl::Handle const program, render::BufferSubObjects& formats)
{
    auto const numData{[]() {
        if constexpr (fill_data_mode == FillDataMode::Attributes)
        {
            return ogl::getNumAttribs;
        }
        else if constexpr (fill_data_mode == FillDataMode::Uniforms ||
                           fill_data_mode == FillDataMode::UniformBlockData)
        {
            return ogl::getNumUniforms;
        }
        else if constexpr (fill_data_mode == FillDataMode::UniformBlocks)
        {
            return ogl::getNumUniformBlocks;
        }
    }()(program)};
    formats.clear();
    if (numData > 0U)
    {
        formats.reserve(numData);
        formats.clear();
        ogl::GetLowLevelShaderData low_level_shared_data;
        low_level_shared_data.name.reserve(256U);
        for (auto index{0U}; index < numData; ++index)
        {
            low_level_shared_data.array_size = {};
            low_level_shared_data.location   = {};
            low_level_shared_data.type       = {};
            low_level_shared_data.name.clear();

            if constexpr (fill_data_mode == FillDataMode::UniformBlockData)
            {
                low_level_shared_data.extra_param0 = 0;
            }
            else
            {
                low_level_shared_data.extra_param0 = -1;
            }

            []() {
                if constexpr (fill_data_mode == FillDataMode::Attributes)
                {
                    return ogl::getAttribData;
                }
                else if constexpr (fill_data_mode == FillDataMode::Uniforms)
                {
                    return ogl::getUniformData;
                }
                else if constexpr (fill_data_mode ==
                                   FillDataMode::UniformBlocks)
                {
                    return ogl::getUniformBlocksData;
                }
                else if constexpr (fill_data_mode ==
                                   FillDataMode::UniformBlockData)
                {
                    return ogl::getUniformBlocksElementsData;
                }
            }()(program, index, low_level_shared_data);

            if (low_level_shared_data.location > -1)
            {
                render::VertexFormat format;
                if (low_level_shared_data.array_size > -1)
                {
                    format.arraySize = static_cast<core::u32>(
                        low_level_shared_data.array_size);
                }

                if (low_level_shared_data.type ==
                    ogl::LowLevelConstants::f32vec4)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 4U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::f32vec3)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 3U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::f32vec2)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 2U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::f32vec1)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 1U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::s32vec1)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 1U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::f32mat4x4)
                {
                    format.bufferType  = render::BufferType::Float;
                    format.numElements = 16U;
                }
                else if (low_level_shared_data.type ==
                         ogl::LowLevelConstants::sampler2D)
                {
                    format.bufferType  = render::BufferType::Sampler;
                    format.numElements = 2U;
                }

                formats.push_back(make_bufferSubObject(
                    core::str{low_level_shared_data.name},
                    low_level_shared_data.location, core::move(format)));
            }
        }
    }
}

inline void fillAttributes(ogl::Handle const program,
                           render::BufferSubObjects& attribVertexFormat)
{
    fillData<FillDataMode::Attributes>(program, attribVertexFormat);
}

inline void fillUniforms(ogl::Handle const program,
                         render::BufferSubObjects& uniformsFormat)
{
    fillData<FillDataMode::Uniforms>(program, uniformsFormat);
}

inline void fillUniformBlocks(ogl::Handle const program,
                              render::BufferSubObjects& uniformBlocksFormat)
{
    fillData<FillDataMode::UniformBlocks>(program, uniformBlocksFormat);
}

inline void fillUniformBlocksData(
    ogl::Handle const program,
    render::BufferSubObjects& uniformBlockselementsFormat)
{
    fillData<FillDataMode::UniformBlockData>(program,
                                             uniformBlockselementsFormat);
}

inline void bindUniformBlocksToDefaultBindingPoints(
    ogl::Handle const program,
    render::BufferSubObjects& uniformBlocksFormat)
{

    for (auto const& uniformBlockFormat : uniformBlocksFormat)
    {
        auto const bindingPoint{
            DefaultUniformBlocks::getDefaultUniformBlockBindingPoint(
                uniformBlockFormat.index().to_view())};

        if (bindingPoint > -1)
        {
            ogl::bindUniformBlockIndex(program, uniformBlockFormat.location(),
                                       bindingPoint);
        }
    }
}

}  // namespace haf::res

#endif
