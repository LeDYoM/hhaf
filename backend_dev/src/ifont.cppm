export module backend_dev:ifont;

import htypes;
import facil_math;

namespace haf::backend
{
class IFont
{
protected:
    ~IFont() = default;

public:
    virtual fmath::Rectf32 getBounds(const htps::u32 codePoint) const = 0;
    virtual fmath::Rectf32 getTextureBounds(
        const htps::u32 codePoint) const                          = 0;
    virtual htps::f32 getAdvance(const htps::u32 codePoint) const = 0;
    virtual htps::f32 getLineSpacing() const                      = 0;
    virtual htps::f32 getKerning(const htps::u32 first,
                                 const htps::u32 second) const    = 0;
    virtual htps::str getTexture(char const character)            = 0;
};
}  // namespace haf::backend
