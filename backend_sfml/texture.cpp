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

str Texture::info() const
{
    return make_str("name:SFMLTexture;provider:SFML;provider_version:",
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:2:patch3");
}

}  // namespace haf::backend::sfmlb
