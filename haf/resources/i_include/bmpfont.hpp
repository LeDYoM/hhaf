#ifndef HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP
#define HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>

namespace haf::res
{
class BMFontPrivate;

class BMPFont : public IFont
{
public:
    BMPFont(const htps::str& file_name);
    ~BMPFont() override;

    htps::Rectf32 getBounds(const htps::u32 codePoint) const override;
    htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const override;
    htps::f32 getAdvance(const htps::u32 codePoint) const override;
    htps::f32 getLineSpacing() const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second) const override;
    htps::sptr<ITexture> getTexture() const override;
    htps::vector2df textSize(const htps::str& text) const override;
    const htps::vector2du32& size() const;

    htps::vector<htps::str> textureFileNames() const;
    void setTexturePages(
        const htps::vector<htps::sptr<ITexture>>& texture_pages);

private:
    htps::rptr<BMFontPrivate> fontPrivate_;
    bool ParseFont(const htps::str&);
};
}  // namespace haf::res

#endif
