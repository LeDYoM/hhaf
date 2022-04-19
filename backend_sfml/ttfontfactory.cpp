#include "ttfontfactory.hpp"
#include "ttfont.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
ITTFont* TTFontFactory::loadFromRawMemory(RawMemory* raw_memory)
{
    uptr<sf::Font> font(muptr<sf::Font>());
    RawMemory internal_raw_memory(*raw_memory);
    font->loadFromMemory(internal_raw_memory.data(),
                         internal_raw_memory.size());
    uptr<TTFont> t{
        muptr<TTFont>(std::move(font), std::move(internal_raw_memory))};
    font_cache_.push_back(std::move(t));
    return (*(font_cache_.end() - 1)).get();
}

TTFontFactory::~TTFontFactory()
{
    font_cache_.clear();
    font_cache_.shrink_to_fit();
}
}  // namespace haf::backend::sfmlb
