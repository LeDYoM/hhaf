#ifndef HAF_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ifont.hpp>

namespace haf::res
{
class ITTFont
{
public:
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
    virtual htps::sptr<ITexture> getTexture(
        const htps::u32 characterSize) const                              = 0;
    virtual htps::vector2df textSize(const htps::str& text,
                                     const htps::u32 characterSize) const = 0;
    virtual htps::sptr<IFont> font(const htps::u32 charactersize)         = 0;
};
}  // namespace haf::res

#endif
