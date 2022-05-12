HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TTFONTINSTANCE_INCLUDE_HPP
#define HAF_SCENE_TTFONTINSTANCE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ifont.hpp>

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
    htps::sptr<ITexture> getTexture() override;
    ~TTFontInstance();
    TTFontInstance(const TTFont& parent, const htps::u32 characterSize);

private:
    const TTFont& parent_instance_;
    htps::u32 character_size_;
    friend class TTFont;
};
}  // namespace haf::res

#endif
