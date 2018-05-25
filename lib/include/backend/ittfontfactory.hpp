#ifndef LIB_BACKEND_ITTFONTFACTORY_HPP
#define LIB_BACKEND_ITTFONTFACTORY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include "ittfont.hpp"

namespace lib
{
	namespace backend
	{
		class ITTFontFactory
		{
		public:
			virtual ITTFont* loadFromFile(const str &file) = 0;
			virtual ~ITTFontFactory() {}
		};
	}
}
#endif
