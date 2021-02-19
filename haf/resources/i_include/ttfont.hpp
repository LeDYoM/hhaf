#ifndef HAF_SCENE_TTFONT_INCLUDE_HPP
#define HAF_SCENE_TTFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

#include "texture.hpp"
#include <haf/resources/include/ittfont.hpp>

namespace haf::backend
{
class ITTFont;
}

namespace haf::res
{
class TTFont final : public ITTFont
{
public:
    TTFont(backend::ITTFont* font);
    ~TTFont() override;
    htps::Rectf32 getBounds(const htps::u32 codePoint,
                            const htps::u32 characterSize) const override;
    htps::Rectf32 getTextureBounds(
        const htps::u32 codePoint,
        const htps::u32 characterSize) const override;
    htps::f32 getAdvance(const htps::u32 codePoint,
                         const htps::u32 characterSize) const override;
    htps::f32 getLineSpacing(const htps::u32 characterSize) const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second,
                         const htps::u32 characterSize) const override;
    htps::sptr<ITexture> getTexture(
        const htps::u32 characterSize) const override;
    htps::vector2df textSize(const htps::str& text,
                             const htps::u32 characterSize) const override;
    htps::sptr<IFont> font(const htps::u32 charactersize) override;

private:
    struct FontPrivate;
    htps::uptr<FontPrivate> m_private;
};
}  // namespace haf::res

#endif
