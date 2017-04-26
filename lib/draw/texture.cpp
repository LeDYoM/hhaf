#include "texture.hpp"
#include <lib/backend/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace draw
	{
		class Texture::TexturePrivate final
		{
		public:
			TexturePrivate() {}
			~TexturePrivate() {}
			uptr<backend::ITexture> m_backendTexture{ nullptr };
		};
		Texture::Texture(str name) : core::HasName{ std::move(name) }, m_texturePrivate{ new TexturePrivate }, m_texturePrivateOld{ new sf::Texture } {}
		Texture::Texture(const sf::Texture &texture) : core::HasName{ "internal" }, m_texturePrivate{ new TexturePrivate }, m_texturePrivateOld{ new sf::Texture(texture) } {}

		Texture::~Texture() = default;

		bool Texture::loadFromFile(const str& filename)
		{
			return m_texturePrivateOld->loadFromFile(filename);
		}

		vector2du32 Texture::size() const
		{
			return{ static_cast<u32>(m_texturePrivateOld->getSize().x), static_cast<u32>(m_texturePrivateOld->getSize().y) };
		}

		const sf::Texture * Texture::backEndTexture() const
		{
			return m_texturePrivateOld.get();
		}
	}
}
