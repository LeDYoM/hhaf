#include "texture.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace draw
	{

		Texture::Texture(const std::string name) : core::HasName(name), m_texturePrivate{ new sf::Texture } {}
		Texture::Texture(const sf::Texture &texture) : core::HasName("internal"), m_texturePrivate{ new sf::Texture(texture) } {}

		Texture::~Texture() = default;

		bool Texture::loadFromFile(const std::string& filename)
		{
			return m_texturePrivate->loadFromFile(filename);
		}

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivate->getSize().x), static_cast<u32>(m_texturePrivate->getSize().y) };
		}

		const sf::Texture * Texture::backEndTexture() const
		{
			return m_texturePrivate.get();
		}
	}
}
