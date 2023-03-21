#include "shader_manager.hpp"
#include <hlog/include/hlog.hpp>

using namespace haf::core;

namespace haf::res
{
ShaderManager::ShaderManager() noexcept  = default;
ShaderManager::~ShaderManager() noexcept = default;

void ShaderManager::addShader(str_view rid, sptr<Shader> shader)
{
    m_shaders.add(rid, core::move(shader), false);
    DisplayLog::info(StaticTypeName, ": Added shader");
    DisplayLog::info(StaticTypeName, ": Number of shaders: ", m_shaders.size());
}

size_type ShaderManager::setUniformForAll(core::str_view uniformName,
                                          math::Matrix4x4 const& matrix)
{
    fast_u32 result{0U};
    for (auto const& element : m_shaders)
    {
        if (setUniform(element.second, uniformName, matrix))
        {
            ++result;
        }
    }
    return result;
}

bool ShaderManager::setUniform(sptr<Shader> const& shader,
                               str_view uniformName,
                               math::Matrix4x4 const& matrix)
{
    if (auto const index{shader->uniformIndex(uniformName)}; index > -1)
    {
        shader->setUniform(index, matrix);
        return true;
    }
    return false;
}

}  // namespace haf::res
