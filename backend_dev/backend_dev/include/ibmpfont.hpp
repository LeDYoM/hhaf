#pragma once

#ifndef HAF_BACKEND_IBMPFONT_INCLUDE_HPP
#define HAF_BACKEND_IBMPFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include "itexture.hpp"

namespace haf::backend
{
class IBMPFont
{
public:
    IBMPFont() {}
    virtual ~IBMPFont() {}

    virtual mtps::Rectf32 getBounds(const mtps::u32 codePoint) const = 0;
    virtual mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint) const = 0;
    virtual mtps::f32 getAdvance(const mtps::u32 codePoint) const = 0;
    virtual mtps::f32 getLineSpacing() const = 0;
    virtual mtps::f32 getKerning(const mtps::u32 first, const mtps::u32 second) const = 0;
    virtual ITexture *getTexture() = 0;
};
} // namespace haf::backend

#endif
