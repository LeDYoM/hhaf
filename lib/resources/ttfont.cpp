#include "ttfont.hpp"
#include "ttfontinstance.hpp"

#include <backend_dev/include/ittfont.hpp>
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

	Rectf32 TTFont::getBounds(const u32 codePoint, const u32 characterSize) const
	{
		return m_private->m_font->getBounds(codePoint, characterSize);
	}

	Rectf32 TTFont::getTextureBounds(const u32 codePoint, const u32 characterSize) const
	{
		return m_private->m_font->getTextureBounds(codePoint, characterSize);
	}

	f32 TTFont::getAdvance(const u32 codePoint, const u32 characterSize) const
	{
		return m_private->m_font->getAdvance(codePoint, characterSize);
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
                const f32 hspace{ getAdvance(L' ', characterSize) };

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
                const Rectf32 letterBox{ getBounds(curChar, characterSize) + vector2df{ x,y } };

                // Update the current bounds
                {
                    max.x = std::max(max.x, letterBox.right());
                    max.y = std::max(max.y, letterBox.bottom());
                }

                // Advance to the next character
				x += getAdvance(curChar, characterSize);
            }
        }
        return max;
    }

    sptr<Font> TTFont::font(const u32 charactersize)
    {
        if (auto iterator = m_private->m_fontMap.find(charactersize);
                iterator == m_private->m_fontMap.end())
        {
            sptr<TTFontInstance> newFont{msptr<TTFontInstance>(*this,charactersize)};
            return m_private->m_fontMap[charactersize] = newFont;
        }
        else
        {
            return (*iterator).second;
        }
    }
}
