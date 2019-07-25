#pragma once

#ifndef LIB_SCENE_BMPFONTINSTANCE_INCLUDE_HPP
#define LIB_SCENE_BMPFONTINSTANCE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/ifont.hpp>
#include "texture.hpp"

namespace lib::scene
{
    class BMFontPrivate;

    class BMPFont : public IFont
    {
    public:
        BMPFont();
        ~BMPFont() override;

        Rectf32 getBounds(const u32 codePoint) const override;
        Rectf32 getTextureBounds(const u32 codePoint) const override;
        f32 getAdvance(const u32 codePoint) const override;
        f32 getLineSpacing() const override;
        f32 getKerning(const u32 first, const u32 second) const override;
        sptr<ITexture> getTexture() const override;
        vector2df textSize(const str& text) const override;
        const vector2du32 &size() const;

    private:
        BMFontPrivate *fontPrivate;
        bool ParseFont(const str&);
    };
}

#endif
