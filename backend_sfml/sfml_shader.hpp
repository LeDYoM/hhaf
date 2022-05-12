#ifndef HAF_BACKEND_SFML_SHADER_INCLUDE_HPP
#define HAF_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ishader.hpp>

namespace sf
{
    class Shader;
}

namespace haf::backend::sfmlb
{
class SFMLShader : public IShader
{
public:
    explicit SFMLShader(htps::uptr<sf::Shader> shader);
    ~SFMLShader() override;

    void setUniform(htps::str const& name, bool const& v) override;
    void setUniform(htps::str const& name, htps::vector2df const& v) override;
    void setUniform(htps::str const& name, ITexture const* texture) override;

    sf::Shader const* backEndShader() const { return priv_.get(); }

private:
    htps::uptr<sf::Shader> priv_;
};
}  // namespace haf::backend::sfmlb

#endif
