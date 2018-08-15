#include "shader.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
    Shader::Shader(uptr<sf::Shader> shader) : m_shaderPrivate{ std::move(shader) } {}

    Shader::~Shader() = default;

    void Shader::setUniform(const str &name, vector2df v)
    {
        m_shaderPrivate->setUniform(to_sf_type(name), to_sf_type(v));
    }

    void Shader::setUniform(const str &name, ITexture *texture)
    {

    }
}
