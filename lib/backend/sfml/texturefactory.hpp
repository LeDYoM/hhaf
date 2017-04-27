#ifndef LIB_BACKEND_SFML_TEXTUREFACTORY_HPP
#define LIB_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include <lib/backend/itexturefactory.hpp>

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace backend
	{
		class TextureFactory : public ITextureFactory
		{
		public:
			virtual sptr<ITexture> loadTextureFromDisk(const str &file) override;
			// Temporary
			virtual sptr<ITexture> getITexture(const sf::Texture &texture) override;
		};
	}
}

#endif
