#include "texture.hpp"

using namespace mtps;

namespace haf::backend::sfmlb
{
Texture::Texture(const sf::Texture* const texture, const bool owned) :
    m_texturePrivate{texture}, owned_{owned}
{}

Texture::~Texture()
{
    if (owned_ && m_texturePrivate != nullptr)
    {
        delete m_texturePrivate;
    }
}

vector2du32 Texture::size() const
{
    return {static_cast<u32>(m_texturePrivate->getSize().x),
            static_cast<u32>(m_texturePrivate->getSize().y)};
}
}  // namespace haf::backend::sfmlb
