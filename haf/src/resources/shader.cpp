#include <haf/include/resources/shader.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/menum.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/uniform_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "shader_private.hpp"

#include <hogl/include/vao_functions.hpp>

using namespace haf::core;
using namespace haf::math;

namespace haf::res
{
Shader::Shader(sptr<VertexShaderCode> vsc,
               sptr<TessellationControlShaderCode> tcsc,
               sptr<TessellationEvaluationShaderCode> tesc,
               sptr<GeometryShaderCode> gsc,
               sptr<FragmentShaderCode> fsc,
               sptr<ComputeShaderCode> csc) :
    m_p{make_pimplp<ShaderPrivate>()}
{
    DisplayLog::debug(staticTypeName(), ": Creating Shader...");

    DisplayLog::debug_if(vsc != nullptr, staticTypeName(),
                         ": Fragment shader:\n",
                         vsc != nullptr ? vsc->data() : str{});
    DisplayLog::debug_if(tcsc != nullptr, staticTypeName(),
                         ": Tesellation control shader:\n",
                         tcsc != nullptr ? tcsc->data() : str{});
    DisplayLog::debug_if(tesc != nullptr, staticTypeName(),
                         ": Tesellation evaluation shader:\n",
                         tesc != nullptr ? tesc->data() : str{});
    DisplayLog::debug_if(gsc != nullptr, staticTypeName(),
                         ": Geometry shader:\n",
                         gsc != nullptr ? gsc->data() : str{});
    DisplayLog::debug_if(fsc != nullptr, staticTypeName(),
                         ": Fragment shader:\n",
                         fsc != nullptr ? fsc->data() : str{});
    DisplayLog::debug_if(csc != nullptr, staticTypeName(),
                         ": Compute shader:\n",
                         csc != nullptr ? csc->data() : str{});

    SHArray<sptr<IShaderCode>> shader_codes{core::move(vsc),  core::move(tcsc),
                                            core::move(tesc), core::move(gsc),
                                            core::move(fsc),  core::move(csc)};
    SHArray<ogl::Handle> shader_handles{ogl::invalidHandle()};

    loadShaderCodesInHandles(shader_codes, shader_handles);

    m_p->m_program = ogl::createProgram();
    DefaultAttribs::bindDefaultAttributes(m_p->m_program);

    attachAllShaders(m_p->m_program, shader_handles);
    ogl::linkProgram(m_p->m_program);
    deleteAllShaders(shader_handles);

    DisplayLog::debug(staticTypeName(), ": Shader id: ", m_p->m_program);
    fillAttributes(m_p->m_program, m_p->m_attribVertexFormat);
    fillUniforms(m_p->m_program, m_p->m_uniformFormat);

    for (auto const& [name, indexed_format] : m_p->m_attribVertexFormat)
    {
        DisplayLog::debug(
            staticTypeName(), ": Format for attrib ", indexed_format.first,
            " (", name,
            ") is: ", static_cast<int>(indexed_format.second.bufferType),
            ", number of elements: ", indexed_format.second.numElements,
            ", array size: ", indexed_format.second.arraySize);
    }

    DisplayLog::debug_if(m_p->m_attribVertexFormat.empty(), staticTypeName(),
                         ": No attributes found");

    for (auto const& [name, indexed_format] : m_p->m_uniformFormat)
    {
        DisplayLog::debug(
            staticTypeName(), ": Format for uniform ", indexed_format.first,
            " (", name,
            ") is: ", static_cast<int>(indexed_format.second.bufferType),
            ", number of elements: ", indexed_format.second.numElements,
            ", array size: ", indexed_format.second.arraySize);
    }
    DisplayLog::debug_if(m_p->m_uniformFormat.empty(), staticTypeName(),
                         ": No uniforms found");
}

Shader::~Shader()
{
    if (ogl::isValid(m_p->m_program))
    {
        DisplayLog::debug(staticTypeName(),
                          "Deleting program: ", m_p->m_program);
        ogl::deleteProgram(m_p->m_program);
        m_p->m_program = ogl::invalidHandle();
    }
}

void Shader::bind()
{
    ogl::useProgram(m_p->m_program);
}

void Shader::unbind()
{
    ogl::clearUseProgram();
}

u32 Shader::handle() const
{
    return m_p->m_program;
}

bool Shader::isValid() const
{
    return ogl::isValid(m_p->m_program);
}

u32 Shader::numAttribs() const
{
    return static_cast<u32>(m_p->m_attribVertexFormat.size());
}

VertexFormat Shader::vertexFormat(u32 const index) const
{
    return NamedIndexedVertexFormatFunctions::getVertexFormatForIndex(
        m_p->m_attribVertexFormat, index);
}

void Shader::setUniform(s32 const index, Matrix4x4 const& m4x4)
{
    ogl::setMatrixUniform(m_p->m_program, index, 1, false, m4x4.cbegin());
}

void Shader::setUniform(str_view const name, Matrix4x4 const& m4x4)
{
    setUniform(uniformIndex(name), m4x4);
}

s32 Shader::uniformIndex(str_view const name) const
{
    return NamedIndexedVertexFormatFunctions::getIndexForName(
        m_p->m_uniformFormat, name);
}

VertexFormat Shader::uniformFormat(u32 const uniformIndex) const
{
    return NamedIndexedVertexFormatFunctions::getVertexFormatForIndex(
        m_p->m_uniformFormat, uniformIndex);
}

VertexFormat Shader::uniformFormat(core::str_view const name) const
{
    return NamedIndexedVertexFormatFunctions::getVertexFormatForName(
        m_p->m_uniformFormat, name);
}

s32 Shader::attributeIndex(str_view const name) const
{
    return NamedIndexedVertexFormatFunctions::getIndexForName(
        m_p->m_attribVertexFormat, name);
}

VertexFormat Shader::attributeFormat(u32 const attributeIndex) const
{
    return NamedIndexedVertexFormatFunctions::getVertexFormatForIndex(
        m_p->m_attribVertexFormat, attributeIndex);
}

VertexFormat Shader::attributeFormat(core::str_view const name) const
{
    return NamedIndexedVertexFormatFunctions::getVertexFormatForName(
        m_p->m_attribVertexFormat, name);
}

vector<pair<str, u32>> Shader::unusedAttribs(vector<u32> const& usedAttribs)
{
    vector<pair<str, u32>> result;
    for (const auto& attrib : m_p->m_attribVertexFormat)
    {
        auto const iterator{usedAttribs.cfind(attrib.second.first)};
        if (iterator == usedAttribs.cend())
        {
            result.emplace_back(attrib.first, attrib.second.first);
        }
    }
    return result;
}

}  // namespace haf::res
