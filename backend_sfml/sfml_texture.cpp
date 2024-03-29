#include "sfml_texture.hpp"
#include <SFML/Graphics/Texture.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLTexture::SFMLTexture(sf::Texture const* const texture, bool const owned) :
    priv_{texture}, owned_{owned}
{}

SFMLTexture::~SFMLTexture()
{
    if (owned_ && priv_ != nullptr)
    {
        delete priv_;
    }
}

vector2du32 SFMLTexture::size() const
{
    auto const size{priv_->getSize()};
    return {static_cast<u32>(size.x), static_cast<u32>(size.y)};
}

str SFMLTexture::info() const
{
    return make_str("name:SFMLTexture;provider:SFML;provider_version:",
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:2:patch3");
}

}  // namespace haf::backend::sfmlb
