#ifndef HAF_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_ITTFONT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ifont.hpp>

namespace haf::res
{
class ITTFont
{
public:
    virtual ~ITTFont() {}
    virtual mtps::Rectf32 getBounds(const mtps::u32 codePoint,
                                    const mtps::u32 characterSize) const = 0;
    virtual mtps::Rectf32 getTextureBounds(
        const mtps::u32 codePoint,
        const mtps::u32 characterSize) const                              = 0;
    virtual mtps::f32 getAdvance(const mtps::u32 codePoint,
                                 const mtps::u32 characterSize) const     = 0;
    virtual mtps::f32 getLineSpacing(const mtps::u32 characterSize) const = 0;
    virtual mtps::f32 getKerning(const mtps::u32 first,
                                 const mtps::u32 second,
                                 const mtps::u32 characterSize) const     = 0;
    virtual mtps::sptr<ITexture> getTexture(
        const mtps::u32 characterSize) const                              = 0;
    virtual mtps::vector2df textSize(const mtps::str& text,
                                     const mtps::u32 characterSize) const = 0;
    virtual mtps::sptr<IFont> font(const mtps::u32 charactersize)         = 0;
};
}  // namespace haf::res

#endif
