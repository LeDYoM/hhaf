#include "shader.hpp"
#include "conversions.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
Shader::Shader(uptr<sf::Shader> shader) : priv_{std::move(shader)}
{}

Shader::~Shader()
{}

void Shader::setUniform(const str& name, vector2df v)
{
    priv_->setUniform(to_sf_type(name), to_sf_type(v));
}

void Shader::setUniform(const str&, ITexture*)
{}
}  // namespace haf::backend::sfmlb
