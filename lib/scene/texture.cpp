#include "texture.hpp"

#include <backend_dev/include/itexture.hpp>
#include <lib/core/backendfactory.hpp>

namespace lib::scene
{
	Texture::Texture(backend::ITexture *texture) : m_texturePrivate{ texture } {}

	Texture::~Texture() {}

	vector2du32 Texture::size() const
	{
		return m_texturePrivate->size();
	}
}
