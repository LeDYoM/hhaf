#include "texture.hpp"

#include <lib/include/backend/itexture.hpp>
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
