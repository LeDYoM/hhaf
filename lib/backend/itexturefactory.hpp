#ifndef LIB_BACKEND_ITEXTUREFACTORY_HPP
#define LIB_BACKEND_ITEXTUREFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include "itexture.hpp"

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace backend
	{
		class ITextureFactory
		{
		public:
			virtual sptr<ITexture> loadFromFile(const str &file) = 0;
		};
	}
}
#endif
