#include "bmpfontfactory.hpp"
#include "bmpfont.hpp"
#include "texture.hpp"

using namespace htps;

namespace haf::res
{
sptr<BMPFont> BMPFontFactory::loadFromFile(const str& file)
{
    sptr<BMPFont> font(msptr<BMPFont>(file));
    return font;
}

backend::IFont* BMPFontFactory::loadFromRawMemory(RawMemory*)
{
    return nullptr;
//    BMPFont* font = new BMPFont("");
//    return font;
}
}  // namespace haf::res
