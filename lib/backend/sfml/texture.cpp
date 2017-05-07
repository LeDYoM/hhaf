#include "texture.hpp"
#include <lib/backend/itexture.hpp>

namespace lib
{
	namespace backend
	{
		Texture::Texture(uptr<sf::Texture> &&texture) : m_texturePrivate{ std::move(texture) } {}

		Texture::~Texture() = default;

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivate->getSize().x), static_cast<u32>(m_texturePrivate->getSize().y) };
		}
	}
}
