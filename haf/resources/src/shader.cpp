#include <resources/i_include/shader.hpp>
#include <backend_dev/include/ishader.hpp>

namespace haf::res
{
Shader::Shader(backend::IShader* shader) : m_ShaderPrivate{shader}
{}

Shader::~Shader()
{}

backend::IShader const* Shader::backEndShader() const noexcept
{
    return m_ShaderPrivate;
}

}  // namespace haf::res
