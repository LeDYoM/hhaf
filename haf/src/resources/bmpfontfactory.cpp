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

sptr<BMPFont> BMPFontFactory::loadFromRawMemory(RawMemory*)
{
    sptr<BMPFont> font(msptr<BMPFont>(""));
    return font;
}
}  // namespace haf::res
