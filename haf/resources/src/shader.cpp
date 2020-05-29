#include "shader.hpp"

#include <backend_dev/include/ishader.hpp>
#include <map>

namespace haf::scene
{
Shader::Shader(backend::IShader* shader) : m_ShaderPrivate{shader}
{}

Shader::~Shader()
{}

const backend::IShader* const Shader::backEndShader() const noexcept
{
    return m_ShaderPrivate;
}

}  // namespace haf::scene
