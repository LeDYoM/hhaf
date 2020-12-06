#ifndef HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

// TO be removed
#include "itexture.hpp"

namespace haf::res
{
/// This class provides the minimum interface for a font, independent
/// of its type
class IFont
{
public:
    virtual ~IFont() {}
    virtual mtps::Rectf32 getBounds(const mtps::u32 codePoint) const        = 0;
    virtual mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint) const = 0;
    virtual mtps::f32 getAdvance(const mtps::u32 codePoint) const           = 0;
    virtual mtps::f32 getLineSpacing() const                                = 0;
    virtual mtps::f32 getKerning(const mtps::u32 first,
                                 const mtps::u32 second) const              = 0;
    virtual mtps::sptr<ITexture> getTexture() const                         = 0;
    virtual mtps::vector2df textSize(const mtps::str& text) const           = 0;
};
}  // namespace haf::res

#endif
