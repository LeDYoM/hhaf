#include "texture.hpp"
#include <lib/backend/itexture.hpp>
#include <lib/backend/itexturefactory.hpp>
#include <lib/backend/backendfactory.hpp>

namespace lib
{
	namespace draw
	{
		using namespace backend;

		Texture::Texture(str name) : core::HasName{ std::move(name) }, m_texturePrivate{ } {}
		Texture::Texture(const sf::Texture &texture) : core::HasName{ "internal" }, m_texturePrivate{ textureFactory().getITexture(texture) } {}

		Texture::~Texture() = default;

		bool Texture::loadFromFile(const str& filename)
		{
			m_texturePrivate = textureFactory().loadTextureFromDisk(filename);
			return m_texturePrivate != nullptr;
		}

		vector2du32 Texture::size() const
		{
			return m_texturePrivate->size();
		}
	}
}
