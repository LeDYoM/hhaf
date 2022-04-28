#ifndef HAF_BACKEND_SFML_TEXTURE_INCLUDE_HPP
#define HAF_BACKEND_SFML_TEXTURE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace haf::backend::sfmlb
{
class Texture : public ITexture
{
public:
    Texture(sf::Texture const* const texture, bool const owned);
    ~Texture() override;

    virtual htps::vector2du32 size() const override;

    sf::Texture const* backEndTexture() const noexcept { return priv_; }
    htps::str info() const;

private:
    sf::Texture const* const priv_;
    bool const owned_;
};
}  // namespace haf::backend::sfmlb

#endif
