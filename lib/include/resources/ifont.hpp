#pragma once

#ifndef LIB_SCENE_FONT_INTERFACE_INCLUDE_HPP
#define LIB_SCENE_FONT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

// TO be removed
#include "itexture.hpp"

namespace lib::scene
{
    /// This class provides the minimum interface for a font, independent
    /// of its type
    class IFont
    {
    public:
        virtual ~IFont() {}
        virtual Rectf32 getBounds(const u32 codePoint) const = 0;
        virtual Rectf32 getTextureBounds(const u32 codePoint) const = 0;
        virtual f32 getAdvance(const u32 codePoint) const = 0;
        virtual f32 getLineSpacing() const = 0;
        virtual f32 getKerning(const u32 first, const u32 second) const = 0;
        virtual sptr<ITexture> getTexture() const = 0;
        virtual vector2df textSize(const str& text) const = 0;
    };
}

#endif
