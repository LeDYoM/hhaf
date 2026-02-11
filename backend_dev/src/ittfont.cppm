export module backend_dev:ittfont;

import facil_math;
import htypes;

namespace haf::backend
{
export class ITTFont
{
public:
    virtual ~ITTFont() = default;

    virtual fmath::Rectf32 getBounds(htps::u32 const codePoint,
                                     htps::u32 const characterSize) const = 0;
    virtual fmath::Rectf32 getTextureBounds(
        htps::u32 const codePoint,
        htps::u32 const characterSize) const                              = 0;
    virtual htps::f32 getAdvance(htps::u32 const codePoint,
                                 htps::u32 const characterSize) const     = 0;
    virtual htps::f32 getLineSpacing(htps::u32 const characterSize) const = 0;
    virtual htps::f32 getKerning(htps::u32 const first,
                                 htps::u32 const second,
                                 htps::u32 const characterSize) const     = 0;
    virtual htps::str getTexture(htps::u32 const characterSize,
                                 char const character)                    = 0;
};
}  // namespace haf::backend
