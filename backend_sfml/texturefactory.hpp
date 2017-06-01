#ifndef LIB_BACKEND_SFML_TEXTUREFACTORY_HPP
#define LIB_BACKEND_SFML_TEXTUREFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include <lib/backend/itexturefactory.hpp>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			class TextureFactory : public ITextureFactory
			{
			public:
				virtual sptr<ITexture> loadFromFile(const str &file) override;
			};
		}
	}
}

#endif