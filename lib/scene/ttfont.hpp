#pragma once

#ifndef LIB_SCENE_TTFONT_INCLUDE_HPP__
#define LIB_SCENE_TTFONT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/font.hpp>
#include <lib/include/backend/ittfont.hpp>

namespace lib
{
    namespace backend
    {
        class IFont;
    }

    namespace scene
    {
        class TTFont final
        {
        public:
            TTFont(backend::ITTFont *font);
            ~TTFont();
            bool loadFromFile(const str& filename);
            TTGlyph getGlyph(const u32 codePoint, const u32 characterSize) const;
            f32 getLineSpacing(const u32 characterSize) const;
            f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const;
            sptr<Texture> getTexture(const u32 characterSize) const;
            vector2df textSize(const str& text, const u32 characterSize) const;
            sptr<Font> font(const u32 charactersize);
        private:
            struct FontPrivate;
            uptr<FontPrivate> m_private;
        };

        class TTFontInstance : public Font
        {
        public:
            TTGlyph getGlyph(const u32 codePoint) const override;
            f32 getLineSpacing() const override;
            f32 getKerning(const u32 first, const u32 second) const override;
            sptr<Texture> getTexture() const override;
            vector2df textSize(const str& text) const override;
        private:
            TTFontInstance(const TTFont &parent, u32 characterSize);
            const TTFont &m_parentInstance;
            u32 m_characterSize;
            friend class TTFont;
        };
    }
}

#endif
