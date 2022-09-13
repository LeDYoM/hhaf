#ifndef HAF_BACKEND_SFML_TEXTURE_INCLUDE_HPP
#define HAF_BACKEND_SFML_TEXTURE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/itexture.hpp>

namespace sf
{
    class Texture;
}

namespace haf::backend::sfmlb
{
class SFMLTexture : public ITexture
{
public:
    SFMLTexture(sf::Texture const* const texture, bool const owned);
    ~SFMLTexture() override;

    htps::vector2du32 size() const override;
    htps::u64 uniqueId() const override;
    void bind() const override;

    sf::Texture const* backEndTexture() const noexcept { return priv_; }
    htps::str info() const override;

private:
    sf::Texture const* const priv_;
    bool const owned_;
};
}  // namespace haf::backend::sfmlb

#endif
