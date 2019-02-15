#pragma once

#ifndef LIB_SCENE_TTFONT_INCLUDE_HPP
#define LIB_SCENE_TTFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include "texture.hpp"
#include "font.hpp"

namespace lib
{
    namespace backend
    {
        class ITTFont;
    }

    namespace scene
    {
        class TTFont final
        {
        public:
            TTFont(backend::ITTFont *font);
            ~TTFont();
			Rectf32 getBounds(const u32 codePoint, const u32 characterSize) const;
			Rectf32 getTextureBounds(const u32 codePoint, const u32 characterSize) const;
			f32 getAdvance(const u32 codePoint, const u32 characterSize) const;
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
			Rectf32 getBounds(const u32 codePoint) const override;
			Rectf32 getTextureBounds(const u32 codePoint) const override;
			f32 getAdvance(const u32 codePoint) const override;
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
