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
				font.loadFromFile(file.c_str());
				auto *ttffont(new TTFont(font));
				m_fontCache.push_back(ttffont);
				return ttffont;
			}

			TTFontFactory::~TTFontFactory()
			{
				for (auto *font : m_fontCache) {
					delete font;
				}
				m_fontCache.clear();
			}
		}
	}
}
