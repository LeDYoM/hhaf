#ifndef LIB_BACKEND_SFML_TTFONTFACTORY_HPP
#define LIB_BACKEND_SFML_TTFONTFACTORY_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

#include <lib/backend/ittfontfactory.hpp>
#include "ttfont.hpp"

namespace sf
{
	class Font;
}

namespace lib
{
	namespace backend
	{
		class TTFontFactory : public ITTFontFactory
		{
		public:
			virtual sptr<ITTFont> loadFromFile(const str &file) override;
			// Temporary
			virtual sptr<ITTFont> getITTFont(const sf::Font &font) override;
		};
	}
}
#endif