#ifndef HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP
#define HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include <haf/resources/include/ifont.hpp>
#include <haf/resources/include/itexture.hpp>

namespace haf::res
{
class BMFontPrivate;

class BMPFont : public IFont
{
public:
    BMPFont(const mtps::str& file_name);
    ~BMPFont() override;

    mtps::Rectf32 getBounds(const mtps::u32 codePoint) const override;
    mtps::Rectf32 getTextureBounds(const mtps::u32 codePoint) const override;
    mtps::f32 getAdvance(const mtps::u32 codePoint) const override;
    mtps::f32 getLineSpacing() const override;
    mtps::f32 getKerning(const mtps::u32 first,
                         const mtps::u32 second) const override;
    mtps::sptr<ITexture> getTexture() const override;
    mtps::vector2df textSize(const mtps::str& text) const override;
    const mtps::vector2du32& size() const;

    mtps::vector<mtps::str> textureFileNames() const;
    void setTexturePages(
        const mtps::vector<mtps::sptr<ITexture>>& texture_pages);

private:
    mtps::rptr<BMFontPrivate> fontPrivate_;
    bool ParseFont(const mtps::str&);
};
}  // namespace haf::res

#endif
