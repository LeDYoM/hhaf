#include "ttfontfactory.hpp"
#include "ttfont.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib
{
	namespace backend
	{
		sptr<ITTFont> TTFontFactory::loadFromFile(const str & file)
		{
			sf::Font font;
			font.loadFromFile(file);
			return msptr<TTFont>(font);
		}

		sptr<ITTFont> TTFontFactory::getITTFont(const sf::Font & font)
		{
			return msptr<TTFont>(font);
		}
	}
}
