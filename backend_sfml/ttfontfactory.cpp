#include "ttfontfactory.hpp"
#include "ttfont.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			ITTFont* TTFontFactory::loadFromFile(const str & file)
			{
				sf::Font font;
				font.loadFromFile(file);
				return new TTFont(font);
			}
		}
	}
}
