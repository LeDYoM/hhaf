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
        Texture(const sf::Texture* const texture, const bool owned);
        ~Texture() override;

        virtual htps::vector2du32 size() const override;

        const sf::Texture &backEndTexture() const { return *m_texturePrivate; }
        htps::str info() const;

    private:
        const sf::Texture* const m_texturePrivate;
        const bool owned_;
    };
}

#endif
