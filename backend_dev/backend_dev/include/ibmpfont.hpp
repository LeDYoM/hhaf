#pragma once

#ifndef LIB_BACKEND_IBMPFONT_INCLUDE_HPP
#define LIB_BACKEND_IBMPFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include "itexture.hpp"

namespace lib::backend
{
class IBMPFont
{
public:
    IBMPFont() {}
    virtual ~IBMPFont() {}

    virtual Rectf32 getBounds(const u32 codePoint) const = 0;
    virtual Rectf32 getTextureBounds(const u32 codePoint) const = 0;
    virtual f32 getAdvance(const u32 codePoint) const = 0;
    virtual f32 getLineSpacing() const = 0;
    virtual f32 getKerning(const u32 first, const u32 second) const = 0;
    virtual ITexture *getTexture() = 0;
};
} // namespace lib::backend

#endif
