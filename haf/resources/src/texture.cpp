#include "texture.hpp"

#include <backend_dev/include/itexture.hpp>

using namespace mtps;

namespace haf::res
{
Texture::Texture(backend::ITexture *texture)
    : m_texturePrivate{texture} {}

Texture::~Texture() = default;

vector2du32 Texture::size() const
{
    return m_texturePrivate->size();
}

const backend::ITexture* const Texture::backEndTexture() const noexcept
{
    return m_texturePrivate;
}

} // namespace haf::res
