#include <resources/i_include/ttfont.hpp>
#include <resources/i_include/ttfontinstance.hpp>

#include <backend_dev/include/ittfont.hpp>

#include <map>
#include <algorithm>

using namespace mtps;

namespace haf::res
{
struct TTFont::FontPrivate
{
    FontPrivate(backend::ITTFont* font) : m_font{font} {}
    backend::ITTFont* m_font;
    std::map<u32, sptr<TTFontInstance>> m_fontMap;
};

TTFont::TTFont(backend::ITTFont* font) : m_private{muptr<FontPrivate>(font)}
{}

TTFont::~TTFont() = default;

Rectf32 TTFont::getBounds(const u32 codePoint, const u32 characterSize) const
{
    return m_private->m_font->getBounds(codePoint, characterSize);
}

Rectf32 TTFont::getTextureBounds(const u32 codePoint,
                                 const u32 characterSize) const
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

f32 TTFont::getKerning(const u32 first,
                       const u32 second,
                       const u32 characterSize) const
{
    return m_private->m_font->getKerning(first, second, characterSize);
}

sptr<ITexture> TTFont::getTexture(const u32 characterSize) const
{
    return std::dynamic_pointer_cast<ITexture>(
        msptr<Texture>(m_private->m_font->getTexture(characterSize)));
}

vector2df TTFont::textSize(const str& text, const u32 characterSize) const
{
    if (text.empty())
    {
        return {};
    }

    const f32 vspace{getLineSpacing(characterSize)};

    f32 x{0.f};
    f32 y{static_cast<f32>(characterSize)};

    // Create one quad for each character
    vector2df max{};
    u32 prevChar{0};

    for (auto curChar : text)
    {
        // Apply the kerning offset
        x += getKerning(prevChar, curChar, characterSize);
        prevChar = curChar;

        // Handle special characters
        if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
        {
            // Update the current bounds (min coordinates)
            const f32 hspace{getAdvance(L' ', characterSize)};

            switch (curChar)
            {
                case ' ':
                    x += hspace;
                    break;
                case '\t':
                    x += hspace * 4;
                    break;
                case '\n':
                    y += vspace;
                    x = 0;
                    break;
            }

            // Update the current bounds (max coordinates)
            max.x = std::max(max.x, x);
            max.y = std::max(max.y, y);
        }
        else
        {
            const Rectf32 letterBox{getBounds(curChar, characterSize) +
                                    vector2df{x, y}};

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

sptr<IFont> TTFont::font(const u32 charactersize)
{
    if (auto iterator = m_private->m_fontMap.find(charactersize);
        iterator == m_private->m_fontMap.end())
    {
        sptr<TTFontInstance> newFont{
            msptr<TTFontInstance>(*this, charactersize)};
        return m_private->m_fontMap[charactersize] = newFont;
    }
    else
    {
        return (*iterator).second;
    }
}
}  // namespace haf::res
