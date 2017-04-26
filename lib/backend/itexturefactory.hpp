#ifndef LIB_BACKEND_ITEXTUREFACTORY_HPP
#define LIB_BACKEND_ITEXTUREFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>

#include "itexture.hpp"

namespace lib
{
	namespace backend
	{
		class ITextureFactory
		{
		public:
			virtual ~ITextureFactory() {}
		};
	}
}
#endif
