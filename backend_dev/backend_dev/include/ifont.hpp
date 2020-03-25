#pragma once

#ifndef LIB_BACKEND_IFONT_HPP
#define LIB_BACKEND_IFONT_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include "itexture.hpp"

namespace lib::backend
{
class IFont
{
public:
    IFont() {}
    virtual ~IFont() {}

    virtual mtps::Rectf32 getBounds(const mtps::u32 codePoint) const = 0;
    virtual mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint) const = 0;
    virtual mtps::f32 getAdvance(const mtps::u32 codePoint) const = 0;
    virtual mtps::f32 getLineSpacing() const = 0;
    virtual mtps::f32 getKerning(const mtps::u32 first, const mtps::u32 second) const = 0;
    virtual ITexture *getTexture() = 0;
};
} // namespace lib::backend

#endif
