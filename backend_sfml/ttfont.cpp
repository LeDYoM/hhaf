#include "ttfont.hpp"
#include "conversions.hpp"

namespace lib::backend::sfmlb
{
    TTFont::TTFont(uptr<sf::Font> f, RawMemory raw_memory)
        : m_font{ std::move(f) }, raw_memory_{ std::move(raw_memory) } {}
    TTFont::~TTFont() = default;

    Rectf32 TTFont::getBounds(const u32 codePoint, const u32 characterSize) const
    {
        return from_sft_type<f32>(m_font->getGlyph(codePoint, characterSize, false).bounds);
    }

    Rectf32 TTFont::getTextureBounds(const u32 codePoint, const u32 characterSize) const
    {
        return from_sft_type<s32>(m_font->getGlyph(codePoint, characterSize, false).textureRect);
    }

    f32 TTFont::getAdvance(const u32 codePoint, const u32 characterSize) const
    {
        return static_cast<f32>(m_font->getGlyph(codePoint, characterSize, false).advance);
    }

    f32 TTFont::getLineSpacing(const u32 characterSize) const
    {
        return m_font->getLineSpacing(characterSize);
    }

    f32 TTFont::getKerning(const u32 first, const u32 second, const u32 characterSize) const
    {
        return m_font->getKerning(first, second, characterSize);
    }

    ITexture *TTFont::getTexture(const u32 characterSize)
    {
        if (auto iterator(m_fontTexturesCache.find(characterSize)); iterator != m_fontTexturesCache.end()) 
        {
            return iterator->second.get();
        }

        auto nTexture(muptr<Texture>( &m_font->getTexture(characterSize), false));

        // What is needed here is to force the load of the font surface
        for (u32 i = 0U; i < 0xff; ++i)
            getTextureBounds(i, characterSize);

        auto *ret(nTexture.get());
        m_fontTexturesCache[characterSize] = std::move(nTexture);
        return ret;
    }
}
