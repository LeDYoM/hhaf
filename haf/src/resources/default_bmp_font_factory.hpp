HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_DEFAULT_BMP_FONT_FACTORY_HPP
#define HAF_RESOURCES_DEFAULT_BMP_FONT_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/ibmp_font.hpp>

namespace haf::res
{
class DefaultBMPFont;

class DefaultBMPFontFactory final : public backend::IBMPFontFactory
{
public:
    backend::IBMPFont* loadFromRawMemory(htps::RawMemory* raw_memory) override;
    htps::vector<htps::str> textureFileNames(
        htps::sptr<DefaultBMPFont> font) const;
    void setTexturePages(
        htps::sptr<DefaultBMPFont> font,
        htps::vector<backend::ITexture const*> const& texture_pages);

private:
    htps::vector<htps::sptr<DefaultBMPFont>> bmpfont_cache_;
};
}  // namespace haf::res

#endif
