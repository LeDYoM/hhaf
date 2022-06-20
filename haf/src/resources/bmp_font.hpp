HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP
#define HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/rawmemory.hpp>

#include <haf/include/resources/ibmp_font.hpp>

namespace haf::backend
{
class IFont;
class IBMPFont;
}

namespace haf::res
{
/**
 * @brief Class implementing a font loaded from a bitmap file
 */
class BMPFont : public IBMPFont
{
public:
    explicit BMPFont(backend::IBMPFont* font);
    ~BMPFont();

    htps::Rectf32 getBounds(const htps::u32 codePoint) const override;
    htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const override;
    htps::f32 getAdvance(const htps::u32 codePoint) const override;
    htps::f32 getLineSpacing() const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second) const override;
    htps::str getTexture(char const character) override;

private:
    backend::IBMPFont* ifont_;
};
}  // namespace haf::res

#endif
