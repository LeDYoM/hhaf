#include "texture.hpp"

#include <lib/include/backend/itexture.hpp>
#include <lib/include/backend/itexturefactory.hpp>
#include <lib/core/backendfactory.hpp>

namespace lib::scene
{
	Texture::Texture(backend::ITexture *texture) : m_texturePrivate{ texture } {}

	Texture::~Texture() {}

	bool Texture::loadFromFile(const str& filename)
	{
		m_texturePrivate = backend::textureFactory().loadFromFile(filename);
		return m_texturePrivate != nullptr;
	}

	vector2du32 Texture::size() const
	{
		return m_texturePrivate->size();
	}
}
