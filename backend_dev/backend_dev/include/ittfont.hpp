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

    virtual htps::Rectf32 getBounds(const htps::u32 codePoint,
                                    const htps::u32 characterSize) const = 0;
    virtual htps::Rectf32 getTextureBounds(
        const htps::u32 codePoint,
        const htps::u32 characterSize) const                              = 0;
    virtual htps::f32 getAdvance(const htps::u32 codePoint,
                                 const htps::u32 characterSize) const     = 0;
    virtual htps::f32 getLineSpacing(const htps::u32 characterSize) const = 0;
    virtual htps::f32 getKerning(const htps::u32 first,
                                 const htps::u32 second,
                                 const htps::u32 characterSize) const     = 0;
    virtual ITexture* getTexture(const htps::u32 characterSize)           = 0;
};
}  // namespace haf::backend

#endif
