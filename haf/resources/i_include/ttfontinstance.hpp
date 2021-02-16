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
    mtps::Rectf32 getBounds(const mtps::u32 codePoint) const override;
    mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint) const override;
    mtps::f32 getAdvance(const mtps::u32 codePoint) const override;
    mtps::f32 getLineSpacing() const override;
    mtps::f32 getKerning(const mtps::u32 first,
                         const mtps::u32 second) const override;
    mtps::sptr<ITexture> getTexture() const override;
    mtps::vector2df textSize(const mtps::str& text) const override;
    ~TTFontInstance() override;
    TTFontInstance(const TTFont& parent, const mtps::u32 characterSize);

private:
    const TTFont& m_parentInstance;
    mtps::u32 m_characterSize;
    friend class TTFont;
};
}  // namespace haf::res

#endif
