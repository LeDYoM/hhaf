#include "ttfont.hpp"

#include <lib/include/backend/ittfont.hpp>
#include <lib/core/backendfactory.hpp>

#include <map>
#include <algorithm>

namespace lib::scene
{
    using namespace backend;

    struct TTFont::FontPrivate
    {
        ITTFont *m_font;
        std::map<u32,sptr<TTFontInstance>> m_fontMap;
    };

    TTFont::TTFont(backend::ITTFont* font) :
        m_private{ new FontPrivate{ std::move(font) } } {}

    TTFont::~TTFont() = default;

    TTGlyph TTFont::getGlyph(const u32 codePoint, const u32 characterSize) const
    {
        return TTGlyph(m_private->m_font->getGlyph(codePoint, characterSize));
    }

    f32 TTFont::getLineSpacing(const u32 characterSize) const
    {
        return m_private->m_font->getLineSpacing(characterSize);
    }

    f32 TTFont::getKerning(const u32 first, const u32 second, const u32 characterSize) const
    {
        return m_private->m_font->getKerning(first, second, characterSize);
    }

    sptr<Texture> TTFont::getTexture(const u32 characterSize) const
    {
        return msptr<Texture>(m_private->m_font->getTexture(characterSize));
    }

    vector2df TTFont::textSize(const lib::str& text,
                                           const u32 characterSize) const
    {
        if (text.empty()) {
            return {};
        }

        const f32 vspace{ getLineSpacing(characterSize) };

        f32 x{ 0.f };
        f32 y{ static_cast<f32>(characterSize) };

        // Create one quad for each character
        vector2df max{};
        u32 prevChar{ 0 };

        for (auto curChar : text)
        {
            // Apply the kerning offset
            x += getKerning(prevChar, curChar, characterSize);
            prevChar = curChar;

            // Handle special characters
            if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
            {
                // Update the current bounds (min coordinates)
                const f32 hspace{ getGlyph(L' ', characterSize).advance };

                switch (curChar)
                {
                    case ' ':  x += hspace;        break;
                    case '\t': x += hspace * 4;    break;
                    case '\n': y += vspace; x = 0; break;
                }

                // Update the current bounds (max coordinates)
                max.x = std::max(max.x, x);
                max.y = std::max(max.y, y);
            }
            else
            {
                const TTGlyph glyph{ getGlyph(curChar, characterSize) };
                const Rectf32 letterBox{ glyph.bounds + vector2df{ x,y } };

                // Update the current bounds
                {
                    max.x = std::max(max.x, letterBox.right());
                    max.y = std::max(max.y, letterBox.bottom());
                }

                // Advance to the next character
                x += glyph.advance;
            }
        }
        return max;
    }

    sptr<Font> TTFont::font(const u32 charactersize)
    {
        if (auto iterator = m_private->m_fontMap.find(charactersize);
                iterator == m_private->m_fontMap.end())
        {
            sptr<TTFontInstance> newFont{new TTFontInstance{*this,charactersize}};
            return m_private->m_fontMap[charactersize] = newFont;
        }
        else
        {
            return (*iterator).second;
        }
    }

    TTFontInstance::TTFontInstance(const TTFont &parent, u32 characterSize)
        : m_parentInstance{parent}, m_characterSize{characterSize}
    {
    }

    TTGlyph TTFontInstance::getGlyph(const u32 codePoint) const
    {
        return m_parentInstance.getGlyph(codePoint, m_characterSize);
    }

    f32 TTFontInstance::getLineSpacing() const
    {
        return m_parentInstance.getLineSpacing(m_characterSize);
    }

    f32 TTFontInstance::getKerning(const u32 first, const u32 second) const
    {
        return m_parentInstance.getKerning(first, second, m_characterSize);
    }

    sptr<Texture> TTFontInstance::getTexture() const
    {
        return m_parentInstance.getTexture(m_characterSize);
    }

    vector2df TTFontInstance::textSize(const str&text) const
    {
        return m_parentInstance.textSize(text, m_characterSize);
    }
}
