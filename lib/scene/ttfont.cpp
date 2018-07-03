#include "ttfont.hpp"

#include <lib/include/backend/ittfont.hpp>
#include <lib/include/backend/ittfontfactory.hpp>

#include <lib/core/backendfactory.hpp>

namespace lib::scene
{
    using namespace backend;

    TTFont::TTFont(backend::ITTFont* font) : m_font{ std::move(font) } {}

    bool TTFont::loadFromFile(const str & filename)
    {
        m_font = ttfontFactory().loadFromFile(filename);
        return m_font != nullptr;
    }

    TTGlyph TTFont::getGlyph(const u32 codePoint, const u32 characterSize) const
    {
        return TTGlyph(m_font->getGlyph(codePoint, characterSize));
    }

    f32 TTFont::getLineSpacing(const u32 characterSize) const
    {
        return m_font->getLineSpacing(characterSize);
    }

    f32 TTFont::getKerning(const u32 first, const u32 second, const u32 characterSize) const
    {
        return m_font->getKerning(first, second, characterSize);
    }

    sptr<Texture> TTFont::getTexture(const u32 characterSize) const
    {
        return msptr<Texture>(m_font->getTexture(characterSize));
    }

    void TTFont::ensureLoadGlyphs(const u32 first, const u32 last, const u32 characterSize)
    {
        for (u32 codePoint = first; codePoint <= last; ++codePoint) {
            (void)(m_font->getGlyph(codePoint, characterSize));
        }
    }

    void TTFont::ensureLoadASCIIGlyps(const u32 characterSize)
    {
        ensureLoadGlyphs(0,255, characterSize);
    }

    Rectf32 TTFont::textBox(const lib::str& text,
                                           const u32 characterSize) const
    {
        if (text.empty()) {
            return {};
        }

        const f32 vspace{ getLineSpacing(characterSize) };

        f32 x{ 0.f };
        f32 y{ static_cast<f32>(characterSize) };

        // Create one quad for each character
        f32 minX{ y };
        f32 minY{ y };
        f32 maxX{ 0.f };
        f32 maxY{ 0.f };
        u32 prevChar{ 0 };

        for (auto&& curChar : text)
        {
            // Apply the kerning offset
            x += getKerning(prevChar, curChar, characterSize);
            prevChar = curChar;

            // Handle special characters
            if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
            {
                using namespace std;

                // Update the current bounds (min coordinates)
                minX = min(minX, x);
                minY = min(minY, y);
                const f32 hspace{ getGlyph(L' ', characterSize).advance };

                switch (curChar)
                {
                    case ' ':  x += hspace;        break;
                    case '\t': x += hspace * 4;    break;
                    case '\n': y += vspace; x = 0; break;
                }

                // Update the current bounds (max coordinates)
                maxX = max(maxX, x);
                maxY = max(maxY, y);
            }
            else
            {
                const TTGlyph glyph{ getGlyph(curChar, characterSize) };
                const Rectf32 letterBox{ glyph.bounds + vector2df{ x,y } };

                // Update the current bounds
                {
                    using namespace std;
                    minX = min(minX, letterBox.left);
                    maxX = max(maxX, letterBox.right());
                    minY = min(minY, letterBox.top);
                    maxY = max(maxY, letterBox.bottom());
                }

                // Advance to the next character
                x += glyph.advance;
            }
        }
        return {minX, minY, maxX, maxY };
    }
}
