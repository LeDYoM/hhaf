#include "texture.hpp"

namespace lib::backend::sfmlb
{
    Texture::Texture(const sf::Texture* const texture, const bool owned) : m_texturePrivate{ texture }, owned_{ owned } {}

    Texture::~Texture()
    {
        if (owned_ && m_texturePrivate != nullptr)
        {
            delete m_texturePrivate;
        }
    }

    mtps::vector2du32 Texture::size() const
    {
        return{ static_cast<mtps::u32>(m_texturePrivate->getSize().x), static_cast<mtps::u32>(m_texturePrivate->getSize().y) };
    }
}
