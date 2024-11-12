HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP
#define HAF_SCENE_FONT_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <facil_math/include/rect.hpp>
#include <htypes/include/str.hpp>

namespace haf::res
{
/// This class provides the minimum interface for a font, independent
/// of its type
class IFont
{
protected:
    ~IFont() = default;

public:
    virtual fmath::Rectf32 getBounds(const htps::u32 codePoint) const        = 0;
    virtual fmath::Rectf32 getTextureBounds(const htps::u32 codePoint) const = 0;
    virtual htps::f32 getAdvance(const htps::u32 codePoint) const           = 0;
    virtual htps::f32 getLineSpacing() const                                = 0;
    virtual htps::f32 getKerning(const htps::u32 first,
                                 const htps::u32 second) const              = 0;
    virtual htps::str getTexture(char const character)                      = 0;
};
}  // namespace haf::res

#endif
