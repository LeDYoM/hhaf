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
		const sf::Glyph & TTFont::getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const
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
		const Rectf32 TTFont::getGlyphRect(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const
		{
			sf::FloatRect glyphRect(m_font->getGlyph(codePoint, characterSize, bold, outlineThickness).bounds);
			return { glyphRect.left, glyphRect.top, glyphRect.width, glyphRect.height };
		}
	}
}
