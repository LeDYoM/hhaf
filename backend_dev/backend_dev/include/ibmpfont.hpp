#ifndef HAF_BACKEND_IBMPFONT_INCLUDE_HPP
#define HAF_BACKEND_IBMPFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include "itexture.hpp"

namespace haf::backend
{
class IBMPFont
{
public:
    IBMPFont() {}
    virtual ~IBMPFont() {}

    virtual htps::Rectf32 getBounds(const htps::u32 codePoint) const        = 0;
    virtual htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const = 0;
    virtual htps::f32 getAdvance(const htps::u32 codePoint) const           = 0;
    virtual htps::f32 getLineSpacing() const                                = 0;
    virtual htps::f32 getKerning(const htps::u32 first,
                                 const htps::u32 second) const              = 0;
    virtual ITexture* getTexture()                                          = 0;
};
}  // namespace haf::backend

#endif
