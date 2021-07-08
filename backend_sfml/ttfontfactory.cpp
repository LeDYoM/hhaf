#include "ttfontfactory.hpp"
#include "ttfont.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "texture.hpp"

using namespace htps;

namespace haf::backend::sfmlb
{
ITTFont* TTFontFactory::loadFromFile(const str& file)
{
    uptr<sf::Font> font(muptr<sf::Font>());
    font->loadFromFile(file.c_str());
    uptr<TTFont> t{muptr<TTFont>(std::move(font), RawMemory{})};
    m_fontCache.push_back(std::move(t));
    return (*(m_fontCache.end() - 1)).get();
}

ITTFont* TTFontFactory::loadFromRawMemory(RawMemory* raw_memory)
{
    uptr<sf::Font> font(muptr<sf::Font>());
    RawMemory internal_raw_memory(*raw_memory);
    font->loadFromMemory(internal_raw_memory.data(),
                         internal_raw_memory.size());
    uptr<TTFont> t{
        muptr<TTFont>(std::move(font), std::move(internal_raw_memory))};
    m_fontCache.push_back(std::move(t));
    return (*(m_fontCache.end() - 1)).get();
}

TTFontFactory::~TTFontFactory()
{
    m_fontCache.clear();
    m_fontCache.shrink_to_fit();
}
}  // namespace haf::backend::sfmlb
