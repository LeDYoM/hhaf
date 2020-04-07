#pragma once

#ifndef HAF_SCENE_TTFONT_INCLUDE_HPP
#define HAF_SCENE_TTFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>

#include "texture.hpp"
#include <lib/resources/include/ittfont.hpp>

namespace haf
{
namespace backend
{
class ITTFont;
}

namespace scene
{
class TTFont final : public ITTFont
{
public:
    TTFont(backend::ITTFont *font);
    ~TTFont() override;
    mtps::Rectf32 getBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
    mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
    mtps::f32 getAdvance(const mtps::u32 codePoint, const mtps::u32 characterSize) const override;
    mtps::f32 getLineSpacing(const mtps::u32 characterSize) const override;
    mtps::f32 getKerning(const mtps::u32 first, const mtps::u32 second, const mtps::u32 characterSize) const override;
    mtps::sptr<ITexture> getTexture(const mtps::u32 characterSize) const override;
    mtps::vector2df textSize(const mtps::str &text, const mtps::u32 characterSize) const override;
    mtps::sptr<IFont> font(const mtps::u32 charactersize) override;

private:
    struct FontPrivate;
    mtps::uptr<FontPrivate> m_private;
};
} // namespace scene
} // namespace haf

#endif
