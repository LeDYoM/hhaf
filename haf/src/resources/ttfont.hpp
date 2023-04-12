HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TTFONT_INCLUDE_HPP
#define HAF_SCENE_TTFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

#include <haf/include/resources/texture.hpp>
#include <haf/include/resources/ittfont.hpp>

namespace haf::backend
{
class ITTFont;
}

namespace haf::res
{
class TTFont final : public ITTFont
{
public:
    TTFont(backend::ITTFont* const font);
    ~TTFont();
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
    htps::str getTexture(const htps::u32 characterSize,
                                    char const character) const override;
    htps::sptr<IFont> font(const htps::u32 charactersize) override;

private:
    struct FontPrivate;
    htps::uptr<FontPrivate> priv_;
};
}  // namespace haf::res

#endif
