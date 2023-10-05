#include <haf/include/resources/shader.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/menum.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/uniform_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "shader_private.hpp"

#include <hogl/include/vao_functions.hpp>

#include <facil_math/include/math_types.hpp>

using namespace haf::core;
using namespace haf::render;
using namespace fmath;

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
    logger::DisplayLog::debug(staticTypeName(), ": Creating Shader...");

    logger::DisplayLog::debug_if(vsc != nullptr, staticTypeName(),
                         ": Fragment shader:\n",
                         vsc != nullptr ? vsc->data() : str{});
    logger::DisplayLog::debug_if(tcsc != nullptr, staticTypeName(),
                         ": Tesellation control shader:\n",
                         tcsc != nullptr ? tcsc->data() : str{});
    logger::DisplayLog::debug_if(tesc != nullptr, staticTypeName(),
                         ": Tesellation evaluation shader:\n",
                         tesc != nullptr ? tesc->data() : str{});
    logger::DisplayLog::debug_if(gsc != nullptr, staticTypeName(),
                         ": Geometry shader:\n",
                         gsc != nullptr ? gsc->data() : str{});
    logger::DisplayLog::debug_if(fsc != nullptr, staticTypeName(),
                         ": Fragment shader:\n",
                         fsc != nullptr ? fsc->data() : str{});
    logger::DisplayLog::debug_if(csc != nullptr, staticTypeName(),
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

    m_shader_metadata.init(m_p->m_program);
}

Shader::~Shader()
{
    if (ogl::isValid(m_p->m_program))
    {
        logger::DisplayLog::debug(staticTypeName(),
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

void Shader::setUniform(s32 const index, Matrix4x4 const& m4x4)
{
    ogl::setMatrixUniform(m_p->m_program, index, 1, false, m4x4.cbegin());
}

void Shader::setUniform(str_view const name, Matrix4x4 const& m4x4)
{
    setUniform(m_shader_metadata.uniformIndex(name), m4x4);
}

}  // namespace haf::res
