HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_DEFAULT_BMP_FONT_INCLUDE_HPP
#define HAF_RESOURCES_DEFAULT_BMP_FONT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rawmemory.hpp>

#include <backend_dev/include/itexture.hpp>
#include <backend_dev/include/ibmp_font.hpp>

namespace haf::res
{
/**
 * @brief Class implementing a font loaded from a bitmap file
 *
 */
class DefaultBMPFont : public backend::IBMPFont
{
public:
    DefaultBMPFont();
    ~DefaultBMPFont();

    void loadFromMemory(htps::RawMemory* data);
    htps::Rectf32 getBounds(const htps::u32 codePoint) const override;
    htps::Rectf32 getTextureBounds(const htps::u32 codePoint) const override;
    htps::f32 getAdvance(const htps::u32 codePoint) const override;
    htps::f32 getLineSpacing() const override;
    htps::f32 getKerning(const htps::u32 first,
                         const htps::u32 second) const override;
    htps::str getTexture(char const character) override;
    const htps::vector2du32& size() const;

    htps::vector<htps::pair<htps::str, htps::str>> texturesToLoad() const;

private:
    class DefaultBMFontPrivate;
    htps::uptr<DefaultBMFontPrivate> p_;
};
}  // namespace haf::res

#endif
