#include "texture.hpp"

namespace lib
{
	namespace draw
	{

		Texture::Texture(const std::string name) : core::HasName(name) {}
		Texture::Texture(const sf::Texture &texture) : core::HasName("internal"), m_texturePrivate(texture) {}

		bool Texture::loadFromFile(const std::string& filename)
		{
			return m_texturePrivate.loadFromFile(filename);
		}

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivate.getSize().x), static_cast<u32>(m_texturePrivate.getSize().y) };
		}

	}
}
