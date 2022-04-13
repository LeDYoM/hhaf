#include "shader.hpp"
#include "conversions.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
Shader::Shader(uptr<sf::Shader> shader) : priv_{std::move(shader)}
{}

Shader::~Shader()
{}

void Shader::setUniform(str const& name, bool const& v)
{
    priv_->setUniform(to_sf_type(name), v);
}

void Shader::setUniform(str const& name, vector2df const& v)
{
    priv_->setUniform(to_sf_type(name), to_sf_type(v));
}

void Shader::setUniform(str const& name, ITexture const* v)
{
//    (void)(v);
    priv_->setUniform(to_sf_type(name), *to_sf_type(v));
//    priv_->setUniform(to_sf_type(name), sf::Shader::CurrentTexture);
}
}  // namespace haf::backend::sfmlb
