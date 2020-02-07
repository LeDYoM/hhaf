#pragma once

#ifndef LIB_SCENE_TTFONTINSTANCE_INCLUDE_HPP
#define LIB_SCENE_TTFONTINSTANCE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include "texture.hpp"
#include <lib/resources/include/ifont.hpp>

namespace lib::scene
{
    class TTFont;

    class TTFontInstance : public IFont
    {
    public:
        Rectf32 getBounds(const u32 codePoint) const override;
        Rectf32 getTextureBounds(const u32 codePoint) const override;
        f32 getAdvance(const u32 codePoint) const override;
        f32 getLineSpacing() const override;
        f32 getKerning(const u32 first, const u32 second) const override;
        sptr<ITexture> getTexture() const override;
        vector2df textSize(const str& text) const override;
        ~TTFontInstance() override;
        TTFontInstance(const TTFont &parent, const u32 characterSize);
    private:
        const TTFont &m_parentInstance;
        u32 m_characterSize;
        friend class TTFont;
    };
}

#endif
