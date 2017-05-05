#ifndef LIB_BACKEND_ITEXTURE_HPP
#define LIB_BACKEND_ITEXTURE_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace backend
	{
		class ITexture
		{
		public:
			ITexture() {}
			virtual ~ITexture() {}

			virtual vector2du32 size() const = 0;
		};
	}
}
#endif
