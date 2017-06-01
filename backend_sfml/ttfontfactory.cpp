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
			sptr<ITTFont> TTFontFactory::loadFromFile(const str & file)
			{
				sf::Font font;
				font.loadFromFile(file);
				return msptr<TTFont>(font);
			}
		}
	}
}
