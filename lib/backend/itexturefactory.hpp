#ifndef LIB_BACKEND_ITEXTUREFACTORY_HPP
#define LIB_BACKEND_ITEXTUREFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include "itexture.hpp"

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
