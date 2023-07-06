#include <haf/include/resources/shader.hpp>
#include <haf/include/resources/shader_metadata.hpp>
#include <hogl/include/types.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/uniform_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "shader_data_filler.hpp"

#include <hogl/include/vao_functions.hpp>
#include <facil_math/include/math_types.hpp>

using namespace haf::core;
using namespace haf::render;
using namespace fmath;

namespace haf::res
{
void ShaderMetadata::init(ShaderId const program)
{
    fillAttributes(program, m_attribVertexFormat);
    fillUniforms(program, m_uniformFormat);
    fillUniformBlocks(program, m_uniformBlockFormat);
    fillUniformBlocksData(program, m_uniformBlockElementsFormat);
    bindUniformBlocksToDefaultBindingPoints(program, m_uniformBlockFormat);

    for (auto const& subObject : m_attribVertexFormat)
    {
        DisplayLog::debug(
            StaticTypeName, ": Format for attrib ", subObject.location(),
            " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }

    DisplayLog::debug_if(m_attribVertexFormat.empty(), StaticTypeName,
                         ": No attributes found");

    for (auto const& subObject : m_uniformFormat)
    {
        DisplayLog::debug(
            StaticTypeName, ": Format for uniform ", subObject.location(),
            " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    DisplayLog::debug_if(m_uniformFormat.empty(), StaticTypeName,
                         ": No uniforms found");

    for (auto const& subObject : m_uniformBlockFormat)
    {
        DisplayLog::debug(
            StaticTypeName, ": Format for uniform block ",
            subObject.location(), " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    DisplayLog::debug_if(m_uniformFormat.empty(), StaticTypeName,
                         ": No uniform blocks found");

    for (auto const& subObject : m_uniformBlockElementsFormat)
    {
        DisplayLog::debug(
            StaticTypeName, ": Format for uniform block elements ",
            subObject.location(), " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    DisplayLog::debug_if(m_uniformFormat.empty(), StaticTypeName,
                         ": No uniform block elements found");
}

/*
Shader::Shader(sptr<VertexShaderCode> vsc,
               sptr<TessellationControlShaderCode> tcsc,
               sptr<TessellationEvaluationShaderCode> tesc,
               sptr<GeometryShaderCode> gsc,
               sptr<FragmentShaderCode> fsc,
               sptr<ComputeShaderCode> csc) :
    m_p{make_pimplp<ShaderPrivate>()}
{
    DefaultAttribs::bindDefaultAttributes(m_p->m_program);

    attachAllShaders(m_p->m_program, shader_handles);
    ogl::linkProgram(m_p->m_program);
    deleteAllShaders(shader_handles);

    DisplayLog::debug(staticTypeName(), ": Shader id: ", m_p->m_program);
}
*/

u32 ShaderMetadata::numAttribs() const
{
    return static_cast<u32>(m_attribVertexFormat.size());
}

VertexFormat ShaderMetadata::vertexFormat(u32 const index) const
{
    return getVertexFormatForIndex(m_attribVertexFormat, index);
}

s32 ShaderMetadata::uniformIndex(str_view const name) const
{
    return getIndexForName(m_uniformFormat, name);
}

VertexFormat ShaderMetadata::uniformFormat(u32 const uniformIndex) const
{
    return getVertexFormatForIndex(m_uniformFormat, uniformIndex);
}

VertexFormat ShaderMetadata::uniformFormat(core::str_view const name) const
{
    return getVertexFormatForName(m_uniformFormat, name);
}

s32 ShaderMetadata::attributeIndex(str_view const name) const
{
    return getIndexForName(m_attribVertexFormat, name);
}

VertexFormat ShaderMetadata::attributeFormat(u32 const attributeIndex) const
{
    return getVertexFormatForIndex(m_attribVertexFormat, attributeIndex);
}

VertexFormat ShaderMetadata::attributeFormat(core::str_view const name) const
{
    return getVertexFormatForName(m_attribVertexFormat, name);
}

vector<pair<str, u32>> ShaderMetadata::unusedAttribs(
    vector<u32> const& usedAttribs)
{
    vector<pair<str, u32>> result;
    for (const auto& attrib : m_attribVertexFormat)
    {
        auto const iterator{usedAttribs.cfind(attrib.location())};
        if (iterator == usedAttribs.cend())
        {
            result.emplace_back(attrib.index(), attrib.location());
        }
    }
    return result;
}

}  // namespace haf::res
