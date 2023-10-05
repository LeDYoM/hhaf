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
struct ShaderMetadata::ShaderMetadataPrivate
{
    render::BufferSubObjects m_attribVertexFormat;
    render::BufferSubObjects m_uniformFormat;
    render::BufferSubObjects m_uniformBlockFormat;
    render::BufferSubObjects m_uniformBlockElementsFormat;
};

ShaderMetadata::ShaderMetadata() : m_p{make_pimplp<ShaderMetadataPrivate>()}
{}

ShaderMetadata::~ShaderMetadata() = default;

void ShaderMetadata::init(ShaderId const program)
{
    fillAttributes(program, m_p->m_attribVertexFormat);
    fillUniforms(program, m_p->m_uniformFormat);
    fillUniformBlocks(program, m_p->m_uniformBlockFormat);
    fillUniformBlocksData(program, m_p->m_uniformBlockElementsFormat);
    bindUniformBlocksToDefaultBindingPoints(program, m_p->m_uniformBlockFormat);

    for (auto const& subObject : m_p->m_attribVertexFormat)
    {
        logger::DisplayLog::debug(
            StaticTypeName, ": Format for attrib ", subObject.location(), " (",
            subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }

    logger::DisplayLog::debug_if(m_p->m_attribVertexFormat.empty(), StaticTypeName,
                         ": No attributes found");

    for (auto const& subObject : m_p->m_uniformFormat)
    {
        logger::DisplayLog::debug(
            StaticTypeName, ": Format for uniform ", subObject.location(), " (",
            subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    logger::DisplayLog::debug_if(m_p->m_uniformFormat.empty(), StaticTypeName,
                         ": No uniforms found");

    for (auto const& subObject : m_p->m_uniformBlockFormat)
    {
        logger::DisplayLog::debug(
            StaticTypeName, ": Format for uniform block ", subObject.location(),
            " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    logger::DisplayLog::debug_if(m_p->m_uniformFormat.empty(), StaticTypeName,
                         ": No uniform blocks found");

    for (auto const& subObject : m_p->m_uniformBlockElementsFormat)
    {
        logger::DisplayLog::debug(
            StaticTypeName, ": Format for uniform block elements ",
            subObject.location(), " (", subObject.index(),
            ") is: ", static_cast<int>(subObject.vertexFormat().bufferType),
            ", number of elements: ", subObject.vertexFormat().numElements,
            ", array size: ", subObject.vertexFormat().arraySize);
    }
    logger::DisplayLog::debug_if(m_p->m_uniformFormat.empty(), StaticTypeName,
                         ": No uniform block elements found");
}

u32 ShaderMetadata::numAttribs() const
{
    return static_cast<u32>(m_p->m_attribVertexFormat.size());
}

VertexFormat ShaderMetadata::vertexFormat(u32 const index) const
{
    return getVertexFormatForIndex(m_p->m_attribVertexFormat, index);
}

s32 ShaderMetadata::uniformIndex(str_view const name) const
{
    return getIndexForName(m_p->m_uniformFormat, name);
}

VertexFormat ShaderMetadata::uniformFormat(u32 const uniformIndex) const
{
    return getVertexFormatForIndex(m_p->m_uniformFormat, uniformIndex);
}

VertexFormat ShaderMetadata::uniformFormat(core::str_view const name) const
{
    return getVertexFormatForName(m_p->m_uniformFormat, name);
}

s32 ShaderMetadata::attributeIndex(str_view const name) const
{
    return getIndexForName(m_p->m_attribVertexFormat, name);
}

VertexFormat ShaderMetadata::attributeFormat(u32 const attributeIndex) const
{
    return getVertexFormatForIndex(m_p->m_attribVertexFormat, attributeIndex);
}

VertexFormat ShaderMetadata::attributeFormat(core::str_view const name) const
{
    return getVertexFormatForName(m_p->m_attribVertexFormat, name);
}

vector<pair<str, u32>> ShaderMetadata::unusedAttribs(
    vector<u32> const& usedAttribs)
{
    vector<pair<str, u32>> result;
    for (const auto& attrib : m_p->m_attribVertexFormat)
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
