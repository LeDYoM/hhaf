#ifndef HAF_BACKEND_SFML_SHADER_INCLUDE_HPP
#define HAF_BACKEND_SFML_SHADER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ishader.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace haf::backend::sfmlb
{
class Shader : public IShader
{
public:
    Shader(htps::uptr<sf::Shader> shader);
    ~Shader() override;

    void setUniform(const htps::str& name, htps::vector2df v) override;
    void setUniform(const htps::str& name, ITexture* texture) override;

    const sf::Shader& backEndShader() const { return *priv_; }

private:
    htps::uptr<sf::Shader> priv_;
};
}  // namespace haf::backend::sfmlb

#endif
