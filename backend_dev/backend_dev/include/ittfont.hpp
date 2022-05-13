#ifndef HAF_BACKEND_ITTFONT_HPP
#define HAF_BACKEND_ITTFONT_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include "itexture.hpp"

namespace haf::backend
{
class ITTFont
{
public:
    ITTFont() {}
    virtual ~ITTFont() {}

    virtual htps::Rectf32 getBounds(htps::u32 const codePoint,
                                    htps::u32 const characterSize) const = 0;
    virtual htps::Rectf32 getTextureBounds(
        htps::u32 const codePoint,
        htps::u32 const characterSize) const                              = 0;
    virtual htps::f32 getAdvance(htps::u32 const codePoint,
                                 htps::u32 const characterSize) const     = 0;
    virtual htps::f32 getLineSpacing(htps::u32 const characterSize) const = 0;
    virtual htps::f32 getKerning(htps::u32 const first,
                                 htps::u32 const second,
                                 htps::u32 const characterSize) const     = 0;
    virtual ITexture* getTexture(
        htps::u32 const characterSize, char const character) = 0;
};
}  // namespace haf::backend

#endif
