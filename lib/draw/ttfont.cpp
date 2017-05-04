#include "ttfont.hpp"
#include <lib/backend/sfml/conversions.hpp>

#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace draw
	{
		TTFont::TTFont(str name) 
			: core::HasName{ std::move(name) }, m_font{ msptr<sf::Font>() } {}

		TTFont::~TTFont() = default;

		bool TTFont::loadFromFile(const std::string & filename)
		{
			return m_font->loadFromFile(filename);
		}

		const TTGlyph TTFont::getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const
		{
			const sf::Glyph &glyph(m_font->getGlyph(codePoint, characterSize, bold, outlineThickness));
			return TTGlyph{ backend::toRect<f32>(glyph.bounds), backend::toRect<s32>(glyph.textureRect), glyph.advance };
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
