#include "texture.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
Texture::Texture(const sf::Texture* const texture, const bool owned) :
    priv_{texture}, owned_{owned}
{}

Texture::~Texture()
{
    if (owned_ && priv_ != nullptr)
    {
        delete priv_;
    }
}

vector2du32 Texture::size() const
{
    return {static_cast<u32>(priv_->getSize().x),
            static_cast<u32>(priv_->getSize().y)};
}

str Texture::info() const
{
    return make_str("name:SFMLTexture;provider:SFML;provider_version:",
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:2:patch3");
}

}  // namespace haf::backend::sfmlb
