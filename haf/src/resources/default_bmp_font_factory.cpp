#include "default_bmp_font_factory.hpp"
#include "bmp_font.hpp"
#include "texture.hpp"
#include <htypes/include/str.hpp>
#include "resource_loaders/default_resources/default_bmp_font.hpp"

using namespace htps;

namespace haf::res
{
backend::IBMPFont* DefaultBMPFontFactory::loadFromRawMemory(
    RawMemory* raw_memory)
{
    sptr<DefaultBMPFont> font{msptr<DefaultBMPFont>()};
    font->loadFromMemory(raw_memory);
    bmpfont_cache_.push_back(htps::move(font));
    return bmpfont_cache_.back().get();
}

vector<str> DefaultBMPFontFactory::textureFileNames(
    sptr<DefaultBMPFont> font) const
{
    return font->textureFileNames();
}

void DefaultBMPFontFactory::setTexturePages(
    sptr<DefaultBMPFont> font,
    vector<backend::ITexture const*> const& texture_pages)
{
    font->setTexturePages(texture_pages);
}

}  // namespace haf::res
