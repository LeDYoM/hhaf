#ifndef HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP
#define HAF_SCENE_RESOURCES_BMPFONT_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/resources/ifont.hpp>
#include <haf/include/resources/itexture.hpp>

namespace haf::res
{
/**
 * @brief Class implementing a font loaded from a bitmap file
 * 
 */
class BMPFont : public IFont
{
public:
    explicit BMPFont(const htps::str& file_name);
    ~BMPFont() override;

    htps::Rectf32 getBounds(const htps::u32 codePoint) const override;
    htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const override;
    htps::f32 getAdvance(const htps::u32 codePoint) const override;
    htps::f32 getLineSpacing() const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second) const override;
    htps::sptr<ITexture> getTexture() const override;
    const htps::vector2du32& size() const;

    htps::vector<htps::str> textureFileNames() const;
    void setTexturePages(
        const htps::vector<htps::sptr<ITexture>>& texture_pages);

private:
    class BMFontPrivate;
    htps::uptr<BMFontPrivate> p_;
};
}  // namespace haf::res

#endif
