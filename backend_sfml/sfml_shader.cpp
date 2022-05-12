#include "sfml_shader.hpp"
#include "conversions.hpp"
#include <SFML/Graphics/Shader.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLShader::SFMLShader(uptr<sf::Shader> shader) : priv_{htps::move(shader)}
{}

SFMLShader::~SFMLShader()
{}

void SFMLShader::setUniform(str const& name, bool const& v)
{
    priv_->setUniform(to_sf_type(name), v);
}

void SFMLShader::setUniform(str const& name, vector2df const& v)
{
    priv_->setUniform(to_sf_type(name), to_sf_type(v));
}

void SFMLShader::setUniform(str const& name, ITexture const* v)
{
//    (void)(v);
    priv_->setUniform(to_sf_type(name), *to_sf_type(v));
//    priv_->setUniform(to_sf_type(name), sf::Shader::CurrentTexture);
}
}  // namespace haf::backend::sfmlb
