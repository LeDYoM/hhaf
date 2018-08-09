#include "ttfont.hpp"
#include "texturettfont.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
    TTFont::TTFont(uptr<sf::Font> f) : m_font{ std::move(f) } {}
    TTFont::~TTFont() = default;

	ITTGlyph TTFont::getGlyph(u32 codePoint, u32 characterSize) const 
    {
		const sf::Glyph &glyph(m_font->getGlyph(codePoint, characterSize, false));
		return ITTGlyph{ toRect<f32>(glyph.bounds), toRect<s32>(glyph.textureRect), glyph.advance };
	}

	f32 TTFont::getLineSpacing(u32 characterSize) const 
    {
		return m_font->getLineSpacing(characterSize);
	}

	f32 TTFont::getKerning(u32 first, u32 second, u32 characterSize) const 
    {
		return m_font->getKerning(first, second, characterSize);
	}

	ITexture *TTFont::getTexture(u32 characterSize) 
    {
        if (auto iterator(m_fontTexturesCache.find(characterSize));
        iterator != m_fontTexturesCache.end()) 
        {
            return iterator->second.get();
		}

		auto nTexture(muptr<TextureTTFont>( m_font->getTexture(characterSize)));

		for (u32 i = 0U; i < 0xff; ++i)
			getGlyph(i, characterSize);

        auto *ret(nTexture.get());
		m_fontTexturesCache[characterSize] = std::move(nTexture);
        return ret;
	}
}
