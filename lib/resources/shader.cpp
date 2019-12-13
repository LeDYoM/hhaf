#include "shader.hpp"

#include <backend_dev/include/ishader.hpp>
#include <map>

namespace lib::scene
{
Shader::Shader(backend::IShader *shader) : m_ShaderPrivate{shader} {}

Shader::~Shader() {}

} // namespace lib::scene
