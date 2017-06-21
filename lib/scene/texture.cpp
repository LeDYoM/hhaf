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
		Texture::Texture(backend::ITexture *texture) : m_texturePrivate{ texture } {}

		Texture::~Texture() {
			m_texturePrivate = nullptr;
			int b = 0;
			b;
		}

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
