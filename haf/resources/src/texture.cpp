#include <haf/resources/i_include/texture.hpp>
#include <backend_dev/include/itexture.hpp>

using namespace mtps;

namespace haf::scene
{
Texture::Texture(backend::ITexture *texture)
    : m_texturePrivate{texture} {}

Texture::~Texture() {}

vector2du32 Texture::size() const
{
    return m_texturePrivate->size();
}
} // namespace haf::scene
