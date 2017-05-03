#include "ttfont.hpp"

namespace lib
{
	namespace draw
	{
		TTFont::TTFont(str name) 
			: core::HasName{ std::move(name) }, m_font{ msptr<sf::Font>() } 
		{
		}

		TTFont::~TTFont()
		{
		}

		bool TTFont::loadFromFile(const std::string & filename)
		{
			return m_font->loadFromFile(filename);
		}
		const sf::Glyph & TTFont::getGlyph(u32 codePoint, u32 characterSize, bool bold, float outlineThickness) const
		{
			return m_font->getGlyph(codePoint, characterSize, bold, outlineThickness);
		}

		f32 TTFont::getLineSpacing(u32 characterSize) const
		{
			return m_font->getLineSpacing(characterSize);
		}

		f32 TTFont::getKerning(u32 first, u32 second, u32 characterSize) const
		{
			return m_font->getKerning(first, second, characterSize);
		}

		const sf::Texture & TTFont::getTexture(u32 characterSize) const
		{
			return m_font->getTexture(characterSize);
		}
	}
}
