#include "texture.hpp"
#include <backend_dev/include/itexture.hpp>

using namespace htps;

namespace haf::res
{
Texture::Texture(backend::ITexture const* texture) : priv_{texture}
{}

Texture::~Texture() = default;

vector2du32 Texture::size() const
{
    return priv_->size();
}

backend::ITexture const* Texture::backEndTexture() const noexcept
{
    return priv_;
}

}  // namespace haf::res
