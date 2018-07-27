#include "shader.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
    Shader::Shader(uptr<sf::Shader> shader) : m_shaderPrivate{ std::move(shader) } {}
}
