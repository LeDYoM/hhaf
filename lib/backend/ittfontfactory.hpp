#ifndef LIB_BACKEND_ITTFONTFACTORY_HPP
#define LIB_BACKEND_ITTFONTFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include "ittfont.hpp"

namespace sf
{
	class Font;
}

namespace lib
{
	namespace backend
	{
		class ITTFontFactory
		{
		public:
			virtual sptr<ITTFont> loadFromFile(const str &file) = 0;
			// Temporary
			virtual sptr<ITTFont> getITTFont(const sf::Font &font) = 0;
		};
	}
}
#endif
