#include "bmpfontfactory.hpp"
#include "bmpfont.hpp"
#include "texture.hpp"
#include <htypes/include/str.hpp>

using namespace htps;

namespace haf::res
{
sptr<BMPFont> BMPFontFactory::loadFromFile(const str& file)
{
    sptr<BMPFont> font(msptr<BMPFont>(file));
    return font;
}

backend::IFont* BMPFontFactory::loadFromRawMemory(RawMemory* raw_memory)
{
    uptr<BMPFont> font{muptr<BMPFont>(raw_memory)};
//    RawMemory internal_raw_memory{*raw_memory};
//    font->loadFromMemory(internal_raw_memory.data(),
//                         internal_raw_memory.size());
//    uptr<TTFont> t{
//        muptr<TTFont>(std::move(font), std::move(internal_raw_memory))};
    bmpfont_cache_.push_back(std::move(font));
//    return (*(bmpfont_cache_.end() - 1)).get();

    return nullptr;
//    BMPFont* font = new BMPFont("");
//    return font;
}
}  // namespace haf::res
