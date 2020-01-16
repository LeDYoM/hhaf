#pragma once

#ifndef LIB_SCENE_TTFONT_INCLUDE_HPP
#define LIB_SCENE_TTFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include "texture.hpp"
#include <lib/resources/include/ittfont.hpp>

namespace lib
{
    namespace backend
    {
        class ITTFont;
    }

    namespace scene
    {
        class TTFont final : public ITTFont
        {
        public:
            TTFont(backend::ITTFont *font);
            ~TTFont() override;
            Rectf32 getBounds(const u32 codePoint, const u32 characterSize) const override;
            Rectf32 getTextureBounds(const u32 codePoint, const u32 characterSize) const override;
            f32 getAdvance(const u32 codePoint, const u32 characterSize) const override;
            f32 getLineSpacing(const u32 characterSize) const override;
            f32 getKerning(const u32 first, const u32 second, const u32 characterSize) const override;
            sptr<ITexture> getTexture(const u32 characterSize) const override;
            vector2df textSize(const str& text, const u32 characterSize) const override;
            sptr<IFont> font(const u32 charactersize) override;
        private:
            struct FontPrivate;
            uptr<FontPrivate> m_private;
        };
    }
}

#endif
