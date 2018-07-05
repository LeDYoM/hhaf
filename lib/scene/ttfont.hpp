#pragma once

#ifndef LIB_SCENE_TTFONT_INCLUDE_HPP__
#define LIB_SCENE_TTFONT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/texture.hpp>
#include <lib/include/backend/ittfont.hpp>

namespace lib
{
    namespace backend
    {
        class IFont;
    }

    namespace scene
    {
        struct TTGlyph final : public backend::ITTGlyph
        {
            TTGlyph(const backend::ITTGlyph &rhs) : backend::ITTGlyph{ rhs } {}
        };

        class TTFont final
        {
        public:
            TTFont(backend::ITTFont *font);
            bool loadFromFile(const str& filename);
            TTGlyph getGlyph(const u32 codePoint, const u32 characterSize) const;
            f32 getLineSpacing(const u32 characterSize) const;
            f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const;
            sptr<Texture> getTexture(const u32 characterSize) const;
            void ensureLoadGlyphs(const u32 first, const u32 last, const u32 characterSize);
            void ensureLoadASCIIGlyps(const u32 characterSize);
            vector2df textSize(const str& text, const u32 characterSize) const;
        private:
            backend::ITTFont* m_font;
        };
    }
}

#endif
