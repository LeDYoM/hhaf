#include <lib/resources/i_include/shader.hpp>

#include <backend_dev/include/ishader.hpp>
#include <map>

namespace haf::scene
{
Shader::Shader(backend::IShader *shader) : m_ShaderPrivate{shader} {}

Shader::~Shader() {}

} // namespace haf::scene
