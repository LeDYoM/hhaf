#pragma once

#ifndef LIB_SCENE_FONT_INTERFACE_INCLUDE_HPP__
#define LIB_SCENE_FONT_INTERFACE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/texture.hpp>
#include <lib/include/backend/ittfont.hpp>

namespace lib
{
    namespace scene
    {
        struct TTGlyph final : public backend::ITTGlyph
        {
            TTGlyph(const backend::ITTGlyph &rhs) : backend::ITTGlyph{ rhs } {}
        };

        /// This class provides the minimum interface for a font, independent
        /// of its type
        class Font
        {
        public:
            virtual ~Font() {}
            virtual TTGlyph getGlyph(const u32 codePoint) const = 0;
            virtual f32 getLineSpacing() const = 0;
            virtual f32 getKerning(const u32 first, const u32 second) const = 0;
            virtual sptr<Texture> getTexture() const = 0;
            virtual vector2df textSize(const str& text) const = 0;
        };
    }
}

#endif
