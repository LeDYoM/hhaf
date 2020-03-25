#pragma once

#ifndef LIB_BACKEND_ITTFONT_HPP
#define LIB_BACKEND_ITTFONT_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include "itexture.hpp"

namespace lib::backend
{
class ITTFont
{
public:
    ITTFont() {}
    virtual ~ITTFont() {}

    virtual mtps::Rectf32 getBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const = 0;
    virtual mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const = 0;
    virtual mtps::f32 getAdvance(const mtps::u32 codePoint, const mtps::u32 characterSize) const = 0;
    virtual mtps::f32 getLineSpacing(const mtps::u32 characterSize) const = 0;
    virtual mtps::f32 getKerning(const mtps::u32 first, const mtps::u32 second, const mtps::u32 characterSize) const = 0;
    virtual ITexture *getTexture(const mtps::u32 characterSize) = 0;
};
} // namespace lib::backend

#endif
