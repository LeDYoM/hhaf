#include "texture.hpp"
#include <lib/backend/itexture.hpp>

namespace lib
{
	namespace backend
	{
		Texture::Texture(const sf::Texture &texture) : m_texturePrivate{ texture } {}

		Texture::~Texture() = default;

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivate.getSize().x), static_cast<u32>(m_texturePrivate.getSize().y) };
		}
	}
}
