#ifndef HAF_SCENE_TTFONTINSTANCE_INCLUDE_HPP
#define HAF_SCENE_TTFONTINSTANCE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include "texture.hpp"
#include <haf/resources/include/ifont.hpp>

namespace haf::res
{
class TTFont;

class TTFontInstance final : public IFont
{
public:
    htps::Rectf32 getBounds(const htps::u32 codePoint) const override;
    htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const override;
    htps::f32 getAdvance(const htps::u32 codePoint) const override;
    htps::f32 getLineSpacing() const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second) const override;
    htps::sptr<ITexture> getTexture() const override;
    htps::vector2df textSize(const htps::str& text) const override;
    ~TTFontInstance() override;
    TTFontInstance(const TTFont& parent, const htps::u32 characterSize);

private:
    const TTFont& m_parentInstance;
    htps::u32 m_characterSize;
    friend class TTFont;
};
}  // namespace haf::res

#endif
