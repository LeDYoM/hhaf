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
    /*
            uptr<sf::Font> font(muptr<sf::Font>());
            RawMemory internal_raw_memory(*raw_memory);
            font->loadFromMemory(internal_raw_memory.data(),
       internal_raw_memory.size()); uptr<TTFont> t{
       muptr<TTFont>(std::move(font), std::move(internal_raw_memory)) };
            m_fontCache.push_back(std::move(t));
            return (*(m_fontCache.end() - 1)).get();
            */
}
}  // namespace haf::res
