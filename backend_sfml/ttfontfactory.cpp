#include "ttfontfactory.hpp"
#include "ttfont.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

namespace lib::backend::sfmlb
{
	ITTFont* TTFontFactory::loadFromFile(const str & file)
	{
        uptr<sf::Font> font(muptr<sf::Font>());
        font->loadFromFile(file.c_str());
        uptr<TTFont> t{ muptr<TTFont>(std::move(font)) };
        m_fontCache.push_back(std::move(t));
        return (*(m_fontCache.end() - 1)).get();
	}

	ITTFont * TTFontFactory::loadFromRawMemory(RawMemory * raw_memory)
	{
		uptr<sf::Font> font(muptr<sf::Font>());
		font->loadFromMemory(raw_memory->first, raw_memory->second);
		uptr<TTFont> t{ muptr<TTFont>(std::move(font)) };
		m_fontCache.push_back(std::move(t));
		return (*(m_fontCache.end() - 1)).get();
	}

	TTFontFactory::~TTFontFactory()
	{
        m_fontCache.clear();
        m_fontCache.shrink_to_fit();
    }
}
