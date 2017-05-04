#include "ttfont.hpp"
#include <lib/backend/sfml/conversions.hpp>

#include <SFML/Graphics/Font.hpp>

#include <lib/backend/ittfont.hpp>
#include <lib/backend/ittfontfactory.hpp>
#include <lib/backend/backendfactory.hpp>

namespace lib
{
	namespace draw
	{
		using namespace backend;

		TTFont::TTFont(str name) : core::HasName{ std::move(name) }, m_font{ } {}

		TTFont::~TTFont() = default;

		bool TTFont::loadFromFile(const std::string & filename)
		{
			m_font = ttfontFactory().loadFromFile(filename);
			return m_font != nullptr;
		}

		const TTGlyph TTFont::getGlyph(u32 codePoint, u32 characterSize, bool bold, f32 outlineThickness) const
		{
			return static_cast<TTGlyph>(m_font->getGlyph(codePoint, characterSize, bold, outlineThickness));
		}

		f32 TTFont::getLineSpacing(u32 characterSize) const
		{
			return m_font->getLineSpacing(characterSize);
		}

		f32 TTFont::getKerning(u32 first, u32 second, u32 characterSize) const
		{
			return m_font->getKerning(first, second, characterSize);
		}

		const Texture TTFont::getTexture(u32 characterSize) const
		{
			return m_font->getTexture(characterSize);
		}
	}
}
