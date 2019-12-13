#include "shader.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
Shader::Shader(sf::Shader* shader, const bool owned)
    : m_shaderPrivate{shader}, owned_{owned} {}

Shader::~Shader()
{
    if (owned_ && m_shaderPrivate != nullptr)
    {
        delete m_shaderPrivate;
    }
}

void Shader::setUniform(const str &name, vector2df v)
{
    m_shaderPrivate->setUniform(to_sf_type(name), to_sf_type(v));
}

void Shader::setUniform(const str &, ITexture *)
{
}
} // namespace lib::backend::sfmlb
