#ifndef HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

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
    virtual htps::Rectf32 getBounds(const htps::u32 codePoint) const        = 0;
    virtual htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const = 0;
    virtual htps::f32 getAdvance(const htps::u32 codePoint) const           = 0;
    virtual htps::f32 getLineSpacing() const                                = 0;
    virtual htps::f32 getKerning(const htps::u32 first,
                                 const htps::u32 second) const              = 0;
    virtual htps::sptr<ITexture> getTexture() const                         = 0;
    virtual htps::vector2df textSize(const htps::str& text) const           = 0;
};
}  // namespace haf::res

#endif
