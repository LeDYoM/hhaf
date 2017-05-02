#include "texture.hpp"
#include <lib/backend/itexture.hpp>
#include <lib/backend/itexturefactory.hpp>
#include <lib/backend/backendfactory.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace draw
	{
		struct Texture::TexturePrivate final
		{
			sf::Texture* m_backendTexture;
			TexturePrivate(sf::Texture*t) : m_backendTexture{ t } {}
			~TexturePrivate() { if (m_backendTexture) { delete m_backendTexture; } }
		};
		Texture::Texture(str name) : core::HasName{ std::move(name) }, m_texturePrivate{ muptr<TexturePrivate>(new sf::Texture) } {}
		Texture::Texture(const sf::Texture &texture) : core::HasName{ "internal" }, m_texturePrivate{ muptr<TexturePrivate>(new sf::Texture(texture)) } {}

		Texture::~Texture() = default;

		bool Texture::loadFromFile(const str& filename)
		{
			return m_texturePrivate->m_backendTexture->loadFromFile(filename);
		}

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivate->m_backendTexture->getSize().x), static_cast<u32>(m_texturePrivate->m_backendTexture->getSize().y) };
		}

		const sf::Texture * Texture::backEndTexture() const
		{
			return m_texturePrivate->m_backendTexture;
		}
	}
}
