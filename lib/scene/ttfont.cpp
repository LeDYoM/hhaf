#include "ttfont.hpp"

#include <lib/backend/ittfont.hpp>
#include <lib/backend/ittfontfactory.hpp>
#include <lib/backend/backendfactory.hpp>

namespace lib
{
    namespace scene
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

        void TTFont::ensureLoadGlyphs(const u32 first, const u32 last)
        {
            for (u32 codePoint = first;i <= last; ++i) {
                (void)(m_font->getGlyph(codePoint, characterSize));
            }
        }

        void TTFont::ensureLoadASCIIGlyps()
        {
            ensureLoadGlyphs(0,255);
        }
    }
}
