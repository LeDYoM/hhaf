#include "texture.hpp"
#include <lib/backend/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace draw
	{
		class TextureV1::TexturePrivate final
		{
		public:
			TexturePrivate() {}
			~TexturePrivate() {}
			uptr<backend::ITexture> m_backendTexture{ nullptr };
		};
		TextureV1::TextureV1(str name) : core::HasName{ std::move(name) }, m_texturePrivate{ new TexturePrivate }, m_texturePrivateOld{ new sf::Texture } {}
		TextureV1::TextureV1(const sf::Texture &texture) : core::HasName{ "internal" }, m_texturePrivate{ new TexturePrivate }, m_texturePrivateOld{ new sf::Texture(texture) } {}

		TextureV1::~TextureV1() = default;

		bool TextureV1::loadFromFile(const str& filename)
		{
			return m_texturePrivateOld->loadFromFile(filename);
		}

		vector2du32 TextureV1::size() const
		{
			return{ static_cast<u32>(m_texturePrivateOld->getSize().x), static_cast<u32>(m_texturePrivateOld->getSize().y) };
		}

		const sf::Texture * TextureV1::backEndTexture() const
		{
			return m_texturePrivateOld.get();
		}
	}
}
