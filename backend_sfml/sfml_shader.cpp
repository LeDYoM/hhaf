#include "sfml_shader.hpp"
#include "conversions.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLShader::SFMLShader(uptr<sf::Shader> shader) noexcept :
    priv_{htps::move(shader)}
{}

SFMLShader::~SFMLShader() noexcept = default;

void SFMLShader::setUniform(str const& name, bool const& v)
{
    priv_->setUniform(to_sf_type(name), v);
}

void SFMLShader::setUniform(str const& name, vector2df const& v)
{
    priv_->setUniform(to_sf_type(name), to_sf_type(v));
}

void SFMLShader::setUniform(str const& name, rptr<ITexture const> const v)
{
    priv_->setUniform(to_sf_type(name), *to_sf_type(v));
}

void SFMLShader::setTexture(htps::size_type const /*index*/,
                            ITexture const* const texture)
{
    sf::Shader* shader{priv_.get()};
    if (texture != nullptr)
    {
        shader->setUniform("has_texture", true);
        shader->setUniform("texture", *(to_sf_type(texture)));
    }
    else
    {
        shader->setUniform("has_texture", false);
    }
}

void SFMLShader::bind() const
{
    sf::Shader::bind(priv_.get());
}

void SFMLShader::unbind() const
{
    sf::Shader::bind(nullptr);
}

}  // namespace haf::backend::sfmlb
