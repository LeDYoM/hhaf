#include "texture.hpp"
#include <lib/backend/itexture.hpp>
#include <lib/backend/itexturefactory.hpp>
#include <lib/backend/backendfactory.hpp>

namespace lib
{
	namespace scene
	{
		using namespace backend;

//		Texture::Texture() = default;
		Texture::Texture(sptr<backend::ITexture> texture) : m_texturePrivate{ std::move(texture) } {}

		Texture::~Texture() = default;

		bool Texture::loadFromFile(const str& filename)
		{
			m_texturePrivate = textureFactory().loadFromFile(filename);
			return m_texturePrivate != nullptr;
		}

		vector2du32 Texture::size() const
		{
			return m_texturePrivate->size();
		}
	}
}
