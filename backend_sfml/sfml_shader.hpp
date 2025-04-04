#ifndef HAF_BACKEND_SFML_SHADER_INCLUDE_HPP
#define HAF_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ishader.hpp>

namespace sf
{
class Shader;
class Texture;
}  // namespace sf

namespace haf::backend::sfmlb
{
class SFMLShader : public IShader
{
public:
    explicit SFMLShader(htps::uptr<sf::Shader> shader) noexcept;
    ~SFMLShader() noexcept override;

    void setUniform(htps::str const& name, bool const& v) override;
    void setUniform(htps::str const& name, fmath::vector2df const& v) override;
    void setUniform(htps::str const& name,
                    htps::rptr<ITexture const> const texture) override;

    void setTexture(htps::size_type const index,
                    ITexture const* const texture) override;

    void bind() const override;
    void unbind() const override;

    sf::Shader const* backEndShader() const { return priv_.get(); }

private:
    htps::uptr<sf::Shader> priv_;
};
}  // namespace haf::backend::sfmlb

#endif
